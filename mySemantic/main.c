#include "semanticAnalysis.h"

int main()
{
	if (lex())
	{
		delSymbolList();
		return -1;
	}
	initStates();
	initNames();
	initTable();

	out = fopen("process.txt", "w");
	if (control() == false)
	{
		fclose(out);
		freeTable();
		freeNames();
		freeStates();
		delSymbolList();
		return -1;
	}
	fclose(out);

	testS();
	//showSymbolList();

	freeTable();
	freeNames();
	freeStates();
	delSymbolList();
	return 0;
}
