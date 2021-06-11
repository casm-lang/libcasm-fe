//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
//                Florian Hahn
//                Ioan Molnar
//                <https://github.com/casm-lang/libcasm-fe>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "SymbolicConsistencyVisitor.h"

#include <libstdhl/RestoreOnScopeExit>

#include <algorithm>
#include <sstream>
#include <stdexcept>

using namespace libcasm_fe;
using SCVisitor = SymbolicConsistencyVisitor;

template < typename T >
class ScopedOverwrite : public libstdhl::RestoreOnScopeExit< T >
{
  public:
    ScopedOverwrite( T& target, const T& value )
    : RestoreOnScopeExit< T >( target )
    {
        target = value;
    }
};

std::vector< SCVisitor::BuiltinRule > generateBuiltins( void )
{
    return { { {
                   IR::Value::OPERATOR_INSTRUCTION, IR::Value::ARITHMETIC_INSTRUCTION,
                   IR::Value::ADD_INSTRUCTION,      IR::Value::SUB_INSTRUCTION,
                   IR::Value::MUL_INSTRUCTION,      IR::Value::DIV_INSTRUCTION,
                   IR::Value::POW_INSTRUCTION,      IR::Value::MOD_INSTRUCTION,

                   IR::Value::COMPARE_INSTRUCTION,  IR::Value::EQU_INSTRUCTION,
                   IR::Value::NEQ_INSTRUCTION,      IR::Value::LTH_INSTRUCTION,
                   IR::Value::LEQ_INSTRUCTION,      IR::Value::GTH_INSTRUCTION,
                   IR::Value::GEQ_INSTRUCTION,

                   IR::Value::LOGICAL_INSTRUCTION,  IR::Value::OR_INSTRUCTION,
                   IR::Value::XOR_INSTRUCTION,      IR::Value::AND_INSTRUCTION,
                   IR::Value::IMP_INSTRUCTION,

                   IR::Value::OPERATOR_BUILTIN,     IR::Value::ARITHMETIC_BUILTIN,
                   IR::Value::ADDU_BUILTIN,         IR::Value::ADDS_BUILTIN,
                   IR::Value::SUBU_BUILTIN,         IR::Value::SUBS_BUILTIN,
                   IR::Value::MULU_BUILTIN,         IR::Value::MULS_BUILTIN,

                   IR::Value::COMPARE_BUILTIN,      IR::Value::LESU_BUILTIN,
                   IR::Value::LESS_BUILTIN,         IR::Value::LEQU_BUILTIN,
                   IR::Value::LEQS_BUILTIN,         IR::Value::GREU_BUILTIN,
                   IR::Value::GRES_BUILTIN,         IR::Value::GEQU_BUILTIN,
                   IR::Value::GEQS_BUILTIN,

                   IR::Value::BINARY_BUILTIN,       IR::Value::ZEXT_BUILTIN,
                   IR::Value::SEXT_BUILTIN,         IR::Value::TRUNC_BUILTIN,
                   IR::Value::SHL_BUILTIN,          IR::Value::SHR_BUILTIN,
                   IR::Value::ASHR_BUILTIN,         IR::Value::CLZ_BUILTIN,
                   IR::Value::CLO_BUILTIN,          IR::Value::CLS_BUILTIN,
               },
               2,
               [ & ]( const auto& args ) { return args[ 0 ] && args[ 1 ]; } },
             { {
                   IR::Value::INV_INSTRUCTION,
                   IR::Value::NOT_INSTRUCTION,

                   IR::Value::CASTING_BUILTIN,
                   IR::Value::AS_BOOLEAN_BUILTIN,
                   IR::Value::AS_INTEGER_BUILTIN,
                   IR::Value::AS_BINARY_BUILTIN,
                   IR::Value::AS_STRING_BUILTIN,
                   IR::Value::AS_DECIMAL_BUILTIN,
                   IR::Value::AS_RATIONAL_BUILTIN,
                   IR::Value::AS_ENUMERATION_BUILTIN,

                   IR::Value::STRINGIFY_BUILTIN,
                   IR::Value::DEC_BUILTIN,
                   IR::Value::HEX_BUILTIN,
                   IR::Value::OCT_BUILTIN,
                   IR::Value::BIN_BUILTIN,
               },
               1,
               [ & ]( const auto& args ) { return args[ 0 ]; } },
             { {
                   IR::Value::GENERAL_BUILTIN,
                   IR::Value::IS_SYMBOLIC_BUILTIN,
                   IR::Value::ABORT_BUILTIN,
                   IR::Value::ASSERT_BUILTIN,
                   IR::Value::ASSURE_BUILTIN,
                   IR::Value::SIZE_BUILTIN,
                   IR::Value::AT_BUILTIN,

                   IR::Value::OUTPUT_BUILTIN,
                   IR::Value::PRINT_BUILTIN,
                   IR::Value::PRINTLN_BUILTIN,

               },
               -1,
               [ & ]( const auto& args ) {
                   return SymbolicConsistencyVisitor::FunctionType::NUMERIC;
               } } };
}

