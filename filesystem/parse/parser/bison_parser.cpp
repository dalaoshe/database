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
	std::vector<std::vector<hsql::Expr*>*>* expr_vec_in_vec;

#line 364 "bison_parser.cpp" /* yacc.c:355  */
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

#line 394 "bison_parser.cpp" /* yacc.c:358  */

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
#define YYLAST   508

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  154
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  81
/* YYNRULES -- Number of rules.  */
#define YYNRULES  181
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  343

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
       0,   253,   253,   260,   261,   265,   270,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   299,   304,   312,   316,   328,   336,
     340,   350,   356,   366,   367,   368,   372,   373,   377,   378,
     382,   385,   391,   392,   395,   396,   399,   400,   401,   404,
     405,   406,   407,   417,   421,   433,   441,   453,   459,   467,
     472,   479,   480,   490,   499,   500,   504,   516,   517,   521,
     522,   526,   531,   543,   544,   545,   549,   560,   561,   565,
     570,   575,   576,   580,   585,   589,   590,   593,   594,   598,
     599,   600,   605,   606,   607,   614,   615,   619,   620,   624,
     631,   632,   633,   634,   635,   639,   640,   641,   645,   646,
     647,   648,   649,   650,   654,   655,   656,   657,   658,   659,
     660,   661,   662,   663,   664,   669,   670,   671,   672,   673,
     674,   675,   679,   683,   684,   688,   689,   690,   691,   695,
     700,   701,   705,   709,   714,   725,   726,   736,   737,   743,
     748,   749,   754,   764,   772,   773,   778,   779,   783,   784,
     792,   804,   805,   806,   807,   808,   814,   820,   824,   833,
     834,   839,   840,   850,   856,   864,   875,   886,   895,   905,
     917,   931
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
  "value_lists", "opt_column_list", "update_statement",
  "update_clause_commalist", "update_clause", "select_statement",
  "select_with_paren", "select_no_paren", "set_operator", "select_clause",
  "opt_distinct", "select_list", "from_clause", "opt_where", "opt_group",
  "opt_having", "opt_order", "opt_order_type", "opt_limit", "expr_list",
  "literal_list", "expr_alias", "expr", "scalar_expr", "unary_expr",
  "binary_expr", "comp_expr", "function_expr", "column_name", "literal",
  "string_literal", "num_literal", "int_literal", "star_expr",
  "placeholder_expr", "table_ref", "table_ref_atomic",
  "table_ref_commalist", "table_ref_name", "table_ref_name_no_alias",
  "table_name", "alias", "opt_alias", "join_clause", "opt_join_type",
  "join_table", "join_condition", "opt_semicolon", "ident_commalist",
  "createDB_statement", "DBname", "dropDB_statement", "useDB_statement",
  "showDB_statement", "showTable_statement", "createIndex_statement",
  "dropIndex_statement", "desc_statement", YY_NULLPTR
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

#define YYPACT_NINF -265

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-265)))

