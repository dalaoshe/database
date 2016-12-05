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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         HSQL_STYPE
#define YYLTYPE         HSQL_LTYPE
/* Substitute the variable and function names.  */
#define yyparse         hsql_parse
#define yylex           hsql_lex
#define yyerror         hsql_error
#define yydebug         hsql_debug
#define yynerrs         hsql_nerrs


/* Copy the first part of user declarations.  */
#line 1 "bison_parser.y" /* yacc.c:339  */

/**
 * bison_parser.y
 * defines bison_parser.h
 * outputs bison_parser.c
 * 
 * Grammar File Spec: http://dinosaur.compilertools.net/bison/bison_6.html
 *
 */
/*********************************
 ** Section 1: C Declarations
 *********************************/

#include "bison_parser.h"
#include "flex_lexer.h"

#include <stdio.h>

using namespace hsql;

int yyerror(YYLTYPE* llocp, SQLParserResult** result, yyscan_t scanner, const char *msg) {

	SQLParserResult* list = new SQLParserResult();
	list->isValid = false;
	list->errorMsg = strdup(msg);
	list->errorLine = llocp->first_line;
	list->errorColumn = llocp->first_column;

	*result = list;
	return 0;
}




#line 110 "bison_parser.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison_parser.h".  */
#ifndef YY_HSQL_BISON_PARSER_H_INCLUDED
# define YY_HSQL_BISON_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef HSQL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define HSQL_DEBUG 1
#  else
#   define HSQL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define HSQL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined HSQL_DEBUG */
#if HSQL_DEBUG
extern int hsql_debug;
#endif
/* "%code requires" blocks.  */
#line 42 "bison_parser.y" /* yacc.c:355  */

// %code requires block	
#include "stdio.h"
#include "../sql/statements.h"
#include "../SQLParserResult.h"
#include "../sqlhelper.h"
#include "parser_typedef.h"
#include "../../utils/base.h"
// Auto update column and line number
#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
    	yylloc->total_column++; \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

#line 172 "bison_parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef HSQL_TOKENTYPE
# define HSQL_TOKENTYPE
  enum hsql_tokentype
  {
    SQL_IDENTIFIER = 258,
    SQL_STRING = 259,
    SQL_FLOATVAL = 260,
    SQL_INTVAL = 261,
    SQL_NOTEQUALS = 262,
    SQL_LESSEQ = 263,
    SQL_GREATEREQ = 264,
    SQL_DEALLOCATE = 265,
    SQL_PARAMETERS = 266,
    SQL_INTERSECT = 267,
    SQL_TEMPORARY = 268,
    SQL_TIMESTAMP = 269,
    SQL_DISTINCT = 270,
    SQL_NVARCHAR = 271,
    SQL_RESTRICT = 272,
    SQL_TRUNCATE = 273,
    SQL_ANALYZE = 274,
    SQL_BETWEEN = 275,
    SQL_CASCADE = 276,
    SQL_COLUMNS = 277,
    SQL_CONTROL = 278,
    SQL_DEFAULT = 279,
    SQL_EXECUTE = 280,
    SQL_EXPLAIN = 281,
    SQL_HISTORY = 282,
    SQL_INTEGER = 283,
    SQL_NATURAL = 284,
    SQL_PREPARE = 285,
    SQL_PRIMARY = 286,
    SQL_SCHEMAS = 287,
    SQL_SPATIAL = 288,
    SQL_VIRTUAL = 289,
    SQL_BEFORE = 290,
    SQL_COLUMN = 291,
    SQL_CREATE = 292,
    SQL_DELETE = 293,
    SQL_DIRECT = 294,
    SQL_DOUBLE = 295,
    SQL_ESCAPE = 296,
    SQL_EXCEPT = 297,
    SQL_EXISTS = 298,
    SQL_GLOBAL = 299,
    SQL_HAVING = 300,
    SQL_IMPORT = 301,
    SQL_INSERT = 302,
    SQL_ISNULL = 303,
    SQL_OFFSET = 304,
    SQL_RENAME = 305,
    SQL_SCHEMA = 306,
    SQL_SELECT = 307,
    SQL_SORTED = 308,
    SQL_TABLES = 309,
    SQL_UNIQUE = 310,
    SQL_UNLOAD = 311,
    SQL_UPDATE = 312,
    SQL_VALUES = 313,
    SQL_AFTER = 314,
    SQL_ALTER = 315,
    SQL_CROSS = 316,
    SQL_DELTA = 317,
    SQL_GROUP = 318,
    SQL_INDEX = 319,
    SQL_INNER = 320,
    SQL_LIMIT = 321,
    SQL_LOCAL = 322,
    SQL_MERGE = 323,
    SQL_MINUS = 324,
    SQL_ORDER = 325,
    SQL_OUTER = 326,
    SQL_RIGHT = 327,
    SQL_TABLE = 328,
    SQL_UNION = 329,
    SQL_USING = 330,
    SQL_WHERE = 331,
    SQL_CALL = 332,
    SQL_DATE = 333,
    SQL_DESC = 334,
    SQL_DROP = 335,
    SQL_FILE = 336,
    SQL_FROM = 337,
    SQL_FULL = 338,
    SQL_HASH = 339,
    SQL_HINT = 340,
    SQL_INTO = 341,
    SQL_JOIN = 342,
    SQL_LEFT = 343,
    SQL_LIKE = 344,
    SQL_LOAD = 345,
    SQL_NULL = 346,
    SQL_PART = 347,
    SQL_PLAN = 348,
    SQL_SHOW = 349,
    SQL_TEXT = 350,
    SQL_TIME = 351,
    SQL_VIEW = 352,
    SQL_WITH = 353,
    SQL_ADD = 354,
    SQL_ALL = 355,
    SQL_AND = 356,
    SQL_ASC = 357,
    SQL_CSV = 358,
    SQL_FOR = 359,
    SQL_INT = 360,
    SQL_KEY = 361,
    SQL_NOT = 362,
    SQL_OFF = 363,
    SQL_SET = 364,
    SQL_TBL = 365,
    SQL_TOP = 366,
    SQL_AS = 367,
    SQL_BY = 368,
    SQL_IF = 369,
    SQL_IN = 370,
    SQL_IS = 371,
    SQL_OF = 372,
    SQL_ON = 373,
    SQL_OR = 374,
    SQL_TO = 375,
    SQL_DATABASE = 376,
    SQL_USE = 377,
    SQL_CHECK = 378,
    SQL_SUM = 379,
    SQL_AVG = 380,
    SQL_MIN = 381,
    SQL_MAX = 382,
    SQL_DATABASES = 383,
    SQL_EQUALS = 384,
    SQL_LESS = 385,
    SQL_GREATER = 386,
    SQL_NOTNULL = 387,
    SQL_UMINUS = 388
  };
