//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                https://github.com/casm-lang/libcasm-fe
//
//  This file is part of libcasm-fe.
//
//  libcasm-fe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-fe is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//

#include "ExecutionPassBase.h"

#include "cpp/Default.h"
#include "cpp/Math.h"
#include "cpp/Type.h"

#include <sys/wait.h>

#include "../Driver.h"
#include "../Exceptions.h"
#include "../Symbols.h"

using namespace libcasm_fe;

extern Driver* global_driver;

u1 ExecutionPassBase::hasEmptyUpdateSet() const
{
    return updateSetManager.currentUpdateSet()->empty();
}

Update* ExecutionPassBase::addUpdate( Function* function,
    const std::vector< value_t >& arguments, const value_t& value,
    const location& location )
{
    if( function->checkArguments )
    {
        try
        {
            validateArguments( function->arguments_, arguments );
        }
        catch( const std::domain_error& e )
        {
            throw RuntimeException( location, e.what(),
                libcasm_fe::Code::FunctionArgumentsInvalidRangeAtUpdate );
        }
    }

    if( function->checkReturnValue )
    {
        try
        {
            validateValue( function->return_type_, value );
        }
        catch( const std::domain_error& e )
        {
            throw RuntimeException( location,
                std::string( e.what() ) + " of `" + function->name + "`",
                libcasm_fe::Code::FunctionValueInvalidRangeAtUpdate );
        }
    }

    auto& function_map = function_states[ function->id ];
    auto it = function_map.find( arguments ); // TODO EP: use emplace only
    if( it == function_map.end() )
    {
        const auto defaultValue
            = ExecutionPassBase::defaultFunctionValue( function, arguments );
        const auto pair = function_map.insert( arguments, defaultValue );
        it = pair.first;
    }

    Update* up = reinterpret_cast< Update* >(
        stack.allocate( sizeof( Update ) ) ); // FIXME make it nicer!!
    up->value = std::move( value );
    up->func = function->id;
    up->args = &it.key();
    up->location = &location;

    try
    {
        updateSetManager.add( &it.value(), up );
    }
    catch( const ExecutionUpdateSet::Conflict& e )
    {
        const auto& conflictingUpdate = e.conflictingUpdate();
        const auto& existingUpdate = e.existingUpdate();

        const auto& conflictingValue = conflictingUpdate.second;
        const auto& existingValue = existingUpdate.second;

        const auto info
            = "Conflict while adding update " + function->name
              + to_string( *conflictingValue->args ) + " = " + value.to_str()
              + " at line "
              + std::to_string( conflictingValue->location->begin.line )
              + ", conflicting with line "
              + std::to_string( existingValue->location->begin.line )
              + " with value '" + existingValue->value.to_str() + "'";
        throw RuntimeException(
            { existingValue->location, conflictingValue->location }, info,
            libcasm_fe::Codes::UpdateSetClash );
    }

    return up;
}

void ExecutionPassBase::fork( ExecutionUpdateSet::Semantics semantics )
{
    updateSetManager.fork( semantics, 100UL );
}

void ExecutionPassBase::merge()
{
    try
    {
        updateSetManager.merge();
    }
    catch( const ExecutionUpdateSet::Conflict& e )
    {
        const auto& conflictingUpdate = e.conflictingUpdate();
        const auto& existingUpdate = e.existingUpdate();

        const auto& conflictingValue = conflictingUpdate.second;
        const auto& existingValue = existingUpdate.second;

        const auto function = function_symbols[ conflictingValue->func ];
        const auto functionLocation
            = function->name + to_string( *conflictingValue->args );

        const auto info
            = "Conflict while merging updateset " + functionLocation
              + " at line "
              + std::to_string( conflictingValue->location->begin.line )
              + " with value '" + conflictingValue->value.to_str() + "'"
              + " and at line "
              + std::to_string( existingValue->location->begin.line )
              + " with value '" + existingValue->value.to_str() + "'";
        throw RuntimeException(
            { existingValue->location, conflictingValue->location }, info,
            libcasm_fe::Codes::UpdateSetMergeConflict );
    }
}

