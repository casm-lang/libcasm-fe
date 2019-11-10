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

#include "Frame.h"

#include "../ast/Definition.h"

#include <libstdhl/String>

using namespace libcasm_fe;
using namespace Ast;

namespace ir = libcasm_ir;

std::size_t Frame::id = 0;

Frame::Frame( CallExpression* call, Node* callee, std::size_t numberOfLocals )
: m_call( call )
, m_callee( callee )
, m_locals( numberOfLocals )
, m_frameId( id++ )
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

static std::string generateCalleeTraceLine( Frame* frame, const SourceLocation& problemLocation )
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

                args += arg->identifier()->name() + "=" + frame->local( arg->localIndex() ).name();
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

                args += arg->identifier()->name() + "=" + frame->local( arg->localIndex() ).name();
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
        case Node::ID::INVARIANT_DEFINITION:
        {
            const auto invariant = callee->ptr< InvariantDefinition >();
            type = "Invariant";
            name = invariant->identifier()->name();
            break;
        }
        case Node::ID::BUILTIN_DEFINITION:
        {
            const auto builtin = callee->ptr< BuiltinDefinition >();
            type = "Builtin";
            name = builtin->identifier()->name();
            break;
        }
        default:
        {
            type = callee->description();
            name = "UNKNOWN";
        }
    }

    return libstdhl::String::format(
        "%s %s(%s) at %s:%u",
        type.c_str(),
        name.c_str(),
        args.c_str(),
        problemLocation.fileName()->c_str(),
        problemLocation.begin.line );
}

std::vector< std::string > FrameStack::generateBacktrace(
    libstdhl::SourceLocation problemLocation, const libcasm_ir::Constant& agentId ) const
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
        const auto traceLine = generateCalleeTraceLine( frame.get(), problemLocation );
        backtrace.emplace_back( "#" + std::to_string( frameCounter ) + " in " + traceLine );

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