SCVisitor::BuiltinRule::BuiltinRule(
    const std::vector< IR::Value::ID > ids,
    int nargs,
    const std::function< FunctionType( const std::vector< FunctionType >& ) > function )
: m_ids( ids )
, m_nargs( nargs )
, m_function( function )
{
}

SCVisitor::FunctionType SCVisitor::BuiltinRule::evaluate(
    const std::vector< FunctionType >& args ) const
{
    // is guaranteed by type inference pass
    assert( args.size() == m_nargs || m_nargs == -1 );

    return m_function( args );
}

bool SCVisitor::BuiltinRule::contains( const IR::Value::ID& id ) const
{
    return std::any_of(
        m_ids.begin(), m_ids.end(), [ & ]( const auto& _id ) { return _id == id; } );
}

SCVisitor::RuleDependency::RuleDependency( const LST::RuleDefinition::Ptr& rule )
: m_rule( rule )
, m_dependsOn()
, m_usedBy()
, m_returns( FunctionType::UNKNOWN )
, m_arguments( rule->arguments()->size(), FunctionType::UNKNOWN )
, m_status( Status::INIT )
{
    if( rule->type()->result().isVoid() )
    {
        m_returns = FunctionType::NUMERIC;
    }
}

const LST::RuleDefinition::Ptr& SCVisitor::RuleDependency::rule( void ) const
{
    return m_rule;
}

std::set< SCVisitor::RuleDependency::Ptr >& SCVisitor::RuleDependency::dependsOn( void )
{
    return m_dependsOn;
}

std::set< SCVisitor::RuleDependency::Ptr >& SCVisitor::RuleDependency::usedBy( void )
{
    return m_usedBy;
}

void SCVisitor::RuleDependency::calls( RuleDependency::Ptr& callee )
{
    m_dependsOn.insert( callee );
}

void SCVisitor::RuleDependency::isCalledBy(
    RuleDependency::Ptr& caller, std::vector< FunctionType >& args )
{
    for( size_t i = 0; i < args.size(); ++i )
    {
        m_arguments[ i ] = m_arguments[ i ] && args[ i ];
    }
    m_usedBy.insert( caller );
}

SCVisitor::FunctionType SCVisitor::RuleDependency::returns( void )
{
    return m_returns;
}

bool SCVisitor::RuleDependency::fullyDefined( void ) const
{
    return std::all_of( m_arguments.begin(), m_arguments.end(), [ & ]( auto& arg ) {
        return arg != FunctionType::UNKNOWN;
    } );
}

void SCVisitor::RuleDependency::define( void )
{
    for( auto& arg : m_arguments )
    {
        if( arg == FunctionType::UNKNOWN )
        {
            arg = FunctionType::NUMERIC;
        }
    }
}

const std::vector< SCVisitor::FunctionType >& SCVisitor::RuleDependency::arguments() const
{
    return m_arguments;
}

SCVisitor::FunctionType SCVisitor::RuleDependency::argumentAt( const size_t index ) const
{
    return m_arguments[ index ];
}

SCVisitor::RuleDependency::Status SCVisitor::RuleDependency::status( void ) const
{
    return m_status;
}

void SCVisitor::RuleDependency::setStatus( Status status )
{
    m_status = status;
}

bool SCVisitor::RuleDependency::inStatus( std::vector< Status > status ) const
{
    return std::any_of( status.begin(), status.end(), [ & ]( auto s ) { return s == m_status; } );
}

SCVisitor::RuleDependency::Ptr SCVisitor::findOrInsert( const LST::RuleDefinition::Ptr& rule )
{
    auto ruleIt = std::find_if( m_dependencies.begin(), m_dependencies.end(), [ & ]( auto& r ) {
        return r->rule() == rule;
    } );
    if( ruleIt == m_dependencies.end() )
    {
        return *( m_dependencies.insert( std::make_shared< RuleDependency >( rule ) ) ).first;
    }
    else
    {
        return *ruleIt;
    }
}

SCVisitor::Conflict::Conflict(
    const LST::FunctionDefinition::Ptr& function,
    const std::vector< libstdhl::SourceLocation >& locations,
    Cause cause )
: Conflict( description( function, cause ), function, locations, cause )
{
}

SCVisitor::Conflict::Conflict(
    const std::string& msg,
    const LST::FunctionDefinition::Ptr& function,
    const std::vector< libstdhl::SourceLocation >& locations,
    Cause cause )
: Exception( locations, msg, Code::Unspecified )
, m_function( function )
, m_cause( cause )
{
}

LST::FunctionDefinition::Ptr& SCVisitor::Conflict::conflictingFunction( void )
{
    return m_function;
}