void ExecutionPassBase::applyUpdates()
{
    assert( updateSetManager.size() == 1 );

    std::vector< value_t* > to_fold;

    auto updateSet = updateSetManager.currentUpdateSet();
    const auto end = updateSet->end();
    for( auto it = updateSet->begin(); it != end; ++it )
    {
        value_t* location = const_cast< value_t* >( it.key() );
        Update* u = it.value();

        // TODO handle tuples
        if( u->value.type == TypeType::LIST )
        {
            if( u->value.is_undef() )
            {
                // set list to undef
                if( not location->is_undef() )
                {
                    location->value.list->decrease_usage();
                    location->type = TypeType::UNDEF;
                }
            }
            else
            {
                if( not location->is_undef() and not location->is_symbolic() )
                {
                    location->value.list->decrease_usage();
                }
                else
                {
                    location->type = u->value.type;
                }
                location->value.list = u->value.value.list;
                location->value.list->bump_usage();
                to_fold.push_back( location );
            }
        }
        else
        {
            // we could erase keys that store an undef value in concrete mode,
            // but we need to know if a key was set to undef explicitly in
            // symbolic
            // mode
            *location = std::move( u->value );
        }
    }
    updateSetManager.clear();

    // Handle lists
    // 1. convert chained lists to BottomLists
    for( value_t* v : to_fold )
    {
        BottomList* new_l = v->value.list->collect();
        if( new_l->check_allocated_and_set_to_false() )
        {
            temp_lists.push_back( new_l );
        }
        v->value.list = new_l;
    }

    // delete all list objects, except BottomLists that are currently used
    std::vector< size_t > deleted;
    for( size_t i = 0; i < temp_lists.size(); i++ )
    {
        if( !( temp_lists[ i ]->is_bottom()
                && reinterpret_cast< BottomList* >( temp_lists[ i ] )
                       ->is_used() ) )
        {
            delete temp_lists[ i ];
            deleted.push_back( i );
        }
    }

    // remove deleted lists from temp_lists
    for( size_t del : deleted )
    {
        temp_lists[ del ] = std::move( temp_lists.back() );
        temp_lists.pop_back();
    }
    // list handling done

    stack.freeAll();
}

value_t ExecutionPassBase::functionValue(
    Function* function, const std::vector< value_t >& arguments )
{
    if( function->checkArguments )
    {
        try
        {
            validateArguments( function->arguments_, arguments );
        }
        catch( const std::domain_error& e )
        {
            throw RuntimeException( function->location, e.what(),
                libcasm_fe::Code::FunctionArgumentsInvalidRangeAtLookup );
        }
    }

    const auto& function_map = function_states[ function->id ];

    const auto it = function_map.find( arguments );
    if( it != function_map.end() )
    {
        const auto& value = it.value();
        const auto update = updateSetManager.lookup( &value );

        if( update )
        {
            return update.value()->value;
        }
        else
        {
            return value;
        }
    }
    else
    {
        return defaultFunctionValue( function, arguments );
    }
}

value_t ExecutionPassBase::defaultFunctionValue(
    Function* function, const std::vector< value_t >& )
{
    return functionDefaultValues[ function->id ];
}

u1 ExecutionPassBase::filter_enabled( const std::string& filter )
{
    return debuginfo_filters.count( "all" ) > 0
           || debuginfo_filters.count( filter ) > 0;
}

void ExecutionPassBase::visit_body_elements_pre( AstListNode* )
{
    fork( ExecutionUpdateSet::Semantics::Sequential );
}

void ExecutionPassBase::visit_body_elements_post( AstListNode* )
{
    merge();
}

void ExecutionPassBase::visit_function_def_pre(
    FunctionDefNode* node, const value_t& defaultValue )
{
    const auto function = node->sym;

    try
    {
        validateValue( function->return_type_, defaultValue );
    }
    catch( const std::domain_error& e )
    {
        throw RuntimeException( node->defaultValue()->location,
            std::string( e.what() ) + " of `" + function->name + "`",
            libcasm_fe::Code::FunctionDefaultValueInvalidRange );
    }

    function_states[ function->id ]
        = FunctionState( function->argument_count() * 100 );
    function_symbols[ function->id ] = function;
    functionDefaultValues[ function->id ] = defaultValue;

    fork( ExecutionUpdateSet::Semantics::Parallel );
}

void ExecutionPassBase::visit_function_def_post( FunctionDefNode* )
{
    merge();
}

void ExecutionPassBase::visit_seqblock_pre( UnaryNode* )
{
    fork( ExecutionUpdateSet::Semantics::Sequential );
}

