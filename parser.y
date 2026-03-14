/* bison -d parser.y; flex lexer.l; gcc parser.tab.c lex.yy.c -o luminix; ./luminix input.txt */

%{
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

%}

%union{
    int ival;
    float fval;
    char cval;
    char *sval;
    double dval;
}

/* tokens */

%token INCLUDE DEFINE HEADER

%token INT_TYPE FLOAT_TYPE DOUBLE_TYPE CHAR_TYPE BOOL_TYPE
%token VOID_TYPE LONG_TYPE SHORT_TYPE UNSIGNED_TYPE CONST

%token STRUCT UNION TYPEDEF ENUM

%token IF ELSE ELSEIF SWITCH CASE DEFAULT
%token FOR WHILE DO BREAK CONTINUE RETURN

%token MAIN PRINT SCAN

%token TRUE_LITERAL FALSE_LITERAL

%token POW SQRT ABS FLOOR CEIL

%token EQ NEQ GE LE GT LT
%token AND OR NOT
%token INC DEC
%token PLUS MINUS MUL DIV MOD
%token ASSIGN

%token BIT_AND BIT_OR BIT_XOR BIT_NOT SHL SHR

%token SEMI COMMA
%token LPAREN RPAREN
%token LBRACE RBRACE
%token LBRACKET RBRACKET

%token <ival> INT_LITERAL
%token <fval> FLOAT_LITERAL
%token <sval> STRING_LITERAL
%token <cval> CHAR_LITERAL
%token <sval> IDENTIFIER

%type <dval> expression term factor primary condition function_call array_access
%type <ival> array_size

%left OR
%left AND
%left EQ NEQ
%left GT LT GE LE
%left PLUS MINUS
%left MUL DIV MOD
%right UNARY

%start program

%%

program
    : preprocessor_list main_function
    ;

preprocessor_list
    : preprocessor_list preprocessor
    |
    ;

preprocessor
    : INCLUDE HEADER
    | DEFINE IDENTIFIER INT_LITERAL
    ;

main_function
    : MAIN LPAREN RPAREN LBRACE statement_list RBRACE
    ;

statement_list
    : statement_list statement
    |
    ;

statement
    : declaration
    | assignment SEMI
    | array_assignment SEMI
    | print_stmt
    | scan_stmt
    | if_stmt
    | loop_stmt
    | return_stmt SEMI
    ;

declaration
    : type identifier_list SEMI
        { /* handled in identifier_list actions */ }
    | type IDENTIFIER LBRACKET array_size RBRACKET SEMI
        { if(execute_flag) declare_array($2,$4); }
    | type IDENTIFIER LBRACKET array_size RBRACKET LBRACKET array_size RBRACKET SEMI
    { 
        if(execute_flag)
            declare_2d_array($2,$4,$7); 
    }
    ;

array_size
    : INT_LITERAL { $$=$1; }
    ;

type
    : INT_TYPE          { current_decl_type = 0; }
    | FLOAT_TYPE        { current_decl_type = 0; }
    | DOUBLE_TYPE       { current_decl_type = 0; }
    | CHAR_TYPE         { current_decl_type = 1; }
    | BOOL_TYPE         { current_decl_type = 0; }
    | VOID_TYPE         { current_decl_type = 0; }
    | LONG_TYPE         { current_decl_type = 0; }
    | SHORT_TYPE        { current_decl_type = 0; }
    | UNSIGNED_TYPE     { current_decl_type = 0; }
    ;

identifier_list
    : IDENTIFIER
        { if(execute_flag) set_symbol($1,0); }
    | IDENTIFIER ASSIGN expression
        { if(execute_flag) set_symbol($1,$3); }
    | IDENTIFIER COMMA identifier_list
        { if(execute_flag) set_symbol($1,0); }
    | IDENTIFIER ASSIGN expression COMMA identifier_list
        { if(execute_flag) set_symbol($1,$3); }
    ;

assignment
    : IDENTIFIER ASSIGN expression
        { if(execute_flag) set_symbol($1,$3); }
    ;

array_assignment
    : IDENTIFIER LBRACKET expression RBRACKET ASSIGN expression
        { if(execute_flag) set_array_element($1,(int)$3,$6); }
    | IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET ASSIGN expression
        { if(execute_flag) set_array2d_element($1,(int)$3,(int)$6,$9); }
    ;

/* ---------------- EXPRESSIONS ---------------- */

expression
    : expression PLUS term   { $$=$1+$3; }
    | expression MINUS term  { $$=$1-$3; }
    | MINUS term %prec UNARY { $$=-$2; }
    | term                   { $$=$1; }
    ;

