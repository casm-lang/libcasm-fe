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

#ifndef _LIBCASM_FE_SYMBOL_RESOLVER_PASS_H_
#define _LIBCASM_FE_SYMBOL_RESOLVER_PASS_H_

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libpass/Pass>

namespace libcasm_fe
{
    /**
     * @brief Resolves AST identifiers of type-, call-, ... nodes
     */
    class SymbolResolverPass final : public libpass::Pass
    {
      public:
        static char id;

        void usage( libpass::PassUsage& pu ) override;

        bool run( libpass::PassResult& pr ) override;
    };

    class SymbolResolveVisitor final : public Ast::RecursiveVisitor
    {
      public:
        SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

        void visit( Ast::InitDefinition& node ) override;

        void visit( Ast::FunctionDefinition& node ) override;
        void visit( Ast::DerivedDefinition& node ) override;
        void visit( Ast::RuleDefinition& node ) override;
        void visit( Ast::EnumerationDefinition& node ) override;
        void visit( Ast::StructureDefinition& node ) override;
        void visit( Ast::BehaviorDefinition& node ) override;
        void visit( Ast::ImplementDefinition& node ) override;
        void visit( Ast::BuiltinDefinition& node ) override;
        void visit( Ast::DomainDefinition& node ) override;
        void visit( Ast::UsingDefinition& node ) override;
        void visit( Ast::Declaration& node ) override;

        void visit( Ast::ReferenceLiteral& node ) override;

        void visit( Ast::DirectCallExpression& node ) override;
        void visit( Ast::LiteralCallExpression& node ) override;
        void visit( Ast::LetExpression& node ) override;
        void visit( Ast::ChooseExpression& node ) override;
        void visit( Ast::UniversalQuantifierExpression& node ) override;
        void visit( Ast::ExistentialQuantifierExpression& node ) override;

        void visit( Ast::LetRule& node ) override;
        void visit( Ast::LocalRule& node ) override;
        void visit( Ast::ForallRule& node ) override;
        void visit( Ast::ChooseRule& node ) override;

        void visit( Ast::BasicType& node ) override;
        void visit( Ast::TupleType& node ) override;
        void visit( Ast::RecordType& node ) override;
        void visit( Ast::FixedSizedType& node ) override;
        void visit( Ast::RelationType& node ) override;
        void visit( Ast::TemplateType& node ) override;

      private:
        void pushSymbol( const Ast::Definition::Ptr& symbol );
        void popSymbol( const Ast::Definition::Ptr& symbol );

        template < typename T >
        void pushSymbols( const typename Ast::NodeList< T >::Ptr& symbols )
        {
            for( const auto& symbol : *symbols )
            {
                pushSymbol( symbol );
            }
        }

        template < typename T >
        void popSymbols( const typename Ast::NodeList< T >::Ptr& symbols )
        {
            for( const auto& symbol : *symbols )
            {
                popSymbol( symbol );
            }
        }

        void pushVariableBindings( const Ast::VariableBindings::Ptr& variableBindings );
        void popVariableBindings( const Ast::VariableBindings::Ptr& variableBindings );

        /**
         * If the \a definition is a type alias, it will be resolved and the aliased
         * definition will be returned. Otherwise the given \a definition will be
         * returned.
         */
        Ast::Definition::Ptr resolveIfAlias( const Ast::Definition::Ptr& definition ) const;

        Ast::Definition::Ptr tryResolveSymbol( const Ast::IdentifierPath& identifierPath ) const;

        Ast::Definition::Ptr resolveSymbol( const Ast::Definition& node ) const;

        void resolveBehaviorInstance( Ast::Type& node );

        void resolveTypeInstance( Ast::Type& node );

        Ast::Definition::Ptr resolveBuiltinCall(
            Ast::TargetCallExpression& node, const Ast::BuiltinDefinition::Ptr& builtinDefinition );

      private:
        libcasm_fe::Logger& m_log;
        Namespace& m_symboltable;

        std::unordered_map< std::string, Ast::Definition::Ptr > m_scopeSymbols;
        Ast::TypeDefinition::Ptr m_objectDefinition;
        Ast::TypeDefinition::Ptr m_behaviorDefinition;
        Ast::DomainDefinition::Ptr m_agentDomainDefinition;
    };

    class ReplaceTypeVisitor final : public Ast::RecursiveVisitor
    {
      public:
        ReplaceTypeVisitor(
            libcasm_fe::Logger& log, const Ast::Type::Ptr& from, const Ast::Type::Ptr& to );

        void visit( Ast::DomainDefinition& node ) override;
        void visit( Ast::RuleDefinition& node ) override;
        void visit( Ast::DerivedDefinition& node ) override;
        void visit( Ast::Declaration& node ) override;
        void visit( Ast::BuiltinDefinition& node ) override;
        void visit( Ast::ImplementDefinition& node ) override;
        void visit( Ast::VariableDefinition& node ) override;

        void visit( Ast::TemplateType& node ) override;

      private:
        libcasm_fe::Logger& m_log;
        const Ast::Type::Ptr& m_from;
        const Ast::Type::Ptr& m_to;
    };
}

#endif  // _LIBCASM_FE_SYMBOL_RESOLVER_PASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
