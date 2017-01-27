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

#pragma once

#include "Expression.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class Rule : public Node
        {
          public:
            using Ptr = std::shared_ptr< Rule >;

            using Node::Node;
        };

        using Rules = NodeList< Rule >;

        class PrintRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< PrintRule >;

            PrintRule( const Expression::Ptr& expression );

            Expression::Ptr expression() const;

            void setFilter( const std::string& filter );
            std::string filter() const;

          private:
            Expression::Ptr m_expression;
            std::string m_filter;
        };

        class AssertRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< AssertRule >;

            AssertRule( const Expression::Ptr& expression );

            Expression::Ptr expression() const;

          private:
            Expression::Ptr m_expression;
        };

        class AssureRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< AssureRule >;

            AssureRule( const Expression::Ptr& expression );

            Expression::Ptr expression() const;

          private:
            Expression::Ptr m_expression;
        };

        class SkipRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SkipRule >;

            SkipRule();
        };

        class DieDieRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< DieDieRule >;

            DieDieRule( const Expression::Ptr& expression );

            Expression::Ptr expression() const;

          private:
            Expression::Ptr m_expression;
        };

        class ConditionalRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ConditionalRule >;

            ConditionalRule( const Expression::Ptr& condition,
                const Rule::Ptr& thenRule, const Rule::Ptr& elseRule );
            ConditionalRule(
                const Expression::Ptr& condition, const Rule::Ptr& thenRule );

            Expression::Ptr condition() const;
            Rule::Ptr thenRule() const;
            Rule::Ptr elseRule() const;

          private:
            Expression::Ptr m_condition;
            Rule::Ptr m_thenRule;
            Rule::Ptr m_elseRule;
        };

        class Variable // TODO move it to the correct place
        {
          public:
            using Ptr = std::shared_ptr< Variable >;

            Variable( const std::string& identifier, libcasm_ir::Type* type );

            std::string identifier() const;
            libcasm_ir::Type* type() const;

          private:
            std::string m_identifier;
            libcasm_ir::Type* m_type;
        };

        class LetRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< LetRule >;

            LetRule( const Variable::Ptr& variable,
                const Expression::Ptr& expression, const Rule::Ptr& rule );

            Variable::Ptr variable() const;
            Expression::Ptr expression() const;
            Rule::Ptr rule() const;

          private:
            Variable::Ptr m_variable;
            Expression::Ptr m_expression;
            Rule::Ptr m_rule;
        };

        class ForallRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< ForallRule >;

            ForallRule( const Variable::Ptr& variable,
                const Expression::Ptr& expression, const Rule::Ptr& rule );

            Variable::Ptr variable() const;
            Expression::Ptr expression() const;
            Rule::Ptr rule() const;

          private:
            Variable::Ptr m_variable;
            Expression::Ptr m_expression;
            Rule::Ptr m_rule;
        };

        class IterateRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< IterateRule >;

            IterateRule( const Rule::Ptr& rule );

            Rule::Ptr rule() const;

          private:
            Rule::Ptr m_rule;
        };

        class BlockRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< BlockRule >;

            BlockRule( const Rules::Ptr& rules );

            Rules::Ptr rules() const;

          private:
            Rules::Ptr m_rules;
        };

        class SequenceRule : public Rule
        {
          public:
            using Ptr = std::shared_ptr< SequenceRule >;

            SequenceRule( const Rules::Ptr& rules );

            Rules::Ptr rules() const;

          private:
            Rules::Ptr m_rules;
        };

        // TODO add PushRule
        // TODO add PopRule
        // TODO add CallRule
        // TODO add CaseRule
        // TODO add UpdateRule
        // TODO add ImpossibleRule
    }
}
