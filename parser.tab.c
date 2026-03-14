/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void yyerror(const char *s);
int yylex(void);
extern int yylineno;

/* ---------------- Symbol Table ---------------- */

typedef struct{
    char name[50];
    double value;
    int type; /* 0: numeric, 1: char */
    int is_array;
    int dimensions; /* 1= 1D, 2 = 2D */
    int rows;
    int cols;
    double array_values[100];
    int array_size;

    double array2d[50][50];
} Symbol;

Symbol symtab[1000];
int symcount = 0;
int execute_flag = 1;  /* 1 = execute, 0 = skip */
int loop_flag = 0;     /* 1 = in loop, 0 = not in loop */

int current_decl_type = 0; /* 0: numeric, 1: char */

void set_symbol(char *name, double value){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            symtab[i].value=value;
            return;
        }
    }
    strcpy(symtab[symcount].name,name);
    symtab[symcount].value=value;
    symtab[symcount].type=current_decl_type;
    symtab[symcount].is_array=0;
    symtab[symcount].array_size=0;
    symcount++;
}

int get_symbol_type(char *name){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0)
            return symtab[i].type;
    }
    return 0;
}

void declare_2d_array(char *name,int r,int c){
    strcpy(symtab[symcount].name,name);

    symtab[symcount].is_array = 1;
    symtab[symcount].dimensions = 2;

    symtab[symcount].rows = r;
    symtab[symcount].cols = c;
    symtab[symcount].type = current_decl_type;

    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++)
            symtab[symcount].array2d[i][j] = 0;

    symcount++;
}

void set_array2d_element(char *name,int r,int c,double value){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){

            if(symtab[i].dimensions == 2 &&
               r < symtab[i].rows &&
               c < symtab[i].cols){

                symtab[i].array2d[r][c] = value;
            }

            return;
        }
    }
}
double get_array2d_element(char *name,int r,int c){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){

            if(symtab[i].dimensions == 2 &&
               r < symtab[i].rows &&
               c < symtab[i].cols){

                return symtab[i].array2d[r][c];
            }
        }
    }

    printf("Runtime error: 2D array access error\n");
    return 0;
}

void set_array_element(char *name, int index, double value){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            if(symtab[i].is_array && index >= 0 && index < symtab[i].array_size){
                symtab[i].array_values[index]=value;
            }
            return;
        }
    }
}

double get_array_element(char *name, int index){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0){
            if(symtab[i].is_array && index >= 0 && index < symtab[i].array_size){
                return symtab[i].array_values[index];
            }
        }
    }
    printf("Runtime error: array access error\n");
    return 0;
}

void declare_array(char *name, int size){
    strcpy(symtab[symcount].name,name);
    symtab[symcount].is_array=1;
    symtab[symcount].dimensions=1;
    symtab[symcount].array_size=size;
    symtab[symcount].type = current_decl_type;
    for(int i=0;i<size;i++){
        symtab[symcount].array_values[i]=0;
    }
    symcount++;
}

double get_symbol(char *name){
    for(int i=0;i<symcount;i++){
        if(strcmp(symtab[i].name,name)==0)
            return symtab[i].value;
    }
    printf("Runtime error: variable %s not declared\n",name);
    return 0;
}


