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
    { SyntaxError                                  = 0x0000
	, FunctionAttributeIsInvalid                   = 0xf100
	, FunctionAttributeMultipleUseOfStatic         = 0xf101
	, FunctionAttributeMultipleUseOfSymbolic       = 0xf102
	, FunctionAttributeMultipleUseOfControlled     = 0xf103
	, Unspecified                                  = 0xffff
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