#endif

/* Value type.  */
#if ! defined HSQL_STYPE && ! defined HSQL_STYPE_IS_DECLARED

union HSQL_STYPE
{
#line 102 "bison_parser.y" /* yacc.c:355  */

	double fval;
	int64_t ival;
	char* sval;
	uint uval;
	bool bval;

	hsql::SQLStatement* statement;
	hsql::SelectStatement* 	select_stmt;
	hsql::ImportStatement* 	import_stmt;
	hsql::CreateStatement* 	create_stmt;
	hsql::InsertStatement* 	insert_stmt;
	hsql::DeleteStatement* 	delete_stmt;
	hsql::UpdateStatement* 	update_stmt;
	hsql::DropStatement*   	drop_stmt;
	hsql::PrepareStatement* prep_stmt;
	hsql::ExecuteStatement* exec_stmt;

	hsql::TableRef* table;
	hsql::Expr* expr;
	hsql::OrderDescription* order;
	hsql::OrderType order_type;
	hsql::LimitDescription* limit;
	hsql::ColumnDefinition* column_t;
	hsql::GroupByDescription* group_t;
	hsql::UpdateClause* update_t;

	hsql::SQLParserResult* stmt_list;

    hsql::CreateIndexStatement* createIndex_stmt;
    hsql::CreateDBStatement* createDB_stmt;
    hsql::DescStatement* desc_stmt;
    hsql::DropDBStatement* dropDB_stmt;
    hsql::DropIndexStatement* dropIndex_stmt;
    hsql::ShowDBStatement* showDB_stmt;
    hsql::ShowTableStatement* showTable_stmt;
    hsql::UseDBStatement* useDB_stmt;

	std::vector<char*>* str_vec;
	std::vector<hsql::TableRef*>* table_vec;
	std::vector<hsql::ColumnDefinition*>* column_vec;
	std::vector<hsql::UpdateClause*>* update_vec;
	std::vector<hsql::Expr*>* expr_vec;

#line 363 "bison_parser.cpp" /* yacc.c:355  */
};

typedef union HSQL_STYPE HSQL_STYPE;
# define HSQL_STYPE_IS_TRIVIAL 1
# define HSQL_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined HSQL_LTYPE && ! defined HSQL_LTYPE_IS_DECLARED
typedef struct HSQL_LTYPE HSQL_LTYPE;
struct HSQL_LTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define HSQL_LTYPE_IS_DECLARED 1
# define HSQL_LTYPE_IS_TRIVIAL 1
#endif



int hsql_parse (hsql::SQLParserResult** result, yyscan_t scanner);

#endif /* !YY_HSQL_BISON_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 393 "bison_parser.cpp" /* yacc.c:358  */

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
         || (defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL \
             && defined HSQL_STYPE_IS_TRIVIAL && HSQL_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  66
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   548

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  154
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  80
/* YYNRULES -- Number of rules.  */
#define YYNRULES  175
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  321

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   388

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   140,     2,     2,
     145,   146,   138,   136,   152,   137,   147,   139,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   149,   148,
     131,   129,   132,   153,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   143,     2,   144,   141,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   150,     2,   151,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   130,   133,   134,   135,   142
};

#if HSQL_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   252,   252,   259,   260,   264,   269,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,   290,   298,   303,   311,   315,   327,   335,
     339,   349,   355,   365,   366,   367,   371,   372,   376,   377,
     381,   384,   390,   391,   394,   395,   398,   399,   400,   403,
     404,   405,   406,   416,   420,   432,   440,   452,   458,   468,
     469,   479,   488,   489,   493,   505,   506,   510,   511,   515,
     520,   532,   533,   534,   538,   549,   550,   554,   559,   564,
     565,   569,   574,   578,   579,   582,   583,   587,   588,   589,
     594,   595,   596,   603,   604,   608,   609,   613,   620,   621,
     622,   623,   624,   628,   629,   630,   634,   635,   639,   640,
     641,   642,   643,   644,   645,   646,   647,   648,   649,   654,
     655,   656,   657,   658,   659,   660,   664,   668,   669,   673,
     674,   675,   676,   680,   685,   686,   690,   694,   699,   710,
     711,   721,   722,   728,   733,   734,   739,   749,   757,   758,
     763,   764,   768,   769,   777,   789,   790,   791,   792,   793,
     799,   805,   809,   818,   819,   824,   825,   835,   841,   849,
     860,   871,   880,   890,   902,   916
};
#endif

