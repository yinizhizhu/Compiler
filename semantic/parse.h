//LexAnalysis, SyntaxAnalysis and ProducingMiddleCodes
#pragma once

#include "stdafx.h"
#include <conio.h>
#define maxvartablep 500	//The size of the symbol table

int name_def(char *name);//Insert into the symbol table: @name-def��n, t
int lookup(char *name, int *paddress);//Return address while checking in the symbol table
int parse();//LexAnalysis, SyntaxAnalysis and ProducingMiddleCodes
void readNext();//Read the next pair< token, value >
int program();//program::={<declaration_list><statement_list>}
//<declaration_list>::=
//<declaration_list><declaration_stat>|<declaration_stat>
int declaration_list();//get into <declaration_list>::={<declaration_stat>}
int declaration_stat();//<declaration_stat>��vartablep,datap,codep ->int ID��n@name-def��n,t;
//<statement_list>::=<statement_list><statement>|<statement>
int statement_list();//get into <statement_list>::={<statement>}
int statement();//<statement>::= <if_stat>|<while_stat>|<for_stat>|<compound_stat> |<expression_stat>
//<IF_stat>::= if (<expr>) <statement > [else < statement >]
/*
if (<expression>)@BRF��label1 <statement > @BR��label2 @SETlabel��label1
[ else < statement >] @SETlabel��label2
@BRF��label1 ��output BRF label1,
@BR��label2��output BR label2,
@SETlabel��label1��set label1
@SETlabel��label2��set label2
*/
int if_stat();
//<do_while_stat>::=do<statement>while(<exper>)
//<do_while_stat>::=do @SET��labellabel1<statement>
//                  while(<expression>)
//                  @BRF��label2@BR��label1@SETlabel��label2
//@SETlabel��label1��set label1
//@BRF��label2 ��output BRF label2,
//@BR��label1��output BR label1,
//@SETlabel��label2��set label2
int do_stat();
//<while_stat>::= while (<expr >) < statement >
//<while_stat>::=while @SET��labellabel1(<expression>) @BRF��label2 
//				<statement >@BR��label1 @SETlabel��label2
//@SETlabel��label1��set label1
//@BRF��label2 ��output BRF label2,
//@BR��label1��output BR label1,
//@SETlabel��label2��set label2
int while_stat();
//<for_stat>::= for(<expr>,<expr>,<expr>)<statement>
/*
<for_stat>::=for (<expression>;
@SETlabel��label1< expression >@BRF��label2@BR��label3;
@SETlabel��label4 < expression >@BR��label1)
@SETlabel��label3 <sentence >@BR��label4@SETlabel��label2
1.	@SETlabel��label1��set label1
2.	@BRF��label2 ��output BRF label2,
3.	@BR��label3��output BR label3,
4.	@SETlabel��label4��set label4
5.	@BR��label1��output BR label1,
6.	@SETlabel��label3��set label3
7.	@BR��label4��output BR label4,
8.	@SETlabel��label2��set label2
*/
int for_stat();
//<write_stat>::=write <expression>;
//<write_stat>::=write <expression>@OUT;
//@ OUT��output OUT
int write_stat();
//<read_stat>::=read ID;
//<read_stat>::=read ID��n LOOK��n��d @IN@STI��d;
//@LOOK��n��d:check n in symbol table, and d store the address
//@IN��input----IN
//@STI��d��Oput the asm code----STI  d
int read_stat();
int compound_stat();//<compound_stat>::={<statement_list>} 
int expression_stat();//<expression_stat>::=<expression>;|;
int expression();//<expression>::=ID��n@LOOK��n��d@ASSIGN=<bool_expr>@STO��d |<bool_expr>
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
//< factor >::=(< expression >)| ID��n@LOOK��n��d@LOAD��d |NUM��i@LOADI��i
int factor();