#define YYTABLE_NINF -168

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-168)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     293,    13,    43,    65,    66,   -10,   -12,    16,    -4,    95,
      43,    43,    -6,   -19,   114,   -31,   124,   -21,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,    30,  -265,  -265,  -265,  -265,  -265,  -265,  -265,
    -265,   122,   -13,  -265,    -8,   -99,    43,    48,   114,    43,
      54,    43,  -265,    21,    67,  -265,  -265,    43,    43,   114,
    -265,  -265,  -265,  -265,    19,    35,  -265,   293,  -265,  -265,
    -265,    75,  -265,   131,   132,  -265,   208,    10,    56,   293,
      74,   106,    43,  -265,   138,  -265,   139,    76,  -109,  -265,
    -265,  -265,  -265,    21,    77,    80,    81,    82,    21,  -265,
      21,  -265,   146,    79,  -265,   197,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,  -265,   226,    87,
    -265,  -265,  -265,  -265,  -265,    21,   164,   229,  -265,  -265,
    -113,  -265,  -265,   -21,   233,   194,   -48,    21,  -265,   235,
     237,    47,    95,   238,   352,   240,   240,   240,   240,    69,
      53,     4,   138,    21,  -265,    21,    21,    21,    21,    21,
     155,   242,   104,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,  -265,  -265,   121,   -57,  -265,   248,   263,
     132,   204,  -265,    10,   105,   111,  -265,   148,     0,   339,
     179,  -265,  -265,   -93,   128,  -265,    21,  -265,   119,   129,
     130,   133,   134,  -265,   -31,  -265,   115,    99,     7,  -265,
      68,   205,  -265,   367,   311,   311,   367,   352,    21,  -265,
      10,   282,   367,   311,   311,    69,    69,   136,   136,   136,
    -265,    10,   226,  -265,   135,  -265,  -265,  -265,  -265,   229,
    -265,  -265,  -265,   193,     1,   137,   160,   -26,  -265,  -265,
      43,  -265,   275,    10,   140,   123,  -265,  -265,  -265,  -265,
     141,     4,  -265,  -265,  -265,  -265,  -265,   198,   171,  -265,
     367,    15,  -265,  -265,  -265,  -265,   235,  -265,  -265,  -265,
    -265,   143,    21,   149,   187,    -1,   150,  -265,  -265,    23,
     152,  -265,     7,  -265,   147,     8,    21,  -265,  -265,   289,
     195,   339,   154,    21,   156,   199,  -265,  -265,  -265,    10,
     108,     4,   -31,  -265,   188,   -23,   161,   217,  -265,  -265,
     167,   307,   169,    51,  -265,   175,    21,    21,  -265,  -265,
    -265,  -265,   176,   312,  -265,     7,   339,  -265,   339,  -265,
     178,  -265,  -265
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    78,
       0,     0,     0,     0,     0,     0,     0,   170,     3,     6,
       5,    15,     8,     9,    14,    11,    12,    10,    13,     7,
      67,    68,    88,    16,    17,    18,    19,    20,    21,    22,
      23,     0,   154,    56,    26,     0,     0,    37,     0,     0,
       0,     0,    77,     0,     0,   153,   181,     0,     0,     0,
     178,   177,   174,   176,     0,     0,     1,   169,     2,    74,
      75,     0,    73,     0,    94,    54,     0,     0,     0,     0,
       0,     0,     0,   173,    82,    29,     0,    62,   133,   139,
     140,   142,   137,     0,     0,     0,     0,     0,     0,   143,
       0,   144,     0,    79,    95,   159,   101,   102,   103,   114,
     104,   105,   107,   135,   136,   141,   106,   138,     0,     0,
      53,   175,    70,    69,     4,     0,    88,     0,    71,   155,
       0,    97,    24,   170,     0,     0,     0,     0,    55,     0,
       0,     0,    78,     0,   109,     0,     0,     0,     0,   108,
       0,     0,    82,     0,   157,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,    99,     0,    82,    64,     0,    91,
      94,    92,    27,     0,     0,     0,    36,     0,    48,    81,
       0,    30,   171,     0,     0,    58,     0,   134,   133,     0,
       0,     0,     0,   100,     0,    80,   145,   147,   159,   149,
     165,    84,    96,   126,   129,   130,   123,   121,     0,   156,
       0,   122,   125,   127,   128,   116,   115,   118,   117,   119,
     120,     0,     0,    63,     0,    90,    89,    87,    72,     0,
      98,    25,   179,     0,     0,     0,     0,    35,    38,    41,
       0,    61,     0,     0,    57,     0,   110,   111,   113,   112,
       0,     0,   152,   161,   162,   164,   163,     0,     0,    76,
     124,     0,    66,    65,   180,    93,     0,    50,    51,    52,
      49,    43,     0,     0,     0,    48,     0,    28,   172,     0,
       0,   132,     0,   150,   146,     0,     0,   131,    31,     0,
      45,     0,   114,     0,     0,     0,    39,    32,    60,     0,
     148,     0,     0,   167,     0,    86,     0,     0,    40,    47,
     114,     0,     0,     0,   151,     0,     0,     0,    83,    42,
      44,    46,     0,     0,    59,     0,   168,   160,    85,    34,
       0,   166,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -265,  -265,   246,   250,   249,  -265,  -265,  -265,  -265,    73,
    -265,  -265,  -265,  -265,    58,  -265,  -265,  -265,  -265,  -265,
    -265,  -265,  -265,  -265,  -265,  -265,  -265,   100,  -192,   326,
       2,  -265,   271,   209,  -265,  -265,  -112,  -265,  -265,   227,
    -265,   174,    59,  -188,   203,   -80,  -265,  -265,  -265,  -251,
    -265,    70,   -76,  -135,  -265,  -121,  -265,  -265,  -265,  -238,
    -265,    62,  -265,    -2,  -264,   158,  -265,  -265,    63,  -265,
     230,  -265,  -265,   -11,  -265,  -265,  -265,  -265,  -265,  -265,
    -265
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    20,    21,    22,    86,   190,
      23,   286,    82,   247,   248,   300,   318,   249,   281,    24,
      25,    26,    27,   254,   141,    28,   176,   177,    29,    30,
      31,    73,    32,    53,   102,   152,   138,   269,   328,    74,
     237,   128,   103,   130,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   205,   206,
     294,   207,    54,   208,   173,   174,   209,   267,   210,   337,
      68,   193,    33,    63,    34,    35,    36,    37,    38,    39,
      40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   131,   244,   244,   191,   284,   181,    42,    55,    56,
     154,    42,   260,   144,    89,    90,    91,    65,   149,   137,
     150,     9,   327,   293,    88,    89,    90,    91,   310,   277,
     305,   302,   271,   182,   187,    60,   142,    83,   143,   183,
     211,   278,    69,    41,    80,   179,    42,    84,   121,    87,
      78,    79,   320,   251,    46,   119,   120,   189,    57,   252,
     155,   156,   157,    47,   233,   289,     1,    58,    44,    45,
      49,   341,    70,   324,     2,   213,   214,   215,   216,   217,
     136,     3,    51,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,     5,     6,   232,   279,   188,    50,     9,
      71,    92,     7,     8,    72,   194,   280,   240,     9,    61,
      52,    48,    92,    10,    15,    59,   255,    62,   275,   161,
     325,   323,   245,   245,    66,    75,   285,    67,    93,   153,
     155,   156,   157,   263,    76,    11,    12,    77,   270,   264,
     265,   191,   158,   195,   131,    94,    95,    96,    97,   204,
      13,   246,   246,   312,   159,   272,   266,    85,    98,    99,
     160,   297,    81,   101,  -167,   122,   100,   183,   162,   308,
    -167,  -167,   163,  -166,   101,   183,   118,   131,    14,  -166,
    -166,   123,   164,     9,   165,   166,  -167,  -167,   125,   167,
     168,   169,   170,   171,   172,  -166,  -166,   334,   127,   203,
     154,    15,   301,   183,   155,   156,   157,   169,   170,   171,
     172,   129,   158,   135,   137,   199,   200,   201,   202,   134,
     139,   140,   145,   301,   159,   146,   147,   148,   151,   175,
     160,   153,   178,   131,    71,    91,   185,   186,   162,    89,
     192,   197,   163,   198,   218,   219,   336,   338,   287,   220,
     231,   234,   164,   239,   165,   166,   241,   242,   243,   167,
     168,   169,   170,   171,   172,   250,   143,   261,   268,   291,
     155,   156,   157,   253,   276,   256,   257,   172,   288,   258,
     259,   274,   282,   283,   296,   295,   158,   292,   299,   155,
     156,   157,   290,   304,   303,   316,   307,   309,   159,   311,
     319,   321,   317,     1,   160,   322,   326,   329,   330,   161,
     332,     2,   162,   331,   333,   340,   163,   124,     3,  -168,
    -168,   335,   339,     4,   342,   133,   164,   132,   165,   166,
       5,     6,   273,   167,   168,   169,   170,   171,   172,     7,
       8,    64,   235,   306,   126,     9,   155,   156,   157,   298,
      10,   196,   158,   180,   238,   315,   212,   313,   314,   155,
     156,   157,     0,   184,   159,   236,   262,     0,     0,     0,
     160,   158,    11,    12,   155,   156,   157,     0,   162,     0,
       0,     0,   163,   159,     0,     0,     0,    13,     0,   160,
       0,     0,   164,     0,   165,   166,     0,   162,     0,   167,
     168,   169,   170,   171,   172,     0,     0,     0,     0,     0,
       0,   164,     0,   165,   166,    14,     0,     0,   167,   168,
     169,   170,   171,   172,     0,     0,   162,     0,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15,     0,
     159,   158,  -168,  -168,     0,     0,   160,   167,   168,   169,
     170,   171,   172,     0,   162,     0,   158,     0,   163,   160,
       0,     0,     0,     0,     0,     0,     0,   162,   164,     0,
     165,   166,     0,     0,     0,   167,   168,   169,   170,   171,
     172,   164,   162,   165,   166,     0,     0,     0,   167,   168,
     169,   170,   171,   172,     0,     0,   164,     0,   165,   166,
       0,     0,     0,   167,   168,   169,   170,   171,   172
};

