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

char assignment[5][KEY_LENGTH] = { "assignment_statement", "->", "variable_access", "ASSIGNMENT", "expression" };
char relop[5][KEY_LENGTH] = { "expression", "->", "simple_expression", "relop", "simple_expression" };//for operator '>'
char ifStatement[8][KEY_LENGTH] = { "closed_if_statement", "->", "IF", "boolean_expression", "THEN", "closed_statement", "ELSE", "closed_statement" };
char addop[5][KEY_LENGTH] = { "simple_expression", "->", "simple_expression", "addop", "term" };//for operator '+'
char forto[3][KEY_LENGTH] = { "variable_access", "->", "identifier" };
char forStatement[10][KEY_LENGTH] = { "closed_for_statement", "->", "FOR", "control_variable", "ASSIGNMENT", "initial_value", "direction", "final_value", "DO", "closed_statement" };
static int tag = 0;

int getIndex(char* word)		//return the col of the word in the table
{
	int i = 1;
	for (; i < 200; i++)
		if (strcmp(word, key[i]) == 0)
			return i;
	return -1;
}

void shift(int index, char* word)		//shift, Just shift the word into the table
{
	int x = topStates();

	fprintf(out, "shift %s\n", getContainer(x, index)[0]); //container[0], word

	pushStates(atoi(getContainer(x, index)[0]));
	pushNames(word);
	//printf("The size of states: %d, %d, the size of names: %d, %s\n", sizeStates(), topStates(), sizeNames(), topNames());
	return;
}

void assignmentT(int x, int y, char** container)
{
	int i;
	for (i = 0; i < 5; i++)
		if (strcmp(container[i], assignment[i]) != 0)
			break;
	if (i == 5)
	{
		printf("assignmentT\n");
		showQueue();
		token *head = frontQueue();
		if (tag == 1)
			insertThreeAddress(0, head->next->value, ":=", head->value);
		else
			pushStatement(0, head->next->value, ":=", head->value);
		for (int i = 0; i < 2; i++)
			popQueue();
		showQueue();
		showThreeAddress();
		showStatement();
	}
	return;
}

void relopT(int x, int y, char** container)
{
	int i;
	for (i = 0; i < 5; i++)
		if (strcmp(container[i], relop[i]) != 0)
			break;
	if (i == 5)
	{
		printf("relopT\n");
		showQueue();
		token *head = frontQueue();
		if (tag == 1)
			insertThreeAddress(5, head->next->value, ">", head->value);
		else
			pushStatement(5, head->next->value, ">", head->value);
		for (int i = 0; i < 2; i++)
			popQueue();
		showQueue();
		showThreeAddress();
		showStatement();
	}
	return;
}

void addopT(int x, int y, char** container)
{
	int i;
	for (i = 0; i < 5; i++)
		if (strcmp(container[i], addop[i]) != 0)
			break;
	if (i == 5)
	{
		printf("addopT\n");
		showQueue();
		token *head = frontQueue();
		if (tag == 1)
			insertThreeAddress(1, head->next->value, head->next->next->value, head->value);
		else
			pushStatement(1, head->next->value, head->next->next->value, head->value);
		for (int i = 0; i < 3; i++)
			popQueue();
		showQueue();
		showThreeAddress();
		showStatement();
	}
	return;
}

void ifT(int x, int y, char** container)
{
	int i;
	for (i = 0; i < 8; i++)
		if (strcmp(container[i], ifStatement[i]) != 0)
			break;
	if (i == 8)
	{
		printf("ifT\n");
		addressCode *head = frontStatement();
		insertThreeAddressP(head);
		tag = 1;
	}
	return;
}

void fortoT(int x, int y, char** container)
{
	int i;
	for (i = 0; i < 3; i++)
		if (strcmp(container[i], forto[i]) != 0)
			break;
	if (i == 10)
	{
		printf("fortoT\n");
		showQueue();
		token *head = frontQueue();
		pushStatement(1, head->value, "<=", "i");
		for (int i = 0; i < 1; i++)
			popQueue();
		showQueue();
		showThreeAddress();
		showStatement();
	}
	return;
}

