//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#include "Ast.h"
#include "Driver.h"

using namespace libcasm_fe;

static std::map< NodeType, const std::string > node_type_names_ = {
    { NodeType::ASSERT, std::string( "ASSERT" ) },
    { NodeType::UNDEF_ATOM, std::string( "UNDEF ATOM" ) },
    { NodeType::INTEGER_ATOM, std::string( "INTEGER ATOM" ) },
    { NodeType::FLOATING_ATOM, std::string( "FLOATING ATOM" ) },
    { NodeType::SELF_ATOM, std::string( "SELF ATOM" ) },
    { NodeType::STRING_ATOM, std::string( "STRING ATOM" ) },
    { NodeType::RULE_ATOM, std::string( "RULE ATOM" ) },
    { NodeType::BOOLEAN_ATOM, std::string( "BOOLEAN ATOM" ) },
    { NodeType::DUMMY_ATOM, std::string( "DUMMY ATOM" ) },
    { NodeType::INIT, std::string( "INIT" ) },
    { NodeType::IFTHENELSE, std::string( "IFTHENELSE" ) },
    { NodeType::BODY_ELEMENTS, std::string( "BODY ELEMENTS" ) },
    { NodeType::PROVIDER, std::string( "PROVIDER" ) },
    { NodeType::OPTION, std::string( "OPTION" ) },
    { NodeType::ENUM, std::string( "ENUM" ) },
    { NodeType::FUNCTION, std::string( "FUNCTION" ) },
    { NodeType::DERIVED, std::string( "DERIVED" ) },
    { NodeType::RULE, std::string( "RULE" ) },
    { NodeType::BINARY_EXPRESSION, std::string( "BINARY EXPRESSION" ) },
    { NodeType::UNARY_EXPRESSION, std::string( "UNARY EXPRESSION" ) },
    { NodeType::UPDATE, std::string( "UPDATE" ) },
    { NodeType::SPECIFICATION, std::string( "SPECIFICATION" ) },
    { NodeType::STATEMENT, std::string( "STATEMENT" ) },
    { NodeType::STATEMENTS, std::string( "STATEMENTS" ) },
    { NodeType::SKIP, std::string( "SKIP" ) },
    { NodeType::PARBLOCK, std::string( "PARBLOCK" ) },
    { NodeType::SEQBLOCK, std::string( "SEQBLOCK" ) },
    { NodeType::FUNCTION_ATOM, std::string( "FUNCTION ATOM" ) },
    { NodeType::CALL, std::string( "CALL NODE" ) },
    { NodeType::PRINT, std::string( "PRINT NODE" ) },
    { NodeType::POP, std::string( "POP NODE" ) },
};

std::string unknown_type = "unknown node type";

const std::string& libcasm_fe::type_to_str( NodeType t )
{
    try
    {
        return node_type_names_.at( t );
    }
    catch( const std::out_of_range& e )
    {
        return unknown_type;
    }
}

AstNode::AstNode( NodeType node_type )
: type_( TypeType::UNKNOWN )
{
    node_type_ = node_type;
    // DEBUG(this->to_str());
}

AstNode::AstNode( yy::location& loc, NodeType nt )
: location( loc )
, node_type_( nt )
, type_( TypeType::UNKNOWN )
{
}

AstNode::AstNode( yy::location& loc, NodeType nt, Type t )
: location( loc )
, node_type_( nt )
, type_( t )
{
}

AstNode::~AstNode()
{
    // no dynamically alloceted stuff here
}

std::string AstNode::to_str() const
{
    return std::string( "AStNode: " ) + type_to_str( node_type_ );
}

bool AstNode::equals( AstNode* other ) const
{
    return node_type_ == other->node_type_;
}

std::string AstNode::location_str() const
{
    if( location.begin.filename != nullptr )
    {
        return *location.begin.filename;
    }
    else
    {
        return "NO FILE";
    }
}

AstListNode::AstListNode( yy::location& loc, NodeType node_type )
: AstNode( loc, node_type )
{
}

AstListNode::~AstListNode()
{
    for( auto n : nodes )
    {
        delete n;
    }
    nodes.clear();
}

void AstListNode::add( AstNode* n )
{
    this->nodes.push_back( n );
}

