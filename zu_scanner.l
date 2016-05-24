%option c++ yyclass="zu_scanner" outfile="zu_scanner.cpp"
%option stack noyywrap yylineno 8bit
%{ 
/* $Id: zu_scanner.l,v 1.15 2016/05/13 10:43:30 ist178414 Exp $ */
// make relevant includes before including the parser's tab file
#include <string>
#include <cdk/ast/sequence_node.h>
#include <cdk/ast/expression_node.h>
#include "zu_scanner.h"
#include "zu_parser.tab.h"
#include <iostream>

// don't change this
#define yyerror LexerError
%}

DIGIT  	   [0-9]
FDIGIT     [1-9]
HEXADIGIT  [0-9a-fA-F]
EXP			   [eE][+-]?{INT}
INT			   {FDIGIT}{DIGIT}*
DOUBLE		 {DIGIT}+
SPACE	     [ \t\n\r]


%x X_STRING X_COMMENT X_STR_SPECIAL X_NEXT

%%




"//".*$                ; /* ignore comments */

"/*"                   yy_push_state(X_COMMENT);
<X_COMMENT>"/*"        yy_push_state(X_COMMENT);
<X_COMMENT>"*/"        yy_pop_state();
<X_COMMENT>.|\n        ;            


">="                   return tGE; 
"<="                   return tLE; 
"=="                   return tEQ; 
"!="                   return tNE; 

"!!"                   return tPRINT;
"!!!"                  return tRET;
"><"                   return tBREAK;
"<>"                   return tCONTINUE;


[A-Za-z_][A-Za-z0-9_]*  						yylval.s = new std::string(yytext); return tIDENTIFIER;

\"                     							yy_push_state(X_STRING); yylval.s = new std::string("");
<X_STRING>\\00 											yy_push_state(X_STR_SPECIAL); return tSTRING;
<X_STRING>\\{HEXADIGIT}{HEXADIGIT}  *yylval.s += (char)strtol(yytext+1, nullptr, 16);
<X_STRING>\\0												yy_push_state(X_STR_SPECIAL); return tSTRING;
<X_STRING>\\{HEXADIGIT}							*yylval.s += (char)strtol(yytext+1, nullptr, 16);
<X_STRING>\\\"         							*yylval.s += (char)34;
<X_STRING>\\t         							*yylval.s += (char)9;
<X_STRING>\\n         							*yylval.s += (char)10;
<X_STRING>\\r         							*yylval.s += (char)13;
<X_STRING>\\\\         							*yylval.s += (char)92;
<X_STRING>\\.												*yylval.s += yytext+1;
<X_STRING>\"           							yy_pop_state(); return tSTRING;
<X_STRING>.            							*yylval.s += yytext;
<X_STRING>\n           							yyerror("newline in string");

<X_STR_SPECIAL>\\\"			;
<X_STR_SPECIAL>\"				yy_pop_state(); yy_pop_state();
<X_STR_SPECIAL>.				;
<X_STR_SPECIAL>\n				yyerror("newline in string");

{DOUBLE}{EXP}								yylval.d = strtod(yytext, nullptr); return tDOUBLE;
{DOUBLE}\.{DIGIT}*{EXP}?			yylval.d = strtod(yytext, nullptr); return tDOUBLE;
\.{DIGIT}+{EXP}?					yylval.d = strtod(yytext, nullptr); return tDOUBLE;

{FDIGIT}{DIGIT}*                     yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;
0                         yylval.i = strtol(yytext, nullptr, 10); return tINTEGER;

0[xX]{HEXADIGIT}+					yylval.i = strtol(yytext+2, nullptr, 16); return tINTEGER;


[-=<>()/#$@!&|~{}+*?,:;.%\[\]]  		return *yytext;

{SPACE}+               							; /* ignore whitespace */

.                      							yyerror("Unknown character");

%%
// Very, very dirty hack: flex is a mess generating C++ scanners.
int zu_scanner::yywrap() { return 1; }