#line 222 "parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INCLUDE = 3,                    /* INCLUDE  */
  YYSYMBOL_DEFINE = 4,                     /* DEFINE  */
  YYSYMBOL_HEADER = 5,                     /* HEADER  */
  YYSYMBOL_INT_TYPE = 6,                   /* INT_TYPE  */
  YYSYMBOL_FLOAT_TYPE = 7,                 /* FLOAT_TYPE  */
  YYSYMBOL_DOUBLE_TYPE = 8,                /* DOUBLE_TYPE  */
  YYSYMBOL_CHAR_TYPE = 9,                  /* CHAR_TYPE  */
  YYSYMBOL_BOOL_TYPE = 10,                 /* BOOL_TYPE  */
  YYSYMBOL_VOID_TYPE = 11,                 /* VOID_TYPE  */
  YYSYMBOL_LONG_TYPE = 12,                 /* LONG_TYPE  */
  YYSYMBOL_SHORT_TYPE = 13,                /* SHORT_TYPE  */
  YYSYMBOL_UNSIGNED_TYPE = 14,             /* UNSIGNED_TYPE  */
  YYSYMBOL_CONST = 15,                     /* CONST  */
  YYSYMBOL_STRUCT = 16,                    /* STRUCT  */
  YYSYMBOL_UNION = 17,                     /* UNION  */
  YYSYMBOL_TYPEDEF = 18,                   /* TYPEDEF  */
  YYSYMBOL_ENUM = 19,                      /* ENUM  */
  YYSYMBOL_IF = 20,                        /* IF  */
  YYSYMBOL_ELSE = 21,                      /* ELSE  */
  YYSYMBOL_ELSEIF = 22,                    /* ELSEIF  */
  YYSYMBOL_SWITCH = 23,                    /* SWITCH  */
  YYSYMBOL_CASE = 24,                      /* CASE  */
  YYSYMBOL_DEFAULT = 25,                   /* DEFAULT  */
  YYSYMBOL_FOR = 26,                       /* FOR  */
  YYSYMBOL_WHILE = 27,                     /* WHILE  */
  YYSYMBOL_DO = 28,                        /* DO  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 30,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 31,                    /* RETURN  */
  YYSYMBOL_MAIN = 32,                      /* MAIN  */
  YYSYMBOL_PRINT = 33,                     /* PRINT  */
  YYSYMBOL_SCAN = 34,                      /* SCAN  */
  YYSYMBOL_TRUE_LITERAL = 35,              /* TRUE_LITERAL  */
  YYSYMBOL_FALSE_LITERAL = 36,             /* FALSE_LITERAL  */
  YYSYMBOL_POW = 37,                       /* POW  */
  YYSYMBOL_SQRT = 38,                      /* SQRT  */
  YYSYMBOL_ABS = 39,                       /* ABS  */
  YYSYMBOL_FLOOR = 40,                     /* FLOOR  */
  YYSYMBOL_CEIL = 41,                      /* CEIL  */
  YYSYMBOL_EQ = 42,                        /* EQ  */
  YYSYMBOL_NEQ = 43,                       /* NEQ  */
  YYSYMBOL_GE = 44,                        /* GE  */
  YYSYMBOL_LE = 45,                        /* LE  */
  YYSYMBOL_GT = 46,                        /* GT  */
  YYSYMBOL_LT = 47,                        /* LT  */
  YYSYMBOL_AND = 48,                       /* AND  */
  YYSYMBOL_OR = 49,                        /* OR  */
  YYSYMBOL_NOT = 50,                       /* NOT  */
  YYSYMBOL_INC = 51,                       /* INC  */
  YYSYMBOL_DEC = 52,                       /* DEC  */
  YYSYMBOL_PLUS = 53,                      /* PLUS  */
  YYSYMBOL_MINUS = 54,                     /* MINUS  */
  YYSYMBOL_MUL = 55,                       /* MUL  */
  YYSYMBOL_DIV = 56,                       /* DIV  */
  YYSYMBOL_MOD = 57,                       /* MOD  */
  YYSYMBOL_ASSIGN = 58,                    /* ASSIGN  */
  YYSYMBOL_BIT_AND = 59,                   /* BIT_AND  */
  YYSYMBOL_BIT_OR = 60,                    /* BIT_OR  */
  YYSYMBOL_BIT_XOR = 61,                   /* BIT_XOR  */
  YYSYMBOL_BIT_NOT = 62,                   /* BIT_NOT  */
  YYSYMBOL_SHL = 63,                       /* SHL  */
  YYSYMBOL_SHR = 64,                       /* SHR  */
  YYSYMBOL_SEMI = 65,                      /* SEMI  */
  YYSYMBOL_COMMA = 66,                     /* COMMA  */
  YYSYMBOL_LPAREN = 67,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 68,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 69,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 70,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 71,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 72,                  /* RBRACKET  */
  YYSYMBOL_INT_LITERAL = 73,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 74,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 75,            /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 76,              /* CHAR_LITERAL  */
  YYSYMBOL_IDENTIFIER = 77,                /* IDENTIFIER  */
  YYSYMBOL_UNARY = 78,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 79,                  /* $accept  */
  YYSYMBOL_program = 80,                   /* program  */
  YYSYMBOL_preprocessor_list = 81,         /* preprocessor_list  */
  YYSYMBOL_preprocessor = 82,              /* preprocessor  */
  YYSYMBOL_main_function = 83,             /* main_function  */
  YYSYMBOL_statement_list = 84,            /* statement_list  */
  YYSYMBOL_statement = 85,                 /* statement  */
  YYSYMBOL_declaration = 86,               /* declaration  */
  YYSYMBOL_array_size = 87,                /* array_size  */
  YYSYMBOL_type = 88,                      /* type  */
  YYSYMBOL_identifier_list = 89,           /* identifier_list  */
  YYSYMBOL_assignment = 90,                /* assignment  */
  YYSYMBOL_array_assignment = 91,          /* array_assignment  */
  YYSYMBOL_expression = 92,                /* expression  */
  YYSYMBOL_term = 93,                      /* term  */
  YYSYMBOL_factor = 94,                    /* factor  */
  YYSYMBOL_primary = 95,                   /* primary  */
  YYSYMBOL_array_access = 96,              /* array_access  */
  YYSYMBOL_function_call = 97,             /* function_call  */
  YYSYMBOL_print_stmt = 98,                /* print_stmt  */
  YYSYMBOL_scan_stmt = 99,                 /* scan_stmt  */
  YYSYMBOL_if_stmt = 100,                  /* if_stmt  */
  YYSYMBOL_101_1 = 101,                    /* @1  */
  YYSYMBOL_else_part = 102,                /* else_part  */
  YYSYMBOL_103_2 = 103,                    /* $@2  */
  YYSYMBOL_condition = 104,                /* condition  */
  YYSYMBOL_loop_stmt = 105,                /* loop_stmt  */
  YYSYMBOL_return_stmt = 106               /* return_stmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   305

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  79
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  194

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   333


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   215,   215,   219,   220,   224,   225,   229,   233,   234,
     238,   239,   240,   241,   242,   243,   244,   245,   249,   251,
     253,   261,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   277,   279,   281,   283,   288,   293,   295,   302,   303,
     304,   305,   309,   310,   311,   312,   316,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   332,   334,   341,   343,
     345,   347,   349,   356,   365,   373,   380,   395,   409,   408,
     421,   420,   426,   432,   433,   434,   435,   436,   437,   443,
     448,   457
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INCLUDE", "DEFINE",
  "HEADER", "INT_TYPE", "FLOAT_TYPE", "DOUBLE_TYPE", "CHAR_TYPE",
  "BOOL_TYPE", "VOID_TYPE", "LONG_TYPE", "SHORT_TYPE", "UNSIGNED_TYPE",
  "CONST", "STRUCT", "UNION", "TYPEDEF", "ENUM", "IF", "ELSE", "ELSEIF",
  "SWITCH", "CASE", "DEFAULT", "FOR", "WHILE", "DO", "BREAK", "CONTINUE",
  "RETURN", "MAIN", "PRINT", "SCAN", "TRUE_LITERAL", "FALSE_LITERAL",
  "POW", "SQRT", "ABS", "FLOOR", "CEIL", "EQ", "NEQ", "GE", "LE", "GT",
  "LT", "AND", "OR", "NOT", "INC", "DEC", "PLUS", "MINUS", "MUL", "DIV",
  "MOD", "ASSIGN", "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT", "SHL", "SHR",
  "SEMI", "COMMA", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "INT_LITERAL", "FLOAT_LITERAL", "STRING_LITERAL",
  "CHAR_LITERAL", "IDENTIFIER", "UNARY", "$accept", "program",
  "preprocessor_list", "preprocessor", "main_function", "statement_list",
  "statement", "declaration", "array_size", "type", "identifier_list",
  "assignment", "array_assignment", "expression", "term", "factor",
  "primary", "array_access", "function_call", "print_stmt", "scan_stmt",
  "if_stmt", "@1", "else_part", "$@2", "condition", "loop_stmt",
  "return_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-126)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -126,    15,    10,  -126,    30,   -32,    -8,  -126,  -126,  -126,
      20,    36,  -126,    -6,  -126,    -4,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,    81,    83,    85,   220,    87,
      91,  -126,   -37,  -126,  -126,    34,    67,    92,  -126,  -126,
    -126,  -126,    96,   220,    99,   220,  -126,  -126,   110,   115,
     116,   119,   120,   228,   220,  -126,  -126,  -126,   117,    71,
     118,  -126,  -126,  -126,  -126,   208,   113,   220,   220,   -30,
     135,  -126,  -126,  -126,   151,   133,   144,   138,   139,   220,
     220,   220,   220,   220,   118,    38,   220,   228,   228,   228,
     228,   228,   140,    -7,    42,    52,    71,   -34,   220,   141,
     146,  -126,   220,   220,   220,   220,   220,   220,  -126,   220,
     152,     3,    44,    49,    60,    65,  -126,   -22,   118,   118,
    -126,  -126,  -126,   155,   157,   159,   160,   220,    51,    93,
      63,  -126,  -126,   154,    71,    71,    71,    71,    71,    71,
     162,   167,  -126,   220,  -126,  -126,  -126,  -126,   156,  -126,
    -126,  -126,  -126,   -10,   220,   220,   141,   -47,  -126,    99,
      74,    77,   220,   165,    71,    -5,  -126,  -126,   146,   129,
     170,  -126,  -126,    18,   174,   182,   169,   221,   181,  -126,
    -126,   220,   186,  -126,  -126,  -126,    71,  -126,   183,   158,
    -126,  -126,   203,  -126
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,     3,     2,     5,
       0,     0,     6,     0,     9,     0,    22,    23,    24,    25,
      26,    27,    28,    29,    30,     0,     0,     0,     0,     0,
       0,     7,     0,     8,    10,     0,     0,     0,    13,    14,
      15,    16,     0,     0,     0,     0,    50,    51,     0,     0,
       0,     0,     0,     0,     0,    48,    49,    52,    47,    81,
      41,    45,    46,    55,    54,     0,     0,     0,     0,    31,
       0,    11,    12,    17,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    40,     0,     0,     0,     0,     0,
       0,     0,     0,    47,     0,     0,    35,     0,     0,     0,
       0,    18,     0,     0,     0,     0,     0,     0,    68,     0,
       0,     0,     0,     0,     0,     0,    53,     0,    38,    39,
      42,    43,    44,     0,     0,     0,     0,     0,     0,    32,
      31,    33,    21,     0,    73,    74,    77,    78,    75,    76,
       0,     0,     9,     0,    59,    60,    61,    62,    56,    63,
      64,    65,    66,     0,     0,     0,     0,     0,     9,     0,
       0,     0,     0,     0,    36,     0,    34,    19,     0,     0,
       0,    79,    58,     0,     0,     0,     0,    72,     0,    57,
      67,     0,     0,    70,    69,     9,    37,    20,     0,     0,
       9,    80,     0,    71
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -126,  -126,  -126,  -126,  -126,  -125,  -126,  -126,    86,  -126,
     -88,   -43,  -126,   -28,   -41,    90,  -126,  -126,  -126,  -126,
    -126,  -126,  -126,  -126,  -126,   -20,  -126,  -126
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,     8,    15,    33,    34,   133,    35,
      70,    36,    37,    74,    60,    61,    62,    63,    64,    38,
      39,    40,   140,   184,   188,    75,    41,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    77,    16,    17,    18,    19,    20,    21,    22,    23,
      24,   131,    84,     4,     5,     3,    25,   160,   167,    87,
      88,    67,    26,    27,   168,    78,    85,    28,    98,    29,
      30,    87,    88,   169,    68,     9,    99,    94,   128,    96,
      97,   100,     6,    87,    88,    10,   118,   119,    87,    88,
     148,   111,   112,   113,   114,   115,    87,    88,   117,    11,
     189,   124,   163,    14,    86,   192,    31,   175,   166,   143,
     129,    87,    88,    32,   134,   135,   136,   137,   138,   139,
      16,    17,    18,    19,    20,    21,    22,    23,    24,   141,
     179,    87,    88,    12,    25,    87,    88,    87,    88,   153,
      26,    27,    87,    88,    13,    28,   116,    29,    30,   154,
     125,    69,   144,    87,    88,   161,   170,   145,    87,    88,
     126,    98,   155,   127,    87,    88,   164,   165,   146,    99,
      87,    88,    71,   147,   173,    16,    17,    18,    19,    20,
      21,    22,    23,    24,   171,   172,    87,    88,    43,    25,
      44,    32,    45,   186,    65,    26,    27,    72,    66,   156,
      28,    73,    29,    30,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    89,    90,    91,    76,    79,    25,   120,
     121,   122,    80,    81,    26,    27,    82,    83,    86,    28,
      95,    29,    30,   102,   103,   104,   105,   106,   107,   177,
     101,   108,    67,   109,    87,    88,    32,   110,   123,    16,
      17,    18,    19,    20,    21,    22,    23,    24,   130,   132,
     149,   142,   150,    25,   151,   152,   157,   162,   191,    26,
      27,   158,   159,   174,    28,    32,    29,    30,   178,   180,
     181,   182,   183,    46,    47,    48,    49,    50,    51,    52,
     185,   187,   190,     0,   176,    46,    47,    48,    49,    50,
      51,    52,    53,    46,    47,    48,    49,    50,    51,    52,
       0,     0,     0,   193,    53,    54,     0,     0,     0,     0,
      32,    55,    56,    92,    57,    93,     0,    54,     0,     0,
       0,     0,     0,    55,    56,    54,    57,    58,     0,     0,
       0,    55,    56,     0,    57,    58
};

static const yytype_int16 yycheck[] =
{
      28,    44,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    99,    53,     3,     4,     0,    20,   142,    65,    53,
      54,    58,    26,    27,    71,    45,    54,    31,    58,    33,
      34,    53,    54,   158,    71,     5,    66,    65,    72,    67,
      68,    71,    32,    53,    54,    77,    87,    88,    53,    54,
      72,    79,    80,    81,    82,    83,    53,    54,    86,    67,
     185,    68,    72,    69,    71,   190,    70,    72,   156,    66,
      98,    53,    54,    77,   102,   103,   104,   105,   106,   107,
       6,     7,     8,     9,    10,    11,    12,    13,    14,   109,
      72,    53,    54,    73,    20,    53,    54,    53,    54,   127,
      26,    27,    53,    54,    68,    31,    68,    33,    34,    58,
      68,    77,    68,    53,    54,   143,   159,    68,    53,    54,
      68,    58,    71,    71,    53,    54,   154,   155,    68,    66,
      53,    54,    65,    68,   162,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    70,    68,    53,    54,    67,    20,
      67,    77,    67,   181,    67,    26,    27,    65,    67,    66,
      31,    65,    33,    34,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    55,    56,    57,    77,    67,    20,    89,
      90,    91,    67,    67,    26,    27,    67,    67,    71,    31,
      77,    33,    34,    42,    43,    44,    45,    46,    47,    70,
      65,    68,    58,    65,    53,    54,    77,    68,    68,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    77,    73,
      65,    69,    65,    20,    65,    65,    72,    71,    70,    26,
      27,    69,    65,    68,    31,    77,    33,    34,    68,    65,
      58,    72,    21,    35,    36,    37,    38,    39,    40,    41,
      69,    65,    69,    -1,   168,    35,    36,    37,    38,    39,
      40,    41,    54,    35,    36,    37,    38,    39,    40,    41,
      -1,    -1,    -1,    70,    54,    67,    -1,    -1,    -1,    -1,
      77,    73,    74,    75,    76,    77,    -1,    67,    -1,    -1,
      -1,    -1,    -1,    73,    74,    67,    76,    77,    -1,    -1,
      -1,    73,    74,    -1,    76,    77
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    80,    81,     0,     3,     4,    32,    82,    83,     5,
      77,    67,    73,    68,    69,    84,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    20,    26,    27,    31,    33,
      34,    70,    77,    85,    86,    88,    90,    91,    98,    99,
     100,   105,   106,    67,    67,    67,    35,    36,    37,    38,
      39,    40,    41,    54,    67,    73,    74,    76,    77,    92,
      93,    94,    95,    96,    97,    67,    67,    58,    71,    77,
      89,    65,    65,    65,    92,   104,    77,    90,   104,    67,
      67,    67,    67,    67,    93,    92,    71,    53,    54,    55,
      56,    57,    75,    77,    92,    77,    92,    92,    58,    66,
      71,    65,    42,    43,    44,    45,    46,    47,    68,    65,
      68,    92,    92,    92,    92,    92,    68,    92,    93,    93,
      94,    94,    94,    68,    68,    68,    68,    71,    72,    92,
      77,    89,    73,    87,    92,    92,    92,    92,    92,    92,
     101,   104,    69,    66,    68,    68,    68,    68,    72,    65,
      65,    65,    65,    92,    58,    71,    66,    72,    69,    65,
      84,    92,    71,    72,    92,    92,    89,    65,    71,    84,
      90,    70,    68,    92,    68,    72,    87,    70,    68,    72,
      65,    58,    72,    21,   102,    69,    92,    65,   103,    84,
      69,    70,    84,    70
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    79,    80,    81,    81,    82,    82,    83,    84,    84,
      85,    85,    85,    85,    85,    85,    85,    85,    86,    86,
      86,    87,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    90,    91,    91,    92,    92,
      92,    92,    93,    93,    93,    93,    94,    95,    95,    95,
      95,    95,    95,    95,    95,    95,    96,    96,    97,    97,
      97,    97,    97,    98,    98,    98,    99,    99,   101,   100,
     103,   102,   102,   104,   104,   104,   104,   104,   104,   105,
     105,   106
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     3,     6,     2,     0,
       1,     2,     2,     1,     1,     1,     1,     2,     3,     6,
       9,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     5,     3,     6,     9,     3,     3,
       2,     1,     3,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     1,     4,     7,     6,     4,
       4,     4,     4,     5,     5,     5,     5,     8,     0,     9,
       0,     5,     0,     3,     3,     3,     3,     3,     3,     7,
      11,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 18: /* declaration: type identifier_list SEMI  */
