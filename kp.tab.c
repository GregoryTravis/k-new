/* A Bison parser, made from kp.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

# define	_TOK___u0	257
# define	_TOK___u1	258
# define	_TOK___u10	259
# define	_TOK___u11	260
# define	_TOK___u12	261
# define	_TOK___u13	262
# define	_TOK___u14	263
# define	_TOK___u15	264
# define	_TOK___u16	265
# define	_TOK___u17	266
# define	_TOK___u18	267
# define	_TOK___u19	268
# define	_TOK___u2	269
# define	_TOK___u20	270
# define	_TOK___u21	271
# define	_TOK___u22	272
# define	_TOK___u23	273
# define	_TOK___u24	274
# define	_TOK___u25	275
# define	_TOK___u26	276
# define	_TOK___u3	277
# define	_TOK___u4	278
# define	_TOK___u5	279
# define	_TOK___u6	280
# define	_TOK___u7	281
# define	_TOK___u8	282
# define	_TOK___u9	283
# define	_TOK_boolconst	284
# define	_TOK_equals	285
# define	_TOK_genop	286
# define	_TOK_identifier	287
# define	_TOK_integer	288
# define	_TOK_level02	289
# define	_TOK_level03	290
# define	_TOK_level05	291
# define	_TOK_level06	292
# define	_TOK_level07	293
# define	_TOK_level08	294
# define	_TOK_level09	295
# define	_TOK_level10	296
# define	_TOK_level11	297
# define	_TOK_nil	298
# define	_TOK_quotetick	299
# define	_TOK_string	300

#line 2 "kp.y"

#include <stdio.h>
#include "mem.h"
#include "sexp.h"
#define YYDEBUG 1
void yyerror( char *s );
extern FILE *yyin;
extern char *yytext;
char *__kp_filename;
extern int __kp_token_start_line, __kp_token_end_line;
extern int __kp_token_start_char, __kp_token_end_char;
extern int __kp_token_start_gchar, __kp_token_end_gchar;
extern sexp __kp_where_stamp( void );
extern char *__kp_strdoop_no_quotes( char *string );
sexp _ccc_top=0;

#line 19 "kp.y"
#ifndef YYSTYPE
typedef union {
  char *c;
  sexp s;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		221
#define	YYFLAG		-32768
#define	YYNTBASE	47

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 300 ? yytranslate[x] : 129)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     2,     6,    10,    14,    17,    21,    27,    31,
      35,    39,    43,    47,    51,    55,    59,    63,    67,    77,
      87,    89,    93,    98,   101,   103,   105,   109,   111,   113,
     116,   120,   123,   125,   127,   131,   133,   135,   138,   142,
     144,   146,   148,   150,   154,   158,   161,   163,   165,   167,
     172,   174,   178,   180,   184,   186,   189,   192,   194,   196,
     198,   200,   202,   204,   207,   210,   212,   215,   221,   224,
     226,   228,   236,   242,   250,   252,   255,   256,   258,   259,
     263,   265,   267,   268,   272,   274,   277,   278,   280,   281,
     285,   287,   290,   291,   293,   295,   297,   299,   301,   303,
     305,   307,   309,   311,   313,   315,   317,   319,   321,   323,
     325,   327,   329,   331,   333,   335,   337,   339,   341,   343,
     345,   347,   349,   351,   353,   355,   357,   359,   361,   363,
     365,   367,   369,   371,   373,   375,   377
};
static const short yyrhs[] =
{
      63,     0,    85,    82,    97,     0,   105,    61,    52,     0,
     115,   113,    69,     0,   106,    69,     0,   107,    84,   108,
       0,   109,   115,   107,    67,   108,     0,    69,   117,    69,
       0,    69,   118,    69,     0,    69,   119,    69,     0,    69,
     120,    69,     0,    69,   121,    69,     0,    69,   122,    69,
       0,    69,   123,    69,     0,    69,   124,    69,     0,    69,
     125,    69,     0,    69,   114,    69,     0,   110,    85,    69,
     111,    69,   111,    69,    97,    52,     0,   110,    85,    71,
     111,    69,   111,    69,    97,    52,     0,    76,     0,   115,
      87,   115,     0,    88,    89,    59,   111,     0,    88,    68,
       0,    77,     0,   115,     0,    85,    79,    97,     0,   115,
       0,    75,     0,    69,   111,     0,    90,    69,   111,     0,
      90,   111,     0,    74,     0,    52,     0,    89,    59,   111,
       0,    68,     0,    58,     0,   115,    91,     0,    92,   115,
     111,     0,    70,     0,    55,     0,    73,     0,    53,     0,
      93,    62,   111,     0,    94,   128,   111,     0,    66,    64,
       0,    64,     0,    95,     0,    81,     0,    96,   115,    61,
      52,     0,    60,     0,    69,   113,    69,     0,    54,     0,
      85,    69,    97,     0,    49,     0,    98,    69,     0,    99,
      69,     0,   116,     0,   112,     0,   126,     0,   128,     0,
      52,     0,    51,     0,    69,    48,     0,   127,   115,     0,
      57,     0,   100,   115,     0,   101,    85,    69,    97,    52,
       0,    89,    59,     0,    52,     0,    74,     0,   102,    52,
     101,    85,    69,    97,   111,     0,   103,    85,    69,    97,
      52,     0,   103,    85,    69,    97,    52,   104,    72,     0,
      56,     0,    64,    76,     0,     0,    78,     0,     0,    50,
      86,    78,     0,    50,     0,    80,     0,     0,   115,    86,
      80,     0,   115,     0,    65,    81,     0,     0,    83,     0,
       0,    69,    86,    83,     0,    69,     0,    64,    84,     0,
       0,     3,     0,     4,     0,     5,     0,     6,     0,     7,
       0,     8,     0,     9,     0,    10,     0,    11,     0,    12,
       0,    13,     0,    14,     0,    15,     0,    16,     0,    17,
       0,    18,     0,    19,     0,    20,     0,    21,     0,    22,
       0,    23,     0,    24,     0,    25,     0,    26,     0,    27,
       0,    28,     0,    29,     0,    30,     0,    31,     0,    32,
       0,    33,     0,    34,     0,    35,     0,    36,     0,    37,
       0,    38,     0,    39,     0,    40,     0,    41,     0,    42,
       0,    43,     0,    44,     0,    45,     0,    46,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,    40,    44,    53,    64,    74,    83,    92,   102,   111,
     119,   127,   135,   143,   151,   159,   167,   175,   185,   195,
     206,   215,   225,   232,   240,   249,   258,   267,   276,   285,
     292,   299,   305,   311,   317,   324,   330,   336,   342,   348,
     354,   360,   366,   372,   378,   386,   394,   402,   411,   420,
     432,   439,   446,   452,   458,   464,   471,   478,   484,   490,
     496,   502,   508,   514,   521,   527,   533,   541,   551,   560,
     567,   575,   585,   594,   606,   617,   621,   625,   629,   633,
     636,   640,   644,   648,   651,   655,   659,   663,   667,   671,
     674,   678,   682,   688,   694,   700,   706,   712,   718,   724,
     730,   736,   742,   748,   754,   760,   766,   772,   778,   784,
     790,   796,   802,   808,   814,   820,   826,   832,   838,   844,
     850,   856,   862,   868,   874,   880,   886,   892,   898,   904,
     910,   916,   922,   928,   934,   940,   946
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "_TOK___u0", "_TOK___u1", "_TOK___u10", 
  "_TOK___u11", "_TOK___u12", "_TOK___u13", "_TOK___u14", "_TOK___u15", 
  "_TOK___u16", "_TOK___u17", "_TOK___u18", "_TOK___u19", "_TOK___u2", 
  "_TOK___u20", "_TOK___u21", "_TOK___u22", "_TOK___u23", "_TOK___u24", 
  "_TOK___u25", "_TOK___u26", "_TOK___u3", "_TOK___u4", "_TOK___u5", 
  "_TOK___u6", "_TOK___u7", "_TOK___u8", "_TOK___u9", "_TOK_boolconst", 
  "_TOK_equals", "_TOK_genop", "_TOK_identifier", "_TOK_integer", 
  "_TOK_level02", "_TOK_level03", "_TOK_level05", "_TOK_level06", 
  "_TOK_level07", "_TOK_level08", "_TOK_level09", "_TOK_level10", 
  "_TOK_level11", "_TOK_nil", "_TOK_quotetick", "_TOK_string", "_top", 
  "paramlist", "lambda", "adecl", "callcc", "block", "class", "opexpr", 
  "for", "statement_list", "objectaccess", "export", "decllist", 
  "variable", "arglist", "importspec", "top", "statement", 
  "class_statement", "class_access_modifier", "class_statement_list", 
  "function", "expression", "while", "fordecls", "elsepart", "do", "if", 
  "program", "__u30", "__u31", "__u32", "__u33", "__u34", "__u35", 
  "__u27", "__u28", "__u29", "__u0", "__u1", "__u10", "__u11", "__u12", 
  "__u13", "__u14", "__u15", "__u16", "__u17", "__u18", "__u19", "__u2", 
  "__u20", "__u21", "__u22", "__u23", "__u24", "__u25", "__u26", "__u3", 
  "__u4", "__u5", "__u6", "__u7", "__u8", "__u9", "boolconst", "equals", 
  "genop", "identifier", "integer", "level02", "level03", "level05", 
  "level06", "level07", "level08", "level09", "level10", "level11", "nil", 
  "quotetick", "string", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,    47,    48,    49,    50,    51,    52,    53,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    55,    55,
      56,    57,    58,    58,    59,    60,    61,    62,    63,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    65,    65,    66,    67,    68,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    70,    71,    72,
      72,    73,    74,    74,    75,    76,    76,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    84,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     1,     3,     3,     3,     2,     3,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     9,     9,
       1,     3,     4,     2,     1,     1,     3,     1,     1,     2,
       3,     2,     1,     1,     3,     1,     1,     2,     3,     1,
       1,     1,     1,     3,     3,     2,     1,     1,     1,     4,
       1,     3,     1,     3,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     2,     5,     2,     1,
       1,     7,     5,     7,     1,     2,     0,     1,     0,     3,
       1,     1,     0,     3,     1,     2,     0,     1,     0,     3,
       1,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
      76,    93,    96,    97,    98,   100,   101,   102,   104,   106,
     107,   108,   109,   110,   111,   113,   114,   115,   117,   118,
     120,   123,   124,   134,   135,   136,    54,    62,    33,    42,
      52,    40,    74,    65,    36,    50,     1,    76,    35,     0,
      39,    41,    32,    28,    20,     0,     0,    78,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    92,     0,     0,    58,    25,    57,    59,     0,    60,
      75,   119,   121,   122,   125,   126,   127,   128,   129,   130,
     131,   132,   133,    63,    88,    29,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    61,     0,    25,
      23,    78,    80,     0,    24,    77,     0,     0,    31,     0,
       0,    27,     0,     0,    55,    56,    66,     0,     0,     0,
       0,    82,     5,    92,     0,     0,     0,    95,    99,     0,
      37,    64,    90,     0,    87,    51,    17,     8,     9,    10,
      11,    12,    13,    14,    15,    16,   105,    53,     0,    94,
       0,    34,     0,    30,    38,    43,    44,     0,     0,     0,
       0,     3,     0,    81,    84,    91,   116,     6,    86,     0,
       0,    78,    21,     0,     2,    22,    79,     4,    49,     0,
       0,     0,    26,     0,   103,    46,    86,     0,     0,    48,
      47,     0,     0,    68,    89,    67,     0,    72,    83,    85,
      45,     7,     0,     0,     0,   112,     0,     0,     0,    71,
      69,    73,    70,     0,     0,     0,     0,    18,    19,     0,
       0,     0
};

static const short yydefgoto[] =
{
     219,    83,    26,   102,    27,    97,    29,    30,    31,    32,
      33,    34,   103,    35,   120,   110,    36,    37,   186,   187,
     188,    38,    39,    40,   170,   211,    41,    42,    43,    44,
     104,   105,   162,   163,   189,   133,   134,   124,    45,   150,
     129,    46,    47,    48,   130,    49,    50,    51,   190,    52,
     147,    53,    54,    55,    56,    57,    58,   206,    59,    60,
      61,   167,    62,    63,    85,    64,    86,    87,    99,    66,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    67,
      68,    69
};

static const short yypact[] =
{
     259,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   452,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,   259,-32768,   407,
  -32768,-32768,-32768,-32768,-32768,   384,    -2,   -31,   336,   -31,
     -31,   -38,   -31,   384,   384,   -31,    10,   -10,    10,    10,
     384,   259,   -31,    10,-32768,     9,-32768,-32768,   -31,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,   384,-32768,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,-32768,   420,    20,
  -32768,   -31,    19,     2,-32768,-32768,    -4,   407,-32768,     2,
       2,-32768,     2,    10,    62,    62,-32768,   384,    14,   384,
     -10,   -31,    62,   259,     3,   -10,   360,-32768,-32768,   -31,
  -32768,-32768,   437,    13,-32768,    62,    27,    10,    18,   225,
      23,   186,    89,   159,   134,   209,-32768,-32768,     2,-32768,
     -31,-32768,   384,-32768,-32768,-32768,-32768,   -10,   420,    10,
     420,-32768,    13,-32768,    19,-32768,-32768,-32768,   304,   407,
       2,   -31,-32768,   384,-32768,-32768,-32768,    62,-32768,   -10,
     384,   -10,-32768,   -31,-32768,-32768,   304,   259,     3,-32768,
  -32768,   384,   384,-32768,-32768,-32768,   420,    16,-32768,-32768,
  -32768,-32768,   407,   407,     2,-32768,    -1,   384,   384,-32768,
  -32768,-32768,-32768,   420,   420,   -10,   -10,-32768,-32768,    39,
      41,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,     0,-32768,-32768,-32768,-32768,
  -32768,-32768,   -82,-32768,   -57,-32768,-32768,   -55,-32768,-32768,
  -32768,    25,   -44,-32768,-32768,-32768,-32768,  -132,-32768,    43,
  -32768,   -74,-32768,   -93,   -91,-32768,   -77,   -17,    95,  -129,
  -32768,-32768,   -35,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
    -126,-32768,-32768,-32768,   -11,-32768,-32768,-32768,-32768,-32768,
     -16,   -78,-32768,-32768,   -26,-32768,     5,-32768,    17,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,    61
};


#define	YYLAST		495


static const short yytable[] =
{
      28,    98,    21,   173,   107,     3,   123,   174,    25,   114,
     115,   101,     8,     1,   127,    17,   122,    65,   128,   148,
      14,     1,   108,   149,    17,   127,     1,    72,   146,   166,
       1,    71,   179,    12,   181,   183,   182,    28,   205,   220,
     132,   221,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,    74,    65,    73,   157,   118,    74,    75,
      76,    28,    74,    75,   106,     1,   109,   111,   123,   113,
     204,   100,   116,   158,   212,   160,   176,   151,    65,   125,
      70,   153,   169,   154,   155,   131,   156,   215,   216,   193,
     198,   171,     1,    72,    73,   199,   194,    74,    75,    76,
      77,    78,    79,    80,    81,    82,   165,   159,   177,   168,
     201,   152,   112,   185,     0,     0,     0,     0,   106,     0,
     161,    73,   175,    28,    74,    75,    76,    77,    78,   132,
       0,   185,   200,     0,    84,     0,   196,     1,   164,     0,
      65,     0,     0,   191,   192,     0,   172,   202,   203,     0,
       0,   117,     0,   119,   121,     0,     0,   178,   126,     0,
       0,     0,     1,   213,   214,     0,    73,   106,    28,    74,
      75,    76,    77,    78,    79,    80,   207,   208,   209,   195,
       0,   197,     0,     0,     0,    65,    28,    28,   106,     1,
       0,    73,     0,    84,    74,    75,    76,    77,    78,    79,
     164,     0,    84,    65,    65,     0,   210,     0,   121,    84,
      84,     0,     1,     0,     0,   217,   218,    84,    73,     0,
       0,    74,    75,    76,    77,     0,     0,    84,     1,     0,
      84,    84,    84,    84,    84,    84,    84,    84,    84,    84,
      84,    73,     0,     0,    74,    75,    76,    77,    78,    79,
      80,    81,     0,    84,   180,    84,     0,    73,     0,     0,
      74,    75,     1,     0,    84,     2,     3,     4,     0,     5,
       6,     7,    84,     8,     0,     9,    10,    11,    12,    13,
      14,     0,    15,    16,    17,     0,    18,    19,     0,    20,
       0,    84,    21,    22,     0,     0,     0,    84,    84,     0,
       0,     0,     0,    23,    24,    25,     0,     1,    84,    84,
       2,     3,     4,     0,     5,     6,     7,   184,     8,     0,
       9,    10,    11,    12,    13,    14,     0,    15,    16,    17,
       0,    18,    19,     0,    20,     0,     0,    21,    22,     1,
       0,     0,     0,     0,     0,     0,     0,     0,    23,    24,
      25,     0,     9,    10,    11,     0,     0,     0,     0,    15,
      16,    17,     0,     1,     0,    71,    20,     3,     0,    21,
      22,     0,     0,     0,     0,     0,     9,    10,    11,     0,
      23,    24,    25,    15,    16,    17,     0,     1,     0,     0,
      20,     0,     0,    21,    22,     0,     0,     0,     0,     0,
       9,    10,    11,     0,    23,    24,    25,    15,    16,    17,
       1,     0,     0,     0,    20,     0,     0,    21,    22,     0,
       0,     0,     0,     1,     0,     0,     0,     0,    23,    24,
      25,     0,     0,     0,     0,   146,    71,     0,    72,    73,
       1,   149,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    72,    73,     0,     0,    74,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,     0,     0,    72,    73,
       0,     0,    74,    75,    76,    77,    78,    79,    80,    81,
      82,   -61,     0,   -61,   -61,     0,     0,   -61,   -61,   -61,
     -61,   -61,   -61,   -61,   -61,   -61
};

static const short yycheck[] =
{
       0,    45,    33,   132,    48,     7,    61,   133,    46,    53,
      54,    46,    14,     3,     5,    25,    60,     0,     9,   101,
      21,     3,    48,     4,    25,     5,     3,    31,    15,    26,
       3,    29,   158,    19,   160,   164,   162,    37,    22,     0,
      84,     0,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    35,    37,    32,   113,    57,    35,    36,
      37,    61,    35,    36,    47,     3,    49,    50,   123,    52,
     196,    46,    55,   117,   206,   119,   150,   103,    61,    62,
      37,   107,   126,   109,   110,    68,   112,   213,   214,   171,
     183,   126,     3,    31,    32,   186,   173,    35,    36,    37,
      38,    39,    40,    41,    42,    43,   123,   118,   152,   125,
     188,   106,    51,   168,    -1,    -1,    -1,    -1,   101,    -1,
     120,    32,   148,   123,    35,    36,    37,    38,    39,   173,
      -1,   186,   187,    -1,    39,    -1,   180,     3,   121,    -1,
     123,    -1,    -1,   169,   170,    -1,   129,   191,   192,    -1,
      -1,    56,    -1,    58,    59,    -1,    -1,   157,    63,    -1,
      -1,    -1,     3,   207,   208,    -1,    32,   150,   168,    35,
      36,    37,    38,    39,    40,    41,   202,   203,   204,   179,
      -1,   181,    -1,    -1,    -1,   168,   186,   187,   171,     3,
      -1,    32,    -1,    98,    35,    36,    37,    38,    39,    40,
     183,    -1,   107,   186,   187,    -1,   206,    -1,   113,   114,
     115,    -1,     3,    -1,    -1,   215,   216,   122,    32,    -1,
      -1,    35,    36,    37,    38,    -1,    -1,   132,     3,    -1,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,    32,    -1,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,   158,   159,   160,    -1,    32,    -1,    -1,
      35,    36,     3,    -1,   169,     6,     7,     8,    -1,    10,
      11,    12,   177,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    25,    -1,    27,    28,    -1,    30,
      -1,   196,    33,    34,    -1,    -1,    -1,   202,   203,    -1,
      -1,    -1,    -1,    44,    45,    46,    -1,     3,   213,   214,
       6,     7,     8,    -1,    10,    11,    12,    13,    14,    -1,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    25,
      -1,    27,    28,    -1,    30,    -1,    -1,    33,    34,     3,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    -1,    16,    17,    18,    -1,    -1,    -1,    -1,    23,
      24,    25,    -1,     3,    -1,    29,    30,     7,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,    -1,
      44,    45,    46,    23,    24,    25,    -1,     3,    -1,    -1,
      30,    -1,    -1,    33,    34,    -1,    -1,    -1,    -1,    -1,
      16,    17,    18,    -1,    44,    45,    46,    23,    24,    25,
       3,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,    -1,
      -1,    -1,    -1,     3,    -1,    -1,    -1,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    15,    29,    -1,    31,    32,
       3,     4,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    31,    32,    -1,    -1,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    -1,    -1,    -1,    -1,    31,    32,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    29,    -1,    31,    32,    -1,    -1,    35,    36,    37,
      38,    39,    40,    41,    42,    43
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 1:
#line 40 "kp.y"
{ yyval.s = yyvsp[0].s;  _ccc_top = yyvsp[0].s; ;
    break;}
case 2:
#line 45 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(paramlist), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 3:
#line 54 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(lambda), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 4:
#line 65 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(adecl), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 5:
#line 75 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(callcc), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 6:
#line 84 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(block), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 7:
#line 93 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-3].s, s );
      s = cons( S(class), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 8:
#line 103 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level02), s ) );
      yyval.s = s;
    ;
    break;}
case 9:
#line 111 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level03), s ) );
      yyval.s = s;
    ;
    break;}
case 10:
#line 119 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level05), s ) );
      yyval.s = s;
    ;
    break;}
case 11:
#line 127 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level06), s ) );
      yyval.s = s;
    ;
    break;}
case 12:
#line 135 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level07), s ) );
      yyval.s = s;
    ;
    break;}
case 13:
#line 143 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level08), s ) );
      yyval.s = s;
    ;
    break;}
case 14:
#line 151 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level09), s ) );
      yyval.s = s;
    ;
    break;}
case 15:
#line 159 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level10), s ) );
      yyval.s = s;
    ;
    break;}
case 16:
#line 167 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(level11), s ) );
      yyval.s = s;
    ;
    break;}
case 17:
#line 175 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(opexpr), cons( S(genop), s ) );
      yyval.s = s;
    ;
    break;}
case 18:
#line 186 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( yyvsp[-4].s, s );
      s = cons( yyvsp[-6].s, s );
      s = cons( S(for), cons( S(for), s ) );
      yyval.s = s;
    ;
    break;}
case 19:
#line 195 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( yyvsp[-4].s, s );
      s = cons( yyvsp[-6].s, s );
      s = cons( S(for), cons( S(forwithdecl), s ) );
      yyval.s = s;
    ;
    break;}
case 20:
#line 207 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement_list), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 21:
#line 216 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(objectaccess), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 22:
#line 226 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(export), cons( S(decls), s ) );
      yyval.s = s;
    ;
    break;}
case 23:
#line 232 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(export), cons( S(fun), s ) );
      yyval.s = s;
    ;
    break;}
case 24:
#line 241 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(decllist), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 25:
#line 250 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(variable), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 26:
#line 259 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(arglist), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 27:
#line 268 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(importspec), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 28:
#line 277 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(top), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 29:
#line 286 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(statement), cons( S(expressionstatement), s ) );
      yyval.s = s;
    ;
    break;}
case 30:
#line 292 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(statement), cons( S(returnargs), s ) );
      yyval.s = s;
    ;
    break;}
case 31:
#line 299 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(statement), cons( S(returnnoargs), s ) );
      yyval.s = s;
    ;
    break;}
case 32:
#line 305 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement), cons( S(if), s ) );
      yyval.s = s;
    ;
    break;}
case 33:
#line 311 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement), cons( S(block), s ) );
      yyval.s = s;
    ;
    break;}
case 34:
#line 317 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(statement), cons( S(decls), s ) );
      yyval.s = s;
    ;
    break;}
case 35:
#line 324 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement), cons( S(function), s ) );
      yyval.s = s;
    ;
    break;}
case 36:
#line 330 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement), cons( S(export), s ) );
      yyval.s = s;
    ;
    break;}
case 37:
#line 336 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(statement), cons( S(label), s ) );
      yyval.s = s;
    ;
    break;}
case 38:
#line 342 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(statement), cons( S(goto), s ) );
      yyval.s = s;
    ;
    break;}
case 39:
#line 348 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement), cons( S(while), s ) );
      yyval.s = s;
    ;
    break;}
case 40:
#line 354 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement), cons( S(for), s ) );
      yyval.s = s;
    ;
    break;}
case 41:
#line 360 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement), cons( S(do), s ) );
      yyval.s = s;
    ;
    break;}
case 42:
#line 366 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(statement), cons( S(class), s ) );
      yyval.s = s;
    ;
    break;}
case 43:
#line 372 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(statement), cons( S(import), s ) );
      yyval.s = s;
    ;
    break;}
case 44:
#line 378 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(statement), cons( S(include), s ) );
      yyval.s = s;
    ;
    break;}
case 45:
#line 387 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( S(class_statement), cons( S(modified), s ) );
      yyval.s = s;
    ;
    break;}
case 46:
#line 394 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(class_statement), cons( S(unmodified), s ) );
      yyval.s = s;
    ;
    break;}
case 47:
#line 403 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(class_access_modifier), cons( S(public), s ) );
      yyval.s = s;
    ;
    break;}
case 48:
#line 412 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(class_statement_list), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 49:
#line 421 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( yyvsp[-3].s, s );
      s = cons( S(function), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 50:
#line 433 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(variable), s ) );
      yyval.s = s;
    ;
    break;}
case 51:
#line 439 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(expression), cons( S(assignment), s ) );
      yyval.s = s;
    ;
    break;}
case 52:
#line 446 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(opexpr), s ) );
      yyval.s = s;
    ;
    break;}
case 53:
#line 452 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-1].s, s );
      s = cons( S(expression), cons( S(paren), s ) );
      yyval.s = s;
    ;
    break;}
case 54:
#line 458 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(lambda), s ) );
      yyval.s = s;
    ;
    break;}
case 55:
#line 464 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( S(expression), cons( S(show), s ) );
      yyval.s = s;
    ;
    break;}
case 56:
#line 471 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( S(expression), cons( S(yield), s ) );
      yyval.s = s;
    ;
    break;}
case 57:
#line 478 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(integer), s ) );
      yyval.s = s;
    ;
    break;}
case 58:
#line 484 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(boolconst), s ) );
      yyval.s = s;
    ;
    break;}
case 59:
#line 490 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(nil), s ) );
      yyval.s = s;
    ;
    break;}
case 60:
#line 496 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(string), s ) );
      yyval.s = s;
    ;
    break;}
case 61:
#line 502 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(block), s ) );
      yyval.s = s;
    ;
    break;}
case 62:
#line 508 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(callcc), s ) );
      yyval.s = s;
    ;
    break;}
case 63:
#line 514 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( S(expression), cons( S(funcall), s ) );
      yyval.s = s;
    ;
    break;}
case 64:
#line 521 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(quoteatom), s ) );
      yyval.s = s;
    ;
    break;}
case 65:
#line 527 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(objectaccess), s ) );
      yyval.s = s;
    ;
    break;}
case 66:
#line 533 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(expression), cons( S(new), s ) );
      yyval.s = s;
    ;
    break;}
case 67:
#line 542 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( S(while), cons( S(while), s ) );
      yyval.s = s;
    ;
    break;}
case 68:
#line 552 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(fordecls), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 69:
#line 561 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(elsepart), cons( S(block), s ) );
      yyval.s = s;
    ;
    break;}
case 70:
#line 567 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(elsepart), cons( S(if), s ) );
      yyval.s = s;
    ;
    break;}
case 71:
#line 576 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[-2].s, s );
      s = cons( yyvsp[-5].s, s );
      s = cons( S(do), cons( S(do), s ) );
      yyval.s = s;
    ;
    break;}
case 72:
#line 586 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( yyvsp[-4].s, s );
      s = cons( S(if), cons( S(if), s ) );
      yyval.s = s;
    ;
    break;}
case 73:
#line 594 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( yyvsp[-1].s, s );
      s = cons( yyvsp[-2].s, s );
      s = cons( yyvsp[-4].s, s );
      s = cons( yyvsp[-6].s, s );
      s = cons( S(if), cons( S(ifelse), s ) );
      yyval.s = s;
    ;
    break;}
case 74:
#line 607 "kp.y"
{
      sexp s = nil;
      s = cons( yyvsp[0].s, s );
      s = cons( S(program), cons( S(default), s ) );
      yyval.s = s;
    ;
    break;}
case 75:
#line 618 "kp.y"
{
      yyval.s = cons( yyvsp[-1].s, yyvsp[0].s );;
    ;
    break;}
case 76:
#line 621 "kp.y"
{
    yyval.s = nil;
    ;
    break;}
case 77:
#line 626 "kp.y"
{
      yyval.s = yyvsp[0].s;
    ;
    break;}
case 78:
#line 629 "kp.y"
{
      yyval.s = nil;
    ;
    break;}
case 79:
#line 633 "kp.y"
{
    yyval.s = cons( yyvsp[-2].s, yyvsp[0].s );
    ;
    break;}
case 80:
#line 636 "kp.y"
{
      yyval.s = cons( yyvsp[0].s, nil );
    ;
    break;}
case 81:
#line 641 "kp.y"
{
      yyval.s = yyvsp[0].s;
    ;
    break;}
case 82:
#line 644 "kp.y"
{
      yyval.s = nil;
    ;
    break;}
case 83:
#line 648 "kp.y"
{
    yyval.s = cons( yyvsp[-2].s, yyvsp[0].s );
    ;
    break;}
case 84:
#line 651 "kp.y"
{
      yyval.s = cons( yyvsp[0].s, nil );
    ;
    break;}
case 85:
#line 656 "kp.y"
{
      yyval.s = cons( yyvsp[-1].s, yyvsp[0].s );;
    ;
    break;}
case 86:
#line 659 "kp.y"
{
    yyval.s = nil;
    ;
    break;}
case 87:
#line 664 "kp.y"
{
      yyval.s = yyvsp[0].s;
    ;
    break;}
case 88:
#line 667 "kp.y"
{
      yyval.s = nil;
    ;
    break;}
case 89:
#line 671 "kp.y"
{
    yyval.s = cons( yyvsp[-2].s, yyvsp[0].s );
    ;
    break;}
case 90:
#line 674 "kp.y"
{
      yyval.s = cons( yyvsp[0].s, nil );
    ;
    break;}
case 91:
#line 679 "kp.y"
{
      yyval.s = cons( yyvsp[-1].s, yyvsp[0].s );;
    ;
    break;}
case 92:
#line 682 "kp.y"
{
    yyval.s = nil;
    ;
    break;}
case 93:
#line 688 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 94:
#line 694 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 95:
#line 700 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 96:
#line 706 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 97:
#line 712 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 98:
#line 718 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 99:
#line 724 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 100:
#line 730 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 101:
#line 736 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 102:
#line 742 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 103:
#line 748 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 104:
#line 754 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 105:
#line 760 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 106:
#line 766 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 107:
#line 772 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 108:
#line 778 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 109:
#line 784 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 110:
#line 790 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 111:
#line 796 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 112:
#line 802 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 113:
#line 808 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 114:
#line 814 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 115:
#line 820 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 116:
#line 826 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 117:
#line 832 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 118:
#line 838 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 119:
#line 844 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 120:
#line 850 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 121:
#line 856 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 122:
#line 862 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 123:
#line 868 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 124:
#line 874 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 125:
#line 880 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 126:
#line 886 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 127:
#line 892 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 128:
#line 898 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 129:
#line 904 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 130:
#line 910 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 131:
#line 916 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 132:
#line 922 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 133:
#line 928 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 134:
#line 934 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 135:
#line 940 "kp.y"
{
  sexp s;
  s = mksym( strdoop( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
case 136:
#line 946 "kp.y"
{
  sexp s;
  s = mkstring( __kp_strdoop_no_quotes( yytext ) );
  SEXP_PROPERTIES( s ) = __kp_where_stamp();
  yyval.s = s;
 ;
    break;}
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 953 "kp.y"

sexp __kp_where_stamp()
{
  static char spbuf[2048];
  sexp s;

  s = sexp_build( "((file %)(line % %) (char % %) (gchar % %))",
    SEXP_MKSTRING( __kp_filename ),
    SEXP_MKINT( __kp_token_start_line ), SEXP_MKINT( __kp_token_end_line ),
    SEXP_MKINT( __kp_token_start_char ), SEXP_MKINT( __kp_token_end_char ),
    SEXP_MKINT( __kp_token_start_gchar ), SEXP_MKINT( __kp_token_end_gchar ) );

  return s;
}
char *__kp_strdoop_no_quotes( char *string )
{
  int c, len;
  char *dup;

  len = strlen( string );
  A(len>=2);
  c = string[len-1];
  string[len-1] = 0;

  dup = strdoop( string+1 );

  string[len-1] = c;

  return dup;
}
sexp kp_parse( char *filename, FILE *instream )
{
  yyin = instream;
  __kp_filename = filename == NULL ? "[NULL]" : filename;

  if (yyparse()) {
    return nil;
  } else {
    return _ccc_top;
  }
}
void yyerror( char *s )
{
  fprintf( stderr, "Syntax error at line %d, char %d
",
    __kp_token_start_line, __kp_token_start_char );
}
int yywrap()
{
  return 1;
}
