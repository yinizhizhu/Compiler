// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include <stdio.h>
// TODO:  在此处引用程序需要的其他头文件
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "state.h"
#include "lrTable.h"
#include "nonTerminal.h"

#define KEY_COL 200	//1~199
#define KEY_LENGTH 42

char key[KEY_COL][KEY_LENGTH] = { "",
	"AND", "ARRAY", "ASSIGNMENT", "CASE", "CHARACTER_STRING",
	"COLON", "COMMA", "CONST", "DIGSEQ", "DIV",
	"DO", "DOT", "DOTDOT", "DOWNTO", "ELSE",
	"END", "EQUAL", "EXTERNAL", "FOR", "FORWARD",
	"FUNCTION", "GE", "GOTO", "GT", "IDENTIFIER",
	"IF", "IN", "LABEL", "LBRAC", "LE", "LPAREN",
	"LT", "MINUS", "MOD", "NIL", "NOT", "NOTEQUAL",
	"OF", "OR", "OTHERWISE", "PACKED", "PBEGIN", "PFILE",
	"PLUS", "PROCEDURE", "PROGRAM", "RBRAC", "REALNUMBER",
	"RECORD", "REPEAT", "RPAREN", "SEMICOLON", "SET", "SLASH",
	"STAR", "STARSTAR", "THEN", "TO", "TYPE", "UNTIL",
	"UPARROW", "VAR", "WHILE", "WITH", "$", "file", "program",
	"module", "program_heading", "semicolon", "block", "identifier",
	"identifier_list", "comma", "label_declaration_part",
	"constant_definition_part", "type_definition_part", "variable_declaration_part",
	"procedure_and_function_declaration_part", "statement_part",
	"label_list", "label", "constant_list", "constant_definition",
	"cexpression", "constant", "csimple_expression", "relop", "cterm",
	"addop", "cfactor", "mulop", "sign", "cexponentiation", "cprimary",
	"unsigned_constant", "non_string", "type_definition_list",
	"type_definition", "type_denoter", "new_type", "new_ordinal_type",
	"new_structured_type", "new_pointer_type", "enumerated_type",
	"subrange_type", "structured_type", "array_type", "record_type",
	"set_type", "file_type", "index_list", "component_type", "index_type",
	"ordinal_type", "record_section_list", "variant_part", "record_section",
	"variant_selector", "variant_list", "tag_field", "tag_type", "variant",
	"case_constant_list", "case_constant", "base_type", "domain_type",
	"variable_declaration_list", "variable_declaration", "proc_or_func_declaration_list",
	"proc_or_func_declaration", "procedure_declaration", "function_declaration",
	"procedure_heading", "directive", "procedure_block", "procedure_identification",
	"formal_parameter_list", "formal_parameter_section_list", "formal_parameter_section",
	"value_parameter_specification", "variable_parameter_specification",
	"procedural_parameter_specification", "functional_parameter_specification",
	"function_heading", "function_identification", "function_block", "result_type",
	"compound_statement", "statement_sequence", "statement", "open_statement",
	"closed_statement", "non_labeled_open_statement", "non_labeled_closed_statement",
	"assignment_statement", "procedure_statement", "goto_statement", "case_statement",
	"repeat_statement", "closed_with_statement", "closed_if_statement",
	"closed_while_statement", "closed_for_statement", "open_with_statement",
	"open_if_statement", "open_while_statement", "open_for_statement",
	"boolean_expression", "control_variable", "initial_value", "direction",
	"final_value", "record_variable_list", "variable_access", "expression",
	"indexed_variable", "field_designator", "index_expression_list",
	"index_expression", "params", "actual_parameter_list", "actual_parameter",
	"case_index", "case_list_element_list", "otherwisepart", "case_list_element",
	"simple_expression", "term", "factor", "exponentiation", "primary",
	"function_designator", "set_constructor", "unsigned_number", "unsigned_integer",
	"unsigned_real", "member_designator_list", "member_designator" };

void control();		//control the shift-reduce-accpet
int getIndex(char* token);		//return the col of the token in the table
void shift(int index, char* token);		//shift, Just shift the token into the table
bool reduce(int index);		//reduce
bool go(char* token);			//goto the next state
bool error(char* info);
void testKey();

FILE* out;