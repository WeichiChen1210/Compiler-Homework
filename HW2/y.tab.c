/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "compiler_hw2.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

int err_flag = 0;
int scope_num = 0;

struct symbols{
    char name[50];
    char kind[50];
    char type[50];
    int scope;
    char attribute[50];
    int printed;

    struct symbols *next;
};

struct symbols table[200];

/* Symbol table function - you can add new function if needed. */
int lookup_symbol();
void create_symbol();
void insert_symbol();
void dump_symbol();


#line 100 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ADD = 258,
    SUB = 259,
    MUL = 260,
    DIV = 261,
    MOD = 262,
    INC = 263,
    DEC = 264,
    MT = 265,
    LT = 266,
    MTE = 267,
    LTE = 268,
    EQ = 269,
    NE = 270,
    ASGN = 271,
    ADDASGN = 272,
    SUBASGN = 273,
    MULASGN = 274,
    DIVASGN = 275,
    MODASGN = 276,
    AND = 277,
    OR = 278,
    NOT = 279,
    LB = 280,
    RB = 281,
    LCB = 282,
    RCB = 283,
    LSB = 284,
    RSB = 285,
    COMMA = 286,
    IF = 287,
    ELSE = 288,
    FOR = 289,
    WHILE = 290,
    BREAK = 291,
    CONT = 292,
    PRINT = 293,
    RET = 294,
    QUOTA = 295,
    ID = 296,
    SEMICOLON = 297,
    C_COMMENT = 298,
    CPLUS_COMMENT = 299,
    I_CONST = 300,
    F_CONST = 301,
    STR_CONST = 302,
    STRING = 303,
    INT = 304,
    FLOAT = 305,
    BOOL = 306,
    VOID = 307,
    TRUE = 308,
    FALSE = 309
  };
#endif
/* Tokens.  */
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define MOD 262
#define INC 263
#define DEC 264
#define MT 265
#define LT 266
#define MTE 267
#define LTE 268
#define EQ 269
#define NE 270
#define ASGN 271
#define ADDASGN 272
#define SUBASGN 273
#define MULASGN 274
#define DIVASGN 275
#define MODASGN 276
#define AND 277
#define OR 278
#define NOT 279
#define LB 280
#define RB 281
#define LCB 282
#define RCB 283
#define LSB 284
#define RSB 285
#define COMMA 286
#define IF 287
#define ELSE 288
#define FOR 289
#define WHILE 290
#define BREAK 291
#define CONT 292
#define PRINT 293
#define RET 294
#define QUOTA 295
#define ID 296
#define SEMICOLON 297
#define C_COMMENT 298
#define CPLUS_COMMENT 299
#define I_CONST 300
#define F_CONST 301
#define STR_CONST 302
#define STRING 303
#define INT 304
#define FLOAT 305
#define BOOL 306
#define VOID 307
#define TRUE 308
#define FALSE 309

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 39 "compiler_hw2.y" /* yacc.c:355  */

    int i_val;
    double f_val;
    char* string;
    _Bool b_val;

