%{
// $Id: zu_parser.y,v 1.24 2016/05/19 17:48:40 ist179027 Exp $
//-- don't change *any* of these: if you do, you'll break the compiler.
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
//-- don't change *any* of these --- END!
%}

%union {
  int                   i;	/* integer value */
  double                d;  /* double value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  zu::lvalue_node      *lvalue;
	basic_type			     *basictype;
	zu::block_node			 *blocknode;
};

%token <i> tINTEGER, tHEXA
%token <d> tDOUBLE 
%token <s> tIDENTIFIER tSTRING
%token tPRINT tRET tBREAK tCONTINUE


%nonassoc tIFX
%nonassoc ':'

%right '='
%left '|'
%left '&'
%nonassoc tNOT
%left tEQ tNE
%left tGE tLE '>' '<'
%left '+' '-'
%left '*' '/' '%'

%nonassoc tUNARY

%type <s> string
%type <node> stmt program decl var func vardecl arg for_stmt
%type <sequence> list decls vardecls exprs args optargs optexprs inits optdecls optlist
%type <expression> expr literal optliteral
%type <lvalue> lval
%type <basictype> type
%type <blocknode> block body


%{
//-- The rules below will be included in yyparse, the main parsing function.
%}
%%

program	: decls { compiler->ast($1); }
	      ;

decls		: decl				{ $$ = new cdk::sequence_node(LINE, $1); }
				|	decls decl	{ $$ = new cdk::sequence_node(LINE, $2, $1); }
				;

decl		:	vardecl			{ $$ = $1; }
				|	func				{ $$ = $1; }
				;

vardecl : var ';'     { $$ = $1; }
        ;

optdecls  :                     { $$ = nullptr; }
          | vardecls            { $$ = $1; }
          ;
vardecls: vardecl						{ $$ = new cdk::sequence_node(LINE, $1); }
				| vardecls vardecl	{ $$ = new cdk::sequence_node(LINE, $2, $1); }
				;

var			:	arg 																{ $$ = $1; }
				|	type tIDENTIFIER '!' '=' expr			 	{ $$ = new zu::vardef_node(LINE, $1, $2, true, false, $5); }
				| type tIDENTIFIER '!'								{ $$ = new zu::vardecl_node(LINE, $1, $2, true, false); }
				|	type tIDENTIFIER '?'								{ $$ = new zu::vardecl_node(LINE, $1, $2, false, true); }
				;

func		:	type tIDENTIFIER '!' '(' optargs ')' optliteral body	{ $$ = new zu::fundef_node(LINE, $1, $2, true, false, $5, $7, $8); } 	 
				|	type tIDENTIFIER '(' optargs ')' optliteral body			{ $$ = new zu::fundef_node(LINE, $1, $2, false, false, $4, $6, $7); }
	
				|	type tIDENTIFIER '!' '(' optargs ')' 					{ $$ = new zu::fundecl_node(LINE, $1, $2, true, false, $5); }	
				|	type tIDENTIFIER '?' '(' optargs ')' 					{ $$ = new zu::fundecl_node(LINE, $1, $2, false, true, $5); }	
				|	type tIDENTIFIER '(' optargs ')' 						 	{ $$ = new zu::fundecl_node(LINE, $1, $2, false, false, $4); }


				| '!' tIDENTIFIER '!' '(' optargs ')' optliteral body	{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, true, false, $5, $7, $8); } 		 
				|	'!' tIDENTIFIER '(' optargs ')' optliteral body			{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, false, $4, $6, $7); }
	
				|	'!' tIDENTIFIER '!' '(' optargs ')' 					{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, true, false, $5); }	
				|	'!' tIDENTIFIER '?' '(' optargs ')' 					{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, true, $5); }	
				|	'!' tIDENTIFIER '(' optargs ')' 						 	{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, false, $4); }
				;

type		: '#'					{ $$ = new basic_type(4, basic_type::TYPE_INT); }
				|	'%'					{ $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
				|	'$'					{ $$ = new basic_type(4, basic_type::TYPE_STRING); }
				|	'<'type'>'	{ $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $2; }
				;

arg     : type tIDENTIFIER '=' expr   { $$ = new zu::vardef_node(LINE, $1, $2, false, false, $4); }
        | type tIDENTIFIER            { $$ = new zu::vardecl_node(LINE, $1, $2, false, false); }
        ;

optargs :             { $$ = nullptr; }
        | args        { $$ = $1; }
        ;

args    : arg             { $$ = new cdk::sequence_node(LINE, $1); }
        | args ',' arg    { $$ = new cdk::sequence_node(LINE, $3, $1); }
        ;

body		: block       { $$ = $1; }
				;

block		:	'{' optdecls optlist '}'	{ $$ = new zu::block_node(LINE, $2, $3); }
				;

list : stmt	     	{ $$ = new cdk::sequence_node(LINE, $1); }
	   | list stmt 	{ $$ = new cdk::sequence_node(LINE, $2, $1); }
	   ;

optlist   :                     { $$ = nullptr; }
          | list                { $$ = $1; }
          ;

stmt : expr ';'                                         { $$ = new zu::evaluation_node(LINE, $1); }
		 | expr '!'                                         { $$ = new zu::print_node(LINE, $1, false); } 
 	   | expr tPRINT                                      { $$ = new zu::print_node(LINE, $1, true); }
		 | tBREAK                                           { $$ = new zu::break_node(LINE); }
		 | tCONTINUE                                        { $$ = new zu::continue_node(LINE); }
		 | tRET                                             { $$ = new zu::return_node(LINE); }
		 | for_stmt																					{ $$ = $1; }                                 
     | '[' expr ']' '#' stmt						                { $$ = new zu::if_node(LINE, $2, $5); }
     | '[' expr ']' '?' stmt 	%prec tIFX           			{ $$ = new zu::if_node(LINE, $2, $5); }
     | '[' expr ']' '?' stmt ':' stmt							      { $$ = new zu::if_else_node(LINE, $2, $5, $7); }
     | block                                            { $$ = $1; }
     ;

for_stmt: '[' inits ';' exprs ';' optexprs ']' stmt      	{ $$ = new zu::for_node(LINE, $2, $4, $6, $8); }
				| '[' inits ';'       ';' optexprs ']' stmt      	{ $$ = new zu::for_node(LINE, $2, new cdk::sequence_node(LINE, new cdk::integer_node(LINE, 1)), $5, $7); }
				;

inits	:								{ $$ = nullptr; }
			|	exprs					{ $$ = $1; }
			|	args					{ $$ = $1; }
			;

expr : literal							            { $$ = $1; }
     | '@'                              { $$ = new zu::read_node(LINE); }
     | '-' expr %prec tUNARY            { $$ = new cdk::neg_node(LINE, $2); }
     | '~' expr %prec tNOT              { $$ = new zu::not_node(LINE, $2); }
     | '+' expr %prec tUNARY 	          { $$ = new zu::identity_node(LINE, $2); }
     | expr '&' expr	                  { $$ = new zu::and_node(LINE, $1, $3); }
     | expr '|' expr	                  { $$ = new zu::or_node(LINE, $1, $3); }		 
     | expr '+' expr	                  { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	                  { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	                  { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	                  { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	                  { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	                  { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	                  { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr	                  { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr                    { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	                  { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	                  { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '(' expr ')'                     { $$ = $2; }
     | '[' expr ']'									    { $$ = new zu::malloc_node(LINE, $2); }
     | lval                    					{ $$ = new zu::rvalue_node(LINE, $1); } 
     | lval '=' expr           					{ $$ = new zu::assignment_node(LINE, $1, $3); }     
     | tIDENTIFIER '(' optexprs ')' 	  { $$ = new zu::funcall_node(LINE, $1, $3); }     
     | lval '?' %prec tUNARY            { $$ = new zu::address_node(LINE, $1); }
     ;

optexprs:             { $$ = nullptr; }
        | exprs       { $$ = $1; }
        ;

exprs : expr                      { $$ = new cdk::sequence_node(LINE, $1); }
      | exprs ',' expr            { $$ = new cdk::sequence_node(LINE, $3, $1); }
      ;

literal	: tINTEGER                	{ $$ = new cdk::integer_node(LINE, $1); }
				| tDOUBLE                 	{ $$ = new cdk::double_node(LINE, $1); }
        | string                 		{ $$ = new cdk::string_node(LINE, $1); }
		    ;

optliteral  :             { $$ = nullptr; }
            | '=' literal { $$ = $2; }
            ;

string	: tSTRING 					  { $$ = $1; }
				| string tSTRING 			{ $$ = new std::string(*$1+*$2); delete $1; delete $2;	}
				;

lval : tIDENTIFIER             		                { $$ = new zu::variable_node(LINE, $1); }
		 | '(' expr ')' '[' expr ']'	                { $$ = new zu::index_node(LINE, $2, $5); } 
		 | lval '[' expr ']'                          { $$ = new zu::index_node(LINE, $1, $3); }
     | tIDENTIFIER '(' optexprs ')' '[' expr ']'  { $$ = new zu::index_node(LINE, new zu::funcall_node(LINE, $1, $3), $6); }
     | '[' expr ']' '[' expr ']'                  { $$ = new zu::index_node(LINE, new zu::malloc_node(LINE, $2), $5); }
     ;

%%
