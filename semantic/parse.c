#include "parse.h"

char token[20], value[40];				//token, the value of the token
char ScanoutIn[300] = "syntaxResult.txt";
char Codeout[300] = "result.txt";		//Store the middle codes
FILE *fp, *fout;

struct{
	char name[8];
	int address;
} vartable[maxvartablep]; //The structure of symbol table with the 500 sizes

int vartablep = 0;	//The total number of iterms stored
int labelp = 0;
int datap = 0;		//The pointer of data

int name_def(char *name)//Insert into the symbol table: @name-def¡ýn, t
{
	int i;
	if (vartablep >= maxvartablep)
		return 21;		//21 - 'Overflow in the symbol table'

	for (i = vartablep - 1; i >= 0; i--)
		if (strcmp(vartable[i].name, name) == 0)
			return 22;	//22 - 'The redefination of variable'

	strcpy(vartable[vartablep].name, name);
	vartable[vartablep].address = datap;
	vartablep++;

	datap++;	//The pointer of data add 1
	return 0;	//0 - 'No error'
}

int lookup(char *name, int *paddress)//Return address while checking in the symbol table
{
	int i;
	for (i = 0; i<vartablep; i++)
		if (strcmp(vartable[i].name, name) == 0)
		{
			*paddress = vartable[i].address;
			return 0;	//0 - 'No error'
		}
	return 23;			//23 - 'No defination of the variable'
}

int parse()//LexAnalysis, SyntaxAnalysis and ProducingMiddleCodes
{
	int es = 0;
	if ((fp = fopen(ScanoutIn, "r")) == NULL)
	{
		printf("\nCannot open the file \"%s\"!\n", ScanoutIn);
		return 10;//10 - 'Cannot open the file'
	}
	printf("The middle code is in the file: %s\n", Codeout);

	if ((fout = fopen(Codeout, "w")) == NULL)
	{
		printf("\nCannot create the file \"%s\"!\n", Codeout);
		return 10;//10 - 'Cannot create the file'
	}

	es = program();
	printf("==The result Lex, Syn and Pro==\n");
	switch (es)
	{
	case 0: printf("Successed to produce the asm code!\n"); break;
	case 1: printf("Less for {!\n"); break;
	case 2: printf("Less for }!\n"); break;
	case 3: printf("Less for Identifer!\n"); break;
	case 4: printf("Less for ;!\n"); break;
	case 5: printf("Less for (!\n"); break;
	case 6: printf("Less for )!\n"); break;
	case 7: printf("Less for operator!\n"); break;
	case 10: printf("Cannot open or create file!\n"); break;
	case 21: printf("Overflow for symbol table!\n"); break;
	case 22: printf("Redefination of variable!\n"); break;
	case 23: printf("No defination of variable!\n"); break;
	default: printf("No match code for this error code!\n"); break;
	}
	fclose(fp);
	fclose(fout);
	return es;		//0 - 'No error'
}

void readNext()//Read the next pair< token, value >
{
	fscanf(fp, "%s %s\n", token, value);
	printf("%s %s\n", token, value);
	return;
}

int program()//program::={<declaration_list><statement_list>}
{
	int es = 0, i;

	readNext();
	if (strcmp(token, "{"))//Judege the '{'
		return 1;
	readNext();

	es = declaration_list();
	if (es)
		return es;

	printf("     Symbol Table\n");
	printf("     NAME       ADDRESS\n");
	for (i = 0; i < vartablep; i++)
		printf("      %s   %d\n", vartable[i].name, vartable[i].address);

	es = statement_list();
	if (es)
		return es;

	if (strcmp(token, "}"))//Judge the '}'
		return 2;
	fprintf(fout, "        STOP\n");//²úÉúÍ£Ö¹Ö¸Áî
	return 0;
}

//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
int declaration_list()//get into <declaration_list>::={<declaration_stat>}
{
	int es = 0;
	while (strcmp(token, "int") == 0)
	{
		es = declaration_stat();
		if (es)
			return es;
	}
	return 0;
}

int declaration_stat()//<declaration_stat>¡ývartablep,datap,codep ->int ID¡ün@name-def¡ýn,t;
{
	int es = 0;
	readNext();
	if (strcmp(token, "ID"))
		return 3;  //3 - 'Not Identifier'
	es = name_def(value);//Insert into the symbol table
	if (es)
		return es;
	readNext();
	if (strcmp(token, ";"))
		return 4;	//4 - 'Less for ;'
	readNext();
	return 0;
}

