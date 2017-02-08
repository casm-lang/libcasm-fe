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

#ifndef _LIB_CASMFE_DEFINITION_H_
#define _LIB_CASMFE_DEFINITION_H_

#include "Node.h"
#include "Rule.h"

namespace libcasm_ir
{
    class Type;
}

namespace libcasm_fe
{
    namespace Ast
    {
        class Definition : public Node
        {
          public:
            using Ptr = std::shared_ptr< Definition >;

            using Node::Node;
        };

        using Definitions = NodeList< Definition >;

        class Signature // TODO move it to the correct place
        {
          public:
            using Ptr = std::shared_ptr< Signature >;

            Signature( const std::vector< libcasm_ir::Type* >& argumentTypes,
                libcasm_ir::Type* returnType );
            Signature( const std::vector< libcasm_ir::Type* >& argumentTypes );

            std::vector< libcasm_ir::Type* > argumentTypes() const;
            libcasm_ir::Type* returnType() const;

            std::size_t arity() const;

          private:
            std::vector< libcasm_ir::Type* > m_argumentTypes;
            libcasm_ir::Type* m_returnType;
        };

        class FunctionDefinition : public Definition
        {
          public:
            enum class Category
            {
                Monitored,
                Controlled,
                Static
            };

          public:
            using Ptr = std::shared_ptr< FunctionDefinition >;

            FunctionDefinition( Category category,
                const std::string& identifier,
                const Signature::Ptr& signature );

            Category category() const;
            std::string identifier() const;
            Signature::Ptr signature() const;

            void setInitializers(
                const NodeList< UpdateRule >::Ptr& initializers );
            NodeList< UpdateRule >::Ptr initializers() const;

            void setDefaultValue( const Atom::Ptr& defaultValue );
            Atom::Ptr defaultValue() const;

          private:
            Category m_category;
            std::string m_identifier;
            Signature::Ptr m_signature;
            NodeList< UpdateRule >::Ptr m_initializers;
            Atom::Ptr m_defaultValue;
        };

        class DerivedDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DerivedDefinition >;

            DerivedDefinition( const std::string& identifier,
                const Signature::Ptr& signature,
                const Expression::Ptr& expression );

            std::string identifier() const;
            Signature::Ptr signature() const;
            Expression::Ptr expression() const;

          private:
            std::string m_identifier;
            Signature::Ptr m_signature;
            Expression::Ptr m_expression;
        };

        class RuleDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< RuleDefinition >;

            RuleDefinition( const std::string& identifier,
                const Signature::Ptr& signature,
                const Rule::Ptr& rule );

            std::string identifier() const;
            Signature::Ptr signature() const;
            Rule::Ptr rule() const;

          private:
            std::string m_identifier;
            Signature::Ptr m_signature;
            Rule::Ptr m_rule;
        };

        class EnumerationDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< EnumerationDefinition >;

            EnumerationDefinition( const std::string& identifier,
                const std::vector< std::string >& enumerators );

            std::string identifier() const;
            std::vector< std::string > enumerators() const;

          private:
            std::string m_identifier;
            std::vector< std::string > m_enumerators;
        };
    }
}

#endif // _LIB_CASMFE_DEFINITION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