#if HSQL_DEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "FLOATVAL",
  "INTVAL", "NOTEQUALS", "LESSEQ", "GREATEREQ", "DEALLOCATE", "PARAMETERS",
  "INTERSECT", "TEMPORARY", "TIMESTAMP", "DISTINCT", "NVARCHAR",
  "RESTRICT", "TRUNCATE", "ANALYZE", "BETWEEN", "CASCADE", "COLUMNS",
  "CONTROL", "DEFAULT", "EXECUTE", "EXPLAIN", "HISTORY", "INTEGER",
  "NATURAL", "PREPARE", "PRIMARY", "SCHEMAS", "SPATIAL", "VIRTUAL",
  "BEFORE", "COLUMN", "CREATE", "DELETE", "DIRECT", "DOUBLE", "ESCAPE",
  "EXCEPT", "EXISTS", "GLOBAL", "HAVING", "IMPORT", "INSERT", "ISNULL",
  "OFFSET", "RENAME", "SCHEMA", "SELECT", "SORTED", "TABLES", "UNIQUE",
  "UNLOAD", "UPDATE", "VALUES", "AFTER", "ALTER", "CROSS", "DELTA",
  "GROUP", "INDEX", "INNER", "LIMIT", "LOCAL", "MERGE", "MINUS", "ORDER",
  "OUTER", "RIGHT", "TABLE", "UNION", "USING", "WHERE", "CALL", "DATE",
  "DESC", "DROP", "FILE", "FROM", "FULL", "HASH", "HINT", "INTO", "JOIN",
  "LEFT", "LIKE", "LOAD", "NULL", "PART", "PLAN", "SHOW", "TEXT", "TIME",
  "VIEW", "WITH", "ADD", "ALL", "AND", "ASC", "CSV", "FOR", "INT", "KEY",
  "NOT", "OFF", "SET", "TBL", "TOP", "AS", "BY", "IF", "IN", "IS", "OF",
  "ON", "OR", "TO", "DATABASE", "USE", "CHECK", "SUM", "AVG", "MIN", "MAX",
  "DATABASES", "'='", "EQUALS", "'<'", "'>'", "LESS", "GREATER", "NOTNULL",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "UMINUS", "'['", "']'", "'('",
  "')'", "'.'", "';'", "':'", "'{'", "'}'", "','", "'?'", "$accept",
  "input", "statement_list", "statement", "preparable_statement",
  "prepare_statement", "execute_statement", "import_statement",
  "import_file_type", "file_path", "create_statement", "opt_primary_key",
  "opt_not_exists", "column_def_commalist", "column_def", "opt_size",
  "opt_not_null", "opt_check", "column_type", "drop_statement",
  "delete_statement", "truncate_statement", "insert_statement",
  "opt_column_list", "update_statement", "update_clause_commalist",
  "update_clause", "select_statement", "select_with_paren",
  "select_no_paren", "set_operator", "select_clause", "opt_distinct",
  "select_list", "from_clause", "opt_where", "opt_group", "opt_having",
  "opt_order", "opt_order_type", "opt_limit", "expr_list", "literal_list",
  "expr_alias", "expr", "scalar_expr", "unary_expr", "binary_expr",
  "comp_expr", "function_expr", "column_name", "literal", "string_literal",
  "num_literal", "int_literal", "star_expr", "placeholder_expr",
  "table_ref", "table_ref_atomic", "table_ref_commalist", "table_ref_name",
  "table_ref_name_no_alias", "table_name", "alias", "opt_alias",
  "join_clause", "opt_join_type", "join_table", "join_condition",
  "opt_semicolon", "ident_commalist", "createDB_statement", "DBname",
  "dropDB_statement", "useDB_statement", "showDB_statement",
  "showTable_statement", "createIndex_statement", "dropIndex_statement",
  "desc_statement", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,    61,
     384,    60,    62,   385,   386,   387,    43,    45,    42,    47,
      37,    94,   388,    91,    93,    40,    41,    46,    59,    58,
     123,   125,    44,    63
};
# endif

#define YYPACT_NINF -236

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-236)))

