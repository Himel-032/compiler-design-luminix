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
#define HEADER 73
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
const char* token_name(int token)
{
    switch (token)
    {
        case HEADER: return "HEADER";
        case INCLUDE: return "INCLUDE";
        case DEFINE: return "DEFINE";

        case INT_TYPE: return "INT_TYPE";
        case FLOAT_TYPE: return "FLOAT_TYPE";
        case DOUBLE_TYPE: return "DOUBLE_TYPE";
        case CHAR_TYPE: return "CHAR_TYPE";
        case BOOL_TYPE: return "BOOL_TYPE";
        case VOID_TYPE: return "VOID_TYPE";
        case LONG_TYPE: return "LONG_TYPE";
        case SHORT_TYPE: return "SHORT_TYPE";
        case UNSIGNED_TYPE: return "UNSIGNED_TYPE";
        case CONST: return "CONST";

        case STRUCT: return "STRUCT";
        case UNION: return "UNION";
        case TYPEDEF: return "TYPEDEF";
        case ENUM: return "ENUM";

        case IF: return "IF";
        case ELSE: return "ELSE";
        case ELSEIF: return "ELSEIF";
        case SWITCH: return "SWITCH";
        case CASE: return "CASE";
        case DEFAULT: return "DEFAULT";
        case BREAK: return "BREAK";
        case RETURN: return "RETURN";

        case FOR: return "FOR";
        case WHILE: return "WHILE";
        case DO: return "DO";
        case CONTINUE: return "CONTINUE";

        case MAIN: return "MAIN";
        case PRINT: return "PRINT";
        case SCAN: return "SCAN";

        case POW: return "POW";
        case SQRT: return "SQRT";
        case ABS: return "ABS";
        case FLOOR: return "FLOOR";
        case CEIL: return "CEIL";

        case EQ: return "EQ";
        case NEQ: return "NEQ";
        case GE: return "GE";
        case LE: return "LE";
        case GT: return "GT";
        case LT: return "LT";

        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";

        case INC: return "INC";
        case DEC: return "DEC";

        case PLUS: return "PLUS";
        case MINUS: return "MINUS";
        case MUL: return "MUL";
        case DIV: return "DIV";
        case MOD: return "MOD";
        case ASSIGN: return "ASSIGN";

        case BIT_AND: return "BIT_AND";
        case BIT_OR: return "BIT_OR";
        case BIT_XOR: return "BIT_XOR";
        case BIT_NOT: return "BIT_NOT";
        case SHL: return "SHL";
        case SHR: return "SHR";

        case SEMI: return "SEMI";
        case COMMA: return "COMMA";
        case LPAREN: return "LPAREN";
        case RPAREN: return "RPAREN";
        case LBRACE: return "LBRACE";
        case RBRACE: return "RBRACE";
        case LBRACKET: return "LBRACKET";
        case RBRACKET: return "RBRACKET";

        case FLOAT_LITERAL: return "FLOAT_LITERAL";
        case INT_LITERAL: return "INT_LITERAL";
        case STRING_LITERAL: return "STRING_LITERAL";
        case CHAR_LITERAL: return "CHAR_LITERAL";
        case IDENTIFIER: return "IDENTIFIER";

        default: return "UNKNOWN";
    }
}


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
HEADER_SYS   <[a-zA-Z_][a-zA-Z0-9_]*\.h>
HEADER_USER  \"[a-zA-Z_][a-zA-Z0-9_]*\.h\"


%x MULTILINE_COMMENT

%%


"#Import"     { return INCLUDE; }
"#Suppose"    { return DEFINE; }

{HEADER_SYS}  { return HEADER; }
{HEADER_USER} { return HEADER; }



"Number"        { return INT_TYPE; }
"Decimal"       { return FLOAT_TYPE; }
"LargeDecimal"  { return DOUBLE_TYPE; }
"Letter"        { return CHAR_TYPE; }
"TrueFalse"     { return BOOL_TYPE; }
"Nothing"       { return VOID_TYPE; }
"BigNumber"     { return LONG_TYPE; }
"SmallNumber"   { return SHORT_TYPE; }
"Positive"      { return UNSIGNED_TYPE; }
"Constant"      { return CONST; }



"Record"        { return STRUCT; }
"SharedRecord"  { return UNION; }
"Rename"        { return TYPEDEF; }
"Choices"       { return ENUM; }



"Check"         { return IF; }
"Otherwise"     { return ELSE; }
"ElseCheck"     { return ELSEIF; }
"Choose"        { return SWITCH; }
"Option"        { return CASE; }
"DefaultOption" { return DEFAULT; }
"Stop"          { return BREAK; }
"Return"        { return RETURN; }



"Repeat"        { return FOR; }
"WhileStudy"    { return WHILE; }
"DoOnce"        { return DO; }
"Skip"          { return CONTINUE; }



"StartExam"     { return MAIN; }
"Show"          { return PRINT; }
"Take"          { return SCAN; }


"Power"         { return POW; }
"Root"          { return SQRT; }
"Absolute"      { return ABS; }
"Floor"         { return FLOOR; }
"Ceil"          { return CEIL; }



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

{FLOAT}   { yylval.fval = atof(yytext); return FLOAT_LITERAL; }
{INTEGER} { yylval.ival = atoi(yytext); return INT_LITERAL; }
{STRING}  { yylval.sval = strdup(yytext); return STRING_LITERAL; }
{CHAR}    { yylval.cval = yytext[1]; return CHAR_LITERAL; }
{ID}      { yylval.sval = strdup(yytext); return IDENTIFIER; }



"##".*         { }
"#*"           { BEGIN(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>\n { line++; }
<MULTILINE_COMMENT>.  { }
<MULTILINE_COMMENT>"*#" { BEGIN(INITIAL); }

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
    printf("Line: %d -> <%s, ", line, token_name(token));

    switch (token) {
        case INT_LITERAL:
            printf("%d", yylval.ival);
            break;
        case FLOAT_LITERAL:
            printf("%f", yylval.fval);
            break;
        case CHAR_LITERAL:
            printf("'%c'", yylval.cval);
            break;
        case STRING_LITERAL:
        case IDENTIFIER:
            printf("%s", yylval.sval);
            break;
        default:
            printf("%s", yytext);
    }

    printf(">\n");
}

    
    fclose(f);
    return 0;
}