#line 255 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 272 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  16
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   571

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  124
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   309

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    74,    74,    75,    79,    80,    84,    85,    92,    93,
      97,    98,   102,   103,   107,   108,   109,   110,   114,   115,
     116,   117,   118,   119,   120,   124,   128,   132,   133,   137,
     138,   142,   143,   147,   148,   152,   153,   154,   155,   156,
     157,   161,   165,   166,   170,   171,   175,   176,   180,   181,
     185,   186,   187,   191,   192,   193,   194,   198,   199,   203,
     204,   208,   209,   213,   214,   218,   219,   220,   224,   225,
     229,   230,   234,   235,   239,   243,   244,   245,   246,   250,
     251,   252,   253,   254,   255,   259,   263,   264,   265,   266,
     267,   268,   272,   273,   274,   278,   282,   283,   284,   285,
     286,   287,   288,   292,   293,   297,   298,   299,   303,   304,
     305,   306,   307,   311,   312,   313,   317,   318,   319,   320,
     325,   326,   327,   328,   329
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ADD", "SUB", "MUL", "DIV", "MOD", "INC",
  "DEC", "MT", "LT", "MTE", "LTE", "EQ", "NE", "ASGN", "ADDASGN",
  "SUBASGN", "MULASGN", "DIVASGN", "MODASGN", "AND", "OR", "NOT", "LB",
  "RB", "LCB", "RCB", "LSB", "RSB", "COMMA", "IF", "ELSE", "FOR", "WHILE",
  "BREAK", "CONT", "PRINT", "RET", "QUOTA", "ID", "SEMICOLON", "C_COMMENT",
  "CPLUS_COMMENT", "I_CONST", "F_CONST", "STR_CONST", "STRING", "INT",
  "FLOAT", "BOOL", "VOID", "TRUE", "FALSE", "$accept", "translation_unit",
  "external_declaration", "function_definition", "declaration_specifiers",
  "declaration_list", "compound_statement", "declarator", "in_scope",
  "out_scope", "declaration", "statement_list", "identifier_list",
  "init_declarator_list", "statement", "conditional_expression",
  "parameter_list", "init_declarator", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "print_statement", "logical_or_expression", "expression",
  "parameter_declaration", "initializer", "logical_and_expression",
  "assignment_expression", "initializer_list", "inclusive_or_expression",
  "unary_expression", "assignment_operator", "exclusive_or_expression",
  "postfix_expression", "unary_operator", "and_expression",
  "primary_expression", "argument_expression_list", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "type_specifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309
};
# endif