#define YYTABLE_NINF -162

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-162)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     266,    52,    34,    83,    94,   -25,    25,    30,    27,    99,
      34,    34,   -10,   -27,   115,   -28,   123,   -24,  -236,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,    20,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,   131,   -11,  -236,    -8,   -40,    34,    21,   115,    34,
      36,    34,  -236,     9,    32,  -236,  -236,    34,    34,   115,
    -236,  -236,  -236,  -236,     2,     3,  -236,   266,  -236,  -236,
    -236,    37,  -236,   103,    92,  -236,   156,    12,   304,   266,
      18,    59,    34,  -236,    91,  -236,    87,    26,   -39,  -236,
    -236,  -236,  -236,     9,     9,  -236,     9,  -236,    88,    24,
    -236,   170,  -236,  -236,  -236,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,   169,    35,  -236,  -236,  -236,  -236,
    -236,     9,   111,   176,  -236,  -236,  -111,  -236,  -236,   -24,
     181,   142,   -53,     9,  -236,   182,   185,   -16,    99,   186,
     388,   -88,    68,     7,    91,     9,  -236,     9,     9,     9,
       9,     9,   101,   188,    47,     9,     9,     9,     9,     9,
       9,     9,     9,     9,     9,  -236,  -236,    64,   -50,  -236,
     192,   323,    92,   147,  -236,    12,    51,    57,  -236,   100,
       4,   350,   126,  -236,  -236,   -63,    53,  -236,     9,  -236,
    -236,   -28,  -236,    69,    73,    17,  -236,   157,   160,  -236,
     407,   124,   124,   407,   388,     9,  -236,    12,   369,   407,
     124,   124,   -88,   -88,    79,    79,    79,  -236,    12,   169,
    -236,    78,  -236,  -236,  -236,  -236,   176,  -236,  -236,  -236,
     144,     0,    81,   107,   -12,  -236,  -236,    34,  -236,   229,
      12,   112,    90,     7,  -236,  -236,  -236,  -236,  -236,   150,
     125,  -236,   407,   -61,  -236,  -236,  -236,  -236,   182,  -236,
    -236,  -236,  -236,    95,     9,    97,   140,    -1,   108,  -236,
    -236,   -59,  -236,    17,  -236,   105,     8,     9,  -236,  -236,
     241,   159,   350,   121,     9,   127,   162,  -236,  -236,  -236,
     146,     7,   -28,  -236,   151,   -22,   128,   179,  -236,  -236,
     129,   270,   133,  -236,   134,     9,     9,  -236,  -236,  -236,
    -236,   135,   276,    17,   350,  -236,   350,  -236,   137,  -236,
    -236
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    76,
       0,     0,     0,     0,     0,     0,     0,   164,     3,     6,
       5,    15,     8,     9,    14,    11,    12,    10,    13,     7,
      65,    66,    86,    16,    17,    18,    19,    20,    21,    22,
      23,     0,   148,    56,    26,     0,     0,    37,     0,     0,
       0,     0,    75,     0,     0,   147,   175,     0,     0,     0,
     172,   171,   168,   170,     0,     0,     1,   163,     2,    72,
      73,     0,    71,     0,    92,    54,     0,     0,     0,     0,
       0,     0,     0,   167,    80,    29,     0,    60,   127,   133,
     134,   136,   131,     0,     0,   137,     0,   138,     0,    77,
      93,   153,    99,   100,   101,   108,   102,   103,   105,   129,
     130,   135,   104,   132,     0,     0,    53,   169,    68,    67,
       4,     0,    86,     0,    69,   149,     0,    95,    24,   164,
       0,     0,     0,     0,    55,     0,     0,     0,    76,     0,
     107,   106,     0,     0,    80,     0,   151,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   152,    97,     0,    80,    62,
       0,    89,    92,    90,    27,     0,     0,     0,    36,     0,
      48,    79,     0,    30,   165,     0,     0,    58,     0,   128,
      98,     0,    78,   139,   141,   153,   143,   159,    82,    94,
     120,   123,   124,   117,   115,     0,   150,     0,   116,   119,
     121,   122,   110,   109,   112,   111,   113,   114,     0,     0,
      61,     0,    88,    87,    85,    70,     0,    96,    25,   173,
       0,     0,     0,     0,    35,    38,    41,     0,    59,     0,
       0,     0,     0,     0,   146,   155,   156,   158,   157,     0,
       0,    74,   118,     0,    64,    63,   174,    91,     0,    50,
      51,    52,    49,    43,     0,     0,     0,    48,     0,    28,
     166,     0,   126,     0,   144,   140,     0,     0,   125,    31,
       0,    45,     0,   108,     0,     0,     0,    39,    32,    57,
     142,     0,     0,   161,     0,    84,     0,     0,    40,    47,
     108,     0,     0,   145,     0,     0,     0,    81,    42,    44,
      46,     0,     0,     0,   162,   154,    83,    34,     0,   160,
      33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -236,  -236,   207,   220,   210,  -236,  -236,  -236,  -236,    39,
    -236,  -236,  -236,  -236,    23,  -236,  -236,  -236,  -236,  -236,
    -236,  -236,  -236,  -236,  -236,  -236,    74,  -166,   277,     6,
    -236,   221,   167,  -236,  -236,   -80,  -236,  -236,   173,  -236,
     143,    40,  -161,   153,   -90,  -236,  -236,  -236,  -180,  -236,
    -236,   -76,  -130,  -236,  -101,  -236,  -236,  -236,  -210,  -236,
      43,  -236,    -2,  -235,   130,  -236,  -236,    44,  -236,   171,
    -236,  -236,   -14,  -236,  -236,  -236,  -236,  -236,  -236,  -236
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    20,    21,    22,    86,   182,
      23,   268,    82,   234,   235,   281,   298,   236,   263,    24,
      25,    26,    27,   137,    28,   168,   169,    29,    30,    31,
      73,    32,    53,    98,   144,   134,   251,   307,    74,   224,
     124,    99,   126,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   192,   193,   275,
     194,    54,   195,   165,   166,   196,   249,   197,   315,    68,
     185,    33,    63,    34,    35,    36,    37,    38,    39,    40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   127,   231,   140,   141,   183,   142,   231,    55,    56,
      42,    42,    88,    89,    90,    91,    89,    90,    91,   266,
     146,    65,   173,   306,     9,   242,   133,    60,   259,   179,
     286,   171,    69,   274,    83,   174,     9,    42,   290,    46,
     260,   175,   186,   181,    80,   117,   253,    84,    47,    87,
     161,   162,   163,   164,    57,   115,   116,   200,   201,   202,
     203,   204,    70,    58,   198,   208,   209,   210,   211,   212,
     213,   214,   215,   216,   217,   147,   148,   149,   319,   271,
     132,   303,    41,   238,   283,   278,    44,   289,   220,   239,
      71,   175,   180,   175,    72,   261,    48,    45,   241,   227,
      92,    61,   219,    92,   300,   262,   138,    49,   139,    78,
      79,    59,    50,    51,    52,   252,    93,    15,    62,   147,
     148,   149,   232,    66,    67,   257,   304,   232,   183,   153,
     145,   127,  -162,  -162,    75,    81,    76,    77,  -161,    85,
     267,   114,   254,   187,  -161,  -161,    94,    95,   118,   119,
     121,   233,   191,   292,    96,     9,   233,   150,   123,   125,
    -161,  -161,    97,   130,   127,    97,   131,   133,   135,   151,
     143,   136,   167,   146,   282,   152,   145,   147,   148,   149,
     170,    71,    91,   154,   177,   178,    89,   155,   184,   189,
     205,   206,   207,   218,   282,   221,   226,   156,   240,   157,
     158,   150,   228,   229,   159,   160,   161,   162,   163,   164,
     230,  -160,   237,   151,   190,   314,   316,  -160,  -160,   152,
     164,   243,   245,   250,   256,   258,   264,   154,   246,   247,
     265,   155,   270,  -160,  -160,   269,   273,   276,   277,   154,
     280,   156,   284,   157,   158,   248,   285,   296,   159,   160,
     161,   162,   163,   164,   288,  -162,  -162,   291,   272,   150,
     159,   160,   161,   162,   163,   164,   297,   299,   302,   305,
     309,   151,   301,   311,   308,   310,     1,   152,   312,   318,
     313,   317,   153,   320,     2,   154,   129,   120,   128,   155,
     287,     3,    64,   255,   122,   172,     4,   279,   199,   156,
     176,   157,   158,     5,     6,   188,   159,   160,   161,   162,
     163,   164,     7,     8,     1,   225,     0,   295,     9,   293,
     294,     0,     2,    10,     0,   244,     0,     0,     0,     3,
     147,   148,   149,     0,     0,     0,     0,     0,     0,     0,
       0,     5,     6,     0,     0,    11,    12,     0,     0,     0,
       7,     8,     0,     0,     0,     0,     9,   147,   148,   149,
      13,    10,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   147,   148,   149,     0,
       0,     0,     0,    11,    12,     0,     0,     0,    14,     0,
       0,     0,     0,     0,     0,   147,   148,   149,    13,     0,
       0,     0,   222,     0,     0,     0,     0,     0,     0,     0,
       0,    15,   150,     0,   147,   148,   149,     0,     0,     0,
       0,     0,     0,     0,   151,   223,    14,     0,     0,     0,
     152,     0,     0,     0,     0,     0,     0,     0,   154,   150,
       0,     0,   155,     0,     0,     0,     0,     0,     0,    15,
       0,   151,   156,     0,   157,   158,     0,   152,   150,   159,
     160,   161,   162,   163,   164,   154,     0,     0,     0,   155,
     151,     0,     0,     0,     0,     0,   152,   150,     0,   156,
       0,   157,   158,     0,   154,     0,   159,   160,   161,   162,
     163,   164,     0,     0,     0,   152,   150,     0,   156,     0,
     157,   158,     0,   154,     0,   159,   160,   161,   162,   163,
     164,     0,     0,     0,     0,     0,     0,   156,     0,   157,
     158,     0,   154,     0,   159,   160,   161,   162,   163,   164,
       0,     0,     0,     0,     0,     0,   156,     0,   157,   158,
       0,     0,     0,   159,   160,   161,   162,   163,   164
};