#line 250 "parser.y"
        { /* handled in identifier_list actions */ }
#line 1470 "parser.tab.c"
    break;

  case 19: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET SEMI  */
#line 252 "parser.y"
        { if(execute_flag) declare_array((yyvsp[-4].sval),(yyvsp[-2].ival)); }
#line 1476 "parser.tab.c"
    break;

  case 20: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI  */
#line 254 "parser.y"
    { 
        if(execute_flag)
            declare_2d_array((yyvsp[-7].sval),(yyvsp[-5].ival),(yyvsp[-2].ival)); 
    }
#line 1485 "parser.tab.c"
    break;

  case 21: /* array_size: INT_LITERAL  */
#line 261 "parser.y"
                  { (yyval.ival)=(yyvsp[0].ival); }
#line 1491 "parser.tab.c"
    break;

  case 22: /* type: INT_TYPE  */
#line 265 "parser.y"
                        { current_decl_type = 0; }
#line 1497 "parser.tab.c"
    break;

  case 23: /* type: FLOAT_TYPE  */
#line 266 "parser.y"
                        { current_decl_type = 0; }
#line 1503 "parser.tab.c"
    break;

  case 24: /* type: DOUBLE_TYPE  */
#line 267 "parser.y"
                        { current_decl_type = 0; }
