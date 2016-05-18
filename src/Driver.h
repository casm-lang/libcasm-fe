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

#ifndef CASMI_LIBPARSE_DRIVER_H
#define CASMI_LIBPARSE_DRIVER_H
#include <string>
#include <fstream>
#include <cstdint>
#include <cstdio>
#include <map>
#include <memory>
#include <set>

#include "various/GrammarParser.tab.h"

#include "Symbols.h"

class AstNode;
class RuleNode;

class Driver
{
private:
    std::string filename_;
    FILE *file_;
    std::vector<std::string> lines_;
    uint64_t error_;
    uint64_t warning_;
    
public:
    Driver();
    virtual ~Driver();

    std::map<std::string, RuleNode*> rules_map_;
    AstNode *result;
    std::string spec_name;
    
    std::string init_name;

    // State information for the lexer
    bool trace_parsing;
    bool trace_scanning;

    std::map<std::string, std::set<std::string>> init_dependencies;

    // Handling the scanner.
    size_t get_next_chars(char buffer[], size_t max_size);

    // Run the parser. Return 0 on success.
    AstNode *parse(const std::string& f);

    // Error handling.
    void error(const yy::location& l, const std::string& m);
    void warning(const yy::location& l, const std::string& m);
    void info(const yy::location& l, const std::string& m);
    bool ok() const;

    uint64_t get_error_count() const;
    uint64_t get_warning_count() const;
    
    // Rule handling
    /**
     * @throws RuleAlreadyExists when the rules table contains a rule with
     *         the same name as the name of the \a rule_root.
     * @throws IdentifierAlreadyUsed when the name of the \a rule_root is already
     *         used somewhere else (e.g. for a function).
     */
    void add(RuleNode *rule_root);
    RuleNode *get_init_rule() const;

    // functions
    /**
     * @throws SymbolAlreadyExists when the symbol table contains a symbol with
     *         the same name as the name of the \a function.
     * @throws IdentifierAlreadyUsed when the name of the \a function is already
     *         used somewhere else (e.g. for a rule).
     */
    void add(Function *function);
    SymbolTable function_table;

    // Bindings
    std::map<std::string, size_t> binding_offsets;

    // Dumplist map
    std::unordered_map<size_t, const std::string> function_trace_map;

    const std::string& get_filename();

private:
    void underline( const yy::location& l );
};

class StringDriver: public Driver {
  private:
    std::string str_;
    std::string::iterator iter_;
    std::string::iterator end_;

  public:
    AstNode *parse (const std::string& str);
};

// Tell Flex the lexer's prototype ...
#define YY_DECL \
    yy::casmi_parser::symbol_type yylex (Driver& driver)
    YY_DECL;


#endif