std::string SCVisitor::Conflict::description(
    const LST::FunctionDefinition::Ptr& function, Cause cause )
{
    std::stringstream str;
    str << "Promoting function '" << function->identifier()->name() << "' to be symbolic."
        << std::endl;
    str << "Cause: " << causeDescription( cause );
    return str.str();
}

std::string SCVisitor::Conflict::causeDescription( Cause cause )
{
    switch( cause )
    {
        case Cause::UPDATE:
        {
            return "Function is updated with symbolic value.";
        }
        case Cause::CALLED:
        {
            return "Function is called with symbolic argument.";
        }
        case Cause::CONDITION:
        {
            return "Function is updated in a condition.";
        }
    }
}

SCVisitor::Abort::Abort( void )
: std::logic_error( "rule check aborted" )
{
}

SCVisitor::Frame::Frame( LST::Node* callee, std::size_t numberOfLocals )
: m_callee( callee )
, m_locals( numberOfLocals, FunctionType::UNKNOWN )
{
}

LST::Node* SCVisitor::Frame::callee( void ) const
{
    return m_callee;
}

void SCVisitor::Frame::setLocal( std::size_t index, FunctionType function )
{
    assert( index < m_locals.size() );
    m_locals[ index ] = function;
}

SCVisitor::FunctionType SCVisitor::Frame::local( std::size_t index )
{
    assert( index < m_locals.size() );
    return m_locals[ index ];
}

std::vector< SCVisitor::FunctionType >& SCVisitor::Frame::locals( void )
{
    return m_locals;
}

SymbolicConsistencyVisitor::SymbolicConsistencyVisitor( Logger& logger )
: m_logger( logger )
, m_dependencies()
, m_stack()
, m_context()
, m_forceContextCreation( false )
, m_unknownUpdate( false )
, m_evaluateUpdateLocation( false )
, m_updateLocation( nullptr )
, m_currentRule( nullptr )
, m_frame( nullptr )
, m_builtins( generateBuiltins() )
{
    m_context.push( Context::PLAIN );
}

void SymbolicConsistencyVisitor::visit( Specification& specification )
{
    ExecutionLocationRegistry registry;
    Storage storage;
    SCStateInitializationVisitor initVisitor( registry, storage, m_logger );
    try
    {
        initVisitor.visit( specification );
    }
    catch( Abort ignore )
    {
        assert( !"rule calles in init definitions are not supported." );
    }

    const auto end = storage.programState().end();
    for( auto it = storage.programState().begin(); it != end; ++it )
    {
        auto value = it.value();
        const auto& ruleRef = static_cast< const ReferenceConstant& >( value );

        if( ruleRef.defined() )
        {
            const auto& literal = ruleRef.value();
            assert(
                ( literal->reference()->id() == LST::Node::ID::RULE_DEFINITION ) &&
                "Must be a rule reference" );

            const auto& rule =
                std::static_pointer_cast< LST::RuleDefinition >( literal->reference() );
            assert(
                ( rule->arguments()->size() == 0 ) && "Only parameter-less rules are supported" );
            m_dependencies.insert( std::make_shared< RuleDependency >( rule ) );
        }
    }

    using Status = RuleDependency::Status;
    while( not done() )
    {
        // TODO: if no more progress is made, set m_forceContextCreation = true
        // with all rules having a return type Void, this condition cannot happen

        m_stack.clear();
        m_context.clear();
        m_context.push( Context::PLAIN );

        auto rule = nextRule();

        m_currentRule = rule->rule();

        m_frame = std::make_shared< Frame >(
            m_currentRule.get(), m_currentRule->maximumNumberOfLocals() );

        for( size_t i = 0; i < m_currentRule->arguments()->size(); ++i )
        {
            m_frame->setLocal(
                m_currentRule->arguments()->at( i )->localIndex(), rule->argumentAt( i ) );
        }

        try
        {
            rule->setStatus( Status::STARTED );
            m_unknownUpdate = false;
            m_currentRule->accept( *this );
        }
        catch( Abort ignore )
        {
            continue;
        }

        if( m_unknownUpdate || ( not m_currentRule->type()->result().isVoid() &&
                                 m_stack.pop() == FunctionType::UNKNOWN ) )
        {
            rule->setStatus( Status::EVALUATED );
        }
        else
        {
            rule->setStatus( Status::FINISHED );
        }
        bool allEvaluated =
            std::all_of( m_dependencies.begin(), m_dependencies.end(), [ & ]( const auto& dep ) {
                return dep->inStatus( { Status::EVALUATED, Status::FINISHED } );
            } );

        if( allEvaluated )
        {
            for( auto& dep : m_dependencies )
            {
                dep->define();
            }
        }
    }
}

// void SymbolicConsistencyVisitor::visit( LST::Initially& node )
// {
//     // just evaluate the encapsulated initializers
//     node.initializers()->accept( *this );
// }

