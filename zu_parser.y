%{
// $Id: zu_parser.y,v 1.17 2016/04/14 22:03:13 ist179027 Exp $
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
  cdk::string_node     *snode;
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
%left tGE tLE tEQ tNE '>' '<'
%nonassoc '['
%left '+' '-'
%left '*' '/' '%'

%nonassoc tUNARY
%nonassoc tADDR

%type <node> stmt program decl var func vardecl arg for_stmt
%type <sequence> list decls vardecls exprs args
%type <expression> expr literal
%type <snode> string
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

vardecls: vardecl						{ $$ = new cdk::sequence_node(LINE, $1); }
				| vardecls vardecl	{ $$ = new cdk::sequence_node(LINE, $2, $1); }
				;

vardecl : var ';'			{ $$ = $1; }
				;

args		: arg							{ $$ = new cdk::sequence_node(LINE, $1); }
				|	args ',' arg		{ $$ = new cdk::sequence_node(LINE, $3, $1); }
				;

arg			: type tIDENTIFIER '=' expr   { $$ = new zu::vardef_node(LINE, $1, $2, false, false, $4); }
				| type tIDENTIFIER						{ $$ = new zu::vardecl_node(LINE, $1, $2, false, false); }
				;

var			:	type tIDENTIFIER '=' expr			 			{ $$ = new zu::vardef_node(LINE, $1, $2, false, false, $4); }	
				|	type tIDENTIFIER '!' '=' expr			 	{ $$ = new zu::vardef_node(LINE, $1, $2, true, false, $5); }	
				|	type tIDENTIFIER 										{ $$ = new zu::vardecl_node(LINE, $1, $2, false, false); }
				| type tIDENTIFIER '!'								{ $$ = new zu::vardecl_node(LINE, $1, $2, true, false); }
				|	type tIDENTIFIER '?'								{ $$ = new zu::vardecl_node(LINE, $1, $2, false, true); }
				;

func		:	type tIDENTIFIER '!' '(' args ')' '=' literal body	{ $$ = new zu::fundef_node(LINE, $1, $2, true, false, $5, $8, $9); } 
				| type tIDENTIFIER '!' '(' ')' '=' literal body			{ $$ = new zu::fundef_node(LINE, $1, $2, true, false, nullptr, $7, $8); } 
				|	type tIDENTIFIER '!' '(' args ')' body							{ $$ = new zu::fundef_node(LINE, $1, $2, true, false, $5, nullptr, $7); }	
				|	type tIDENTIFIER '!' '('  ')' body									{ $$ = new zu::fundef_node(LINE, $1, $2, true, false, nullptr, nullptr, $6); }			 
				|	type tIDENTIFIER '(' args ')' '=' literal body			{ $$ = new zu::fundef_node(LINE, $1, $2, false, false, $4, $7, $8); }
				|	type tIDENTIFIER '(' ')' '=' literal body					{ $$ = new zu::fundef_node(LINE, $1, $2, false, false, nullptr, $6, $7); }
				|	type tIDENTIFIER '(' args ')' body									{ $$ = new zu::fundef_node(LINE, $1, $2, false, false, $4, nullptr, $6); }
				|	type tIDENTIFIER '(' ')' body											{ $$ = new zu::fundef_node(LINE, $1, $2, false, false, nullptr, nullptr, $5); }
	
				|	type tIDENTIFIER '!' '(' args ')' 					{ $$ = new zu::fundecl_node(LINE, $1, $2, true, false, $5); }	
				|	type tIDENTIFIER '?' '(' args ')' 					{ $$ = new zu::fundecl_node(LINE, $1, $2, false, true, $5); }	
				|	type tIDENTIFIER '(' args ')' 						 	{ $$ = new zu::fundecl_node(LINE, $1, $2, false, false, $4); }
				|	type tIDENTIFIER '!' '(' ')' 					{ $$ = new zu::fundecl_node(LINE, $1, $2, true, false, nullptr); }	
				|	type tIDENTIFIER '?' '(' ')' 					{ $$ = new zu::fundecl_node(LINE, $1, $2, false, true, nullptr); }	
				|	type tIDENTIFIER '(' ')' 						 	{ $$ = new zu::fundecl_node(LINE, $1, $2, false, false, nullptr); }


				| '!' tIDENTIFIER '!' '(' args ')' '=' literal body	{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, true, false, $5, $8, $9); } 
				| '!' tIDENTIFIER '!' '(' ')' '=' literal body			{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, true, false, nullptr, $7, $8); } 
				|	'!' tIDENTIFIER '!' '(' args ')' body							{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, true, false, $5, nullptr, $7); }	
				|	'!' tIDENTIFIER '!' '('  ')' body									{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, true, false, nullptr, nullptr, $6); }			 
				|	'!' tIDENTIFIER '(' args ')' '=' literal body			{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, false, $4, $7, $8); }
				|	'!' tIDENTIFIER '(' ')' '=' literal body					{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, false, nullptr, $6, $7); }
				|	'!' tIDENTIFIER '(' args ')' body									{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, false, $4, nullptr, $6); }
				|	'!' tIDENTIFIER '(' ')' body											{ $$ = new zu::fundef_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, false, nullptr, nullptr, $5); }
	
				|	'!' tIDENTIFIER '!' '(' args ')' 					{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, true, false, $5); }	
				|	'!' tIDENTIFIER '?' '(' args ')' 					{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, true, $5); }	
				|	'!' tIDENTIFIER '(' args ')' 						 	{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, false, $4); }
				|	'!' tIDENTIFIER '!' '(' ')' 					{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, true, false, nullptr); }	
				|	'!' tIDENTIFIER '?' '(' ')' 					{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, true, nullptr); }	
				|	'!' tIDENTIFIER '(' ')' 						 	{ $$ = new zu::fundecl_node(LINE, new basic_type(4, basic_type::TYPE_VOID), $2, false, false, nullptr); }
				;