#define YYPACT_NINF -133

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-133)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      24,    21,  -133,  -133,  -133,  -133,  -133,  -133,     6,  -133,
    -133,    41,   519,  -133,   154,   144,  -133,  -133,  -133,    62,
      -7,  -133,   -12,    15,   361,    41,   -23,  -133,  -133,  -133,
    -133,   384,   -23,  -133,    21,  -133,  -133,   104,  -133,   192,
    -133,  -133,   497,   497,  -133,   497,  -133,   -25,  -133,  -133,
    -133,  -133,  -133,    39,    28,    49,  -133,  -133,  -133,    55,
     497,  -133,  -133,   146,   197,   194,   177,    52,  -133,  -133,
     384,  -133,  -133,  -133,   118,  -133,  -133,  -133,    21,   -16,
      11,  -133,  -133,    72,    75,    79,    76,   105,   125,   409,
     140,  -133,   244,  -133,  -133,  -133,  -133,  -133,  -133,    19,
    -133,  -133,  -133,    67,    81,  -133,   497,   497,  -133,  -133,
     419,   497,  -133,   497,   497,   497,   497,   497,   497,   497,
     497,   497,   497,   497,  -133,    64,  -133,  -133,  -133,  -133,
    -133,  -133,   497,    61,  -133,   158,  -133,   154,   497,   444,
     497,  -133,  -133,   180,  -133,    57,  -133,   283,  -133,  -133,
     497,  -133,  -133,  -133,    49,  -133,  -133,  -133,    77,   204,
     197,   197,   194,   194,   194,   194,   177,   177,  -133,  -133,
    -133,  -133,   138,   384,  -133,  -133,  -133,  -133,  -133,   115,
     444,   131,   168,   161,  -133,  -133,  -133,  -133,  -133,  -133,
     497,  -133,  -133,  -133,   322,   478,   322,   178,   183,  -133,
    -133,   189,   322,   132,  -133,   210,  -133,   322,  -133,   322,
     209,  -133,  -133,  -133
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    18,   123,   120,   121,   122,   124,     0,     2,
       4,     0,     0,     5,    10,     0,     1,     3,    27,    44,
       0,    33,    25,    25,     0,     0,     0,     9,    12,    11,
      19,     0,     0,     7,     0,    28,    24,     0,    14,     0,
      92,    93,     0,     0,    94,     0,    21,     0,    96,    97,
      98,   100,   101,     0,    41,    59,    68,   116,    74,    75,
       0,    85,    86,    95,   105,   108,   113,    44,     8,    13,
       0,    70,    45,    65,   116,     6,    34,    31,    64,     0,
       0,    42,    46,     0,     0,     0,     0,     0,     0,     0,
       0,    35,     0,    29,    36,    37,    38,    39,    40,     0,
      61,    76,    77,     0,     0,    20,     0,     0,    90,    91,
       0,     0,    78,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    72,     0,    79,    80,    81,    82,
      83,    84,     0,    63,    26,     0,    26,     0,     0,     0,
       0,    54,    53,     0,    55,     0,    26,     0,    26,    30,
       0,    47,   102,    99,    60,    69,    88,   103,     0,     0,
     106,   107,   110,   109,   112,   111,   114,   115,   117,   118,
     119,    66,     0,     0,    71,    23,    32,    22,    43,     0,
       0,     0,     0,     0,    56,    16,    26,    15,    62,    89,
       0,    87,    67,    73,     0,     0,     0,     0,     0,    17,
     104,    48,     0,     0,    50,     0,    57,     0,    51,     0,
       0,    49,    52,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,   231,  -133,     3,    -6,     4,     7,   233,  -127,
      12,   167,  -133,  -133,   -87,   234,  -133,   225,  -132,  -133,
    -133,  -133,  -133,  -133,   -44,   123,   -68,   155,   -31,  -133,
     156,    10,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
     136,    96,   135,  -133
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    25,    26,    91,    12,    37,   175,
      28,    92,    79,    20,    93,    71,    80,    21,    94,    95,
      96,    97,    98,    54,    99,    81,    72,    55,   100,   125,
      56,    74,   132,    58,    59,    60,    61,    62,   158,    63,
      64,    65,    66,    14
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      73,   103,   124,    11,    23,   149,    16,   180,    15,   177,
     134,    11,    13,    32,    36,   135,    27,    29,    19,   185,
      13,   187,   104,    33,    34,     3,     4,     5,     6,     7,
      68,     1,    67,    90,    57,    35,    75,   136,    69,    73,
      78,    67,   137,    38,    69,   145,     1,     2,   195,     1,
     150,   106,   101,   102,     3,     4,     5,     6,     7,   199,
     149,   151,     2,   108,   109,     2,     1,   159,    31,   105,
     112,   107,     3,     4,     5,     6,     7,    22,    31,   157,
     110,    24,     2,    18,   111,   133,    22,    22,   150,    23,
      24,    24,   171,   152,   179,   172,   181,   138,   150,   184,
     139,   174,    69,   189,   140,   193,   173,   201,   190,   204,
       3,     4,     5,     6,     7,   208,    57,    57,   141,   188,
     211,   153,   212,    57,    57,    57,    57,    57,    57,    57,
      57,   168,   169,   170,   126,   127,   128,   129,   130,   131,
      78,   194,    73,    40,    41,    77,   150,   142,    42,    43,
     143,   203,     3,     4,     5,     6,     7,   196,   209,   200,
     113,   114,   150,   150,    44,    45,   192,    23,   146,    22,
      30,    82,    83,    24,    84,    85,    86,    87,    88,    89,
      47,    48,   121,   122,   123,    49,    50,   198,     3,     4,
       5,     6,     7,    51,    52,    40,    41,   119,   120,   176,
      42,    43,     3,     4,     5,     6,     7,   115,   116,   117,
     118,   162,   163,   164,   165,   197,    44,    45,   205,    23,
     182,   183,   207,    82,    83,   206,    84,    85,    86,    87,
      88,    89,    47,    48,   191,   150,   210,    49,    50,    17,
       3,     4,     5,     6,     7,    51,    52,    40,    41,   160,
     161,   213,    42,    43,   166,   167,    39,   147,    53,    76,
     178,   154,     0,   155,     0,     0,     0,     0,    44,    45,
       0,    23,   148,     0,     0,    82,    83,     0,    84,    85,
      86,    87,    88,    89,    47,    48,    40,    41,     0,    49,
      50,    42,    43,     0,     0,     0,     0,    51,    52,     0,
       0,     0,     0,     0,     0,     0,     0,    44,    45,     0,
      23,   186,     0,     0,    82,    83,     0,    84,    85,    86,
      87,    88,    89,    47,    48,    40,    41,     0,    49,    50,
      42,    43,     0,     0,     0,     0,    51,    52,     0,     0,
       0,     0,     0,     0,     0,     0,    44,    45,     0,    23,
       0,     0,     0,    82,    83,     0,    84,    85,    86,    87,
      88,    89,    47,    48,    40,    41,     0,    49,    50,    42,
      43,     0,     0,     0,     0,    51,    52,     0,     0,     0,
       0,     0,     0,     0,     0,    44,    45,    40,    41,     0,
       0,    46,    42,    43,     0,     0,     0,     0,     0,     0,
       0,    47,    48,     0,     0,     0,    49,    50,    44,    45,
       0,    70,    40,    41,    51,    52,     0,    42,    43,     0,
       0,     0,    40,    41,    47,    48,     0,    42,    43,    49,
      50,     0,     0,    44,    45,     0,     0,    51,    52,     0,
       0,     0,     0,    44,    45,   156,     0,    40,    41,    47,
      48,   144,    42,    43,    49,    50,     0,     0,     0,    47,
      48,     0,    51,    52,    49,    50,     0,     0,    44,    45,
       0,     0,    51,    52,     0,    82,     0,     0,     0,     0,
       0,    40,    41,     0,    47,    48,    42,    43,     0,    49,
      50,     0,     0,     0,     0,     0,     0,    51,    52,     0,
      40,    41,    44,    45,   202,    42,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,    48,
       0,    44,    45,    49,    50,     0,     0,     0,     0,     0,
       0,    51,    52,     0,     0,     0,     0,    47,    48,     0,
       0,     0,    49,    50,    22,     0,    23,     0,    24,     0,
      51,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     3,     4,     5,
       6,     7
};

