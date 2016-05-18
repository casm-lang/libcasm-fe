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

#ifndef CASMI_EXCEPTIONS_H
#define CASMI_EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include <string>

class RuntimeException : public std::exception {
  private:
    const std::string msg_;

  public:
    RuntimeException(const std::string& msg);
    virtual const char* what() const throw();

};

class ImpossibleException : public std::exception {
    virtual const char* what() const throw();
};

class IdentifierAlreadyUsed : public std::logic_error {
public:
    using logic_error::logic_error;
};

class SymbolAlreadyExists : public IdentifierAlreadyUsed {
public:
    using IdentifierAlreadyUsed::IdentifierAlreadyUsed;
};

class RuleAlreadyExists : public IdentifierAlreadyUsed {
public:
    using IdentifierAlreadyUsed::IdentifierAlreadyUsed;
};

#endif //CASMI_EXCEPTIONS_H
