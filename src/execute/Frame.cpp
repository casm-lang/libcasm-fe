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

#include "Frame.h"

#include "../stdhl/cpp/String.h"

#include "../ast/Definition.h"

using namespace libcasm_fe;
using namespace Ast;

namespace ir = libcasm_ir;

Frame::Frame( CallExpression* call, Node* callee, std::size_t numberOfLocals )
: m_call( call )
, m_callee( callee )
, m_locals( numberOfLocals )
{
}

CallExpression* Frame::call( void ) const
{
    return m_call;
}

Node* Frame::callee( void ) const
{
    return m_callee;
}

void Frame::setLocal( std::size_t index, const ir::Constant& local )
{
    assert( index < m_locals.size() );

    m_locals[ index ] = local;
}

const ir::Constant& Frame::local( std::size_t index ) const
{
    assert( index < m_locals.size() );

    return m_locals[ index ];
}

const std::vector< ir::Constant >& Frame::locals( void ) const
{
    return m_locals;
}

FrameStack::FrameStack( void )
: m_frames()
{
}

void FrameStack::push( std::unique_ptr< Frame > frame )
{
    m_frames.emplace_back( std::move( frame ) );
}

std::unique_ptr< Frame > FrameStack::pop( void )
{
    assert( not m_frames.empty() );

    auto frame = std::move( m_frames.back() );
    m_frames.pop_back();
    return frame;
}

Frame* FrameStack::top( void ) const
{
    assert( not m_frames.empty() );

    return m_frames.back().get();
}

static std::string generateBuiltinTraceLine( Frame* frame )
{
    const auto call = frame->call();
    assert( call != nullptr );
    assert( call->targetType() == CallExpression::TargetType::BUILTIN );

    std::string args;
    const auto numberOfArguments = call->arguments()->size();
    for( std::size_t i = 0; i < numberOfArguments; i++ )
    {
        if( i > 0 )
        {
            args += ", ";
        }
        args += frame->local( i ).name();
    }

    std::string name;
    if( call->id() == Node::ID::DIRECT_CALL_EXPRESSION )
    {
        name = call->ptr< DirectCallExpression >()->identifier()->path();
    }
    else
    {
        name = "UNKNOWN";
    }

    return libstdhl::String::format(
        "Builtin %s(%s)", name.c_str(), args.c_str() );
}

static std::string generateCalleeTraceLine(
    Frame* frame, const SourceLocation& problemLocation )
{
    const auto callee = frame->callee();
    assert( callee != nullptr );

    std::string type;
    std::string name;
    std::string args;

    switch( callee->id() )
    {
        case Node::ID::RULE_DEFINITION:
        {
            const auto rule = callee->ptr< RuleDefinition >();
            type = "Rule";
            name = rule->identifier()->name();

            bool isFirstArg = true;
            for( const auto& arg : *rule->arguments() )
            {
                if( not isFirstArg )
                {
                    args += ", ";
                }
                isFirstArg = false;

                args += arg->identifier()->name() + "="
                        + frame->local( arg->localIndex() ).name();
            }
            break;
        }
        case Node::ID::DERIVED_DEFINITION:
        {
            const auto derived = callee->ptr< DerivedDefinition >();
            type = "Derived";
            name = derived->identifier()->name();

            bool isFirstArg = true;
            for( const auto& arg : *derived->arguments() )
            {
                if( not isFirstArg )
                {
                    args += ", ";
                }
                isFirstArg = false;

                args += arg->identifier()->name() + "="
                        + frame->local( arg->localIndex() ).name();
            }
            break;
        }
        case Node::ID::FUNCTION_DEFINITION:
        {
            const auto function = callee->ptr< FunctionDefinition >();
            type = "Function";
            name = function->identifier()->name();

            const auto numberOfArguments = function->argumentTypes()->size();
            for( std::size_t i = 0; i < numberOfArguments; i++ )
            {
                if( i > 0 )
                {
                    args += ", ";
                }
                args += frame->local( i ).name();
            }
            break;
        }
        default:
        {
            type = callee->description();
            name = "UNKNOWN";
        }
    }

    return libstdhl::String::format( "%s %s(%s) at %s:%u",
        type.c_str(),
        name.c_str(),
        args.c_str(),
        problemLocation.fileName()->c_str(),
        problemLocation.begin.line );
}

std::vector< std::string > FrameStack::generateBacktrace(
    SourceLocation problemLocation, const libcasm_ir::Constant& agentId ) const
{
    std::vector< std::string > backtrace;
    backtrace.reserve( m_frames.size() );

    backtrace.emplace_back( "# Agent " + agentId.name() + ":" );

    std::size_t frameCounter = 0;

    const auto end = m_frames.rend();
    for( auto it = m_frames.rbegin(); it != end; ++it )
    {
        const auto& frame = *it;

        const auto call = frame->call();
        const auto callee = frame->callee();

        // callee can only be nullptr when calling builtins
        const auto traceLine
            = ( callee == nullptr )
                  ? generateBuiltinTraceLine( frame.get() )
                  : generateCalleeTraceLine( frame.get(), problemLocation );
        backtrace.emplace_back(
            "#" + std::to_string( frameCounter ) + " in " + traceLine );

        ++frameCounter;

        if( call != nullptr )
        {
            problemLocation = call->sourceLocation();
        }
    }

    return backtrace;
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