#line 1509 "parser.tab.c"
    break;

  case 25: /* type: CHAR_TYPE  */
#line 268 "parser.y"
                        { current_decl_type = 1; }
#line 1515 "parser.tab.c"
    break;

  case 26: /* type: BOOL_TYPE  */
#line 269 "parser.y"
                        { current_decl_type = 0; }
#line 1521 "parser.tab.c"
    break;

  case 27: /* type: VOID_TYPE  */
#line 270 "parser.y"
                        { current_decl_type = 0; }
#line 1527 "parser.tab.c"
    break;

  case 28: /* type: LONG_TYPE  */
#line 271 "parser.y"
                        { current_decl_type = 0; }
#line 1533 "parser.tab.c"
    break;

  case 29: /* type: SHORT_TYPE  */
#line 272 "parser.y"
                        { current_decl_type = 0; }
#line 1539 "parser.tab.c"
    break;

  case 30: /* type: UNSIGNED_TYPE  */
#line 273 "parser.y"
                        { current_decl_type = 0; }
#line 1545 "parser.tab.c"
    break;

  case 31: /* identifier_list: IDENTIFIER  */
#line 278 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[0].sval),0); }
#line 1551 "parser.tab.c"
    break;

  case 32: /* identifier_list: IDENTIFIER ASSIGN expression  */
