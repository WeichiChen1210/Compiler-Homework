/*	Definition section */
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[256];  // Get current code line from lex

int sem_err_flag = -1;
int syn_err_flag = 0;
char error_id[50];
int scope_num = 0;

char constants[50] = "NULL";

FILE *file; // To generate .j file for Jasmin

struct symbols{
    int index;
    char value[50];
    char name[50];
    char kind[50];
    char type[50];
    int scope;
    char attribute[50];
    int printed;
    int symbol_num;
    int defined;

    struct symbols *next;
};

struct functions{
    int index;
    char name[50];
    char type[50];
    char attribute[50];

    struct functions *next;
};

struct id_data{
    char id[50];
    char value[100];
} id_struct;

struct func_data{
    char id[50];
    char type[10];
} func_struct;

struct symbols table[20];
struct functions *func_table;

void yyerror(char *s);

/* Symbol table function - you can add new function if needed. */
int lookup_symbol(char *id, int scope, int mode);
void create_symbol();
void insert_symbol(char *name, char *kind, char *type, int scope, char *attribute, char *value);
void insert_function(char* name, char* type, char* attribute);
void dump_symbol(int scope);
void semantic_errors(int kind_of_error, int offset);    // print semantic errors messages
void delete_parameter_symbol(int scope);                // delete the parameter of forwarding function
void fill_parameter(int scope, char *id, char *attribute);  // refill the parameters to forwarding functions
void free_symbol_table();
void search_type(char* id, int scope, char* result);
int search_index(char* id, int scope);
void analyze_parameters(char* attribute);
/* generate jasmin code */
void gencode_function(char* input);
char* casting(char* value, int type);
void j_global_var_declaration(char* id, char* value, char* constant_type);
void j_local_var_declaration(char* id, char* value, char* constant_type);
void j_func_declaration(char* id, char* return_type, char* parameters);
void j_func_call(char* id, char* parameter);
void j_print(char* item, char *type);

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
%type <string> type_specifier declaration_specifiers direct_declarator declarator func_declarator declaration init_declarator_list init_declarator initializer
%type <string> function_definition parameter_list parameter_declaration
%type <string> postfix_expression primary_expression unary_expression multiplicative_expression
%type <string> additive_expression relational_expression equality_expression  and_expression inclusive_or_expression exclusive_or_expression
%type <string> logical_and_expression logical_or_expression conditional_expression assignment_expression
%type <string> initializer_list id_stat print_statement statement argument_expression_list
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
    /* normal function declaration and definition */
    | declaration_specifiers func_declarator    {   /* split the string that contains ID and parameter list */
                                                    char *temp; 
                                                    temp = strtok($2, ":");
                                                    /* ID */
                                                    $2 = temp;
                                                    printf("%s\n", $2);
                                                    /* parameters */
                                                    temp = strtok(NULL, ":");
                                                    /* lookup */
                                                    int result = lookup_symbol($2, scope_num, 1);
                                                    /* if return 2, it is a forwarding function(encountered at the 2nd time) */
                                                    if(result == 2){
                                                        /* refill the attribute with the ID and parameter list */
                                                        fill_parameter(scope_num, $2, temp);
                                                    }
                                                    /* if return 1, redeclared function*/
                                                    else if(result){
                                                        // redeclared function
                                                        /* set semantic error flag and lex will call the semantic function */
                                                        sem_err_flag = 1;
                                                        /* save the ID to use in semantic function */
                                                        strcpy(error_id, $2);
                                                    }
                                                    /* return 0, new function, insert the symbol */
                                                    else {
                                                        printf("func decl %s %s %s\n", $1, $2, temp);
                                                        strcpy(func_struct.id, $2);
                                                        strcpy(func_struct.type, $1);
                                                        j_func_declaration($2, $1, temp);
                                                        insert_symbol($2, "function", $1, scope_num, temp, "NULL");
                                                        insert_function($2, $1, temp);
                                                    }    
                                                } compound_statement {  printf("%s\n", func_struct.type);
                                                                        if(!strcmp(func_struct.type, "int"))
                                                                            fprintf(file, "\tireturn\n.end method\n");
                                                                        else if(!strcmp(func_struct.type, "float"))
                                                                            fprintf(file, "\tfreturn\n.end method\n");
                                                                        else if(!strcmp(func_struct.type, "void"))
                                                                            fprintf(file, "\treturn\n.end method\n");
                                                                        strcpy(func_struct.id, "");
                                                                        strcpy(func_struct.type, "");
                                                                    }
    | declarator declaration_list compound_statement
    | declarator compound_statement
    | declaration_specifiers func_declarator SEMICOLON   {   /* forwarding function(encountered at the first time) */
                                                        char *temp;
                                                        temp = strtok($2, ":");
                                                        $2 = temp;
                                                        char notdef[15];
                                                        strcpy(notdef, "notdefined");
                                                        /* check if redeclared */
                                                        if(lookup_symbol($2, scope_num, 1)){
                                                            // redeclared function
                                                            sem_err_flag = 1;
                                                            strcpy(error_id, $2);
                                                        }
                                                        /* false, insert */
                                                        else{
                                                            insert_symbol($2, "function", $1, scope_num, notdef, "NULL");
                                                            insert_function($2, $1, "NULL");
                                                        }
                                                        /* delete the symbols of the forwarding function */
                                                        delete_parameter_symbol(scope_num+1);
                                                    }
    ;