void ExecutionPassBase::visit_seqblock_post( UnaryNode* )
{
    merge();
}

void ExecutionPassBase::visit_parblock_pre( UnaryNode* )
{
    fork( ExecutionUpdateSet::Semantics::Parallel );
}

void ExecutionPassBase::visit_parblock_post( UnaryNode* )
{
    merge();
}

void ExecutionPassBase::visit_forall_pre( ForallNode* )
{
    fork( ExecutionUpdateSet::Semantics::Parallel );
}

void ExecutionPassBase::visit_forall_post( ForallNode* )
{
    merge();
}

void ExecutionPassBase::visit_forall_iteration_pre(
    ForallNode*, const value_t& value )
{
    rule_bindings.back()->push_back( value );
}

void ExecutionPassBase::visit_forall_iteration_post( ForallNode* )
{
    rule_bindings.back()->pop_back();
}

namespace libcasm_fe
{
    namespace builtins
    {
        static const value_t pow( const value_t& base, const value_t& power )
        {
            switch( base.type )
            {
                case TypeType::INTEGER:
                    return value_t( (INTEGER_T)std::pow(
                        base.value.integer, power.value.integer ) );
                case TypeType::FLOATING:
                    return value_t( (FLOATING_T)std::pow(
                        base.value.float_, power.value.float_ ) );
                default:
                    FAILURE();
            }
        }

        static const value_t dec( const value_t& arg )
        {
            // TODO LEAK!
            if( arg.is_undef() )
            {
                return value_t( new std::string( "undef" ) );
            }

            std::stringstream ss;
            if( arg.value.integer < 0 )
            {
                ss << "-" << std::dec << ( -1 ) * arg.value.integer;
            }
            else
            {
                ss << std::dec << arg.value.integer;
            }
            return value_t( new std::string( ss.str() ) );
        }

        static const value_t hex( const value_t& arg )
        {
            // TODO LEAK!
            if( arg.is_undef() )
            {
                return value_t( new std::string( "undef" ) );
            }

            std::stringstream ss;
            if( arg.value.integer < 0 )
            {
                ss << "-" << std::hex << ( -1 ) * arg.value.integer;
            }
            else
            {
                ss << std::hex << arg.value.integer;
            }
            return value_t( new std::string( ss.str() ) );
        }

        static const value_t bin( const value_t& arg )
        {
            // TODO LEAK!
            if( arg.is_undef() )
            {
                return value_t( new std::string( "undef" ) );
            }

            std::bitset< 256 > bits( (uint64_t)arg.value.integer );
            std::string str = bits.to_string();
            str.erase(
                0, std::min( str.find_first_not_of( '0' ), str.size() - 1 ) );

            return value_t( new std::string( str ) );
        }

        static const value_t nth(
            const value_t& list_arg, const value_t& index )
        {
            if( list_arg.is_undef() || index.is_undef() )
            {
                return value_t();
            }

            List* list = list_arg.value.list;
            List::const_iterator iter = list->begin();
            INTEGER_T i = 1;

            while( iter != list->end() && i < index.value.integer )
            {
                i++;
                iter++;
            }
            if( i == index.value.integer && iter != list->end() )
            {
                return value_t( *iter );
            }
            else
            {
                return value_t();
            }
        }