#line 280 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[-2].sval),(yyvsp[0].dval)); }
#line 1557 "parser.tab.c"
    break;

  case 33: /* identifier_list: IDENTIFIER COMMA identifier_list  */
#line 282 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[-2].sval),0); }
#line 1563 "parser.tab.c"
    break;

  case 34: /* identifier_list: IDENTIFIER ASSIGN expression COMMA identifier_list  */
#line 284 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[-4].sval),(yyvsp[-2].dval)); }
#line 1569 "parser.tab.c"
    break;

  case 35: /* assignment: IDENTIFIER ASSIGN expression  */
#line 289 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[-2].sval),(yyvsp[0].dval)); }
#line 1575 "parser.tab.c"
    break;

  case 36: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression  */
#line 294 "parser.y"
        { if(execute_flag) set_array_element((yyvsp[-5].sval),(int)(yyvsp[-3].dval),(yyvsp[0].dval)); }
#line 1581 "parser.tab.c"
    break;

  case 37: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression  */
#line 296 "parser.y"
        { if(execute_flag) set_array2d_element((yyvsp[-8].sval),(int)(yyvsp[-6].dval),(int)(yyvsp[-3].dval),(yyvsp[0].dval)); }
#line 1587 "parser.tab.c"
    break;

  case 38: /* expression: expression PLUS term  */
