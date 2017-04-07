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

#ifndef _LIB_CASMFE_NAMESPACE_H_
#define _LIB_CASMFE_NAMESPACE_H_

#include "Logger.h"
#include "ast/Definition.h"
#include "ast/Expression.h"

namespace libcasm_fe
{
    /**
     * @extends CasmFE
     */
    class Namespace
    {
      public:
        class Symbol
        {
          public:
            Symbol( const Ast::Identifier& identifier,
                Ast::Node& definition,
                const Ast::CallExpression::TargetType targetType,
                const std::size_t arity );

            const Ast::Identifier& identifier( void ) const;
            Ast::Node& definition( void );
            Ast::CallExpression::TargetType targetType( void ) const;
            std::size_t arity( void ) const;

          private:
            const Ast::Identifier& m_identifier;
            Ast::Node& m_definition;
            Ast::CallExpression::TargetType m_targetType;
            std::size_t m_arity;
        };

      public:
        using Ptr = std::shared_ptr< Namespace >;

        Namespace( void );

        u64 registerSymbol(
            Logger& log, const Ast::DirectCallExpression& node );

        u64 registerSymbol( Logger& log, const Ast::FunctionDefinition& node );

        u64 registerSymbol( Logger& log, const Ast::DerivedDefinition& node );

        u64 registerSymbol( Logger& log, const Ast::RuleDefinition& node );

        u64 registerSymbol(
            Logger& log, const Ast::EnumerationDefinition& node );

        Symbol find( const Ast::DirectCallExpression& node ) const;

        Symbol find( const Ast::BasicType& node ) const;

        std::string dump( const std::string& indention = "" ) const;

      private:
        u64 registerSymbol( Logger& log, const Ast::Identifier& node,
            const Ast::Node& definition,
            const Ast::CallExpression::TargetType targetType,
            const std::size_t arity = 0 );

        Symbol find( const Ast::IdentifierPath& node, const std::size_t arity,
            const std::size_t index = 0 ) const;

        std::unordered_map< std::string, Symbol > m_symboltable;

        std::unordered_map< std::string, Namespace::Ptr > m_namespaces;
    };
}

#endif // _LIB_CASMFE_NAMESPACE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
