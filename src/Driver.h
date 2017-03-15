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

#ifndef CASMI_LIBPARSE_DRIVER_H
#define CASMI_LIBPARSE_DRIVER_H

#include "cpp/Default.h"
#include "cpp/Type.h"

#include <vector>
#include <unordered_map>

#include "Exceptions.h"
#include "various/location.hh"

namespace libcasm_fe
{
    class Driver
    {
      private:
        std::string filename_;
        std::vector< std::string > lines_;
        uint64_t error_;
        uint64_t warning_;

      public:
        Driver();

        std::string spec_name;

        // State information for the lexer
        bool trace_parsing;
        bool trace_scanning;

        // Error handling.
        void error( const yy::location& l, const std::string& m,
            libcasm_fe::Codes code = libcasm_fe::Codes::Unspecified );

        void error( const std::vector< yy::location >& locations,
            const std::string& m,
            libcasm_fe::Codes code = libcasm_fe::Codes::Unspecified );

        void error( const Exception& exception );

        void warning( const yy::location& l, const std::string& m );
        void info( const yy::location& l, const std::string& m );
        bool ok() const;

        uint64_t get_error_count() const;
        uint64_t get_warning_count() const;

        // Dumplist map
        std::unordered_map< size_t, const std::string > function_trace_map;

        const std::string& get_filename();

      private:
        void underline( const yy::location& l );
    };
}

#endif