#line 302 "parser.y"
                             { (yyval.dval)=(yyvsp[-2].dval)+(yyvsp[0].dval); }
#line 1593 "parser.tab.c"
    break;

  case 39: /* expression: expression MINUS term  */
#line 303 "parser.y"
                             { (yyval.dval)=(yyvsp[-2].dval)-(yyvsp[0].dval); }
#line 1599 "parser.tab.c"
    break;

  case 40: /* expression: MINUS term  */
#line 304 "parser.y"
                             { (yyval.dval)=-(yyvsp[0].dval); }
#line 1605 "parser.tab.c"
    break;

  case 41: /* expression: term  */
#line 305 "parser.y"
                             { (yyval.dval)=(yyvsp[0].dval); }
#line 1611 "parser.tab.c"
    break;

  case 42: /* term: term MUL factor  */
#line 309 "parser.y"
                        { (yyval.dval)=(yyvsp[-2].dval)*(yyvsp[0].dval); }
#line 1617 "parser.tab.c"
    break;

  case 43: /* term: term DIV factor  */
#line 310 "parser.y"
                        { if((yyvsp[0].dval)!=0) (yyval.dval)=(yyvsp[-2].dval)/(yyvsp[0].dval); else {yyerror("Division by zero"); (yyval.dval)=0;} }
#line 1623 "parser.tab.c"
    break;

  case 44: /* term: term MOD factor  */
