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

#ifndef _LIBCASM_FE_RULE_H_
#define _LIBCASM_FE_RULE_H_

#include <libcasm-fe/ast/Expression>
#include <libcasm-fe/ast/Node>
#include <libcasm-fe/ast/Token>

#include <set>

namespace libcasm_fe
{
    namespace Ast
    {
        class VariableDefinition;
        using VariableDefinitions = NodeList< VariableDefinition >;

        class FunctionDefinition;
        using FunctionDefinitions = NodeList< FunctionDefinition >;

        class Rule : public Node
        {
          public:
            using Ptr = std::shared_ptr< Rule >;

            using Node::Node;
        };

        using Rules = NodeList< Rule >;

        class SkipRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SkipRule >;

            SkipRule( const Token::Ptr& skipToken );

            explicit SkipRule( void );

            const Token::Ptr& skipToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Token::Ptr m_skipToken;
        };

        class ConditionalRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ConditionalRule >;

            ConditionalRule(
                const Token::Ptr& ifToken,
                const Expression::Ptr& condition,
                const Token::Ptr& thenToken,
                const Rule::Ptr& thenRule,
                const Token::Ptr& elseToken,
                const Rule::Ptr& elseRule );

            ConditionalRule(
                const Token::Ptr& ifToken,
                const Expression::Ptr& condition,
                const Token::Ptr& thenToken,
                const Rule::Ptr& thenRule );

            const Expression::Ptr& condition( void ) const;
            const Rule::Ptr& thenRule( void ) const;
            const Rule::Ptr& elseRule( void ) const;

            const Token::Ptr& ifToken( void ) const;

            const Token::Ptr& thenToken( void ) const;

