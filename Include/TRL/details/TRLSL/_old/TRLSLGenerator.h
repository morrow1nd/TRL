#pragma once

#include "ToyUtility/Container/List.h"
#include "TRL/details/TRLSL/Token.h"


namespace TRL
{


#define TRLSL_IN_TYPE_DEFAULT_VALUE nullptr

#define TRLSL_RULE_HANDLER_DECL(HandlerName)             \
virtual RetType HandlerName(                        \
    InType* _,                                      \
    InType _1 = TRLSL_IN_TYPE_DEFAULT_VALUE,        \
    InType _2 = TRLSL_IN_TYPE_DEFAULT_VALUE,        \
    InType _3 = TRLSL_IN_TYPE_DEFAULT_VALUE,        \
    InType _4 = TRLSL_IN_TYPE_DEFAULT_VALUE,        \
    InType _5 = TRLSL_IN_TYPE_DEFAULT_VALUE,        \
    InType _6 = TRLSL_IN_TYPE_DEFAULT_VALUE,        \
    InType _7 = TRLSL_IN_TYPE_DEFAULT_VALUE) = 0;


class TRLSLGenerator
{
public:
    virtual ~TRLSLGenerator() = default;

    virtual int GetTokenSize() const { return 0; }
    virtual Token* GetToken(int index) { return nullptr; }

    // Used to traversal all tokens
    virtual Token* NextToken(bool restart = false) = 0;

    virtual void SetAllTokens(const ToyUtility::List<Token>& tokens) = 0;


public:
    virtual void SyntaxError() = 0;
    virtual void ParseFailure() = 0;
    virtual void StackOverflow() = 0;
    virtual void ParseAccept() = 0;


    using RetType = void;
    using InType = Token*;

