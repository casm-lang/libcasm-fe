//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#include "SymbolicExecutionPass.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sys/wait.h>
#include <type_traits>
#include <unistd.h>
#include <utility>

#include "../Driver.h"
#include "../Exceptions.h"
#include "../Symbolic.h"
#include "../Symbols.h"

using namespace libcasm_fe;

extern Driver* global_driver;

char SymbolicExecutionPass::id = 0;

static libpass::PassRegistration< SymbolicExecutionPass > PASS(
    "Symbolic Execution Pass",
    "execute symbolically over the AST input specification", "ast-exec-sym",
    0 );

SymbolicExecutionPass::~SymbolicExecutionPass()
{
    delete walker;
}

bool SymbolicExecutionPass::run( libpass::PassResult& pr )
{
    walker = new SymbolicExecutionWalker( *this );

    Ast* root = (Ast*)pr.getResult< TypeCheckPass >();
    RuleNode* node
        = global_driver->rules_map_[ root->getInitRule()->identifier ];

    rule_bindings.push_back( &main_bindings );
    function_states
        = std::vector< FunctionState >( global_driver->function_table.size() );
    function_symbols = std::vector< const Function* >(
        global_driver->function_table.size() );
    Function* program_sym
        = global_driver->function_table.get_function( "program" );
    // TODO location is wrong here
    program_sym->intitializers_
        = new std::vector< std::pair< ExpressionBase*, ExpressionBase* > >();
    RuleAtom* init_atom
        = new RuleAtom( node->location, std::string( node->name ) );
    init_atom->rule = node;
    program_sym->intitializers_->push_back(
        std::make_pair( new SelfAtom( node->location ), init_atom ) );

    try
    {
        for( auto pair : global_driver->init_dependencies )
        {
            std::set< std::string > visited;
            if( initialized.count( pair.first ) > 0 )
            {
                continue;
                ;
            }
            if( !init_function( pair.first, visited ) )
            {
                Function* func
                    = global_driver->function_table.get_function( pair.first );
                std::string cycle = pair.first;
                for( const std::string& dep : visited )
                {
                    cycle = cycle + " => " + dep;
                }
                throw RuntimeException(
                    func->intitializers_->at( 0 ).second->location,
                    "initializer dependency cycle detected: " + cycle );
            }
        }

        for( auto pair : global_driver->function_table.table_ )
        {
            if( pair.second->type != Symbol::SymbolType::FUNCTION
                || initialized.count( pair.first ) > 0 )
            {
                continue;
            }

            std::set< std::string > visited;
            init_function( pair.first, visited );
        }

        for( List* l : temp_lists )
        {
            l->bump_usage();
        }
        temp_lists.clear();

        mainLoop();
        printTrace();
    }
    catch( const RuntimeException& ex )
    {
        global_driver->error( ex.getLocations(), ex.what(), ex.getErrorCode() );
        return false;
    }
    catch( char* e )
    {
        std::cerr << "Abort after catching a string: " << e << std::endl;
        return false;
    }

    return true;
}

namespace symbolic
{
    enum class check_status_t
    {
        NOT_FOUND,
        TRUE,
        FALSE
    };

    static uint32_t last_symbol_id
        = 1; // symbol id of 0 means 'non existing symbol'
    static uint32_t current_time = 2; // FIXME EP: why?

    const static uint32_t FINAL_TIME = 0;

    static uint32_t next_symbol_id()
    {
        return last_symbol_id++;
    }

    static void advance_timestamp()
    {
        ++current_time;
    }

    static uint32_t get_timestamp()
    {
        return current_time;
    }
}

#define WRAP_NUMERICAL_OPERATION( op, lhs, rhs )                               \
    if( ( lhs.is_symbolic() and rhs.is_symbolic() )                            \
        or ( lhs.is_symbolic() and not rhs.is_undef() )                        \
        or ( rhs.is_symbolic() and not lhs.is_undef() ) )                      \
    {                                                                          \
        return value_t( new symbol_t( symbolic::next_symbol_id() ) );          \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        return op( lhs, rhs );                                                 \
    }

namespace operators
{
    static const value_t lesser( const value_t& lhs, const value_t& rhs )
    {
        if( lhs.is_symbolic() and rhs.is_symbolic() and lhs == rhs )
        {
            return value_t( false );
        }
        WRAP_NUMERICAL_OPERATION( operator<, lhs, rhs)
    }