// void SymbolicConsistencyVisitor::visit( LST::Initializer& node )
// {
//     ScopedOverwrite< LST::FunctionDefinition::Ptr > withUpdateLocation( m_updateLocation, nullptr
//     );
//     {
//         ScopedOverwrite< bool > withLocationEvaluation( m_evaluateUpdateLocation, true );
//         node.function()->accept( *this );

//         assert( m_updateLocation != nullptr && "update location must be defined" );
//     }
//     auto args = typeOfList( node.arguments() );

//     auto function = m_stack.pop();

//     node.value()->accept( *this );
//     auto value = m_stack.pop();

//     if( function == FunctionType::NUMERIC )
//     {
//         if( value == FunctionType::SYMBOLIC )
//         {
//             throw Conflict( m_updateLocation, { node.sourceLocation() }, Conflict::Cause::UPDATE
//             );
//         }
//         if( args == FunctionType::SYMBOLIC )
//         {
//             throw Conflict( m_updateLocation, { node.sourceLocation() }, Conflict::Cause::CALLED
//             );
//         }
//         if( value == FunctionType::UNKNOWN || args == FunctionType::UNKNOWN )
//         {
//             m_unknownUpdate = true;
//             return;
//         }
//         if( m_context.top() == Context::CONDITIONAL )
//         {
//             throw Conflict(
//                 m_updateLocation, { node.sourceLocation() }, Conflict::Cause::CONDITION );
//         }
//     }
//     if( function == FunctionType::UNKNOWN )
//     {
//         m_logger.warning(
//             { node.sourceLocation() }, "update location is unknown if symbolic or numeric" );
//         if( value == FunctionType::SYMBOLIC )
//         {
//             m_logger.warning(
//                 { node.sourceLocation() }, "function may be numeric with symbolic update" );
//         }
//         m_unknownUpdate = true;
//     }
// }

void SymbolicConsistencyVisitor::visit( LST::VariableDefinition& node )
{
    m_stack.push( m_frame->local( node.localIndex() ) );
}