static const yytype_int16 yycheck[] =
{
       2,    77,     3,    93,    94,   135,    96,     3,    10,    11,
       3,     3,     3,     4,     5,     6,     4,     5,     6,    31,
       3,    15,   123,    45,    52,   191,    76,    54,    28,    82,
      31,   121,    12,   243,    48,   146,    52,     3,   273,    64,
      40,   152,    58,   133,    46,    59,   207,    49,    73,    51,
     138,   139,   140,   141,    64,    57,    58,   147,   148,   149,
     150,   151,    42,    73,   144,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,     7,     8,     9,   313,   240,
      82,   291,    30,   146,   264,   146,     3,   146,   168,   152,
      70,   152,   145,   152,    74,    95,   121,     3,   188,   175,
      91,   128,   152,    91,   284,   105,   145,    82,   147,   149,
     150,   121,    82,    86,    15,   205,   107,   145,     3,     7,
       8,     9,   123,     0,   148,   226,   292,   123,   258,   112,
     152,   207,     8,     9,     3,   114,   147,   145,    65,   103,
     152,   109,   218,   137,    71,    72,   137,   138,   146,   146,
     113,   152,   145,   145,   145,    52,   152,    89,    66,     3,
      87,    88,   153,   145,   240,   153,   107,    76,    81,   101,
      82,   145,     3,     3,   264,   107,   152,     7,     8,     9,
     145,    70,     6,   115,     3,    43,     4,   119,     3,     3,
      89,     3,   145,   129,   284,     3,    49,   129,   145,   131,
     132,    89,   151,   146,   136,   137,   138,   139,   140,   141,
     110,    65,    86,   101,   146,   305,   306,    71,    72,   107,
     141,   152,    65,    63,   146,    81,   145,   115,    71,    72,
     123,   119,     3,    87,    88,   237,   146,    87,   113,   115,
     145,   129,   145,   131,   132,    88,   106,     6,   136,   137,
     138,   139,   140,   141,   146,   131,   132,   152,   146,    89,
     136,   137,   138,   139,   140,   141,   107,   146,   106,   118,
      91,   101,   145,     3,   146,   146,    10,   107,   145,     3,
     146,   146,   112,   146,    18,   115,    79,    67,    78,   119,
     267,    25,    15,   219,    73,   122,    30,   258,   145,   129,
     129,   131,   132,    37,    38,   138,   136,   137,   138,   139,
     140,   141,    46,    47,    10,   172,    -1,   277,    52,   276,
     276,    -1,    18,    57,    -1,   195,    -1,    -1,    -1,    25,
       7,     8,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    -1,    -1,    79,    80,    -1,    -1,    -1,
      46,    47,    -1,    -1,    -1,    -1,    52,     7,     8,     9,
      94,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     7,     8,     9,    -1,
      -1,    -1,    -1,    79,    80,    -1,    -1,    -1,   122,    -1,
      -1,    -1,    -1,    -1,    -1,     7,     8,     9,    94,    -1,
      -1,    -1,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   145,    89,    -1,     7,     8,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   101,   102,   122,    -1,    -1,    -1,
     107,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,    89,
      -1,    -1,   119,    -1,    -1,    -1,    -1,    -1,    -1,   145,
      -1,   101,   129,    -1,   131,   132,    -1,   107,    89,   136,
     137,   138,   139,   140,   141,   115,    -1,    -1,    -1,   119,
     101,    -1,    -1,    -1,    -1,    -1,   107,    89,    -1,   129,
      -1,   131,   132,    -1,   115,    -1,   136,   137,   138,   139,
     140,   141,    -1,    -1,    -1,   107,    89,    -1,   129,    -1,
     131,   132,    -1,   115,    -1,   136,   137,   138,   139,   140,
     141,    -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,   131,
     132,    -1,   115,    -1,   136,   137,   138,   139,   140,   141,
      -1,    -1,    -1,    -1,    -1,    -1,   129,    -1,   131,   132,
      -1,    -1,    -1,   136,   137,   138,   139,   140,   141
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    18,    25,    30,    37,    38,    46,    47,    52,
      57,    79,    80,    94,   122,   145,   155,   156,   157,   158,
     159,   160,   161,   164,   173,   174,   175,   176,   178,   181,
     182,   183,   185,   225,   227,   228,   229,   230,   231,   232,
     233,    30,     3,   216,     3,     3,    64,    73,   121,    82,
      82,    86,    15,   186,   215,   216,   216,    64,    73,   121,
      54,   128,     3,   226,   182,   183,     0,   148,   223,    12,
      42,    70,    74,   184,   192,     3,   147,   145,   149,   150,
     216,   114,   166,   226,   216,   103,   162,   216,     3,     4,
       5,     6,    91,   107,   137,   138,   145,   153,   187,   195,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   109,   216,   216,   226,   146,   146,
     157,   113,   185,    66,   194,     3,   196,   205,   158,   156,
     145,   107,   216,    76,   189,    81,   145,   177,   145,   147,
     198,   198,   198,    82,   188,   152,     3,     7,     8,     9,
      89,   101,   107,   112,   115,   119,   129,   131,   132,   136,
     137,   138,   139,   140,   141,   217,   218,     3,   179,   180,
     145,   198,   192,   208,   146,   152,   223,     3,    43,    82,
     145,   198,   163,   206,     3,   224,    58,   183,   186,     3,
     146,   145,   211,   212,   214,   216,   219,   221,   189,   197,
     198,   198,   198,   198,   198,    89,     3,   145,   198,   198,
     198,   198,   198,   198,   198,   198,   198,   198,   129,   152,
     189,     3,    79,   102,   193,   194,    49,   205,   151,   146,
     110,     3,   123,   152,   167,   168,   171,    86,   146,   152,
     145,   198,   181,   152,   218,    65,    71,    72,    88,   220,
      63,   190,   198,   196,   205,   180,   146,   208,    81,    28,
      40,    95,   105,   172,   145,   123,    31,   152,   165,   216,
       3,   196,   146,   146,   212,   213,    87,   113,   146,   163,
     145,   169,   198,   202,   145,   106,    31,   168,   146,   146,
     217,   152,   145,   214,   221,   195,     6,   107,   170,   146,
     202,   145,   106,   212,   181,   118,    45,   191,   146,    91,
     146,     3,   145,   146,   198,   222,   198,   146,     3,   217,
     146
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   154,   155,   156,   156,   157,   157,   158,   158,   158,
     158,   158,   158,   158,   158,   158,   158,   158,   158,   158,
     158,   158,   158,   158,   159,   159,   160,   160,   161,   162,
     163,   164,   164,   165,   165,   165,   166,   166,   167,   167,
     168,   168,   169,   169,   170,   170,   171,   171,   171,   172,
     172,   172,   172,   173,   173,   174,   175,   176,   176,   177,
     177,   178,   179,   179,   180,   181,   181,   182,   182,   183,
     183,   184,   184,   184,   185,   186,   186,   187,   188,   189,
     189,   190,   190,   191,   191,   192,   192,   193,   193,   193,
     194,   194,   194,   195,   195,   196,   196,   197,   198,   198,
     198,   198,   198,   199,   199,   199,   200,   200,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   201,   201,   202,
     202,   202,   202,   202,   202,   202,   203,   204,   204,   205,
     205,   205,   205,   206,   207,   207,   208,   209,   210,   211,
     211,   212,   212,   212,   213,   213,   214,   215,   216,   216,
     217,   217,   218,   218,   219,   220,   220,   220,   220,   220,
     221,   221,   222,   223,   223,   224,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     6,     2,     5,     7,     1,
       1,     8,     8,     6,     5,     0,     3,     0,     1,     3,
       4,     1,     3,     0,     2,     0,     5,     4,     0,     1,
       1,     1,     1,     3,     3,     4,     2,     8,     5,     3,
       0,     5,     1,     3,     3,     1,     1,     3,     3,     3,
       5,     1,     1,     1,     6,     1,     0,     1,     2,     2,
       0,     4,     0,     2,     0,     4,     0,     1,     1,     0,
       2,     4,     0,     1,     3,     1,     3,     2,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     4,     3,
       3,     3,     3,     3,     3,     5,     5,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     4,     1,     1,     3,     2,     1,     1,     3,
       2,     1,     1,     0,     6,     1,     1,     1,     1,     0,
       4,     1,     1,     1,     0,     1,     3,     3,     1,     3,
       2,     2,     2,     6,     6,     2
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
      yyerror (&yylloc, result, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if HSQL_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, hsql::SQLParserResult** result, yyscan_t scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, hsql::SQLParserResult** result, yyscan_t scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result, scanner);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, hsql::SQLParserResult** result, yyscan_t scanner)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !HSQL_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !HSQL_DEBUG */


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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, hsql::SQLParserResult** result, yyscan_t scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (hsql::SQLParserResult** result, yyscan_t scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 80 "bison_parser.y" /* yacc.c:1429  */
{
	// Initialize
	yylloc.first_column = 0;
	yylloc.last_column = 0;
	yylloc.first_line = 0;
	yylloc.last_line = 0;
	yylloc.total_column = 0;
	yylloc.placeholder_id = 0;
}

#line 1724 "bison_parser.cpp" /* yacc.c:1429  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 252 "bison_parser.y" /* yacc.c:1646  */
    {
			*result = (yyvsp[-1].stmt_list);
		}
#line 1915 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 259 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.stmt_list) = new SQLParserResult((yyvsp[0].statement)); }
#line 1921 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 260 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].stmt_list)->addStatement((yyvsp[0].statement)); (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 1927 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 264 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].prep_stmt)->setPlaceholders(yyloc.placeholder_list);
			yyloc.placeholder_list.clear();
			(yyval.statement) = (yyvsp[0].prep_stmt);
		}
