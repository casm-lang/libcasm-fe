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

#include <stdexcept>
#include <cstdio>
#include <cstring>

#include "Driver.h"

#define BOLD_BLACK   "\x1b[1m"
#define BOLD_RED     "\x1b[1;31m"
#define BOLD_GREEN   "\x1b[1;32m"
#define BOLD_YELLOW  "\x1b[1;33m"
#define BOLD_MAGENTA "\x1b[1;35m"
#define RED          "\x1b[31m"
#define GREEN        "\x1b[32m"
#define YELLOW       "\x1b[33m"
#define MAGENTA      "\x1b[35m"
#define RESET        "\x1b[0m"

extern int yylex_destroy(void);

// driver must be global, because it is needed for YY_INPUT
Driver *global_driver;

Driver::Driver () 
    : error_(0), warning_(0), trace_parsing (false), trace_scanning (false), init_dependencies(),
      function_table(), function_trace_map() {
  file_ = nullptr;
  result = nullptr;

  std::vector<Type*> args;
  args.push_back(new Type(TypeType::SELF));
  function_table.add(new Function("program", yy::location(nullptr), args, new Type(TypeType::RULEREF), nullptr));

  lines_.push_back("");
}

Driver::~Driver () {
  if (file_ != nullptr) {
    fclose(file_);
  }
  yylex_destroy();
}

size_t Driver::get_next_chars(char buf[], size_t max_size) {
  if (fgets(buf, max_size, file_) == NULL) {
    if (ferror(file_)) {
      return -1;
    } else {
      return 0;
    }
  } else {
    // lines_ must not be empty (initialized with empty string in constructor)
    lines_.back().append(buf);
    if (buf[strlen(buf)-1] == '\n') {
      lines_.push_back("");
    }
    return strlen(buf);
  }
}

AstNode *Driver::parse (const std::string &f) {
  int res = -1;

  if (file_ != nullptr) {
    fclose(file_);
  }

  filename_ = f;
  file_ = fopen(filename_.c_str(), "rt");
  if (file_ == NULL) {
    std::cerr << "error: could not open `" << filename_ << "´" << std::endl;
    return nullptr;
  }

  yy::casmi_parser parser (*this);
  parser.set_debug_level (trace_parsing);

  try {
    res = parser.parse ();

    // TODO check leak on parser error
    if( res != 0 || error_ > 0 )
    {
      return nullptr;
    }

  } catch (const std::exception& e) {
    std::cerr << "error: got exception: " << e.what() << " -- exiting" << std::endl;
    return nullptr;
  }

  return result;
}

void Driver::error( const yy::location& l, const std::string& m )
{
    // Set state to error!
    error_++;
    
    std::cerr << BOLD_BLACK << filename_ << ":" << l << ": " << BOLD_RED
              << "error: " << RESET << BOLD_BLACK << m << RESET << std::endl;
    
    underline( l );
}

void Driver::warning( const yy::location& l, const std::string& m )
{
    // increment warning counter
    warning_++;

    std::cerr << BOLD_BLACK << filename_ << ":" << l << ": " << BOLD_MAGENTA
              << "warning: " << RESET << BOLD_BLACK << m << RESET << std::endl;
    
    underline( l );
}

void Driver::info( const yy::location& l, const std::string& m )
{
    std::cerr << BOLD_BLACK << filename_ << ":" << l << ": " << BOLD_GREEN
              << "info: " << RESET << BOLD_BLACK << m << RESET << std::endl;
    
    underline( l );
}


void Driver::underline( const yy::location& l )
{
    if( l.begin.line == l.end.line && l.begin.line <= lines_.size() )
    {
        const std::string location_info = filename_ + ":" + std::to_string(l.begin.line) + " ";
        const std::string& error_line = lines_[l.begin.line - 1];

        std::cerr << location_info << error_line
                  << std::string(location_info.size() + l.begin.column - 1, ' ')
                  << GREEN << "^" << std::string(l.end.column - l.begin.column + 1, '~') << RESET
                  << std::endl;
    }
    else
    {
        for( size_t i = l.begin.line; (i <= l.end.line && i <= lines_.size()); i++ )
        {
            std::cerr << filename_ << ":" << i << " " << lines_[i - 1];
        }
    }
}



bool Driver::ok() const
{
  return error_ == 0;
}

uint64_t Driver::get_error_count() const
{
    return error_;
}

uint64_t Driver::get_warning_count() const
{
    return warning_;
}

void Driver::add(RuleNode *rule_root) {
  Function *function = function_table.get_function(rule_root->name);
  if (function != nullptr) { // rules and functions can't have the same name
    throw IdentifierAlreadyUsed("identifier `" + rule_root->name +
                                "` already used as name for a function in line " +
                                std::to_string(function->location.begin.line));
  }

  const auto result = rules_map_.emplace(rule_root->name, rule_root);
  if (result.second) {
    DEBUG("Add symbol "+rule_root->name);
    rule_root->binding_offsets = std::move(binding_offsets);
    binding_offsets.clear(); // is this necessary? move should empty map
  } else {
    const auto it = result.first;
    RuleNode *existingRule = it->second;
    throw RuleAlreadyExists("redefinition of rule `" + rule_root->name +
                            "` which is defined in line " +
                            std::to_string(existingRule->location.begin.line));
  }
}

RuleNode *Driver::get_init_rule() const {
  return rules_map_.at(init_name);
}

void Driver::add(Function *function)
{
  const auto it = rules_map_.find(function->name);
  if (it != rules_map_.cend()) { // rules and functions can't have the same name
    RuleNode *existingRule = it->second;
    throw IdentifierAlreadyUsed("identifier `" + function->name +
                                "` already used as name for a rule in line " +
                                std::to_string(existingRule->location.begin.line));
  }

  function_table.add(function);
}

const std::string& Driver::get_filename() {
  return filename_;
}

AstNode *StringDriver::parse (const std::string &str) {
  char tmpname[] = "/tmp/casmi_test_XXXXXX";
  int fd = mkstemp(&tmpname[0]);

  if (fd == -1) {
    std::cerr << "Could not create tmpfile" << std::endl;
    return nullptr;
  }

  FILE *file = fdopen(fd, "w");
  if (file == NULL) {
    std::cerr << "Could not open file stream for tmpfile" << std::endl;
    return nullptr;
  } 

  fwrite(str.c_str(), str.length(), sizeof(char), file);
  fclose(file);
  AstNode *res = Driver::parse(tmpname);
  remove(tmpname);

  return res;
}


