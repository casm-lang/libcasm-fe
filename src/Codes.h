//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                <https://github.com/casm-lang/libcasm-fe>
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
        SyntaxError = 0x0000  // 00** ... syntax/grammar
        ,
        SyntaxErrorUnrecognizedCharacter = 0x0001,
        SyntaxErrorUnclosedString = 0x0002,
        SyntaxErrorInvalidStatement = 0x0003,
        SyntaxErrorUnclosedComment = 0x0004

        ,
        IdentifierAlreadyUsed = 0x0010

        // --------------------------------------------------------- 05** ...
        // attribution errors
        ,
        AttributionBasicAttributeUnknown = 0x0400,
        AttributionBasicAttributeAlreadyUsed = 0x0401,
        AttributionExpressionAttributeUnknown = 0x0410,
        AttributionExpressionAttributeAlreadyUsed = 0x0411

        // --------------------------------------------------------- 05** ...
        // symbol resolver errors
        ,
        SymbolIsUnknown = 0x0500,
        UpdateRuleFunctionSymbolIsInvalid = 0x0501,
        SymbolAlreadyDefined = 0x0502,
        SymbolArgumentSizeMismatch = 0x0503

        // --------------------------------------------------------- f*** ...
        // function errors
        ,
        FunctionSymbolIsUnknown = 0xf000,

        FunctionDefinitionAlreadyUsed = 0xf010,
        FunctionDefinitionReClassification = 0xf011,

        FunctionAttributeIsInvalid = 0xfa00  // fa** ... function attribute
        ,
        FunctionAttributeMultipleUseOfFunctionClassifier = 0xfa01,
        FunctionAttributeMultipleUseOfSymbolic = 0xfa02

        ,
        FunctionDefaultValueInvalidRange = 0xfb01,
        FunctionDefaultValueTypeMismatch = 0xfb02

        ,
        FunctionArgumentInvalidValueAtLookup = 0xfe00  // fe** ... function argument
        ,
        FunctionArgumentInvalidValueAtUpdate = 0xfe01

        ,
        FunctionUpdateInvalidValueAtUpdate = 0xfd00  // fd** ... function value
        ,
        FunctionValueInvalidRangeAtInitially = 0xfd01,
        FunctionValueAlreadyInitializedAtInitially = 0xfd02,

        FunctionDefinitionIdentifierIsBuiltinName = 0xf100,  // f1** ... function identifer
        FunctionDefinitionIdentifierIsTypeName = 0xf200,

        FunctionDefinitionDefaultValueInvalidProperty = 0xf301,

        // --------------------------------------------------------- d*** ...
        // derived errors
        DerivedDefinitionAlreadyUsed = 0xd000,

        DerivedArgumentValueInvalid = 0xda00,  // da** ... derived argment
        DerivedReturnValueInvalid = 0xda01,
        DerivedExpressionInvalidType = 0xde00,  // de** ... derived expression

        DerivedDefinitionIdentifierIsBuiltinName = 0xd100,  // d1** ... derived identifer
        DerivedDefinitionIdentifierIsTypeName = 0xd200,

        DerivedDefinitionExpressionInvalidProperty = 0xdede,

        // --------------------------------------------------------- 5*** ...
        // rule errors

        RuleDefinitionAlreadyUsed = 0x5000,
        RuleDefinitionIdentifierIsBuiltinName = 0x5001,
        RuleDefinitionIdentifierIsTypeName = 0x5002,

        NotSideEffectFreeRuleCall = 0x5100,

        RuleArgumentValueInvalid = 0x5e00  // 5e** ... rule argument
        ,
        RuleArgumentsSizeInvalidAtCall = 0x5e01,
        RuleArgumentsTypeInvalidAtCall = 0x5e02

        ,
        RuleArgumentsSizeInvalidAtIndirectCall = 0x5e04,
        RuleArgumentsTypeInvalidAtIndirectCall = 0x5e05

        ,
        CaseRuleMultipleDefaultCases = 0x5c00  // 5c** ... case errors

        ,
        AssertInvalidExpression = 0x5a00  // 5a** ... assert errors

        ,
        LetAssignedValueInvalid = 0x5d00

        ,
        BuiltinArgumentValueInvalid = 0x5f00

        ,
        ConditionalRuleConditionInvalidProperty = 0x5f01,
        ForallRuleUniverseInvalidProperty = 0x5f02,
        ForallRuleConditionInvalidProperty = 0x5f03,
        ChooseRuleConditionInvalidProperty = 0x5f04,
        UpdateRuleFunctionArgumentInvalidProperty = 0x5f05,
        UpdateRuleUpdateExpressionInvalidProperty = 0x5f06,
        CallRuleArgumentInvalidProperty = 0x5f07

        // --------------------------------------------------------- a*** ...
        // enumeration errors

        ,
        EnumerationDefinitionAlreadyUsed = 0xe000,
        EnumerationDefinitionIdentifierIsBuiltinName = 0xe100,
        EnumerationDefinitionIdentifierIsTypeName = 0xe200,
        EnumeratorDefinitionAlreadyUsed = 0xe001,

        // using errors
        UsingDefinitionAlreadyUsed = 0x6000,
        UsingDefinitionIdentifierIsBuiltinName = 0x6001,
        UsingDefinitionIdentifierIsTypeName = 0x6002,

        // --------------------------------------------------------- a*** ...
        // agent errors

        AgentInitRuleDoesNotExist = 0xa000,
        AgentInitRuleMultipleDefinitions = 0xa001,
        AgentInitRuleNotDefined = 0xa002,

        // type errors
        TypeInvalidProperty = 0x10de,

        // --------------------------------------------------------- 01** ...
        // type annotation errors

        TypeAnnotationInvalidBasicTypeName = 0x0100,
        TypeAnnotationInvalidFixedSizeTypeName = 0x0101,
        TypeAnnotationInvalidComposedTypeName = 0x0102,
        TypeAnnotationInvalidTemplateTypeName = 0x0103,
        TypeAnnotationInvalidRelationTypeName = 0x0104,

        TypeAnnotationTemplateTypeHasNoSubType = 0x0113,
        TypeAnnotationRelationTypeHasNoSubType = 0x0114,

        TypeAnnotationInvalidTemplateTypeSize = 0x0123,

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
        TypeInferenceUpdateRuleFunctionIsBuiltin = 0x1206,

        TypeInferenceNotDefinedForExpression = 0x1300,
        TypeInferenceArgumentTypeMismatch = 0x1301,

        TypeInferenceFunctionArgumentTypeMismatch = 0x1302,
        TypeInferenceFunctionDefaultValueTypeMismatch = 0x1332,

        TypeInferenceDerivedArgumentTypeMismatch = 0x1303,
        TypeInferenceDerivedReturnTypeMismatch = 0x1323,

        TypeInferenceBuiltinArgumentTypeMismatch = 0x1304,
        TypeInferenceBuiltinRelationTypeInvalid = 0x1324,

        TypeInferenceRuleArgumentTypeMismatch = 0x1305,

        TypeInferenceOperatorUnaryRelationTypeInvalid = 0x1306,
        TypeInferenceOperatorBinaryRelationTypeInvalid = 0x1307,

        TypeInferenceQuantifierUniversalPropositionTypeMismatch = 0x1400,
        TypeInferenceQuantifierUniversalPredicateTypeMismatch = 0x1401,
        TypeInferenceQuantifierExistentialPropositionTypeMismatch = 0x1410,
        TypeInferenceQuantifierExistentialPredicateTypeMismatch = 0x1411,

        TypeInferenceConditionalRuleInvalidConditionType = 0x1500,

        TypeInferenceInvalidMethodCallExpression = 0x1900,
        TypeInferenceInvalidLiteralCallExpression = 0x1a00,

        TypeInferenceInvalidExpression = 0x1001,
        TypeInferenceInvalidPrint = 0x1002

        ,
        TypeInferenceInvalidIfExpression = 0x1003,

        TypeInferenceForallVariableHasNoType = 0x1004,
        TypeInferenceForallUniverseHasNoType = 0x1014,
        TypeInferenceForallRuleTypeMismatch = 0x1024,
        TypeInferenceForallRuleInvalidConditionType = 0x1025,
        TypeInferenceForallRuleInvalidUniverseType = 0x1026,

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

        TypeInferenceRangeLiteralTypeMismatch = 0x1600,
        TypeInferenceInvalidListLiteralType = 0x1610,
        TypeInferenceListLiteralTypeMismatch = 0x1611,

        TypeInferenceInvalidTypeCastingExpression = 0x1700,
        TypeInferenceTypeCastingExpressionFromHasNoType = 0x1701,
        TypeInferenceTypeCastingExpressionAsHasInvalidType = 0x1702,

        TypeCheckUseOfUndeclaredFunctionInInitially = 0xc000,

        TypeIntegerRangedInvalidInterval = 0x2000,  // 2*** ... Integer type error

        // --------------------------------------------------------- cc** ...
        // consistency check errors

        UpdateRuleInvalidClassifier = 0xcc00,
        DirectCallExpressionInvalidClassifier = 0xcc01,
        DirectCallExpressionInvalidRelativePath = 0xcc11

        // --------------------------------------------------------- 8*** ...
        // operator errors
        ,
        OperatorAddInvalidOperandType = 0x8000,
        OperatorInvalidOperands = 0x8001

        // --------------------------------------------------------- b*** ...
        // binary type errors
        ,
        TypeBinarySizeIsInvalid = 0xb001

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
        ForallRuleInvalidCondition = 0x9006,

        MethodCallExpressionInvalidBaseExpression = 0x9100,

        // --------------------------------------------------------- fff* ...
        // not categorized errors

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
