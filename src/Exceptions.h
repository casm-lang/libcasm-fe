//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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

#ifndef _LIB_CASMFE_EXCEPTIONS_H_
#define _LIB_CASMFE_EXCEPTIONS_H_

#include <exception>
#include <stdexcept>
#include <string>

#include "various/location.hh"

#include "Codes.h"

// TODO: namespace libcasm_fe

class RuntimeException : public std::exception
{
private:
    const yy::location& location_;
    const std::string msg_;
    const libcasm_fe::Codes error_code_;
    
public:
    RuntimeException
    ( const std::string& msg
    , const libcasm_fe::Codes error_code = libcasm_fe::Codes::Unspecified
    );
    
    RuntimeException
    ( const yy::location& location
    , const std::string& msg
    , const libcasm_fe::Codes error_code_ = libcasm_fe::Codes::Unspecified
    );
    
    virtual const char* what() const throw();
    
    const yy::location& getLocation( void ) const;
    
    const libcasm_fe::Codes getErrorCode( void ) const;
};

class ImpossibleException : public std::exception
{
public:
    virtual const char* what() const throw();
};

class IdentifierAlreadyUsed : public std::logic_error
{
public:
    using logic_error::logic_error;
};

class SymbolAlreadyExists : public IdentifierAlreadyUsed
{
public:
    using IdentifierAlreadyUsed::IdentifierAlreadyUsed;
};

class RuleAlreadyExists : public IdentifierAlreadyUsed
{
public:
    using IdentifierAlreadyUsed::IdentifierAlreadyUsed;
};

#endif // _LIB_CASMFE_EXCEPTIONS_H_