void SymbolicConsistencyVisitor::visit( LST::FunctionDefinition& node )
{
    if( m_evaluateUpdateLocation )
    {
        m_updateLocation = node.ptr< LST::FunctionDefinition >();
    }
    m_stack.push( node.symbolic() ? FunctionType::SYMBOLIC : FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( LST::DerivedDefinition& node )
{
    node.expression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::RuleDefinition& node )
{
    node.rule()->accept( *this );

    const auto& returnType = node.type()->ptr_result();
    if( not returnType->isVoid() )
    {
        if( false /* update set has result update */ )
        {
            // const auto& value = TODO get update value and REMOVE update from
            // update set
            // TODO validate return value
            // m_evaluationStack.push( value );
        }
        else
        {
            m_stack.push( FunctionType::NUMERIC );
        }
    }
}

void SymbolicConsistencyVisitor::visit( LST::EnumeratorDefinition& node )
{
    m_stack.push( FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( LST::InvariantDefinition& node )
{
    node.expression()->accept( *this );
    m_stack.pop();
}

// void SymbolicConsistencyVisitor::visit( LST::UndefLiteral& node )
// {
//     m_stack.push( FunctionType::NUMERIC );
// }

void SymbolicConsistencyVisitor::visit( LST::ValueLiteral& node )
{
    m_stack.push( FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( LST::ReferenceLiteral& node )
{
    m_stack.push( FunctionType::NUMERIC );
}

void SymbolicConsistencyVisitor::visit( LST::ListLiteral& node )
{
    auto type = typeOfList( node.expressions() );
    m_stack.push( type );
}

void SymbolicConsistencyVisitor::visit( LST::RangeLiteral& node )
{
    node.left()->accept( *this );
    auto left = m_stack.pop();

    node.right()->accept( *this );
    auto right = m_stack.pop();

    m_stack.push( left && right );
}

void SymbolicConsistencyVisitor::visit( LST::TupleLiteral& node )
{
    auto type = typeOfList( node.expressions() );
    m_stack.push( type );
}

void SymbolicConsistencyVisitor::visit( LST::RecordLiteral& node )
{
    auto type = typeOfList( node.namedExpressions() );
    m_stack.push( type );
}

// void SymbolicConsistencyVisitor::visit( LST::BasicType& node )
// {
//     m_stack.push( FunctionType::NUMERIC );
// }

// void SymbolicConsistencyVisitor::visit( LST::EmbracedExpression& node )
// {
//     // just evaluate the named expression and push it to the stack
//     node.expression()->accept( *this );
// }

void SymbolicConsistencyVisitor::visit( LST::NamedExpression& node )
{
    // just evaluate the named expression and push it to the stack
    node.expression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::DirectCallExpression& node )
{
    using TargetType = LST::DirectCallExpression::TargetType;
    switch( node.targetType() )
    {
        case TargetType::FUNCTION:
        {
            const auto& function =
                std::static_pointer_cast< LST::FunctionDefinition >( node.targetDefinition() );
            function->accept( *this );
            auto functionType = m_stack.pop();

            assert(
                functionType != FunctionType::UNKNOWN &&
                "function type of definition must be symbolic or numeric" );

            if( functionType == FunctionType::SYMBOLIC )
            {
                m_stack.push( FunctionType::SYMBOLIC );
                return;
            }

            auto type = typeOfList( node.arguments() );
            if( type == FunctionType::SYMBOLIC )
            {
                throw SCVisitor::Conflict(
                    function, { node.sourceLocation() }, Conflict::Cause::CALLED );
            }
            m_stack.push( type );
            break;
        }
        case TargetType::DERIVED:
        {
            const auto& definition = node.targetDefinition();
            // derived function needs its own frame
            auto oldFrame = m_frame;
            m_frame =
                std::make_shared< Frame >( definition.get(), definition->maximumNumberOfLocals() );
            std::size_t localIndex = 0;
            for( const auto& argument : *node.arguments() )
            {
                argument->accept( *this );
                const auto value = m_stack.pop();
                m_frame->setLocal( localIndex, value );
                ++localIndex;
            }

            definition->accept( *this );
            m_frame = oldFrame;
            break;
        }
        case TargetType::RULE:
        {
            assert( node.targetDefinition()->id() == LST::Node::ID::RULE_DEFINITION );

            const auto rule =
                std::static_pointer_cast< LST::RuleDefinition >( node.targetDefinition() );
            auto args = toTypeList( node.arguments() );
            auto result = callRule( rule, args );
            if( not node.type()->result().isVoid() )
            {
                m_stack.push( result );
            }
            break;
        }
        case TargetType::BUILTIN:
        {
            // const auto& id = node.targetDefinition()->id();
            // const auto& type = node.targetDefinition()->type();
            // if( not type->result().isVoid() )
            // {
            //     bool found = false;
            //     for( const auto& rule : m_builtins )
            //     {
            //         if( rule.contains( id ) )
            //         {
            //             auto args = toTypeList( node.arguments() );
            //             m_stack.push( rule.evaluate( args ) );
            //             found = true;
            //             break;
            //         }
            //     }
            //     if( not found )
            //     {
            //         m_logger.error( "Unknown Builtin '" + IR::Value::token( id ) + "'." );
            //         m_stack.push(
            //             m_forceContextCreation ? FunctionType::SYMBOLIC : FunctionType::UNKNOWN );
            //     }
            // }
            break;
        }
        case TargetType::DOMAINTYPE:
        {
            // no symbolic types
            m_stack.push( FunctionType::NUMERIC );
            break;
        }
        case TargetType::CONSTANT:  // [[fallthrough]]
        case TargetType::VARIABLE:
        {
            node.targetDefinition()->accept( *this );
            break;
        }
        // case TargetType::SELF:
        // {
        //     m_stack.push( FunctionType::NUMERIC );
        //     break;
        // }
        case TargetType::UNKNOWN:
        {
            assert( !"cannot call an unknown target" );
            break;
        }
    }
}

// void SymbolicConsistencyVisitor::visit( LST::MethodCallExpression& node )
// {
//     node.object()->accept( *this );
//     auto object = m_stack.pop();

//     switch( node.methodType() )
//     {
//         case LST::MethodCallExpression::MethodType::FUNCTION:  // [[fallthrough]]
//         case LST::MethodCallExpression::MethodType::DERIVED:
//         {
//             const auto& function =
//                 std::static_pointer_cast< LST::FunctionDefinition >( node.targetDefinition() );
//             function->accept( *this );
//             auto functionType = m_stack.pop();

//             assert(
//                 functionType != FunctionType::UNKNOWN &&
//                 "function type of definition must be symbolic or numeric" );

//             if( functionType == FunctionType::SYMBOLIC )
//             {
//                 m_stack.push( FunctionType::SYMBOLIC );
//                 return;
//             }

//             auto type = object && typeOfList( node.arguments() );
//             if( type == FunctionType::SYMBOLIC )
//             {
//                 throw SCVisitor::Conflict(
//                     function, { node.sourceLocation() }, Conflict::Cause::CALLED );
//             }
//             m_stack.push( type );
//             break;
//         }
//         case LST::MethodCallExpression::MethodType::RULE:
//         {
//             assert( node.targetDefinition()->id() == LST::Node::ID::RULE_DEFINITION );

//             const auto rule =
//                 std::static_pointer_cast< LST::RuleDefinition >( node.targetDefinition() );
//             auto args = toTypeList( node.arguments() );
//             args.insert( args.begin(), object );

//             auto result = callRule( rule, args );
//             if( not node.type()->result().isVoid() )
//             {
//                 m_stack.push( result );
//             }
//             break;
//         }
//         case LST::MethodCallExpression::MethodType::BUILTIN:
//         {
//             const auto& id = node.targetBuiltinId();
//             const auto& type = node.targetBuiltinType();
//             if( not type->result().isVoid() )
//             {
//                 bool found = false;
//                 for( const auto& rule : m_builtins )
//                 {
//                     if( rule.contains( id ) )
//                     {
//                         auto args = toTypeList( node.arguments() );
//                         args.insert( args.begin(), object );
//                         m_stack.push( rule.evaluate( args ) );
//                         found = true;
//                         break;
//                     }
//                 }
//                 if( not found )
//                 {
//                     m_logger.error( "Unknown Builtin '" + IR::Value::token( id ) + "'." );
//                     m_stack.push(
//                         m_forceContextCreation ? FunctionType::SYMBOLIC : FunctionType::UNKNOWN );
//                 }
//             }
//             break;
//         }
//         case LST::MethodCallExpression::MethodType::UNKNOWN:
//         {
//             assert( !"cannot call an unknown method" );
//             break;
//         }
//     }
// }

// void SymbolicConsistencyVisitor::visit( LST::LiteralCallExpression& node )
// {
//     node.object()->accept( *this );
// }

void SymbolicConsistencyVisitor::visit( LST::IndirectCallExpression& node )
{
    // TODO: fix me: needs evaluation of reference
    m_logger.error(
        { node.sourceLocation() },
        "Indirect calls are not supported in symbolic consistency checks. Result may have errors.",
        Code::Unspecified );
}

// void SymbolicConsistencyVisitor::visit( LST::TypeCastingExpression& node )
// {
//     // no symbolic types -> symbolic state of from expression is symbolic state of casted
//     // expression
//     node.fromExpression()->accept( *this );
// }

// void SymbolicConsistencyVisitor::visit( LST::UnaryExpression& node )
// {
//     node.expression()->accept( *this );
// }

// void SymbolicConsistencyVisitor::visit( LST::BinaryExpression& node )
// {
//     node.left()->accept( *this );
//     auto left = m_stack.pop();

//     node.right()->accept( *this );
//     auto right = m_stack.pop();

//     m_stack.push( left && right );
// }

void SymbolicConsistencyVisitor::visit( LST::LetExpression& node )
{
    node.variableBindings()->accept( *this );
    node.expression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::ConditionalExpression& node )
{
    node.condition()->accept( *this );
    auto condition = m_stack.pop();

    if( not createContext( condition ) )
    {
        m_logger.warning(
            { node.sourceLocation() },
            "Couldn't determine if condition is symbolic or numeric. Assumed symbolic." );
    }

    node.thenExpression()->accept( *this );
    auto thenExp = m_stack.pop();

    node.elseExpression()->accept( *this );
    auto elseExp = m_stack.pop();

    if( m_context.top() == Context::PLAIN )
    {
        m_stack.push( thenExp && elseExp );
    }
    else
    {
        m_stack.push( FunctionType::SYMBOLIC );
    }

    m_context.pop();
}

void SymbolicConsistencyVisitor::visit( LST::ChooseExpression& node )
{
    node.universe()->accept( *this );
    m_stack.pop();

    for( const auto& variable : *node.variables() )
    {
        m_frame->setLocal( variable->localIndex(), FunctionType::SYMBOLIC );
    }
    node.expression()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::UniversalQuantifierExpression& node )
{
    node.universe()->accept( *this );
    auto universe = m_stack.pop();
    for( const auto& variable : *node.predicateVariables() )
    {
        m_frame->setLocal( variable->localIndex(), universe );
    }
    node.proposition()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::ExistentialQuantifierExpression& node )
{
    node.universe()->accept( *this );
    auto universe = m_stack.pop();
    for( const auto& variable : *node.predicateVariables() )
    {
        m_frame->setLocal( variable->localIndex(), universe );
    }
    node.proposition()->accept( *this );
}

// void SymbolicConsistencyVisitor::visit( LST::CardinalityExpression& node )
// {
//     auto args = typeOfList( node.arguments() );
//     node.expression()->accept( *this );
//     auto expression = m_stack.pop();
//     m_stack.push( args && expression );
// }

void SymbolicConsistencyVisitor::visit( LST::ConditionalRule& node )
{
    node.condition()->accept( *this );
    auto condition = m_stack.pop();

    if( not createContext( condition ) )
    {
        m_logger.warning(
            { node.sourceLocation() },
            "Couldn't determine if condition is symbolic or numeric. Assumed symbolic." );
    }

    node.thenRule()->accept( *this );

    node.elseRule()->accept( *this );

    m_context.pop();
}

void SymbolicConsistencyVisitor::visit( LST::CaseRule& node )
{
    node.expression()->accept( *this );
    const auto expression = m_stack.pop();

    if( not createContext( expression ) )
    {
        m_logger.warning(
            { node.sourceLocation() },
            "Couldn't determine if case expression is symbolic or numeric. Assumed symbolic." );
    }

    for( const auto& _case : *node.cases() )
    {
        switch( _case->id() )
        {
            case LST::Node::ID::DEFAULT_CASE:
            {
                _case->rule()->accept( *this );
                break;
            }
            case LST::Node::ID::EXPRESSION_CASE:
            {
                const auto& exprCase = std::static_pointer_cast< LST::ExpressionCase >( _case );
                exprCase->expression()->accept( *this );
                m_stack.pop();

                _case->rule()->accept( *this );
                break;
            }
            default:
            {
                assert( !"unknown case" );
                break;
            }
        }
    }

    m_context.pop();
}

void SymbolicConsistencyVisitor::visit( LST::LetRule& node )
{
    node.variableBindings()->accept( *this );
    node.rule()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::LocalRule& node )
{
    for( const auto& localFunction : *node.localFunctions() )
    {
        localFunction->initially()->accept( *this );
    }
    node.rule()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::ForallRule& node )
{
    node.universe()->accept( *this );
    auto universe = m_stack.pop();
    for( const auto& variable : *node.variables() )
    {
        m_frame->setLocal( variable->localIndex(), universe );
    }
    node.condition()->accept( *this );
    auto condition = m_stack.pop();

    createContext( condition );
    node.rule()->accept( *this );
    m_context.pop();
}

void SymbolicConsistencyVisitor::visit( LST::ChooseRule& node )
{
    node.universe()->accept( *this );
    m_stack.pop();

    for( const auto& variable : *node.variables() )
    {
        m_frame->setLocal( variable->localIndex(), FunctionType::SYMBOLIC );
    }
    node.rule()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::IterateRule& node )
{
    node.rule()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::BlockRule& node )
{
    node.rules()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::SequenceRule& node )
{
    node.rules()->accept( *this );
}

void SymbolicConsistencyVisitor::visit( LST::UpdateRule& node )
{
    ScopedOverwrite< LST::FunctionDefinition::Ptr > withUpdateLocation( m_updateLocation, nullptr );
    {
        ScopedOverwrite< bool > withLocationEvaluation( m_evaluateUpdateLocation, true );
        node.function()->accept( *this );

        assert( m_updateLocation != nullptr && "update location must be defined" );
    }
    auto function = m_stack.pop();

    node.expression()->accept( *this );
    auto expression = m_stack.pop();

    if( function == FunctionType::NUMERIC )
    {
        if( expression == FunctionType::UNKNOWN )
        {
            m_unknownUpdate = true;
            return;
        }
        if( expression == FunctionType::SYMBOLIC )
        {
            throw Conflict( m_updateLocation, { node.sourceLocation() }, Conflict::Cause::UPDATE );
        }
        if( m_context.top() == Context::CONDITIONAL )
        {
            throw Conflict(
                m_updateLocation, { node.sourceLocation() }, Conflict::Cause::CONDITION );
        }
    }
    if( function == FunctionType::UNKNOWN )
    {
        m_logger.warning(
            { node.sourceLocation() }, "update location is unknown if symbolic or numeric" );
        if( expression == FunctionType::SYMBOLIC )
        {
            m_logger.warning(
                { node.sourceLocation() }, "function may be numeric with symbolic update" );
        }
        m_unknownUpdate = true;
    }
}

void SymbolicConsistencyVisitor::visit( LST::CallRule& node )
{
    node.call()->accept( *this );
    const auto& returnType = node.call()->type()->result();
    if( not returnType.isVoid() )
    {
        m_stack.pop();  // drop return value
    }
}

// void SymbolicConsistencyVisitor::visit( LST::WhileRule& node )
// {
//     node.condition()->accept( *this );
//     auto condition = m_stack.pop();

//     if( not createContext( condition ) )
//     {
//         m_logger.warning(
//             { node.sourceLocation() },
//             "Couldn't determine if condition is symbolic or numeric. Assumed symbolic." );
//     }

//     node.rule()->accept( *this );

//     m_context.pop();
// }

void SymbolicConsistencyVisitor::visit( LST::VariableBinding& node )
{
    node.expression()->accept( *this );
    const auto value = m_stack.pop();

    const auto variableIndex = node.variable()->localIndex();
    m_frame->setLocal( variableIndex, value );
}

bool SymbolicConsistencyVisitor::createContext( const FunctionType condition )
{
    if( m_context.top() == Context::CONDITIONAL )
    {
        m_context.push( Context::CONDITIONAL );
        return true;
    }

    switch( condition )
    {
        case FunctionType::UNKNOWN:
        {
            if( not m_forceContextCreation )
            {
                throw Abort();
            }
            else
            {
                m_context.push( Context::CONDITIONAL );
                return false;
            }
        }

        case FunctionType::SYMBOLIC:
        {
            m_context.push( Context::CONDITIONAL );
            break;
        }
        case FunctionType::NUMERIC:
        {
            m_context.push( Context::PLAIN );
            break;
        }
    }
    return true;
}

SymbolicConsistencyVisitor::FunctionType SymbolicConsistencyVisitor::callRule(
    const LST::RuleDefinition::Ptr& rule, std::vector< FunctionType > args )
{
    auto currentDeps = findOrInsert( m_currentRule );

    auto ruleDeps = findOrInsert( rule );
    currentDeps->calls( ruleDeps );

    ruleDeps->isCalledBy( currentDeps, args );

    return ruleDeps->returns();
}

template < class T >
SCVisitor::FunctionType SymbolicConsistencyVisitor::typeOfList( const T& list )
{
    FunctionType type = FunctionType::NUMERIC;
    for( const auto& el : *list )
    {
        el->accept( *this );
        auto value = m_stack.pop();
        type = type && value;
    }
    return type;
}

template < class T >
std::vector< SCVisitor::FunctionType > SymbolicConsistencyVisitor::toTypeList( const T& list )
{
    std::vector< FunctionType > result;
    for( const auto& el : *list )
    {
        el->accept( *this );
        auto value = m_stack.pop();
        result.push_back( value );
    }
    return result;
}

bool SymbolicConsistencyVisitor::done( void ) const
{
    return std::all_of( m_dependencies.begin(), m_dependencies.end(), [ & ]( const auto& dep ) {
        return dep->inStatus( { RuleDependency::Status::FINISHED } );
    } );
}

SymbolicConsistencyVisitor::RuleDependency::Ptr SymbolicConsistencyVisitor::nextRule( void )
{
    using Status = RuleDependency::Status;
    RuleDependency::Ptr next;
    Status nextStatus = Status::FINISHED;
    bool nextDefined = false;
    for( auto const& rule : m_dependencies )
    {
        if( rule->inStatus( { Status::FINISHED } ) )
        {
            continue;
        }
        if( rule->status() < nextStatus )
        {
            next = rule;
            nextStatus = rule->status();
            nextDefined = rule->fullyDefined();
        }
        if( rule->status() == nextStatus && nextDefined == false && rule->fullyDefined() == true )
        {
            next = rule;
            nextStatus = rule->status();
            nextDefined = rule->fullyDefined();
        }
    }
    if( next == nullptr )
    {
        throw RuntimeException(
            {}, "Pass is not done, but no calculatable rule available.", {}, Code::Unspecified );
    }
    return next;
}

SymbolicConsistencyVisitor::FunctionType libcasm_fe::operator&&(
    const SymbolicConsistencyVisitor::FunctionType lhs,
    const SymbolicConsistencyVisitor::FunctionType rhs )
{
    using FunctionType = SymbolicConsistencyVisitor::FunctionType;

    if( lhs == FunctionType::SYMBOLIC || rhs == FunctionType::SYMBOLIC )
    {
        return FunctionType::SYMBOLIC;
    }
    if( lhs == FunctionType::UNKNOWN || rhs == FunctionType::UNKNOWN )
    {
        return FunctionType::UNKNOWN;
    }
    if( lhs == FunctionType::NUMERIC && rhs == FunctionType::NUMERIC )
    {
        return FunctionType::NUMERIC;
    }
    assert( !"invalid Function Type" );
}

SCStateInitializationVisitor::SCStateInitializationVisitor(
    ExecutionLocationRegistry& locationRegistry, Storage& globalState, Logger& logger )
: EmptyVisitor()
, m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_updateSetManager()
, m_logger( logger )
{
}

void SCStateInitializationVisitor::visit( Specification& node )
{
    m_updateSetManager.fork( Semantics::Sequential, 100 );

    // node.header()->accept( *this );
    node.lst()->definitions()->accept( *this );

    auto updateSet = m_updateSetManager.currentUpdateSet();
    m_globalState.fireUpdateSet( updateSet );
    m_updateSetManager.clear();
}

// void SCStateInitializationVisitor::visit( LST::InitDefinition& node )
// {
//     assert( node.programFunction() and "checked during frame size determination pass!" );
//     node.programFunction()->accept( *this );
// }

void SCStateInitializationVisitor::visit( LST::FunctionDefinition& node )
{
    assert( not node.local() );

    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
    if( node.program() )
    {
        ExecutionVisitor executionVisitor(
            m_locationRegistry, m_globalState, m_updateSetManager, ReferenceConstant() );
        node.initially()->accept( executionVisitor );
    }
    else
    {
        SymbolicConsistencyVisitor consistencyVisitor( m_logger );
        node.initially()->accept( consistencyVisitor );
    }
    transaction.merge();
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
