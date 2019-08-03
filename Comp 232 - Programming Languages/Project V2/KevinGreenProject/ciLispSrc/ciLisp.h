#ifndef __cilisp_h_
#define __cilisp_h_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "../cmake-build-debug/ciLispParser.h"


/**
* Name: Kevin Green
* Lab/task: ciLisp
* Date: 05/07/18
**/

int yyparse(void);

int yylex(void);

void yyerror(char *);

typedef enum oper { // must be in sync with funcs in resolveFunc()
    NEG,
    ABS,
    EXP,
    SQRT,
    ADD,
    SUB,
    MULT,
    DIV,
    REMAINDER,
    LOG,
    POW,
    MAX,
    MIN,
    EXP2,
    CBRT,
    HYPOT,
    PRINT,
    EQUAL,
    SMALLER,
    LARGER,
    RAND,
    READ,
    INVALID_OPER = 255
} OPER_TYPE;

typedef enum {
    NO_TYPE, INTEGER_TYPE, REAL_TYPE
} DATA_TYPE;
typedef enum {
    VARIABLE_TYPE, LAMBDA_TYPE, ARG_TYPE
} SUB_SYMBOL_TYPE;

typedef struct stackNode {
    struct ast_node *data;
    struct stackNode *next;
} STACK_NODE;

typedef struct symbol_table_node {
    SUB_SYMBOL_TYPE type;
    DATA_TYPE val_type;
    char *ident;
    struct ast_node *val;
    struct stackNode *stack;
    struct symbol_table_node *next;
} SYMBOL_TABLE_NODE;

typedef enum {
    NUM_TYPE, FUNC_TYPE, SYMBOL_TYPE, SYMBOL_TABLE_TYPE
} AST_NODE_TYPE;

typedef struct {
    double value;
} NUMBER_AST_NODE;

typedef struct {
    char *name;
    struct ast_node *opList;
} FUNCTION_AST_NODE;

typedef struct symbol_ast_node {
    char *name;
    //printf("\n");
} SYMBOL_AST_NODE;

typedef struct ast_node {
    AST_NODE_TYPE type;
    SYMBOL_TABLE_NODE *scope;
    struct ast_node *parent;
    struct ast_node *next;
    union {
        NUMBER_AST_NODE number;
        FUNCTION_AST_NODE function;
        SYMBOL_AST_NODE symbol;
        //SYMBOL_TABLE_NODE table;
    } data;
} AST_NODE;

typedef struct return_value {
    DATA_TYPE type;
    double value;
} RETURN_VALUE;

AST_NODE *number(double value);

//AST_NODE *function(char *funcName, AST_NODE *op1, AST_NODE *op2);
AST_NODE *function(char *funcName, AST_NODE *op_list, AST_NODE_TYPE type);

AST_NODE *symbol(char *symbolName);

AST_NODE *table_node(SYMBOL_TABLE_NODE *table, AST_NODE *op);

SYMBOL_TABLE_NODE *
build_element(char *name, AST_NODE *op, DATA_TYPE type, SYMBOL_TABLE_NODE *arg_list, SUB_SYMBOL_TYPE type2);
//AST_NODE *build_list()

void freeNode(AST_NODE *p);

//double eval(AST_NODE *ast);
AST_NODE *build_list(AST_NODE *op, AST_NODE *list);

RETURN_VALUE eval(AST_NODE *);

SYMBOL_TABLE_NODE *add_element(SYMBOL_TABLE_NODE *table, SYMBOL_TABLE_NODE *addition);

RETURN_VALUE get_val(char *symbol, AST_NODE *p);

RETURN_VALUE get_val_helper(char *symbol, AST_NODE *p, AST_NODE *orig);

SYMBOL_TABLE_NODE *add_argument(char *name, SYMBOL_TABLE_NODE *table);

RETURN_VALUE eval_lambda(AST_NODE *orig, AST_NODE *p);

AST_NODE *pop(STACK_NODE *root);

void push(STACK_NODE **root, AST_NODE *data);

int isEmpty(STACK_NODE *root);

STACK_NODE *newNode(AST_NODE *data);

AST_NODE *peek(STACK_NODE *root);
//AST_NODE *user_function(char *name, AST_NODE *op_list);
//AST_NODE build_list(AST_NODE op, AST_NODE next_op);
#endif
