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

        class SkipRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SkipRule >;

            SkipRule( void );
        };

        class ConditionalRule : public Rule
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

          private:
            Expression::Ptr m_condition;
            Rule::Ptr m_thenRule;
            Rule::Ptr m_elseRule;
        };

        class CaseRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< CaseRule >;
            using Case = std::pair< Expression::Ptr, Rule::Ptr >;

            CaseRule( const Expression::Ptr& expression,
                const std::vector< Case >& cases );

            Expression::Ptr expression( void ) const;
            std::vector< Case > cases( void ) const;

          private:
            Expression::Ptr m_expression;
            std::vector< Case > m_cases;
        };

        class LetRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< LetRule >;

            LetRule( const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& expression, const Rule::Ptr& rule );

            std::shared_ptr< VariableDefinition > variable( void ) const;
            Expression::Ptr expression( void ) const;
            Rule::Ptr rule( void ) const;

          private:
            std::shared_ptr< VariableDefinition > m_variable;
            Expression::Ptr m_expression;
            Rule::Ptr m_rule;
        };

        class ForallRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ForallRule >;

            ForallRule( const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& expression, const Rule::Ptr& rule );

            std::shared_ptr< VariableDefinition > variable( void ) const;
            Expression::Ptr expression( void ) const;
            Rule::Ptr rule( void ) const;

          private:
            std::shared_ptr< VariableDefinition > m_variable;
            Expression::Ptr m_expression;
            Rule::Ptr m_rule;
        };

        class IterateRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< IterateRule >;

            IterateRule( const Rule::Ptr& rule );

            Rule::Ptr rule( void ) const;

          private:
            Rule::Ptr m_rule;
        };

        class BlockRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< BlockRule >;

            BlockRule( const Rules::Ptr& rules );

            Rules::Ptr rules( void ) const;

          private:
            Rules::Ptr m_rules;
        };

        class SequenceRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SequenceRule >;

            SequenceRule( const Rules::Ptr& rules );

            Rules::Ptr rules( void ) const;

          private:
            Rules::Ptr m_rules;
        };

        class UpdateRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< UpdateRule >;

            UpdateRule( const DirectCallExpression::Ptr& function,
                const Expression::Ptr& expression );

            DirectCallExpression::Ptr function( void ) const;
            Expression::Ptr expression( void ) const;

          private:
            DirectCallExpression::Ptr m_function;
            Expression::Ptr m_expression;
        };

        class CallRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< CallRule >;

            CallRule( const CallExpression::Ptr& call,
                const std::set< CallExpression::TargetType >&
                    allowedCallTargetTypes );

            CallExpression::Ptr call( void ) const;
            std::set< CallExpression::TargetType > allowedCallTargetTypes(
                void ) const;

          private:
            CallExpression::Ptr m_call;
            std::set< CallExpression::TargetType > m_allowedCallTargetTypes;
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