#if !defined CODE_H
#define CODE_H

//The code of tokens
#define AND 1
#define ARRAY 2
#define BEGIN 3
#define CASE 4
#define CONST 5
#define DIV 6
#define DO 7
#define DOWNTO 8
#define ELSE 9
#define END 10
#define FILE_ 11
#define FOR 12
#define FUNC 13
#define GOTO 14
#define IF 15
#define IN 16
#define LABEL 17
#define MOD 18
#define NIL 19
#define NOT 20
#define OF 21
#define OR 22
#define PACKED 23
#define PROC 24
#define PROG 25
#define RECORD 26
#define REPEAT 27
#define SET 28
#define THEN 29
#define TO 30
#define TYPE 31
#define UNTIL 32
#define VAR 33
#define WHILE 34
#define WITH 35
#define ID 36
#define INT 37
#define REAL 38
#define STRING 39
#define PLUS 40
#define MINUS 41
#define MULTI 42
#define RDIV 43
#define EQ 44
#define LT 45
#define GT 46
#define LE 47
#define GE 48
#define NE 49
#define LR_BRAC 50
#define RR_BRAC 51
#define COMMA 52
#define P_MARK 53
#define F_STOP 54
#define RANGE 55
#define COLON 56
#define ASSIGN 57
#define SEMIC 58
#define CAP 59
#define EXP 60
#define LS_BRAC 61
#define RS_BRAC 62
#define Q_MARK 63

//The upper of key words
const char KEY_WORDS[64][10] = { "", 
								"AND", "ARRAY", "BEGIN", "CASE",
								"CONST", "DIV", "DO", "DOWNTO",
								"ELSE", "END", "FILE", "FOR",
								"FUNCTION", "GOTO", "IF", "IN",
								"LABEL", "MOD", "NIL", "NOT",
								"OF", "OR", "PACKED", "PROCEDURE",
								"PROGRAM", "RECORD", "REPEAT", "SET",
								"THEN", "TO", "TYPE", "UNTIL",
								"VAR", "WHILE", "WITH", "ID",
								"INT", "REAL", "STRING", "PLUS",
								"MINUS", "MULTI", "RDIV", "EQ",
								"LT", "GT", "LE", "GE",
								"NE", "LR_BRAC", "RR_BRAC", "COMMA",
								"P_MARK", "F_STOP", "RANGE", "COLON",
								"ASSIGN", "SEMIC", "CAP", "EXP",
								"LS_BRAC", "RS_BRAC", "Q_MARK" };

//The lower of key words
const char key_words[63][10] = { "and", "array", "begin", "case",
									"const", "div", "do", "downto",
									"else", "end", "file", "for",
									"function", "goto", "if", "in",
									"label", "mod", "nil", "not",
									"of", "or", "packed", "procedure",
									"program", "record", "repeat", "set",
									"then", "to", "type", "until",
									"var", "while", "with", "id",
									"int", "real", "string", "plus",
									"minus", "multi", "rdiv", "eq",
									"lt", "gt", "le", "ge", "ne",
									"lr_brac", "rr_brac", "comma",
									"p_mark", "f_stop", "range", "colon",
									"assign", "semic", "cap", "exp",
									"ls_brac", "rs_brac", "q_mark" };


#define NODE_LENGTH 26			//only support the lower string to store
typedef struct TrieNode                     //the node of Trie
{
	bool isStr;                            //tag the node is tail of the string
	struct TrieNode *next[NODE_LENGTH];            //the subTrie
} Trie;


#endif