    static const value_t greater( const value_t& lhs, const value_t& rhs )
    {
        if( lhs.is_symbolic() and rhs.is_symbolic() and lhs == rhs )
        {
            return value_t( false );
        }
        WRAP_NUMERICAL_OPERATION( operator>, lhs, rhs)
    }

    static const value_t lessereq( const value_t& lhs, const value_t& rhs )
    {
        if( lhs.is_symbolic() and rhs.is_symbolic() and ( lhs == rhs ) )
        {
            return value_t( true );
        }
        else if( lhs.is_symbolic() or rhs.is_symbolic() )
        {
            return value_t( new symbol_t( symbolic::next_symbol_id() ) );
        }
        else
        {
            return lhs <= rhs;
        }
    }

    static const value_t greatereq( const value_t& lhs, const value_t& rhs )
    {
        if( lhs.is_symbolic() and rhs.is_symbolic() and ( lhs == rhs ) )
        {
            return value_t( true );
        }
        else if( lhs.is_symbolic() or rhs.is_symbolic() )
        {
            return value_t( new symbol_t( symbolic::next_symbol_id() ) );
        }
        else
        {
            return lhs >= rhs;
        }
    }
}

namespace symbolic
{
    static std::string symbol_to_string( const uint32_t sym_id )
    {
        return "sym" + std::to_string( sym_id );
    }

    static void fof( std::stringstream& ss, const std::string& name,
        const Function* func, const std::vector< value_t >& arguments,
        const value_t& val, uint32_t time, const std::string& type )
    {
        ss << "fof(" << name << ",hypothesis,"
           << ( func->is_static ? "cs" : "st" ) << func->name << "(" << time
           << ",";
        if( not arguments.empty() )
        {
            ss << to_string( arguments ) << ",";
        }
        ss << val.to_str( true ) << "))." << type << ": " << func->name
           << to_string( arguments ) << std::endl;
    }

    static void dump_type( std::stringstream& ss, const value_t& v )
    {
        if( v.is_symbolic() and not v.value.sym->type_dumped )
        {
            ss << "tff(symbolNext, type, " << v.to_str() << ": $int)."
               << std::endl;
            v.value.sym->type_dumped = true;
        }
    }

    static void dump_catchup( std::vector< std::string >& trace,
        const Function* func, const std::vector< value_t >& arguments,
        const value_t& v )
    {
        for( uint32_t i = 1; i < symbolic::get_timestamp() - 1; i++ )
        {
            std::stringstream ss;
            fof( ss, "id%u", func, arguments, v, i, "%%CATCHUP" );
            trace.push_back( ss.str() );
        }
    }

    static void dump_create( std::vector< std::string >& trace,
        const Function* func, const std::vector< value_t >& arguments,
        const value_t& v )
    {
        std::stringstream ss;
        dump_type( ss, v );
        fof( ss, "id%u", func, arguments, v, symbolic::get_timestamp() - 1,
            "%%CREATE" );
        trace.push_back( ss.str() );

        if( symbolic::get_timestamp() > 2 )
        {
            dump_catchup( trace, func, arguments, v );
        }
    }

    static void dump_symbolic( std::vector< std::string >& trace,
        const Function* func, const std::vector< value_t >& arguments,
        const value_t& v )
    {
        std::stringstream ss;
        fof( ss, "id%u", func, arguments, v, symbolic::get_timestamp(),
            "%%SYMBOLIC" );
        trace.push_back( ss.str() );
    }

    static void dump_update( std::vector< std::string >& trace,
        const Function* func, const Update* update )
    {
        std::stringstream ss;
        dump_type( ss, update->value );
        fof( ss, "id%u", func, *update->args, update->value,
            symbolic::get_timestamp(), "%%UPDATE" );
        trace.push_back( ss.str() );
    }

    static void dump_pathcond_match( std::vector< std::string >& trace,
        const std::string& filename, size_t lineno,
        const symbolic_condition_t* cond, bool status )
    {
        std::stringstream ss;
        ss << "% " << filename << ":" << lineno << " PC-LOOKUP ("
           << cond->to_str() << ") = " << status << std::endl;
        trace.push_back( ss.str() );
    }

    static void dump_if( std::vector< std::string >& trace,
        const std::string& filename, size_t lineno,
        const symbolic_condition_t* cond )
    {
        std::stringstream ss;
        ss << "fof('id" << filename << ":" << lineno << "',hypothesis,"
           << cond->to_str() << ")." << std::endl;
        trace.push_back( ss.str() );
    }

