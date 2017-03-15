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

#ifndef _LIB_CASMFE_ASTDUMPPASS_H_
#define _LIB_CASMFE_ASTDUMPPASS_H_

#include <ostream>

#include "libpass.h"

#include "../ast/RecursiveVisitor.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_fe
{
    namespace Ast
    {
        class Node;
    }

    class AstDumpPass final : public libpass::Pass
    {
      public:
        static char id;

        bool run( libpass::PassResult& pr ) override;
    };

    class AstDumpVisitor final : public Ast::RecursiveVisitor
    {
      public:
        AstDumpVisitor( std::ostream& stream );

        void visit( Ast::IdentifierNode& node ) override;

        void visit( Ast::Specification& node ) override;

        void visit( Ast::VariableDefinition& node ) override;
        void visit( Ast::FunctionDefinition& node ) override;
        void visit( Ast::DerivedDefinition& node ) override;
        void visit( Ast::RuleDefinition& node ) override;
        void visit( Ast::EnumerationDefinition& node ) override;

        void visit( Ast::ValueAtom& node ) override;
        void visit( Ast::RuleReferenceAtom& node ) override;
        void visit( Ast::ZeroAtom& node ) override;
        void visit( Ast::UndefAtom& node ) override;
        void visit( Ast::DirectCallExpression& node ) override;
        void visit( Ast::IndirectCallExpression& node ) override;
        void visit( Ast::UnaryExpression& node ) override;
        void visit( Ast::BinaryExpression& node ) override;
        void visit( Ast::RangeExpression& node ) override;
        void visit( Ast::ListExpression& node ) override;
        void visit( Ast::ConditionalExpression& node ) override;
        void visit( Ast::UniversalQuantifierExpression& node ) override;
        void visit( Ast::ExistentialQuantifierExpression& node ) override;

        void visit( Ast::SkipRule& node ) override;
        void visit( Ast::ConditionalRule& node ) override;
        void visit( Ast::CaseRule& node ) override;
        void visit( Ast::LetRule& node ) override;
        void visit( Ast::ForallRule& node ) override;
        void visit( Ast::IterateRule& node ) override;
        void visit( Ast::BlockRule& node ) override;
        void visit( Ast::SequenceRule& node ) override;
        void visit( Ast::UpdateRule& node ) override;
        void visit( Ast::CallRule& node ) override;

        void visit( Ast::BasicType& node ) override;
        void visit( Ast::ComposedType& node ) override;
        void visit( Ast::FixedSizedType& node ) override;
        void visit( Ast::RangedType& node ) override;

      private:
        void dumpNode( const Ast::Node& node, const std::string& name );
        void dumpLink( const Ast::Node& from, const Ast::Node& to );

      private:
        std::ostream& m_stream;
    };
}

#endif /* _LIB_CASMFE_ASTDUMPPASS_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