//<statement_list>::=<statement_list><statement>|<statement>
int statement_list()//get into <statement_list>::={<statement>}
{
	int es = 0;
	while (strcmp(token, "}"))
	{
		es = statement();
		if (es)
			return es;
	}
	return 0;
}

int statement()//<statement>::= <if_stat>|<while_stat>|<for_stat>|<compound_stat> |<expression_stat>
{
	int es = 0;
	if (es == 0 && strcmp(token, "if") == 0) es = if_stat();//<IF>
	if (es == 0 && strcmp(token, "while") == 0) es = while_stat();//<while>
	if (es == 0 && strcmp(token, "do") == 0) es = do_stat();//<do_while>
	if (es == 0 && strcmp(token, "for") == 0) es = for_stat();//<for>
	if (es == 0 && strcmp(token, "read") == 0) es = read_stat();//<read>
	if (es == 0 && strcmp(token, "write") == 0) es = write_stat();//<write>
	if (es == 0 && strcmp(token, "{") == 0) es = compound_stat();//<Compound>
	if (es == 0 && (strcmp(token, "ID") == 0 || strcmp(token, "NUM") == 0)) es = expression_stat();//<Operation>
	return es;
}

//<IF_stat>::= if (<expr>) <statement > [else < statement >]
/*
if (<expression>)@BRF¡ülabel1 <statement > @BR¡ülabel2 @SETlabel¡ýlabel1
[ else < statement >] @SETlabel¡ýlabel2
@BRF¡ülabel1 £ºoutput BRF label1,
@BR¡ülabel2£ºoutput BR label2,
@SETlabel¡ýlabel1£ºset label1
@SETlabel¡ýlabel2£ºset label2
*/
int if_stat()
{
	int es = 0, label1, label2;  //if
	readNext();
	if (strcmp(token, "("))
		return 5;//5 - 'Less for ('
	readNext();

	es = expression();
	if (es)
		return es;

	if (strcmp(token, ")"))
		return 6; //6 - 'Less for )'

	label1 = labelp++;//set label1: the destination with false conditional jump
	fprintf(fout, "        BRF LABEL%d\n", label1);//output false conditional jump order
	readNext();
	es = statement();
	if (es)
		return es;
	label2 = labelp++;//set label2: the destination we jump
	fprintf(fout, "        BR LABEL%d\n", label2);//output jump order
	fprintf(fout, "LABEL%d:\n", label1);//set label1
	if (strcmp(token, "else") == 0)//else
	{
		readNext();
		es = statement();
		if (es)
			return es;
	}
	fprintf(fout, "LABEL%d:\n", label2);//set label2
	return 0;
}

//<do_while_stat>::=do<statement>while(<exper>)
//<do_while_stat>::=do @SET¡ülabellabel1<statement>
//                  while(<expression>)
//                  @BRF¡ülabel2@BR¡ülabel1@SETlabel¡ýlabel2
//@SETlabel¡ülabel1£ºset label1
//@BRF¡ülabel2 £ºoutput BRF label2,
//@BR¡ýlabel1£ºoutput BR label1,
//@SETlabel¡ýlabel2£ºset label2
int do_stat()
{
	int es, label1, label2;
	es = 0;
	label1 = labelp++;
	fprintf(fout, "LABEL%d:\n", label1);//set label1
	readNext();
	es = statement();
	if (es)
		return es;
	readNext();
	if (strcmp(token, "while") == 0)//while
	{
		readNext();
		if (strcmp(token, "("))
			return 5;//5 - 'Less for ('
		readNext();
		es = expression();
		if (es)
			return es;
		if (strcmp(token, ")"))
			return 6;//6 - 'Less for )'
	}
	else
		printf("Less for while");
	label2 = labelp++;
	fprintf(fout, "        BRF LABEL%d\n", label2);//output false conditional jump order
	fprintf(fout, "        BR LABEL%d\n", label1);//output jump order
	fprintf(fout, "LABEL%d:\n", label2);//set label2
	readNext();
	return 0;
}

