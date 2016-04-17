#include "symbolManager.h"

int hashPJW(char* s)	//get the index of the string in the hash table of symbol list
{
	char* p = s;
	unsigned h = 0, g;
	for (; p!= EOS; p++)
	{
		h = (h << 4) + (*p);
		if (g = h & 0xf0000000)
		{
			h = g ^ (g >> 24);
			h = h ^ g;
		}
	}
	return h % PRIME;
}

void initSymbolList()	//to let the symbol list initial
{
	int i;
	symbolList = NULL;
	symbolList = (symbolN**)malloc(SYMBOL_LIST_LENGTH*sizeof(symbolN*));
	for (i = 0; i < SYMBOL_LIST_LENGTH; i++)
		symbolList[i] = NULL;
	return;
}

symbolN* getSymbolN(char* s) //get pointer of the token in the symbol list
{
	int index = hashPJW(s);
	symbolN* tmp = symbolList[index];
	while (tmp)
	{
		if (strcmp(s, tmp->name) == 0)
			return tmp;
		tmp = tmp->next;
	}
	return tmp;
}

void insertIntoSymbolList(char* name)		//insert the identifier into the symbol list with the name of identifier
{
	int index = hashPJW(name);
	int stringLen = strlen(name);
	symbolN* tmp;
	if (getSymbolN(name) != NULL)		//return while there is it
		return;
	if (symbolList[index] == NULL)
	{
		symbolList[index] = (symbolN*)malloc(sizeof(symbolN));
		tmp = symbolList[index];
	}
	else
	{
		tmp = symbolList[index];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (symbolN*)malloc(sizeof(symbolN));	//malloc the room for name of the identifire
		tmp = tmp->next;
	}
	tmp->name = (char*)malloc(stringLen*sizeof(char));
	strcpy(tmp->name, name);
	tmp->typeB = -1;
	tmp->typeS = -1;
	tmp->address = -1;
	tmp->properties = NULL;
	tmp->next = NULL;
	return;
}

void insertIntoSymbolList2(char* name, int typeB, int typeS, u_int address)		//insert the identifier into the symbol list with name, typeB...
{
	int index = hashPJW(name);
	int stringLen = strlen(name);
	symbolN* tmp = getSymbolN(name);
	if (tmp != NULL)		//return while there is it, and change the content
	{
		tmp->typeB = typeB;
		tmp->typeS = typeS;
		tmp->address = address;
		return;
	}
	if (symbolList[index] == NULL)
	{
		symbolList[index] = (symbolN*)malloc(sizeof(symbolN));
		tmp = symbolList[index];
	}
	else
	{
		tmp = symbolList[index];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (symbolN*)malloc(sizeof(symbolN));	//malloc the room for name of the identifire
		tmp = tmp->next;
	}
	tmp->name = (char*)malloc(stringLen*sizeof(char));
	strcpy(tmp->name, name);
	tmp->typeB = typeB;
	tmp->typeS = typeS;
	tmp->address = address;
	tmp->properties = NULL;
	tmp->next = NULL;
	return;
}

void insertIntoSymbolList3(char* name, int typeB, int typeS, u_int address, int* nextP, int lenP)		//insert the identifier into the symbol list with name, typeB...
{
	int i, index = hashPJW(name);
	int stringLen = strlen(name);
	symbolN* tmp = getSymbolN(name);
	if (tmp != NULL)		//return while there is it, and change the content
	{
		tmp->typeB = typeB;
		tmp->typeS = typeS;
		tmp->address = address;
		tmp->properties->dimensionNum = lenP;
		for (i = 0; i < lenP; i++)
			tmp->properties->dimensions[i] = nextP[i];
		return;
	}
	if (symbolList[index] == NULL)
	{
		symbolList[index] = (symbolN*)malloc(sizeof(symbolN));
		tmp = symbolList[index];
	}
	else
	{
		tmp = symbolList[index];
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = (symbolN*)malloc(sizeof(symbolN));	//malloc the room for name of the identifire
		tmp = tmp->next;
	}
	tmp->name = (char*)malloc(stringLen*sizeof(char));
	strcpy(tmp->name, name);
	tmp->typeB = typeB;
	tmp->typeS = typeS;
	tmp->address = address;
	tmp->properties = NULL;
	tmp->next = NULL;
	tmp->properties = (extendP*)malloc(sizeof(extendP));	//malloc the room for property
	tmp->properties->dimensionNum = lenP;
	tmp->properties->dimensions = (int*)malloc(lenP*sizeof(int));	//malloc the room to store the length of dimensions
	for (i = 0; i < lenP; i++)
		tmp->properties->dimensions[i] = nextP[i];
	tmp->next = NULL;
	return;
}

void delSymbolList()	//to free the room gotten from system
{
	symbolN* levelOne;
	symbolN* levelOneN;
	int i;
	for (i = 0; i < SYMBOL_LIST_LENGTH; i++)
	{
		levelOne = symbolList[i];
		while (levelOne)
		{
			levelOneN = levelOne;
			free(levelOne->name);	//free the room for the name
			if (levelOne->properties)
			{
				free(levelOne->properties->dimensions);	//free the room for the dimension in extendProperty
				free(levelOne->properties);		//free the room for the extend property
			}
			levelOne = levelOne->next;
			free(levelOneN);
		}
	}
	free(symbolList);	//free the room for the symbol list
}