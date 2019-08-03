#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"

//typedef enum {IDENTIFIER = 1, NUMBER, EXPR, TERM, ASSIGN_STMT, REPEAT_STMT, PRINT_STMT, FACTOR, ADDOP, MULTOP, PROGRAM, STATEMENT} AST_NODE_TYPE;
//char *node2str[] = {"I"};
AST_NODE *program() {
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    //used for testing recursive print_program
    //temp_node->left_node = temp_node;
    //Code used for testing  main->parser->scanner
    /*TOKEN *token = NULL;
    token = scanner();
    printf("{%d, %s}\n", token->type, (token->strVal != NULL) ? token->strVal : "");*/
    //printf("Program\n");
    //printf("funcProg: ");
    temp_node->type = PROGRAM;
    temp_node->left_node = statement();
    //printf("funcProg: ");
    printf("\n");
    if (temp_node->left_node != NULL)
        temp_node->right_node = program();
    return temp_node;
}

AST_NODE *statement() {
    //printf("Statement\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = STATEMENT;
    TOKEN *temp_token = malloc(sizeof(TOKEN));
    temp_token = scanner();
    if (temp_token == NULL)
        return NULL;
    else
        printf("funcProg: ");
    if (temp_token->type == REPEAT)
        temp_node->left_node = repeatStmt(temp_token);
    else if (temp_token->type == PRINT)
        temp_node->left_node = printStmt(temp_token);
    else if (temp_token->type == IDENTTOKEN)
        temp_node->left_node = assignStmt(temp_token);
    else
        error();

    temp_node->right_node = NULL;
    return temp_node;
}

AST_NODE *assignStmt(TOKEN *currToken) {
    //printf("AssignStmt\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    printf("funcAssign: ");
    temp_node->type = ASSIGN_STMT;
    temp_node->left_node = id(currToken); //Handle ID
    expect(ASSIGNMENT);
    printf("to ");
    temp_node->right_node = expr(currToken);
    //currToken = scanner(); //get past semicolon
    expect(SEMICOLON);
    return temp_node;
}

AST_NODE *repeatStmt(TOKEN *currToken) {
    //printf("RepeatStmt\n");
    printf("funcRepeat: ");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = REPEAT_STMT;
    expect(LPAREN);
    temp_node->left_node = expr(currToken);
    expect(RPAREN);
    temp_node->right_node = statement();
    return temp_node;
}

AST_NODE *printStmt(TOKEN *currToken) {
    // printf("PrintStmt\n");
    printf("funcPrint: ");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = PRINT_STMT;
    temp_node->left_node = expr(currToken);
    expect(SEMICOLON);
    return temp_node;
}

AST_NODE *expr(TOKEN *currToken) {
    //printf("Expr\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = EXPR;
    currToken = scanner(); //gets start of expr;
    temp_node->left_node = term(currToken);
    currToken = scanner();
    if (currToken->type == MINUS || currToken->type == PLUS) {
        temp_node->right_node = addOP(currToken);
        if (temp_node->right_node != NULL) {
            temp_node->right_node->left_node = malloc(sizeof(AST_NODE));
            temp_node->right_node->left_node->type = EXPR;
            temp_node->right_node->left_node->left_node = temp_node->left_node;
            temp_node->left_node = temp_node->right_node;
            temp_node->right_node = NULL;
            freeToken(&currToken);
        }
    } else {
        ungetToken(&currToken);
        temp_node->right_node = NULL;
    }

    return temp_node;
}

AST_NODE *term(TOKEN *currToken)
{
    //printf("Term\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = TERM;
    //currToken = scanner(); //gets start of expr;
    temp_node->left_node = factor(currToken);
    currToken = scanner();
    if (currToken->type == MULT || currToken->type == DIV)
    {
        temp_node->right_node = multOP(currToken);
        if (temp_node->right_node != NULL) {
            temp_node->right_node->left_node = malloc(sizeof(AST_NODE));
            temp_node->right_node->left_node->type = TERM;
            temp_node->right_node->left_node->left_node = temp_node->left_node;
            temp_node->left_node = temp_node->right_node;
            temp_node->right_node = NULL;
            freeToken(&currToken);
        }
    } else {
        ungetToken(&currToken);
        temp_node->right_node = NULL;
    }

    return temp_node;
}

AST_NODE *factor(TOKEN *currToken) {
    //printf("Factor\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = FACTOR;
    if (currToken->type == IDENTTOKEN)
        temp_node->left_node = id(currToken);
    else if (currToken->type == NUMBERTOKEN)
        temp_node->left_node = number(currToken);
    else if (currToken->type == LPAREN) {
        temp_node->left_node = expr(currToken);
        expect(RPAREN);
    } else
        printf("TEST\n");

    temp_node->right_node = NULL;
    return temp_node;
}

AST_NODE *id(TOKEN *currToken) {
    //printf("ID\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = IDENTIFIER;
    strcpy(temp_node->data.identifier, currToken->strVal);
    temp_node->left_node = NULL;
    temp_node->right_node = NULL;
    printf("ID(%s) ", currToken->strVal);
    return temp_node;
}

AST_NODE *number(TOKEN *currToken) {
    //printf("Number\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = NUMBER;
    temp_node->data.number = strtol(currToken->strVal, NULL, 10);
    temp_node->left_node = NULL;
    temp_node->right_node = NULL;
    printf("INT(%s) ", currToken->strVal);
    return temp_node;
}

void error() {
    printf("+++TREE FAILED TO TAKE ROOT. CONGRATS. NOW THE TREE IS DEAD. YOU MONSTER+++\n");
    //return 0;
}

int expect(TOKEN_TYPE type) {
    TOKEN *nextToken = scanner();
    if (nextToken->type != type)
        error();
    return 0;
}

AST_NODE *multOP(TOKEN *currToken)//altered grammar to accept
{
    //printf("MULTOP\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = MULTOP;
    temp_node->data.addOp = currToken->strVal[0];
    printf("multOp(%c) ", temp_node->data.multOp);
    //temp_node->left_node = expr(currToken);//done in expr
    currToken = scanner();
    temp_node->right_node = term(currToken);
    return temp_node;
}

AST_NODE *addOP(TOKEN *currToken) {
    //printf("ADDOP\n");
    AST_NODE *temp_node = malloc(sizeof(AST_NODE));
    temp_node->type = ADDOP;
    temp_node->data.addOp = currToken->strVal[0];
    printf("multOp(%c) ", temp_node->data.addOp);
    //temp_node->left_node = expr(currToken);//done in expr
    currToken = scanner();
    temp_node->right_node = term(currToken);
    return temp_node;
}