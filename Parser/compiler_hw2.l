/* Definition section */
%{
#include "y.tab.h"	/* header file generated by bison */
#define BUF_SIZE 256

extern YYSTYPE yylval; //YYSTYPE
extern int sem_err_flag;
extern int yylineno;
char buf[BUF_SIZE];
int line_num = 0;
int scope = 0;
char temp[20];  // temp is used to save the previous yytext
int rsb = 0;

/* This macro is used to record code line */
#define CONCAT { strncat(buf, yytext, BUF_SIZE - strlen(buf) - 1); strcpy(temp, yytext); }
%}

/* Define regular expression label */
digit		[0-9]
letter		[a-zA-Z]
integer     {digit}+
float       {digit}+"."{digit}+
id			{letter}+({letter}|{digit})*

%option yylineno

%x COMMENT STRING_STATE

/* Rules section */
%%

 /* Arithmetic */
"+"     { CONCAT; return ADD; }
"-" 	{ CONCAT; return SUB; }
"*" 	{ CONCAT; return MUL; }
"/" 	{ CONCAT; return DIV; }
"%"     { CONCAT; return MOD; }
"++"    { CONCAT; return INC; }
"--"    { CONCAT; return DEC; }

 /* Relational */
">"		{ CONCAT; return MT; }
"<"		{ CONCAT; return LT; }
">="	{ CONCAT; return MTE; }
"<="	{ CONCAT;; return LTE; }
"=="	{ CONCAT; return EQ; }
"!="	{ CONCAT; return NE; }

 /* Assignment */
"="		{ CONCAT; return ASGN; }
"+="	{ CONCAT; return ADDASGN; }
"-="	{ CONCAT; return SUBASGN; }
"*="	{ CONCAT; return MULASGN; }
"/="	{ CONCAT; return DIVASGN; }
"%="	{ CONCAT; return MODASGN; }

 /* Logical */
"&&"	{ CONCAT; return AND; }
"||"	{ CONCAT; return OR; }
"!"		{ CONCAT; return NOT; }

 /* Delimiters */
"("		{ CONCAT; scope++; return LB; }
")"		{ CONCAT; scope--; return RB; }
"{"		{ CONCAT; scope++; return LCB; }
 /* Situation that it encounters } when } isn't followed by \n statement, delay until finish reading the whole line */
"}"		{   CONCAT; scope--;
            /* set the rsb flag */
            rsb = 1;
            return RCB; 
        }
"["		{ CONCAT; return LSB; }
"]"		{ CONCAT; return RSB; }
","		{ CONCAT; return COMMA; }
 /* Print Keywords */	
"print"		{ CONCAT; return PRINT; }

 /* Condition and Loop Keywords */
"if"		{ CONCAT; return IF; }
"else"		{ CONCAT; return ELSE; }
"for"		{ CONCAT; return FOR; }
"while"		{ CONCAT; return WHILE; }
"break"     { CONCAT; return BREAK; }
"continue"     { CONCAT; return CONT; }

 /* Declaration Keywords */
"void"		{ CONCAT; return VOID; }
"int"		{ CONCAT; return INT; }
"float"  	{ CONCAT; return FLOAT; }
"string"  	{ CONCAT; return STRING; }
"bool"  	{ CONCAT; return BOOL; }

 /* boolean Keywords */
"true"      { CONCAT; return TRUE; }
"false"     { CONCAT; return FALSE; }

"return"    { CONCAT; return RET; }

 /* String Constant */
\"				        { BEGIN STRING_STATE; CONCAT; return QUOTA; }
<STRING_STATE>\"		{ BEGIN INITIAL; CONCAT; return QUOTA;}
<STRING_STATE>[^"]*		{ CONCAT; return STR_CONST; }

 /* Number Constant */
{integer}	{ CONCAT; return I_CONST; }
{float}	    { CONCAT; return F_CONST; }

 /* C type Comment */
"/*"				{ BEGIN COMMENT; CONCAT; }
<COMMENT>[^*\n]+	{ CONCAT; }
 /* encounter \n then print the whole line, clean the buffer */
<COMMENT>\n			{ CONCAT; line_num++; printf("%d: %s", line_num, buf); memset(buf, 0, BUF_SIZE); }
<COMMENT>"*"		{ CONCAT; }
<COMMENT>"*/"		{ BEGIN INITIAL; CONCAT; }

 /* C++ type Comment */
\/\/.*	{ CONCAT; }

 /* Variable ID */
 {id}       { CONCAT; return ID; }

 /* others */

[;]         { CONCAT; return SEMICOLON; }
 /* encounter \n, there are several situation with \n */
[\n]        {   /* when there is a semantic error(the flag is from yacc),
                 * call semantic_errors to deal with the error
                 */
                if(sem_err_flag != -1){
                    semantic_errors(sem_err_flag, 0);
                    /* reset the flag */
                    sem_err_flag = -1;
                }
                /* if there is a } before \n and } is not followed by a \n(delay until the whole line is over */
                else if(strcmp(temp, "}") && rsb){
                    printf("%d: %s%s", yylineno, buf, "\n");
                    /* dump the table */
                    dump_symbol(scope);
                    strcpy(temp, "\0");
                    /* reset the rsb flag */
                    rsb = 0;
                }
                /* if there is a } before \n and it is followed by \n */
                else if(!strcmp(temp, "}")) {
                    printf("%d: %s%s", yylineno, buf, "\n");
                    /* dump the table */
                    dump_symbol(scope+1);
                    strcpy(temp, "\0");
                    /* reset rsb flag */
                    rsb = 0;
                }
                /* other normal situation */
                else{
                    CONCAT; line_num++;
                    if(!strcmp(buf, "\n")) printf("%d:\n", yylineno);
                    else printf("%d: %s", yylineno, buf); 
                }
                memset(buf, 0, BUF_SIZE);
            }
[ \t]		{ CONCAT; } /* Ignore */
[^ \t\n] 	{ CONCAT; } /* Ignore other charactor sets */
<<EOF>>     { yyterminate(); }

%%

int yywrap()
{
    return 1;
}
