#include "stdafx.h"
#include "scan.h"
#include "parse.h"

int main(){
	int es = 0;
	es = lex();//Lex Analysis
	if (es > 0)
	{
		printf("Something wrong is in parse, and stop compiling!\n");
		return -1;
	}
	printf("Success to Lex Analysis!\n");
	es = parse();//Call Syntax and Semantic Analysor to get the middle code.
	if (es == 0)
		printf("Syntax and Semantic analysising is successful to produce the middle code!\n");
	else
		printf("Syntax and Semantic analysising  is wrong!\n");
	return 0;
}
