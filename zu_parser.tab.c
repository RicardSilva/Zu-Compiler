/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140715

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "zu_parser.y"
/* $Id: zu_parser.y,v 1.8 2016/03/17 00:16:20 ist179027 Exp $*/
/*-- don't change *any* of these: if you do, you'll break the compiler.*/
#include <cdk/compiler.h>
#include "ast/all.h"
#define LINE       compiler->scanner()->lineno()
#define yylex()    compiler->scanner()->scan()
#define yyerror(s) compiler->scanner()->error(s)
#define YYPARSE_PARAM_TYPE std::shared_ptr<cdk::compiler>
#define YYPARSE_PARAM      compiler
/*-- don't change *any* of these --- END!*/
#line 14 "zu_parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  int                   i;	/* integer value */
  std::string          *s;	/* symbol name or string literal */
  cdk::basic_node      *node;	/* node pointer */
  cdk::sequence_node   *sequence;
  cdk::expression_node *expression; /* expression nodes */
  zu::lvalue_node  *lvalue;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 42 "zu_parser.y"
/*-- The rules below will be included in yyparse, the main parsing function.*/
#line 50 "zu_parser.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define tINTEGER 257
#define tIDENTIFIER 258
#define tSTRING 259
#define tIF 260
#define tPRINT 261
#define tREAD 262
#define tBEGIN 263
#define tEND 264
#define tFOR 265
#define tIFX 266
#define tELSE 267
#define tGE 268
#define tLE 269
#define tEQ 270
#define tNE 271
#define tUNARY 272
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    2,    2,    1,    1,    1,    1,    1,    1,    1,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    4,
};
static const YYINT yylen[] = {                            2,
    3,    1,    2,    2,    3,    3,    9,    5,    7,    3,
    1,    1,    2,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    1,    3,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    0,   11,   28,   12,    0,    0,    0,    0,    0,
    0,    0,    2,    0,    0,    0,    0,    0,    0,    0,
   13,    0,    0,    1,    3,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    4,    0,    0,    5,
    6,    0,   25,   10,    0,    0,    0,    0,    0,    0,
    0,    0,   16,   17,   18,    0,    0,    0,    0,    0,
    0,    0,    9,    0,    0,    7,
};
static const YYINT yydgoto[] = {                          2,
   13,   14,   15,   16,
};
static const YYINT yysindex[] = {                      -261,
  141,    0,    0,    0,    0,  -22,  -31, -255,  -20,  -31,
  -31,  141,    0,   14,  -30,  -35,  -31,   -9,  -32,  141,
    0,   -2,   99,    0,    0,  -31,  -31,  -31,  -31,  -31,
  -31,  -31,  -31,  -31,  -31,  -31,    0,  -31,   20,    0,
    0,  112,    0,    0,  103,  103,  103,  103,  103,  103,
  -26,  -26,    0,    0,    0,   27,  141,  141, -243,  121,
  141,  141,    0,  132,  141,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  -37,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   43,   47,   52,   58,   63,   67,
   32,   38,    0,    0,    0,  -40,    0,    0,   90,    0,
    0,    0,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
  118,   66,  397,   23,
};
#define YYTABLESIZE 435
static const YYINT yytable[] = {                         26,
   27,    1,    4,   26,   26,   26,   36,   26,   11,   26,
   36,   34,   32,   10,   33,   34,   35,   17,   27,   20,
   35,   26,   26,   61,   26,   38,   41,   36,   37,   31,
   19,   30,   34,   32,   36,   33,    0,   35,   43,   34,
   32,    0,   33,    0,   35,    0,    0,    0,    0,   40,
   31,    0,   30,   11,    0,    0,   36,   31,   10,   30,
   57,   34,   32,   36,   33,    0,   35,    0,   34,   32,
    0,   33,   14,   35,   14,    0,   14,   23,   15,   31,
   15,   30,   15,   21,    0,   42,   31,   22,   30,    0,
   14,   14,   24,   14,    0,    0,   15,   15,   23,   15,
    0,   21,   21,   20,   21,   22,   22,   19,   22,    0,
   24,   24,    0,   24,    0,    0,   23,   23,    0,   23,
    0,   20,   20,   60,   20,   19,   19,   64,   19,    8,
    8,   25,    0,    0,    8,    0,   12,    0,   11,   36,
   25,    0,    0,   10,   34,   32,    0,   33,    8,   35,
    0,   11,    0,    0,    0,    0,   10,    0,    0,   25,
   11,    0,    0,    0,    0,   10,    0,    0,    0,    0,
   58,   11,   65,    0,   59,    0,   10,   25,   63,   62,
   11,   25,   66,    0,    0,   10,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    8,    0,    8,    0,    0,    0,    0,    0,
    0,   12,    0,   44,    0,    3,    4,    5,    0,    0,
   26,   26,   26,   26,   12,    0,    0,   26,   27,   28,
   29,    0,    0,   12,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   12,    0,    0,    0,   26,   27,
   28,   29,    0,   12,    0,   26,   27,   28,   29,    0,
    3,    4,    5,    6,    7,    8,    0,   24,    9,    0,
    0,    0,    0,    0,    0,    0,    0,   26,   27,   28,
   29,    0,    0,    0,   26,   27,   28,   29,    0,   14,
   14,   14,   14,    0,    0,   15,   15,   15,   15,    0,
   21,   21,   21,   21,   22,   22,   22,   22,    0,   24,
   24,   24,   24,    0,    0,   23,   23,   23,   23,    0,
   20,   20,   20,   20,   19,   19,   19,   19,    0,    0,
    0,    0,    0,    0,    0,    0,    8,    8,    8,    8,
    8,    8,    0,    8,    8,    3,    4,    5,    6,    7,
    8,    0,    0,    9,    0,    0,    0,    0,    3,    4,
    5,    6,    7,    8,    0,    0,    9,    3,    4,    5,
    6,    7,    8,    0,    0,    9,    0,    0,    3,    4,
    5,    6,    7,    8,    0,    0,    9,    3,    4,    5,
    6,    7,    8,   18,    0,    9,   21,   22,    0,    0,
    0,    0,    0,   39,    0,    0,    0,    0,    0,    0,
    0,    0,   45,   46,   47,   48,   49,   50,   51,   52,
   53,   54,   55,    0,   56,
};
static const YYINT yycheck[] = {                         37,
   41,  263,  258,   41,   42,   43,   37,   45,   40,   47,
   37,   42,   43,   45,   45,   42,   47,   40,   59,   40,
   47,   59,   60,  267,   62,   61,   59,   37,   59,   60,
    8,   62,   42,   43,   37,   45,   -1,   47,   41,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,   59,
   60,   -1,   62,   40,   -1,   -1,   37,   60,   45,   62,
   41,   42,   43,   37,   45,   -1,   47,   -1,   42,   43,
   -1,   45,   41,   47,   43,   -1,   45,   12,   41,   60,
   43,   62,   45,   41,   -1,   20,   60,   41,   62,   -1,
   59,   60,   41,   62,   -1,   -1,   59,   60,   41,   62,
   -1,   59,   60,   41,   62,   59,   60,   41,   62,   -1,
   59,   60,   -1,   62,   -1,   -1,   59,   60,   -1,   62,
   -1,   59,   60,   58,   62,   59,   60,   62,   62,   40,
   41,   14,   -1,   -1,   45,   -1,  123,   -1,   40,   37,
   23,   -1,   -1,   45,   42,   43,   -1,   45,   59,   47,
   -1,   40,   -1,   -1,   -1,   -1,   45,   -1,   -1,   42,
   40,   -1,   -1,   -1,   -1,   45,   -1,   -1,   -1,   -1,
   59,   40,   41,   -1,   57,   -1,   45,   60,   61,   59,
   40,   64,   65,   -1,   -1,   45,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  123,   -1,  125,   -1,   -1,   -1,   -1,   -1,
   -1,  123,   -1,  125,   -1,  257,  258,  259,   -1,   -1,
  268,  269,  270,  271,  123,   -1,   -1,  268,  269,  270,
  271,   -1,   -1,  123,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  123,   -1,   -1,   -1,  268,  269,
  270,  271,   -1,  123,   -1,  268,  269,  270,  271,   -1,
  257,  258,  259,  260,  261,  262,   -1,  264,  265,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  268,  269,  270,
  271,   -1,   -1,   -1,  268,  269,  270,  271,   -1,  268,
  269,  270,  271,   -1,   -1,  268,  269,  270,  271,   -1,
  268,  269,  270,  271,  268,  269,  270,  271,   -1,  268,
  269,  270,  271,   -1,   -1,  268,  269,  270,  271,   -1,
  268,  269,  270,  271,  268,  269,  270,  271,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,  260,
  261,  262,   -1,  264,  265,  257,  258,  259,  260,  261,
  262,   -1,   -1,  265,   -1,   -1,   -1,   -1,  257,  258,
  259,  260,  261,  262,   -1,   -1,  265,  257,  258,  259,
  260,  261,  262,   -1,   -1,  265,   -1,   -1,  257,  258,
  259,  260,  261,  262,   -1,   -1,  265,  257,  258,  259,
  260,  261,  262,    7,   -1,  265,   10,   11,   -1,   -1,
   -1,   -1,   -1,   17,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   26,   27,   28,   29,   30,   31,   32,   33,
   34,   35,   36,   -1,   38,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 1
#endif
#define YYMAXTOKEN 272
#define YYUNDFTOKEN 279
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"tINTEGER","tIDENTIFIER","tSTRING","tIF","tPRINT","tREAD",
"tBEGIN","tEND","tFOR","tIFX","tELSE","tGE","tLE","tEQ","tNE","tUNARY",0,0,0,0,
0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : tBEGIN list tEND",
"list : stmt",
"list : list stmt",
"stmt : expr ';'",
"stmt : tPRINT expr ';'",
"stmt : tREAD lval ';'",
"stmt : tFOR '(' list ';' list ';' list ')' stmt",
"stmt : tIF '(' expr ')' stmt",
"stmt : tIF '(' expr ')' stmt tELSE stmt",
"stmt : '{' list '}'",
"expr : tINTEGER",
"expr : tSTRING",
"expr : '-' expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '%' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr tGE expr",
"expr : expr tLE expr",
"expr : expr tNE expr",
"expr : expr tEQ expr",
"expr : '(' expr ')'",
"expr : lval",
"expr : lval '=' expr",
"lval : tIDENTIFIER",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 46 "zu_parser.y"
	{ /* compiler->ast(new zu::program_node(LINE, $2)); */}
break;
case 2:
#line 49 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node); }
break;
case 3:
#line 50 "zu_parser.y"
	{ yyval.sequence = new cdk::sequence_node(LINE, yystack.l_mark[0].node, yystack.l_mark[-1].sequence); }
break;
case 4:
#line 53 "zu_parser.y"
	{ yyval.node = new zu::evaluation_node(LINE, yystack.l_mark[-1].expression); }
break;
case 5:
#line 54 "zu_parser.y"
	{ /*FIXME: $$ = new zu::print_node(LINE, $2);*/ }
break;
case 6:
#line 55 "zu_parser.y"
	{ yyval.node = new zu::read_node(LINE, yystack.l_mark[-1].lvalue); }
break;
case 7:
#line 56 "zu_parser.y"
	{ yyval.node = new zu::for_node(LINE, yystack.l_mark[-6].sequence, yystack.l_mark[-4].sequence, yystack.l_mark[-2].sequence, yystack.l_mark[0].node); }
break;
case 8:
#line 57 "zu_parser.y"
	{ yyval.node = new zu::if_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].node); }