static const yytype_int16 yycheck[] =
{
      31,    45,    70,     0,    27,    92,     0,   139,     1,   136,
      26,     8,     0,    19,    26,    31,    12,    14,    11,   146,
       8,   148,    47,    19,    31,    48,    49,    50,    51,    52,
      26,    25,    25,    39,    24,    42,    32,    26,    26,    70,
      37,    34,    31,    28,    32,    89,    25,    41,   180,    25,
      31,    23,    42,    43,    48,    49,    50,    51,    52,   186,
     147,    42,    41,     8,     9,    41,    25,   111,    16,    30,
      60,    22,    48,    49,    50,    51,    52,    25,    16,   110,
      25,    29,    41,    42,    29,    78,    25,    25,    31,    27,
      29,    29,    28,    26,   138,    31,   140,    25,    31,    42,
      25,   132,    90,    26,    25,   173,    42,   194,    31,   196,
      48,    49,    50,    51,    52,   202,   106,   107,    42,   150,
     207,    40,   209,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,    16,    17,    18,    19,    20,    21,
     137,    26,   173,     3,     4,    41,    31,    42,     8,     9,
      25,   195,    48,    49,    50,    51,    52,    26,    26,   190,
      14,    15,    31,    31,    24,    25,    28,    27,    28,    25,
      26,    31,    32,    29,    34,    35,    36,    37,    38,    39,
      40,    41,     5,     6,     7,    45,    46,    26,    48,    49,
      50,    51,    52,    53,    54,     3,     4,     3,     4,    41,
       8,     9,    48,    49,    50,    51,    52,    10,    11,    12,
      13,   115,   116,   117,   118,    47,    24,    25,    40,    27,
      40,    41,    33,    31,    32,    42,    34,    35,    36,    37,
      38,    39,    40,    41,    30,    31,    26,    45,    46,     8,
      48,    49,    50,    51,    52,    53,    54,     3,     4,   113,
     114,    42,     8,     9,   119,   120,    23,    90,    24,    34,
     137,   106,    -1,   107,    -1,    -1,    -1,    -1,    24,    25,
      -1,    27,    28,    -1,    -1,    31,    32,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,     3,     4,    -1,    45,
      46,     8,     9,    -1,    -1,    -1,    -1,    53,    54,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    -1,
      27,    28,    -1,    -1,    31,    32,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,     3,     4,    -1,    45,    46,
       8,     9,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    24,    25,    -1,    27,
      -1,    -1,    -1,    31,    32,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,     3,     4,    -1,    45,    46,     8,
       9,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    25,     3,     4,    -1,
      -1,    30,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    -1,    -1,    -1,    45,    46,    24,    25,
      -1,    27,     3,     4,    53,    54,    -1,     8,     9,    -1,
      -1,    -1,     3,     4,    40,    41,    -1,     8,     9,    45,
      46,    -1,    -1,    24,    25,    -1,    -1,    53,    54,    -1,
      -1,    -1,    -1,    24,    25,    26,    -1,     3,     4,    40,
      41,    42,     8,     9,    45,    46,    -1,    -1,    -1,    40,
      41,    -1,    53,    54,    45,    46,    -1,    -1,    24,    25,
      -1,    -1,    53,    54,    -1,    31,    -1,    -1,    -1,    -1,
      -1,     3,     4,    -1,    40,    41,     8,     9,    -1,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,
       3,     4,    24,    25,    26,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
      -1,    24,    25,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    -1,    -1,    -1,    -1,    40,    41,    -1,
      -1,    -1,    45,    46,    25,    -1,    27,    -1,    29,    -1,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    52
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    41,    48,    49,    50,    51,    52,    56,    57,
      58,    59,    62,    65,    98,    62,     0,    57,    42,    62,
      68,    72,    25,    27,    29,    59,    60,    61,    65,    59,
      26,    16,    60,    61,    31,    42,    26,    63,    28,    63,
       3,     4,     8,     9,    24,    25,    30,    40,    41,    45,
      46,    53,    54,    70,    78,    82,    85,    86,    88,    89,
      90,    91,    92,    94,    95,    96,    97,    62,    61,    65,
      27,    70,    81,    83,    86,    61,    72,    41,    59,    67,
      71,    80,    31,    32,    34,    35,    36,    37,    38,    39,
      60,    61,    66,    69,    73,    74,    75,    76,    77,    79,
      83,    86,    86,    79,    47,    30,    23,    22,     8,     9,
      25,    29,    86,    14,    15,    10,    11,    12,    13,     3,
       4,     5,     6,     7,    81,    84,    16,    17,    18,    19,
      20,    21,    87,    62,    26,    31,    26,    31,    25,    25,
      25,    42,    42,    25,    42,    79,    28,    66,    28,    69,
      31,    42,    26,    40,    82,    85,    26,    83,    93,    79,
      95,    95,    96,    96,    96,    96,    97,    97,    86,    86,
      86,    28,    31,    42,    83,    64,    41,    64,    80,    79,
      73,    79,    40,    41,    42,    64,    28,    64,    83,    26,
      31,    30,    28,    81,    26,    73,    26,    47,    26,    64,
      83,    69,    26,    79,    69,    40,    42,    33,    69,    26,
      26,    69,    69,    42
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    57,    57,    58,    58,    58,    58,
      59,    59,    60,    60,    61,    61,    61,    61,    62,    62,
      62,    62,    62,    62,    62,    63,    64,    65,    65,    66,
      66,    67,    67,    68,    68,    69,    69,    69,    69,    69,
      69,    70,    71,    71,    72,    72,    73,    73,    74,    74,
      75,    75,    75,    76,    76,    76,    76,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    81,    82,    82,
      83,    83,    84,    84,    85,    86,    86,    86,    86,    87,
      87,    87,    87,    87,    87,    88,    89,    89,    89,    89,
      89,    89,    90,    90,    90,    91,    92,    92,    92,    92,
      92,    92,    92,    93,    93,    94,    94,    94,    95,    95,
      95,    95,    95,    96,    96,    96,    97,    97,    97,    97,
      98,    98,    98,    98,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     4,     3,     3,     2,
       1,     2,     1,     2,     2,     5,     5,     6,     1,     3,
       4,     3,     6,     6,     3,     0,     0,     2,     3,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     3,     1,     2,     5,     7,
       5,     6,     7,     2,     2,     2,     3,     5,     7,     1,
       3,     1,     3,     2,     1,     1,     3,     4,     1,     3,
       1,     3,     1,     3,     1,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     3,     4,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 7:
#line 85 "compiler_hw2.y" /* yacc.c:1646  */
    { char *temp; 
                                                            temp = strtok((yyvsp[-1].string), ":");
                                                            (yyvsp[-1].string) = temp;
                                                            temp = strtok(NULL, ":");
                                                            insert_symbol((yyvsp[-1].string), "function", (yyvsp[-2].string), scope_num, temp); 
                                                            dump_symbol(scope_num+1);
                                                            }
#line 1593 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 97 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1599 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 98 "compiler_hw2.y" /* yacc.c:1646  */
    { ; }
#line 1605 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 114 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = strdup(yytext); }
#line 1611 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 115 "compiler_hw2.y" /* yacc.c:1646  */
    { ; }
#line 1617 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 118 "compiler_hw2.y" /* yacc.c:1646  */
    { strcat((yyval.string), ":"); strcat((yyval.string), (yyvsp[-2].string)); }
#line 1623 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 124 "compiler_hw2.y" /* yacc.c:1646  */
    { scope_num++; }
#line 1629 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 128 "compiler_hw2.y" /* yacc.c:1646  */
    { scope_num--; }
#line 1635 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 133 "compiler_hw2.y" /* yacc.c:1646  */
    { insert_symbol((yyvsp[-1].string), "variable", (yyvsp[-2].string), scope_num, "NULL");}
#line 1641 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 147 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1647 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 148 "compiler_hw2.y" /* yacc.c:1646  */
    { ; }
#line 1653 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 165 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1659 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 166 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = strcat((yyvsp[-2].string), ", "); (yyval.string) = strcat((yyval.string), (yyvsp[0].string)); }
#line 1665 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 170 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[0].string); }
#line 1671 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 171 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = (yyvsp[-2].string); }
#line 1677 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 213 "compiler_hw2.y" /* yacc.c:1646  */
    { insert_symbol((yyvsp[0].string), "parameter", (yyvsp[-1].string), scope_num, "NULL"); (yyval.string) = (yyvsp[-1].string); }
#line 1683 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 325 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = strdup(yytext); }
#line 1689 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 326 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = strdup(yytext); }
#line 1695 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 327 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = strdup(yytext); }
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 123:
#line 328 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = strdup(yytext); }
#line 1707 "y.tab.c" /* yacc.c:1646  */
    break;

  case 124:
#line 329 "compiler_hw2.y" /* yacc.c:1646  */
    { (yyval.string) = strdup(yytext); }
#line 1713 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1717 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 332 "compiler_hw2.y" /* yacc.c:1906  */


/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;
    create_symbol();
    yyparse();
    if(!err_flag) printf("\nTotal lines: %d \n",yylineno);

    return 0;
}

