/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

int err_flag = 0;
int scope_num = 0;

struct symbols{
    char name[50];
    char kind[50];
    char type[50];
    int scope;
    char attribute[50];
    int printed;
    int symbol_num;

    struct symbols *next;
};

struct symbols table[200];

/* Symbol table function - you can add new function if needed. */
int lookup_symbol();
void create_symbol();
void insert_symbol();
void dump_symbol();
void semantic_errors();

%}

/* Use variable or self-defined structure to represent
 * nonterminal and token type
 */
%union {
    int i_val;
    double f_val;
    char* string;
    _Bool b_val;
}

/* Token without return */
%token ADD SUB MUL DIV MOD INC DEC                  // Arithmetic
%token MT LT MTE LTE EQ NE                          // Relational
%token ASGN ADDASGN SUBASGN MULASGN DIVASGN MODASGN // Assignment
%token AND OR NOT                                   // Logical
%token LB RB LCB RCB LSB RSB COMMA                  // Delimiters
%token IF ELSE FOR WHILE BREAK CONT PRINT           // Conditions and loops
%token RET QUOTA                                    // boolean
%token ID SEMICOLON C_COMMENT CPLUS_COMMENT

/* Token with return, which need to sepcify type */
%token <i_val> I_CONST
%token <f_val> F_CONST
%token <string> STR_CONST;
%token <string> STRING INT FLOAT BOOL VOID 
%token <b_val> TRUE FALSE

/* Nonterminal with return, which need to sepcify type */
// %type <f_val> stat compound_statement expression_statement initializer print_func
%type <string> type_specifier declaration_specifiers declarator declaration init_declarator_list init_declarator
%type <string> function_definition parameter_list parameter_declaration

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
    | declaration_specifiers declarator compound_statement  { char *temp; 
                                                            temp = strtok($2, ":");
                                                            $2 = temp;
                                                            temp = strtok(NULL, ":");
                                                            printf("lookup %s %d\n", $2, lookup_symbol($2, scope_num));
                                                            if(lookup_symbol($2, scope_num)){
                                                                // redeclared function
                                                                semantic_errors(1);
                                                            }
                                                            else insert_symbol($2, "function", $1, scope_num, temp); 
                                                            }
    | declarator declaration_list compound_statement
    | declarator compound_statement
    ;

declaration_specifiers
    : type_specifier    { $$ = $1; }
    | type_specifier declaration_specifiers { ; }
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

compound_statement
    : LCB RCB
    | LCB in_scope statement_list RCB out_scope
    | LCB in_scope declaration_list RCB out_scope
    | LCB in_scope declaration_list statement_list RCB out_scope
    ;

declarator
    : ID                { $$ = strdup(yytext); }
    | LB declarator RB  { ; }
    | declarator LSB conditional_expression RSB
    | declarator LSB RSB
    | declarator LB in_scope parameter_list RB out_scope { strcat($$, ":"); strcat($$, $4); }
    | declarator LB in_scope identifier_list RB out_scope
    | declarator LB RB
    ;

in_scope
    : { scope_num++; }
    ;

out_scope
    : { scope_num--; }
    ;

declaration
    : declaration_specifiers SEMICOLON
    | declaration_specifiers init_declarator_list SEMICOLON     {   printf("lookup %s %d\n", $2, lookup_symbol($2, scope_num)); 
                                                                    if(lookup_symbol($2, scope_num)){
                                                                        // redeclared variable
                                                                        semantic_errors(0);
                                                                    }
                                                                    else insert_symbol($2, "variable", $1, scope_num, "NULL");
                                                                }
    ;

statement_list
    : statement
    | statement_list statement
    ;

identifier_list
    : ID
    | identifier_list COMMA ID
    ;

init_declarator_list
    : init_declarator                               { $$ = $1; }
    | init_declarator_list COMMA init_declarator    { ; }
    ;

statement
    : compound_statement
    | expression_statement
    | selection_statement
    | iteration_statement
    | jump_statement
    | print_statement
    ;

conditional_expression
    : logical_or_expression
    ;

parameter_list
    : parameter_declaration { $$ = $1; }
    | parameter_list COMMA parameter_declaration    { $$ = strcat($1, ", "); $$ = strcat($$, $3); }
    ;

init_declarator
    : declarator                    { $$ = $1; }
    | declarator ASGN initializer   { $$ = $1; }
    ;

expression_statement
    : COMMA
    | expression SEMICOLON
    ;

selection_statement
    : IF LB expression RB statement
    | IF LB expression RB statement ELSE statement
    ;

iteration_statement
    : WHILE LB expression RB statement
    | FOR LB expression_statement expression_statement RB statement
    | FOR LB expression_statement expression_statement expression RB statement
    ;

jump_statement
    : CONT SEMICOLON
    | BREAK SEMICOLON
    | RET SEMICOLON
    | RET expression SEMICOLON
    ;

print_statement
    : PRINT LB ID RB SEMICOLON
    | PRINT LB QUOTA STR_CONST QUOTA RB SEMICOLON
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR logical_and_expression
    ;

expression
    : assignment_expression
    | expression COMMA assignment_expression
    ;

