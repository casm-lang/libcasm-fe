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

#ifndef _LIBCASM_FE_FRAME_H_
#define _LIBCASM_FE_FRAME_H_

#include <libcasm-fe/ast/Expression>

#include <libstdhl/SourceLocation>

namespace libcasm_fe
{
    class Frame
    {
        static std::size_t id;

      public:
        Frame( Ast::CallExpression* call, Ast::Node* callee, std::size_t numberOfLocals );

        Ast::CallExpression* call( void ) const;
        Ast::Node* callee( void ) const;

        void setLocal( std::size_t index, const libcasm_ir::Constant& local );
        const libcasm_ir::Constant& local( std::size_t index ) const;
        const std::vector< libcasm_ir::Constant >& locals( void ) const;

        std::size_t frameId() const;

      private:
        const std::size_t m_frameId;
        Ast::CallExpression* m_call;
        Ast::Node* m_callee;
        std::vector< libcasm_ir::Constant > m_locals;
    };

    class FrameStack
    {
      public:
        explicit FrameStack( void );

        void push( std::unique_ptr< Frame > frame );
        std::unique_ptr< Frame > pop( void );

        Frame* top( void ) const;

        std::vector< std::string > generateBacktrace(
            libstdhl::SourceLocation problemLocation, const libcasm_ir::Constant& agentId ) const;

      private:
        std::vector< std::unique_ptr< Frame > > m_frames;
    };
}

#endif  // _LIBCASM_FE_FRAME_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
