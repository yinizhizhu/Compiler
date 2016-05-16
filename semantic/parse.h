//LexAnalysis, SyntaxAnalysis and ProducingMiddleCodes
#pragma once

#include "stdafx.h"
#include <conio.h>
#define maxvartablep 500	//The size of the symbol table

int name_def(char *name);//Insert into the symbol table: @name-def¡ýn, t
int lookup(char *name, int *paddress);//Return address while checking in the symbol table
int parse();//LexAnalysis, SyntaxAnalysis and ProducingMiddleCodes
void readNext();//Read the next pair< token, value >
int program();//program::={<declaration_list><statement_list>}
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
int declaration_list();//get into <declaration_list>::={<declaration_stat>}
int declaration_stat();//<declaration_stat>¡ývartablep,datap,codep ->int ID¡ün@name-def¡ýn,t;
//<statement_list>::=<statement_list><statement>|<statement>
int statement_list();//get into <statement_list>::={<statement>}
int statement();//<statement>::= <if_stat>|<while_stat>|<for_stat>|<compound_stat> |<expression_stat>
//<IF_stat>::= if (<expr>) <statement > [else < statement >]
/*
if (<expression>)@BRF¡ülabel1 <statement > @BR¡ülabel2 @SETlabel¡ýlabel1
[ else < statement >] @SETlabel¡ýlabel2
@BRF¡ülabel1 £ºoutput BRF label1,
@BR¡ülabel2£ºoutput BR label2,
@SETlabel¡ýlabel1£ºset label1
@SETlabel¡ýlabel2£ºset label2
*/
int if_stat();
//<do_while_stat>::=do<statement>while(<exper>)
//<do_while_stat>::=do @SET¡ülabellabel1<statement>
//                  while(<expression>)
//                  @BRF¡ülabel2@BR¡ülabel1@SETlabel¡ýlabel2
//@SETlabel¡ülabel1£ºset label1
//@BRF¡ülabel2 £ºoutput BRF label2,
//@BR¡ýlabel1£ºoutput BR label1,
//@SETlabel¡ýlabel2£ºset label2
int do_stat();
//<while_stat>::= while (<expr >) < statement >
//<while_stat>::=while @SET¡ülabellabel1(<expression>) @BRF¡ülabel2 
//				<statement >@BR¡ýlabel1 @SETlabel¡ýlabel2
//@SETlabel¡ülabel1£ºset label1
//@BRF¡ülabel2 £ºoutput BRF label2,
//@BR¡ýlabel1£ºoutput BR label1,
//@SETlabel¡ýlabel2£ºset label2
int while_stat();
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
int for_stat();
//<write_stat>::=write <expression>;
//<write_stat>::=write <expression>@OUT;
//@ OUT£ºoutput OUT
int write_stat();
//<read_stat>::=read ID;
//<read_stat>::=read ID¡ün LOOK¡ýn¡üd @IN@STI¡ýd;
//@LOOK¡ýn¡üd:check n in symbol table, and d store the address
//@IN£ºinput----IN
//@STI¡ýd£ºOput the asm code----STI  d
int read_stat();
int compound_stat();//<compound_stat>::={<statement_list>} 
int expression_stat();//<expression_stat>::=<expression>;|;
int expression();//<expression>::=ID¡ün@LOOK¡ýn¡üd@ASSIGN=<bool_expr>@STO¡ýd |<bool_expr>
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
int bool_expr();
//<additive_expr>::=<term>{(+|-)< term >} 
//< additive_expr>::=<term>{(+< term >@ADD |-<term>@SUB)}
int additive_expr();
//< term >::=<factor>{(*| /)< factor >} 
//< term >::=<factor>{(*< factor >@MULT | /< factor >@DIV)} 
int term();
//< factor >::=(<additive_expr>)| ID|NUM
//< factor >::=(< expression >)| ID¡ün@LOOK¡ýn¡üd@LOAD¡ýd |NUM¡üi@LOADI¡ýi
int factor();