declaration_specifiers
    : type_specifier    { $$ = $1; }
    | type_specifier declaration_specifiers { ; }
    ;

declaration_list
    : declaration
    | declaration_list declaration
    ;

block_item_list
	: block_item
	| block_item_list block_item
    ;

block_item
	: declaration_list
	| statement
	;

declarator
    : direct_declarator
    ;
func_declarator
    : direct_declarator
    ;

direct_declarator
    : ID                { $$ = strdup(yytext); }
    | LB declarator RB  { ; }
    | direct_declarator LSB conditional_expression RSB
    | direct_declarator LSB RSB
    /* attach parameters together */
    | direct_declarator LB{ scope_num++; } parameter_list RB { scope_num--; strcat($$, ":"); strcat($$, $4); }
    | direct_declarator LB{ scope_num++; } identifier_list RB{ scope_num--; }
    | direct_declarator LB RB  
    ;

declaration
    : declaration_specifiers SEMICOLON  
    | declaration_specifiers init_declarator_list SEMICOLON     {   /* variable declaration */
                                                                    int result = lookup_symbol($2, scope_num, 0);
                                                                    printf("decl %s\n", $2);
                                                                    // printf("declaration %s %s %d\n", $1, $2, scope_num);
                                                                    if(result){
                                                                        // redeclared variable
                                                                        sem_err_flag = 0;
                                                                        strcpy(error_id, $2);
                                                                    }
                                                                    else{
                                                                        /* global variable declaration */
                                                                        if(scope_num == 0){
                                                                            printf("global variable\n");
                                                                            // generate code
                                                                            j_global_var_declaration($2, constants, $1);
                                                                        }
                                                                        /* local variable declaration */
                                                                        else{
                                                                            printf("local variable\n");
                                                                            printf("decl id_struct %s %s %s\n", $1, id_struct.id, id_struct.value);
                                                                            
                                                                            j_local_var_declaration($2, id_struct.value, $1);
                                                                        }
                                                                        insert_symbol($2, "variable", $1, scope_num, "NULL", constants);
                                                                        strcpy(constants, "NULL");
                                                                    }
                                                                }
    ;

identifier_list
    : ID
    | identifier_list COMMA ID
    ;

init_declarator_list
    : init_declarator                               {   $$ = $1; 
                                                        printf("init_decl_list %s\n", $$);
                                                        printf("id_struct %s %s\n", id_struct.id, id_struct.value); 
                                                    }
    | init_declarator_list COMMA init_declarator
    ;

/* statements */
statement
    : compound_statement    {;}
    | expression_statement  {;}
    | selection_statement   {;}
    | iteration_statement   {;}
    | jump_statement        {;}
    | print_statement       {;}
    ;

