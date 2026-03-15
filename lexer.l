%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "parser.tab.h"
  
    
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


"#Attach"     { return INCLUDE; }
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
":"                 { return COLON; }
".."                { return RANGE; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }
"{"                 { return LBRACE; }
"}"                 { return RBRACE; }
"["                 { return LBRACKET; }
"]"                 { return RBRACKET; }


"True"  { return TRUE_LITERAL; }
"False" { return FALSE_LITERAL; }
{FLOAT}   { yylval.fval = atof(yytext); return FLOAT_LITERAL; }
{INTEGER} { yylval.ival = atoi(yytext); return INT_LITERAL; }
{STRING}  { yylval.sval = strdup(yytext); return STRING_LITERAL; }
{CHAR}    { yylval.cval = yytext[1]; return CHAR_LITERAL; }
{ID}      { yylval.sval = strdup(yytext); return IDENTIFIER; }



"##".*         { }
"#*"           { BEGIN(MULTILINE_COMMENT); }
<MULTILINE_COMMENT>\n ; 
<MULTILINE_COMMENT>.  { }
<MULTILINE_COMMENT>"*#" { BEGIN(INITIAL); }

[ \t\r]+    ;
\n          ; 


.           {  }
%%

int yywrap(){
    return 1;
}