static const yytype_int16 yycheck[] =
{
       2,    77,     3,     3,   139,    31,   127,     3,    10,    11,
       3,     3,   204,    93,     4,     5,     6,    15,    98,    76,
     100,    52,    45,   261,     3,     4,     5,     6,   292,    28,
      31,   282,   220,   146,    82,    54,   145,    48,   147,   152,
     152,    40,    12,    30,    46,   125,     3,    49,    59,    51,
     149,   150,   303,   146,    64,    57,    58,   137,    64,   152,
       7,     8,     9,    73,   176,   253,    10,    73,     3,     3,
      82,   335,    42,   311,    18,   155,   156,   157,   158,   159,
      82,    25,    86,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,    37,    38,   152,    95,   145,    82,    52,
      70,    91,    46,    47,    74,    58,   105,   183,    52,   128,
      15,   121,    91,    57,   145,   121,   196,     3,   239,   112,
     312,   309,   123,   123,     0,     3,   152,   148,   107,   152,
       7,     8,     9,    65,   147,    79,    80,   145,   218,    71,
      72,   276,    89,   141,   220,   124,   125,   126,   127,   145,
      94,   152,   152,   145,   101,   231,    88,   103,   137,   138,
     107,   146,   114,   153,    65,   146,   145,   152,   115,   146,
      71,    72,   119,    65,   153,   152,   109,   253,   122,    71,
      72,   146,   129,    52,   131,   132,    87,    88,   113,   136,
     137,   138,   139,   140,   141,    87,    88,   146,    66,   146,
       3,   145,   282,   152,     7,     8,     9,   138,   139,   140,
     141,     3,    89,   107,    76,   145,   146,   147,   148,   145,
      81,   145,   145,   303,   101,   145,   145,   145,    82,     3,
     107,   152,   145,   309,    70,     6,     3,    43,   115,     4,
       3,     3,   119,     3,    89,     3,   326,   327,   250,   145,
     129,     3,   129,    49,   131,   132,   151,   146,   110,   136,
     137,   138,   139,   140,   141,    86,   147,   152,    63,   146,
       7,     8,     9,   145,    81,   146,   146,   141,     3,   146,
     146,   146,   145,   123,   113,    87,    89,   146,   145,     7,
       8,     9,   152,   106,   145,     6,   146,   145,   101,   152,
     146,   145,   107,    10,   107,   106,   118,   146,    91,   112,
       3,    18,   115,   146,   145,     3,   119,    67,    25,     8,
       9,   146,   146,    30,   146,    79,   129,    78,   131,   132,
      37,    38,   232,   136,   137,   138,   139,   140,   141,    46,
      47,    15,    79,   285,    73,    52,     7,     8,     9,   276,
      57,   142,    89,   126,   180,   296,   153,   295,   295,     7,
       8,     9,    -1,   133,   101,   102,   208,    -1,    -1,    -1,
     107,    89,    79,    80,     7,     8,     9,    -1,   115,    -1,
      -1,    -1,   119,   101,    -1,    -1,    -1,    94,    -1,   107,
      -1,    -1,   129,    -1,   131,   132,    -1,   115,    -1,   136,
     137,   138,   139,   140,   141,    -1,    -1,    -1,    -1,    -1,
      -1,   129,    -1,   131,   132,   122,    -1,    -1,   136,   137,
     138,   139,   140,   141,    -1,    -1,   115,    -1,    89,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,    -1,
     101,    89,   131,   132,    -1,    -1,   107,   136,   137,   138,
     139,   140,   141,    -1,   115,    -1,    89,    -1,   119,   107,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   115,   129,    -1,
     131,   132,    -1,    -1,    -1,   136,   137,   138,   139,   140,
     141,   129,   115,   131,   132,    -1,    -1,    -1,   136,   137,
     138,   139,   140,   141,    -1,    -1,   129,    -1,   131,   132,
      -1,    -1,    -1,   136,   137,   138,   139,   140,   141
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    18,    25,    30,    37,    38,    46,    47,    52,
      57,    79,    80,    94,   122,   145,   155,   156,   157,   158,
     159,   160,   161,   164,   173,   174,   175,   176,   179,   182,
     183,   184,   186,   226,   228,   229,   230,   231,   232,   233,
     234,    30,     3,   217,     3,     3,    64,    73,   121,    82,
      82,    86,    15,   187,   216,   217,   217,    64,    73,   121,
      54,   128,     3,   227,   183,   184,     0,   148,   224,    12,
      42,    70,    74,   185,   193,     3,   147,   145,   149,   150,
     217,   114,   166,   227,   217,   103,   162,   217,     3,     4,
       5,     6,    91,   107,   124,   125,   126,   127,   137,   138,
     145,   153,   188,   196,   198,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   109,   217,
     217,   227,   146,   146,   157,   113,   186,    66,   195,     3,
     197,   206,   158,   156,   145,   107,   217,    76,   190,    81,
     145,   178,   145,   147,   199,   145,   145,   145,   145,   199,
     199,    82,   189,   152,     3,     7,     8,     9,    89,   101,
     107,   112,   115,   119,   129,   131,   132,   136,   137,   138,
     139,   140,   141,   218,   219,     3,   180,   181,   145,   199,
     193,   209,   146,   152,   224,     3,    43,    82,   145,   199,
     163,   207,     3,   225,    58,   184,   187,     3,     3,   205,
     205,   205,   205,   146,   145,   212,   213,   215,   217,   220,
     222,   190,   198,   199,   199,   199,   199,   199,    89,     3,
     145,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   129,   152,   190,     3,    79,   102,   194,   195,    49,
     206,   151,   146,   110,     3,   123,   152,   167,   168,   171,
      86,   146,   152,   145,   177,   199,   146,   146,   146,   146,
     182,   152,   219,    65,    71,    72,    88,   221,    63,   191,
     199,   197,   206,   181,   146,   209,    81,    28,    40,    95,
     105,   172,   145,   123,    31,   152,   165,   217,     3,   197,
     152,   146,   146,   213,   214,    87,   113,   146,   163,   145,
     169,   199,   203,   145,   106,    31,   168,   146,   146,   145,
     218,   152,   145,   215,   222,   196,     6,   107,   170,   146,
     203,   145,   106,   197,   213,   182,   118,    45,   192,   146,
      91,   146,     3,   145,   146,   146,   199,   223,   199,   146,
       3,   218,   146
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
     177,   178,   178,   179,   180,   180,   181,   182,   182,   183,
     183,   184,   184,   185,   185,   185,   186,   187,   187,   188,
     189,   190,   190,   191,   191,   192,   192,   193,   193,   194,
     194,   194,   195,   195,   195,   196,   196,   197,   197,   198,
     199,   199,   199,   199,   199,   200,   200,   200,   201,   201,
     201,   201,   201,   201,   202,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   203,   203,   203,   203,   203,
     203,   203,   204,   205,   205,   206,   206,   206,   206,   207,
     208,   208,   209,   210,   211,   212,   212,   213,   213,   213,
     214,   214,   215,   216,   217,   217,   218,   218,   219,   219,
     220,   221,   221,   221,   221,   221,   222,   222,   223,   224,
     224,   225,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     6,     2,     5,     7,     1,
       1,     8,     8,     6,     5,     0,     3,     0,     1,     3,
       4,     1,     3,     0,     2,     0,     5,     4,     0,     1,
       1,     1,     1,     3,     3,     4,     2,     6,     5,     5,
       3,     3,     0,     5,     1,     3,     3,     1,     1,     3,
       3,     3,     5,     1,     1,     1,     6,     1,     0,     1,
       2,     2,     0,     4,     0,     2,     0,     4,     0,     1,
       1,     0,     2,     4,     0,     1,     3,     1,     3,     2,
       3,     1,     1,     1,     1,     1,     1,     1,     2,     2,
       4,     4,     4,     4,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     3,     3,     3,     3,     3,
       3,     5,     5,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     4,     1,
       1,     3,     2,     1,     1,     3,     2,     1,     1,     0,
       6,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       0,     1,     3,     3,     1,     3,     2,     2,     2,     6,
       6,     2
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

#line 1728 "bison_parser.cpp" /* yacc.c:1429  */
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
#line 253 "bison_parser.y" /* yacc.c:1646  */
    {
			*result = (yyvsp[-1].stmt_list);
		}
#line 1919 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 260 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.stmt_list) = new SQLParserResult((yyvsp[0].statement)); }
#line 1925 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 261 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].stmt_list)->addStatement((yyvsp[0].statement)); (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 1931 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 265 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].prep_stmt)->setPlaceholders(yyloc.placeholder_list);
			yyloc.placeholder_list.clear();
			(yyval.statement) = (yyvsp[0].prep_stmt);
		}
