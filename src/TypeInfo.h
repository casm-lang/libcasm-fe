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

#ifndef _LIBCASM_FE_TYPE_INFO_H_
#define _LIBCASM_FE_TYPE_INFO_H_

#include <libcasm-fe/CasmFE>
#include <libcasm-ir/Type>

namespace libcasm_fe
{
    /**
     * @extends CasmFE
     */
    class TypeInfo
    {
      public:
        void setType( const std::string& name, const libcasm_ir::Type::Ptr& type );

        libcasm_ir::Type::Ptr getType( const std::string& name ) const;

        u1 hasType( const std::string& name ) const;

      protected:
        TypeInfo( void );

        TypeInfo( TypeInfo const& ) = delete;
        TypeInfo( TypeInfo&& ) = delete;
        TypeInfo& operator=( TypeInfo const& ) = delete;
        TypeInfo& operator=( TypeInfo&& ) = delete;

      public:
        // basic types
        static constexpr const char* TYPE_NAME_VOID = "Void";
        static constexpr const char* TYPE_NAME_BOOLEAN = "Boolean";
        static constexpr const char* TYPE_NAME_BINARY = "Binary";
        static constexpr const char* TYPE_NAME_INTEGER = "Integer";
        static constexpr const char* TYPE_NAME_STRING = "String";
        static constexpr const char* TYPE_NAME_DECIMAL = "Decimal";
        static constexpr const char* TYPE_NAME_RATIONAL = "Rational";

        // composed types
        static constexpr const char* TYPE_NAME_TUPLE = "Tuple";
        static constexpr const char* TYPE_NAME_RECORD = "Record";

        // template types
        static constexpr const char* TYPE_NAME_LIST = "List";
        static constexpr const char* TYPE_NAME_RANGE = "Range";
        static constexpr const char* TYPE_NAME_FILE = "File";
        static constexpr const char* TYPE_NAME_PORT = "Port";

        // reference types
        static constexpr const char* TYPE_NAME_RULEREF = "RuleRef";
        static constexpr const char* TYPE_NAME_FUNCREF = "FuncRef";

        // object types
        static constexpr const char* TYPE_NAME_ENUMERATION = "enumeration";
        static constexpr const char* TYPE_NAME_OBJECT = "Object";
        static constexpr const char* TYPE_NAME_AGENT = "Agent";

        static TypeInfo& instance( void )
        {
            static TypeInfo cache;
            return cache;
        }

      private:
        std::unordered_map< std::string, libcasm_ir::Type::Ptr > m_typeName2typePtr;
    };
}

#endif  // _LIBCASM_FE_TYPE_INFO_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