compound_statement
    : LCB RCB
    | LCB{ scope_num++; } block_item_list RCB{ scope_num--; }
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
    : PRINT LB id_stat RB SEMICOLON                 {   if($3 != NULL){                 // if variable undeclared, do nothing
                                                            char type[10];
                                                            search_type(strdup($3), scope_num, type);
                                                            // printf("%s %s %d\n", $3, type, scope_num);
                                                            j_print($3, type);
                                                        }                                                        
                                                    }
    | PRINT LB QUOTA STR_CONST{ strcpy(constants, strdup(yytext)); } QUOTA RB SEMICOLON{
                                                        // printf("print %s %s %d\n", constants, "string", scope_num);
                                                        char temp[50];
                                                        sprintf(temp, "\"%s\"", constants);
                                                        j_print(temp, "string");
                                                        strcpy(constants, "NULL");
                                                    }
    | PRINT LB I_CONST{ strcpy(constants, strdup(yytext)); } RB SEMICOLON{
                                                        // printf("print %s %s %d\n", constants, "int", scope_num);
                                                        j_print(constants, "int");
                                                        strcpy(constants, "NULL");
                                                    }
    | PRINT LB F_CONST{ strcpy(constants, strdup(yytext));} RB SEMICOLON{
                                                        // printf("print %s %s %d\n", constants, "float", scope_num);
                                                        j_print(constants, "float");
                                                        strcpy(constants, "NULL");
                                                    }
    ;

conditional_expression
    : logical_or_expression { $$ = $1; /*printf("condi %s\n", $$);*/ }
    ;

parameter_list
    : parameter_declaration { $$ = $1; }
    /* attach parameters */
    | parameter_list COMMA parameter_declaration    { $$ = strcat($1, ", "); $$ = strcat($$, $3); }
    ;

init_declarator
    : declarator                    {   $$ = $1; printf("init_declarator %s\n", $1);
                                        strcpy(id_struct.id, $1);
                                        strcpy(id_struct.value, "NULL");
                                    }
    | func_declarator               { $$ = $1; }
    | declarator ASGN initializer   {   char temp[100];
                                        strcpy(temp, strdup($3));
                                        char c = temp[0];
                                        // asign to one item
                                        if(c != '+' && c != '-' && c != '*' && c != '/' && c != '%'){
                                            $$ = $1; 
                                            printf("init_declarator %s\n", $3);
                                            strcpy(id_struct.id, $1);
                                            strcpy(id_struct.value, $3);
                                        }
                                        else{
                                            printf("add %s\n", $3);
                                            $$ = $3;
                                        }
                                        
                                    }
    ;

id_stat
    : ID    {   if(!lookup_symbol(yytext, scope_num, 1)){
                    sem_err_flag = 2;
                    strcpy(error_id, yytext);
                }
                else{
                    $$ = strdup(yytext);
                }
            }
    ;

logical_or_expression
    : logical_and_expression    { $$ = $1; /*printf("logi or %s\n", $$);*/ }
    | logical_or_expression OR logical_and_expression
    ;

expression
    : assignment_expression     { ; }
    | expression COMMA assignment_expression
    ;

parameter_declaration
    : declaration_specifiers declarator {   /* check parameter*/
                                            if(!lookup_symbol($2, scope_num, 0))
                                                insert_symbol($2, "parameter", $1, scope_num, "NULL", "NULL");
                                            $$ = $1; 
                                        }
    | declaration_specifiers
    ;

initializer
    : assignment_expression             { $$ = $1; printf("initializer %s\n", $$); }
    | LCB initializer_list RCB          {;}
    | LCB initializer_list COMMA RCB    {;}
    ;

logical_and_expression
    : inclusive_or_expression   { $$ = $1; /*printf("logic and %s\n", $$);*/ }
    | logical_and_expression AND inclusive_or_expression
    ;

assignment_expression
    : conditional_expression    { $$ = $1; printf("assign %s\n", $$); }
    | unary_expression assignment_operator assignment_expression    { ; }
    ;

initializer_list
    : initializer
    | initializer_list SEMICOLON initializer
    ;

inclusive_or_expression
    : exclusive_or_expression   { $$ = $1; /*printf("incl %s\n", $$);*/ }
    ;

unary_expression
    : postfix_expression        { $$ = $1; /*printf("unary %s\n", $$);*/ }
    | INC unary_expression      {}
    | DEC unary_expression      {}
    | unary_operator unary_expression   {}
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
    : and_expression            { $$ = $1; /*printf("excl %s\n", $$);*/ }
    ;