#line 1941 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 275 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].select_stmt); }
#line 1947 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 276 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].import_stmt); }
#line 1953 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 277 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].create_stmt); }
#line 1959 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 278 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].insert_stmt); }
#line 1965 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 279 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1971 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 280 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1977 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 281 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].update_stmt); }
#line 1983 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 282 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].drop_stmt); }
#line 1989 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 283 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].exec_stmt); }
#line 1995 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 284 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].createDB_stmt); }
#line 2001 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 285 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].dropDB_stmt); }
#line 2007 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 286 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].useDB_stmt); }
#line 2013 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 287 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].showDB_stmt); }
#line 2019 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 288 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].showTable_stmt); }
#line 2025 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 289 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].createIndex_stmt); }
#line 2031 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 290 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].dropIndex_stmt); }
#line 2037 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 291 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].desc_stmt); }
#line 2043 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 299 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-2].sval);
			(yyval.prep_stmt)->query = new SQLParserResult((yyvsp[0].statement));
		}
#line 2053 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 304 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-4].sval);
			(yyval.prep_stmt)->query = (yyvsp[-2].stmt_list);
		}
#line 2063 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 312 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[0].sval);
		}
#line 2072 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 316 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[-3].sval);
			(yyval.exec_stmt)->parameters = (yyvsp[-1].expr_vec);
		}