break;
case 9:
#line 58 "zu_parser.y"
	{ yyval.node = new zu::if_else_node(LINE, yystack.l_mark[-4].expression, yystack.l_mark[-2].node, yystack.l_mark[0].node); }
break;
case 10:
#line 59 "zu_parser.y"
	{ yyval.node = yystack.l_mark[-1].sequence; }
break;
case 11:
#line 62 "zu_parser.y"
	{ yyval.expression = new cdk::integer_node(LINE, yystack.l_mark[0].i); }
break;
case 12:
#line 63 "zu_parser.y"
	{ yyval.expression = new cdk::string_node(LINE, yystack.l_mark[0].s); }
break;
case 13:
#line 64 "zu_parser.y"
	{ yyval.expression = new cdk::neg_node(LINE, yystack.l_mark[0].expression); }
break;
case 14:
#line 65 "zu_parser.y"
	{ yyval.expression = new cdk::add_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 15:
#line 66 "zu_parser.y"
	{ yyval.expression = new cdk::sub_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 16:
#line 67 "zu_parser.y"
	{ yyval.expression = new cdk::mul_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 17:
#line 68 "zu_parser.y"
	{ yyval.expression = new cdk::div_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 18:
#line 69 "zu_parser.y"
	{ yyval.expression = new cdk::mod_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 19:
#line 70 "zu_parser.y"
	{ yyval.expression = new cdk::lt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 20:
#line 71 "zu_parser.y"
	{ yyval.expression = new cdk::gt_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 21:
#line 72 "zu_parser.y"
	{ yyval.expression = new cdk::ge_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 22:
#line 73 "zu_parser.y"
	{ yyval.expression = new cdk::le_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 23:
#line 74 "zu_parser.y"
	{ yyval.expression = new cdk::ne_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 24:
#line 75 "zu_parser.y"
	{ yyval.expression = new cdk::eq_node(LINE, yystack.l_mark[-2].expression, yystack.l_mark[0].expression); }
break;
case 25:
#line 76 "zu_parser.y"
	{ yyval.expression = yystack.l_mark[-1].expression; }
break;
case 26:
#line 77 "zu_parser.y"
	{ yyval.expression = new zu::rvalue_node(LINE, yystack.l_mark[0].lvalue); }
break;
case 27:
#line 78 "zu_parser.y"
	{ yyval.expression = new zu::assignment_node(LINE, yystack.l_mark[-2].lvalue, yystack.l_mark[0].expression); }
break;
case 28:
#line 81 "zu_parser.y"
	{ /*FIXME: $$ = new zu::lvalue_node(LINE, $1);*/ }
break;
#line 638 "zu_parser.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
