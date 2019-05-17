/* Definition section */
%{
	#include <stdio.h>
	#include <stdlib.h>

	int num_line = 0;
	int num_comment = 0;
%}

/* Define regular expression label */
%x string_const
%x C_COMMENT
%x CPLUS_COMMENT
letter [a-zA-Z]
digit [0-9]
id {letter}+({letter}|{digit})*
number {digit}+
float_number [-]?{digit}*"."{digit}+
string_constants \"([^\\\"]|\\.)*\"
comment "/*"([^*]|\*+[^*/])*"*/" 
single_comment "//"([^\n])*"\n"

/* Rules section */
%%
"\""	{ BEGIN(string_const); ECHO; printf(" \t QUOTA\n");}
<string_const>"\\\""	{ ECHO; }
<string_const>"\""	{ BEGIN(INITIAL); printf(" \t STR_CONST\n%s \t QUOTA\n", yytext);}
<string_const>.	{ ECHO; }

"/*"	{ BEGIN(C_COMMENT); ECHO; }
<C_COMMENT>\n	{ num_comment++; num_line++; ECHO; }
<C_COMMENT>"*/"	{ BEGIN(INITIAL); num_comment++; printf("*/ \t C Comment\n"); }
<C_COMMENT>.	{ ECHO; }

"//"	{ BEGIN(CPLUS_COMMENT); ECHO; }
<CPLUS_COMMENT>\n	{ BEGIN(INITIAL); num_comment++; num_line++; printf(" \t C++ Comment\n"); }
<CPLUS_COMMENT>.	{ ECHO; }
"+" 	{ printf("%s \t ADD\n", yytext); }
"-"		{ printf("%s \t SUB\n", yytext); }
"*" 	{ printf("%s \t MUL\n", yytext); }
"/"		{ printf("%s \t DIV\n", yytext); }
"%" 	{ printf("%s \t MOD\n", yytext); }
"++"	{ printf("%s \t INC\n", yytext); }
"--" 	{ printf("%s \t DEC\n", yytext); }
">"		{ printf("%s \t MT\n", yytext); }
"<" 	{ printf("%s \t LT\n", yytext); }
">="	{ printf("%s \t MTE\n", yytext); }
"<=" 	{ printf("%s \t LTE\n", yytext); }
"=="	{ printf("%s \t EQ\n", yytext); }
"!=" 	{ printf("%s \t NE\n", yytext); }
"["		{ printf("%s \t LSB\n", yytext); }
"]" 	{ printf("%s \t RSB\n", yytext); }
","		{ printf("%s \t COMMA\n", yytext); }
";" 	{ printf("%s \t SEMICOLON\n", yytext); }
"print" { printf("%s \t PRINT\n", yytext); }
"if"	{ printf("%s \t IF\n", yytext); }
"else" 	{ printf("%s \t ELSE\n", yytext); }
"for"	{ printf("%s \t FOR\n", yytext); }
"while" { printf("%s \t WHILE\n", yytext); }
"string"	{ printf("%s \t STRING\n", yytext); }
"int" 	{ printf("%s \t INT\n", yytext); }
"float"	{ printf("%s \t FLOAT\n", yytext); }
"=" 	{ printf("%s \t ASGN\n", yytext); }
"+="	{ printf("%s \t ADDASGN\n", yytext); }
"-=" 	{ printf("%s \t SUBASGN\n", yytext); }
"*="	{ printf("%s \t MULASGN\n", yytext); }
"/=" 	{ printf("%s \t DIVASGN\n", yytext); }
"%="	{ printf("%s \t MODASGN\n", yytext); }
"&&" 	{ printf("%s \t AND\n", yytext); }
"||"	{ printf("%s \t OR\n", yytext); }
"!" 	{ printf("%s \t NOT\n", yytext); }
"("		{ printf("%s \t LB\n", yytext); }
")" 	{ printf("%s \t RB\n", yytext); }
"{"		{ printf("%s \t LCB\n", yytext); }
"}" 	{ printf("%s \t RCB\n", yytext); }
"void"	{ printf("%s \t VOID\n", yytext); }
"bool" 	{ printf("%s \t BOOL\n", yytext); }
"true"	{ printf("%s \t TRUE\n", yytext); }
"false" { printf("%s \t FALSE\n", yytext); }
"return"	{ printf("%s \t RET\n", yytext); }
"continue" 	{ printf("%s \t CONT\n", yytext); }
"break"	{ printf("%s \t BREAK\n", yytext); }
" "		{;}
{id}	{ printf("%s \t ID\n", yytext); }
{number}	{ printf("%s \t I_CONST\n", yytext); }
{float_number}	{ printf("%s \t F_CONST\n", yytext); }
\n		{num_line++;}
%%

/*	C Code section */
int yywrap(void)
{
    return 1;
}

int main(int argc,char *argv[])
{
	num_comment = 0;
	num_line = 0;
	yyin = fopen(argv[1],"r");
	yylex();
	printf("\nParse over, the line number is %d.\n\n", num_line);
	printf("comment: %d lines\n\n", num_comment);

	return 0;
}
