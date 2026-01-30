%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int line = 1;
    typedef union {
    int ival;
    float fval;
    char cval;
    char *sval;
} YYSTYPE;

YYSTYPE yylval;

// Dummy token definitions for testing lexer only
#define INCLUDE 1
#define DEFINE 2
#define INT_TYPE 3
#define FLOAT_TYPE 4
#define DOUBLE_TYPE 5
#define CHAR_TYPE 6
#define BOOL_TYPE 7
#define VOID_TYPE 8
#define LONG_TYPE 9
#define SHORT_TYPE 10
#define UNSIGNED_TYPE 11
#define CONST 12
#define STRUCT 13
#define UNION 14
#define TYPEDEF 15
#define ENUM 16
#define IF 17
#define ELSE 18
#define ELSEIF 19
#define SWITCH 20
#define CASE 21
#define DEFAULT 22
#define BREAK 23
#define RETURN 24
#define FOR 25
#define WHILE 26
#define DO 27
#define CONTINUE 28
#define MAIN 29
#define PRINT 30
#define SCAN 31
#define POW 32
#define SQRT 33
#define ABS 34
#define FLOOR 35
#define CEIL 36
#define EQ 37
#define NEQ 38
#define GE 39
#define LE 40
#define AND 41
#define OR 42
#define NOT 43
#define INC 44
#define DEC 45
#define PLUS 46
#define MINUS 47
#define MUL 48
#define DIV 49
#define MOD 50
#define ASSIGN 51
#define BIT_AND 52
#define BIT_OR 53
#define BIT_XOR 54
#define BIT_NOT 55
#define SHL 56
#define SHR 57
#define GT 58
#define LT 59
#define SEMI 60
#define COMMA 61
#define LPAREN 62
#define RPAREN 63
#define LBRACE 64
#define RBRACE 65
#define LBRACKET 66
#define RBRACKET 67
#define FLOAT_LITERAL 68
#define INT_LITERAL 69
#define STRING_LITERAL 70
#define CHAR_LITERAL 71
#define IDENTIFIER 72

%}

%option yylineno


DIGIT   [0-9]
LETTER    [a-zA-Z]
ID    [a-zA-Z_][a-zA-Z0-9_]*
INTEGER    {DIGIT}+
FLOAT    {DIGIT}+"."{DIGIT}+
EXPONENT    {DIGIT}+("."{DIGIT}+)?[eE][+-]?{DIGIT}+
STRING    \"([^\"\\\n]|\\.)*\"
CHAR        \'([^\'\\\n]|\\.)\'

%x MULTILINE_COMMENT

%%


"#Import"   { printf("#Import"); return INCLUDE; }
"#Suppose"  { printf("#Suppose"); return DEFINE; }


"Number"    { printf("Int: %s\n", yytext); return INT_TYPE; }
"Decimal"   { printf("float: %s\n", yytext); return FLOAT_TYPE; }
"LargeDecimal"  { printf("double: %s\n", yytext); return DOUBLE_TYPE; }
"Letter"    { printf("Char: %s\n", yytext); return CHAR_TYPE; }
"TrueFalse" { printf("Bool: %s\n", yytext); return BOOL_TYPE; }
"Nothing"   { printf("void: %s\n", yytext); return VOID_TYPE; }
"BigNumber" { printf("Large Int: %s\n", yytext); return LONG_TYPE; }
"SmallNumber"   { printf("Short: %s\n", yytext); return SHORT_TYPE; }
"Positive"  { printf("Unsigned: %s\n", yytext); return UNSIGNED_TYPE; }


"Constant"      {printf("const: %s\n", yytext); return CONST;}


"Record"    { printf("Struct: %s\n", yytext); return STRUCT; }
"SharedRecord"    { printf("Union: %s\n", yytext); return UNION; }
"Rename"    { printf("typedef: %s\n", yytext); return TYPEDEF; }
"Choices"    { printf("Enum: %s\n", yytext); return ENUM; }


"Check"    { printf("if: %s\n", yytext); return IF; }
"Otherwise"    { printf("else: %s\n", yytext); return ELSE; }
"ElseCheck"    { printf("else if: %s\n", yytext); return ELSEIF; }
"Choose"    { printf("switch: %s\n", yytext); return SWITCH; }
"Option"    { printf("case: %s\n", yytext); return CASE; }
"DefaultOption"    { printf("default: %s\n", yytext); return DEFAULT; }
"Stop"    { printf("break: %s\n", yytext); return BREAK; }
"Return"    { printf("return: %s\n", yytext); return RETURN; }


"Repeat"    { printf("for: %s\n", yytext); return FOR; }
"WhileStudy"    { printf("while: %s\n", yytext); return WHILE; }
"DoOnce"    { printf("do: %s\n", yytext); return DO; }
"Skip"    { printf("continue: %s\n", yytext); return CONTINUE; }


"StartExam"    { printf("main: %s\n", yytext); return MAIN; }
"Show"    { printf("printf: %s\n", yytext); return PRINT; }
"Take"    { printf("scanf: %s\n", yytext); return SCAN; }

"Power"    { printf("power: %s\n", yytext); return POW; }
"Root"    { printf("sqrt: %s\n", yytext); return SQRT; }
"Absolute"    { printf("abs: %s\n", yytext); return ABS; }
"Floor"    { printf("floor: %s\n", yytext); return FLOOR; }
"Ceil"    { printf("ceil: %s\n", yytext); return CEIL; }


"=="                { return EQ; }
"!="                { return NEQ; }
">="                { return GE; }
"<="                { return LE; }


"&&"                { return AND; }
"||"                { return OR; }
"!"                 { return NOT; }

"++"                { return INC; }
"--"                { return DEC; }

"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MUL; }
"/"                 { return DIV; }
"%"                 { return MOD; }

"="                 { return ASSIGN; }


"&"                 { return BIT_AND; }
"|"                 { return BIT_OR; }
"^"                 { return BIT_XOR; }
"~"                 { return BIT_NOT; }
"<<"                { return SHL; }
">>"                { return SHR; }
">"                 { return GT; }
"<"                 { return LT; }


";"                 { return SEMI; }
","                 { return COMMA; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
"["                 { return LBRACKET; }
"]"                 { return RBRACKET; }


{FLOAT}             { printf("float_val: %s\n", yytext); yylval.fval = atof(yytext); return FLOAT_LITERAL; }
{INTEGER}             { printf("int_val: %s\n", yytext); yylval.ival = atoi(yytext); return INT_LITERAL; }
{STRING}             { printf("string_val: %s\n", yytext); yylval.sval = strdup(yytext); return STRING_LITERAL; }
{CHAR}             { printf("char_val: %s\n", yytext); yylval.cval = yytext[1]; return CHAR_LITERAL; }


{ID}            {printf("variable: %s\n", yytext); yylval.sval=strdup(yytext); return IDENTIFIER; }


"##".*          {printf("singleline comment");}
"#*"            {printf("Multi line comment begins"); BEGIN(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>\n   { line++; }
<MULTILINE_COMMENT>.    {}
<MULTILINE_COMMENT>"*#"     {printf("Multiline comments ends"); BEGIN(INITIAL); }

[ \t\r]+    ;
\n          { line++; }


.           { printf("Lexical error at line %d: %s\n", line, yytext); }
%%

int yywrap(){
    return 1;
}

int main()
{
    FILE *f = fopen("input.txt", "r");
    yyin = f;
    int token;
    while ((token = yylex()) != 0) {
        printf("Line %d: token = %d\n", line, token);
    }
    
    fclose(f);
    return 0;
}