#line 2082 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 328 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.import_stmt) = new ImportStatement((ImportStatement::ImportType) (yyvsp[-4].uval));
			(yyval.import_stmt)->filePath = (yyvsp[-2].sval);
			(yyval.import_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2092 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 336 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ImportStatement::kImportCSV; }
#line 2098 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 340 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].expr)->name; }
#line 2104 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 350 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.create_stmt) = new CreateStatement(CreateStatement::kTableFromTbl);
			(yyval.create_stmt)->ifNotExists = (yyvsp[-5].bval);
			(yyval.create_stmt)->tableName = (yyvsp[-4].sval);
			(yyval.create_stmt)->filePath = (yyvsp[0].sval);
		}
#line 2115 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 356 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
			(yyval.create_stmt)->ifNotExists = (yyvsp[-5].bval);
			(yyval.create_stmt)->tableName = (yyvsp[-4].sval);
			(yyval.create_stmt)->columns = (yyvsp[-2].column_vec);
			(yyval.create_stmt)->primary_key = (yyvsp[-1].sval);
		}
#line 2127 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 366 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-1].sval); }
#line 2133 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 367 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[-1].sval); }
#line 2139 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 368 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 2145 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 372 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2151 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 373 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2157 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 377 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.column_vec) = new std::vector<ColumnDefinition*>(); (yyval.column_vec)->push_back((yyvsp[0].column_t)); }
#line 2163 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 378 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].column_vec)->push_back((yyvsp[0].column_t)); (yyval.column_vec) = (yyvsp[-2].column_vec); }
#line 2169 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 382 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.column_t) = new ColumnDefinition((yyvsp[-3].sval), (AttrType) (yyvsp[-2].uval), (yyvsp[-1].ival), (yyvsp[0].bval));
		}
