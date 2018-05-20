#pragma once

#include "TRL/TRLSL/Token.h"


namespace TRL
{


#define TRLSL_IN_TYPE_DEFAULT_VALUE nullptr

#define TRLSL_RULE_HANDLER(HandlerName) \
virtual RetType HandlerName(InType, \
    InType _1 = TRLSL_IN_TYPE_DEFAULT_VALUE, \
    InType _2 = TRLSL_IN_TYPE_DEFAULT_VALUE, \
    InType _3 = TRLSL_IN_TYPE_DEFAULT_VALUE, \
    InType _4 = TRLSL_IN_TYPE_DEFAULT_VALUE, \
    InType _5 = TRLSL_IN_TYPE_DEFAULT_VALUE, \
    InType _6 = TRLSL_IN_TYPE_DEFAULT_VALUE, \
    InType _7 = TRLSL_IN_TYPE_DEFAULT_VALUE) = 0;

class TRLSLGenerator
{
public:
    virtual ~TRLSLGenerator() = default;


public:
    using RetType = void;
    using InType = Token*;

    TRLSL_RULE_HANDLER(variable_identifier__To__IDENTIFIER)
    TRLSL_RULE_HANDLER(primary_expression__To__variable_identifier)
    TRLSL_RULE_HANDLER(primary_expression__To__INTCONSTANT)
    TRLSL_RULE_HANDLER(primary_expression__To__UINTCONSTANT)
    TRLSL_RULE_HANDLER(primary_expression__To__FLOATCONSTANT)
    TRLSL_RULE_HANDLER(primary_expression__To__BOOLCONSTANT)
    TRLSL_RULE_HANDLER(primary_expression__To__LS___expression___RS)
    TRLSL_RULE_HANDLER(postfix_expression__To__primary_expression)
    TRLSL_RULE_HANDLER(postfix_expression__To__postfix_expression___LM___integer_expression___RM)
    TRLSL_RULE_HANDLER(postfix_expression__To__function_call)
    TRLSL_RULE_HANDLER(postfix_expression__To__postfix_expression___DOT___FIELD_SELECTION)
    TRLSL_RULE_HANDLER(postfix_expression__To__postfix_expression___INC_OP)
    TRLSL_RULE_HANDLER(postfix_expression__To__postfix_expression___DEC_OP)
    TRLSL_RULE_HANDLER(integer_expression__To__expression)
    TRLSL_RULE_HANDLER(function_call__To__function_call_or_method)
    TRLSL_RULE_HANDLER(function_call_or_method__To__function_call_generic)
    TRLSL_RULE_HANDLER(function_call_generic__To__function_call_header_with_parameters___RS)
    TRLSL_RULE_HANDLER(function_call_generic__To__function_call_header_no_parameters___RS)
    TRLSL_RULE_HANDLER(function_call_header_no_parameters__To__function_call_header___VOID)
    TRLSL_RULE_HANDLER(function_call_header_no_parameters__To__function_call_header)
    TRLSL_RULE_HANDLER(function_call_header_with_parameters__To__function_call_header___assignment_expression)
    TRLSL_RULE_HANDLER(function_call_header_with_parameters__To__function_call_header_with_parameters___COMMA___assignment_expression)
    TRLSL_RULE_HANDLER(function_call_header__To__function_identifier___LS)
    TRLSL_RULE_HANDLER(function_identifier__To__type_specifier)
    TRLSL_RULE_HANDLER(function_identifier__To__postfix_expression)
    TRLSL_RULE_HANDLER(unary_expression__To__postfix_expression)
    TRLSL_RULE_HANDLER(unary_expression__To__INC_OP___unary_expression)
    TRLSL_RULE_HANDLER(unary_expression__To__DEC_OP___unary_expression)
    TRLSL_RULE_HANDLER(unary_expression__To__unary_operator___unary_expression)
    TRLSL_RULE_HANDLER(unary_operator__To__PLUS)
    TRLSL_RULE_HANDLER(unary_operator__To__DASH)
    TRLSL_RULE_HANDLER(unary_operator__To__BANG)
    TRLSL_RULE_HANDLER(unary_operator__To__TILDE)
    TRLSL_RULE_HANDLER(multiplicative_expression__To__unary_expression)
    TRLSL_RULE_HANDLER(multiplicative_expression__To__multiplicative_expression___STAR___unary_expression)
    TRLSL_RULE_HANDLER(multiplicative_expression__To__multiplicative_expression___SLASH___unary_expression)
    TRLSL_RULE_HANDLER(multiplicative_expression__To__multiplicative_expression___PERCENT___unary_expression)
    TRLSL_RULE_HANDLER(additive_expression__To__multiplicative_expression)
    TRLSL_RULE_HANDLER(additive_expression__To__additive_expression___PLUS___multiplicative_expression)
    TRLSL_RULE_HANDLER(additive_expression__To__additive_expression___DASH___multiplicative_expression)
    TRLSL_RULE_HANDLER(shift_expression__To__additive_expression)
    TRLSL_RULE_HANDLER(shift_expression__To__shift_expression___LEFT_OP___additive_expression)
    TRLSL_RULE_HANDLER(shift_expression__To__shift_expression___RIGHT_OP___additive_expression)
    TRLSL_RULE_HANDLER(relational_expression__To__shift_expression)
    TRLSL_RULE_HANDLER(relational_expression__To__relational_expression___LEFT_ANGLE___shift_expression)
    TRLSL_RULE_HANDLER(relational_expression__To__relational_expression___RIGHT_ANGLE___shift_expression)
    TRLSL_RULE_HANDLER(relational_expression__To__relational_expression___LE_OP___shift_expression)
    TRLSL_RULE_HANDLER(relational_expression__To__relational_expression___GE_OP___shift_expression)
    TRLSL_RULE_HANDLER(equality_expression__To__relational_expression)
    TRLSL_RULE_HANDLER(equality_expression__To__equality_expression___EQ_OP___relational_expression)
    TRLSL_RULE_HANDLER(equality_expression__To__equality_expression___NE_OP___relational_expression)
    TRLSL_RULE_HANDLER(and_expression__To__equality_expression)
    TRLSL_RULE_HANDLER(and_expression__To__and_expression___AMPERSAND___equality_expression)
    TRLSL_RULE_HANDLER(exclusive_or_expression__To__and_expression)
    TRLSL_RULE_HANDLER(exclusive_or_expression__To__exclusive_or_expression___CARET___and_expression)
    TRLSL_RULE_HANDLER(inclusive_or_expression__To__exclusive_or_expression)
    TRLSL_RULE_HANDLER(inclusive_or_expression__To__inclusive_or_expression___VERTICAL_BAR___exclusive_or_expression)
    TRLSL_RULE_HANDLER(logical_and_expression__To__inclusive_or_expression)
    TRLSL_RULE_HANDLER(logical_and_expression__To__logical_and_expression___AND_OP___inclusive_or_expression)
    TRLSL_RULE_HANDLER(logical_or_expression__To__logical_and_expression)
    TRLSL_RULE_HANDLER(logical_or_expression__To__logical_or_expression___OR_OP___logical_and_expression)
    TRLSL_RULE_HANDLER(conditional_expression__To__logical_or_expression)
    TRLSL_RULE_HANDLER(conditional_expression__To__logical_or_expression___QUESTION___expression___COLON___assignment_expression)
    TRLSL_RULE_HANDLER(assignment_expression__To__conditional_expression)
    TRLSL_RULE_HANDLER(assignment_expression__To__unary_expression___assignment_operator___assignment_expression)
    TRLSL_RULE_HANDLER(assignment_operator__To__EQUAL)
    TRLSL_RULE_HANDLER(assignment_operator__To__MUL_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__DIV_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__MOD_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__ADD_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__SUB_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__LEFT_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__RIGHT_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__AND_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__XOR_ASSIGN)
    TRLSL_RULE_HANDLER(assignment_operator__To__OR_ASSIGN)
    TRLSL_RULE_HANDLER(expression__To__assignment_expression)
    TRLSL_RULE_HANDLER(expression__To__expression___COMMA___assignment_expression)
    TRLSL_RULE_HANDLER(constant_expression__To__conditional_expression)
    TRLSL_RULE_HANDLER(declaration__To__init_declarator_list___SEMICOLON)
    TRLSL_RULE_HANDLER(function_prototype__To__function_declarator___RS)
    TRLSL_RULE_HANDLER(function_declarator__To__function_header)
    TRLSL_RULE_HANDLER(function_declarator__To__function_header_with_parameters)
    TRLSL_RULE_HANDLER(function_header_with_parameters__To__function_header___parameter_declaration)
    TRLSL_RULE_HANDLER(function_header_with_parameters__To__function_header_with_parameters___COMMA___parameter_declaration)
    TRLSL_RULE_HANDLER(function_header__To__fully_specified_type___IDENTIFIER___LS)
    TRLSL_RULE_HANDLER(parameter_declarator__To__type_specifier___IDENTIFIER)
    TRLSL_RULE_HANDLER(parameter_declarator__To__type_specifier___IDENTIFIER___array_specifier)
    TRLSL_RULE_HANDLER(parameter_declaration__To__type_qualifier___parameter_declarator)
    TRLSL_RULE_HANDLER(parameter_declaration__To__parameter_declarator)
    TRLSL_RULE_HANDLER(parameter_declaration__To__type_qualifier___parameter_type_specifier)
    TRLSL_RULE_HANDLER(parameter_declaration__To__parameter_type_specifier)
    TRLSL_RULE_HANDLER(parameter_type_specifier__To__type_specifier)
    TRLSL_RULE_HANDLER(init_declarator_list__To__single_declaration)
    TRLSL_RULE_HANDLER(init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER)
    TRLSL_RULE_HANDLER(init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier)
    TRLSL_RULE_HANDLER(init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier___EQUAL___initializer)
    TRLSL_RULE_HANDLER(init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___EQUAL___initializer)
    TRLSL_RULE_HANDLER(single_declaration__To__fully_specified_type)
    TRLSL_RULE_HANDLER(single_declaration__To__fully_specified_type___IDENTIFIER)
    TRLSL_RULE_HANDLER(single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier)
    TRLSL_RULE_HANDLER(single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier___EQUAL___initializer)
    TRLSL_RULE_HANDLER(single_declaration__To__fully_specified_type___IDENTIFIER___EQUAL___initializer)
    TRLSL_RULE_HANDLER(fully_specified_type__To__type_specifier)
    TRLSL_RULE_HANDLER(fully_specified_type__To__type_qualifier___type_specifier)
    TRLSL_RULE_HANDLER(type_qualifier__To__single_type_qualifier)
    TRLSL_RULE_HANDLER(type_qualifier__To__type_qualifier___single_type_qualifier)
    TRLSL_RULE_HANDLER(single_type_qualifier__To__storage_qualifier)
    TRLSL_RULE_HANDLER(single_type_qualifier__To__precision_qualifier)
    TRLSL_RULE_HANDLER(storage_qualifier__To__CONST)
    TRLSL_RULE_HANDLER(storage_qualifier__To__IN)
    TRLSL_RULE_HANDLER(storage_qualifier__To__OUT)
    TRLSL_RULE_HANDLER(storage_qualifier__To__INOUT)
    TRLSL_RULE_HANDLER(storage_qualifier__To__UNIFORM)
    TRLSL_RULE_HANDLER(type_specifier__To__type_specifier_nonarray)
    TRLSL_RULE_HANDLER(type_specifier__To__type_specifier_nonarray___array_specifier)
    TRLSL_RULE_HANDLER(array_specifier__To__LM___RM)
    TRLSL_RULE_HANDLER(array_specifier__To__LM___constant_expression___RM)
    TRLSL_RULE_HANDLER(array_specifier__To__array_specifier___LM___RM)
    TRLSL_RULE_HANDLER(array_specifier__To__array_specifier___LM___constant_expression___RM)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__VOID)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__FLOAT)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__INT)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__UINT)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__BOOL)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__VEC2)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__VEC3)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__VEC4)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__BVEC2)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__BVEC3)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__BVEC4)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__IVEC2)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__IVEC3)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__IVEC4)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__UVEC2)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__UVEC3)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__UVEC4)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT2)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT3)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT4)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT2X2)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT2X3)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT2X4)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT3X2)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT3X3)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT3X4)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT4X2)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT4X3)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__MAT4X4)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__SAMPLER2D)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__SAMPLER3D)
    TRLSL_RULE_HANDLER(type_specifier_nonarray__To__SAMPLERCUBE)
    TRLSL_RULE_HANDLER(precision_qualifier__To__HIGH_PRECISION)
    TRLSL_RULE_HANDLER(precision_qualifier__To__MEDIUM_PRECISION)
    TRLSL_RULE_HANDLER(precision_qualifier__To__LOW_PRECISION)
    TRLSL_RULE_HANDLER(initializer__To__assignment_expression)
    TRLSL_RULE_HANDLER(declaration_statement__To__declaration)
    TRLSL_RULE_HANDLER(statement__To__compound_statement)
    TRLSL_RULE_HANDLER(statement__To__simple_statement)
    TRLSL_RULE_HANDLER(simple_statement__To__declaration_statement)
    TRLSL_RULE_HANDLER(simple_statement__To__expression_statement)
    TRLSL_RULE_HANDLER(simple_statement__To__selection_statement)
    TRLSL_RULE_HANDLER(simple_statement__To__iteration_statement)
    TRLSL_RULE_HANDLER(simple_statement__To__jump_statement)
    TRLSL_RULE_HANDLER(compound_statement__To__LB___RB)
    TRLSL_RULE_HANDLER(compound_statement__To__LB___statement_list___RB)
    TRLSL_RULE_HANDLER(statement_list__To__statement)
    TRLSL_RULE_HANDLER(statement_list__To__statement_list___statement)
    TRLSL_RULE_HANDLER(expression_statement__To__SEMICOLON)
    TRLSL_RULE_HANDLER(expression_statement__To__expression___SEMICOLON)
    TRLSL_RULE_HANDLER(selection_statement__To__IF___LS___expression___RS___selection_rest_statement)
    TRLSL_RULE_HANDLER(selection_rest_statement__To__statement___ELSE___statement)
    TRLSL_RULE_HANDLER(selection_rest_statement__To__statement)
    TRLSL_RULE_HANDLER(condition__To__expression)
    TRLSL_RULE_HANDLER(condition__To__fully_specified_type___IDENTIFIER___EQUAL___initializer)
    TRLSL_RULE_HANDLER(iteration_statement__To__WHILE___LS___condition___RS___statement)
    TRLSL_RULE_HANDLER(iteration_statement__To__FOR___LS___for_init_statement___for_rest_statement___RS___statement)
    TRLSL_RULE_HANDLER(for_init_statement__To__expression_statement)
    TRLSL_RULE_HANDLER(for_init_statement__To__declaration_statement)
    TRLSL_RULE_HANDLER(condition_opt__To__condition)
    TRLSL_RULE_HANDLER(condition_opt__To__Empty)
    TRLSL_RULE_HANDLER(for_rest_statement__To__condition_opt___SEMICOLON)
    TRLSL_RULE_HANDLER(for_rest_statement__To__condition_opt___SEMICOLON___expression)
    TRLSL_RULE_HANDLER(jump_statement__To__CONTINUE___SEMICOLON)
    TRLSL_RULE_HANDLER(jump_statement__To__BREAK___SEMICOLON)
    TRLSL_RULE_HANDLER(jump_statement__To__RETURN___SEMICOLON)
    TRLSL_RULE_HANDLER(jump_statement__To__RETURN___expression___SEMICOLON)
    TRLSL_RULE_HANDLER(jump_statement__To__DISCARD___SEMICOLON)
    TRLSL_RULE_HANDLER(translation_unit__To__external_declaration_list)
    TRLSL_RULE_HANDLER(external_declaration_list__To__external_declaration)
    TRLSL_RULE_HANDLER(external_declaration_list__To__external_declaration_list___external_declaration)
    TRLSL_RULE_HANDLER(external_declaration__To__function_definition)
    TRLSL_RULE_HANDLER(external_declaration__To__declaration)
    TRLSL_RULE_HANDLER(function_definition__To__function_prototype___compound_statement)

