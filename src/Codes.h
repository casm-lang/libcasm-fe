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

#ifndef _LIB_CASMFE_CODES_H_
#define _LIB_CASMFE_CODES_H_

namespace libcasm_fe
{
    enum class Code
    // --------------------------------------------------------- 0*** ...
    // generic syntax error
    {
        SyntaxError = 0x0000 // 00** ... syntax/grammar
        ,
        SyntaxErrorUnrecognizedCharacter = 0x0001,
        SyntaxErrorUnclosedString = 0x0002,
        SyntaxErrorInvalidStatement = 0x0003,
        SyntaxErrorUnclosedComment = 0x0004

        ,
        IdentifierAlreadyUsed = 0x0010

        // --------------------------------------------------------- 05** ...
        // symbol resolver errors
        ,
        SymbolIsUnknown = 0x0500,
        UpdateRuleFunctionSymbolIsInvalid = 0x0501

        // --------------------------------------------------------- f*** ...
        // function errors
        ,
        FunctionSymbolIsUnknown = 0xf000

        ,
        FunctionDefinitionAlreadyUsed = 0xf010

        ,
        FunctionAttributeIsInvalid = 0xfa00 // fa** ... function attribute
        ,
        FunctionAttributeMultipleUseOfFunctionClassifier = 0xfa01,
        FunctionAttributeMultipleUseOfSymbolic = 0xfa02

        ,
        FunctionDefaultValueInvalidRange = 0xfb01,
        FunctionDefaultValueTypeMismatch = 0xfb02

        ,
        FunctionArgumentInvalidValueAtLookup
        = 0xfe00 // fe** ... function argument
        ,
        FunctionArgumentInvalidValueAtUpdate = 0xfe01

        ,
        FunctionUpdateInvalidValueAtUpdate = 0xfd00 // fd** ... function value
        ,
        FunctionValueInvalidRangeAtInitially = 0xfd01,
        FunctionValueAlreadyInitializedAtInitially = 0xfd02

        ,
        FunctionIdentifierIsBuiltinName = 0xf100 // f1** ... function identifer

        // --------------------------------------------------------- d*** ...
        // derived errors
        ,
        DerivedArgumentValueInvalid = 0xda00, // da** ... derived argment
        DerivedReturnValueInvalid = 0xda01,
        DerivedExpressionInvalidType = 0xde00 // de** ... derived expression

        // --------------------------------------------------------- 5*** ...
        // statement errors
        ,
        RuleArgumentsInvalidRangeAtCall = 0x5e00 // 5e** ... rule argument
        ,
        RuleArgumentsSizeInvalidAtCall = 0x5e01,
        RuleArgumentsTypeInvalidAtCall = 0x5e02

        ,
        RuleArgumentsInvalidRangeAtIndirectCall = 0x5e03,
        RuleArgumentsSizeInvalidAtIndirectCall = 0x5e04,
        RuleArgumentsTypeInvalidAtIndirectCall = 0x5e05

        ,
        CaseLabelMultipleUseOfDefault = 0x5c00 // 5c** ... case errors

        ,
        AssertInvalidExpression = 0x5a00 // 5a** ... assert errors

        ,
        LetAssignedValueInvalid = 0x5d00,

        // --------------------------------------------------------- a*** ...
        // agent errors

        AgentInitRuleDoesNotExist = 0xa000,
        AgentInitRuleMultipleDefinitions = 0xa001,
        AgentInitRuleNotDefined = 0xa002,

        // --------------------------------------------------------- 01** ...
        // type annotation errors

        TypeAnnotationInvalidComposedTypeName = 0x0100,

        // --------------------------------------------------------- 1*** ...
        // type inference errors

        TypeInferenceFoundNoTypeAnnotation = 0x1000,

        TypeInferenceFoundNoResultType = 0x1100,
        TypeInferenceFoundMultipleResultTypes = 0x1101,
        TypeInferenceFoundNoArgumentType = 0x1102,

        TypeInferenceInvalidLetRuleVariableType = 0x1200,
        TypeInferenceInvalidLetRuleExpressionType = 0x1201,
        TypeInferenceLetRuleTypesMismatch = 0x1202,

        TypeInferenceInvalidUpdateRuleFunctionType = 0x1203,
        TypeInferenceInvalidUpdateRuleExpressionType = 0x1204,
        TypeInferenceUpdateRuleTypesMismatch = 0x1205,

        TypeInferenceBuiltinAsBitInvalid2ndArgumentType = 0x1b00,

        TypeInferenceNotDefinedForExpression = 0x1300,
        TypeInferenceArgumentTypeMismatch = 0x1301,

        TypeInferenceFunctionArgumentTypeMismatch = 0x1302,
        TypeInferenceFunctionArgumentSizeMismatch = 0x1312,
        TypeInferenceDerivedArgumentTypeMismatch = 0x1303,
        TypeInferenceDerivedArgumentSizeMismatch = 0x1313,
        TypeInferenceBuiltinArgumentTypeMismatch = 0x1304,
        TypeInferenceBuiltinArgumentSizeMismatch = 0x1314,
        TypeInferenceRuleArgumentTypeMismatch = 0x1305,
        TypeInferenceRuleArgumentSizeMismatch = 0x1315,

        TypeInferenceQuantifierUniversalPropositionTypeMismatch = 0x1400,
        TypeInferenceQuantifierUniversalPredicateTypeMismatch = 0x1401,
        TypeInferenceQuantifierExistentialPropositionTypeMismatch = 0x1410,
        TypeInferenceQuantifierExistentialPredicateTypeMismatch = 0x1411,

        TypeInferenceConditionalRuleInvalidConditionType = 0x1500,

        TypeInferenceInvalidExpression = 0x1001,
        TypeInferenceInvalidPrint = 0x1002

        ,
        TypeInferenceInvalidIfExpression = 0x1003,
        TypeInferenceInvalidForallExpression = 0x1004

        ,
        TypeInferenceInvalidConditionalExpressionCondition = 0x1005,
        TypeInferenceInvalidConditionalExpressionPaths = 0x1006

        ,
        TypeCheckUseOfUndeclaredFunctionInInitially = 0xc000

        ,
        TypeIntegerRangedInvalidInterval = 0x2000 // 2*** ... Integer type error

        ,
        TypeNumberRangeInvalidTypeAtLeftHandSide
        = 0x3000 // 3*** ... Number range type error
        ,
        TypeNumberRangeInvalidTypeAtRightHandSide
        = 0x3001 // 3*** ... Number range type error

        // --------------------------------------------------------- cc** ...
        // consistency check errors
        ,
        UpdateRuleInvalidClassifier = 0xcc00,
        DirectCallExpressionInvalidClassifier = 0xcc01

        // --------------------------------------------------------- 8*** ...
        // operator errors
        ,
        OperatorAddInvalidOperandType = 0x8000,
        OperatorInvalidOperands = 0x8001

        // --------------------------------------------------------- b*** ...
        // bit type errors
        ,
        TypeBitSyntaxError = 0xb000,
        TypeBitSizeIsInvalid = 0xb001,
        TypeBitSizeInvalidExpression = 0xb002

        ,
        TypeBitSizeInvalidInLetExpression = 0xb003,
        TypeBitSizeInvalidInIninitallyExpression = 0xb004

        // --------------------------------------------------------- 7*** ...
        // update set errors
        ,
        UpdateSetClash = 0x7000,
        UpdateSetMergeConflict = 0x7001

        // --------------------------------------------------------- 9*** ...
        // unsorted run-time errors
        ,
        ConditionalRuleInvalidCondition = 0x9000,
        ConditionalExpressionInvalidCondition = 0x9001,
        QuantifierExpressionInvalidUniverse = 0x9002

        // --------------------------------------------------------- fff* ...
        // not categorized errors
        ,
        TypeUnknown = 0xfffd,
        TypeUnsupported = 0xfffe

        ,
        Unspecified = 0xffff
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