    static void dump_final( std::vector< std::string >& trace,
        const std::vector< const Function* >& symbols,
        const std::vector< FunctionState >& states )
    {
        assert( symbols.size() == states.size() );

        std::stringstream ss;
        uint32_t finalId = 0;
        for( uint32_t i = 0; i < symbols.size(); i++ )
        {
            if( not symbols[ i ]->is_symbolic )
            {
                continue;
            }
            const auto end = states[ i ].end();
            for( auto it = states[ i ].begin(); it != end; ++it )
            {
                const auto& arguments = it.key();
                const auto& value = it.value();

                fof( ss, "final" + std::to_string( finalId ), symbols[ i ],
                    arguments, value, FINAL_TIME, "%FINAL" );

                ++finalId;
            }
        }
        trace.push_back( ss.str() );
    }

    constexpr inline uint16_t operator,( const libcasm_ir::Value::ID lhs,
        const libcasm_ir::Value::ID rhs ) noexcept
    {
        static_assert( sizeof( libcasm_ir::Value::ID ) == 1,
            "uint8_t | (uint8_t << 8) == uint16_t" );
        return ( static_cast< uint16_t >( lhs ) << 8 )
               | static_cast< uint16_t >( rhs );
    }

    static check_status_t check_inclusion(
        const symbolic_condition_t& known, const symbolic_condition_t& check )
    {
        using Opcode = libcasm_ir::Value::ID;

        switch( check.op, known.op )
        {
            case( Opcode::EQU_INSTRUCTION, Opcode::EQU_INSTRUCTION ):
                return ( *known.rhs == *check.rhs ) ? check_status_t::TRUE
                                                    : check_status_t::FALSE;
            case( Opcode::EQU_INSTRUCTION, Opcode::NEQ_INSTRUCTION ):
                return ( *known.rhs == *check.rhs ) ? check_status_t::FALSE
                                                    : check_status_t::NOT_FOUND;
            case( Opcode::NEQ_INSTRUCTION, Opcode::NEQ_INSTRUCTION ):
                return ( *known.rhs == *check.rhs ) ? check_status_t::TRUE
                                                    : check_status_t::NOT_FOUND;
            case( Opcode::NEQ_INSTRUCTION, Opcode::EQU_INSTRUCTION ):
                return ( *known.rhs == *check.rhs ) ? check_status_t::FALSE
                                                    : check_status_t::TRUE;
            case( Opcode::LEQ_INSTRUCTION, Opcode::EQU_INSTRUCTION ):
            {
                const value_t res
                    = operators::lessereq( *known.rhs, *check.rhs );
                return res.value.boolean ? check_status_t::TRUE
                                         : check_status_t::FALSE;
            }
            case( Opcode::LEQ_INSTRUCTION, Opcode::LEQ_INSTRUCTION ):
            {
                const value_t res
                    = operators::lessereq( *check.rhs, *known.rhs );
                return res.value.boolean ? check_status_t::TRUE
                                         : check_status_t::NOT_FOUND;
            }
            case( Opcode::LEQ_INSTRUCTION, Opcode::GTH_INSTRUCTION ):
            {
                const value_t res
                    = operators::lessereq( *check.rhs, *known.rhs );
                return res.value.boolean ? check_status_t::FALSE
                                         : check_status_t::NOT_FOUND;
            }
            case( Opcode::GTH_INSTRUCTION, Opcode::EQU_INSTRUCTION ):
            {
                const value_t res
                    = operators::greater( *known.rhs, *check.rhs );
                return res.value.boolean ? check_status_t::TRUE
                                         : check_status_t::FALSE;
            }
            case( Opcode::GTH_INSTRUCTION, Opcode::LEQ_INSTRUCTION ):
            {
                const value_t res
                    = operators::greater( *check.rhs, *known.rhs );
                return res.value.boolean ? check_status_t::FALSE
                                         : check_status_t::NOT_FOUND;
            }
            case( Opcode::GTH_INSTRUCTION, Opcode::GTH_INSTRUCTION ):
            {
                const value_t res
                    = operators::greater( *check.rhs, *known.rhs );
                return res.value.boolean ? check_status_t::TRUE
                                         : check_status_t::NOT_FOUND;
            }
            default:
                return check_status_t::NOT_FOUND;
        }
    }