    TRLSL_RULE_HANDLER_DECL(variable_identifier__To__IDENTIFIER)
    TRLSL_RULE_HANDLER_DECL(primary_expression__To__variable_identifier)
    TRLSL_RULE_HANDLER_DECL(primary_expression__To__INTCONSTANT)
    TRLSL_RULE_HANDLER_DECL(primary_expression__To__UINTCONSTANT)
    TRLSL_RULE_HANDLER_DECL(primary_expression__To__FLOATCONSTANT)
    TRLSL_RULE_HANDLER_DECL(primary_expression__To__BOOLCONSTANT)
    TRLSL_RULE_HANDLER_DECL(primary_expression__To__LS___expression___RS)
    TRLSL_RULE_HANDLER_DECL(postfix_expression__To__primary_expression)
    TRLSL_RULE_HANDLER_DECL(postfix_expression__To__postfix_expression___LM___integer_expression___RM)
    TRLSL_RULE_HANDLER_DECL(postfix_expression__To__function_call)
    TRLSL_RULE_HANDLER_DECL(postfix_expression__To__postfix_expression___DOT___FIELD_SELECTION)
    TRLSL_RULE_HANDLER_DECL(postfix_expression__To__postfix_expression___INC_OP)
    TRLSL_RULE_HANDLER_DECL(postfix_expression__To__postfix_expression___DEC_OP)
    TRLSL_RULE_HANDLER_DECL(integer_expression__To__expression)
    TRLSL_RULE_HANDLER_DECL(function_call__To__function_call_or_method)
    TRLSL_RULE_HANDLER_DECL(function_call_or_method__To__function_call_generic)
    TRLSL_RULE_HANDLER_DECL(function_call_generic__To__function_call_header_with_parameters___RS)
    TRLSL_RULE_HANDLER_DECL(function_call_generic__To__function_call_header_no_parameters___RS)
    TRLSL_RULE_HANDLER_DECL(function_call_header_no_parameters__To__function_call_header___VOID)
    TRLSL_RULE_HANDLER_DECL(function_call_header_no_parameters__To__function_call_header)
    TRLSL_RULE_HANDLER_DECL(function_call_header_with_parameters__To__function_call_header___assignment_expression)
    TRLSL_RULE_HANDLER_DECL(function_call_header_with_parameters__To__function_call_header_with_parameters___COMMA___assignment_expression)
    TRLSL_RULE_HANDLER_DECL(function_call_header__To__function_identifier___LS)
    TRLSL_RULE_HANDLER_DECL(function_identifier__To__type_specifier)
    TRLSL_RULE_HANDLER_DECL(function_identifier__To__postfix_expression)
    TRLSL_RULE_HANDLER_DECL(unary_expression__To__postfix_expression)
    TRLSL_RULE_HANDLER_DECL(unary_expression__To__INC_OP___unary_expression)
    TRLSL_RULE_HANDLER_DECL(unary_expression__To__DEC_OP___unary_expression)
    TRLSL_RULE_HANDLER_DECL(unary_expression__To__unary_operator___unary_expression)
    TRLSL_RULE_HANDLER_DECL(unary_operator__To__PLUS)
    TRLSL_RULE_HANDLER_DECL(unary_operator__To__DASH)
    TRLSL_RULE_HANDLER_DECL(unary_operator__To__BANG)
    TRLSL_RULE_HANDLER_DECL(unary_operator__To__TILDE)
    TRLSL_RULE_HANDLER_DECL(multiplicative_expression__To__unary_expression)
    TRLSL_RULE_HANDLER_DECL(multiplicative_expression__To__multiplicative_expression___STAR___unary_expression)
    TRLSL_RULE_HANDLER_DECL(multiplicative_expression__To__multiplicative_expression___SLASH___unary_expression)
    TRLSL_RULE_HANDLER_DECL(multiplicative_expression__To__multiplicative_expression___PERCENT___unary_expression)
    TRLSL_RULE_HANDLER_DECL(additive_expression__To__multiplicative_expression)
    TRLSL_RULE_HANDLER_DECL(additive_expression__To__additive_expression___PLUS___multiplicative_expression)
    TRLSL_RULE_HANDLER_DECL(additive_expression__To__additive_expression___DASH___multiplicative_expression)
    TRLSL_RULE_HANDLER_DECL(shift_expression__To__additive_expression)
    TRLSL_RULE_HANDLER_DECL(shift_expression__To__shift_expression___LEFT_OP___additive_expression)
    TRLSL_RULE_HANDLER_DECL(shift_expression__To__shift_expression___RIGHT_OP___additive_expression)
    TRLSL_RULE_HANDLER_DECL(relational_expression__To__shift_expression)
    TRLSL_RULE_HANDLER_DECL(relational_expression__To__relational_expression___LEFT_ANGLE___shift_expression)
    TRLSL_RULE_HANDLER_DECL(relational_expression__To__relational_expression___RIGHT_ANGLE___shift_expression)
    TRLSL_RULE_HANDLER_DECL(relational_expression__To__relational_expression___LE_OP___shift_expression)
    TRLSL_RULE_HANDLER_DECL(relational_expression__To__relational_expression___GE_OP___shift_expression)
    TRLSL_RULE_HANDLER_DECL(equality_expression__To__relational_expression)
    TRLSL_RULE_HANDLER_DECL(equality_expression__To__equality_expression___EQ_OP___relational_expression)
    TRLSL_RULE_HANDLER_DECL(equality_expression__To__equality_expression___NE_OP___relational_expression)
    TRLSL_RULE_HANDLER_DECL(and_expression__To__equality_expression)
    TRLSL_RULE_HANDLER_DECL(and_expression__To__and_expression___AMPERSAND___equality_expression)
    TRLSL_RULE_HANDLER_DECL(exclusive_or_expression__To__and_expression)
    TRLSL_RULE_HANDLER_DECL(exclusive_or_expression__To__exclusive_or_expression___CARET___and_expression)
    TRLSL_RULE_HANDLER_DECL(inclusive_or_expression__To__exclusive_or_expression)
    TRLSL_RULE_HANDLER_DECL(inclusive_or_expression__To__inclusive_or_expression___VERTICAL_BAR___exclusive_or_expression)
    TRLSL_RULE_HANDLER_DECL(logical_and_expression__To__inclusive_or_expression)
    TRLSL_RULE_HANDLER_DECL(logical_and_expression__To__logical_and_expression___AND_OP___inclusive_or_expression)
    TRLSL_RULE_HANDLER_DECL(logical_or_expression__To__logical_and_expression)
    TRLSL_RULE_HANDLER_DECL(logical_or_expression__To__logical_or_expression___OR_OP___logical_and_expression)
    TRLSL_RULE_HANDLER_DECL(conditional_expression__To__logical_or_expression)
    TRLSL_RULE_HANDLER_DECL(conditional_expression__To__logical_or_expression___QUESTION___expression___COLON___assignment_expression)
    TRLSL_RULE_HANDLER_DECL(assignment_expression__To__conditional_expression)
    TRLSL_RULE_HANDLER_DECL(assignment_expression__To__unary_expression___assignment_operator___assignment_expression)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__EQUAL)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__MUL_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__DIV_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__MOD_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__ADD_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__SUB_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__LEFT_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__RIGHT_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__AND_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__XOR_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(assignment_operator__To__OR_ASSIGN)
    TRLSL_RULE_HANDLER_DECL(expression__To__assignment_expression)
    TRLSL_RULE_HANDLER_DECL(expression__To__expression___COMMA___assignment_expression)
    TRLSL_RULE_HANDLER_DECL(constant_expression__To__conditional_expression)
    TRLSL_RULE_HANDLER_DECL(declaration__To__init_declarator_list___SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(function_prototype__To__function_declarator___RS)
    TRLSL_RULE_HANDLER_DECL(function_declarator__To__function_header)
    TRLSL_RULE_HANDLER_DECL(function_declarator__To__function_header_with_parameters)
    TRLSL_RULE_HANDLER_DECL(function_header_with_parameters__To__function_header___parameter_declaration)
    TRLSL_RULE_HANDLER_DECL(function_header_with_parameters__To__function_header_with_parameters___COMMA___parameter_declaration)
    TRLSL_RULE_HANDLER_DECL(function_header__To__fully_specified_type___IDENTIFIER___LS)
    TRLSL_RULE_HANDLER_DECL(parameter_declarator__To__type_specifier___IDENTIFIER)
    TRLSL_RULE_HANDLER_DECL(parameter_declarator__To__type_specifier___IDENTIFIER___array_specifier)
    TRLSL_RULE_HANDLER_DECL(parameter_declaration__To__type_qualifier___parameter_declarator)
    TRLSL_RULE_HANDLER_DECL(parameter_declaration__To__parameter_declarator)
    TRLSL_RULE_HANDLER_DECL(parameter_declaration__To__type_qualifier___parameter_type_specifier)
    TRLSL_RULE_HANDLER_DECL(parameter_declaration__To__parameter_type_specifier)
    TRLSL_RULE_HANDLER_DECL(parameter_type_specifier__To__type_specifier)
    TRLSL_RULE_HANDLER_DECL(init_declarator_list__To__single_declaration)
    TRLSL_RULE_HANDLER_DECL(init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER)
    TRLSL_RULE_HANDLER_DECL(init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier)
    TRLSL_RULE_HANDLER_DECL(init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___array_specifier___EQUAL___initializer)
    TRLSL_RULE_HANDLER_DECL(init_declarator_list__To__init_declarator_list___COMMA___IDENTIFIER___EQUAL___initializer)
    TRLSL_RULE_HANDLER_DECL(single_declaration__To__fully_specified_type)
    TRLSL_RULE_HANDLER_DECL(single_declaration__To__fully_specified_type___IDENTIFIER)
    TRLSL_RULE_HANDLER_DECL(single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier)
    TRLSL_RULE_HANDLER_DECL(single_declaration__To__fully_specified_type___IDENTIFIER___array_specifier___EQUAL___initializer)
    TRLSL_RULE_HANDLER_DECL(single_declaration__To__fully_specified_type___IDENTIFIER___EQUAL___initializer)
    TRLSL_RULE_HANDLER_DECL(fully_specified_type__To__type_specifier)
    TRLSL_RULE_HANDLER_DECL(fully_specified_type__To__type_qualifier___type_specifier)
    TRLSL_RULE_HANDLER_DECL(type_qualifier__To__single_type_qualifier)
    TRLSL_RULE_HANDLER_DECL(type_qualifier__To__type_qualifier___single_type_qualifier)
    TRLSL_RULE_HANDLER_DECL(single_type_qualifier__To__storage_qualifier)
    TRLSL_RULE_HANDLER_DECL(single_type_qualifier__To__precision_qualifier)
    TRLSL_RULE_HANDLER_DECL(storage_qualifier__To__CONST)
    TRLSL_RULE_HANDLER_DECL(storage_qualifier__To__IN)
    TRLSL_RULE_HANDLER_DECL(storage_qualifier__To__OUT)
    TRLSL_RULE_HANDLER_DECL(storage_qualifier__To__INOUT)
    TRLSL_RULE_HANDLER_DECL(storage_qualifier__To__UNIFORM)
    TRLSL_RULE_HANDLER_DECL(type_specifier__To__type_specifier_nonarray)
    TRLSL_RULE_HANDLER_DECL(type_specifier__To__type_specifier_nonarray___array_specifier)
    TRLSL_RULE_HANDLER_DECL(array_specifier__To__LM___RM)
    TRLSL_RULE_HANDLER_DECL(array_specifier__To__LM___constant_expression___RM)
    TRLSL_RULE_HANDLER_DECL(array_specifier__To__array_specifier___LM___RM)
    TRLSL_RULE_HANDLER_DECL(array_specifier__To__array_specifier___LM___constant_expression___RM)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__STRUCT__IDENTIFIER)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__VOID)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__FLOAT)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__INT)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__UINT)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__BOOL)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__VEC2)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__VEC3)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__VEC4)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__BVEC2)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__BVEC3)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__BVEC4)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__IVEC2)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__IVEC3)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__IVEC4)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__UVEC2)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__UVEC3)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__UVEC4)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT2)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT3)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT4)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT2X2)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT2X3)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT2X4)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT3X2)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT3X3)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT3X4)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT4X2)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT4X3)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__MAT4X4)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__SAMPLER2D)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__SAMPLER3D)
    TRLSL_RULE_HANDLER_DECL(type_specifier_nonarray__To__SAMPLERCUBE)
    TRLSL_RULE_HANDLER_DECL(precision_qualifier__To__HIGH_PRECISION)
    TRLSL_RULE_HANDLER_DECL(precision_qualifier__To__MEDIUM_PRECISION)
    TRLSL_RULE_HANDLER_DECL(precision_qualifier__To__LOW_PRECISION)
    TRLSL_RULE_HANDLER_DECL(initializer__To__assignment_expression)
    TRLSL_RULE_HANDLER_DECL(declaration_statement__To__declaration)
    TRLSL_RULE_HANDLER_DECL(statement__To__compound_statement)
    TRLSL_RULE_HANDLER_DECL(statement__To__simple_statement)
    TRLSL_RULE_HANDLER_DECL(simple_statement__To__declaration_statement)
    TRLSL_RULE_HANDLER_DECL(simple_statement__To__expression_statement)
    TRLSL_RULE_HANDLER_DECL(simple_statement__To__selection_statement)
    TRLSL_RULE_HANDLER_DECL(simple_statement__To__iteration_statement)
    TRLSL_RULE_HANDLER_DECL(simple_statement__To__jump_statement)
    TRLSL_RULE_HANDLER_DECL(compound_statement__To__LB___RB)
    TRLSL_RULE_HANDLER_DECL(compound_statement__To__LB___statement_list___RB)
    TRLSL_RULE_HANDLER_DECL(statement_list__To__statement)
    TRLSL_RULE_HANDLER_DECL(statement_list__To__statement_list___statement)
    TRLSL_RULE_HANDLER_DECL(expression_statement__To__SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(expression_statement__To__expression___SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(selection_statement__To__IF___LS___expression___RS___selection_rest_statement)
    TRLSL_RULE_HANDLER_DECL(selection_rest_statement__To__statement___ELSE___statement)
    TRLSL_RULE_HANDLER_DECL(selection_rest_statement__To__statement)
    TRLSL_RULE_HANDLER_DECL(condition__To__expression)
    TRLSL_RULE_HANDLER_DECL(condition__To__fully_specified_type___IDENTIFIER___EQUAL___initializer)
    TRLSL_RULE_HANDLER_DECL(iteration_statement__To__WHILE___LS___condition___RS___statement)
    TRLSL_RULE_HANDLER_DECL(iteration_statement__To__FOR___LS___for_init_statement___for_rest_statement___RS___statement)
    TRLSL_RULE_HANDLER_DECL(for_init_statement__To__expression_statement)
    TRLSL_RULE_HANDLER_DECL(for_init_statement__To__declaration_statement)
    TRLSL_RULE_HANDLER_DECL(condition_opt__To__condition)
    TRLSL_RULE_HANDLER_DECL(condition_opt__To__Empty)
    TRLSL_RULE_HANDLER_DECL(for_rest_statement__To__condition_opt___SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(for_rest_statement__To__condition_opt___SEMICOLON___expression)
    TRLSL_RULE_HANDLER_DECL(jump_statement__To__CONTINUE___SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(jump_statement__To__BREAK___SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(jump_statement__To__RETURN___SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(jump_statement__To__RETURN___expression___SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(jump_statement__To__DISCARD___SEMICOLON)
    TRLSL_RULE_HANDLER_DECL(translation_unit__To__external_declaration_list)
    TRLSL_RULE_HANDLER_DECL(external_declaration_list__To__external_declaration)
    TRLSL_RULE_HANDLER_DECL(external_declaration_list__To__external_declaration_list___external_declaration)
    TRLSL_RULE_HANDLER_DECL(external_declaration__To__function_definition)
    TRLSL_RULE_HANDLER_DECL(external_declaration__To__declaration)
    TRLSL_RULE_HANDLER_DECL(external_declaration__To__struct_definition)
    TRLSL_RULE_HANDLER_DECL(function_definition__To__function_prototype___compound_statement)
    TRLSL_RULE_HANDLER_DECL(declaration_list__To__declaration)
    TRLSL_RULE_HANDLER_DECL(declaration_list__To__declaration_list__declaration)
    TRLSL_RULE_HANDLER_DECL(struct_definition__To__STRUCT__IDENTIFIER__LB__declaration_list__RB__SEMICOLON)
};


} // end of namespace TRL