#line 2177 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 385 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.column_t) = new ColumnDefinition((yyvsp[0].expr));
		}
#line 2185 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 391 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.ival) = (yyvsp[-1].ival); }
#line 2191 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 392 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.ival) = 20;}
#line 2197 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 395 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2203 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 396 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false;}
#line 2209 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 399 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2215 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 400 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2221 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 401 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2227 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 404 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = AttrType::INT; }
#line 2233 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 405 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = AttrType::INT; }
#line 2239 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 406 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = AttrType::FLOAT; }
#line 2245 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 407 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = AttrType::STRING; }
#line 2251 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 417 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kTable);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2260 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 421 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kPreparedStatement);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2269 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 433 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[-1].sval);
			(yyval.delete_stmt)->expr = (yyvsp[0].expr);
		}
#line 2279 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 441 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2288 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 453 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertValues);
			(yyval.insert_stmt)->tableName = (yyvsp[-3].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-2].str_vec);
			(yyval.insert_stmt)->values = (yyvsp[0].expr_vec_in_vec);
		}
#line 2299 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 459 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertSelect);
			(yyval.insert_stmt)->tableName = (yyvsp[-2].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-1].str_vec);
			(yyval.insert_stmt)->select = (yyvsp[0].select_stmt);
		}
#line 2310 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 467 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyvsp[-4].expr_vec_in_vec)->push_back((yyvsp[-1].expr_vec));
            (yyval.expr_vec_in_vec) = (yyvsp[-4].expr_vec_in_vec);
        }