#line 311 "parser.y"
                        { if((int)(yyvsp[0].dval)!=0) (yyval.dval)=(int)(yyvsp[-2].dval)%(int)(yyvsp[0].dval); else {yyerror("Modulo by zero"); (yyval.dval)=0;} }
#line 1629 "parser.tab.c"
    break;

  case 45: /* term: factor  */
#line 312 "parser.y"
                        { (yyval.dval)=(yyvsp[0].dval); }
#line 1635 "parser.tab.c"
    break;

  case 46: /* factor: primary  */
#line 316 "parser.y"
                        { (yyval.dval)=(yyvsp[0].dval); }
#line 1641 "parser.tab.c"
    break;

  case 47: /* primary: IDENTIFIER  */
#line 320 "parser.y"
                        { (yyval.dval)=get_symbol((yyvsp[0].sval)); }
#line 1647 "parser.tab.c"
    break;

  case 48: /* primary: INT_LITERAL  */
#line 321 "parser.y"
                        { (yyval.dval)=(yyvsp[0].ival); }
#line 1653 "parser.tab.c"
    break;

  case 49: /* primary: FLOAT_LITERAL  */
#line 322 "parser.y"
                        { (yyval.dval)=(yyvsp[0].fval); }
#line 1659 "parser.tab.c"
    break;

  case 50: /* primary: TRUE_LITERAL  */
#line 323 "parser.y"
                        { (yyval.dval)=1; }
#line 1665 "parser.tab.c"
    break;

  case 51: /* primary: FALSE_LITERAL  */
#line 324 "parser.y"
                        { (yyval.dval)=0; }
#line 1671 "parser.tab.c"
    break;

  case 52: /* primary: CHAR_LITERAL  */
#line 325 "parser.y"
                        { (yyval.dval) = (yyvsp[0].cval); }
#line 1677 "parser.tab.c"
    break;

  case 53: /* primary: LPAREN expression RPAREN  */
#line 326 "parser.y"
                               { (yyval.dval)=(yyvsp[-1].dval); }
#line 1683 "parser.tab.c"
    break;

  case 54: /* primary: function_call  */
#line 327 "parser.y"
                        { (yyval.dval)=(yyvsp[0].dval); }
#line 1689 "parser.tab.c"
    break;

  case 55: /* primary: array_access  */
#line 328 "parser.y"
                        { (yyval.dval)=(yyvsp[0].dval); }
#line 1695 "parser.tab.c"
    break;

  case 56: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 333 "parser.y"
        { (yyval.dval)=get_array_element((yyvsp[-3].sval),(int)(yyvsp[-1].dval)); }
#line 1701 "parser.tab.c"
    break;

  case 57: /* array_access: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET  */
#line 335 "parser.y"
        { (yyval.dval) = get_array2d_element((yyvsp[-6].sval),(int)(yyvsp[-4].dval),(int)(yyvsp[-1].dval)); }
#line 1707 "parser.tab.c"
    break;

  case 58: /* function_call: POW LPAREN expression COMMA expression RPAREN  */
#line 342 "parser.y"
        { (yyval.dval)=pow((yyvsp[-3].dval),(yyvsp[-1].dval)); }
#line 1713 "parser.tab.c"
    break;

  case 59: /* function_call: SQRT LPAREN expression RPAREN  */
#line 344 "parser.y"
        { (yyval.dval)=sqrt((yyvsp[-1].dval)); }
#line 1719 "parser.tab.c"
    break;

  case 60: /* function_call: ABS LPAREN expression RPAREN  */
#line 346 "parser.y"
        { (yyval.dval)=fabs((yyvsp[-1].dval)); }
#line 1725 "parser.tab.c"
    break;

  case 61: /* function_call: FLOOR LPAREN expression RPAREN  */
#line 348 "parser.y"
        { (yyval.dval)=floor((yyvsp[-1].dval)); }
#line 1731 "parser.tab.c"
    break;

  case 62: /* function_call: CEIL LPAREN expression RPAREN  */
#line 350 "parser.y"
        { (yyval.dval)=ceil((yyvsp[-1].dval)); }
#line 1737 "parser.tab.c"
    break;

  case 63: /* print_stmt: PRINT LPAREN STRING_LITERAL RPAREN SEMI  */
#line 357 "parser.y"
        { if(execute_flag) { 
            char *s = (yyvsp[-2].sval);
            if(s[0]=='"') s++;
            int len = strlen(s);
            if(len>0 && s[len-1]=='"') s[len-1]='\0';
            printf("%s\n",s); 
          }
        }
#line 1750 "parser.tab.c"
    break;

  case 64: /* print_stmt: PRINT LPAREN IDENTIFIER RPAREN SEMI  */