postfix_expression
    : primary_expression        {   /* check ID declared or not */
                                    if($1 != NULL) {
                                        printf("prim %s\n", $1);
                                        char temp[50];
                                        strcpy(temp, $1);
                                        int len = strlen(temp);
                                        /* passing constants end with '/' */
                                        if(temp[len-1] == '/'){
                                            temp[len-1] = '\0';
                                            $$ = temp;
                                            len = strlen(constants);
                                        }
                                        else if(!lookup_symbol($1, scope_num, 1)){
                                            // undeclared variable
                                            sem_err_flag = 2;
                                            strcpy(error_id, $1);
                                        }
                                    }                               
                                }
    | postfix_expression LSB expression RSB
    | postfix_expression LB RB
    | postfix_expression LB argument_expression_list RB {   /* check function name declared or not */
                                                            if($1 != NULL) {
                                                                if(!lookup_symbol($1, scope_num, 3)){
                                                                    // undeclared function
                                                                    sem_err_flag = 3;
                                                                    strcpy(error_id, $1);
                                                                }
                                                            }
                                                            if($3 != NULL){
                                                                // printf("post %s\n", $3);
                                                                j_func_call(strdup($1), strdup($3));
                                                            }
                                                        }
    | postfix_expression INC
    | postfix_expression DEC
    ;

unary_operator
    : ADD
    | SUB
    | NOT
    ;

and_expression
    : equality_expression       { $$ = $1; /*printf("and %s\n", $$);*/ }
    ;

primary_expression
    : ID                        { $$ = strdup(yytext); }
    | I_CONST                   {   strcpy(constants, strdup(yytext));
                                    printf("%s\n", constants);
                                    char temp[50];
                                    sprintf(temp, "%s/", strdup(yytext));
                                    $$ = temp;
                                }
    | F_CONST                   {   strcpy(constants, strdup(yytext));
                                    printf("%s\n", constants);
                                    char temp[50];
                                    sprintf(temp, "%s/", strdup(yytext));
                                    $$ = temp;
                                }
    | QUOTA STR_CONST{  printf("%s\n", strdup(yytext)); 
                        sprintf(constants, "%s/", strdup(yytext));                        
                    }   QUOTA   {   
                                    $$ = constants;
                                    // printf("%s\n", $$);
                                }
    | TRUE                      {   strcpy(constants, "true/");
                                    $$ = strdup(constants);
                                }
    | FALSE                     {   strcpy(constants, "false/");
                                    $$ = strdup(constants);
                                }
    | LB expression RB          { ; }
    ;

argument_expression_list
    : assignment_expression {   // printf("ass argu %s\n", $1);
                                $$ = $1;    
                            }
    | argument_expression_list COMMA assignment_expression  {   // printf("argu 2 %s %s\n", $1, $3);
                                                                $$ = $1;
                                                                strcat($$, ":");
                                                                strcat($$, strdup($3));
                                                                // printf("argu 2 %s\n", $$);
                                                            }
    ;

equality_expression
    : relational_expression                             { $$ = $1; /*printf("equal %s\n", $$);*/ }
    | equality_expression EQ relational_expression
    | equality_expression NE relational_expression
    ;

relational_expression
    : additive_expression                               { $$ = $1; /*printf("rel %s\n", $$);*/ }
    | relational_expression LT additive_expression
    | relational_expression MT additive_expression
    | relational_expression LTE additive_expression
    | relational_expression MTE additive_expression
    ;

additive_expression
    : multiplicative_expression                         { $$ = $1; /*printf("add %s\n", $$);*/ }
    | additive_expression ADD multiplicative_expression {   char item1[50];
                                                            strcpy(item1, strdup($1));
                                                            char item2[50];
                                                            strcpy(item2, strdup($3));
                                                            char combine[100];
                                                            sprintf(combine, "+ %s %s", item1, item2);
                                                            printf("here %s\n", combine);
                                                            $$ = combine;
                                                        }
    | additive_expression SUB multiplicative_expression
    ;

multiplicative_expression
    : unary_expression                                  { $$ = $1; /*printf("mul %s\n", $$);*/ }
    | multiplicative_expression MUL unary_expression
    | multiplicative_expression DIV unary_expression
    | multiplicative_expression MOD unary_expression
    ;

/* actions can be taken when meet the token or rule */
/* types */
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
    
    file = fopen("compiler_hw3.j","w");
    fprintf(file,   ".class public compiler_hw3\n"
                    ".super java/lang/Object\n");
    
    create_symbol();
    yyparse();
    /* if there is a syntax error, don't print the last line */
    if(!syn_err_flag){
        dump_symbol(0);
        printf("\nTotal lines: %d \n",yylineno);
    }

    fclose(file);

    return 0;
}