    static check_status_t check_condition(
        const std::vector< symbolic_condition_t* >& known_conditions,
        const symbolic_condition_t* check )
    {
        symbolic_condition_t cond( check->lhs, check->rhs, check->op );

        if( check->lhs->type != TypeType::SYMBOL )
        {
            if( check->rhs->type == TypeType::SYMBOL )
            {
                cond
                    = symbolic_condition_t( check->rhs, check->lhs, check->op );
            }
            else
            {
                throw RuntimeException( "Invalid condition passed" );
            }
        }

        for( auto known_cond : known_conditions )
        {
            check_status_t s = check_status_t::NOT_FOUND;
            if( *( known_cond->lhs ) == *( cond.lhs ) )
            {
                s = check_inclusion( *known_cond, cond );
            }
            else if( *( known_cond->rhs ) == *( cond.lhs ) )
            {
                s = check_inclusion( symbolic_condition_t( known_cond->rhs,
                                         known_cond->lhs, known_cond->op ),
                    cond );
            }
            if( s != check_status_t::NOT_FOUND )
            {
                return s;
            }
        }

        return check_status_t::NOT_FOUND;
    }

    static uint32_t dump_listconst( std::vector< std::string >& trace, List* l )
    {
        uint32_t sym_id = 0;

        const auto end = l->end();
        for( auto it = l->begin(); it != end; ++it )
        {
            const uint32_t prev_sym_id = sym_id;
            sym_id = symbolic::next_symbol_id();

            std::stringstream ss;
            ss << "tff(symbolNext,type," << symbol_to_string( sym_id )
               << ": $int)." << std::endl
               << "fof(id%u,hypothesis,fcons("
               << ( ( prev_sym_id > 0 ) ? symbol_to_string( sym_id )
                                        : "eEmptyList" )
               << "," << ( *it ).to_str( true ) << ","
               << symbol_to_string( sym_id ) << "))." << std::endl;
            trace.push_back( ss.str() );
        }

        return sym_id;
    }

    static void dump_builtin( std::vector< std::string >& trace,
        const std::string& name, const std::vector< value_t >& arguments,
        const value_t& ret )
    {
        std::stringstream ss;

        for( const auto& arg : arguments )
        {
            dump_type( ss, arg );
        }
        dump_type( ss, ret );

        ss << "fof(id%u,hypothesis,f" << name << '(' << to_string( arguments )
           << "))." << std::endl;

        trace.push_back( ss.str() );
    }
}

void SymbolicExecutionPass::visit_assure(
    UnaryNode* assure, const value_t& val )
{
    if( val.is_symbolic() && val.value.sym->condition )
    {
        path_conditions.push_back( val.value.sym->condition );
    }
    else
    {
        visit_assert( assure, val );
    }
}

void SymbolicExecutionPass::visit_print(
    PrintNode* node, const value_t& argument )
{
    std::stringstream ss;
    if( node->getFilter().size() > 0 )
    {
        if( filter_enabled( node->getFilter() ) )
        {
            ss << node->getFilter() << ": ";
        }
        else
        {
            return;
        }
    }

    ss << argument.to_str() << std::endl;

    trace.push_back( ss.str() );
}

void SymbolicExecutionPass::visit_push(
    PushNode* node, const value_t& expr, const value_t& atom )
{
    std::vector< value_t > arguments{}; // TODO at the moment, functions with
                                        // arguments are not supported

    const value_t to_res( new symbol_t( symbolic::next_symbol_id() ) );
    if( atom.value.sym->list )
    {
        to_res.value.sym->list = builtins::cons(
            temp_lists, expr, value_t( TypeType::LIST, atom.value.sym->list ) )
                                     .value.list;
    }
    else
    {
        to_res.value.sym->list = builtins::cons( temp_lists, expr,
            value_t( TypeType::LIST,
                new BottomList() ) ).value.list;
    }

    addUpdate( node->to->symbol, arguments, to_res, node->location );

    symbolic::dump_builtin( trace, "push", { atom, expr }, to_res );
}

void SymbolicExecutionPass::visit_pop( PopNode* node, const value_t& val )
{
    std::vector< value_t > arguments{}; // TODO at the moment, functions with
                                        // arguments are not supported

    const value_t to_res
        = ( val.value.sym->list )
              ? builtins::peek( value_t( TypeType::LIST, val.value.sym->list ) )
              : value_t( new symbol_t( symbolic::next_symbol_id() ) );

    Update* up = nullptr;
    if( node->to->symbol_type == FunctionAtom::SymbolType::FUNCTION )
    {
        up = addUpdate( node->to->symbol, arguments, to_res, node->location );
    }
    else
    {
        rule_bindings.back()->push_back( to_res );
    }

    const value_t from_res( new symbol_t( symbolic::next_symbol_id() ) );
    if( val.value.sym->list )
    {
        from_res.value.sym->list = builtins::tail( temp_lists,
            value_t( TypeType::LIST,
                val.value.sym->list ) ).value.list;
    }

    symbolic::dump_builtin( trace, "pop", { val, to_res }, from_res );

    addUpdate( node->from->symbol, arguments, from_res, node->location );
}

