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

#ifndef _LIB_CASMFE_CODES_H_
#define _LIB_CASMFE_CODES_H_


namespace libcasm_fe
{
    enum class Codes
	// --------------------------------------------------------- 0*** ... generic syntax error
	{ SyntaxError                                   = 0x0000  // 00** ... syntax/grammar
	, SyntaxErrorUnrecognizedCharacter              = 0x0001
	, SyntaxErrorUnclosedString                     = 0x0002
	, SyntaxErrorInvalidStatement                   = 0x0003
	
	// --------------------------------------------------------- f*** ... function errors
	, FunctionAttributeIsInvalid                    = 0xfa00  // fa** ... function attribute
	, FunctionAttributeMultipleUseOfStatic          = 0xfa01
	, FunctionAttributeMultipleUseOfSymbolic        = 0xfa02
	, FunctionAttributeMultipleUseOfControlled      = 0xfa03
	, FunctionAttributeControlledAndStaticIsInvalid = 0xfa04
	
	, FunctionArgumentsInvalidRangeAtLookup         = 0xfe00  // fe** ... function argument
	, FunctionArgumentsInvalidRangeAtUpdate         = 0xfe01
	, FunctionArgumentsInvalidRangeAtInitially      = 0xfe02
	
	, FunctionValueInvalidRangeAtUpdate             = 0xfd00  // fd** ... function argument
	, FunctionValueInvalidRangeAtInitially          = 0xfd01
	, FunctionValueAlreadyInitializedAtInitially    = 0xfd02
	
	, AgentInitRuleDoesNotExist                     = 0xa000  // a*** ... Agent errors
			
	, TypeInferenceInvalidLet                       = 0x1000  // 1*** ... type check errors
    , TypeInferenceInvalidExpression                = 0x1001
    , TypeInferenceInvalidPrint                     = 0x1002
    
	, TypeIntegerRangedInvalidInterval              = 0x2000  // 2*** ... Integer type error

    , OperatorAddInvalidOperandType                 = 0x8000  // 8*** ... Operator errors
            
	, TypeBitSyntaxError                            = 0xb000  // b*** ... Bit type error
	, TypeBitSizeIsInvalid                          = 0xb001
    , TypeBitSizeInvalidExpression                  = 0xb002
    
	, TypeUnknown                                   = 0xfffd
	, TypeUnsupported                               = 0xfffe

	, Unspecified                                   = 0xffff
	
	, DUMMY                                         = 0xc0de
	};
	
}

#endif /* _LIB_CASMFE_CODES_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