#line 1937 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 274 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].select_stmt); }
#line 1943 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 275 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].import_stmt); }
#line 1949 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 276 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].create_stmt); }
#line 1955 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 277 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].insert_stmt); }
#line 1961 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 278 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1967 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 279 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1973 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 280 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].update_stmt); }
#line 1979 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 281 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].drop_stmt); }
#line 1985 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 282 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].exec_stmt); }
#line 1991 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 283 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].createDB_stmt); }
#line 1997 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 284 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].dropDB_stmt); }
#line 2003 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 285 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].useDB_stmt); }
#line 2009 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 286 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].showDB_stmt); }
#line 2015 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 287 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].showTable_stmt); }
#line 2021 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 288 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].createIndex_stmt); }
#line 2027 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 289 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].dropIndex_stmt); }
#line 2033 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 290 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].desc_stmt); }
#line 2039 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 298 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-2].sval);
			(yyval.prep_stmt)->query = new SQLParserResult((yyvsp[0].statement));
		}
#line 2049 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 303 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-4].sval);
			(yyval.prep_stmt)->query = (yyvsp[-2].stmt_list);
		}
#line 2059 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 311 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[0].sval);
		}
#line 2068 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 315 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[-3].sval);
			(yyval.exec_stmt)->parameters = (yyvsp[-1].expr_vec);
		}