            const Token::Ptr& elseToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_condition;
            const Rule::Ptr m_thenRule;
            const Rule::Ptr m_elseRule;
            const Token::Ptr m_ifToken;
            const Token::Ptr m_thenToken;
            const Token::Ptr m_elseToken;
        };

        class Case : public Node
        {
          public:
            using Ptr = std::shared_ptr< Case >;

            Case( Node::ID id, const Token::Ptr& colonToken, const Rule::Ptr& rule );

            const Rule::Ptr& rule( void ) const;

            const Token::Ptr& colonToken( void ) const;

          private:
            const Rule::Ptr m_rule;
            const Token::Ptr m_colonToken;
        };

        using Cases = NodeList< Case >;

        class DefaultCase final : public Case
        {
          public:
            using Ptr = std::shared_ptr< DefaultCase >;

            explicit DefaultCase(
                const Token::Ptr& labelToken, const Token::Ptr& colonToken, const Rule::Ptr& rule );

            const Token::Ptr& labelToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Token::Ptr m_labelToken;
        };

        class ExpressionCase final : public Case
        {
          public:
            using Ptr = std::shared_ptr< ExpressionCase >;

            ExpressionCase(
                const Expression::Ptr& expression,
                const Token::Ptr& colonToken,
                const Rule::Ptr& rule );

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_expression;
        };

        class CaseRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< CaseRule >;

            CaseRule(
                const Token::Ptr& caseToken,
                const Expression::Ptr& expression,
                const Token::Ptr& ofToken,
                const Token::Ptr& leftBraceToken,
                const Cases::Ptr& cases,
                const Token::Ptr& rightBraceToken );

            const Expression::Ptr& expression( void ) const;
            const Cases::Ptr& cases( void ) const;

            const Token::Ptr& caseToken( void ) const;

            const Token::Ptr& ofToken( void ) const;

            const Token::Ptr& leftBraceToken( void ) const;

            const Token::Ptr& rightBraceToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_expression;
            const Cases::Ptr m_cases;
            const Token::Ptr m_caseToken;
            const Token::Ptr m_ofToken;
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
        };

        class LetRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< LetRule >;

            LetRule(
                const Token::Ptr& letToken,
                const VariableBindings::Ptr& variableBindings,
                const Token::Ptr& inToken,
                const Rule::Ptr& rule );

            const VariableBindings::Ptr& variableBindings( void ) const;
            const Rule::Ptr& rule( void ) const;

            const Token::Ptr& letToken( void ) const;

            const Token::Ptr& inToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const VariableBindings::Ptr m_variableBindings;
            const Rule::Ptr m_rule;
            const Token::Ptr m_letToken;
            const Token::Ptr m_inToken;
        };

        class LocalRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< LocalRule >;

            LocalRule(
                const Token::Ptr& localToken,
                const std::shared_ptr< FunctionDefinitions >& localFunctions,
                const Token::Ptr& inToken,
                const Rule::Ptr& rule );

            const std::shared_ptr< FunctionDefinitions >& localFunctions( void ) const;
            const Rule::Ptr& rule( void ) const;

            const Token::Ptr& localToken( void ) const;

            const Token::Ptr& inToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< FunctionDefinitions > m_localFunctions;
            const Rule::Ptr m_rule;
            const Token::Ptr m_localToken;
            const Token::Ptr m_inToken;
        };

        class ForallRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ForallRule >;

            ForallRule(
                const Token::Ptr& forallToken,
                const std::shared_ptr< VariableDefinitions >& variables,
                const Token::Ptr& inToken,
                const Expression::Ptr& universe,
                const Token::Ptr& doToken,
                const Rule::Ptr& rule );

            ForallRule(
                const Token::Ptr& forallToken,
                const std::shared_ptr< VariableDefinitions >& variables,
                const Token::Ptr& inToken,
                const Expression::Ptr& universe,
                const Token::Ptr& withToken,
                const Expression::Ptr& condition,
                const Token::Ptr& doToken,
                const Rule::Ptr& rule );

            const std::shared_ptr< VariableDefinitions >& variables( void ) const;
            const Expression::Ptr& universe( void ) const;
            const Expression::Ptr& condition( void ) const;
            const Rule::Ptr& rule( void ) const;

            const Token::Ptr& forallToken( void ) const;

            const Token::Ptr& inToken( void ) const;

            const Token::Ptr& withToken( void ) const;

            const Token::Ptr& doToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinitions > m_variables;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_condition;
            const Rule::Ptr m_rule;
            const Token::Ptr m_forallToken;
            const Token::Ptr m_inToken;
            const Token::Ptr m_withToken;
            const Token::Ptr m_doToken;
        };

        class ChooseRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ChooseRule >;

            ChooseRule(
                const Token::Ptr& chooseToken,
                const std::shared_ptr< VariableDefinitions >& variables,
                const Token::Ptr& inToken,
                const Expression::Ptr& universe,
                const Token::Ptr& doToken,
                const Rule::Ptr& rule );

            const std::shared_ptr< VariableDefinitions >& variables( void ) const;
            const Expression::Ptr& universe( void ) const;
            const Rule::Ptr& rule( void ) const;

            const Token::Ptr& chooseToken( void ) const;

            const Token::Ptr& inToken( void ) const;

            const Token::Ptr& doToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinitions > m_variables;
            const Expression::Ptr m_universe;
            const Rule::Ptr m_rule;
            const Token::Ptr m_chooseToken;
            const Token::Ptr m_inToken;
            const Token::Ptr m_doToken;
        };

        class IterateRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< IterateRule >;

            explicit IterateRule( const Token::Ptr& iterateToken, const Rule::Ptr& rule );

            const Rule::Ptr& rule( void ) const;

            const Token::Ptr& iterateToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Rule::Ptr m_rule;
            const Token::Ptr m_iterateToken;
        };

        class BlockRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< BlockRule >;

            explicit BlockRule(
                const Token::Ptr& leftBraceToken,
                const Rules::Ptr& rules,
                const Token::Ptr& rightBraceToken );

            const Rules::Ptr& rules( void ) const;

            const Token::Ptr& leftBraceToken( void ) const;

            const Token::Ptr& rightBraceToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Rules::Ptr m_rules;
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
        };

        class SequenceRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SequenceRule >;

            explicit SequenceRule(
                const Token::Ptr& leftBraceToken,
                const Rules::Ptr& rules,
                const Token::Ptr& rightBraceToken );

            const Rules::Ptr& rules( void ) const;

            const Token::Ptr& leftBraceToken( void ) const;

            const Token::Ptr& rightBraceToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Rules::Ptr m_rules;
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
        };

        class UpdateRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< UpdateRule >;

            UpdateRule(
                const DirectCallExpression::Ptr& function,
                const Token::Ptr& updateToken,
                const Expression::Ptr& expression );

            UpdateRule(
                const DirectCallExpression::Ptr& function, const Expression::Ptr& expression );

            const DirectCallExpression::Ptr& function( void ) const;
            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& updateToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const DirectCallExpression::Ptr m_function;
            const Expression::Ptr m_expression;
            const Token::Ptr m_updateToken;
        };

        using UpdateRules = NodeList< UpdateRule >;

        class CallRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< CallRule >;

            CallRule( const CallExpression::Ptr& call );

            const CallExpression::Ptr& call( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const CallExpression::Ptr m_call;
        };

        class WhileRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< WhileRule >;

            explicit WhileRule(
                const Token::Ptr& whileToken,
                const Expression::Ptr& condition,
                const Token::Ptr& doToken,
                const Rule::Ptr& rule );

            const Expression::Ptr& condition( void ) const;
            const Rule::Ptr& rule( void ) const;

            const Token::Ptr& whileToken( void ) const;

            const Token::Ptr& doToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_condition;
            const Rule::Ptr m_rule;
            const Token::Ptr m_whileToken;
            const Token::Ptr m_doToken;
        };
    }
}

#endif  // _LIBCASM_FE_RULE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