value_t SymbolicExecutionPass::visit_expression(
    BinaryExpression* expr, const value_t& left_val, const value_t& right_val )
{
    using Opcode = libcasm_ir::Value::ID;

    switch( expr->op )
    {
        case Opcode::ADD_INSTRUCTION:
            WRAP_NUMERICAL_OPERATION( operator+, left_val, right_val)
        case Opcode::SUB_INSTRUCTION:
            WRAP_NUMERICAL_OPERATION( operator-, left_val, right_val)
        case Opcode::MUL_INSTRUCTION:
            WRAP_NUMERICAL_OPERATION( operator*, left_val, right_val)
        case Opcode::DIV_INSTRUCTION:
            WRAP_NUMERICAL_OPERATION( operator/, left_val, right_val);
        case Opcode::MOD_INSTRUCTION:
            WRAP_NUMERICAL_OPERATION( operator%, left_val, right_val);
        case Opcode::EQU_INSTRUCTION:
            if( left_val.is_symbolic() and right_val.is_symbolic()
                and ( left_val == right_val ) )
            {
                return value_t( true );
            }
            else if( left_val.is_symbolic() or right_val.is_symbolic() )
            {
                return value_t( new symbol_t( symbolic::next_symbol_id() ) );
            }
            else
            {
                return value_t( left_val == right_val );
            }
        case Opcode::NEQ_INSTRUCTION:
            if( left_val.is_symbolic() and right_val.is_symbolic()
                and ( left_val == right_val ) )
            {
                return value_t( false );
            }
            else if( left_val.is_symbolic() or right_val.is_symbolic() )
            {
                return value_t( new symbol_t( symbolic::next_symbol_id() ) );
            }
            else
            {
                return value_t( left_val != right_val );
            }
        case Opcode::AND_INSTRUCTION:
            if( left_val.is_symbolic() )
            {
                if( right_val.is_undef() or right_val.is_symbolic()
                    or right_val.value.boolean )
                {
                    return value_t(
                        new symbol_t( symbolic::next_symbol_id() ) );
                }
                else
                {
                    return value_t( false );
                }
            }
            else if( right_val.is_symbolic() )
            {
                if( left_val.is_undef() or left_val.is_symbolic()
                    or left_val.value.boolean )
                {
                    return value_t(
                        new symbol_t( symbolic::next_symbol_id() ) );
                }
                else
                {
                    return value_t( false );
                }
            }
            else
            {
                return left_val and right_val;
            }
        case Opcode::OR_INSTRUCTION:
            if( left_val.is_symbolic() )
            {
                if( right_val.is_undef() or right_val.is_symbolic()
                    or !right_val.value.boolean )
                {
                    return value_t(
                        new symbol_t( symbolic::next_symbol_id() ) );
                }
                else
                {
                    return value_t( true );
                }
            }
            else if( right_val.is_symbolic() )
            {
                if( left_val.is_undef() or left_val.is_symbolic()
                    or !left_val.value.boolean )
                {
                    return value_t(
                        new symbol_t( symbolic::next_symbol_id() ) );
                }
                else
                {
                    return value_t( true );
                }
            }
            else
            {
                return left_val or right_val;
            }
        case Opcode::XOR_INSTRUCTION:
            if( left_val.is_symbolic() or right_val.is_symbolic() )
            {
                return value_t( new symbol_t( symbolic::next_symbol_id() ) );
            }
            else
            {
                return left_val ^ right_val;
            }
        case Opcode::LTH_INSTRUCTION:
            return operators::lesser( left_val, right_val );
        case Opcode::GTH_INSTRUCTION:
            return operators::greater( left_val, right_val );
        case Opcode::LEQ_INSTRUCTION:
            return operators::lessereq( left_val, right_val );
        case Opcode::GEQ_INSTRUCTION:
            return operators::greatereq( left_val, right_val );
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
            return value_t();
    }
}

value_t SymbolicExecutionPass::visit_expression_single(
    UnaryExpression* expr, const value_t& val )
{
    using Opcode = libcasm_ir::Value::ID;

    if( val.is_undef() )
    {
        return value_t();
    }
    else if( val.is_symbolic() )
    {
        return value_t( new symbol_t( symbolic::next_symbol_id() ) );
    }

    switch( expr->op )
    {
        case Opcode::NOT_INSTRUCTION:
            return value_t( not val.value.boolean );
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
            return value_t();
    }
}