//<while_stat>::= while (<expr >) < statement >
//<while_stat>::=while @SET¡ülabellabel1(<expression>) @BRF¡ülabel2 
//				<statement >@BR¡ýlabel1 @SETlabel¡ýlabel2
//@SETlabel¡ülabel1£ºset label1
//@BRF¡ülabel2 £ºoutput BRF label2,
//@BR¡ýlabel1£ºoutput BR label1,
//@SETlabel¡ýlabel2£ºset label2
int while_stat()
{
	int es = 0, label1, label2;
	label1 = labelp++;
	fprintf(fout, "LABEL%d:\n", label1);//set label1
	readNext();
	if (strcmp(token, "("))
		return 5;//5 - 'Less for ('
	readNext();
	es = expression();
	if (es)
		return es;
	if (strcmp(token, ")"))
		return 6;//6 - 'Less for )'
	label2 = labelp++;
	fprintf(fout, "        BRF LABEL%d\n", label2);//output the false conditional jump order
	readNext();
	es = statement();
	if (es)
		return es;
	fprintf(fout, "        BR LABEL%d\n", label1);//output jump order
	fprintf(fout, "LABEL%d:\n", label2);//set label2
	readNext();
	return 0;
}

//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
/*
<for_stat>::=for (<expression>;
@SETlabel¡ülabel1< expression >@BRF¡ülabel2@BR¡ülabel3;
@SETlabel¡ülabel4 < expression >@BR¡ýlabel1)
@SETlabel¡ýlabel3 <sentence >@BR¡ýlabel4@SETlabel¡ýlabel2
1.	@SETlabel¡ýlabel1£ºset label1
2.	@BRF¡ülabel2 £ºoutput BRF label2,
3.	@BR¡ülabel3£ºoutput BR label3,
4.	@SETlabel¡ýlabel4£ºset label4
5.	@BR¡ülabel1£ºoutput BR label1,
6.	@SETlabel¡ýlabel3£ºset label3
7.	@BR¡ülabel4£ºoutput BR label4,
8.	@SETlabel¡ýlabel2£ºset label2
*/
int for_stat()
{
	int es = 0, label1, label2, label3, label4;
	readNext();
	if (strcmp(token, "("))
		return 5;//5 - 'Less for ('
	readNext();
	es = expression();
	if (es)
		return es;
	if (strcmp(token, ";"))
		return 4;//4 - 'Less for ;'
	label1 = labelp++;
	fprintf(fout, "LABEL%d:\n", label1);//set label1
	readNext();
	es = expression();
	if (es)
		return es;
	label2 = labelp++;
	fprintf(fout, "        BRF LABEL%d\n", label2);//output the false conditional jump order
	label3 = labelp++;
	fprintf(fout, "        BR LABEL%d\n", label3);//output jump order
	if (strcmp(token, ";"))
		return 4;//4 - 'Less for ;'
	label4 = labelp++;
	fprintf(fout, "LABEL%d:\n", label4);//set label4
	readNext();
	es = expression();
	if (es)
		return es;
	fprintf(fout, "        BR LABEL%d\n", label1);//output jump order
	if (strcmp(token, ")"))
		return 6;//6 - 'Less for )'
	fprintf(fout, "LABEL%d:\n", label3);//set label3
	readNext();
	es = statement();
	if (es)
		return es;
	fprintf(fout, "        BR LABEL%d\n", label4);//output jump order
	fprintf(fout, "LABEL%d:\n", label2);//set label2
	return 0;
}

//<write_stat>::=write <expression>;
//<write_stat>::=write <expression>@OUT;
//@ OUT£ºoutput OUT
int write_stat()
{
	int es = 0;
	readNext();
	es = expression();
	if (es)
		return es;
	if (strcmp(token, ";"))
		return 4;//4 - 'Less for ;'
	fprintf(fout, "        OUT\n");//output the order
	readNext();
	return 0;
}

//<read_stat>::=read ID;
//<read_stat>::=read ID¡ün LOOK¡ýn¡üd @IN@STI¡ýd;
//@LOOK¡ýn¡üd:check n in symbol table, and d store the address
//@IN£ºinput----IN
//@STI¡ýd£ºOput the asm code----STI  d
int read_stat()
{
	int es = 0, address;
	readNext();
	if (strcmp(token, "ID"))
		return 3;//3 - 'Less for Identifier'
	es = lookup(value, &address);
	if (es)
		return es;
	fprintf(fout, "        IN   \n");//output the order
	fprintf(fout, "        STI   %d\n", address);//output the order
	readNext();
	if (strcmp(token, ";"))
		return 4;//4 - 'Less for ;'
	readNext();
	return 0;
}

int compound_stat()//<compound_stat>::={<statement_list>} 
{
	readNext();
	return statement_list();
}

int expression_stat()//<expression_stat>::=<expression>;|;
{
	int es = 0;
	if (strcmp(token, ";") == 0)
	{
		readNext();
		return 0;
	}
	es = expression();
	if (es)
		return es;
	if (strcmp(token, ";") == 0)
		readNext();
	else
		es = 4;//4 - 'Less for ;'
	return es;
}