void yyerror(char *s)
{
    /* check if there is a semantic error first */
    if(sem_err_flag == -1)
        printf("%d: %s\n", yylineno+1, buf);
    else semantic_errors(sem_err_flag, 1);
    
    syn_err_flag = 1;
    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno+1, buf);
    printf("| %s", s);
    printf("\n|-----------------------------------------------|\n\n");
    exit(-1);
}

/* stmbol table functions */
/* initialize the table */
void create_symbol() {
    int i;
    for(i = 0; i < 20; i++){
        strcpy(table[i].name, "HEAD");
        table[i].next = NULL;
        table[i].scope = 0;
        table[i].printed = -1;
        table[i].symbol_num = 0;
        table[i].defined = -1;
    }
    func_table = (struct functions *)malloc(sizeof(struct functions));
    strcpy(func_table->name, "HEAD");
    strcpy(func_table->type, "NULL");
    strcpy(func_table->attribute, "NULL");
    func_table->index = -1;
    func_table->next = NULL;

}

/* insert symbols */
void insert_symbol(char *name, char *kind, char *type, int scope, char *attribute, char *value) {
    struct symbols *temp, *new_symbol;

    /* traversal to the last symbol */
    temp = &table[scope];
    while(temp->next != NULL){
        temp = temp->next;
    }
    
    /* setting the new symbol */
    new_symbol = (struct symbols *)malloc(sizeof(struct symbols));
    strcpy(new_symbol->name, name);
    strcpy(new_symbol->kind, kind);
    strcpy(new_symbol->type, type);
    
    if(!strcmp(value, "NULL")) strcpy(new_symbol->value, "\0");
    else    strcpy(new_symbol->value, value);
    
    /* some situations for attribute */
    if(attribute == NULL || !strcmp(attribute, "NULL")){
        // variable
        strcpy(new_symbol->attribute, "\0");
        new_symbol->defined = 1;
    }
    // function forwarding, undefined
    else if(!strcmp(attribute, "notdefined"))   new_symbol->defined = 0;
    else {
        // function defined and parameter
        strcpy(new_symbol->attribute, attribute);
        new_symbol->defined = 1;
    }
    new_symbol->index = table[scope].symbol_num;
    new_symbol->scope = scope;
    new_symbol->printed = -1;
    new_symbol->next = NULL;
    temp->next = new_symbol;
    table[scope].symbol_num++;

}

/* insert new function to function table */
void insert_function(char* name, char* type, char* attribute){
    struct functions *temp, *new_function;

    temp = func_table;
    while(temp->next != NULL)
        temp = temp->next;
    
    new_function = (struct functions *)malloc(sizeof(struct functions));
    strcpy(new_function->name, name);

    if(!strcmp(type, "int"))    strcpy(new_function->type, "I");
    else if(!strcmp(type, "float")) strcpy(new_function->type, "F");
    else if(!strcmp(type, "void"))  strcpy(new_function->type, "V");
    
    if(attribute == NULL) strcpy(new_function->attribute, "[Ljava/lang/String;");
    else {
        analyze_parameters(attribute);
        strcpy(new_function->attribute, attribute);
    }

    new_function->index = temp->index + 1;
    new_function->next = NULL;
    temp->next = new_function;

    // struct functions *temp1;
    // temp1 = func_table;
    // while(temp1 != NULL){
    //     printf("%d %s %s %s\n", temp1->index, temp1->name, temp1->type, temp1->attribute);
    //     temp1 = temp1->next;
    // }
}

/* lookup symbols from scope up to 0 */
int lookup_symbol(char *id, int scope, int mode) {  // mode 0: redeclared variable 1: undeclared variable
                                                    //      2: redeclared function 3: undeclared function
    struct symbols *temp;
    int existed = 0, cur_scope = scope;

    if(!mode || mode == 2){
        temp = &table[scope];
        if(table[scope].symbol_num == 0){
            existed = 0;
        }
        else {
            while(temp != NULL){
                /* if this is a variable already existed */
                if(!strcmp(temp->name, id)){
                    existed = 1;
                    break;
                }
                temp = temp->next;
            }
        }
    }
    else if(mode || mode == 3){
        while(scope >= 0){
            temp = &table[scope];
            if(table[scope].symbol_num == 0){
                scope--;
                continue;
            }
            while(temp != NULL){
                if(!strcmp(temp->name, id)){
                    /* if this is a function name and it is undfined */
                    if(!temp->defined) existed = 2;  
                    else existed = 1;
                    break;
                }
                temp = temp->next;
            }
            scope--;
            if(existed) break;
        }
    }
    // return 0: not exist 1: exist 2: forwarding
    return existed;
}