term
    : term MUL factor   { $$=$1*$3; }
    | term DIV factor   { if($3!=0) $$=$1/$3; else {yyerror("Division by zero"); $$=0;} }
    | term MOD factor   { if((int)$3!=0) $$=(int)$1%(int)$3; else {yyerror("Modulo by zero"); $$=0;} }
    | factor            { $$=$1; }
    ;

factor
    : primary           { $$=$1; }
    ;

primary
    : IDENTIFIER        { $$=get_symbol($1); }
    | INT_LITERAL       { $$=$1; }
    | FLOAT_LITERAL     { $$=$1; }
    | TRUE_LITERAL      { $$=1; }
    | FALSE_LITERAL     { $$=0; }
    | CHAR_LITERAL      { $$ = $1; }
    | LPAREN expression RPAREN { $$=$2; }
    | function_call     { $$=$1; }
    | array_access      { $$=$1; }
    ;

array_access
    : IDENTIFIER LBRACKET expression RBRACKET
        { $$=get_array_element($1,(int)$3); }
    | IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET
        { $$ = get_array2d_element($1,(int)$3,(int)$6); }
    ;

/* ---------------- FUNCTIONS ---------------- */

function_call
    : POW LPAREN expression COMMA expression RPAREN
        { $$=pow($3,$5); }
    | SQRT LPAREN expression RPAREN
        { $$=sqrt($3); }
    | ABS LPAREN expression RPAREN
        { $$=fabs($3); }
    | FLOOR LPAREN expression RPAREN
        { $$=floor($3); }
    | CEIL LPAREN expression RPAREN
        { $$=ceil($3); }
    ;

/* ---------------- PRINT ---------------- */

print_stmt
    : PRINT LPAREN STRING_LITERAL RPAREN SEMI
        { if(execute_flag) { 
            char *s = $3;
            if(s[0]=='"') s++;
            int len = strlen(s);
            if(len>0 && s[len-1]=='"') s[len-1]='\0';
            printf("%s\n",s); 
          }
        }
    | PRINT LPAREN IDENTIFIER RPAREN SEMI
        { if(execute_flag) {
            int t = get_symbol_type($3);
            double v = get_symbol($3);
            if(t == 1) printf("%c\n", (int)v);
            else printf("%g\n", v);
          }
        }
    | PRINT LPAREN expression RPAREN SEMI
        { if(execute_flag) printf("%g\n",$3); }
    ;

/* ---------------- INPUT ---------------- */

scan_stmt
    : SCAN LPAREN IDENTIFIER RPAREN SEMI
        {
            if(execute_flag) {
                int t = get_symbol_type($3);
                if(t == 1) { /* char */
                    char v;
                    scanf(" %c", &v);
                    set_symbol($3, (double)v);
                } else {
                    double v;
                    scanf("%lf",&v);
                    set_symbol($3,v);
                }
            }
        }
    | SCAN LPAREN IDENTIFIER LBRACKET expression RBRACKET RPAREN SEMI
        {
            if(execute_flag) {
                double v;
                scanf("%lf",&v);
                set_array_element($3,(int)$5,v);
            }
        }
    ;

/* ---------------- IF ---------------- */

if_stmt
    : IF LPAREN condition RPAREN 
        { 
            $<ival>$ = execute_flag;
            if(!($3)) execute_flag = 0; 
        }
      LBRACE statement_list RBRACE else_part
        { 
            execute_flag = $<ival>5; 
        }
    ;

else_part
    : ELSE 
        { 
            if(execute_flag == 0) execute_flag = 1;
            else execute_flag = 0;
        }
      LBRACE statement_list RBRACE
    | /* empty */
    ;

/* ---------------- CONDITION ---------------- */

condition
    : expression EQ expression { $$=$1==$3; }
    | expression NEQ expression { $$=$1!=$3; }
    | expression GT expression { $$=$1>$3; }
    | expression LT expression { $$=$1<$3; }
    | expression GE expression { $$=$1>=$3; }
    | expression LE expression { $$=$1<=$3; }
    ;

/* ---------------- LOOPS ---------------- */

loop_stmt
    : WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE
        { 
            /* Note: Due to parser limitations, loops execute once per parse.
               For proper loop execution, use the for-loop pattern with arrays. */
        }
    | FOR LPAREN assignment SEMI condition SEMI assignment RPAREN
      LBRACE statement_list RBRACE
        { 
            /* Note: Due to parser limitations, loops execute once per parse.
               For proper loop execution, process arrays with multiple statements. */
        }
    ;

return_stmt
    : RETURN expression
        { if(execute_flag) printf("Program returned: %g\n",$2); }
    ;

%%

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


