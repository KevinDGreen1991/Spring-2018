/**
* Name: Kevin Green
* Lab/task: ciLisp
* Date: 05/07/18
**/

%{
    #include "ciLisp.h"
%}

%union {
    double dval;
    char *sval;
    struct ast_node *astNode;
    struct symbol_table_node *symbolTableNode;
    int ival;
};

%token <sval> FUNC
%token <dval> NUMBER
%token <sval> SYMBOL
%token LPAREN RPAREN EOL LET INTEGER REAL COND LAMBDA QUIT

%type <astNode> s_expr
%type <astNode> s_expr_list
%type <symbolTableNode> scope
%type <symbolTableNode> let_list
%type <symbolTableNode> let_elem
%type <symbolTableNode> arg_list
%type <ival> type
%%

program:
    s_expr EOL {
        fprintf(stderr, "yacc: program ::= s_expr EOL\n");
        //printf("NEW PROGRAM!\n");
        if ($1) {
            printf("FINAL VALUE = %lf\n", eval($1).value);
            freeNode($1);
        }
        else
        {
            printf("NULL NODE RECIEVED!");
        }
    };

s_expr:
    QUIT {
        fprintf(stderr, "QUIT\n");
        exit(0);
    }
    | NUMBER {
        fprintf(stderr, "yacc: NUMBER%lf", $1);
        $$ = number($1);
    }
    | SYMBOL
    {
        fprintf(stderr, "yacc: SYMBOL%s", $1);
        $$ = symbol($1);
    }
    /*| LPAREN FUNC s_expr RPAREN {
        fprintf(stderr, "yacc: LPAREN FUNC expr RPAREN\n");
        $$ = function($2, $3, 0);
    }
    | LPAREN FUNC s_expr s_expr RPAREN {
        fprintf(stderr, "LPAREN FUNC expr expr RPAREN\n");
        $$ = function($2, $3, $4);
    }*/
    |
    LPAREN FUNC s_expr_list RPAREN{
        fprintf(stderr, "yacc: LPAREN FUNC s_expr_list RPAREN\n");
        $$ = function($2, $3, FUNC_TYPE);
    }
    |
    LPAREN SYMBOL s_expr_list RPAREN{
        fprintf(stderr, "yacc: LPAREN SYMBOL s_ezpr_list RPAREN\n");
        //printf("TESTING\n");
        $$ = function($2, $3, SYMBOL_TYPE);
    }
    |
    LPAREN scope s_expr RPAREN
    {
        fprintf(stderr, "yacc: LPAREN scope s_expr RPAREN\n");
        $$ = table_node($2, $3);
    }
    |
    LPAREN COND s_expr s_expr s_expr RPAREN
    {
        fprintf(stderr, "yacc: LPAREN COND s_expr s_expr s_expr RPAREN\n");
        if(eval($3).value == 0)
            $$ = $5;
        else
            $$ = $4;
    }
    | error {
        fprintf(stderr, "yacc: s_expr ::= error\n");
        yyerror("unexpected token");
        $$ = NULL;
    };

s_expr_list:
    /* empty */
        {
            fprintf(stderr, "Empty S_expr_list");
            $$ = NULL;
        }
        |
    s_expr s_expr_list{
        fprintf(stderr, "yacc: s_expr s_expr_list\n");
        $$ = build_list($1, $2);
    }
    |
    s_expr{
        fprintf(stderr, "yacc: s_expr\n");
        $$ = build_list($1, NULL);
    };

scope:
    /* empty */
    {
        fprintf(stderr, "Empty Scope");
        $$ = NULL;
    }
    | LPAREN LET let_list RPAREN
    {
        fprintf(stderr, "yacc: LPAREN LET let_list RPAREN\n");
        $$ = $3;
    };

let_list:
    let_elem
    {
        fprintf(stderr, "yacc: let_elem \n");
        //$$ = $1;
        //$$ = list_elem($1, 0, 0);
        $$ = add_element(NULL, $1);

    }
    |
    let_list let_elem
    {
        fprintf(stderr, "yacc: let_list Let_elem\n");
        //$$ = $1;
        //$$ = list_elem($1, $2, 0);
        $$ = add_element($1, $2);

    };

let_elem:
    LPAREN type SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN{
        fprintf(stderr, "yacc: LPAREN type SYMBOL LAMBDA LPAREN arg_list RPAREN s_expr RPAREN\n");
        $$ = build_element($3, $8, $2, $6, LAMBDA_TYPE);
        //printf("%s\n", $3);
    }
    |
    LPAREN type SYMBOL s_expr RPAREN
    {
        fprintf(stderr, "yacc: LPAREN SYMBOL s_expr RPAREN\n");
        $$ = build_element($3, $4, $2, NULL, VARIABLE_TYPE);
    }
    ;

arg_list:
    SYMBOL arg_list{
    fprintf(stderr, "yacc: SYMBOL arg_list\n");
        $$ = add_argument($1, $2);
        //printf("%s\n", $1);
    }
    |
    SYMBOL{
    fprintf(stderr, "yacc: ARGUMENT\n");
        $$ = add_argument($1, NULL);
        //printf("%s\n", $1);
    };

type:
    /* empty */
    {
        fprintf(stderr, "yacc: Empty type\n");
        $$ = REAL_TYPE;
    }
    |
    REAL
    {
        fprintf(stderr, "yacc: REAL\n");
        $$ = REAL_TYPE;
    }
    |
    INTEGER
    {
        fprintf(stderr, "yacc: INTEGER\n");
        $$ = INTEGER_TYPE;
    };
%%

