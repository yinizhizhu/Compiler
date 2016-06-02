#include "main.h"
//#define TEST

int main()
{
#ifdef TEST
	initQueue();
	testQueue();
#else
	if (!initAll())
	{
		delSymbolList();
		return -1;
	}

	out = fopen("process.txt", "w");
	if (control() == false)
	{
		delAll();	//free the resource
		return -1;
	}
	showSymbolList();

	delAll();		//free the resource
	showQueue();
	showThreeAddress();
	toMiddleCode();
	delThreeAddress();
#endif
	return 0;
}

bool initAll()		//initial the enrionment
{
	initQueue();//Initial the tokenQueue
	if (lex())
	{
		delSymbolList();
		return false;
	}
	initStates();
	initNames();
	initTable();
	return true;
}

void delAll()		//free the resource
{
	fclose(out);
	freeTable();
	freeNames();
	freeStates();
	delSymbolList();
	return;
}