/* lookup function table to get the id's type and attribute */
void lookup_function(char* id, char* type, char* attribute){
    struct functions *temp;
    temp = func_table;
    while(temp != NULL){
        if(!strcmp(temp->name, id)){
            strcpy(type, temp->type);
            strcpy(attribute, temp->attribute);
            break;
        }
        temp = temp->next;
    }
}

/* dump symbols */
void dump_symbol(int scope) {
    /* if there is not symbol in this scope, return */
    if(table[scope].symbol_num == 0)    return;
    
    printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
           "Index", "Name", "Kind", "Type", "Scope", "Attribute");
    
    /* traversal and print */
    int i = 0, index = 0;
    while(table[scope].next != NULL){
        struct symbols *temp = &table[scope];
        temp = temp->next;

        printf("%-10d%-10s%-12s%-10s%-10d", index++, temp->name, temp->kind, temp->type, temp->scope);
        if(strcmp(temp->attribute, "\0"))    printf("%s\n", temp->attribute);
        else printf("\n");
        /* after printed, delete and free */
        table[scope].next = temp->next;
        free(temp);
        i++;
    }
    printf("\n");
    table[scope].symbol_num = 0;
}

/* semantic error */
void semantic_errors(int kind_of_error, int offset){
    int line = yylineno + offset;
    switch(kind_of_error){
        case 0:                 // redeclared variable
            printf("%d: %s\n", line, buf);
            printf("\n|-----------------------------------------------|\n");
            printf("| Error found in line %d: %s\n", line, buf);
            printf("| Redeclared variable %s", error_id);
            printf("\n|-----------------------------------------------|\n\n");
            break;
        case 1:                 // redeclared function
            printf("%d: %s\n", line, buf);
            printf("\n|-----------------------------------------------|\n");
            printf("| Error found in line %d: %s\n", line, buf);
            printf("| Redeclared function %s", error_id);
            printf("\n|-----------------------------------------------|\n\n");
            break;
        case 2:                 // undeclared variable
            printf("%d: %s\n", line, buf);
            printf("\n|-----------------------------------------------|\n");
            printf("| Error found in line %d: %s\n", line, buf);
            printf("| Undeclared variable %s", error_id);
            printf("\n|-----------------------------------------------|\n\n");
            break;
        case 3:                 // undeclared function
            printf("%d: %s\n", line, buf);
            printf("\n|-----------------------------------------------|\n");
            printf("| Error found in line %d: %s\n", line, buf);
            printf("| Undeclared function %s", error_id);
            printf("\n|-----------------------------------------------|\n\n");
            break;
        default:;
        sem_err_flag = -1;
    }
}

/* delete the parameter */
void delete_parameter_symbol(int scope) {
    /* traversal and delete the symbols of the forwading function */
    while(table[scope].next != NULL){
        struct symbols *temp = &table[scope];
        temp = temp->next;

        table[scope].next = temp->next;
        free(temp);
    }
    table[scope].symbol_num = 0;
}

/* fill the attribute to the undefined function */
void fill_parameter(int scope, char *id, char *attribute) {
    struct symbols *temp = &table[scope];
    temp = temp->next;
    
    while(temp != NULL){
        if(!strcmp(temp->name, id)){
            strcpy(temp->attribute, attribute);
            temp->defined = 1;
            break;
        }
        temp = temp->next;        
    }
}

/* lookup symbol table to find the type of the variable */
void search_type(char* id, int scope, char* result){
    struct symbols *temp;

    int found = 0;
    while(scope >= 0){
        temp = &table[scope];
        if(table[scope].symbol_num > 0){
            while(temp != NULL){
                /* if this is a variable already existed */
                if(!strcmp(temp->name, id)){
                    // printf("find type %s\n", temp->type);
                    strcpy(result, temp->type);
                    found = 1;
                    break;
                }
                temp = temp->next;
            }
        }
        if(found)   break;
        scope--;
    }
}

