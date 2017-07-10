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

#ifndef _LIB_CASMFE_RULE_H_
#define _LIB_CASMFE_RULE_H_

#include "Node.h"

#include "Expression.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class VariableDefinition;

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

            explicit SkipRule( void );

            void accept( Visitor& visitor ) override final;
        };

        class ConditionalRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ConditionalRule >;

            ConditionalRule( const Expression::Ptr& condition,
                const Rule::Ptr& thenRule, const Rule::Ptr& elseRule );
            ConditionalRule(
                const Expression::Ptr& condition, const Rule::Ptr& thenRule );

            Expression::Ptr condition( void ) const;
            Rule::Ptr thenRule( void ) const;
            Rule::Ptr elseRule( void ) const;

            void accept( Visitor& visitor ) override final;

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

            Rule::Ptr rule( void ) const;

          private:
            const Rule::Ptr m_rule;
        };

        using Cases = NodeList< Case >;

        class ExpressionCase final : public Case
        {
          public:
            using Ptr = std::shared_ptr< ExpressionCase >;

            ExpressionCase(
                const Expression::Ptr& expression, const Rule::Ptr& rule );

            Expression::Ptr expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_expression;
        };

        class DefaultCase final : public Case
        {
          public:
            using Ptr = std::shared_ptr< DefaultCase >;

            explicit DefaultCase( const Rule::Ptr& rule );

            void accept( Visitor& visitor ) override final;
        };

        class CaseRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< CaseRule >;

            CaseRule(
                const Expression::Ptr& expression, const Cases::Ptr& cases );

            Expression::Ptr expression( void ) const;
            Cases::Ptr cases( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_expression;
            const Cases::Ptr m_cases;
        };

        class LetRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< LetRule >;

            LetRule( const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& expression, const Rule::Ptr& rule );

            std::shared_ptr< VariableDefinition > variable( void ) const;
            Expression::Ptr expression( void ) const;
            Rule::Ptr rule( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinition > m_variable;
            const Expression::Ptr m_expression;
            const Rule::Ptr m_rule;
        };

        class ForallRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ForallRule >;

            ForallRule( const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& universe, const Rule::Ptr& rule );

            std::shared_ptr< VariableDefinition > variable( void ) const;
            Expression::Ptr universe( void ) const;
            Rule::Ptr rule( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinition > m_variable;
            const Expression::Ptr m_universe;
            const Rule::Ptr m_rule;
        };

        class ChooseRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ChooseRule >;

            ChooseRule( const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& universe, const Rule::Ptr& rule );

            std::shared_ptr< VariableDefinition > variable( void ) const;
            Expression::Ptr universe( void ) const;
            Rule::Ptr rule( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinition > m_variable;
            const Expression::Ptr m_universe;
            const Rule::Ptr m_rule;
        };

        class IterateRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< IterateRule >;

            explicit IterateRule( const Rule::Ptr& rule );

            Rule::Ptr rule( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Rule::Ptr m_rule;
        };

        class BlockRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< BlockRule >;

            explicit BlockRule( const Rules::Ptr& rules );

            Rules::Ptr rules( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Rules::Ptr m_rules;
        };

        class SequenceRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SequenceRule >;

            explicit SequenceRule( const Rules::Ptr& rules );

            Rules::Ptr rules( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Rules::Ptr m_rules;
        };

        class UpdateRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< UpdateRule >;

            UpdateRule( const DirectCallExpression::Ptr& function,
                const Expression::Ptr& expression );

            DirectCallExpression::Ptr function( void ) const;
            Expression::Ptr expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const DirectCallExpression::Ptr m_function;
            const Expression::Ptr m_expression;
        };

        class CallRule final : public Rule
        {
          public:
            using Ptr = std::shared_ptr< CallRule >;

            CallRule( const CallExpression::Ptr& call,
                const std::set< CallExpression::TargetType >&
                    allowedCallTargetTypes );

            CallExpression::Ptr call( void ) const;
            const std::set< CallExpression::TargetType >&
            allowedCallTargetTypes( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const CallExpression::Ptr m_call;
            const std::set< CallExpression::TargetType > m_allowedCallTargetTypes;
        };
    }
}

#endif // _LIB_CASMFE_RULE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
