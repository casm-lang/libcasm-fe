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

#ifndef _LIB_CASMFE_FRAME_H_
#define _LIB_CASMFE_FRAME_H_

#include "../ast/Expression.h"

namespace libcasm_fe
{
    class Frame
    {
      public:
        Frame( Ast::CallExpression* call, Ast::Node* callee,
               std::size_t numberOfLocals );

        Ast::CallExpression* call( void ) const;
        Ast::Node* callee( void ) const;

        void setLocal( std::size_t index, const libcasm_ir::Constant& local );
        const libcasm_ir::Constant& local( std::size_t index ) const;
        const std::vector< libcasm_ir::Constant >& locals( void ) const;

      private:
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
            SourceLocation problemLocation,
            const libcasm_ir::Constant& agentId ) const;

      private:
        std::vector< std::unique_ptr< Frame > > m_frames;
    };
}

#endif // _LIB_CASMFE_FRAME_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