bool AstListNode::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }

    AstListNode* other_cast = static_cast< AstListNode* >( other );

    auto ast1_iter = nodes.begin();
    auto ast2_iter = other_cast->nodes.begin();

    while( ast1_iter < nodes.end() && ast2_iter < other_cast->nodes.end() )
    {
        if( !( ( *ast1_iter )->equals( *ast2_iter ) ) )
        {
            return false;
        }
        ast1_iter += 1;
        ast2_iter += 1;
    }

    if( ast1_iter == nodes.cend() && ast2_iter == other_cast->nodes.cend() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

FunctionDefNode::FunctionDefNode( yy::location& loc, Function* sym )
: AstNode( loc, NodeType::FUNCTION )
, sym( sym )
{
}

FunctionDefNode::~FunctionDefNode()
{
    // sym is deleted in the symbol table
}

EnumDefNode::EnumDefNode( yy::location& loc, Enum* enum_ )
: AstNode( loc, NodeType::ENUM )
, enum_( enum_ )
{
}

EnumDefNode::~EnumDefNode()
{
    // enum_ is deleted in the symbol table
}

IfThenElseNode::IfThenElseNode(
    yy::location& loc, ExpressionBase* condition, AstNode* then, AstNode* els )
: AstNode( loc, NodeType::IFTHENELSE )
, condition_( condition )
, then_( then )
, else_( els )
{
}

ZeroAtom::ZeroAtom( yy::location& loc, AstNode* reference )
: AtomNode( loc, NodeType::ZERO_ATOM, Type( TypeType::UNKNOWN ) )
, ref( reference )
{
}

const AstNode* ZeroAtom::getRef( void ) const
{
    assert( ref );
    return ref;
}

IntegerAtom::IntegerAtom( yy::location& loc, INTEGER_T val )
: AtomNode( loc, NodeType::INTEGER_ATOM, Type( TypeType::INTEGER ) )
{
    val_ = val;
}

IntegerAtom::~IntegerAtom()
{
}

bool IntegerAtom::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }

    IntegerAtom* other_cast = static_cast< IntegerAtom* >( other );
    return val_ == other_cast->val_;
}

FloatingAtom::FloatingAtom( yy::location& loc, FLOATING_T val )
: AtomNode( loc, NodeType::FLOATING_ATOM, Type( TypeType::FLOATING ) )
{
    val_ = val;
}

FloatingAtom::~FloatingAtom()
{
}

bool FloatingAtom::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }

    FloatingAtom* other_cast = static_cast< FloatingAtom* >( other );
    return val_ == other_cast->val_;
}

RationalAtom::RationalAtom( yy::location& loc, const rational_t& val )
: AtomNode( loc, NodeType::RATIONAL_ATOM, Type( TypeType::RATIONAL ) )
, val_( val )
{
}

UndefAtom::UndefAtom( yy::location& loc )
: AtomNode( loc, NodeType::UNDEF_ATOM, Type( TypeType::UNKNOWN ) )
{
}

bool UndefAtom::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

SelfAtom::SelfAtom( yy::location& loc )
: AtomNode( loc, NodeType::SELF_ATOM, Type( TypeType::SELF ) )
{
    DEBUG( "TRUE" );
}

bool SelfAtom::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

BooleanAtom::BooleanAtom( yy::location& loc, bool value )
: AtomNode( loc, NodeType::BOOLEAN_ATOM, Type( TypeType::BOOLEAN ) )
, value( value )
{
}

bool BooleanAtom::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }

    BooleanAtom* other_b = reinterpret_cast< BooleanAtom* >( other );
    return value == other_b->value;
}

RuleAtom::RuleAtom( yy::location& loc, const std::string&& name )
: AtomNode( loc, NodeType::RULE_ATOM, Type( TypeType::RULEREF ) )
, name( name )
{
}

RuleAtom::~RuleAtom()
{
}

bool RuleAtom::equals( AstNode* ) const
{
    throw "NOT IMPLEMENTED";
}

StringAtom::StringAtom( yy::location& loc, std::string&& string )
: AtomNode( loc, NodeType::STRING_ATOM, Type( TypeType::STRING ) )
, string( string )
{
    DEBUG( "StringAtom " << string );
}

StringAtom::~StringAtom()
{
}

bool StringAtom::equals( AstNode* ) const
{
    throw "NOT IMPLEMENTED";
}

BaseFunctionAtom::BaseFunctionAtom( yy::location& loc, NodeType t,
    const std::string name, std::vector< ExpressionBase* >* args )
: AtomNode( loc, t, Type( TypeType::UNKNOWN ) )
, name( name )
, arguments( args )
{
}

std::string BaseFunctionAtom::to_str() const
{
    return name;
}

FunctionAtom::FunctionAtom( yy::location& loc, const std::string name )
: FunctionAtom( loc, name, nullptr )
{
}