        static const value_t app( std::vector< List* >& tempLists,
            const value_t& list, const value_t& val )
        {
            // TODO LEAK
            if( list.is_undef() )
            {
                return value_t();
            }

            List* current = list.value.list;

            while( true )
            {
                if( current->list_type == List::ListType::HEAD )
                {
                    current = reinterpret_cast< HeadList* >( current )->right;
                }
                if( current->list_type == List::ListType::SKIP )
                {
                    current = reinterpret_cast< SkipList* >( current )->bottom;
                }
                if( current->list_type == List::ListType::BOTTOM )
                {
                    BottomList* bottom
                        = reinterpret_cast< BottomList* >( current );
                    if( bottom->tail )
                    {
                        current = bottom->tail;
                    }
                    else
                    {
                        break;
                    }
                }
                if( current->list_type == List::ListType::TAIL )
                {
                    TailList* tail = reinterpret_cast< TailList* >( current );
                    if( tail->right )
                    {
                        current = tail->right;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            TailList* tail = new TailList( nullptr, val );
            tempLists.push_back( tail );

            if( current->list_type == List::ListType::TAIL )
            {
                reinterpret_cast< TailList* >( current )->right = tail;
            }
            else if( current->list_type == List::ListType::BOTTOM )
            {
                reinterpret_cast< BottomList* >( current )->tail = tail;
            }
            else
            {
                FAILURE();
            }
            return value_t( list.type, list.value.list );
        }

        const value_t cons( std::vector< List* >& tempLists, const value_t& val,
            const value_t& list )
        {
            // TODO LEAK
            if( list.is_undef() )
            {
                return value_t();
            }

            HeadList* consed_list = new HeadList( list.value.list, val );
            tempLists.push_back( consed_list );
            return value_t( list.type, consed_list );
        }

        const value_t tail(
            std::vector< List* >& tempLists, const value_t& arg_list )
        {
            if( arg_list.is_undef() )
            {
                return value_t();
            }

            List* list = arg_list.value.list;

            if( list->is_head() )
            {
                return value_t( arg_list.type,
                    reinterpret_cast< HeadList* >( list )->right );
            }
            else if( list->is_bottom() )
            {
                BottomList* btm = reinterpret_cast< BottomList* >( list );
                SkipList* skip = new SkipList( 1, btm );
                tempLists.push_back( skip );
                return value_t( arg_list.type, skip );
            }
            else
            {
                SkipList* old_skip = reinterpret_cast< SkipList* >( list );
                SkipList* skip
                    = new SkipList( old_skip->skip + 1, old_skip->bottom );
                tempLists.push_back( skip );
                return value_t( arg_list.type, skip );
            }
        }

        static const value_t len( const value_t& list_arg )
        {
            // TODO len is really slow right now, it itertes over complete list
            if( list_arg.is_undef() )
            {
                return value_t();
            }

            List* list = list_arg.value.list;
            List::const_iterator iter = list->begin();

            size_t count = 0;

            while( iter != list->end() )
            {
                count++;
                iter++;
            }
            return value_t( (INTEGER_T)count );
        }

        const value_t peek( const value_t& arg_list )
        {
            if( arg_list.is_undef() )
            {
                return value_t();
            }

            List* list = arg_list.value.list;

            if( list->begin() != list->end() )
            {
                return value_t( *( list->begin() ) );
            }
            else
            {
                return value_t();
            }
        }

        static const value_t asboolean( const value_t& arg )
        {
            if( arg.is_undef() )
            {
                return std::move( arg );
            }

            return value_t( (u1)arg.value.integer );
        }

        static const value_t asenum( BuiltinAtom* atom, const value_t& arg )
        {
            Enum* enum_ = global_driver->function_table.get_enum(
                atom->type_.enum_name );
            for( auto pair : enum_->mapping )
            {
                // TODO check why the enum mapping contains an extra entry with
                // the
                // name
                // of the enum
                if( pair.first != enum_->name
                    && pair.second->id == arg.value.integer )
                {
                    return value_t( pair.second );
                }
            }
            return value_t();
        }

        static const value_t asstring( const value_t& arg )
        {
            switch( arg.type )
            {
                case TypeType::STRING:
                    return arg;
                case TypeType::BOOLEAN:
                    return value_t( arg.value.boolean
                                        ? new std::string( "true" )
                                        : new std::string( "false" ) );
                case TypeType::ENUM:
                    return value_t(
                        new std::string( *arg.value.enum_val->name ) );
                case TypeType::UNDEF:
                    return value_t( new std::string( "undef" ) );
                default:
                    FAILURE();
            }
        }

        static const value_t asinteger( const value_t& arg )
        {
            switch( arg.type )
            {
                case TypeType::BIT:
                case TypeType::INTEGER:
                    return value_t( arg.value.integer );
                case TypeType::BOOLEAN:
                    return value_t( (INTEGER_T)arg.value.boolean );
                case TypeType::FLOATING:
                    return value_t( (INTEGER_T)arg.value.float_ );
                case TypeType::RATIONAL:
                    return value_t(
                        ( INTEGER_T )( arg.value.rat->numerator
                                       / arg.value.rat->denominator ) );
                case TypeType::ENUM:
                    return value_t( (INTEGER_T)arg.value.enum_val->id );
                case TypeType::UNDEF:
                    return arg;
                default:
                    FAILURE();
            }
        }

        static const value_t asfloating( const value_t& arg )
        {
            switch( arg.type )
            {
                case TypeType::INTEGER:
                    return value_t( (FLOATING_T)arg.value.integer );
                case TypeType::FLOATING:
                    return value_t( arg.value.float_ );
                case TypeType::RATIONAL:
                    return value_t( ( (FLOATING_T)arg.value.rat->numerator )
                                    / arg.value.rat->denominator );
                case TypeType::UNDEF:
                    return arg;
                default:
                    FAILURE();
            }
        }

        static const value_t asbit( const value_t& arg, const value_t& bitsize )
        {
            // TODO PPA: redo after proper bit implementation and new built-ins
            // implementation from IR etc.
            value_t ret = asinteger( arg );
            if( ret.type == TypeType::UNDEF )
            {
                return ret;
            }
            else
            {
                return value_t( (uint64_t)ret.value.integer );
            }
        }

        static const value_t zext( const value_t& arg, const value_t& bitsize )
        {
            // TODO PPA: redo after proper bit implementation and new built-ins
            // implementation from IR etc.
            return value_t( (uint64_t)arg.value.integer );
        }

        static const value_t shl( const value_t& arg, const value_t& bitsize )
        {
            // TODO PPA: redo after proper bit implementation and new built-ins
            // implementation from IR etc.
            return value_t(
                ( (uint64_t)arg.value.integer ) << bitsize.value.integer );
        }

        static const value_t shr( const value_t& arg, const value_t& bitsize )
        {
            // TODO PPA: redo after proper bit implementation and new built-ins
            // implementation from IR etc.
            return value_t(
                ( (uint64_t)arg.value.integer ) >> bitsize.value.integer );
        }

        static const value_t trunc( const value_t& arg, const value_t& bitsize )
        {
            // TODO PPA: redo after proper bit implementation and new built-ins
            // implementation from IR etc.

            uint64_t mask = ( 1 << bitsize.value.integer ) - 1;

            return value_t( ( (uint64_t)arg.value.integer ) & mask );
        }

        static void get_numerator_denominator(
            double x, int64_t* num, int64_t* denom )
        {
            // thanks to
            // http://stackoverflow.com/a/96035/781502
            uint64_t m[ 2 ][ 2 ];
            double startx = x;
            uint64_t maxden = 10000000000;
            int64_t ai;

            /* initialize matrix */
            m[ 0 ][ 0 ] = m[ 1 ][ 1 ] = 1;
            m[ 0 ][ 1 ] = m[ 1 ][ 0 ] = 0;

            /* loop finding terms until denom gets too big */
            while( m[ 1 ][ 0 ] * ( ai = (int64_t)x ) + m[ 1 ][ 1 ] <= maxden )
            {
                long t;
                t = m[ 0 ][ 0 ] * ai + m[ 0 ][ 1 ];
                m[ 0 ][ 1 ] = m[ 0 ][ 0 ];
                m[ 0 ][ 0 ] = t;
                t = m[ 1 ][ 0 ] * ai + m[ 1 ][ 1 ];
                m[ 1 ][ 1 ] = m[ 1 ][ 0 ];
                m[ 1 ][ 0 ] = t;
                if( x == (double)ai )
                    break; // AF: division by zero
                x = 1 / ( x - (double)ai );
                if( x > (double)0x7FFFFFFF )
                    break; // AF: representation failure
            }

            /* now remaining x is between 0 and 1/ai */
            /* approx as either 0 or 1/m where m is max that will fit in maxden
             */
            /* first try zero */

            double error1
                = startx - ( (double)m[ 0 ][ 0 ] / (double)m[ 1 ][ 0 ] );

            *num = m[ 0 ][ 0 ];
            *denom = m[ 1 ][ 0 ];

            /* now try other possibility */
            ai = ( maxden - m[ 1 ][ 1 ] ) / m[ 1 ][ 0 ];
            m[ 0 ][ 0 ] = m[ 0 ][ 0 ] * ai + m[ 0 ][ 1 ];
            m[ 1 ][ 0 ] = m[ 1 ][ 0 ] * ai + m[ 1 ][ 1 ];
            double error2
                = startx - ( (double)m[ 0 ][ 0 ] / (double)m[ 1 ][ 0 ] );

            if( fabs( error1 ) > fabs( error2 ) )
            {
                *num = m[ 0 ][ 0 ];
                *denom = m[ 1 ][ 0 ];
            }
        }

        static const value_t asrational( const value_t& arg )
        {
            auto result = new rational_t;
            switch( arg.type )
            {
                case TypeType::INTEGER:
                    result->numerator = arg.value.integer;
                    result->denominator = 1;
                    return value_t( result );
                case TypeType::FLOATING:
                    get_numerator_denominator( arg.value.float_,
                        &result->numerator, &result->denominator );
                    return value_t( result );
                case TypeType::RATIONAL:
                    return value_t( arg.value.rat );
                case TypeType::UNDEF:
                    return arg;
                default:
                    FAILURE();
            }
        }

        static const value_t issymbolic( const value_t& arg )
        {
            return value_t( arg.is_symbolic() );
        }
    }
}

void ExecutionPassBase::visit_assert( UnaryNode* node, const value_t& value )
{
    if( not value.value.boolean )
    {
        throw RuntimeException( node->location, "assertion failed",
            libcasm_fe::Code::AssertInvalidExpression );
    }
}

void ExecutionPassBase::visit_assure( UnaryNode* node, const value_t& value )
{
    visit_assert( node, value );
}

void ExecutionPassBase::visit_update(
    UpdateNode* node, std::vector< value_t >& arguments, const value_t& value )
{
    const auto function = node->func->symbol;

    addUpdate( function, arguments, value, node->location );

    if( node->dump )
    {
        const auto& filter = global_driver->function_trace_map[ function->id ];
        if( filter_enabled( filter ) )
        {
            std::cout << filter << ": " << function->name
                      << to_string( arguments ) << " = " << value.to_str()
                      << std::endl;
        }
    }
}

void ExecutionPassBase::visit_call_pre( CallNode* )
{
}

void ExecutionPassBase::visit_call_pre( CallNode* call, const value_t& value )
{
    if( value.type != TypeType::UNDEF )
    {
        call->rule = value.value.rule;
    }
    else
    {
        throw RuntimeException( call->location, "Cannot call UNDEF" );
    }
}

void ExecutionPassBase::visit_call(
    CallNode* call, std::vector< value_t >& arguments )
{
    if( call->ruleref )
    {
        // only relevant for indirect calls
        const size_t args_defined = call->rule->arguments.size();
        const size_t args_provided = arguments.size();

        if( args_defined != args_provided )
        {
            throw RuntimeException( call->location,
                "indirectly called rule '" + call->rule->name + "' expects "
                    + std::to_string( args_defined )
                    + " arguments but "
                    + std::to_string( args_provided )
                    + " were provided",
                libcasm_fe::Code::RuleArgumentsSizeInvalidAtIndirectCall );
        }
        else
        {
            for( size_t i = 0; i < args_defined; i++ )
            {
                const auto arg = arguments.at( i );

                Type argType( arg.type );

                Type ruleArgType = call->rule->arguments.at( i );

                if( not( ruleArgType.unify( &argType ) or arg.is_undef() ) )
                {
                    throw RuntimeException( call->arguments->at( i )->location,
                        "argument " + std::to_string( i + 1 )
                            + " of indirectly called rule `"
                            + call->rule->name
                            + "` must be `"
                            + ruleArgType.to_str()
                            + "` but was `"
                            + argType.to_str()
                            + "`",
                        libcasm_fe::Code::
                            RuleArgumentsTypeInvalidAtIndirectCall );
                }
            }
        }
    }

    try
    {
        validateArguments( call->rule->arguments, arguments );
    }
    catch( const std::domain_error& e )
    {
        throw RuntimeException(
            call->location // TODO create a new exception type to pass on the
                           // argument index to get the proper arg location
            ,
            std::string( e.what() ) + " of rule '"
                + ( call->ruleref ? call->rule->name : call->rule_name )
                + "'",
            libcasm_fe::Code::RuleArgumentsInvalidRangeAtCall );
    }

    rule_bindings.push_back( &arguments );
}

void ExecutionPassBase::visit_call_post( CallNode* call )
{
    UNUSED( call );
    rule_bindings.pop_back();
}

void ExecutionPassBase::visit_diedie( DiedieNode* node, const value_t& msg )
{
    if( node->msg )
    {
        throw RuntimeException( node->location, *msg.value.string );
    }
    else
    {
        throw RuntimeException( node->location, "`diedie` executed" );
    }
}

void ExecutionPassBase::visit_impossible( AstNode* node )
{
    throw RuntimeException( node->location, "`impossible` executed" );
}

void ExecutionPassBase::visit_let( LetNode*, const value_t& value )
{
    rule_bindings.back()->push_back( value );
}

void ExecutionPassBase::visit_let_post( LetNode* )
{
    rule_bindings.back()->pop_back();
}

value_t ExecutionPassBase::visit_zero_atom( ZeroAtom* )
{
    return value_t();
}

value_t ExecutionPassBase::visit_undef_atom( UndefAtom* )
{
    return value_t();
}

value_t ExecutionPassBase::visit_self_atom( SelfAtom* )
{
    return value_t();
}

value_t ExecutionPassBase::visit_int_atom( IntegerAtom* atom )
{
    return value_t( atom->val_ );
}

value_t ExecutionPassBase::visit_bit_atom( IntegerAtom* atom )
{
    return value_t( atom->val_ );
}

value_t ExecutionPassBase::visit_floating_atom( FloatingAtom* atom )
{
    return value_t( atom->val_ );
}

value_t ExecutionPassBase::visit_rational_atom( RationalAtom* atom )
{
    return value_t( new rational_t( atom->val_ ) );
}

value_t ExecutionPassBase::visit_rule_atom( RuleAtom* atom )
{
    return value_t( atom->rule );
}

value_t ExecutionPassBase::visit_boolean_atom( BooleanAtom* atom )
{
    return value_t( atom->value );
}

value_t ExecutionPassBase::visit_string_atom( StringAtom* atom )
{
    return value_t( new std::string( atom->string ) );
}

value_t ExecutionPassBase::visit_function_atom(
    FunctionAtom* atom, std::vector< value_t >& arguments )
{
    switch( atom->symbol_type )
    {
        case FunctionAtom::SymbolType::PARAMETER:
            return value_t( rule_bindings.back()->at( atom->offset ) );
        case FunctionAtom::SymbolType::FUNCTION:
            try
            {
                return functionValue( atom->symbol, arguments );
            }
            catch( const RuntimeException& e )
            {
                throw RuntimeException(
                    atom->location, e.what(), e.getErrorCode() );
            }
        case FunctionAtom::SymbolType::ENUM:
        {
            enum_value_t* val = atom->enum_->mapping[ atom->name ];
            value_t v = value_t( val );
            v.type = TypeType::ENUM;
            return v;
        }
        default:
            FAILURE();
    }
}

value_t ExecutionPassBase::visit_builtin_atom(
    BuiltinAtom* atom, std::vector< value_t >& arguments )
{
    switch( atom->id )
    {
        case Builtin::Id::POW:
            return ::builtins::pow( arguments.at( 0 ), arguments.at( 1 ) );
        case Builtin::Id::NTH:
            return ::builtins::nth( arguments.at( 0 ), arguments.at( 1 ) );
        case Builtin::Id::APP:
            return ::builtins::app(
                temp_lists, arguments.at( 0 ), arguments.at( 1 ) );
        case Builtin::Id::CONS:
            return ::builtins::cons(
                temp_lists, arguments.at( 0 ), arguments.at( 1 ) );
        case Builtin::Id::DEC:
            return ::builtins::dec( arguments.at( 0 ) );
        case Builtin::Id::HEX:
            return ::builtins::hex( arguments.at( 0 ) );
        case Builtin::Id::BIN:
            return ::builtins::bin( arguments.at( 0 ) );

        case Builtin::Id::TAIL:
            return ::builtins::tail( temp_lists, arguments.at( 0 ) );
        case Builtin::Id::LEN:
            return ::builtins::len( arguments.at( 0 ) );
        case Builtin::Id::PEEK:
            return ::builtins::peek( arguments.at( 0 ) );
        case Builtin::Id::AS_BOOLEAN:
            return ::builtins::asboolean( arguments.at( 0 ) );
        case Builtin::Id::AS_ENUM:
            // TODO Int2Enum is a special builtin, it needs the complete type
            // information
            // for the enum, values only store TypeType and passing the type to
            // all
            // builtins seems ugly.
            // Maybe store Type* in value_t?
            return ::builtins::asenum( atom, arguments.at( 0 ) );
        case Builtin::Id::AS_STRING:
            return ::builtins::asstring( arguments.at( 0 ) );
        case Builtin::Id::AS_INTEGER:
            return ::builtins::asinteger( arguments.at( 0 ) );
        case Builtin::Id::AS_FLOATING:
            return ::builtins::asfloating( arguments.at( 0 ) );
        case Builtin::Id::AS_RATIONAL:
            return ::builtins::asrational( arguments.at( 0 ) );
        case Builtin::Id::AS_BIT:
            return ::builtins::asbit( arguments.at( 0 ), arguments.at( 1 ) );
        case Builtin::Id::IS_SYMBOLIC:
            return ::builtins::issymbolic( arguments.at( 0 ) );

        case Builtin::Id::ZEXT:
            return ::builtins::zext( arguments.at( 0 ), arguments.at( 1 ) );
        case Builtin::Id::SHL:
            return ::builtins::shl( arguments.at( 0 ), arguments.at( 1 ) );
        case Builtin::Id::SHR:
            return ::builtins::shr( arguments.at( 0 ), arguments.at( 1 ) );
        case Builtin::Id::TRUNC:
            return ::builtins::trunc( arguments.at( 0 ), arguments.at( 1 ) );

        default:
            global_driver->error( atom->location,
                "unimplemented builtin `" + atom->to_str() + "`" );
            return value_t();
    }
}

void ExecutionPassBase::visit_derived_function_atom_pre(
    FunctionAtom* function, std::vector< value_t >& arguments )
{
    if( function->symbol->checkArguments )
    {
        try
        {
            validateArguments( function->symbol->arguments_, arguments );
        }
        catch( const std::domain_error& e )
        {
            throw RuntimeException(
                function->location // TODO create a new exception type to pass
                                   // on the argument index to get the proper
                                   // arg location
                ,
                std::string( e.what() ) + " of derived '"
                    + function->symbol->name
                    + "'",
                libcasm_fe::Code::DerivedArgumentsInvalidRangeAtLookup );
        }
    }

    rule_bindings.push_back( &arguments );
}

value_t ExecutionPassBase::visit_derived_function_atom(
    FunctionAtom* function, const value_t& value )
{
    rule_bindings.pop_back();

    if( function->symbol->checkReturnValue )
    {
        try
        {
            validateValue( function->symbol->return_type_, value );
        }
        catch( const std::domain_error& e )
        {
            throw RuntimeException( function->location,
                std::string( e.what() ) + " of the return value of derived `"
                    + function->symbol->name
                    + "`",
                libcasm_fe::Code::DerivedReturnValueInvalidRange );
        }
    }

    return value;
}

value_t ExecutionPassBase::visit_number_range_atom(
    NumberRangeAtom* atom, const value_t& left, const value_t& right )
{
    if( left.value.integer > right.value.integer )
    {
        return value_t(
            new NumberRange( right.value.integer, left.value.integer ) );
    }
    else
    {
        return value_t(
            new NumberRange( left.value.integer, right.value.integer ) );
    }
}

void libcasm_fe::ExecutionPassBase::validateArguments(
    const std::vector< Type* >& argumentTypes,
    const std::vector< value_t >& argumentValues ) const
{
    assert( argumentTypes.size() == argumentValues.size() );

    for( size_t i = 0; i < argumentValues.size(); i++ )
    {
        const auto& argumentValue = argumentValues.at( i );
        const Type* argumentType = argumentTypes.at( i );

        try
        {
            validateValue( argumentType, argumentValue );
        }
        catch( const std::domain_error& e )
        {
            throw std::domain_error( std::string( e.what() ) + " at argument #"
                                     + std::to_string( i + 1 ) );
        }
    }
}

void libcasm_fe::ExecutionPassBase::validateValue(
    const Type* type, const value_t& value ) const
{
    assert( type != nullptr );

    if( value.is_undef() )
    {
        return;
    }

    switch( type->t )
    {
        case TypeType::INTEGER:
        {
            const INTEGER_T integer = value.value.integer;

            if( type->has_range_restriction()
                and ( integer < type->subrange_start
                        or integer > type->subrange_end ) )
            {
                throw std::domain_error(
                    std::to_string( integer ) + " does violate the subrange "
                    + std::to_string( type->subrange_start )
                    + ".."
                    + std::to_string( type->subrange_end ) );
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
