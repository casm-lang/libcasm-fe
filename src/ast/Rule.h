//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#ifndef _LIBCASM_FE_AST_RULE_H_
#define _LIBCASM_FE_AST_RULE_H_

#include <libcasm-fe/ast/Expression>
#include <libcasm-fe/ast/Node>

namespace libcasm_fe
{
    namespace AST
    {
        class VariableDefinition;
        using VariableDefinitions = NodeList< VariableDefinition >;

        class FunctionDefinition;
        using FunctionDefinitions = NodeList< FunctionDefinition >;

        class Rule : public Node
        {
          public:
            using Ptr = std::shared_ptr< Rule >;

            Rule( const Node::ID id );

          protected:
            void clone( Rule& duplicate ) const;
        };

        using Rules = NodeList< Rule >;

        class SkipRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SkipRule >;

            explicit SkipRule( void );

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        class ConditionalRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ConditionalRule >;

            ConditionalRule(
                const Expression::Ptr& condition,
                const Rule::Ptr& thenRule,
                const Rule::Ptr& elseRule );

            const Expression::Ptr& condition( void ) const;

            const Rule::Ptr& thenRule( void ) const;

            const Rule::Ptr& elseRule( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_condition;
            const Rule::Ptr m_thenRule;
            const Rule::Ptr m_elseRule;
        };

        class Case : public Node
        {
          public:
            using Ptr = std::shared_ptr< Case >;

            Case( Node::ID id, const Rule::Ptr& rule );

            const Rule::Ptr& rule( void ) const;

          protected:
            void clone( Case& duplicate ) const;

          private:
            const Rule::Ptr m_rule;
        };

        using Cases = NodeList< Case >;

        class DefaultCase final : public Case
        {
          public:
            using Ptr = std::shared_ptr< DefaultCase >;

            explicit DefaultCase( const Rule::Ptr& rule );

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        class ExpressionCase final : public Case
        {
          public:
            using Ptr = std::shared_ptr< ExpressionCase >;

            ExpressionCase( const Expression::Ptr& expression, const Rule::Ptr& rule );

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_expression;
        };

        class CaseRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< CaseRule >;

            CaseRule( const Expression::Ptr& expression, const Cases::Ptr& cases );

            const Expression::Ptr& expression( void ) const;
            const Cases::Ptr& cases( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_expression;
            const Cases::Ptr m_cases;
        };

        class LetRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< LetRule >;

            LetRule( const VariableBindings::Ptr& variableBindings, const Rule::Ptr& rule );

            const VariableBindings::Ptr& variableBindings( void ) const;

            const Rule::Ptr& rule( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const VariableBindings::Ptr m_variableBindings;
            const Rule::Ptr m_rule;
        };

        class LocalRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< LocalRule >;

            LocalRule(
                const std::shared_ptr< FunctionDefinitions >& localFunctions,
                const Rule::Ptr& rule );

            const std::shared_ptr< FunctionDefinitions >& localFunctions( void ) const;

            const Rule::Ptr& rule( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const std::shared_ptr< FunctionDefinitions > m_localFunctions;
            const Rule::Ptr m_rule;
        };

        class ForallRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ForallRule >;

            ForallRule(
                const std::shared_ptr< VariableDefinitions >& variables,
                const Expression::Ptr& universe,
                const Expression::Ptr& condition,
                const Rule::Ptr& rule );

            const std::shared_ptr< VariableDefinitions >& variables( void ) const;

            const Expression::Ptr& universe( void ) const;

            const Expression::Ptr& condition( void ) const;

            const Rule::Ptr& rule( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const std::shared_ptr< VariableDefinitions > m_variables;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_condition;
            const Rule::Ptr m_rule;
        };

        class ChooseRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ChooseRule >;

            ChooseRule( const VariableSelection::Ptr& variableSelection, const Rule::Ptr& rule );

            const VariableSelection::Ptr& variableSelection( void ) const;

            const Rule::Ptr& rule( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const VariableSelection::Ptr m_variableSelection;
            const Rule::Ptr m_rule;
        };

        class IterateRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< IterateRule >;

            explicit IterateRule( const Rule::Ptr& rule );

            const Rule::Ptr& rule( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Rule::Ptr m_rule;
        };

        class BlockRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< BlockRule >;

            explicit BlockRule( const Rules::Ptr& rules );

            const Rules::Ptr& rules( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Rules::Ptr m_rules;
        };

        class SequenceRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SequenceRule >;

            explicit SequenceRule( const Rules::Ptr& rules );

            const Rules::Ptr& rules( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Rules::Ptr m_rules;
        };

        class UpdateRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< UpdateRule >;

            UpdateRule( const CallExpression::Ptr& function, const Expression::Ptr& expression );

            const CallExpression::Ptr& function( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const CallExpression::Ptr m_function;
            const Expression::Ptr m_expression;
        };

        using UpdateRules = NodeList< UpdateRule >;

        class CallRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< CallRule >;

            CallRule( const CallExpression::Ptr& call );

            const CallExpression::Ptr& call( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const CallExpression::Ptr m_call;
        };
    }
}

#endif  // _LIBCASM_FE_AST_RULE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