type		: '#'					{ $$ = new basic_type(4, basic_type::TYPE_INT); }
				|	'%'					{ $$ = new basic_type(8, basic_type::TYPE_DOUBLE); }
				|	'$'					{ $$ = new basic_type(4, basic_type::TYPE_STRING); }
				|	'<'type'>'	{ $$ = new basic_type(4, basic_type::TYPE_POINTER); $$->_subtype = $2; }
				;

body		: block       { $$ = $1; }
				;

block		:	'{' vardecls list '}'	{ $$ = new zu::block_node(LINE, $2, $3); }
				|	'{' list '}' 					{ $$ = new zu::block_node(LINE, nullptr, $2); }
				|	'{' vardecls '}' 			{ $$ = new zu::block_node(LINE, $2, nullptr); }
				|	'{' '}' 							{ $$ = new zu::block_node(LINE, nullptr, nullptr); }
				;

list : stmt	     	{ $$ = new cdk::sequence_node(LINE, $1); }
	   | list stmt 	{ $$ = new cdk::sequence_node(LINE, $2, $1); }
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

for_stmt: '[' exprs ';' exprs ';' exprs ']' stmt      	{ std::cout << "for\n"; $$ = new zu::for_node(LINE, $2, $4, $6, $8); }
			  | '[' exprs ';' exprs ';'       ']' stmt      	{ $$ = new zu::for_node(LINE, $2, $4, nullptr, $7); }
				| '[' exprs ';'       ';' exprs ']' stmt      	{ $$ = new zu::for_node(LINE, $2, new cdk::sequence_node(LINE, new cdk::integer_node(LINE, 1)), $5, $7); }
		 		| '[' exprs ';'       ';'       ']' stmt      	{ $$ = new zu::for_node(LINE, $2, new cdk::sequence_node(LINE, new cdk::integer_node(LINE, 1)), nullptr, $6); }	
				|	'[' args ';' exprs ';' exprs ']' stmt      	{ $$ = new zu::for_node(LINE, $2, $4, $6, $8); }
			  | '[' args ';' exprs ';'       ']' stmt      	{ $$ = new zu::for_node(LINE, $2, $4, nullptr, $7); }
				| '[' args ';'       ';' exprs ']' stmt      	{ $$ = new zu::for_node(LINE, $2, new cdk::sequence_node(LINE, new cdk::integer_node(LINE, 1)), $5, $7); }
		 		| '[' args ';'       ';'       ']' stmt      	{ $$ = new zu::for_node(LINE, $2, new cdk::sequence_node(LINE, new cdk::integer_node(LINE, 1)), nullptr, $6); }
				| '['      ';' exprs ';' exprs ']' stmt      	{ $$ = new zu::for_node(LINE, nullptr, $3, $5, $7); }
				| '['      ';' exprs ';'       ']' stmt   		{ $$ = new zu::for_node(LINE, nullptr, $3, nullptr, $6); }
				| '['      ';'       ';' exprs ']' stmt   		{ $$ = new zu::for_node(LINE, nullptr, new cdk::sequence_node(LINE, new cdk::integer_node(LINE, 1)), $4, $6); }
				| '['      ';'       ';'       ']' stmt    		{ $$ = new zu::for_node(LINE, nullptr, new cdk::sequence_node(LINE, new cdk::integer_node(LINE, 1)), nullptr, $5); }
				;

