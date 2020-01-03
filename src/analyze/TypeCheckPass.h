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

#ifndef _LIBCASM_FE_TYPE_CHECK_PASS_H_
#define _LIBCASM_FE_TYPE_CHECK_PASS_H_

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libpass/Pass>

namespace libcasm_fe
{
    /**
     * @brief Type check pass of AST
     */
    class TypeCheckPass final : public libpass::Pass
    {
      public:
        static char id;

        void usage( libpass::PassUsage& pu ) override;

        bool run( libpass::PassResult& pr ) override;
    };

    class TypeCheckVisitor final : public Ast::RecursiveVisitor
    {
      public:
        TypeCheckVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

        void visit( Ast::DerivedDefinition& node ) override;
        void visit( Ast::FunctionDefinition& node ) override;
        void visit( Ast::RuleDefinition& node ) override;
        void visit( Ast::EnumerationDefinition& node ) override;
        void visit( Ast::DomainDefinition& node ) override;
        void visit( Ast::BuiltinDefinition& node ) override;
        void visit( Ast::UsingDefinition& node ) override;
        void visit( Ast::StructureDefinition& node ) override;
        void visit( Ast::BehaviorDefinition& node ) override;
        void visit( Ast::ImplementDefinition& node ) override;
        void visit( Ast::VariableDefinition& node ) override;
        void visit( Ast::Declaration& node ) override;

        void visit( Ast::DirectCallExpression& node ) override;

        void visit( Ast::BasicType& node ) override;
        void visit( Ast::TupleType& node ) override;
        void visit( Ast::RecordType& node ) override;
        void visit( Ast::FixedSizedType& node ) override;
        void visit( Ast::RelationType& node ) override;
        void visit( Ast::TemplateType& node ) override;

      private:
        void resolveRelationType(
            Ast::Definition& node, Ast::VariableDefinitions& argumentTypes, Ast::Type& returnType );
        void resolveRelationType(
            Ast::Definition& node, Ast::Types& argumentTypes, Ast::Type& returnType );

        void pushSymbol( const Ast::VariableDefinition::Ptr& symbol );
        void pushSymbols( const Ast::VariableDefinitions::Ptr& symbols );
        void popSymbol( const Ast::VariableDefinition::Ptr& symbol );
        void popSymbols( const Ast::VariableDefinitions::Ptr& symbols );

        void pushVariableBindings( const Ast::VariableBindings::Ptr& variableBindings );
        void popVariableBindings( const Ast::VariableBindings::Ptr& variableBindings );

        libcasm_fe::Logger& m_log;
        Namespace& m_symboltable;

        std::unordered_map< std::string, Ast::VariableDefinition::Ptr > m_symbols;
    };
}

#endif  // _LIBCASM_FE_TYPE_CHECK_PASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
