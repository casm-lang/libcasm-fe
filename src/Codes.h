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
    { SyntaxError                                   = 0x0000  // 0*** ... generic syntax error
	, SyntaxErrorUnrecognizedCharacter              = 0x0001
	, SyntaxErrorUnclosedString                     = 0x0002
	, SyntaxErrorInvalidStatement                   = 0x0003
	
	, FunctionAttributeIsInvalid                    = 0xfa00  // fa** ... function attribute error
	, FunctionAttributeMultipleUseOfStatic          = 0xfa01
	, FunctionAttributeMultipleUseOfSymbolic        = 0xfa02
	, FunctionAttributeMultipleUseOfControlled      = 0xfa03
	, FunctionAttributeControlledAndStaticIsInvalid = 0xfa04

	, AgentInitRuleDoesNotExist                     = 0xa000  // a*** ... Agent errors
			
	, LetTypeInferenceFailed                        = 0x1000  // 1*** ... type check errors
			
	, TypeIntegerRangedInvalidInterval              = 0x2000  // 2*** ... Integer type error
			
	, TypeBitSyntaxError                            = 0xb000  // b*** ... Bit type error
	, TypeBitSizeIsInvalid                          = 0xb001
			
	, TypeUnknown                                   = 0xfffd
	, TypeUnsupported                               = 0xfffe
			
	, Unspecified                                   = 0xffff
	};
}

#endif /* _LIB_CASMFE_CODES_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