/* lookup symbol table to find the index of the variable */
int search_index(char* id, int scope){  // return > 0: local; == -1, global
    struct symbols *temp;
    int found = 0, index;

    while(scope > 0){
        temp = &table[scope];
        if(table[scope].symbol_num > 0){
            while(temp != NULL){
                /* if this is a variable already existed */
                if(!strcmp(temp->name, id)){
                    // printf("find index %d\n", temp->index);
                    index = temp->index;
                    found = 1;  // in local
                    break;
                }
                temp = temp->next;
            }
        }
        if(found) break;
        scope--;
    }
    /* variable in global */
    if(!found)  index = -1;
    return index;
}

/* analyze the types of parameters */
void analyze_parameters(char* attribute){
    char temp[50];
    strcpy(temp, attribute);
    strcpy(attribute, "");
    char *delim = " ";
    char *pch;
    pch = strtok(temp, delim);
    while(pch != NULL){
        printf("%s\n", pch);
        if(!strcmp(pch, "int") || !strcmp(pch, "int,")){
            strcat(attribute, "I");
        }
        else if(!strcmp(pch, "float") || !strcmp(pch, "float,")){
            strcat(attribute, "F");
        }
        else if(!strcmp(pch, "string") || !strcmp(pch, "string,")){
            strcat(attribute, "Ljava/lang/String;");
        }
        pch = strtok(NULL, delim);
    }
    printf("after %s\n", attribute);
}

/* code generation functions */
void gencode_function(char* input) {
    fputs(input, file);
}

/* handle casting */
char* casting(char* value, int type){
    int i;
    if(type == 0){   // int
        // check if there is a dot
        for(i = 0; i < strlen(value); i++){
            if(value[i] == '.') {   // if yes, change to int
                value[i] = '\0';
                break;
            }
        }
    }
    else{           // float
        int dot = 0;
        // check if there is a dot
        for(i = 0; i < strlen(value); i++){
            if(value[i] == '.') {   // if yes, dot = 1
                dot = 1;
                break;
            }
        }
        if(!dot){   // if there is no dot, add .0 to it
            strcat(value, ".0\0");
        }
    }
    return value;
    
}

/* generating the variable declaration */
void j_global_var_declaration(char* id, char *value, char* constant_type){
    char output[100];
    /* classify with variable type */
    if(!strcmp(constant_type, "int")){
        if(!strcmp(value, "NULL")){
            sprintf(output, ".field public static %s I = 0\n", id); // not initialized, assign 0
            gencode_function(output);      
        }
        /* check type casting */
        else{
            casting(value, 0);
            sprintf(output, ".field public static %s I = %s\n", id, value);
            gencode_function(output);
        }
    }
    else if(!strcmp(constant_type, "float")){
        if(!strcmp(value, "NULL")){
            sprintf(output, ".field public static %s F = 0.0\n", id);
            gencode_function(output);
        }
        else{
            /* check type casting */
            casting(value, 1);
            sprintf(output, ".field public static %s F = %s\n", id, value);
            gencode_function(output);
        }
    }
    else if(!strcmp(constant_type, "string")){
        char temp[50];
        int len = strlen(value);
        value[len-1] = '\0';    // take out the last '/'
        sprintf(temp, "\"%s\"", value); // add ""
        sprintf(output, ".field public static %s Ljava/lang/String; = %s\n", id, temp);
        gencode_function(output);
        strcpy(value, temp);
    }
    else if(!strcmp(constant_type, "bool")){        
        if(!strcmp(value, "NULL"))   fprintf(file, ".field public static %s Z = 1\n", id);  // not initialize
        int len = strlen(value);
        value[len-1] = '\0';    // take out the last '/'
        if(!strcmp(value, "true")) sprintf(output, ".field public static %s Z = 1\n", id);
        else sprintf(output, ".field public static %s Z = 0\n", id);
        gencode_function(output);
    }
}


void j_local_var_declaration(char* id, char *value, char* constant_type){
    printf("local %s %s %s\n", constant_type, id, value);
    return;
}

