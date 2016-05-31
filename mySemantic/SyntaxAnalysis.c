#include "SyntaxAnalysis.h"

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

int getIndex(char* token)		//return the col of the token in the table
{
	int i = 1;
	for (; i < 200; i++)
		if (strcmp(token, key[i]) == 0)
			return i;
	return -1;
}

void shift(int index, char* token)		//shift, Just shift the token into the table
{
	int x = topStates();

	fprintf(out, "shift %s\n", getContainer(x, index)[0]); //container[0], token

	pushStates(atoi(getContainer(x, index)[0]));
	pushNames(token);
	//printf("The size of states: %d, %d, the size of names: %d, %s\n", sizeStates(), topStates(), sizeNames(), topNames());
	return;
}

bool reduce(int index)		//reduce
{
	int i;
	int x = topStates(), y = index;
	char** container = getContainer(x, y);

	fprintf(out, "reduce ");
	for (i = 0; i < getNum(x, y); i++) //output the production
		fprintf(out, "%s ", container[i]);
	fprintf(out, "\n");

	if (strcmp(container[2], EMPTY) != 0)	//the production contain the nonempty string
	{
		for (i = (getNum(x, y) - 1); i >= 2; i--)		//process of reducing
		{
			if (strcmp(topNames(), container[i]) == 0)
			{
				if (sizeNames() == 0)
					return synError("the stack is empty");
				popNames();
				popStates();
			}
			else
				return synError("no matching string bettween stack and production");
		}
	}
	pushNames(container[0]);
	return go(container[0]);
}

bool go(char* token)			//goto the next state
{
	int x, y;
	x = topStates();
	y = getIndex(token);
	if (getS(x, y) == 3)	//the action of goto
	{
		if (getNum(x, y) != -1)		//right for the goto
		{
			pushStates(getNum(x, y));
			return true;
		}
		return synError("the position is null in goto table");
	}
	else	//the state is not goto
		return synError("the state is not 3 for goto");
}

bool synError(char* info)
{
	fprintf(out, "Syntax error: %s!\n", info);
	return false;
}

bool control()		//control the shift-reduce-accpet
{
	int x, y, s;
	FILE* fp = fopen("inputSyn.txt", "r");
	char token[KEY_LENGTH];
	while (fscanf(fp, "%s", token) == 1)
	{
	REP:
		fprintf(out, "\nThe input token is: %s\n", token);
		x = topStates();
		y = getIndex(token);
		if (y < 0)
		{
			fprintf(out, "Syntax error!\n");
			fclose(fp);
			return false;
		}
		s = getS(x, y);
		showNamesFile(out);
		showStatesFile(out);
		if (s == -1)	//error
		{
			fprintf(out, "Syntax error: action is wrong!\n");
			fclose(fp);
			return false;
		}
		else if (s == 0)	//error accept
		{
			fprintf(out, "ACCEPT before end! Syntax error\n");
			fclose(fp);
			return false;
		}
		else if (s == 1)	//reduce the production
		{
			if (!reduce(y))
			{
				fprintf(out, "Reduce is error!\n");
				fclose(fp);
				return false;
			}
			goto
				REP;	//we keep this token to continue to judge
		}
		else if (s == 2)	//shift the token
			shift(y, token);
		else		//the state is wrong for 3, no need to go to the next state
		{
			fprintf(out, "Syntax error: state equal 3, but no need to goto!\n");
			fclose(fp);
			return false;
		}
	}
	printf("The last step!\n");
	strcpy(token, "$");
	y = getIndex(token);
	while (sizeStates() > 1)
	{
		fprintf(out, "\nThe input token is: %s\n", token);
		x = topStates();
		s = getS(x, y);
		showNamesFile(out);
		showStatesFile(out);
		if (s == 0)
		{
			printf("The program is correct!\nACCEPT!\n");
			fprintf(out, "ACCEPT!\n");
			return true;
		}
		else if (s == 1)
		{
			if (!reduce(y))
			{
				fprintf(out, "Reduce is error!\n");
				fclose(fp);
				return false;
			}
		}
		else
		{
			fprintf(out, "Syntax error!\n");
			return false;
		}
	}
	fclose(fp);
	printf("The program is correct!\nACCEPT!\n");
	fprintf(out, "ACCEPT!\n");
	return true;
}

void testKey()
{
	int j;
	for (j = 0; j < 66; j++)
		if (getNum(7, j) > 0)
			printf("%s %d: %d\n", key[j], j, getNum(7, j));
	printf("\n");
}