value_t SymbolicExecutionPass::visit_list_atom(
    ListAtom* atom, const std::vector< value_t >& vals )
{
    BottomList* list = new BottomList( vals );
    // context_.temp_lists.push_back(list);

    const uint32_t sym_id = symbolic::dump_listconst( trace_creates, list );
    if( sym_id > 0 )
    {
        // TODO cleanup symbols
        symbol_t* sym = new symbol_t( sym_id );
        sym->type_dumped = true;
        sym->list = list;
        return value_t( sym );
    }
    else
    {
        return value_t( atom->type_, list );
    }
}

value_t SymbolicExecutionPass::defaultFunctionValue(
    Function* function, const std::vector< value_t >& arguments )
{
    if( function->is_symbolic )
    {
        const value_t value(
            new symbol_t( symbolic::next_symbol_id() ) ); // TODO cleanup symbol

        auto& function_map = function_states[ function->id ];
        function_map.insert( arguments, value );
        symbolic::dump_create( trace_creates, function, arguments, value );

        return value;
    }
    else
    {
        return ExecutionPassBase::defaultFunctionValue( function, arguments );
    }
}

bool SymbolicExecutionPass::init_function(
    const std::string& name, std::set< std::string >& visited )
{
    if( global_driver->init_dependencies.count( name ) != 0 )
    {
        visited.insert( name );
        const std::set< std::string >& deps
            = global_driver->init_dependencies[ name ];
        for( const std::string& dep : deps )
        {
            if( visited.count( dep ) > 0 )
            {
                return false;
            }
            else
            {
                if( !init_function( dep, visited ) )
                {
                    return false;
                }
            }
        }
    }

    Function* func = global_driver->function_table.get_function( name );
    if( !func )
    {
        return true;
    }

    function_states[ func->id ] = FunctionState( 0 );
    function_symbols[ func->id ] = func;

    auto& function_map = function_states[ func->id ];

    if( func->intitializers_ != nullptr )
    {
        for( std::pair< ExpressionBase*, ExpressionBase* > init :
            *func->intitializers_ )
        {
            std::vector< value_t > arguments{};
            arguments.reserve( func->arguments_.size() );

            if( init.first != nullptr )
            {
                const value_t argument_v = walker->walk_atom( init.first );
                if( func->arguments_.size() > 1 )
                {
                    List* list = argument_v.value.list;
                    for( auto iter = list->begin(); iter != list->end();
                         iter++ )
                    {
                        arguments.emplace_back( *iter );
                    }
                }
                else
                {
                    arguments.emplace_back( argument_v );
                }
            }

            if( func->checkArguments )
            {
                try
                {
                    validateArguments( func->arguments_, arguments );
                }
                catch( const std::domain_error& e )
                {
                    const auto location
                        = init.first
                              ? ( init.first->location + init.second->location )
                              : init.second->location;
                    throw RuntimeException( location, e.what() );
                }
            }

            if( function_map.hasKey( arguments ) )
            {
                yy::location loc
                    = init.first ? init.first->location + init.second->location
                                 : init.second->location;
                throw RuntimeException( loc, "function `" + func->name
                                                 + to_string( arguments )
                                                 + "` already initialized" );
            }

            const value_t v = walker->walk_atom( init.second );
            if( func->checkReturnValue )
            {
                try
                {
                    validateValue( func->return_type_, v );
                }
                catch( const std::domain_error& e )
                {
                    const auto location
                        = init.first
                              ? ( init.first->location + init.second->location )
                              : init.second->location;
                    throw RuntimeException( location,
                        std::string( e.what() ) + " of `" + func->name + "`" );
                }
            }

            if( func->is_symbolic )
            {
                symbolic::dump_create( trace_creates, func, arguments, v );
            }

            function_map.insert( arguments, v );
        }
    }

    initialized.insert( name );
    return true;
}

void SymbolicExecutionPass::mainLoop()
{
    Function* program_sym
        = global_driver->function_table.get_function( "program" );
    const auto& function_map = function_states[ program_sym->id ];
    const value_t& program_val = function_map.get( { value_t() } );

    while( program_val.type != TypeType::UNDEF )
    {
        walker->walk_rule( program_val.value.rule );
        if( hasEmptyUpdateSet() )
        {
            break;
        }
        dumpUpdates();
        applyUpdates();
        symbolic::advance_timestamp();
    }

    symbolic::dump_final( trace, function_symbols, function_states );
}

