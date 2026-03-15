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

#define SWITCH_STACK_MAX 64
#define SWITCH_EPSILON 1e-9
typedef struct {
    double value;       /* the switch expression value          */
    int matched;     /* 1 = a case has already matched       */
    int done;        /* 1 = break was hit, skip rest         */
    int outer_exec;  /* saved execute_flag before this switch */
} SwitchFrame;

SwitchFrame switch_stack[SWITCH_STACK_MAX];
int switch_top = -1;   /* index of current (innermost) frame  */

int break_flag = 0;    /* set by break; cleared after use     */
/* helpers */
void switch_push(double val, int outer_exec) {
    if (switch_top + 1 >= SWITCH_STACK_MAX) {
        fprintf(stderr, "Runtime error: switch nesting too deep\n");
        return;
    }
    switch_top++;
    switch_stack[switch_top].value      = val;
    switch_stack[switch_top].matched    = 0;
    switch_stack[switch_top].done       = 0;
    switch_stack[switch_top].outer_exec = outer_exec;
}

void switch_pop(void) {
    if (switch_top < 0) {
        fprintf(stderr, "Runtime error: switch stack underflow\n");
        return;
    }
    switch_top--;
}

SwitchFrame *switch_cur(void) {
    /* returns pointer to innermost active switch frame */
    if (switch_top < 0) return NULL;
    return &switch_stack[switch_top];
}

int sw_match(double a, double b) {
    return fabs(a - b) < SWITCH_EPSILON;
}

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