void yyerror(char *s)
{
    err_flag = 1;
    printf("%d: %s\n", yylineno+1, buf);
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", ++yylineno, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void create_symbol() {
    int i;
    for(i = 0; i < 200; i++){
        table[i].next = NULL;
        table[i].scope = 0;
        table[i].printed = -1;
    }
    printf("table create completed\n");
}

void insert_symbol(char *name, char *kind, char *type, int scope, char *attribute) {
    struct symbols *temp, *new_symbol;

    temp = &table[scope];
    while(temp->next != NULL){
        temp = temp->next;
    }

    new_symbol = (struct symbols *)malloc(sizeof(struct symbols));
    strcpy(new_symbol->name, name);
    strcpy(new_symbol->kind, kind);
    strcpy(new_symbol->type, type);
    if(attribute == NULL || !strcmp(attribute, "NULL")) strcpy(new_symbol->attribute, "\0");
    else strcpy(new_symbol->attribute, attribute);
    new_symbol->scope = scope;
    new_symbol->printed = -1;
    new_symbol->next = NULL;
    temp->next = new_symbol;
}

int lookup_symbol() {
    
}
void dump_symbol(int scope) {
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    struct symbols *temp = &table[scope];
    int count = table[scope].printed;

    temp = temp->next;
    int i = 0;
    while(temp != NULL){
        if(i >= count){
            printf("%-10d%-10s%-12s%-10s%-10d", i, temp->name, temp->kind, temp->type, temp->scope);
            if(strcmp(temp->attribute, "\0"))    printf("%-10s\n", temp->attribute);
            else printf("\n");
        }
        
        temp = temp->next;
        i++;
    }
    printf("\n");
    
    table[scope].printed = i;
    printf("print from %d\n", table[scope].printed);
}

void add_attribute(int scope){
    struct symbols *temp = &table[scope-1];
    int i = 0;
    while(temp->next != NULL){
        temp = temp->next;
    }
    printf("%s\n", temp->name);
}
