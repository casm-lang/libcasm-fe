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

#include "Value.h"

#include <cassert>
#include <utility>
#include <sstream>

#include "Ast.h"

value_t::value_t() : type(TypeType::UNDEF) {}

value_t::value_t(INTEGER_T integer) : type(TypeType::INTEGER) {
  value.integer = integer;
}

value_t::value_t(FLOATING_T float_) : type(TypeType::FLOATING) {
  value.float_ = float_;
}

value_t::value_t(bool boolean) : type(TypeType::BOOLEAN) {
  value.boolean = boolean;
}

value_t::value_t(RuleNode *rule) : type(TypeType::RULEREF) {
  value.rule = rule;
}

value_t::value_t(std::string *string) : type(TypeType::STRING) {
  value.string = string;
}

value_t::value_t(const Type &t, List *list) : type(t.t) {
  value.list = list;
}

value_t::value_t(const enum_value_t *enum_val) : type(TypeType::ENUM) {
  value.enum_val = enum_val;
}

value_t::value_t(const rational_t *rat) : type(TypeType::RATIONAL) {
  value.rat = rat;
}

value_t::value_t(symbol_t *sym) : type(TypeType::SYMBOL) {
  value.sym = sym;
}

value_t::value_t(const value_t& other) : type(other.type), value(other.value) {}

value_t::value_t(value_t&& other) noexcept : type(other.type), value(other.value) {}

value_t& value_t::operator=(const value_t& other) {
  value = other.value;
  type = other.type;
  return *this;
}

bool value_t::operator==(const value_t &other) const {
  if (is_undef() || other.is_undef()) {
    return is_undef() && other.is_undef();
  }

  if (is_symbolic()) {
    if (other.is_symbolic()) {
      if (value.sym->list && other.value.sym->list) {
        return *value.sym->list == *other.value.sym->list;
      } else {
        return value.sym->id == other.value.sym->id;
      }
    } else {
      return false;
    }
  }

  if (other.is_symbolic()) {
    if (is_symbolic()) {
      if (value.sym->list && other.value.sym->list) {
        return *value.sym->list == *other.value.sym->list;
      } else {
        return value.sym->id == other.value.sym->id;
      }
    } else {
      return false;
    }
  }

  switch (type) {
    case TypeType::INTEGER: return value.integer == other.value.integer;
    case TypeType::FLOATING: return value.float_ == other.value.float_;
    case TypeType::BOOLEAN: return value.boolean == other.value.boolean;
    case TypeType::ENUM: return value.enum_val == other.value.enum_val;
    case TypeType::RATIONAL: return *value.rat == *other.value.rat;
    case TypeType::STRING: return *value.string == *other.value.string;
    case TypeType::TUPLE:
    case TypeType::TUPLE_OR_LIST:
    case TypeType::LIST: return *value.list == *other.value.list;
    default: FAILURE();
  }
}

bool value_t::operator!=(const value_t &other) const {
  return !operator==(other);
}

bool value_t::is_undef() const {
  return type == TypeType::UNDEF;
}

bool value_t::is_symbolic() const {
  return type == TypeType::SYMBOL;
}

const std::string value_t::to_str(bool symbolic) const {
  switch (type) {
    case TypeType::INTEGER:
      return std::to_string(value.integer);
    case TypeType::FLOATING:
      return std::to_string(value.float_);
    case TypeType::SELF:
      return std::move("self");
    case TypeType::UNDEF: // are UNDEF and SELF the same here?
      return std::move("undef");
    case TypeType::RULEREF:
      return "@" + value.rule->name;
    case TypeType::ENUM:
      return *value.enum_val->name;
    case TypeType::RATIONAL:
      return value.rat->to_str();
    case TypeType::STRING:
      return *value.string;
    case TypeType::TUPLE:
    case TypeType::TUPLE_OR_LIST:
    case TypeType::LIST: {
        if (symbolic) {
          std::string tmp = value.list->to_str();
          if (tmp == "[  ]") {
            return "eListEmpty";
          } else {
            return tmp;
          }
        }
        return value.list->to_str();
    }
    case TypeType::BOOLEAN:
      if (value.boolean) {
        return "true";
      } else {
        return "false";
      }
    case TypeType::SYMBOL:
      return "sym"+std::to_string(value.sym->id);
    default: throw RuntimeException("Unsupported type in value_t.to_str() ");
  }
}