parameter_declaration
    : declaration_specifiers declarator {   printf("lookup %s %d\n", $2, lookup_symbol($2, scope_num)); 
                                            if(lookup_symbol($2, scope_num)){

                                            }
                                            else insert_symbol($2, "parameter", $1, scope_num, "NULL"); 
                                            $$ = $1; 
                                        }
    | declaration_specifiers
    ;

initializer
    : assignment_expression
    | LCB initializer_list RCB
    | LCB initializer_list COMMA RCB
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
    | initializer_list SEMICOLON initializer
    ;

inclusive_or_expression
    : exclusive_or_expression
    ;

unary_expression
    : postfix_expression
    | INC unary_expression
    | DEC unary_expression
    | unary_operator unary_expression
    ;

assignment_operator
    : ASGN
    | ADDASGN
    | SUBASGN
    | MULASGN
    | DIVASGN
    | MODASGN
    ;

exclusive_or_expression
    : and_expression
    ;

postfix_expression
    : primary_expression
    | postfix_expression LSB expression RSB
    | postfix_expression LB RB
    | postfix_expression LB argument_expression_list RB
    | postfix_expression INC
    | postfix_expression DEC
    ;

unary_operator
    : ADD
    | SUB
    | NOT
    ;

and_expression
    : equality_expression
    ;

primary_expression
    : ID
    | I_CONST
    | F_CONST
    | QUOTA STR_CONST QUOTA
    | TRUE
    | FALSE
    | LB expression RB
    ;

argument_expression_list
    : assignment_expression
    | argument_expression_list COMMA assignment_expression
    ;

equality_expression
    : relational_expression
    | equality_expression EQ relational_expression
    | equality_expression NE relational_expression
    ;

relational_expression
    : additive_expression
    | relational_expression LT additive_expression
    | relational_expression MT additive_expression
    | relational_expression LTE additive_expression
    | relational_expression MTE additive_expression
    ;

additive_expression
    : multiplicative_expression
    | additive_expression ADD multiplicative_expression
    | additive_expression SUB multiplicative_expression
    ;

multiplicative_expression
    : unary_expression
    | multiplicative_expression MUL unary_expression
    | multiplicative_expression DIV unary_expression
    | multiplicative_expression MOD unary_expression
    ;

/* actions can be taken when meet the token or rule */
type_specifier
    : INT   { $$ = strdup(yytext); }
    | FLOAT { $$ = strdup(yytext); }
    | BOOL  { $$ = strdup(yytext); }
    | STRING { $$ = strdup(yytext); }
    | VOID  { $$ = strdup(yytext); }
;

%%

/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;
    create_symbol();
    yyparse();
    dump_symbol(0);
    if(!err_flag) printf("\nTotal lines: %d \n",yylineno);

    return 0;
}

void yyerror(char *s)
{
    err_flag = 1;
    printf("%d: %s\n", yylineno+1, buf);
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", ++yylineno, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
}

void create_symbol() {
    int i;
    for(i = 0; i < 200; i++){
        table[i].next = NULL;
        table[i].scope = 0;
        table[i].printed = -1;
        table[i].symbol_num = 0;
    }
}

void insert_symbol(char *name, char *kind, char *type, int scope, char *attribute) {
    struct symbols *temp, *new_symbol;

    temp = &table[scope];
    while(temp->next != NULL){
        temp = temp->next;
    }

    new_symbol = (struct symbols *)malloc(sizeof(struct symbols));
    strcpy(new_symbol->name, name);
    strcpy(new_symbol->kind, kind);
    strcpy(new_symbol->type, type);
    if(attribute == NULL || !strcmp(attribute, "NULL")) strcpy(new_symbol->attribute, "\0");
    else strcpy(new_symbol->attribute, attribute);
    new_symbol->scope = scope;
    new_symbol->printed = -1;
    new_symbol->next = NULL;
    temp->next = new_symbol;
    table[scope].symbol_num++;
}

int lookup_symbol(char *id, int scope) {
    if(table[scope].symbol_num == 0) return 0;
    struct symbols *temp = &table[scope];
    temp = temp->next;

    int existed = 0;
    while(temp->next != NULL){
        if(!strcmp(temp->name, id)){
            existed = 1;
            break;
        }
        temp = temp->next;
    }

    return existed;
}

void dump_symbol(int scope) {
    if(table[scope].symbol_num == 0){
        
        return;
    }
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    struct symbols *temp = &table[scope];
    int count = table[scope].printed;

    temp = temp->next;
    int i = 0, index = 0;
    while(temp != NULL){
        if(i >= count){
            printf("%-10d%-10s%-12s%-10s%-10d", index++, temp->name, temp->kind, temp->type, temp->scope);
            if(strcmp(temp->attribute, "\0"))    printf("%s\n", temp->attribute);
            else printf("\n");
        }
        
        temp = temp->next;
        i++;
    }
    printf("\n");
    
    table[scope].printed = i;
    // printf("print from %d\n", table[scope].printed);
}

void semantic_errors(int kind_of_error){
    switch(kind_of_error){
        case 0:                 // redeclared variable

            break;
        case 1:                 // redeclared function

            break;
        case 2:                 // undeclared variable

            break;
        case 3:                 // undeclared function

            break;
        default:;
    }
}