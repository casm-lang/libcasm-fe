//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include "AstDumpSourcePass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/ConsistencyCheckPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <iostream>

using namespace libcasm_fe;
using namespace Ast;

namespace ir = libcasm_ir;

char AstDumpSourcePass::id = 0;

static libpass::PassRegistration< AstDumpSourcePass > PASS(
    "AstDumpSourcePass",
    "outputs the parsed AST as a CASM input specification to stdout",
    "ast-dump",
    0 );

class Indentation
{
  public:
    class NextLevel
    {
      public:
        explicit NextLevel( Indentation& indentation )
        : m_indentation( indentation )
        {
            m_indentation.increase();
        }

        ~NextLevel()
        {
            m_indentation.decrease();
        }

      private:
        Indentation& m_indentation;
    };

    class PreviousLevel
    {
      public:
        explicit PreviousLevel( Indentation& indentation )
        : m_indentation( indentation )
        {
            m_indentation.decrease();
        }

        ~PreviousLevel()
        {
            m_indentation.increase();
        }

      private:
        Indentation& m_indentation;
    };

  public:
    explicit Indentation( std::size_t stepSize )
    : m_stepSize( stepSize )
    , m_length( 0 )
    {
    }

    void increase()
    {
        m_length += m_stepSize;
    }

    void decrease()
    {
        assert( m_length >= m_stepSize );
        m_length -= m_stepSize;
    }

    std::size_t length() const
    {
        return m_length;
    }

  private:
    const std::size_t m_stepSize;
    std::size_t m_length;
};

std::ostream& operator<<( std::ostream& stream, const Indentation& indentation )
{
    stream << std::string( indentation.length(), ' ' );
    return stream;
}

class AstDumpSourceVisitor final : public Visitor
{
  public:
    explicit AstDumpSourceVisitor( std::ostream& stream );

    void visit( HeaderDefinition& node ) override;
    void visit( VariableDefinition& node ) override;
    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumeratorDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;
    void visit( UsingDefinition& node ) override;
    void visit( InvariantDefinition& node ) override;

    void visit( UndefLiteral& node ) override;
    void visit( ValueLiteral& node ) override;
    void visit( ReferenceLiteral& node ) override;
    void visit( ListLiteral& node ) override;
    void visit( RangeLiteral& node ) override;
    void visit( TupleLiteral& node ) override;
    void visit( RecordLiteral& node ) override;

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
    void visit( ComposedType& node ) override;
    void visit( TemplateType& node ) override;
    void visit( FixedSizedType& node ) override;
    void visit( RelationType& node ) override;

    void visit( BasicAttribute& node ) override;
    void visit( ExpressionAttribute& node ) override;

    void visit( Identifier& node ) override;
    void visit( IdentifierPath& node ) override;
    void visit( ExpressionCase& node ) override;
    void visit( DefaultCase& node ) override;
    void visit( VariableBinding& node ) override;

  private:
    void dumpAttributes( Attributes& attributes );

    template < typename T >
    void dumpNodes( NodeList< T >& nodes, const std::string& separator )
    {
        bool firstNode = true;
        for( const auto& node : nodes )
        {
            if( not firstNode )
            {
                m_stream << separator;
            }
            node->accept( *this );
            firstNode = false;
        }
    }

  private:
    std::ostream& m_stream;
    Indentation m_indentation;
};

AstDumpSourceVisitor::AstDumpSourceVisitor( std::ostream& stream )
: m_stream( stream )
, m_indentation( 4 )
{
}

void AstDumpSourceVisitor::visit( HeaderDefinition& node )
{
    dumpAttributes( *node.attributes() );
    m_stream << " ";
    node.identifier()->accept( *this );
}

void AstDumpSourceVisitor::visit( VariableDefinition& node )
{
    dumpAttributes( *node.attributes() );
    m_stream << " ";
    node.identifier()->accept( *this );
    m_stream << " : ";
    node.variableType()->accept( *this );
}

void AstDumpSourceVisitor::visit( FunctionDefinition& node )
{
    m_stream << m_indentation;
    dumpAttributes( *node.attributes() );
    m_stream << "\n" << m_indentation << "function ";
    node.identifier()->accept( *this );
    m_stream << " : ";
    dumpNodes( *node.argumentTypes(), " * " );
    m_stream << " -> ";
    node.returnType()->accept( *this );

    m_stream << " default { ";
    node.defaultValue()->accept( *this );

    m_stream << " } initially {\n";
    {
        const Indentation::NextLevel level( m_indentation );
        dumpNodes( *node.initializers(), ",\n" );
    }
    m_stream << "\n" << m_indentation << "}";
}

