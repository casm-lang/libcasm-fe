//
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
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

#ifndef _LIBCASM_FE_EMPTY_VISITOR_H_
#define _LIBCASM_FE_EMPTY_VISITOR_H_

#include <libcasm-fe/ast/Visitor>

namespace libcasm_fe
{
    namespace Ast
    {
        class EmptyVisitor : public Visitor
        {
          public:
            void visit( HeaderDefinition& node ) override;
            void visit( InitDefinition& node ) override;
            void visit( Initially& node ) override;
            void visit( Initializer& node ) override;
            void visit( VariableDefinition& node ) override;
            void visit( FunctionDefinition& node ) override;
            void visit( DerivedDefinition& node ) override;
            void visit( RuleDefinition& node ) override;
            void visit( EnumeratorDefinition& node ) override;
            void visit( EnumerationDefinition& node ) override;
            void visit( UsingDefinition& node ) override;
            void visit( UsingPathDefinition& node ) override;
            void visit( InvariantDefinition& node ) override;
            void visit( ImportDefinition& node ) override;

            void visit( UndefLiteral& node ) override;
            void visit( ValueLiteral& node ) override;
            void visit( ReferenceLiteral& node ) override;
            void visit( ListLiteral& node ) override;
            void visit( RangeLiteral& node ) override;
            void visit( TupleLiteral& node ) override;
            void visit( RecordLiteral& node ) override;

            void visit( EmbracedExpression& node ) override;
            void visit( NamedExpression& node ) override;
            void visit( DirectCallExpression& node ) override;
            void visit( MethodCallExpression& node ) override;
            void visit( LiteralCallExpression& node ) override;
            void visit( IndirectCallExpression& node ) override;
            void visit( TypeCastingExpression& node ) override;
            void visit( UnaryExpression& node ) override;
            void visit( BinaryExpression& node ) override;
            void visit( LetExpression& node ) override;
            void visit( ConditionalExpression& node ) override;
            void visit( ChooseExpression& node ) override;
            void visit( UniversalQuantifierExpression& node ) override;
            void visit( ExistentialQuantifierExpression& node ) override;
            void visit( CardinalityExpression& node ) override;

            void visit( SkipRule& node ) override;
            void visit( ConditionalRule& node ) override;
            void visit( CaseRule& node ) override;
            void visit( LetRule& node ) override;
            void visit( LocalRule& node ) override;
            void visit( ForallRule& node ) override;
            void visit( ChooseRule& node ) override;
            void visit( IterateRule& node ) override;
            void visit( BlockRule& node ) override;
            void visit( SequenceRule& node ) override;
            void visit( UpdateRule& node ) override;
            void visit( CallRule& node ) override;
            void visit( WhileRule& node ) override;

            void visit( UnresolvedType& node ) override;
            void visit( BasicType& node ) override;
            void visit( TupleType& node ) override;
            void visit( RecordType& node ) override;
            void visit( TemplateType& node ) override;
            void visit( FixedSizedType& node ) override;
            void visit( RelationType& node ) override;

            void visit( BasicAttribute& node ) override;
            void visit( ExpressionAttribute& node ) override;

            void visit( Defined& node ) override;

            void visit( Identifier& node ) override;
            void visit( IdentifierPath& node ) override;
            void visit( ExpressionCase& node ) override;
            void visit( DefaultCase& node ) override;
            void visit( VariableBinding& node ) override;
            void visit( Token& node ) override;
            void visit( Span& node ) override;
        };
    }
}

#endif  // _LIBCASM_FE_EMPTY_VISITOR_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