exprs	: expr											{ $$ = new cdk::sequence_node(LINE, $1); }
			| exprs ',' expr						{ $$ = new cdk::sequence_node(LINE, $3, $1); }
			;

expr : literal							   { $$ = $1; }
     | '@'                     { $$ = new zu::read_node(LINE); }
     | '-' expr %prec tUNARY   { $$ = new cdk::neg_node(LINE, $2); }
     | '~' expr %prec tUNARY   { $$ = new zu::not_node(LINE, $2); }
	   | '+' expr %prec tUNARY 	 { $$ = new zu::identity_node(LINE, $2); }
	   | lval '?'	%prec tADDR		 { $$ = new zu::address_node(LINE, $1); }
     | expr '&' expr	         { $$ = new zu::and_node(LINE, $1, $3); }
     | expr '|' expr	         { $$ = new zu::or_node(LINE, $1, $3); }		 
     | expr '+' expr	         { $$ = new cdk::add_node(LINE, $1, $3); }
     | expr '-' expr	         { $$ = new cdk::sub_node(LINE, $1, $3); }
     | expr '*' expr	         { $$ = new cdk::mul_node(LINE, $1, $3); }
     | expr '/' expr	         { $$ = new cdk::div_node(LINE, $1, $3); }
     | expr '%' expr	         { $$ = new cdk::mod_node(LINE, $1, $3); }
     | expr '<' expr	         { $$ = new cdk::lt_node(LINE, $1, $3); }
     | expr '>' expr	         { $$ = new cdk::gt_node(LINE, $1, $3); }
     | expr tGE expr	         { $$ = new cdk::ge_node(LINE, $1, $3); }
     | expr tLE expr           { $$ = new cdk::le_node(LINE, $1, $3); }
     | expr tNE expr	         { $$ = new cdk::ne_node(LINE, $1, $3); }
     | expr tEQ expr	         { $$ = new cdk::eq_node(LINE, $1, $3); }
     | '(' expr ')'            { $$ = $2; }
	   | '[' expr ']'									{ $$ = new zu::malloc_node(LINE, $2); }
     | lval                    					{ $$ = new zu::rvalue_node(LINE, $1); } 
     | lval '=' expr           					{ $$ = new zu::assignment_node(LINE, $1, $3); }
	   | tIDENTIFIER '(' exprs ')' 				{ $$ = new zu::funcall_node(LINE, *$1, $3); }
	   | tIDENTIFIER '(' ')' 							{ $$ = new zu::funcall_node(LINE, *$1, nullptr); }
     ;

literal	: tINTEGER                	{ $$ = new cdk::integer_node(LINE, $1); }
		    | tDOUBLE                 	{ $$ = new cdk::double_node(LINE, $1); }
        | string                 	{ $$ = $1; }
		    ;

string	: tSTRING 					  { $$ = new cdk::string_node(LINE, $1); }
		    | string tSTRING 			{ $$ = new cdk::string_node(LINE, $1->value() + *$2);	}
		    ;

lval : tIDENTIFIER             		{ $$ = new zu::variable_node(LINE, $1); }
		 | expr '[' expr ']'			 		{ $$ = new zu::index_node(LINE, $1, $3); }
     ;

%%