FunctionAtom::FunctionAtom( yy::location& loc, const std::string name,
    std::vector< ExpressionBase* >* args )
: BaseFunctionAtom( loc, NodeType::FUNCTION_ATOM, name, args )
, symbol_type( SymbolType::UNSET )
, initialized( false )
{
}

FunctionAtom::~FunctionAtom()
{
}

bool FunctionAtom::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }

    FunctionAtom* other_func = reinterpret_cast< FunctionAtom* >( other );

    if( symbol_type == SymbolType::UNSET )
    {
        return name == other_func->name;
    }

    if( arguments && other_func->arguments
        && arguments->size() == other_func->arguments->size() )
    {
        for( size_t i = 0; i < arguments->size(); i++ )
        {
            if( !arguments->at( i )->equals( other_func->arguments->at( i ) ) )
            {
                return false;
            }
        }
    }

    if( !( !arguments && !other_func->arguments ) )
    {
        return false;
    }

    if( symbol_type == FunctionAtom::SymbolType::FUNCTION
        && symbol_type == other_func->symbol_type )
    {
        if( symbol && other_func->symbol
            && symbol->name != other_func->symbol->name )
        {
            return false;
        }

        if( !( !symbol && !other_func->symbol ) )
        {
            return false;
        }
        return name == other_func->name;
    }
    else if( symbol_type == FunctionAtom::SymbolType::PARAMETER
             && symbol_type == other_func->symbol_type )
    {
        return name == other_func->name && offset == other_func->offset;
    }
    return false;
}

static Type* builtin_atom_new_type( TypeType t )
{
    if( t != TypeType::LIST and t != TypeType::TUPLE_OR_LIST )
    {
        return new Type( t );
    }
    else
    {
        return new Type( t, new Type( TypeType::UNKNOWN ) );
    }
}

BuiltinAtom::BuiltinAtom( yy::location& loc, const std::string name,
    std::vector< ExpressionBase* >* args )
: BaseFunctionAtom( loc, NodeType::BUILTIN_ATOM, name, args )
, return_type( nullptr )
{
    Builtin* built_in = Builtin::get( name );

    assert( built_in && "built-in cannot be null" );

    assert( built_in->ret_type.size() == 1 );
    return_type = builtin_atom_new_type( built_in->ret_type[ 0 ] );

    for( std::vector< TypeType > v : built_in->arg_type )
    {
        assert( v.size() >= 1 );
        Type* t = builtin_atom_new_type( v[ 0 ] );

        for( int i = 1; i < v.size(); i++ )
        {
            t->constraints.push_back( builtin_atom_new_type( v[ i ] ) );
        }

        types.push_back( t );
    }

    id = built_in->id;

    built_in->unify( return_type, types );
}

BuiltinAtom::~BuiltinAtom()
{
}

bool BuiltinAtom::equals( AstNode* ) const
{
    throw "BuiltinAtom::equals() not implemented";
}

std::string BuiltinAtom::to_str() const
{
    Builtin* built_in = Builtin::get( name );
    assert( built_in && "built-in cannot be null" );
    return built_in->name;
}

ListAtom::ListAtom( yy::location& loc, std::vector< ExpressionBase* >* exprs )
: AtomNode( loc, NodeType::LIST_ATOM, TypeType::UNKNOWN )
, expr_list( exprs )
{
    // TODO LEAK! @fhahn
    type_ = Type( TypeType::LIST, new Type( TypeType::UNKNOWN ) );
}

NumberRangeAtom::NumberRangeAtom(
    yy::location& loc, ExpressionBase* left, ExpressionBase* right )
: AtomNode( loc, NodeType::NUMBER_RANGE_ATOM, TypeType::NUMBER_RANGE )
, left( left )
, right( right )
{
}

BinaryExpression::BinaryExpression( yy::location& loc, ExpressionBase* left,
    ExpressionBase* right, libcasm_ir::Value::ID op )
: ExpressionBase( loc, NodeType::BINARY_EXPRESSION, Type( TypeType::UNKNOWN ) )
, left_( left )
, right_( right )
, op( op )
{
}

BinaryExpression::~BinaryExpression()
{
    delete left_;
    delete right_;
}

bool BinaryExpression::equals( AstNode* other ) const
{
    if( not AstNode::equals( other ) )
    {
        return false;
    }

    BinaryExpression* other_cast = static_cast< BinaryExpression* >( other );
    if( left_ == nullptr || other_cast->left_ == nullptr )
    {
        return left_ == nullptr && other_cast->left_ == nullptr
               && right_->equals( other_cast->right_ ) && op == other_cast->op;
    }
    else
    {
        return left_->equals( other_cast->left_ )
               && right_->equals( other_cast->right_ ) && op == other_cast->op;
    }
}

