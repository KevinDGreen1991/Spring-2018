//
//  main.c (driver for a scanner test)
//
//  Created by Bieszczad, A.J. on 9/20/17.
//  Copyright (c) 2017 CSUCI. All rights reserved.
//
#include "scanner.h"
#include <stdio.h>
int main(){
    TOKEN *token = NULL;
    char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS", "MULT", "DIV", "MOD", "REPEAT", "PRINT", "END_OF_INPUT"};
    printf("\n");
    while((token = scannerAdHoc()) != NULL) {
        printf("{%s, %s}", token2str[token->type], (token->strVal != NULL) ? token->strVal : "");
        fflush(stdout);
    }
    printf("\n");
    //freopen();
}