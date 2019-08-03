//
//  scanner.h
//
//  Created by Bieszczad, A.J. on 2/21/13.
//  Copyright (c) 2013 CSUCI. All rights reserved.
//

typedef enum {
    INVALID_TOKEN = 0,
    NUMBERTOKEN,
    IDENTTOKEN,
    ASSIGNMENT,
    SEMICOLON,
    LPAREN,
    RPAREN,
    PLUS,
    MINUS,
    MULT,
    DIV,
    MOD,
    REPEAT,
    PRINT,
    END_OF_INPUT_TOKEN
} TOKEN_TYPE;

typedef struct token {
    TOKEN_TYPE type;
    char *strVal;
} TOKEN;

TOKEN *scanner();

void ungetToken(TOKEN **);

void freeToken(TOKEN **);

#define BUF_SIZE 128
#define MAX_LINE_LENGTH 256