#line 2319 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 472 "bison_parser.y" /* yacc.c:1646  */
    {
             (yyval.expr_vec_in_vec) = new std::vector<std::vector<Expr*>*>();
             (yyval.expr_vec_in_vec)->push_back((yyvsp[-1].expr_vec));
        }
#line 2328 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 479 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = (yyvsp[-1].str_vec); }
#line 2334 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 480 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = NULL; }
#line 2340 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 490 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.update_stmt) = new UpdateStatement();
		(yyval.update_stmt)->table = (yyvsp[-3].table);
		(yyval.update_stmt)->updates = (yyvsp[-1].update_vec);
		(yyval.update_stmt)->where = (yyvsp[0].expr);
	}
#line 2351 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 499 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.update_vec) = new std::vector<UpdateClause*>(); (yyval.update_vec)->push_back((yyvsp[0].update_t)); }
#line 2357 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 500 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].update_vec)->push_back((yyvsp[0].update_t)); (yyval.update_vec) = (yyvsp[-2].update_vec); }
#line 2363 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 504 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.update_t) = new UpdateClause();
			(yyval.update_t)->column = (yyvsp[-2].sval);
			(yyval.update_t)->value = (yyvsp[0].expr);
		}
#line 2373 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 521 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2379 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 522 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2385 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 526 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2395 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 531 "bison_parser.y" /* yacc.c:1646  */
    {
			// TODO: allow multiple unions (through linked list)
			// TODO: capture type of set_operator
			// TODO: might overwrite order and limit of first select here
			(yyval.select_stmt) = (yyvsp[-4].select_stmt);
			(yyval.select_stmt)->unionSelect = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2409 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 549 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement();
			(yyval.select_stmt)->selectDistinct = (yyvsp[-4].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-3].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2422 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 560 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2428 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 561 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2434 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 570 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[0].table); }
#line 2440 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 575 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2446 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 576 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2452 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 580 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.group_t) = new GroupByDescription();
			(yyval.group_t)->columns = (yyvsp[-1].expr_vec);
			(yyval.group_t)->having = (yyvsp[0].expr);
		}
#line 2462 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 585 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.group_t) = NULL; }
#line 2468 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 589 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2474 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 590 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2480 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 593 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = new OrderDescription((yyvsp[0].order_type), (yyvsp[-1].expr)); }
#line 2486 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 594 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = NULL; }
#line 2492 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 598 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2498 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 599 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderDesc; }
#line 2504 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 600 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2510 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 605 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[0].expr)->ival, kNoOffset); delete (yyvsp[0].expr); }
#line 2516 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 606 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[-2].expr)->ival, (yyvsp[0].expr)->ival); delete (yyvsp[-2].expr); delete (yyvsp[0].expr); }
#line 2522 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 607 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = NULL; }
#line 2528 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 614 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2534 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 615 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2540 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 619 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr));}
#line 2546 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 620 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2552 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 624 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = (yyvsp[-1].expr);
			(yyval.expr)->alias = (yyvsp[0].sval);
		}
#line 2561 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 631 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2567 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 108:
#line 645 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::UMINUS, (yyvsp[0].expr)); }
#line 2573 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 646 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::NOT, (yyvsp[0].expr)); }
#line 2579 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 110:
#line 647 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::SUM, (yyvsp[-1].expr)); }
#line 2585 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 648 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::AVG, (yyvsp[-1].expr)); }
#line 2591 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 649 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::MAX, (yyvsp[-1].expr)); }
#line 2597 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 650 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::MIN, (yyvsp[-1].expr)); }
#line 2603 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 655 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '-', (yyvsp[0].expr)); }
#line 2609 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 656 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '+', (yyvsp[0].expr)); }
#line 2615 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 657 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '/', (yyvsp[0].expr)); }
#line 2621 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 658 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '*', (yyvsp[0].expr)); }
#line 2627 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 659 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '%', (yyvsp[0].expr)); }
#line 2633 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 660 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '^', (yyvsp[0].expr)); }
#line 2639 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 661 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::AND, (yyvsp[0].expr)); }
#line 2645 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 662 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::OR, (yyvsp[0].expr)); }
#line 2651 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 663 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LIKE, (yyvsp[0].expr)); }
#line 2657 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 664 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), Expr::NOT_LIKE, (yyvsp[0].expr)); }
#line 2663 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 669 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '=', (yyvsp[0].expr)); }
#line 2669 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 670 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::NOT_EQUALS, (yyvsp[0].expr)); }
#line 2675 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 671 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '<', (yyvsp[0].expr)); }
#line 2681 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 672 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '>', (yyvsp[0].expr)); }
#line 2687 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 673 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LESS_EQ, (yyvsp[0].expr)); }
#line 2693 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 674 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::GREATER_EQ, (yyvsp[0].expr)); }
#line 2699 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 675 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-4].expr), Expr::IN,(yyvsp[-1].expr_vec));}
#line 2705 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 679 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeFunctionRef((yyvsp[-4].sval), (yyvsp[-1].expr), (yyvsp[-2].bval)); }
#line 2711 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 683 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[0].sval)); }
#line 2717 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 684 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 2723 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 137:
#line 690 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = Expr::makeLiteral();}
#line 2729 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 695 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].sval)); }
#line 2735 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 700 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].fval)); }
#line 2741 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 142:
#line 705 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].ival)); }
#line 2747 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 709 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr(kExprStar); }
#line 2753 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 714 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = Expr::makePlaceholder(yylloc.total_column);
			yyloc.placeholder_list.push_back((yyval.expr));
		}
