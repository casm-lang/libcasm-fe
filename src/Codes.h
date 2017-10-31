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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#ifndef _LIBCASM_FE_CODES_H_
#define _LIBCASM_FE_CODES_H_

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
        UpdateRuleFunctionSymbolIsInvalid = 0x0501,
        SymbolAlreadyDefined = 0x0502

        // --------------------------------------------------------- f*** ...
        // function errors
        ,
        FunctionSymbolIsUnknown = 0xf000,

        FunctionDefinitionAlreadyUsed = 0xf010,

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
        DerivedDefinitionAlreadyUsed = 0xd000,

        DerivedArgumentValueInvalid = 0xda00, // da** ... derived argment
        DerivedReturnValueInvalid = 0xda01,
        DerivedExpressionInvalidType = 0xde00 // de** ... derived expression

        // --------------------------------------------------------- 5*** ...
        // rule errors
        ,
        RuleDefinitionAlreadyUsed = 0x5000,

        NotSideEffectFreeRuleCall = 0x5100,

        RuleArgumentValueInvalid = 0x5e00 // 5e** ... rule argument
        ,
        RuleArgumentsSizeInvalidAtCall = 0x5e01,
        RuleArgumentsTypeInvalidAtCall = 0x5e02

        ,
        RuleArgumentsSizeInvalidAtIndirectCall = 0x5e04,
        RuleArgumentsTypeInvalidAtIndirectCall = 0x5e05

        ,
        CaseRuleMultipleDefaultCases = 0x5c00 // 5c** ... case errors

        ,
        AssertInvalidExpression = 0x5a00 // 5a** ... assert errors

        ,
        LetAssignedValueInvalid = 0x5d00

        ,
        BuiltinArgumentValueInvalid = 0x5f00,

        // --------------------------------------------------------- a*** ...
        // agent errors

        AgentInitRuleDoesNotExist = 0xa000,
        AgentInitRuleMultipleDefinitions = 0xa001,
        AgentInitRuleNotDefined = 0xa002,

        // --------------------------------------------------------- 01** ...
        // type annotation errors

        TypeAnnotationInvalidBasicTypeName = 0x0100,
        TypeAnnotationInvalidFixedSizeTypeName = 0x0101,
        TypeAnnotationInvalidComposedTypeName = 0x0102,
        TypeAnnotationInvalidRelationTypeName = 0x0103,

        TypeAnnotationComposedTypeHasNoSubType = 0x0112,
        TypeAnnotationRelationTypeHasNoSubType = 0x0113,

        // --------------------------------------------------------- 1*** ...
        // type inference errors

        TypeInferenceFoundNoTypeAnnotation = 0x1000,
        TypeInferenceUnableToInferType = 0x1eee,

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
        TypeInferenceDerivedReturnTypeMismatch = 0x1323,
        TypeInferenceBuiltinArgumentTypeMismatch = 0x1304,
        TypeInferenceBuiltinArgumentSizeMismatch = 0x1314,
        TypeInferenceBuiltinRelationTypeInvalid = 0x1324,
        TypeInferenceRuleArgumentTypeMismatch = 0x1305,
        TypeInferenceRuleArgumentSizeMismatch = 0x1315,
        TypeInferenceOperatorUnaryRelationTypeInvalid = 0x1306,
        TypeInferenceOperatorBinaryRelationTypeInvalid = 0x1307,

        TypeInferenceQuantifierUniversalPropositionTypeMismatch = 0x1400,
        TypeInferenceQuantifierUniversalPredicateTypeMismatch = 0x1401,
        TypeInferenceQuantifierExistentialPropositionTypeMismatch = 0x1410,
        TypeInferenceQuantifierExistentialPredicateTypeMismatch = 0x1411,

        TypeInferenceConditionalRuleInvalidConditionType = 0x1500,

        TypeInferenceInvalidExpression = 0x1001,
        TypeInferenceInvalidPrint = 0x1002

        ,
        TypeInferenceInvalidIfExpression = 0x1003,

        TypeInferenceForallVariableHasNoType = 0x1004,
        TypeInferenceForallUniverseHasNoType = 0x1014,
        TypeInferenceForallRuleTypeMismatch = 0x1024,
        TypeInferenceForallRuleInvalidConditionType = 0x1025,

        TypeInferenceInvalidConditionalExpressionCondition = 0x1005,
        TypeInferenceInvalidConditionalExpressionPaths = 0x1006

        ,
        TypeInferenceInvalidChooseExpressionVariableTypeMismatch = 0x1007,
        TypeInferenceInvalidChooseExpressionTypeMismatch = 0x1008

        ,
        TypeInferenceInvalidChooseRuleVariableTypeMismatch = 0x1009

        ,
        TypeInferenceInvalidLetExpressionVariableType = 0x1010,
        TypeInferenceInvalidLetExpressionInitializerType = 0x1011,
        TypeInferenceInvalidLetExpressionTypeMismatch = 0x1012,

        TypeInferenceRangeExpressionTypeMismatch = 0x1600,

        TypeCheckUseOfUndeclaredFunctionInInitially = 0xc000,

        TypeIntegerRangedInvalidInterval
        = 0x2000, // 2*** ... Integer type error

        // --------------------------------------------------------- cc** ...
        // consistency check errors

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
        QuantifierExpressionInvalidUniverse = 0x9002,
        ChooseExpressionInvalidUniverse = 0x9003,
        ChooseRuleInvalidUniverse = 0x9004,
        ForallRuleInvalidUniverse = 0x9005,
        ForallRuleInvalidCondition = 0x9006

        // --------------------------------------------------------- fff* ...
        // not categorized errors
        ,
        TypeUnknown = 0xfffd,
        TypeUnsupported = 0xfffe

        ,
        Unspecified = 0xffff
    };
}

#endif /* _LIBCASM_FE_CODES_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