void SymbolicExecutionPass::printTrace() const
{
    FILE* out;
    /*if (fileout) { TODO EP
        const std::string& filename = global_driver->get_filename().substr(
            0, global_driver->get_filename().rfind("."));

        out = fopen((filename + "_"  + path_name + ".trace").c_str(), "wt");
    } else {*/
    out = stdout;
    //}
    fprintf( out, "forklog:%s\n", path_name.c_str() );
    uint32_t fof_id = 0;
    for( const std::string& s : trace_creates )
    {
        if( s.find( "id%u" ) != std::string::npos )
        {
            fprintf( out, s.c_str(), fof_id );
            fof_id += 1;
        }
        else
        {
            fprintf( out, "%s", s.c_str() );
        }
    }
    for( const std::string& s : trace )
    {
        if( s.find( "id%u" ) != std::string::npos )
        {
            fprintf( out, s.c_str(), fof_id );
            fof_id += 1;
        }
        else
        {
            fprintf( out, "%s", s.c_str() );
        }
    }
    fprintf( out, "\n" );
}

void SymbolicExecutionPass::dumpUpdates()
{
    assert( updateSetManager.size() == 1 );

    const auto updateSet = updateSetManager.currentUpdateSet();

    for( uint32_t i = 0; i < function_symbols.size(); i++ )
    {
        const Function* function = function_symbols[ i ];
        if( not function->is_symbolic or function->is_static )
        {
            continue;
        }

        const auto end = function_states[ i ].end();
        for( auto it = function_states[ i ].begin(); it != end; ++it )
        {
            const auto& arguments = it.key();
            const auto& value = it.value();

            const auto update = updateSet->get( &value );
            if( update )
            {
                symbolic::dump_update( trace, function, update );
            }
            else
            {
                symbolic::dump_symbolic( trace, function, arguments, value );
            }
        }
    }
}

static libcasm_ir::Value::ID invert( libcasm_ir::Value::ID op )
{
    using Opcode = libcasm_ir::Value::ID;

    switch( op )
    {
        case Opcode::EQU_INSTRUCTION:
            return Opcode::NEQ_INSTRUCTION;
        case Opcode::NEQ_INSTRUCTION:
            return Opcode::EQU_INSTRUCTION;
        case Opcode::LEQ_INSTRUCTION:
            return Opcode::GTH_INSTRUCTION;
        case Opcode::LTH_INSTRUCTION:
            return Opcode::GEQ_INSTRUCTION;
        case Opcode::GTH_INSTRUCTION:
            return Opcode::LEQ_INSTRUCTION;
        case Opcode::GEQ_INSTRUCTION:
            return Opcode::LTH_INSTRUCTION;
        default:
            throw RuntimeException( "Invert not implemented for operation" );
    }
}

template <>
void SymbolicExecutionWalker::walk_ifthenelse( IfThenElseNode* node )
{
    const value_t cond = walk_atom( node->condition_ );

    if( cond.is_symbolic() )
    {
        symbolic_condition_t* sym_cond;
        if( cond.value.sym->condition )
        {
            sym_cond = cond.value.sym->condition;
        }
        else
        {
            sym_cond = new symbolic_condition_t( new value_t( cond ),
                new value_t( (INTEGER_T)1 ),
                libcasm_ir::Value::EQU_INSTRUCTION );
        }

        switch( symbolic::check_condition( visitor.path_conditions, sym_cond ) )
        {
            case symbolic::check_status_t::NOT_FOUND:
                break;
            case symbolic::check_status_t::TRUE:
                symbolic::dump_pathcond_match( visitor.trace,
                    global_driver->get_filename(),
                    node->condition_->location.begin.line, sym_cond, true );
                walk_statement( node->then_ );
                return;
            case symbolic::check_status_t::FALSE:
                symbolic::dump_pathcond_match( visitor.trace,
                    global_driver->get_filename(),
                    node->condition_->location.begin.line, sym_cond, false );

                if( node->else_ )
                {
                    walk_statement( node->else_ );
                }
                return;
        }

        pid_t pid = fork();
        switch( pid )
        {
            case -1:
                throw RuntimeException( "Could not fork" );
            case 0:
                visitor.path_name += "I";
                symbolic::dump_if( visitor.trace, global_driver->get_filename(),
                    node->condition_->location.begin.line, sym_cond );
                visitor.path_conditions.push_back( sym_cond );
                walk_statement( node->then_ );
                break;
            default:
            {
                // at the moment this limits parallelism, but ensures a
                // deterministic
                // trace output on stdout
                int status;
                if( waitpid( pid, &status, 0 ) == -1 )
                {
                    throw RuntimeException( "error waiting for child process" );
                }
                if( WEXITSTATUS( status ) != 0 )
                {
                    throw RuntimeException( "error in child process" );
                }

                if( cond.value.sym->condition )
                {
                    sym_cond->op = invert( sym_cond->op );
                }
                else
                {
                    // needed to generate correct output for boolean functions
                    // as conditions
                    delete sym_cond;
                    sym_cond = new symbolic_condition_t( new value_t( cond ),
                        new value_t( (INTEGER_T)0 ),
                        libcasm_ir::Value::EQU_INSTRUCTION );
                }
                visitor.path_name += "E";
                symbolic::dump_if( visitor.trace, global_driver->get_filename(),
                    node->condition_->location.begin.line, sym_cond );
                visitor.path_conditions.push_back( sym_cond );
                if( node->else_ )
                {
                    walk_statement( node->else_ );
                }
            }
        }
    }
    else if( cond.is_undef() )
    {
        throw RuntimeException( node->condition_->location,
            "condition must be true or false but was undef" );
    }
    else if( cond.value.boolean )
    {
        walk_statement( node->then_ );
    }
    else if( node->else_ )
    {
        walk_statement( node->else_ );
    }
}