#line 2078 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 327 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.import_stmt) = new ImportStatement((ImportStatement::ImportType) (yyvsp[-4].uval));
			(yyval.import_stmt)->filePath = (yyvsp[-2].sval);
			(yyval.import_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2088 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 335 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ImportStatement::kImportCSV; }
#line 2094 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 339 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].expr)->name; }
#line 2100 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 349 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.create_stmt) = new CreateStatement(CreateStatement::kTableFromTbl);
			(yyval.create_stmt)->ifNotExists = (yyvsp[-5].bval);
			(yyval.create_stmt)->tableName = (yyvsp[-4].sval);
			(yyval.create_stmt)->filePath = (yyvsp[0].sval);
		}
#line 2111 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 355 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
			(yyval.create_stmt)->ifNotExists = (yyvsp[-5].bval);
			(yyval.create_stmt)->tableName = (yyvsp[-4].sval);
			(yyval.create_stmt)->columns = (yyvsp[-2].column_vec);
			(yyval.create_stmt)->primary_key = (yyvsp[-1].sval);
		}
#line 2123 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 365 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-1].sval); }
#line 2129 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 366 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-1].sval); }
#line 2135 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 367 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 2141 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 371 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2147 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 372 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2153 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 376 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.column_vec) = new std::vector<ColumnDefinition*>(); (yyval.column_vec)->push_back((yyvsp[0].column_t)); }
#line 2159 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 377 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].column_vec)->push_back((yyvsp[0].column_t)); (yyval.column_vec) = (yyvsp[-2].column_vec); }
#line 2165 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 381 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.column_t) = new ColumnDefinition((yyvsp[-3].sval), (AttrType) (yyvsp[-2].uval), (yyvsp[-1].ival), (yyvsp[0].bval));
		}
#line 2173 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 384 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.column_t) = new ColumnDefinition((yyvsp[0].expr));
		}
#line 2181 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 390 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.ival) = (yyvsp[-1].ival); }
#line 2187 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 391 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.ival) = 20;}
#line 2193 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 394 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2199 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 395 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false;}
#line 2205 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 398 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2211 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 399 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2217 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 400 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2223 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 403 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = AttrType::INT; }
#line 2229 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 404 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = AttrType::INT; }
#line 2235 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 405 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = AttrType::FLOAT; }
#line 2241 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 406 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = AttrType::STRING; }
#line 2247 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 416 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kTable);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2256 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 420 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kPreparedStatement);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2265 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 432 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[-1].sval);
			(yyval.delete_stmt)->expr = (yyvsp[0].expr);
		}
#line 2275 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 440 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2284 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 452 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertValues);
			(yyval.insert_stmt)->tableName = (yyvsp[-5].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-4].str_vec);
			(yyval.insert_stmt)->values = (yyvsp[-1].expr_vec);
		}
#line 2295 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 458 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertSelect);
			(yyval.insert_stmt)->tableName = (yyvsp[-2].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-1].str_vec);
			(yyval.insert_stmt)->select = (yyvsp[0].select_stmt);
		}
#line 2306 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 468 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = (yyvsp[-1].str_vec); }
#line 2312 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 469 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = NULL; }
#line 2318 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 479 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.update_stmt) = new UpdateStatement();
		(yyval.update_stmt)->table = (yyvsp[-3].table);
		(yyval.update_stmt)->updates = (yyvsp[-1].update_vec);
		(yyval.update_stmt)->where = (yyvsp[0].expr);
	}
#line 2329 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 488 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.update_vec) = new std::vector<UpdateClause*>(); (yyval.update_vec)->push_back((yyvsp[0].update_t)); }
#line 2335 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 489 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].update_vec)->push_back((yyvsp[0].update_t)); (yyval.update_vec) = (yyvsp[-2].update_vec); }
#line 2341 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 493 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.update_t) = new UpdateClause();
			(yyval.update_t)->column = (yyvsp[-2].sval);
			(yyval.update_t)->value = (yyvsp[0].expr);
		}
#line 2351 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 510 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2357 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 511 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2363 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 515 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2373 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 520 "bison_parser.y" /* yacc.c:1646  */
    {
			// TODO: allow multiple unions (through linked list)
			// TODO: capture type of set_operator
			// TODO: might overwrite order and limit of first select here
			(yyval.select_stmt) = (yyvsp[-4].select_stmt);
			(yyval.select_stmt)->unionSelect = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2387 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 538 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement();
			(yyval.select_stmt)->selectDistinct = (yyvsp[-4].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-3].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2400 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 549 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2406 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 550 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2412 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 559 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[0].table); }
#line 2418 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 564 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2424 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 565 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2430 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 569 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.group_t) = new GroupByDescription();
			(yyval.group_t)->columns = (yyvsp[-1].expr_vec);
			(yyval.group_t)->having = (yyvsp[0].expr);
		}
#line 2440 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 574 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.group_t) = NULL; }
#line 2446 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 578 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2452 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 579 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2458 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 582 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = new OrderDescription((yyvsp[0].order_type), (yyvsp[-1].expr)); }
#line 2464 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 583 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = NULL; }
#line 2470 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 587 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2476 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 588 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderDesc; }
#line 2482 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 589 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2488 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 594 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[0].expr)->ival, kNoOffset); delete (yyvsp[0].expr); }
#line 2494 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 595 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[-2].expr)->ival, (yyvsp[0].expr)->ival); delete (yyvsp[-2].expr); delete (yyvsp[0].expr); }
#line 2500 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 596 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = NULL; }
#line 2506 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 603 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2512 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 604 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2518 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 608 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr));}
#line 2524 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 609 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2530 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 613 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = (yyvsp[-1].expr);
			(yyval.expr)->alias = (yyvsp[0].sval);
		}