UnaryExpression::UnaryExpression(
    yy::location& loc, ExpressionBase* expr, libcasm_ir::Value::ID op )
: ExpressionBase( loc, NodeType::UNARY_EXPRESSION, Type( TypeType::UNKNOWN ) )
, expr_( expr )
, op( op )
{
}

UnaryExpression::~UnaryExpression()
{
    delete expr_;
}

bool UnaryExpression::equals( AstNode* other ) const
{
    if( not AstNode::equals( other ) )
    {
        return false;
    }

    UnaryExpression* other_cast = static_cast< UnaryExpression* >( other );
    if( expr_ == nullptr || other_cast->expr_ == nullptr )
    {
        return expr_ == nullptr && other_cast->expr_ == nullptr
               && op == other_cast->op;
    }
    else
    {
        return expr_->equals( other_cast->expr_ ) && op == other_cast->op;
    }
}

std::string libcasm_fe::operator_to_str( libcasm_ir::Value::ID op )
{
    switch( op )
    {
        case libcasm_ir::Value::ADD_INSTRUCTION:
            return "+";
        case libcasm_ir::Value::SUB_INSTRUCTION:
            return "-";
        case libcasm_ir::Value::MUL_INSTRUCTION:
            return "*";
        case libcasm_ir::Value::DIV_INSTRUCTION:
            return "/";
        case libcasm_ir::Value::MOD_INSTRUCTION:
            return "%";
        case libcasm_ir::Value::RIV_INSTRUCTION:
            return "div";
        case libcasm_ir::Value::EQU_INSTRUCTION:
            return "=";
        case libcasm_ir::Value::NEQ_INSTRUCTION:
            return "!=";
        case libcasm_ir::Value::AND_INSTRUCTION:
            return "and";
        case libcasm_ir::Value::OR_INSTRUCTION:
            return "or";
        case libcasm_ir::Value::XOR_INSTRUCTION:
            return "xor";
        case libcasm_ir::Value::LTH_INSTRUCTION:
            return "<";
        case libcasm_ir::Value::GTH_INSTRUCTION:
            return ">";
        case libcasm_ir::Value::LEQ_INSTRUCTION:
            return "<=";
        case libcasm_ir::Value::GEQ_INSTRUCTION:
            return ">=";
        case libcasm_ir::Value::NOT_INSTRUCTION:
            return "not";
        default:
            assert( !"internal error" ); // PPA: FIXME: with better verbose info
                                         // etc.
            return "";
    }
}

UpdateNode::UpdateNode(
    yy::location& loc, FunctionAtom* func, ExpressionBase* expr )
: AstNode( loc, NodeType::UPDATE )
, func( func )
, expr_( expr )
{
}

UpdateNode::~UpdateNode()
{
    delete func;
    delete expr_;
}

bool UpdateNode::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }

    UpdateNode* other_cast = static_cast< UpdateNode* >( other );
    return expr_->equals( other_cast->expr_ )
           && func->equals( other_cast->func );
}

PushNode::PushNode( yy::location& loc, ExpressionBase* expr, FunctionAtom* to )
: AstNode( loc, NodeType::PUSH )
, expr( expr )
, to( to )
{
    // TODO LEAK, use constructor of AstNode to set type_
    type_ = new Type( TypeType::LIST, new Type( TypeType::UNKNOWN ) );
}

PushNode::~PushNode()
{
    delete expr;
    delete to;
}

bool PushNode::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }
    FAILURE();
}

PopNode::PopNode( yy::location& loc, FunctionAtom* to, FunctionAtom* from )
: AstNode( loc, NodeType::POP )
, to( std::move( to ) )
, from( from )
, from_type( TypeType::LIST, new Type( TypeType::UNKNOWN ) )
{
    type_.unify( from_type.subtypes[ 0 ] );
}

PopNode::~PopNode()
{
    delete to;
    delete from;
}

bool PopNode::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }
    FAILURE();
}

ForallNode::ForallNode( yy::location& loc, const std::string& ident,
    ExpressionBase* expr, AstNode* stmt )
: AstNode( loc, NodeType::FORALL )
, identifier( std::move( ident ) )
, in_expr( expr )
, statement( stmt )
{
}
ForallNode::~ForallNode()
{
    delete in_expr;
    delete statement;
}