void forT(int x, int y, char** container)
{
	int i;
	for (i = 0; i < 10; i++)
		if (strcmp(container[i], forStatement[i]) != 0)
			break;
	if (i == 10)
	{
		printf("forT\n");
		addressCode *head = frontStatement();
		insertThreeAddressP(head);
		tag = 1;
	}
	return;
}

void translate(int x, int y, char** container)
{
	switch (tag)
	{
	case 0:
		break;
	case 1:	//assignment
		if (getNum(x, y) == 5)
		{
			assignmentT(x, y, container);	// a := 2, b := 3=
			addopT(x, y, container);
		}
		break;
	case 2:	//if statement
		if (getNum(x, y) == 5)
			relopT(x, y, container);
		break;
	case 3://then statement
		if (getNum(x, y) == 5)
		{
			assignmentT(x, y, container);
			addopT(x, y, container);
		}
		break;
	case 4://else statement
		if (getNum(x, y) == 8)
			ifT(x, y, container);
		else if (getNum(x, y) == 5)
		{
			assignmentT(x, y, container);
			addopT(x, y, container);
		}
		break;
	case 5:	//for statement
		if (getNum(x, y) == 5)
			assignmentT(x, y, container);
		break;
	case 6:
		if (getNum(x, y) == 3)
			fortoT(x, y, container);
		break;
	case 7:
		if (getNum(x, y) == 10)
			forT(x, y, container);
		else if (getNum(x, y) == 5)
		{
			assignmentT(x, y, container);
			addopT(x, y, container);
		}
		break;
	default:
		break;
	}
	return;
}

bool reduce(int index)		//reduce
{
	int i;
	int x = topStates(), y = index;
	char** container = getContainer(x, y);

	translate(x, y, container);	//translate according to the process of reducing

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

bool go(char* word)			//goto the next state
{
	int x, y;
	x = topStates();
	y = getIndex(word);
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

void setTag(char* word)
{
	if (tag == 0)	//set the starter of the threeAddress
	{
		if (strcmp(word, "PBEGIN") == 0)
			tag = 1;
	}
	else
	{
		switch (tag)
		{
		case 1:
			if (strcmp(word, "IF") == 0)
			{
				popQueue();
				initStatement();
				tag = 2;
			}
			else if (strcmp(word, "FOR") == 0)
			{
				popQueue();
				initStatement();
				tag = 5;
			}
			break;
		case 2:
			if (strcmp(word, "THEN") == 0)
			{
				popQueue();
				tag = 3;
			}
			break;
		case 3:
			if (strcmp(word, "ELSE") == 0)
			{
				popQueue();
				tag = 4;
			}
			break;
		case 4:
			break;
		case 5:
			if (strcmp(word, "TO") == 0)
			{
				popQueue();
				tag = 6;
			}
			break;
		case 6:
			if (strcmp(word, "DO") == 0)
			{
				popQueue();
				tag = 7;
			}
			break;
		case 7:
			break;
		default:
			break;
		}
	}
	//printf("setTag: %s\n", word);
	return;
}

bool control()		//control the shift-reduce-accpet
{
	int x, y, s;
	FILE* fp = fopen("inputSyn.txt", "r");
	char word[KEY_LENGTH];
	while (fscanf(fp, "%s", word) == 1)
	{
	REP:
		fprintf(out, "\nThe input word is: %s\n", word);
		//printf("The input word is: %s\n", word);
		x = topStates();
		y = getIndex(word);
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
				REP;	//we keep this word to continue to judge
		}
		else if (s == 2)	//shift the word
			shift(y, word);
		else		//the state is wrong for 3, no need to go to the next state
		{
			fprintf(out, "Syntax error: state equal 3, but no need to goto!\n");
			fclose(fp);
			return false;
		}
		setTag(word);
	}
	printf("The last step!\n");
	strcpy(word, "$");
	y = getIndex(word);
	while (sizeStates() > 1)
	{
		fprintf(out, "\nThe input word is: %s\n", word);
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