symbol_t::symbol_t(uint32_t id) : symbol_t(id, nullptr)  {}

symbol_t::symbol_t(uint32_t id, symbolic_condition_t *cond) : id(id),
    condition(cond), type_dumped(false), update_dumped(false), list(nullptr) {}


symbolic_condition_t::symbolic_condition_t(value_t *lhs, value_t *rhs,
                                       ExpressionOperation op) : lhs(lhs), rhs(rhs), op(op) {}

std::string symbolic_condition_t::to_str() const {
  switch (op) {
    case ExpressionOperation::EQ:
      return lhs->to_str()+"="+rhs->to_str();
    case ExpressionOperation::NEQ:
      return lhs->to_str()+"!="+rhs->to_str();
    case ExpressionOperation::LESSEREQ:
      return "$lesseq("+lhs->to_str()+", "+rhs->to_str()+")";
    case ExpressionOperation::LESSER:
      return "$less("+lhs->to_str()+", "+rhs->to_str()+")";
    case ExpressionOperation::GREATER:
      return "$greater("+lhs->to_str()+", "+rhs->to_str()+")";
    case ExpressionOperation::GREATEREQ:
      return "$greatereq("+lhs->to_str()+", "+rhs->to_str()+")";
    default:
      FAILURE();
  }
}

rational_t::rational_t() {}

rational_t::rational_t(int64_t num, int64_t denom) {
  numerator = num;
  denominator = denom;
}

rational_t::rational_t(const rational_t& other) : numerator(other.numerator),
    denominator(other.denominator) {}

bool rational_t::operator==(const rational_t& other) const {
  return (numerator * other.denominator) == (other.numerator * denominator);
}

const rational_t& rational_t::operator+(const rational_t& other) const {
  auto result = new rational_t;
  result->numerator = (numerator * other.denominator) + (other.numerator * denominator);
  result->denominator = denominator * other.denominator;
  return *result;
}

const rational_t& rational_t::operator-(const rational_t& other) const {
  auto result = new rational_t;
  result->numerator = (numerator * other.denominator) - (other.numerator * denominator);
  result->denominator = denominator * other.denominator;
  return *result;
}

const rational_t& rational_t::operator*(const rational_t& other) const {
  auto result = new rational_t;
  result->numerator = numerator * other.numerator;
  result->denominator = denominator * other.denominator;
  return *result;
}

const rational_t& rational_t::operator/(const rational_t& other) const {
  auto result = new rational_t;
  result->numerator = numerator * other.denominator;
  result->denominator = denominator * other.numerator;
  return *result;
}

const rational_t& rational_t::operator%(const rational_t&) const {
  // rational modulo is not supported by CASM
  return *this;
}