CaseNode::CaseNode( yy::location& loc, ExpressionBase* expr,
    std::vector< std::pair< AtomNode*, AstNode* > >& case_list )
: AstNode( loc, NodeType::CASE )
, expr( expr )
, case_list( std::move( case_list ) )
, /* TODO label_map(),*/ map_fixed( false )
{
}

CaseNode::~CaseNode()
{
    delete expr;
}

bool CaseNode::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }
    FAILURE();
}

UnaryNode::UnaryNode( yy::location& loc, NodeType node_type, AstNode* child )
: AstNode( loc, node_type )
{
    child_ = child;
}

UnaryNode::~UnaryNode()
{
    delete child_;
}

bool UnaryNode::equals( AstNode* other ) const
{
    if( !AstNode::equals( other ) )
    {
        return false;
    }

    UnaryNode* other_cast = static_cast< UnaryNode* >( other );
    return child_->equals( other_cast->child_ );
}

RuleNode::RuleNode( yy::location& loc, AstNode* child, const std::string& name )
: UnaryNode( loc, NodeType::RULE, child )
, name( std::move( name ) )
, arguments()
, binding_offsets()
, dump_list()
{
}

RuleNode::RuleNode( yy::location& loc,
    AstNode* child,
    const std::string& name,
    std::vector< Type* >& args )
: UnaryNode( loc, NodeType::RULE, child )
, name( std::move( name ) )
, arguments( std::move( args ) )
, binding_offsets()
, dump_list()
{
}

RuleNode::RuleNode( yy::location& loc, AstNode* child, const std::string& name,
    std::vector< Type* >& args,
    const std::vector< std::pair< std::string, std::vector< std::string > > >&
        dump_list )
: UnaryNode( loc, NodeType::RULE, child )
, name( std::move( name ) )
, arguments( std::move( args ) )
, binding_offsets()
, dump_list( std::move( dump_list ) )
{
}

CallNode::CallNode(
    yy::location& loc, const std::string& rule_name, ExpressionBase* ruleref )
: CallNode( loc, rule_name, ruleref, nullptr )
{
}

CallNode::CallNode( yy::location& loc, const std::string& rule_name,
    ExpressionBase* ruleref, std::vector< ExpressionBase* >* args )
: AstNode( loc, NodeType::CALL, Type( TypeType::NO_TYPE ) )
, rule_name( rule_name )
, rule( nullptr )
, arguments( args )
, ruleref( ruleref )
{
}

PrintNode::PrintNode(
    yy::location& loc, ExpressionBase* atom, const std::string& filter )
: AstNode( loc, NodeType::PRINT, Type( TypeType::NO_TYPE ) )
, atom( atom )
, filter( filter )
{
    assert( atom and " invalid PrintNode created! " );
}

PrintNode::PrintNode( yy::location& loc, ExpressionBase* atom )
: PrintNode( loc, atom, "" )
{
}

ExpressionBase* PrintNode::getAtom( void ) const
{
    return atom;
}

const std::string& PrintNode::getFilter( void ) const
{
    return filter;
}

LetNode::LetNode( yy::location& loc, Type type, const std::string& identifier,
    ExpressionBase* expr, AstNode* stmt )
: AstNode( loc, NodeType::LET, type )
, identifier( identifier )
, expr( expr )
, stmt( stmt )
{
}

DiedieNode::DiedieNode( yy::location& loc, ExpressionBase* msg )
: AstNode( loc, NodeType::DIEDIE )
, msg( msg )
{
}

InitNode::InitNode( yy::location& loc, const std::string& identifier )
: AstNode( loc, NodeType::INIT )
, identifier( identifier )
{
}

SpecificationNode::SpecificationNode(
    yy::location& loc, const std::string& identifier )
: AstNode( loc, NodeType::SPECIFICATION )
, identifier( identifier )
{
}

Ast::Ast( yy::location& loc, SpecificationNode* spec, AstListNode* elements )
: AstNode( loc, NodeType::SPECIFICATION )
, spec( spec )
, init_rule( 0 )
, elements( elements )
{
}

void Ast::setInitRule( InitNode* init_rule )
{
    assert( init_rule and "invalid init rule pointer!" );
    this->init_rule = init_rule;
}

SpecificationNode* Ast::getSpecification( void )
{
    assert( spec and "invalid specification node pointer!" );
    return spec;
}

InitNode* Ast::getInitRule( void )
{
    assert( init_rule and "invalid specification node pointer!" );
    return init_rule;
}

AstListNode* Ast::getElements( void )
{
    assert( elements and "invalid specification node pointer!" );
    return elements;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