#line 266 "parser.tab.c"

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
  YYSYMBOL_COLON = 67,                     /* COLON  */
  YYSYMBOL_LPAREN = 68,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 69,                    /* RPAREN  */
  YYSYMBOL_LBRACE = 70,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 71,                    /* RBRACE  */
  YYSYMBOL_LBRACKET = 72,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 73,                  /* RBRACKET  */
  YYSYMBOL_RANGE = 74,                     /* RANGE  */
  YYSYMBOL_INT_LITERAL = 75,               /* INT_LITERAL  */
  YYSYMBOL_FLOAT_LITERAL = 76,             /* FLOAT_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 77,            /* STRING_LITERAL  */
  YYSYMBOL_CHAR_LITERAL = 78,              /* CHAR_LITERAL  */
  YYSYMBOL_IDENTIFIER = 79,                /* IDENTIFIER  */
  YYSYMBOL_UNARY = 80,                     /* UNARY  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_program = 82,                   /* program  */
  YYSYMBOL_preprocessor_list = 83,         /* preprocessor_list  */
  YYSYMBOL_preprocessor = 84,              /* preprocessor  */
  YYSYMBOL_main_function = 85,             /* main_function  */
  YYSYMBOL_statement_list = 86,            /* statement_list  */
  YYSYMBOL_statement = 87,                 /* statement  */
  YYSYMBOL_declaration = 88,               /* declaration  */
  YYSYMBOL_array_size = 89,                /* array_size  */
  YYSYMBOL_type = 90,                      /* type  */
  YYSYMBOL_identifier_list = 91,           /* identifier_list  */
  YYSYMBOL_assignment = 92,                /* assignment  */
  YYSYMBOL_array_assignment = 93,          /* array_assignment  */
  YYSYMBOL_expression = 94,                /* expression  */
  YYSYMBOL_term = 95,                      /* term  */
  YYSYMBOL_factor = 96,                    /* factor  */
  YYSYMBOL_primary = 97,                   /* primary  */
  YYSYMBOL_array_access = 98,              /* array_access  */
  YYSYMBOL_function_call = 99,             /* function_call  */
  YYSYMBOL_print_stmt = 100,               /* print_stmt  */
  YYSYMBOL_scan_stmt = 101,                /* scan_stmt  */
  YYSYMBOL_if_stmt = 102,                  /* if_stmt  */
  YYSYMBOL_103_1 = 103,                    /* @1  */
  YYSYMBOL_104_2 = 104,                    /* $@2  */
  YYSYMBOL_else_if_part = 105,             /* else_if_part  */
  YYSYMBOL_106_3 = 106,                    /* @3  */
  YYSYMBOL_107_4 = 107,                    /* $@4  */
  YYSYMBOL_switch_stmt = 108,              /* switch_stmt  */
  YYSYMBOL_109_5 = 109,                    /* $@5  */
  YYSYMBOL_case_list = 110,                /* case_list  */
  YYSYMBOL_case_item = 111,                /* case_item  */
  YYSYMBOL_112_6 = 112,                    /* $@6  */
  YYSYMBOL_case_expr = 113,                /* case_expr  */
  YYSYMBOL_default_item = 114,             /* default_item  */
  YYSYMBOL_115_7 = 115,                    /* $@7  */
  YYSYMBOL_condition = 116,                /* condition  */
  YYSYMBOL_loop_stmt = 117,                /* loop_stmt  */
  YYSYMBOL_return_stmt = 118               /* return_stmt  */
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
#define YYLAST   450

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  229

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   335


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
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   261,   261,   265,   266,   270,   271,   275,   279,   280,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     297,   299,   301,   309,   313,   314,   315,   316,   317,   318,
     319,   320,   321,   325,   327,   329,   331,   336,   341,   343,
     350,   351,   352,   353,   357,   358,   359,   360,   364,   368,
     369,   370,   371,   372,   373,   374,   375,   376,   380,   382,
     389,   391,   393,   395,   397,   404,   413,   421,   428,   443,
     457,   468,   456,   487,   499,   486,   512,   513,   520,   519,
     550,   551,   552,   557,   556,   572,   589,   617,   616,   647,
     648,   649,   650,   651,   652,   658,   663,   672
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
  "SEMI", "COMMA", "COLON", "LPAREN", "RPAREN", "LBRACE", "RBRACE",
  "LBRACKET", "RBRACKET", "RANGE", "INT_LITERAL", "FLOAT_LITERAL",
  "STRING_LITERAL", "CHAR_LITERAL", "IDENTIFIER", "UNARY", "$accept",
  "program", "preprocessor_list", "preprocessor", "main_function",
  "statement_list", "statement", "declaration", "array_size", "type",
  "identifier_list", "assignment", "array_assignment", "expression",
  "term", "factor", "primary", "array_access", "function_call",
  "print_stmt", "scan_stmt", "if_stmt", "@1", "$@2", "else_if_part", "@3",
  "$@4", "switch_stmt", "$@5", "case_list", "case_item", "$@6",
  "case_expr", "default_item", "$@7", "condition", "loop_stmt",
  "return_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-140)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -140,     8,     3,  -140,     5,   -56,    -8,  -140,  -140,  -140,
     -10,   -43,  -140,    -3,  -140,    80,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,     4,     7,     9,    27,    34,
     362,    40,    42,  -140,   -33,  -140,  -140,    41,    84,    85,
    -140,  -140,  -140,  -140,  -140,    95,   362,   362,    59,   362,
    -140,  -140,  -140,    93,    94,   108,   109,   112,   371,   362,
    -140,  -140,  -140,   107,    76,    88,  -140,  -140,  -140,  -140,
     350,   103,   362,   362,   -42,   118,  -140,  -140,  -140,   110,
     116,   -17,   128,   124,   122,   362,   362,   362,   362,   362,
      88,     0,   362,   371,   371,   371,   371,   371,   136,    56,
      43,    68,    76,   -39,   362,   114,   134,  -140,   362,   362,
     362,   362,   362,   362,  -140,  -140,   362,   141,    -5,    48,
      62,    65,    70,  -140,   -35,    88,    88,  -140,  -140,  -140,
     147,   149,   150,   153,   362,    12,    82,   -38,  -140,  -140,
     152,    76,    76,    76,    76,    76,    76,   156,   157,   155,
    -140,   362,  -140,  -140,  -140,  -140,   158,  -140,  -140,  -140,
    -140,   -32,   362,   362,   114,    33,  -140,  -140,    59,   161,
      73,   362,   159,    76,   -22,  -140,  -140,   134,   190,   -21,
     160,  -140,  -140,    -7,   166,   164,   162,  -140,   362,   167,
    -140,  -140,  -140,   163,  -140,  -140,   362,   171,   125,   -41,
     170,  -140,  -140,    76,  -140,   168,   173,  -140,   362,  -140,
    -140,   237,  -140,   362,    76,  -140,   342,  -140,   266,   183,
     342,  -140,  -140,   169,  -140,   313,  -140,   125,  -140
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     1,     0,     0,     0,     3,     2,     5,
       0,     0,     6,     0,     9,     0,    24,    25,    26,    27,
      28,    29,    30,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     0,     8,    10,     0,     0,     0,
      13,    14,    15,    16,    18,     0,     0,     0,     0,     0,
      17,    52,    53,     0,     0,     0,     0,     0,     0,     0,
      50,    51,    54,    49,    97,    43,    47,    48,    57,    56,
       0,     0,     0,     0,    33,     0,    11,    12,    19,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,     0,    37,     0,     0,     0,     0,    20,     0,     0,
       0,     0,     0,     0,    70,    78,     0,     0,     0,     0,
       0,     0,     0,    55,     0,    40,    41,    44,    45,    46,
       0,     0,     0,     0,     0,     0,    34,    33,    35,    23,
       0,    89,    90,    93,    94,    91,    92,     0,     0,     0,
       9,     0,    61,    62,    63,    64,    58,    65,    66,    67,
      68,     0,     0,     0,     0,     0,     9,    82,     0,     0,
       0,     0,     0,    38,     0,    36,    21,     0,     0,     0,
       0,    95,    60,     0,     0,     0,     0,    71,     0,     0,
      79,    80,    81,     0,    59,    69,     0,     0,    77,    85,
       0,    87,     9,    39,    22,     0,     0,    72,     0,    83,
       9,     0,     9,     0,    86,     9,    88,    96,     0,     0,
      84,    76,    73,     0,     9,     0,    74,    77,    75
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,  -140,  -140,  -140,  -139,  -140,  -140,    77,  -140,
    -100,   -46,  -140,   -30,   -49,   111,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,    15,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,   -48,  -140,  -140
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     7,     8,    15,    35,    36,   140,    37,
      75,    38,    39,    79,    65,    66,    67,    68,    69,    40,
      41,    42,   147,   198,   207,   223,   227,    43,   148,   179,
     191,   215,   200,   192,   210,    80,    44,    45
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      64,    84,    83,   188,   189,   138,     4,     5,     3,    90,
       9,   169,    93,    94,    93,    94,   104,    81,    93,    94,
     104,    93,    94,    10,   105,    72,    13,   178,   105,    91,
     106,    93,    94,   208,   135,     6,    93,    94,   156,    73,
     100,   172,   102,   103,   125,   126,    93,    94,    93,    94,
     190,   185,   115,    93,    94,   118,   119,   120,   121,   122,
      11,   151,   124,   211,   175,    12,   194,    14,   149,   123,
     162,   216,    46,   218,   136,    47,   220,    48,   141,   142,
     143,   144,   145,   146,   163,   225,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    49,    93,    94,   176,    50,
      25,    93,    94,    26,   161,   177,    27,    28,    70,    29,
      71,    30,   132,    31,    32,    93,    94,   152,    93,    94,
      74,   170,   180,    93,    94,   131,    93,    94,    92,    93,
      94,   153,   173,   174,   154,    93,    94,   133,    82,   155,
     134,   183,   182,    95,    96,    97,   205,   206,   164,    76,
      77,    33,   108,   109,   110,   111,   112,   113,   199,    34,
      78,    85,    86,    93,    94,   219,   203,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    87,    88,   214,    92,
      89,    25,   101,   107,    26,   114,    72,    27,    28,   116,
      29,   117,    30,   137,    31,    32,    16,    17,    18,    19,
      20,    21,    22,    23,    24,   130,   127,   128,   129,   139,
      25,   150,   157,    26,   158,   159,    27,    28,   160,    29,
     168,    30,   196,    31,    32,   165,   166,   167,   184,   193,
     171,   195,   181,   202,   201,   197,   204,   209,   212,   224,
      34,   213,   228,    16,    17,    18,    19,    20,    21,    22,
      23,    24,   222,     0,   186,     0,     0,    25,     0,     0,
      26,   187,     0,    27,    28,     0,    29,     0,    30,    34,
      31,    32,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,     0,     0,     0,     0,    25,     0,     0,    26,
       0,     0,    27,    28,     0,    29,     0,    30,     0,    31,
      32,     0,     0,     0,     0,     0,     0,     0,   217,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     0,     0,
       0,     0,     0,    25,     0,     0,    26,   221,     0,    27,
      28,     0,    29,     0,    30,    34,    31,    32,    16,    17,
      18,    19,    20,    21,    22,    23,    24,     0,     0,     0,
       0,     0,    25,     0,     0,    26,     0,     0,    27,    28,
       0,    29,     0,    30,     0,    31,    32,     0,     0,     0,
       0,     0,     0,     0,   226,    51,    52,    53,    54,    55,
      56,    57,    34,     0,     0,     0,     0,    51,    52,    53,
      54,    55,    56,    57,    58,     0,    51,    52,    53,    54,
      55,    56,    57,     0,     0,     0,    58,     0,    59,     0,
       0,    34,     0,     0,     0,    60,    61,    98,    62,    99,
      59,     0,     0,     0,     0,     0,     0,    60,    61,    59,
      62,    63,     0,     0,     0,     0,    60,    61,     0,    62,
      63
};

