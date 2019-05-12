/*	Definition section */
%{
#include <stdio.h>

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

/* Symbol table function - you can add new function if needed. */
int lookup_symbol();
void create_symbol();
void insert_symbol();
void dump_symbol();

%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    double f_val;
    char* string;
}

/* Token without return */
%token ADD SUB MUL DIV MOD INC DEC                  // Arithmetic
%token MT LT MTE LTE EQ NE                          // Relational
%token ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN // Assignment
%token AND OR NOT
%token LB RB LCB RCB LSB RSB COMMA                  // Delimiters
%token IF ELSE FOR WHILE BREAK CONT PRINT                // Conditions and loops
%token TRUE FALSE RET                               // boolean
%token ID SEMICOLON COMMENT

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STR_CONST;
%token <string> STRING INT FLOAT BOOL VOID

/* Nonterminal with return, which need to sepcify type */
%type <f_val> stat compound_statement expression_statement initializer print_func
%type <string> type 

/* Yacc will start at this nonterminal */
%start translation_unit

/* Grammar section */
%%
translation_unit
    : external_declaration
    | translation_unit external_declaration
    ;

external_declaration
    : function_definition
    | declaration
    ;

function_definition
    : declaration_specifiers declarator declaration_list compound_statement
    | declaration_specifiers declarator compound_statement
    | declarator declaration_list compound_statement
    | declarator compound_statement
    ;

declaration_specifiers
    : type_specifier
    | type_specifier declaration_specifiers
    ;

declarator
    : direct_declarator
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

compound_statement
    : '{' '}'
    | '{' statement_list '}'
    | '{' declaration_list '}'
    | '{' declaration_list statement_list '}'
    ;

direct_declarator
    : ID
    | '(' declarator ')'
    | direct_declarator '[' constant_expression ']'
    | direct_declarator '[' ']'
    | direct_declarator '(' parameter_type_list ')'
    | direct_declarator '(' identifier_list ')'
    | direct_declarator '(' ')'
    ;

declaration
    : declaration_specifiers ';'
    | declaration_specifiers init_declarator_list ';'
    ;

statement_list
    : statement
    | statement_list statement
    ;

constant_expression
    : conditional_expression
    ;

parameter_type_list
    : parameter_list
    ;

identifier_list
    : ID
    | identifier_list ',' ID
    ;

init_declarator_list
    : init_declarator
    | init_declarator_list ',' init_declarator
    ;

statement
    : compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    ;

conditional_expression
    : logical_or_expression
    | logical_or_expression '?' expression ':' conditional_expression
    ;

parameter_list
    : parameter_declaration
    | parameter_list ',' parameter_declaration
    ;

init_declarator
    : declarator
    | declarator '=' initializer
    ;

expression_statement
    : ','
    | expression ';'
    ;

selection_statement
    : IF '(' expression ')' statement
    | IF '(' expression ')' statement ELSE statement
    | SWITCH '(' expression ')' statement
    ;

iteration_statement
    : WHILE '(' expression ')' statement
    | DO statement WHILE '(' expression ')'
    | FOR '(' expression_statement expression_statement ')' statement
    | FOR '(' expression_statement expression_statement expression ')' statement
    ;

jump_statement
    : CONT ';'
    | BREAK ';'
    | RET ';'
    | RET expression ';'
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR logical_and_expression
    ;

expression
    : assignment_expression
    | expression ',' assignment_expression
    ;

parameter_declaration
    : declaration_specifiers declarator
    | declaration_specifiers
    ;

initializer
    : assignment_expression
    | '{' initializer_list '}'
    | '{' initializer_list ',' '}'
    ;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression AND inclusive_or_expression
    ;

assignment_expression
    : conditional_expression
    | unary_expression assignment_operator assignment_expression
    ;

initializer_list
    : initializer
    | initializer_list ';' initializer
    ;

inclusive_or_expression
    : exclusive_or_expression
    | inclusive_or_expression '|' exclusive_or_expression
    ;

unary_expression
    : postfix_expression
    | INC unary_expression
    | DEC unary_expression
    ;






/* actions can be taken when meet the token or rule */
type_specifier
    : INT { $$ = $1; }
    | FLOAT { $$ = $1; }
    | BOOL  { $$ = $1; }
    | STRING { $$ = $1; }
    | VOID { $$ = $1; }
;

%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    yyparse();
	printf("\nTotal lines: %d \n",yylineno);

    return 0;
}

void yyerror(char *s)
{
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void create_symbol() {}
void insert_symbol() {}
int lookup_symbol() {}
void dump_symbol() {
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
}