template <>
void SymbolicExecutionWalker::walk_pop( PopNode* node )
{
    const value_t from = walk_function_atom( node->from );
    if( node->to->symbol_type == FunctionAtom::SymbolType::FUNCTION
        and node->to->symbol->is_symbolic )
    {
        walk_function_atom( node->to );
    }
    visitor.visit_pop( node, from );
}

template <>
void SymbolicExecutionWalker::walk_case( CaseNode* node )
{
    const value_t cond = walk_atom( node->expr );

    for( uint32_t i = 0; i < node->case_list.size(); i++ )
    {
        auto pair = node->case_list[ i ];
        // pair.first == nullptr for default:
        symbolic_condition_t* sym_cond;
        if( pair.first )
        {
            const value_t c = walk_atom( pair.first );
            sym_cond = new symbolic_condition_t( new value_t( cond ),
                new value_t( c ), libcasm_ir::Value::EQU_INSTRUCTION );

            switch(
                symbolic::check_condition( visitor.path_conditions, sym_cond ) )
            {
                case symbolic::check_status_t::NOT_FOUND:
                    break;
                case symbolic::check_status_t::TRUE:
                    symbolic::dump_pathcond_match( visitor.trace,
                        global_driver->get_filename(),
                        pair.first->location.begin.line, sym_cond, true );
                    walk_statement( pair.second );
                    return;
                default:
                    break;
            }
        }

        pid_t pid = fork();
        switch( pid )
        {
            case -1:
                throw RuntimeException( "Could not fork" );
            case 0:
            {
                if( pair.first )
                {
                    visitor.path_name += std::to_string( i );
                    visitor.path_conditions.push_back( sym_cond );
                    symbolic::dump_if( visitor.trace,
                        global_driver->get_filename(),
                        pair.first->location.begin.line, sym_cond );
                }
                else
                {
                    visitor.path_name += "D";
                }
                walk_statement( pair.second );
            }
                return;
            default:
            {
                // at the moment this limits parallelism, but ensures a
                // deterministic
                // trace output on stdout
                int status;
                if( waitpid( pid, &status, 0 ) == -1 )
                {
                    throw RuntimeException( "error waiting for child process" );
                }
                if( WEXITSTATUS( status ) != 0 )
                {
                    throw RuntimeException( "error in child process" );
                }
            }
        }
    }
    exit( 0 ); // FIXME EP: ask Florian if this is indended
}

template <>
void SymbolicExecutionWalker::walk_iterate( UnaryNode* node )
{
    visitor.fork( UpdateSet::Type::Sequential );

    while( true )
    {
        visitor.fork( UpdateSet::Type::Parallel );
        walk_statement( node->child_ );
        if( visitor.hasEmptyUpdateSet() )
        {
            visitor.merge(); // to remove the update set from the stack
            break;
        }
        visitor.merge();
    }

    visitor.merge();
}

template <>
void SymbolicExecutionWalker::walk_update( UpdateNode* node )
{
    const auto value = walk_atom( node->expr_ );
    auto argumentValues = evaluateExpressions( node->func->arguments );
    visitor.visit_update( node, argumentValues, value );
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