/*
    virtual RetType variable_identifier__To__IDENTIFIER(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType primary_expression__To__variable_identifier(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType primary_expression__To__INTCONSTANT(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType primary_expression__To__UINTCONSTANT(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType primary_expression__To__FLOATCONSTANT(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType primary_expression__To__BOOLCONSTANT(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType primary_expression__To__LS__expression__RS(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType postfix_expression__To__primary_expression(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType postfix_expression__To__postfix_expression__LM__integer_expression__RM(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType postfix_expression__To__function_call(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType postfix_expression__To__postfix_expression__DOT__FIELD_SELECTION(InType, InType, InType, InType, InType, InType, InType, InType) = 0;
    virtual RetType postfix_expression__To__postfix_expression__INC_OP(InType, InType, InType) = 0;
    virtual RetType postfix_expression__To__postfix_expression__DEC_OP(InType, InType, InType) = 0;
    virtual RetType integer_expression__To__expression(InType, InType) = 0;
    virtual RetType function_call__To__function_call_or_method(InType, InType) = 0;
    virtual RetType function_call_or_method__To__function_call_generic(InType, InType) = 0;
    virtual RetType function_call_generic__To__function_call_header_with_parameters__RS(InType, InType, InType) = 0;
    virtual RetType function_call_generic__To__function_call_header_no_parameters__RS(InType, InType, InType) = 0;
    virtual RetType function_call_header_no_parameters__To__function_call_header__VOID(InType, InType, InType) = 0;
    virtual RetType function_call_header_no_parameters__To__function_call_header(InType, InType) = 0;
    virtual RetType function_call_header_with_parameters__To__function_call_header__assignment_expression(InType, InType, InType) = 0;
    virtual RetType function_call_header_with_parameters__To__function_call_header_with_parameters__COMMA__assignment_expression() = 0;
    virtual RetType function_call_header__To__function_identifier__LS() = 0;
    virtual RetType function_identifier__To__type_specifier() = 0;
    virtual RetType function_identifier__To__postfix_expression() = 0;
    virtual RetType unary_expression__To__postfix_expression() = 0;
    virtual RetType unary_expression__To__INC_OP__unary_expression() = 0;
    virtual RetType unary_expression__To__DEC_OP__unary_expression() = 0;
    virtual RetType unary_expression__To__unary_operator__unary_expression() = 0;
    virtual RetType unary_operator__To__PLUS() = 0;
    virtual RetType unary_operator__To__DASH() = 0;
    virtual RetType unary_operator__To__BANG() = 0;
    virtual RetType unary_operator__To__TILDE() = 0;
    virtual RetType multiplicative_expression__To__unary_expression() = 0;
    virtual RetType multiplicative_expression__To__multiplicative_expression__STAR__unary_expression() = 0;
    virtual RetType multiplicative_expression__To__multiplicative_expression__SLASH__unary_expression() = 0;
    virtual RetType multiplicative_expression__To__multiplicative_expression__PERCENT__unary_expression() = 0;
    virtual RetType additive_expression__To__multiplicative_expression() = 0;
    virtual RetType additive_expression__To__additive_expression__PLUS__multiplicative_expression() = 0;
    virtual RetType additive_expression__To__additive_expression__DASH__multiplicative_expression() = 0;
    virtual RetType shift_expression__To__additive_expression() = 0;
    virtual RetType shift_expression__To__shift_expression__LEFT_OP__additive_expression() = 0;
    virtual RetType shift_expression__To__shift_expression__RIGHT_OP__additive_expression() = 0;
    virtual RetType relational_expression__To__shift_expression() = 0;
    virtual RetType relational_expression__To__relational_expression__LEFT_ANGLE__shift_expression() = 0;
    virtual RetType relational_expression__To__relational_expression__RIGHT_ANGLE__shift_expression() = 0;
    virtual RetType relational_expression__To__relational_expression__LE_OP__shift_expression() = 0;
    virtual RetType relational_expression__To__relational_expression__GE_OP__shift_expression() = 0;
    virtual RetType equality_expression__To__relational_expression() = 0;
    virtual RetType equality_expression__To__equality_expression__EQ_OP__relational_expression() = 0;
    virtual RetType equality_expression__To__equality_expression__NE_OP__relational_expression() = 0;
    virtual RetType and_expression__To__equality_expression() = 0;
    virtual RetType and_expression__To__and_expression__AMPERSAND__equality_expression() = 0;
    virtual RetType exclusive_or_expression__To__and_expression() = 0;
    virtual RetType exclusive_or_expression__To__exclusive_or_expression__CARET__and_expression() = 0;
    virtual RetType inclusive_or_expression__To__exclusive_or_expression() = 0;
    virtual RetType inclusive_or_expression__To__inclusive_or_expression__VERTICAL_BAR__exclusive_or_expression() = 0;
    virtual RetType logical_and_expression__To__inclusive_or_expression() = 0;
    virtual RetType logical_and_expression__To__logical_and_expression__AND_OP__inclusive_or_expression() = 0;
    virtual RetType logical_or_expression__To__logical_and_expression() = 0;
    virtual RetType logical_or_expression__To__logical_or_expression__OR_OP__logical_and_expression() = 0;
    virtual RetType conditional_expression__To__logical_or_expression() = 0;
    virtual RetType conditional_expression__To__logical_or_expression__QUESTION__expression__COLON__assignment_expression() = 0;
    virtual RetType assignment_expression__To__conditional_expression() = 0;
    virtual RetType assignment_expression__To__unary_expression__assignment_operator__assignment_expression() = 0;
    virtual RetType assignment_operator__To__EQUAL() = 0;
    virtual RetType assignment_operator__To__MUL_ASSIGN() = 0;
    virtual RetType assignment_operator__To__DIV_ASSIGN() = 0;
    virtual RetType assignment_operator__To__MOD_ASSIGN() = 0;
    virtual RetType assignment_operator__To__ADD_ASSIGN() = 0;
    virtual RetType assignment_operator__To__SUB_ASSIGN() = 0;
    virtual RetType assignment_operator__To__LEFT_ASSIGN() = 0;
    virtual RetType assignment_operator__To__RIGHT_ASSIGN() = 0;
    virtual RetType assignment_operator__To__AND_ASSIGN() = 0;
    virtual RetType assignment_operator__To__XOR_ASSIGN() = 0;
    virtual RetType assignment_operator__To__OR_ASSIGN() = 0;
    virtual RetType expression__To__assignment_expression() = 0;
    virtual RetType expression__To__expression__COMMA__assignment_expression() = 0;
    virtual RetType constant_expression__To__conditional_expression() = 0;
    virtual RetType declaration__To__init_declarator_list__SEMICOLON() = 0;
    virtual RetType function_prototype__To__function_declarator__RS() = 0;
    virtual RetType function_declarator__To__function_header() = 0;
    virtual RetType function_declarator__To__function_header_with_parameters() = 0;
    virtual RetType function_header_with_parameters__To__function_header__parameter_declaration() = 0;
    virtual RetType function_header_with_parameters__To__function_header_with_parameters__COMMA__parameter_declaration() = 0;
    virtual RetType function_header__To__fully_specified_type__IDENTIFIER__LS() = 0;
    virtual RetType parameter_declarator__To__type_specifier__IDENTIFIER() = 0;
    virtual RetType parameter_declarator__To__type_specifier__IDENTIFIER__array_specifier() = 0;
    virtual RetType parameter_declaration__To__type_qualifier__parameter_declarator() = 0;
    virtual RetType parameter_declaration__To__parameter_declarator() = 0;
    virtual RetType parameter_declaration__To__type_qualifier__parameter_type_specifier() = 0;
    virtual RetType parameter_declaration__To__parameter_type_specifier() = 0;
    virtual RetType parameter_type_specifier__To__type_specifier() = 0;
    virtual RetType init_declarator_list__To__single_declaration() = 0;
    virtual RetType init_declarator_list__To__init_declarator_list__COMMA__IDENTIFIER() = 0;
    virtual RetType init_declarator_list__To__init_declarator_list__COMMA__IDENTIFIER__array_specifier() = 0;
    virtual RetType init_declarator_list__To__init_declarator_list__COMMA__IDENTIFIER__array_specifier__EQUAL__initializer() = 0;
    virtual RetType init_declarator_list__To__init_declarator_list__COMMA__IDENTIFIER__EQUAL__initializer() = 0;
    virtual RetType single_declaration__To__fully_specified_type() = 0;
    virtual RetType single_declaration__To__fully_specified_type__IDENTIFIER() = 0;
    virtual RetType single_declaration__To__fully_specified_type__IDENTIFIER__array_specifier() = 0;
    virtual RetType single_declaration__To__fully_specified_type__IDENTIFIER__array_specifier__EQUAL__initializer() = 0;
    virtual RetType single_declaration__To__fully_specified_type__IDENTIFIER__EQUAL__initializer() = 0;
    virtual RetType fully_specified_type__To__type_specifier() = 0;
    virtual RetType fully_specified_type__To__type_qualifier__type_specifier() = 0;
    virtual RetType type_qualifier__To__single_type_qualifier() = 0;
    virtual RetType type_qualifier__To__type_qualifier__single_type_qualifier() = 0;
    virtual RetType single_type_qualifier__To__storage_qualifier() = 0;
    virtual RetType single_type_qualifier__To__precision_qualifier() = 0;
    virtual RetType storage_qualifier__To__CONST() = 0;
    virtual RetType storage_qualifier__To__IN() = 0;
    virtual RetType storage_qualifier__To__OUT() = 0;
    virtual RetType storage_qualifier__To__INOUT() = 0;
    virtual RetType storage_qualifier__To__UNIFORM() = 0;
    virtual RetType type_specifier__To__type_specifier_nonarray() = 0;
    virtual RetType type_specifier__To__type_specifier_nonarray__array_specifier() = 0;
    virtual RetType array_specifier__To__LM__RM() = 0;
    virtual RetType array_specifier__To__LM__constant_expression__RM() = 0;
    virtual RetType array_specifier__To__array_specifier__LM__RM() = 0;
    virtual RetType array_specifier__To__array_specifier__LM__constant_expression__RM() = 0;
    virtual RetType type_specifier_nonarray__To__VOID() = 0;
    virtual RetType type_specifier_nonarray__To__FLOAT() = 0;
    virtual RetType type_specifier_nonarray__To__INT() = 0;
    virtual RetType type_specifier_nonarray__To__UINT() = 0;
    virtual RetType type_specifier_nonarray__To__BOOL() = 0;
    virtual RetType type_specifier_nonarray__To__VEC2() = 0;
    virtual RetType type_specifier_nonarray__To__VEC3() = 0;
    virtual RetType type_specifier_nonarray__To__VEC4() = 0;
    virtual RetType type_specifier_nonarray__To__BVEC2() = 0;
    virtual RetType type_specifier_nonarray__To__BVEC3() = 0;
    virtual RetType type_specifier_nonarray__To__BVEC4() = 0;
    virtual RetType type_specifier_nonarray__To__IVEC2() = 0;
    virtual RetType type_specifier_nonarray__To__IVEC3() = 0;
    virtual RetType type_specifier_nonarray__To__IVEC4() = 0;
    virtual RetType type_specifier_nonarray__To__UVEC2() = 0;
    virtual RetType type_specifier_nonarray__To__UVEC3() = 0;
    virtual RetType type_specifier_nonarray__To__UVEC4() = 0;
    virtual RetType type_specifier_nonarray__To__MAT2() = 0;
    virtual RetType type_specifier_nonarray__To__MAT3() = 0;
    virtual RetType type_specifier_nonarray__To__MAT4() = 0;
    virtual RetType type_specifier_nonarray__To__MAT2X2() = 0;
    virtual RetType type_specifier_nonarray__To__MAT2X3() = 0;
    virtual RetType type_specifier_nonarray__To__MAT2X4() = 0;
    virtual RetType type_specifier_nonarray__To__MAT3X2() = 0;
    virtual RetType type_specifier_nonarray__To__MAT3X3() = 0;
    virtual RetType type_specifier_nonarray__To__MAT3X4() = 0;
    virtual RetType type_specifier_nonarray__To__MAT4X2() = 0;
    virtual RetType type_specifier_nonarray__To__MAT4X3() = 0;
    virtual RetType type_specifier_nonarray__To__MAT4X4() = 0;
    virtual RetType type_specifier_nonarray__To__SAMPLER2D() = 0;
    virtual RetType type_specifier_nonarray__To__SAMPLER3D() = 0;
    virtual RetType type_specifier_nonarray__To__SAMPLERCUBE() = 0;
    virtual RetType precision_qualifier__To__HIGH_PRECISION() = 0;
    virtual RetType precision_qualifier__To__MEDIUM_PRECISION() = 0;
    virtual RetType precision_qualifier__To__LOW_PRECISION() = 0;
    virtual RetType initializer__To__assignment_expression() = 0;
    virtual RetType declaration_statement__To__declaration() = 0;
    virtual RetType statement__To__compound_statement() = 0;
    virtual RetType statement__To__simple_statement() = 0;
    virtual RetType simple_statement__To__declaration_statement() = 0;
    virtual RetType simple_statement__To__expression_statement() = 0;
    virtual RetType simple_statement__To__selection_statement() = 0;
    virtual RetType simple_statement__To__iteration_statement() = 0;
    virtual RetType simple_statement__To__jump_statement() = 0;
    virtual RetType compound_statement__To__LB__RB() = 0;
    virtual RetType compound_statement__To__LB__statement_list__RB() = 0;
    virtual RetType statement_list__To__statement() = 0;
    virtual RetType statement_list__To__statement_list__statement() = 0;
    virtual RetType expression_statement__To__SEMICOLON() = 0;
    virtual RetType expression_statement__To__expression__SEMICOLON() = 0;
    virtual RetType selection_statement__To__IF__LS__expression__RS__selection_rest_statement() = 0;
    virtual RetType selection_rest_statement__To__statement__ELSE__statement() = 0;
    virtual RetType selection_rest_statement__To__statement() = 0;
    virtual RetType condition__To__expression() = 0;
    virtual RetType condition__To__fully_specified_type__IDENTIFIER__EQUAL__initializer() = 0;
    virtual RetType iteration_statement__To__WHILE__LS__condition__RS__statement() = 0;
    virtual RetType iteration_statement__To__FOR__LS__for_init_statement__for_rest_statement__RS__statement() = 0;
    virtual RetType for_init_statement__To__expression_statement() = 0;
    virtual RetType for_init_statement__To__declaration_statement() = 0;
    virtual RetType condition_opt__To__condition() = 0;
    virtual RetType condition_opt__To__Empty() = 0;
    virtual RetType for_rest_statement__To__condition_opt__SEMICOLON() = 0;
    virtual RetType for_rest_statement__To__condition_opt__SEMICOLON__expression() = 0;
    virtual RetType jump_statement__To__CONTINUE__SEMICOLON() = 0;
    virtual RetType jump_statement__To__BREAK__SEMICOLON() = 0;
    virtual RetType jump_statement__To__RETURN__SEMICOLON() = 0;
    virtual RetType jump_statement__To__RETURN__expression__SEMICOLON() = 0;
    virtual RetType jump_statement__To__DISCARD__SEMICOLON__SEMICOLON() = 0;
    virtual RetType translation_unit__To__external_declaration_list() = 0;
    virtual RetType external_declaration_list__To__external_declaration() = 0;
    virtual RetType external_declaration_list__To__external_declaration_list__external_declaration() = 0;
    virtual RetType external_declaration__To__function_definition() = 0;
    virtual RetType external_declaration__To__declaration() = 0;
    virtual RetType function_definition__To__function_prototype__compound_statement() = 0;*/
};


} // end of namespace TRL