#line 366 "parser.y"
        { if(execute_flag) {
            int t = get_symbol_type((yyvsp[-2].sval));
            double v = get_symbol((yyvsp[-2].sval));
            if(t == 1) printf("%c\n", (int)v);
            else printf("%g\n", v);
          }
        }
#line 1762 "parser.tab.c"
    break;

  case 65: /* print_stmt: PRINT LPAREN expression RPAREN SEMI  */
#line 374 "parser.y"
        { if(execute_flag) printf("%g\n",(yyvsp[-2].dval)); }
#line 1768 "parser.tab.c"
    break;

  case 66: /* scan_stmt: SCAN LPAREN IDENTIFIER RPAREN SEMI  */
#line 381 "parser.y"
        {
            if(execute_flag) {
                int t = get_symbol_type((yyvsp[-2].sval));
                if(t == 1) { /* char */
                    char v;
                    scanf(" %c", &v);
                    set_symbol((yyvsp[-2].sval), (double)v);
                } else {
                    double v;
                    scanf("%lf",&v);
                    set_symbol((yyvsp[-2].sval),v);
                }
            }
        }
#line 1787 "parser.tab.c"
    break;

  case 67: /* scan_stmt: SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI  */
#line 396 "parser.y"
        {
            if(execute_flag) {
                double v;
                scanf("%lf",&v);
                set_array_element((yyvsp[-5].sval),(int)(yyvsp[-3].dval),v);
            }
        }
#line 1799 "parser.tab.c"
    break;

  case 68: /* @1: %empty  */
#line 409 "parser.y"
        { 
            (yyval.ival) = execute_flag;
            if(!((yyvsp[-1].dval))) execute_flag = 0; 
        }
#line 1808 "parser.tab.c"
    break;

  case 69: /* if_stmt: IF LPAREN condition RPAREN @1 LBRACE statement_list RBRACE else_part  */
#line 414 "parser.y"
        { 
            execute_flag = (yyvsp[-4].ival); 
        }
#line 1816 "parser.tab.c"
    break;

  case 70: /* $@2: %empty  */
#line 421 "parser.y"
        { 
            if(execute_flag == 0) execute_flag = 1;
            else execute_flag = 0;
        }
#line 1825 "parser.tab.c"
    break;

  case 73: /* condition: expression EQ expression  */
#line 432 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)==(yyvsp[0].dval); }
#line 1831 "parser.tab.c"
    break;

  case 74: /* condition: expression NEQ expression  */
#line 433 "parser.y"
                                { (yyval.dval)=(yyvsp[-2].dval)!=(yyvsp[0].dval); }
#line 1837 "parser.tab.c"
    break;

  case 75: /* condition: expression GT expression  */
#line 434 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)>(yyvsp[0].dval); }
#line 1843 "parser.tab.c"
    break;

  case 76: /* condition: expression LT expression  */
#line 435 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)<(yyvsp[0].dval); }
#line 1849 "parser.tab.c"
    break;

  case 77: /* condition: expression GE expression  */
#line 436 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)>=(yyvsp[0].dval); }
#line 1855 "parser.tab.c"
    break;

  case 78: /* condition: expression LE expression  */
#line 437 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)<=(yyvsp[0].dval); }
#line 1861 "parser.tab.c"
    break;

  case 79: /* loop_stmt: WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE  */
#line 444 "parser.y"
        { 
            /* Note: Due to parser limitations, loops execute once per parse.
               For proper loop execution, use the for-loop pattern with arrays. */
        }
#line 1870 "parser.tab.c"
    break;

  case 80: /* loop_stmt: FOR LPAREN assignment SEMI condition SEMI assignment RPAREN LBRACE statement_list RBRACE  */
#line 450 "parser.y"
        { 
            /* Note: Due to parser limitations, loops execute once per parse.
               For proper loop execution, process arrays with multiple statements. */
        }
#line 1879 "parser.tab.c"
    break;

  case 81: /* return_stmt: RETURN expression  */
#line 458 "parser.y"
        { if(execute_flag) printf("Program returned: %g\n",(yyvsp[0].dval)); }
#line 1885 "parser.tab.c"
    break;


#line 1889 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 461 "parser.y"


void yyerror(const char *s){
    printf("Syntax Error at line %d: %s\n",yylineno,s);
}

extern FILE *yyin;

int main(int argc, char *argv[]){
    char *filename = (argc > 1) ? argv[1] : "input.txt";
    FILE *fp=fopen(filename,"r");

    if(!fp){
        printf("Cannot open input file: %s\n", filename);
        return 1;
    }

    yyin=fp;

    printf("Running Luminix Program...\n\n");

    yyparse();

    printf("\nProgram finished.\n");

    return 0;
}