int expression()//<expression>::=ID¡ün@LOOK¡ýn¡üd@ASSIGN=<bool_expr>@STO¡ýd |<bool_expr>
{
	int es = 0, fileadd;
	char token2[20], token3[40];
	if (strcmp(token, "ID") == 0)
	{
		fileadd = ftell(fp);   //@ASSIGN rember the current position in the file
		fscanf(fp, "%s %s\n", &token2, &token3);
		printf("%s %s\n", token2, token3);
		if (strcmp(token2, "=") == 0)  //'='
		{
			int address;
			es = lookup(value, &address);
			if (es)
				return es;
			readNext();
			es = bool_expr();
			if (es)
				return es;
			fprintf(fout, "        STO %d\n", address);
		}
		else
		{
			fseek(fp, fileadd, 0); //Go back to the position if not '='
			printf("%s %s\n", token, value);
			es = bool_expr();
			if (es)
				return es;
		}
	}
	return 0;
}

//<bool_expr>::=<additive_expr>
//           |< additive_expr >(>|<|>=|<=|==|!=)< additive_expr >
/*
<bool_expr>::=<additive_expr>
|< additive_expr >><additive_expr>@GT
|< additive_expr ><<additive_expr>@LES
|< additive_expr >>=<additive_expr >@GE
|< additive_expr ><=< additive_expr >@LE
|< additive_expr >==< additive_expr >@EQ
|< additive_expr >!=< additive_expr >@NOTEQ
*/
int bool_expr()
{
	int es = 0;
	es = additive_expr();
	if (es)
		return es;
	if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0
		|| strcmp(token, "<") == 0 || strcmp(token, "<=") == 0
		|| strcmp(token, "==") == 0 || strcmp(token, "!=") == 0)
	{
		char token2[20];
		strcpy(token2, token);//Store the operator
		readNext();
		es = additive_expr();
		if (es)
			return es;
		if (strcmp(token2, ">") == 0) fprintf(fout, "        GT\n");
		if (strcmp(token2, ">=") == 0) fprintf(fout, "        GE\n");
		if (strcmp(token2, "<") == 0) fprintf(fout, "        LES\n");
		if (strcmp(token2, "<=") == 0) fprintf(fout, "        LE\n");
		if (strcmp(token2, "==") == 0) fprintf(fout, "        EQ\n");
		if (strcmp(token2, "!=") == 0) fprintf(fout, "        NOTEQ\n");
	}
	return 0;
}

//<additive_expr>::=<term>{(+|-)< term >} 
//< additive_expr>::=<term>{(+< term >@ADD |-<term>@SUB)}
int additive_expr()
{
	int es = 0;
	es = term();
	if (es)
		return es;
	while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
	{
		char token2[20];
		strcpy(token2, token);
		readNext();
		es = term();
		if (es)
			return es;
		if (strcmp(token2, "+") == 0) fprintf(fout, "        ADD\n");
		if (strcmp(token2, "-") == 0) fprintf(fout, "        SUB\n");
	}
	return 0;
}

//< term >::=<factor>{(*| /)< factor >} 
//< term >::=<factor>{(*< factor >@MULT | /< factor >@DIV)} 
int term()
{
	int es = 0;
	es = factor();
	if (es)
		return es;
	while (strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
	{
		char token2[20];
		strcpy(token2, token);
		readNext();
		es = factor();
		if (es)
			return es;
		if (strcmp(token2, "*") == 0) fprintf(fout, "        MULT\n");
		if (strcmp(token2, "/") == 0) fprintf(fout, "        DIV\n");
	}
	return 0;
}

//< factor >::=(<additive_expr>)| ID|NUM
//< factor >::=(< expression >)| ID¡ün@LOOK¡ýn¡üd@LOAD¡ýd |NUM¡üi@LOADI¡ýi
int factor()
{
	int es = 0;

	if (strcmp(token, "(") == 0)
	{
		readNext();
		es = expression();
		if (es)
			return es;
		if (strcmp(token, ")"))
			return 6;//6 - 'Less for )'
		readNext();
	}
	else
	{
		if (strcmp(token, "ID") == 0)
		{
			int address;
			es = lookup(value, &address);//Get the address while cheching in the symbol table
			if (es)
				return es;//No defination
			fprintf(fout, "        LOAD %d\n", address);
			readNext();
		}
		else if (strcmp(token, "NUM") == 0)
		{
			fprintf(fout, "        LOADI %s\n", value);
			readNext();
		}
		else
			es = 7;//Less for operator
	}
	return es;
}