#line 2539 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 620 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2545 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 634 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::UMINUS, (yyvsp[0].expr)); }
#line 2551 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 107:
#line 635 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::NOT, (yyvsp[0].expr)); }
#line 2557 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 640 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '-', (yyvsp[0].expr)); }
#line 2563 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 641 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '+', (yyvsp[0].expr)); }
#line 2569 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 642 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '/', (yyvsp[0].expr)); }
#line 2575 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 643 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '*', (yyvsp[0].expr)); }
#line 2581 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 644 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '%', (yyvsp[0].expr)); }
#line 2587 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 645 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '^', (yyvsp[0].expr)); }
#line 2593 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 646 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::AND, (yyvsp[0].expr)); }
#line 2599 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 647 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::OR, (yyvsp[0].expr)); }
#line 2605 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 648 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LIKE, (yyvsp[0].expr)); }
#line 2611 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 649 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), Expr::NOT_LIKE, (yyvsp[0].expr)); }
#line 2617 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 654 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '=', (yyvsp[0].expr)); }
#line 2623 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 655 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::NOT_EQUALS, (yyvsp[0].expr)); }
#line 2629 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 656 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '<', (yyvsp[0].expr)); }
#line 2635 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 657 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '>', (yyvsp[0].expr)); }
#line 2641 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 658 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LESS_EQ, (yyvsp[0].expr)); }
#line 2647 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 659 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::GREATER_EQ, (yyvsp[0].expr)); }
#line 2653 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 660 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-4].expr), Expr::IN,(yyvsp[-1].expr_vec));}
#line 2659 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 664 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeFunctionRef((yyvsp[-4].sval), (yyvsp[-1].expr), (yyvsp[-2].bval)); }
#line 2665 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 668 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[0].sval)); }
#line 2671 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 669 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 2677 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 675 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = Expr::makeLiteral();}
#line 2683 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 680 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].sval)); }
#line 2689 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 685 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].fval)); }
#line 2695 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 690 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].ival)); }
#line 2701 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 694 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr(kExprStar); }
#line 2707 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 699 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = Expr::makePlaceholder(yylloc.total_column);
			yyloc.placeholder_list.push_back((yyval.expr));
		}
#line 2716 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 711 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].table_vec)->push_back((yyvsp[-2].table));
			auto tbl = new TableRef(kTableCrossProduct);
			tbl->list = (yyvsp[0].table_vec);
			(yyval.table) = tbl;
		}
#line 2727 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 722 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2738 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 733 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table_vec) = new std::vector<TableRef*>(); (yyval.table_vec)->push_back((yyvsp[0].table)); }
#line 2744 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 734 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].table_vec)->push_back((yyvsp[0].table)); (yyval.table_vec) = (yyvsp[-2].table_vec); }
#line 2750 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 739 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableName);
			tbl->name = (yyvsp[-1].sval);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2761 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 749 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.table) = new TableRef(kTableName);
			(yyval.table)->name = (yyvsp[0].sval);
		}
#line 2770 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 763 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 2776 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 769 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 2782 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 778 "bison_parser.y" /* yacc.c:1646  */
    { 
			(yyval.table) = new TableRef(kTableJoin);
			(yyval.table)->join = new JoinDefinition();
			(yyval.table)->join->type = (JoinType) (yyvsp[-4].uval);
			(yyval.table)->join->left = (yyvsp[-5].table);
			(yyval.table)->join->right = (yyvsp[-2].table);
			(yyval.table)->join->condition = (yyvsp[0].expr);
		}
#line 2795 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 789 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2801 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 790 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinOuter; }
#line 2807 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 791 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinLeft; }
#line 2813 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 792 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinRight; }
#line 2819 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 793 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2825 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 799 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2836 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 824 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = new std::vector<char*>(); (yyval.str_vec)->push_back((yyvsp[0].sval)); }
#line 2842 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 825 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].str_vec)->push_back((yyvsp[0].sval)); (yyval.str_vec) = (yyvsp[-2].str_vec); }
#line 2848 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 835 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.createDB_stmt) = new CreateDBStatement();
			(yyval.createDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 2857 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 849 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.dropDB_stmt) = new DropDBStatement();
			(yyval.dropDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 2866 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 170:
#line 860 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.useDB_stmt) = new UseDBStatement();
			(yyval.useDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 2875 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 871 "bison_parser.y" /* yacc.c:1646  */
    {
 			(yyval.showDB_stmt) = new ShowDBStatement();
 		}
#line 2883 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 880 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.showTable_stmt) = new ShowTableStatement();
		}
#line 2891 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 890 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.createIndex_stmt) = new CreateIndexStatement();
			(yyval.createIndex_stmt)->table = (yyvsp[-3].sval);
			(yyval.createIndex_stmt)->column = (yyvsp[-1].sval);
		}
#line 2901 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 902 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.dropIndex_stmt) = new DropIndexStatement();
			(yyval.dropIndex_stmt)->table = (yyvsp[-3].sval);
			(yyval.dropIndex_stmt)->column = (yyvsp[-1].sval);
		}
#line 2911 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 916 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.desc_stmt) = new DescStatement();
			(yyval.desc_stmt)->table_name = (yyvsp[0].sval);
		}
#line 2920 "bison_parser.cpp" /* yacc.c:1646  */
    break;


#line 2924 "bison_parser.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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
      yyerror (&yylloc, result, scanner, YY_("syntax error"));
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
        yyerror (&yylloc, result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc, result, scanner);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, result, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, result, scanner);
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
#line 924 "bison_parser.y" /* yacc.c:1906  */

/*********************************
 ** Section 4: Additional C code
 *********************************/

/* empty */