#line 2762 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 726 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].table_vec)->push_back((yyvsp[-2].table));
			auto tbl = new TableRef(kTableCrossProduct);
			tbl->list = (yyvsp[0].table_vec);
			(yyval.table) = tbl;
		}
#line 2773 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 737 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2784 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 748 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table_vec) = new std::vector<TableRef*>(); (yyval.table_vec)->push_back((yyvsp[0].table)); }
#line 2790 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 151:
#line 749 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].table_vec)->push_back((yyvsp[0].table)); (yyval.table_vec) = (yyvsp[-2].table_vec); }
#line 2796 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 754 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableName);
			tbl->name = (yyvsp[-1].sval);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2807 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 764 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.table) = new TableRef(kTableName);
			(yyval.table)->name = (yyvsp[0].sval);
		}
#line 2816 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 778 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 2822 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 784 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 2828 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 793 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.table) = new TableRef(kTableJoin);
			(yyval.table)->join = new JoinDefinition();
			(yyval.table)->join->type = (JoinType) (yyvsp[-4].uval);
			(yyval.table)->join->left = (yyvsp[-5].table);
			(yyval.table)->join->right = (yyvsp[-2].table);
			(yyval.table)->join->condition = (yyvsp[0].expr);
		}
#line 2841 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 804 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2847 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 805 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinOuter; }
#line 2853 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 806 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinLeft; }
#line 2859 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 807 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinRight; }
#line 2865 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 808 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2871 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 814 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2882 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 171:
#line 839 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = new std::vector<char*>(); (yyval.str_vec)->push_back((yyvsp[0].sval)); }
#line 2888 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 172:
#line 840 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].str_vec)->push_back((yyvsp[0].sval)); (yyval.str_vec) = (yyvsp[-2].str_vec); }
#line 2894 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 850 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.createDB_stmt) = new CreateDBStatement();
			(yyval.createDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 2903 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 175:
#line 864 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.dropDB_stmt) = new DropDBStatement();
			(yyval.dropDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 2912 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 176:
#line 875 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.useDB_stmt) = new UseDBStatement();
			(yyval.useDB_stmt)->DBname = (yyvsp[0].sval);
		}
#line 2921 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 177:
#line 886 "bison_parser.y" /* yacc.c:1646  */
    {
 			(yyval.showDB_stmt) = new ShowDBStatement();
 		}
#line 2929 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 178:
#line 895 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.showTable_stmt) = new ShowTableStatement();
		}
#line 2937 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 179:
#line 905 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.createIndex_stmt) = new CreateIndexStatement();
			(yyval.createIndex_stmt)->table = (yyvsp[-3].sval);
			(yyval.createIndex_stmt)->column = (yyvsp[-1].sval);
		}
#line 2947 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 180:
#line 917 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.dropIndex_stmt) = new DropIndexStatement();
			(yyval.dropIndex_stmt)->table = (yyvsp[-3].sval);
			(yyval.dropIndex_stmt)->column = (yyvsp[-1].sval);
		}
#line 2957 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 181:
#line 931 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.desc_stmt) = new DescStatement();
			(yyval.desc_stmt)->table_name = (yyvsp[0].sval);
		}
#line 2966 "bison_parser.cpp" /* yacc.c:1646  */
    break;


#line 2970 "bison_parser.cpp" /* yacc.c:1646  */
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
#line 939 "bison_parser.y" /* yacc.c:1906  */

/*********************************
 ** Section 4: Additional C code
 *********************************/

/* empty */