int64_t gcd(int64_t a, int64_t b) {
  int64_t tmp;

  while (b != 0) {
    tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

const std::string rational_t::to_str() const {
  if (numerator == 0) {
    return "0";
  }
  int64_t divisor = gcd(numerator, denominator);
  int64_t num = numerator / divisor;
  int64_t denom = denominator / divisor;
  if (denom == 1) {
    return std::to_string(num);
  } else {
    return std::to_string(num) + "/" + std::to_string(denom);
  }
  return "";
}

List::List(ListType t) : list_type(t) {}


void List::const_iterator::do_init(const List *ptr) {
  pos = 0;
  if (!ptr) {
    head = nullptr;
    bottom = nullptr;
    tail = nullptr;
    return;
  }

  if (ptr->is_head()) {
    head = reinterpret_cast<const HeadList*>(ptr);
    bottom = nullptr;
    tail = nullptr;
  } else if (ptr->is_bottom()){
    bottom = reinterpret_cast<const BottomList*>(ptr);
    pos = bottom->values.size() - 1;
    if (bottom->values.size() == 0) {
      do_init(bottom->tail);
    } else {
      head = nullptr;
      tail = nullptr;
    }
  } else if (ptr->is_skip()){
    bottom = nullptr;
    const SkipList *skip = reinterpret_cast<const SkipList*>(ptr);
    if (skip->bottom->values.size() > skip->skip) {
      bottom = skip->bottom;
      pos = skip->bottom->values.size() - skip->skip - 1;
      tail = nullptr;
    } else {
      if (skip->bottom->tail) {
        TailList *current = skip->bottom->tail;
        size_t i;
        size_t additional_skip =  skip->skip - skip->bottom->values.size();
        for (i=0; current && i < additional_skip; i++) {
          current = current->right;
        }

        if (i == additional_skip) {
          tail = current;
        } else {
          tail = nullptr;
        }
      } else {
        tail = nullptr;
      }
    }
    head = nullptr;
  } else if (ptr->is_tail()) {
    tail = reinterpret_cast<const TailList*>(ptr);
    head = nullptr;
    bottom = nullptr;
  }
}

List::const_iterator::const_iterator(const List *ptr) {
  do_init(ptr);
}

List::const_iterator::const_iterator(const self_type& other) : bottom(other.bottom), head(other.head), pos(other.pos) { }

List::const_iterator::self_type List::const_iterator::operator++() {
  next();
  return *this;
}

// Advancing an invalid iterator does not do anything
void List::const_iterator::next() {
  if (head) {
    do_init(head->right);
  } else if (bottom) {
    if (pos > 0) {
      pos -= 1;
    } else {
      do_init(bottom->tail);
    }
  } else if (tail) {
      do_init(tail->right);
    //FAILURE();
  }
}

List::const_iterator::self_type List::const_iterator::operator++(int) {
  self_type copy(*this);
  operator++();
  return copy;
}

const value_t& List::const_iterator::operator*() {
  if (head) {
    return head->current_head;
  } else if (bottom) {
    return bottom->values[pos];
  } else if (tail) {
    return tail->current_tail;
  } else {
    FAILURE();
  }
}

// all iterators that are not invalid (head = bottom = nullptr and pos = 0)
// are equal; a valid and an invalid iterator are _NOT_ equal
bool List::const_iterator::operator==(const self_type& rhs) const {
  if (!head && !bottom && !tail) {
    return !rhs.head && !rhs.bottom && !rhs.tail;
  } else {
    return rhs.head || rhs.bottom || rhs.tail;
  }
}

bool List::const_iterator::operator!=(const self_type& rhs) const {
  return !(*this == rhs);
}

List::const_iterator List::begin() const {
  return const_iterator(this);
}

List::const_iterator List::end() const {
  return const_iterator(nullptr);
}


bool List::operator==(const List& other) const {
  auto iter1 = begin();
  auto iter2 = other.begin();

  while (iter1 != end() && iter2 != end()) {
    if (*iter1 != *iter2) {
      return false;
    }
    iter1++;
    iter2++;
  }

  if (iter1 == end() && iter2 == end()) {
    return true;
  } else {
    return false;
  }
}

bool List::operator!=(const List& other) const {
  return ! (*this == other);
}

bool List::is_bottom() const {
  return list_type == ListType::BOTTOM;
}

bool List::is_head() const {
  return list_type == ListType::HEAD;
}

bool List::is_skip() const {
  return list_type == ListType::SKIP;
}

bool List::is_tail() const {
  return list_type == ListType::TAIL;
}

const std::string List::to_str() const {
  std::stringstream res;
  bool add_comma = false;
  res << "[ ";
  for (auto iter=begin(); iter != end(); iter.next()) {
    if (add_comma) {
      res << ", ";
    }
    if ((*iter).type == TypeType::STRING) {
      res << "\"" << (*iter).to_str() << "\"";
    } else {
      res << (*iter).to_str();
    }
    add_comma = true;
  }
  res << " ]";
  return res.str();
}


void List::bump_usage() {
  if (is_bottom()) {
    reinterpret_cast<BottomList*>(this)->usage_count += 1;
    return;
  }

  if (is_head()) {
    reinterpret_cast<HeadList*>(this)->right->bump_usage();
  }

  if (is_skip()) {
    reinterpret_cast<SkipList*>(this)->bottom->bump_usage();
  }
}

void List::decrease_usage() {
  if (is_bottom()) {
    reinterpret_cast<BottomList*>(this)->usage_count -= 1;
    return;
  }

  if (is_head()) {
    reinterpret_cast<HeadList*>(this)->right->bump_usage();
  }

  if (is_skip()) {
    reinterpret_cast<SkipList*>(this)->bottom->bump_usage();
  }
}

BottomList* List::collect() {
  if (is_head()) {
    HeadList* list = reinterpret_cast<HeadList*>(this);
    BottomList *result = list->right->collect();
    result->values.push_back(std::move(list->current_head));
    return result;
  } else if (is_skip()) {
    SkipList *list = reinterpret_cast<SkipList*>(this);
    BottomList *result = list->bottom->collect();
    for (size_t i=list->skip; i > 0; i--) {
      result->values.pop_back();
    }
    return result;
  } else if (is_bottom()) {
    BottomList* list = reinterpret_cast<BottomList*>(this);
    if (list->usage_count <= 1) {
      list->usage_count = 1;
      if (list->tail) {
        list->tail->collect(list->values);
        list->tail = nullptr;
      }
      return list;
    } else {
      BottomList *copy = new BottomList();
      copy->usage_count = 1;
      copy->values = list->values;
      list->usage_count -= 1;
      copy->allocated_in_collect = true;

      if (list->tail) {
        list->tail->collect(copy->values);
        list->tail = nullptr;
      }
      return copy;
    }
  } else {
    FAILURE();
  }
}

HeadList::HeadList(List *l, const value_t& val) : List(ListType::HEAD), right(l), current_head(val) {}

TailList::TailList(TailList *l, const value_t& val) : List(ListType::TAIL), right(l), current_tail(val) {}

void TailList::collect(std::vector<value_t>& collect_to) {
  collect_to.insert(collect_to.begin(), current_tail);
  if (right) {
    right->collect(collect_to);
  }
}

BottomList::BottomList()
  : List(ListType::BOTTOM), usage_count(0), values(), tail(nullptr) {}


BottomList::BottomList(const std::vector<value_t>& vals)
  : List(ListType::BOTTOM), usage_count(0), values(std::move(vals)), tail(nullptr) {}

BottomList::~BottomList() {
}


bool BottomList::is_used() const {
  return usage_count > 0;
}

bool BottomList::check_allocated_and_set_to_false() {
  if (allocated_in_collect) {
    allocated_in_collect = false;
    return true;
  }
  return false;
}

SkipList::SkipList(size_t skip, BottomList *btm) : List(ListType::SKIP), skip(skip), bottom(btm) {}


namespace std {
  size_t hash<value_t>::operator()(const value_t &key) const {
    switch (key.type) {
      case TypeType::INTEGER:
        return key.value.integer;
      case TypeType::FLOATING:
        static std::hash<FLOATING_T> floating_hasher;
        return floating_hasher(key.value.float_);
      case TypeType::BOOLEAN:
        return key.value.boolean;
      case TypeType::SELF:
      case TypeType::UNDEF: // are UNDEF and SELF the same here?
        return 0;
      case TypeType::RULEREF:
        return reinterpret_cast<size_t>(key.value.rule);
      case TypeType::STRING:
        static std::hash<std::string> string_hasher;
        return string_hasher(*key.value.string);
      case TypeType::TUPLE:
      case TypeType::TUPLE_OR_LIST:
      case TypeType::LIST: {
        size_t h = 0;
        for (const value_t& v : *key.value.list) {
          h += operator()(v);
        }
        return h;
      }
      case TypeType::ENUM:
        return (size_t) key.value.enum_val->id;
      case TypeType::RATIONAL:
        return (size_t) key.value.rat->numerator + key.value.rat->denominator;
      case TypeType::SYMBOL:
        return reinterpret_cast<size_t>(key.value.sym);
      default: throw RuntimeException("Unsupported type in std::hash<value_t>()");
    }
  }


  std::hash<value_t> hash<std::vector<value_t>>::hasher;
  size_t hash<std::vector<value_t>>::operator()(const std::vector<value_t> &key) const {
    size_t h = 0;
    for (const value_t& v : key) {
      h += hasher(v);
    }
    return h;
  }

  std::hash<value_t> hash<HeadList>::hasher;
  size_t hash<HeadList>::operator()(const HeadList &key) const {
    return hasher(key.current_head);
  }

  std::hash<std::vector<value_t>> hash<BottomList>::list_hasher;
  size_t hash<BottomList>::operator()(const BottomList &key) const {
    return list_hasher(key.values);
  }
}