static const yytype_int16 yycheck[] =
{
      30,    49,    48,    24,    25,   105,     3,     4,     0,    58,
       5,   150,    53,    54,    53,    54,    58,    47,    53,    54,
      58,    53,    54,    79,    66,    58,    69,   166,    66,    59,
      72,    53,    54,    74,    73,    32,    53,    54,    73,    72,
      70,    73,    72,    73,    93,    94,    53,    54,    53,    54,
      71,    73,    69,    53,    54,    85,    86,    87,    88,    89,
      68,    66,    92,   202,   164,    75,    73,    70,   116,    69,
      58,   210,    68,   212,   104,    68,   215,    68,   108,   109,
     110,   111,   112,   113,    72,   224,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    68,    53,    54,    65,    65,
      20,    53,    54,    23,   134,    72,    26,    27,    68,    29,
      68,    31,    69,    33,    34,    53,    54,    69,    53,    54,
      79,   151,   168,    53,    54,    69,    53,    54,    72,    53,
      54,    69,   162,   163,    69,    53,    54,    69,    79,    69,
      72,   171,    69,    55,    56,    57,    21,    22,    66,    65,
      65,    71,    42,    43,    44,    45,    46,    47,   188,    79,
      65,    68,    68,    53,    54,   213,   196,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    68,    68,   208,    72,
      68,    20,    79,    65,    23,    69,    58,    26,    27,    65,
      29,    69,    31,    79,    33,    34,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    69,    95,    96,    97,    75,
      20,    70,    65,    23,    65,    65,    26,    27,    65,    29,
      65,    31,    58,    33,    34,    73,    70,    70,    69,    69,
      72,    65,    71,    70,    67,    73,    65,    67,    70,    70,
      79,    68,   227,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    69,    -1,   177,    -1,    -1,    20,    -1,    -1,
      23,    71,    -1,    26,    27,    -1,    29,    -1,    31,    79,
      33,    34,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    23,
      -1,    -1,    26,    27,    -1,    29,    -1,    31,    -1,    33,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    -1,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    -1,    -1,
      -1,    -1,    -1,    20,    -1,    -1,    23,    71,    -1,    26,
      27,    -1,    29,    -1,    31,    79,    33,    34,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    -1,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    23,    -1,    -1,    26,    27,
      -1,    29,    -1,    31,    -1,    33,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    35,    36,    37,    38,    39,
      40,    41,    79,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    39,    40,    41,    54,    -1,    35,    36,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    54,    -1,    68,    -1,
      -1,    79,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    68,
      78,    79,    -1,    -1,    -1,    -1,    75,    76,    -1,    78,
      79
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    82,    83,     0,     3,     4,    32,    84,    85,     5,
      79,    68,    75,    69,    70,    86,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    20,    23,    26,    27,    29,
      31,    33,    34,    71,    79,    87,    88,    90,    92,    93,
     100,   101,   102,   108,   117,   118,    68,    68,    68,    68,
      65,    35,    36,    37,    38,    39,    40,    41,    54,    68,
      75,    76,    78,    79,    94,    95,    96,    97,    98,    99,
      68,    68,    58,    72,    79,    91,    65,    65,    65,    94,
     116,    94,    79,    92,   116,    68,    68,    68,    68,    68,
      95,    94,    72,    53,    54,    55,    56,    57,    77,    79,
      94,    79,    94,    94,    58,    66,    72,    65,    42,    43,
      44,    45,    46,    47,    69,    69,    65,    69,    94,    94,
      94,    94,    94,    69,    94,    95,    95,    96,    96,    96,
      69,    69,    69,    69,    72,    73,    94,    79,    91,    75,
      89,    94,    94,    94,    94,    94,    94,   103,   109,   116,
      70,    66,    69,    69,    69,    69,    73,    65,    65,    65,
      65,    94,    58,    72,    66,    73,    70,    70,    65,    86,
      94,    72,    73,    94,    94,    91,    65,    72,    86,   110,
      92,    71,    69,    94,    69,    73,    89,    71,    24,    25,
      71,   111,   114,    69,    73,    65,    58,    73,   104,    94,
     113,    67,    70,    94,    65,    21,    22,   105,    74,    67,
     115,    86,    70,    68,    94,   112,    86,    71,    86,   116,
      86,    71,    69,   106,    70,    86,    71,   107,   105
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      88,    88,    88,    89,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    91,    91,    91,    91,    92,    93,    93,
      94,    94,    94,    94,    95,    95,    95,    95,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    98,    98,
      99,    99,    99,    99,    99,   100,   100,   100,   101,   101,
     103,   104,   102,   106,   107,   105,   105,   105,   109,   108,
     110,   110,   110,   112,   111,   113,   113,   115,   114,   116,
     116,   116,   116,   116,   116,   117,   117,   118
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     2,     3,     6,     2,     0,
       1,     2,     2,     1,     1,     1,     1,     2,     1,     2,
       3,     6,     9,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     5,     3,     6,     9,
       3,     3,     2,     1,     3,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     4,     7,
       6,     4,     4,     4,     4,     5,     5,     5,     5,     8,
       0,     0,    10,     0,     0,    10,     4,     0,     0,     8,
       2,     2,     0,     0,     5,     1,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     7,    11,     2
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
  case 17: /* statement: BREAK SEMI  */
#line 291 "parser.y"
                  { if(execute_flag) break_flag = 1; }
#line 1572 "parser.tab.c"
    break;

  case 20: /* declaration: type identifier_list SEMI  */
#line 298 "parser.y"
        { /* handled in identifier_list actions */ }
#line 1578 "parser.tab.c"
    break;

  case 21: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET SEMI  */
#line 300 "parser.y"
        { if(execute_flag) declare_array((yyvsp[-4].sval),(yyvsp[-2].ival)); }
#line 1584 "parser.tab.c"
    break;

  case 22: /* declaration: type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI  */
#line 302 "parser.y"
    { 
        if(execute_flag)
            declare_2d_array((yyvsp[-7].sval),(yyvsp[-5].ival),(yyvsp[-2].ival)); 
    }
#line 1593 "parser.tab.c"
    break;

  case 23: /* array_size: INT_LITERAL  */
#line 309 "parser.y"
                  { (yyval.ival)=(yyvsp[0].ival); }
#line 1599 "parser.tab.c"
    break;

  case 24: /* type: INT_TYPE  */
#line 313 "parser.y"
                        { current_decl_type = 0; }
#line 1605 "parser.tab.c"
    break;

  case 25: /* type: FLOAT_TYPE  */
#line 314 "parser.y"
                        { current_decl_type = 0; }
#line 1611 "parser.tab.c"
    break;

  case 26: /* type: DOUBLE_TYPE  */
#line 315 "parser.y"
                        { current_decl_type = 0; }
#line 1617 "parser.tab.c"
    break;

  case 27: /* type: CHAR_TYPE  */
#line 316 "parser.y"
                        { current_decl_type = 1; }
#line 1623 "parser.tab.c"
    break;

  case 28: /* type: BOOL_TYPE  */
#line 317 "parser.y"
                        { current_decl_type = 0; }
#line 1629 "parser.tab.c"
    break;

  case 29: /* type: VOID_TYPE  */
#line 318 "parser.y"
                        { current_decl_type = 0; }
#line 1635 "parser.tab.c"
    break;

  case 30: /* type: LONG_TYPE  */
#line 319 "parser.y"
                        { current_decl_type = 0; }
#line 1641 "parser.tab.c"
    break;

  case 31: /* type: SHORT_TYPE  */
#line 320 "parser.y"
                        { current_decl_type = 0; }
#line 1647 "parser.tab.c"
    break;

  case 32: /* type: UNSIGNED_TYPE  */
#line 321 "parser.y"
                        { current_decl_type = 0; }
#line 1653 "parser.tab.c"
    break;

  case 33: /* identifier_list: IDENTIFIER  */
#line 326 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[0].sval),0); }
#line 1659 "parser.tab.c"
    break;

  case 34: /* identifier_list: IDENTIFIER ASSIGN expression  */
#line 328 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[-2].sval),(yyvsp[0].dval)); }
#line 1665 "parser.tab.c"
    break;

  case 35: /* identifier_list: IDENTIFIER COMMA identifier_list  */
#line 330 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[-2].sval),0); }
#line 1671 "parser.tab.c"
    break;

  case 36: /* identifier_list: IDENTIFIER ASSIGN expression COMMA identifier_list  */
#line 332 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[-4].sval),(yyvsp[-2].dval)); }
#line 1677 "parser.tab.c"
    break;

  case 37: /* assignment: IDENTIFIER ASSIGN expression  */
#line 337 "parser.y"
        { if(execute_flag) set_symbol((yyvsp[-2].sval),(yyvsp[0].dval)); }
#line 1683 "parser.tab.c"
    break;

  case 38: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression  */
#line 342 "parser.y"
        { if(execute_flag) set_array_element((yyvsp[-5].sval),(int)(yyvsp[-3].dval),(yyvsp[0].dval)); }
#line 1689 "parser.tab.c"
    break;

  case 39: /* array_assignment: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression  */
#line 344 "parser.y"
        { if(execute_flag) set_array2d_element((yyvsp[-8].sval),(int)(yyvsp[-6].dval),(int)(yyvsp[-3].dval),(yyvsp[0].dval)); }
#line 1695 "parser.tab.c"
    break;

  case 40: /* expression: expression PLUS term  */
#line 350 "parser.y"
                             { (yyval.dval)=(yyvsp[-2].dval)+(yyvsp[0].dval); }
#line 1701 "parser.tab.c"
    break;

  case 41: /* expression: expression MINUS term  */
#line 351 "parser.y"
                             { (yyval.dval)=(yyvsp[-2].dval)-(yyvsp[0].dval); }
#line 1707 "parser.tab.c"
    break;

  case 42: /* expression: MINUS term  */
#line 352 "parser.y"
                             { (yyval.dval)=-(yyvsp[0].dval); }
#line 1713 "parser.tab.c"
    break;

  case 43: /* expression: term  */
#line 353 "parser.y"
                             { (yyval.dval)=(yyvsp[0].dval); }
#line 1719 "parser.tab.c"
    break;

  case 44: /* term: term MUL factor  */
#line 357 "parser.y"
                        { (yyval.dval)=(yyvsp[-2].dval)*(yyvsp[0].dval); }
#line 1725 "parser.tab.c"
    break;

  case 45: /* term: term DIV factor  */
#line 358 "parser.y"
                        { if((yyvsp[0].dval)!=0) (yyval.dval)=(yyvsp[-2].dval)/(yyvsp[0].dval); else {yyerror("Division by zero"); (yyval.dval)=0;} }
#line 1731 "parser.tab.c"
    break;

  case 46: /* term: term MOD factor  */
#line 359 "parser.y"
                        { if((int)(yyvsp[0].dval)!=0) (yyval.dval)=(int)(yyvsp[-2].dval)%(int)(yyvsp[0].dval); else {yyerror("Modulo by zero"); (yyval.dval)=0;} }
#line 1737 "parser.tab.c"
    break;

  case 47: /* term: factor  */
#line 360 "parser.y"
                        { (yyval.dval)=(yyvsp[0].dval); }
#line 1743 "parser.tab.c"
    break;

  case 48: /* factor: primary  */
#line 364 "parser.y"
                        { (yyval.dval)=(yyvsp[0].dval); }
#line 1749 "parser.tab.c"
    break;

  case 49: /* primary: IDENTIFIER  */
#line 368 "parser.y"
                        { (yyval.dval)=get_symbol((yyvsp[0].sval)); }
#line 1755 "parser.tab.c"
    break;

  case 50: /* primary: INT_LITERAL  */
#line 369 "parser.y"
                        { (yyval.dval)=(yyvsp[0].ival); }
#line 1761 "parser.tab.c"
    break;

  case 51: /* primary: FLOAT_LITERAL  */
#line 370 "parser.y"
                        { (yyval.dval)=(yyvsp[0].fval); }
#line 1767 "parser.tab.c"
    break;

  case 52: /* primary: TRUE_LITERAL  */
#line 371 "parser.y"
                        { (yyval.dval)=1; }
#line 1773 "parser.tab.c"
    break;

  case 53: /* primary: FALSE_LITERAL  */
#line 372 "parser.y"
                        { (yyval.dval)=0; }
#line 1779 "parser.tab.c"
    break;

  case 54: /* primary: CHAR_LITERAL  */
#line 373 "parser.y"
                        { (yyval.dval) = (yyvsp[0].cval); }
#line 1785 "parser.tab.c"
    break;

  case 55: /* primary: LPAREN expression RPAREN  */
#line 374 "parser.y"
                               { (yyval.dval)=(yyvsp[-1].dval); }
#line 1791 "parser.tab.c"
    break;

  case 56: /* primary: function_call  */
#line 375 "parser.y"
                        { (yyval.dval)=(yyvsp[0].dval); }
#line 1797 "parser.tab.c"
    break;

  case 57: /* primary: array_access  */
#line 376 "parser.y"
                        { (yyval.dval)=(yyvsp[0].dval); }
#line 1803 "parser.tab.c"
    break;

  case 58: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 381 "parser.y"
        { (yyval.dval)=get_array_element((yyvsp[-3].sval),(int)(yyvsp[-1].dval)); }
#line 1809 "parser.tab.c"
    break;

  case 59: /* array_access: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET  */
#line 383 "parser.y"
        { (yyval.dval) = get_array2d_element((yyvsp[-6].sval),(int)(yyvsp[-4].dval),(int)(yyvsp[-1].dval)); }
#line 1815 "parser.tab.c"
    break;

  case 60: /* function_call: POW LPAREN expression COMMA expression RPAREN  */
#line 390 "parser.y"
        { (yyval.dval)=pow((yyvsp[-3].dval),(yyvsp[-1].dval)); }
#line 1821 "parser.tab.c"
    break;

  case 61: /* function_call: SQRT LPAREN expression RPAREN  */
#line 392 "parser.y"
        { (yyval.dval)=sqrt((yyvsp[-1].dval)); }
#line 1827 "parser.tab.c"
    break;

  case 62: /* function_call: ABS LPAREN expression RPAREN  */
#line 394 "parser.y"
        { (yyval.dval)=fabs((yyvsp[-1].dval)); }
#line 1833 "parser.tab.c"
    break;

  case 63: /* function_call: FLOOR LPAREN expression RPAREN  */
#line 396 "parser.y"
        { (yyval.dval)=floor((yyvsp[-1].dval)); }
#line 1839 "parser.tab.c"
    break;

  case 64: /* function_call: CEIL LPAREN expression RPAREN  */
#line 398 "parser.y"
        { (yyval.dval)=ceil((yyvsp[-1].dval)); }
#line 1845 "parser.tab.c"
    break;

  case 65: /* print_stmt: PRINT LPAREN STRING_LITERAL RPAREN SEMI  */
#line 405 "parser.y"
        { if(execute_flag) { 
            char *s = (yyvsp[-2].sval);
            if(s[0]=='"') s++;
            int len = strlen(s);
            if(len>0 && s[len-1]=='"') s[len-1]='\0';
            printf("%s\n",s); 
          }
        }
#line 1858 "parser.tab.c"
    break;

  case 66: /* print_stmt: PRINT LPAREN IDENTIFIER RPAREN SEMI  */
#line 414 "parser.y"
        { if(execute_flag) {
            int t = get_symbol_type((yyvsp[-2].sval));
            double v = get_symbol((yyvsp[-2].sval));
            if(t == 1) printf("%c\n", (int)v);
            else printf("%g\n", v);
          }
        }
#line 1870 "parser.tab.c"
    break;

  case 67: /* print_stmt: PRINT LPAREN expression RPAREN SEMI  */
#line 422 "parser.y"
        { if(execute_flag) printf("%g\n",(yyvsp[-2].dval)); }
#line 1876 "parser.tab.c"
    break;

  case 68: /* scan_stmt: SCAN LPAREN IDENTIFIER RPAREN SEMI  */
#line 429 "parser.y"
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
#line 1895 "parser.tab.c"
    break;

  case 69: /* scan_stmt: SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI  */
#line 444 "parser.y"
        {
            if(execute_flag) {
                double v;
                scanf("%lf",&v);
                set_array_element((yyvsp[-5].sval),(int)(yyvsp[-3].dval),v);
            }
        }
#line 1907 "parser.tab.c"
    break;

  case 70: /* @1: %empty  */
#line 457 "parser.y"
        { 
            (yyval.ival) = execute_flag;
            if (execute_flag) {
                if ((yyvsp[-1].dval)) {
                    /* execute this block */
                } else {
                    execute_flag = 0;
                }
            }
        }
#line 1922 "parser.tab.c"
    break;

  case 71: /* $@2: %empty  */
#line 468 "parser.y"
        {
            if ((yyvsp[-3].ival)) {
                if ((yyvsp[-5].dval)) {
                    execute_flag = 0; /* block ran, skip rest of chain */
                } else {
                    execute_flag = 1; /* didn't run, check next block */
                }
            } else {
                execute_flag = 0; /* were already skipping */
            }
        }
#line 1938 "parser.tab.c"
    break;

  case 72: /* if_stmt: IF LPAREN condition RPAREN @1 LBRACE statement_list RBRACE $@2 else_if_part  */
#line 480 "parser.y"
        { 
            execute_flag = (yyvsp[-5].ival); 
        }
#line 1946 "parser.tab.c"
    break;

  case 73: /* @3: %empty  */
#line 487 "parser.y"
        {
            /* remember state before this block */
            (yyval.ival) = execute_flag;
            if (execute_flag) {
                if ((yyvsp[-1].dval)) {
                    /* execute this */
                } else {
                    execute_flag = 0;
                }
            }
        }
#line 1962 "parser.tab.c"
    break;

  case 74: /* $@4: %empty  */
#line 499 "parser.y"
        {
            /* state before ELSEIF block is in $<ival>5 */
            if ((yyvsp[-3].ival)) {
                if ((yyvsp[-5].dval)) {
                    execute_flag = 0; /* this ran, skip later parts */
                } else {
                    execute_flag = 1; /* this didn't run, search next parts */
                }
            } else {
                execute_flag = 0; /* were already skipping whole chain */
            }
        }
#line 1979 "parser.tab.c"
    break;

  case 78: /* $@5: %empty  */
#line 520 "parser.y"
        {
            /*
             * Push a new frame onto the switch stack.
             * outer_exec = current execute_flag so we can
             * restore it exactly when the switch ends.
             */
            switch_push((yyvsp[-1].dval), execute_flag);

            if (execute_flag) {
                /* start with execute_flag = 0; each case
                   will turn it on/off as needed            */
                execute_flag = 0;
            } else {
                /* we are inside a skipped block — mark
                   the whole switch as already done so
                   every case/default is skipped too        */
                switch_cur()->done = 1;
            }
        }
#line 2003 "parser.tab.c"
    break;

  case 79: /* switch_stmt: SWITCH LPAREN expression RPAREN $@5 LBRACE case_list RBRACE  */
#line 540 "parser.y"
        {
            /* restore the execution context that was active
               before this switch statement                  */
            execute_flag = switch_cur()->outer_exec;
            switch_pop();
            break_flag = 0;   /* consume any leftover break */
        }
#line 2015 "parser.tab.c"
    break;

  case 83: /* $@6: %empty  */
#line 557 "parser.y"
        {
            /* case_expr already set execute_flag appropriately */
        }
#line 2023 "parser.tab.c"
    break;

  case 84: /* case_item: CASE case_expr COLON $@6 statement_list  */
#line 561 "parser.y"
        {
            SwitchFrame *f = switch_cur();
            if (f && break_flag && execute_flag) {
                f->done      = 1;
                execute_flag = 0;
                break_flag   = 0;
            }
        }
#line 2036 "parser.tab.c"
    break;

  case 85: /* case_expr: expression  */
#line 573 "parser.y"
        {
            SwitchFrame *f = switch_cur();
            if (f == NULL) {
                yyerror("case outside switch");
                execute_flag = 0;
            } else if (f->done) {
                execute_flag = 0;
            } else if (f->matched) {
                execute_flag = 1;
            } else if (fabs(f->value - (yyvsp[0].dval)) < SWITCH_EPSILON) {
                f->matched   = 1;
                execute_flag = 1;
            } else {
                execute_flag = 0;
            }
        }
#line 2057 "parser.tab.c"
    break;

  case 86: /* case_expr: expression RANGE expression  */
#line 590 "parser.y"
        {
            SwitchFrame *f = switch_cur();
            if (f == NULL) {
                yyerror("case outside switch");
                execute_flag = 0;
            } else if (f->done) {
                execute_flag = 0;
            } else if (f->matched) {
                execute_flag = 1;
            } else {
                int start = (int)(yyvsp[-2].dval);
                int end = (int)(yyvsp[0].dval);
                int val = (int)f->value;
                
                if (val >= start && val <= end) {
                    f->matched   = 1;
                    execute_flag = 1;
                } else {
                    execute_flag = 0;
                }
            }
        }
#line 2084 "parser.tab.c"
    break;

  case 87: /* $@7: %empty  */
#line 617 "parser.y"
        {
            SwitchFrame *f = switch_cur();
            if (f == NULL) {
                yyerror("default outside switch");
                execute_flag = 0;
            } else if (f->done) {
                /* break was hit earlier */
                execute_flag = 0;
            } else if (f->matched) {
                /* falling through from a previous case (no break) */
                execute_flag = 1;
            } else {
                /* no case matched at all — default is the entry point */
                execute_flag = 1;
            }
        }
#line 2105 "parser.tab.c"
    break;

  case 88: /* default_item: DEFAULT COLON $@7 statement_list  */
#line 634 "parser.y"
        {
            SwitchFrame *f = switch_cur();
            if (f && break_flag && execute_flag) {
                f->done      = 1;
                execute_flag = 0;
                break_flag   = 0;
            }
        }
#line 2118 "parser.tab.c"
    break;

  case 89: /* condition: expression EQ expression  */
#line 647 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)==(yyvsp[0].dval); }
#line 2124 "parser.tab.c"
    break;

  case 90: /* condition: expression NEQ expression  */
#line 648 "parser.y"
                                { (yyval.dval)=(yyvsp[-2].dval)!=(yyvsp[0].dval); }
#line 2130 "parser.tab.c"
    break;

  case 91: /* condition: expression GT expression  */
#line 649 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)>(yyvsp[0].dval); }
#line 2136 "parser.tab.c"
    break;

  case 92: /* condition: expression LT expression  */
#line 650 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)<(yyvsp[0].dval); }
#line 2142 "parser.tab.c"
    break;

  case 93: /* condition: expression GE expression  */
#line 651 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)>=(yyvsp[0].dval); }
#line 2148 "parser.tab.c"
    break;

  case 94: /* condition: expression LE expression  */
#line 652 "parser.y"
                               { (yyval.dval)=(yyvsp[-2].dval)<=(yyvsp[0].dval); }
#line 2154 "parser.tab.c"
    break;

  case 95: /* loop_stmt: WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE  */
#line 659 "parser.y"
        { 
            /* Note: Due to parser limitations, loops execute once per parse.
               For proper loop execution, use the for-loop pattern with arrays. */
        }
#line 2163 "parser.tab.c"
    break;

  case 96: /* loop_stmt: FOR LPAREN assignment SEMI condition SEMI assignment RPAREN LBRACE statement_list RBRACE  */
#line 665 "parser.y"
        { 
            /* Note: Due to parser limitations, loops execute once per parse.
               For proper loop execution, process arrays with multiple statements. */
        }
#line 2172 "parser.tab.c"
    break;

  case 97: /* return_stmt: RETURN expression  */
#line 673 "parser.y"
        { if(execute_flag) printf("Program returned: %g\n",(yyvsp[0].dval)); }
#line 2178 "parser.tab.c"
    break;


#line 2182 "parser.tab.c"

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

#line 676 "parser.y"


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