void j_func_declaration(char* id, char* return_type, char* parameters){
    char out_str[200];
    char para_type[50];
    char ret_type[10];
    /* parameters */
    if(parameters != NULL){
        strcpy(para_type, parameters);        
        analyze_parameters(para_type);
    }
    else    strcpy(para_type, "[Ljava/lang/String;");
    /* return type */
    if(!strcmp(return_type, "int")) strcpy(ret_type, "I");
    else if(!strcmp(return_type, "float"))  strcpy(ret_type, "F");
    else if(!strcmp(return_type, "void"))   strcpy(ret_type, "V");

    sprintf(out_str, ".method public static %s(%s)%s\n.limit stack 50\n.limit locals 50\n", id, para_type, ret_type);
    // printf("%s\n", out_str);
    gencode_function(out_str);
}

void j_func_call(char* id, char* parameter){
    char out_str[300];
    strcpy(out_str, "");
    // printf("in func %s %s\n", id, parameter);
    /* analyze the parameters */
    char temp[50];
    strcpy(temp, parameter);
    char *delim = ":";
    char *name;
    name = strtok(temp, delim);
    char tmp_str[150];
    while(name != NULL){
        // printf("name %s\n", name);
        /* constants */
        if(isdigit(name[0])){
            sprintf(tmp_str, "\tldc %s\n", name);
        }
        /* variable */
        else{
            // printf("variable %d\n", scope_num);
            /* local */
            int index = search_index(name, scope_num);
            char type[10];
            search_type(name, scope_num, type);
            if(index >= 0){
                if(!strcmp(type, "int")){   // int
                    sprintf(tmp_str, "\tiload %d\n", index);
                }
                else if(!strcmp(type, "float")){    // float
                    sprintf(tmp_str, "\tfload %d\n", index);
                }
            }
            /* global */
            else{
                if(!strcmp(type, "int")){   // int
                    sprintf(tmp_str, "\tgetstatic compiler_hw3/%s I\n", name);
                }
                else if(!strcmp(type, "float")){    // float
                    sprintf(tmp_str, "\tgetstatic compiler_hw3/%s F\n", name);
                }
            }
        }
        strcat(out_str, tmp_str);
        name = strtok(NULL, delim);
    }
    /* get attribute and return type */
    char attribute[10];
    char ret_type[10];
    lookup_function(id, ret_type, attribute);
    sprintf(tmp_str, "\tinvokestatic compiler_hw3/%s(%s)%s\n", id, attribute, ret_type);
    strcat(out_str, tmp_str);
    gencode_function(out_str);
}

/* generating the print statement */
void j_print(char* item, char *type){
    char out_str[200];

    /* print string constants */
    if(item[0] == '\"' && !strcmp(type, "string")){
        sprintf(out_str, "ldc %s\ngetstatic java/lang/System/out Ljava/io/PrintStream;\nswap\ninvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n", item);
    }
    /* print variable */
    else if(!isdigit(item[0])){
        int index = search_index(item, scope_num);      // get index
        // printf("index %d\n", index);
        if(index >= 0){    // local
            if(!strcmp(type, "int")){
                sprintf(out_str, "\tiload %d\n\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(I)V\n", index);
            }
            else if(!strcmp(type, "float")){
                sprintf(out_str, "\tfload %d\n\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(F)V\n", index);
            }
            else if(!strcmp(type, "string")){
                sprintf(out_str, "\taload %d\n\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n", index);
                gencode_function(out_str);
            }
        }
        else{       // global
            if(!strcmp(type, "int")){
                sprintf(out_str, "\tgetstatic compiler_hw3/%s I\n\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(I)V\n", item);
            }
            else if(!strcmp(type, "float")){
                sprintf(out_str, "\tgetstatic compiler_hw3/%s F\n\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(F)V\n", item);
            }
            else if(!strcmp(type, "string")){
                sprintf(out_str, "\tgetstatic compiler_hw3/%s Ljava/lang/String;\n\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n", item);
            }
        }

    }
    /* print number constants */
    else{
        if(!strcmp(type, "int")){
            sprintf(out_str, "\tldc %s\n\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(I)V\n", item);
        }
        else if(!strcmp(type, "float")){
            sprintf(out_str, "\tldc %s\n\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n\tinvokevirtual java/io/PrintStream/println(F)V\n", item);
       }
    }
    gencode_function(out_str);
}

int is_float(char* num){
    int result = 0;
    char temp[20];
    strcpy(temp, num);
    int i;
    for(i = 0; i < strlen(temp); i++){
        if(temp[i] == '.'){
            result = 1;
            break;
        }
    }
    return result;
}