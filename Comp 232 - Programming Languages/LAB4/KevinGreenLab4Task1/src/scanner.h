//
//  scanner.h
//
//  Created by Bieszczad, A.J. on 2/21/13.
//  Copyright (c) 2013 CSUCI. All rights reserved.
//
/**
 * Modified by:
* Name: Kevin Green
* Lab/task: Lab 4 Task 1
* Date: 02/28/18
**/
typedef enum {
    INVALID_TOKEN = 0,
    NUMBERTOKEN, //1
    IDENTTOKEN,//2
    ASSIGNMENT,//3
    SEMICOLON,//4
    LPAREN,//5
    RPAREN,//6
    PLUS,//7
    MINUS,//8
    MULT,//9
    DIV,//10
    MOD,//11
    REPEAT,//12
    PRINT,//13
    END_OF_INPUT_TOKEN//14
} TOKEN_TYPE;

typedef struct token {
    TOKEN_TYPE type;
    char *strVal;
} TOKEN;
typedef struct {
    int number_of_rows;
    int number_of_columns;
    char **table;
} TRANS_TABLE_TYPE;
//TOKEN *scannerAdHoc();
//void ungetToken(TOKEN **);

//void freeToken(TOKEN **);

//TOKEN *nested_scanner();
//TOKEN table_scanner();
TOKEN_TYPE get_token_number(char *);

char *get_command(char *, int);

int get_column(char *, char);

TOKEN *scan(TRANS_TABLE_TYPE *);

TRANS_TABLE_TYPE *scan_init(FILE *);

char *token_str(int);

#define BUF_SIZE 128
#define MAX_LINE_LENGTH 256
#define TOKEN_ARRAY_SIZE 14
