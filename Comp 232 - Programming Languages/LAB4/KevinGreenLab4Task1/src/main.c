/**
* Name: Kevin Green
* Lab/task: Lab 4 Task 1
* Date: 02/21/18
**/
#include <stdio.h>
#include "scanner.h"

/*const char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS",
                           "MULT", "DIV", "MOD", "REPEAT", "PRINT", "END_OF_INPUT"};*/

int main(int argc,
         char *argv[])//takes a txt file with corresponding transition table, and an optional second txt file for input
{
    FILE *trans_in_file = fopen(argv[1], "r");
    //printf("Hello world");
    if (trans_in_file == NULL) {
        printf("--INVALID NUMBER OF ARGUMENTS--");
        return 0;
    }

    if (argc > 2)
        freopen(argv[2], "r", stdin);

    TRANS_TABLE_TYPE *trans_table;

    trans_table = scan_init(trans_in_file);

    TOKEN *token = NULL;

    do {
        token = scan(trans_table);
        //printf("%d \n ", token->type);
        printf("{%s, %s}\n", token_str(token->type), (token->strVal != NULL) ? token->strVal : "");
        fflush(stdout);
    } while (token->type != END_OF_INPUT_TOKEN);

    fclose(trans_in_file);
}

