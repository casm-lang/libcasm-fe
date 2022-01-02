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

#ifndef _LIBCASM_FE_CST_VISITOR_H_
#define _LIBCASM_FE_CST_VISITOR_H_

namespace libcasm_fe
{
    namespace CST
    {
        class Root;

        class HeaderDefinition;
        class InitDefinition;
        class VariableDefinition;
        class FunctionDefinition;
        class DerivedDefinition;
        class RuleDefinition;
        class EnumeratorDefinition;
        class EnumerationDefinition;
        class UsingDefinition;
        class UsingPathDefinition;
        class InvariantDefinition;
        class ImportDefinition;
        class DomainDefinition;
        class StructureDefinition;
        class BehaviorDefinition;
        class ImplementDefinition;
        class BuiltinDefinition;
        class Declaration;

        class UndefLiteral;
        class ValueLiteral;
        class ReferenceLiteral;
        class SetLiteral;
        class ListLiteral;
        class RangeLiteral;
        class TupleLiteral;
        class RecordLiteral;

        class AbstractExpression;
        class EmbracedExpression;
        class NamedExpression;
        class MappedExpression;
        class DirectCallExpression;
        class MethodCallExpression;
        class LiteralCallExpression;
        class IndirectCallExpression;
        class TypeCastingExpression;
        class UnaryExpression;
        class BinaryExpression;
        class LetExpression;
        class ConditionalExpression;
        class ChooseExpression;
        class UniversalQuantifierExpression;
        class ExistentialQuantifierExpression;
        class CardinalityExpression;

        class SkipRule;
        class ConditionalRule;
        class CaseRule;
        class LetRule;
        class LocalRule;
        class ForallRule;
        class ChooseRule;
        class IterateRule;
        class BlockRule;
        class SequenceRule;
        class UpdateRule;
        class CallRule;
        class WhileRule;

        class UnresolvedType;
        class BasicType;
        class TupleType;
        class RecordType;
        class TemplateType;
        class FixedSizedType;
        class MappingType;
        class VaradicType;
        class RelationType;

        class BasicAttribute;
        class SymbolAttribute;
        class ExpressionAttribute;

        class Defined;
        class Initially;

        class Identifier;
        class IdentifierPath;
        class ExpressionCase;
        class DefaultCase;
        class VariableBinding;
        class Token;
        class Span;

        /**
         * @extends CasmFE
         */
        class Visitor
        {
          public:
            virtual ~Visitor( void ) = default;

            virtual void visit( Root& node ) = 0;

            virtual void visit( HeaderDefinition& node ) = 0;
            virtual void visit( InitDefinition& node ) = 0;
            virtual void visit( VariableDefinition& node ) = 0;
            virtual void visit( FunctionDefinition& node ) = 0;
            virtual void visit( DerivedDefinition& node ) = 0;
            virtual void visit( RuleDefinition& node ) = 0;
            virtual void visit( EnumeratorDefinition& node ) = 0;
            virtual void visit( EnumerationDefinition& node ) = 0;
            virtual void visit( UsingDefinition& node ) = 0;
            virtual void visit( UsingPathDefinition& node ) = 0;
            virtual void visit( InvariantDefinition& node ) = 0;
            virtual void visit( ImportDefinition& node ) = 0;
            virtual void visit( DomainDefinition& node ) = 0;
            virtual void visit( StructureDefinition& node ) = 0;
            virtual void visit( BehaviorDefinition& node ) = 0;
            virtual void visit( ImplementDefinition& node ) = 0;
            virtual void visit( BuiltinDefinition& node ) = 0;
            virtual void visit( Declaration& node ) = 0;

            virtual void visit( UndefLiteral& node ) = 0;
            virtual void visit( ValueLiteral& node ) = 0;
            virtual void visit( ReferenceLiteral& node ) = 0;
            virtual void visit( SetLiteral& node ) = 0;
            virtual void visit( ListLiteral& node ) = 0;
            virtual void visit( RangeLiteral& node ) = 0;
            virtual void visit( TupleLiteral& node ) = 0;
            virtual void visit( RecordLiteral& node ) = 0;

            virtual void visit( AbstractExpression& node ) = 0;
            virtual void visit( EmbracedExpression& node ) = 0;
            virtual void visit( NamedExpression& node ) = 0;
            virtual void visit( MappedExpression& node ) = 0;
            virtual void visit( DirectCallExpression& node ) = 0;
            virtual void visit( MethodCallExpression& node ) = 0;
            virtual void visit( LiteralCallExpression& node ) = 0;
            virtual void visit( IndirectCallExpression& node ) = 0;
            virtual void visit( TypeCastingExpression& node ) = 0;
            virtual void visit( UnaryExpression& node ) = 0;
            virtual void visit( BinaryExpression& node ) = 0;
            virtual void visit( LetExpression& node ) = 0;
            virtual void visit( ConditionalExpression& node ) = 0;
            virtual void visit( ChooseExpression& node ) = 0;
            virtual void visit( UniversalQuantifierExpression& node ) = 0;
            virtual void visit( ExistentialQuantifierExpression& node ) = 0;
            virtual void visit( CardinalityExpression& node ) = 0;