void AstDumpSourceVisitor::visit( DerivedDefinition& node )
{
    m_stream << m_indentation;
    dumpAttributes( *node.attributes() );
    m_stream << "\n" << m_indentation << "derived ";
    node.identifier()->accept( *this );
    m_stream << "(";
    dumpNodes( *node.arguments(), ", " );
    m_stream << ") -> ";
    node.returnType()->accept( *this );
    m_stream << " =\n" << m_indentation;

    const Indentation::NextLevel level( m_indentation );
    m_stream << m_indentation;
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( RuleDefinition& node )
{
    m_stream << m_indentation;
    dumpAttributes( *node.attributes() );
    m_stream << "\n" << m_indentation << "rule ";
    node.identifier()->accept( *this );
    m_stream << "(";
    dumpNodes( *node.arguments(), ", " );
    m_stream << ") -> ";
    node.returnType()->accept( *this );
    m_stream << " =\n";

    const Indentation::NextLevel level( m_indentation );
    node.rule()->accept( *this );
}

void AstDumpSourceVisitor::visit( EnumeratorDefinition& node )
{
    dumpAttributes( *node.attributes() );
    node.identifier()->accept( *this );
}

void AstDumpSourceVisitor::visit( EnumerationDefinition& node )
{
    m_stream << m_indentation;
    dumpAttributes( *node.attributes() );
    m_stream << "\n" << m_indentation << "enum ";
    node.identifier()->accept( *this );
    m_stream << " = {";
    dumpNodes( *node.enumerators(), ", " );
    m_stream << "}";
}

void AstDumpSourceVisitor::visit( UsingDefinition& node )
{
    m_stream << m_indentation;
    dumpAttributes( *node.attributes() );
    m_stream << "\n" << m_indentation << "using ";
    node.identifier()->accept( *this );
    m_stream << " = ";
    node.type()->accept( *this );
}

void AstDumpSourceVisitor::visit( InvariantDefinition& node )
{
    m_stream << m_indentation;
    dumpAttributes( *node.attributes() );
    m_stream << "\n" << m_indentation << "invariant ";
    node.identifier()->accept( *this );
    m_stream << " =\n" << m_indentation;

    const Indentation::NextLevel level( m_indentation );
    m_stream << m_indentation;
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( UndefLiteral& node )
{
    m_stream << "undef";
}

void AstDumpSourceVisitor::visit( ValueLiteral& node )
{
    m_stream << node.value()->name();
}

void AstDumpSourceVisitor::visit( ReferenceLiteral& node )
{
    m_stream << "@";
    node.identifier()->accept( *this );
}

void AstDumpSourceVisitor::visit( ListLiteral& node )
{
    m_stream << "[";
    dumpNodes( *node.expressions(), ", " );
    m_stream << "]";
}

void AstDumpSourceVisitor::visit( RangeLiteral& node )
{
    m_stream << "[";
    node.left()->accept( *this );
    m_stream << "..";
    node.right()->accept( *this );
    m_stream << "]";
}

void AstDumpSourceVisitor::visit( TupleLiteral& node )
{
    m_stream << "(";
    dumpNodes( *node.expressions(), ", " );
    m_stream << ")";
}

void AstDumpSourceVisitor::visit( RecordLiteral& node )
{
    m_stream << "(";
    dumpNodes( *node.namedExpressions(), ", " );
    m_stream << ")";
}

void AstDumpSourceVisitor::visit( NamedExpression& node )
{
    node.identifier()->accept( *this );
    m_stream << " : ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( DirectCallExpression& node )
{
    node.identifier()->accept( *this );

    if( not node.arguments()->empty() )
    {
        m_stream << "(";
        dumpNodes( *node.arguments(), ", " );
        m_stream << ")";
    }
}

void AstDumpSourceVisitor::visit( MethodCallExpression& node )
{
    node.object()->accept( *this );
    m_stream << ".";
    node.methodName()->accept( *this );

    if( not node.arguments()->empty() )
    {
        m_stream << "(";
        dumpNodes( *node.arguments(), ", " );
        m_stream << ")";
    }
}

void AstDumpSourceVisitor::visit( LiteralCallExpression& node )
{
    node.object()->accept( *this );
    m_stream << ".";
    node.literal()->accept( *this );
}

void AstDumpSourceVisitor::visit( IndirectCallExpression& node )
{
    m_stream << "(*";
    node.expression()->accept( *this );
    m_stream << ")(";
    dumpNodes( *node.arguments(), ", " );
    m_stream << ")";
}

void AstDumpSourceVisitor::visit( TypeCastingExpression& node )
{
    node.fromExpression()->accept( *this );
    m_stream << " as ";
    node.asType()->accept( *this );
}

void AstDumpSourceVisitor::visit( UnaryExpression& node )
{
    m_stream << ir::Value::token( node.op() );
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( BinaryExpression& node )
{
    m_stream << "(";
    node.left()->accept( *this );
    m_stream << " " << ir::Value::token( node.op() ) << " ";
    node.right()->accept( *this );
    m_stream << ")";
}

void AstDumpSourceVisitor::visit( LetExpression& node )
{
    m_stream << "let ";
    dumpNodes( *node.variableBindings(), ", " );
    m_stream << " in ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( ConditionalExpression& node )
{
    m_stream << "if ";
    node.condition()->accept( *this );
    m_stream << " then ";
    node.thenExpression()->accept( *this );
    m_stream << " else ";
    node.elseExpression()->accept( *this );
}

void AstDumpSourceVisitor::visit( ChooseExpression& node )
{
    m_stream << "choose ";
    dumpNodes( *node.variables(), ", " );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " do ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( UniversalQuantifierExpression& node )
{
    m_stream << "forall ";
    dumpNodes( *node.predicateVariables(), ", " );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " holds ";
    node.proposition()->accept( *this );
}

void AstDumpSourceVisitor::visit( ExistentialQuantifierExpression& node )
{
    m_stream << "exists ";
    dumpNodes( *node.predicateVariables(), ", " );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " with ";
    node.proposition()->accept( *this );
}

void AstDumpSourceVisitor::visit( CardinalityExpression& node )
{
    m_stream << "| ";
    node.expression()->accept( *this );
    m_stream << " |";
}

void AstDumpSourceVisitor::visit( SkipRule& node )
{
    m_stream << m_indentation << "skip";
}

void AstDumpSourceVisitor::visit( ConditionalRule& node )
{
    m_stream << m_indentation << "if ";
    node.condition()->accept( *this );

    m_stream << " then\n";
    {
        const Indentation::NextLevel level( m_indentation );
        node.thenRule()->accept( *this );
    }

    m_stream << "\n" << m_indentation << "else\n";
    {
        const Indentation::NextLevel level( m_indentation );
        node.elseRule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( CaseRule& node )
{
    m_stream << m_indentation << "case ";
    node.expression()->accept( *this );
    m_stream << " of\n" << m_indentation << "{\n";
    {
        const Indentation::NextLevel level( m_indentation );
        dumpNodes( *node.cases(), "\n" );
    }
    m_stream << "\n" << m_indentation << "}";
}

void AstDumpSourceVisitor::visit( LetRule& node )
{
    m_stream << m_indentation << "let ";
    dumpNodes( *node.variableBindings(), ", " );
    m_stream << " in\n";
    {
        const Indentation::NextLevel level( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( ForallRule& node )
{
    m_stream << m_indentation << "forall ";
    dumpNodes( *node.variables(), ", " );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " with ";
    node.condition()->accept( *this );
    m_stream << " do\n";
    {
        const Indentation::NextLevel level( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( ChooseRule& node )
{
    m_stream << m_indentation << "choose ";
    dumpNodes( *node.variables(), ", " );
    m_stream << " in ";
    node.universe()->accept( *this );
    m_stream << " do\n";
    {
        const Indentation::NextLevel level( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( IterateRule& node )
{
    m_stream << "iterate\n";
    {
        const Indentation::NextLevel level( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( BlockRule& node )
{
    {
        const Indentation::PreviousLevel level( m_indentation );
        m_stream << m_indentation << "{\n";
    }

    dumpNodes( *node.rules(), "\n" );

    {
        const Indentation::PreviousLevel level( m_indentation );
        m_stream << "\n" << m_indentation << "}";
    }
}

void AstDumpSourceVisitor::visit( SequenceRule& node )
{
    {
        const Indentation::PreviousLevel level( m_indentation );
        m_stream << m_indentation << "{|\n";
    }

    dumpNodes( *node.rules(), "\n" );

    {
        const Indentation::PreviousLevel level( m_indentation );
        m_stream << "\n" << m_indentation << "|}";
    }
}

void AstDumpSourceVisitor::visit( UpdateRule& node )
{
    m_stream << m_indentation;
    node.function()->accept( *this );
    m_stream << " := ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( CallRule& node )
{
    m_stream << m_indentation << "call ";
    node.call()->accept( *this );
}

void AstDumpSourceVisitor::visit( WhileRule& node )
{
    m_stream << m_indentation << "while ";
    node.condition()->accept( *this );
    m_stream << " do\n";
    {
        const Indentation::NextLevel level( m_indentation );
        node.rule()->accept( *this );
    }
}

void AstDumpSourceVisitor::visit( UnresolvedType& node )
{
    node.name()->accept( *this );
}

void AstDumpSourceVisitor::visit( BasicType& node )
{
    node.name()->accept( *this );
}

void AstDumpSourceVisitor::visit( ComposedType& node )
{
    m_stream << "(";
    if( not node.isNamed() )
    {
        dumpNodes( *node.subTypes(), ", " );
    }
    else
    {
        u1 firstNode = true;
        for( std::size_t index = 0; index < node.subTypes()->size(); index++ )
        {
            if( not firstNode )
            {
                m_stream << ", ";
            }
            ( *node.subTypeIdentifiers() )[ index ]->accept( *this );
            m_stream << " : ";
            ( *node.subTypes() )[ index ]->accept( *this );
            firstNode = false;
        }
    }
    m_stream << ")";
}

void AstDumpSourceVisitor::visit( TemplateType& node )
{
    node.name()->accept( *this );
    m_stream << "<";
    dumpNodes( *node.subTypes(), ", " );
    m_stream << ">";
}

void AstDumpSourceVisitor::visit( FixedSizedType& node )
{
    node.name()->accept( *this );
    m_stream << "<";
    node.size()->accept( *this );
    m_stream << ">";
}

void AstDumpSourceVisitor::visit( RelationType& node )
{
    m_stream << "<";
    dumpNodes( *node.argumentTypes(), " * " );
    m_stream << " -> ";
    node.returnType()->accept( *this );
    m_stream << ">";
}

void AstDumpSourceVisitor::visit( BasicAttribute& node )
{
    node.identifier()->accept( *this );
}

void AstDumpSourceVisitor::visit( ExpressionAttribute& node )
{
    node.identifier()->accept( *this );
    m_stream << " ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::visit( Identifier& node )
{
    m_stream << node.name();
}

void AstDumpSourceVisitor::visit( IdentifierPath& node )
{
    m_stream << node.path();
}

void AstDumpSourceVisitor::visit( ExpressionCase& node )
{
    m_stream << m_indentation;
    node.expression()->accept( *this );
    m_stream << ":\n";

    const Indentation::NextLevel level( m_indentation );
    node.rule()->accept( *this );
}

void AstDumpSourceVisitor::visit( DefaultCase& node )
{
    m_stream << m_indentation << "default:\n";

    const Indentation::NextLevel level( m_indentation );
    node.rule()->accept( *this );
}

void AstDumpSourceVisitor::visit( VariableBinding& node )
{
    node.variable()->accept( *this );
    m_stream << " = ";
    node.expression()->accept( *this );
}

void AstDumpSourceVisitor::dumpAttributes( Attributes& attributes )
{
    if( not attributes.empty() )
    {
        m_stream << "[";
        dumpNodes( attributes, ", " );
        m_stream << "]";
    }
}

void AstDumpSourcePass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< ConsistencyCheckPass >();
}

u1 AstDumpSourcePass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto& data = pr.output< SourceToAstPass >();
    const auto& specification = data->specification();

    auto& outputStream = std::cout;

    AstDumpSourceVisitor visitor{ outputStream };

    for( const auto& definition : *specification->definitions() )
    {
        outputStream << "\n";
        definition->accept( visitor );
        outputStream << "\n";
    }

    return true;
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
