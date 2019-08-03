/**
* Name: Your Name(s)
* Lab/task: Lab 3 Task 1
* Date: 02/19/18
**/

#include "scanner.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    TOKEN *token = NULL;
    char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS",
                         "MULT", "DIV", "MOD", "REPEAT", "PRINT", "END_OF_INPUT"};
    printf("\n");
    if (argc > 1)
        //printf(argv[1]);
        freopen(argv[1], "r", stdin);
    //printf(getc(stdin));
    while ((token = nested_scanner()) != NULL) {
        printf("{%s, %s}", token2str[token->type], (token->strVal != NULL) ? token->strVal : "");
        fflush(stdout);
    }
    printf("\n");
}