            virtual void visit( SkipRule& node ) = 0;
            virtual void visit( ConditionalRule& node ) = 0;
            virtual void visit( CaseRule& node ) = 0;
            virtual void visit( LetRule& node ) = 0;
            virtual void visit( LocalRule& node ) = 0;
            virtual void visit( ForallRule& node ) = 0;
            virtual void visit( ChooseRule& node ) = 0;
            virtual void visit( IterateRule& node ) = 0;
            virtual void visit( BlockRule& node ) = 0;
            virtual void visit( SequenceRule& node ) = 0;
            virtual void visit( UpdateRule& node ) = 0;
            virtual void visit( CallRule& node ) = 0;
            virtual void visit( WhileRule& node ) = 0;

            virtual void visit( UnresolvedType& node ) = 0;
            virtual void visit( BasicType& node ) = 0;
            virtual void visit( TupleType& node ) = 0;
            virtual void visit( RecordType& node ) = 0;
            virtual void visit( TemplateType& node ) = 0;
            virtual void visit( FixedSizedType& node ) = 0;
            virtual void visit( MappingType& node ) = 0;
            virtual void visit( VaradicType& node ) = 0;
            virtual void visit( RelationType& node ) = 0;

            virtual void visit( BasicAttribute& node ) = 0;
            virtual void visit( SymbolAttribute& node ) = 0;
            virtual void visit( ExpressionAttribute& node ) = 0;

            virtual void visit( Defined& node ) = 0;
            virtual void visit( Initially& node ) = 0;

            virtual void visit( Identifier& node ) = 0;
            virtual void visit( IdentifierPath& node ) = 0;
            virtual void visit( ExpressionCase& node ) = 0;
            virtual void visit( DefaultCase& node ) = 0;
            virtual void visit( VariableBinding& node ) = 0;
            virtual void visit( Token& node ) = 0;
            virtual void visit( Span& node ) = 0;
        };

        class RecursiveVisitor : public Visitor
        {
          public:
            void visit( Root& node ) override;

            void visit( HeaderDefinition& node ) override;
            void visit( InitDefinition& node ) override;
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
            void visit( DomainDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( Declaration& node ) override;

            void visit( UndefLiteral& node ) override;
            void visit( ValueLiteral& node ) override;
            void visit( ReferenceLiteral& node ) override;
            void visit( SetLiteral& node ) override;
            void visit( ListLiteral& node ) override;
            void visit( RangeLiteral& node ) override;
            void visit( TupleLiteral& node ) override;
            void visit( RecordLiteral& node ) override;

            void visit( AbstractExpression& node ) override;
            void visit( EmbracedExpression& node ) override;
            void visit( NamedExpression& node ) override;
            void visit( MappedExpression& node ) override;
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
            void visit( MappingType& node ) override;
            void visit( VaradicType& node ) override;
            void visit( RelationType& node ) override;

            void visit( BasicAttribute& node ) override;
            void visit( SymbolAttribute& node ) override;
            void visit( ExpressionAttribute& node ) override;

            void visit( Defined& node ) override;
            void visit( Initially& node ) override;

            void visit( Identifier& node ) override;
            void visit( IdentifierPath& node ) override;
            void visit( ExpressionCase& node ) override;
            void visit( DefaultCase& node ) override;
            void visit( VariableBinding& node ) override;
            void visit( Token& node ) override;
            void visit( Span& node ) override;
        };

        class EmptyVisitor : public Visitor
        {
          public:
            void visit( Root& node ) override;

            void visit( HeaderDefinition& node ) override;
            void visit( InitDefinition& node ) override;
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
            void visit( DomainDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( Declaration& node ) override;

            void visit( UndefLiteral& node ) override;
            void visit( ValueLiteral& node ) override;
            void visit( ReferenceLiteral& node ) override;
            void visit( SetLiteral& node ) override;
            void visit( ListLiteral& node ) override;
            void visit( RangeLiteral& node ) override;
            void visit( TupleLiteral& node ) override;
            void visit( RecordLiteral& node ) override;

            void visit( AbstractExpression& node ) override;
            void visit( EmbracedExpression& node ) override;
            void visit( NamedExpression& node ) override;
            void visit( MappedExpression& node ) override;
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
            void visit( MappingType& node ) override;
            void visit( VaradicType& node ) override;
            void visit( RelationType& node ) override;

            void visit( BasicAttribute& node ) override;
            void visit( SymbolAttribute& node ) override;
            void visit( ExpressionAttribute& node ) override;

            void visit( Defined& node ) override;
            void visit( Initially& node ) override;

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

#endif  // _LIBCASM_FE_CST_VISITOR_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
