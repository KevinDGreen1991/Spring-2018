//
// Created by Green, Kevin on 2/14/18.
//
/**
* Name: Your Name(s)
* Lab/task: Lab 3 Task 1
* Date: 02/17/18
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

TOKEN *ungottenToken = NULL;

void ungetToken(TOKEN **token) {
    ungottenToken = *token;
    *token = NULL;
}

//
// clean up the token structure
//
void freeToken(TOKEN **token) {
    if (*token == NULL)
        return;

    if ((*token)->strVal != NULL)
        free((*token)->strVal);

    free(*token);

    *token = NULL;
}

TOKEN *nested_scanner() {
    //getchar()
    if (ungottenToken != NULL) {
        TOKEN *tok = ungottenToken;
        ungottenToken = NULL;
        return tok;
    }

    // temporary buffer for collecting characters
    char tempString[BUF_SIZE];

    // acquire space for the new token
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->type = INVALID_TOKEN; // assume that the toekn is invalid to start with
    token->strVal = NULL;

    int state = 1;
    int current; //use int to ensure EOF is read
    int i = 0;
    while ((token->type == INVALID_TOKEN) && (current = getchar()) != EOF) {
        //current = getchar();
        //printf("%c", (char)current);
        switch (state) {
            case 1:
                switch (current) {
                    case ' ': // skip whitespace
                    case '\t':
                    case '\n':
                        break;
                    case '0'...'9':
                        state = 2;
                        ungetc(current, stdin);
                        //i = 0;
                        break;
                    case 'a'...'z':
                        state = 3;
                        ungetc(current, stdin);
                        //i = 0;
                        break;
                    case '(':
                        token->type = LPAREN;
                        return token;
                    case ')':
                        token->type = RPAREN;
                        return token;
                    case ';':
                        token->type = SEMICOLON;
                        return token;
                    case '+':
                        token->type = PLUS;
                        return token;
                    case '-':
                        token->type = MINUS;
                        return token;
                    case '*':
                        token->type = MULT;
                        return token;
                    case '/':
                        token->type = DIV;
                        return token;
                    case '%':
                        token->type = MOD;
                        return token;
                    case '=':
                        token->type = ASSIGNMENT;
                        return token;
                    default:
                        break;
                }
                break;
            case 2:
                switch ((char) current) {
                    case '0'...'9':
                        tempString[i++] = (char) current;
                        break;
                    default:
                        tempString[i++] = '\0';
                        ungetc(current, stdin);
                        token->type = NUMBERTOKEN;
                        token->strVal = (char *) malloc(strlen(tempString) + 1);
                        strcpy(token->strVal, tempString);
                        return token;
                }
                break;
            case 3:
                //handle IDENTTOKEN
                switch ((char) current) {
                    case 'a'...'z':
                        tempString[i++] = (char) current;
                        break;
                    default:
                        tempString[i++] = '\0';
                        ungetc(current, stdin);
                        if (strcmp(tempString, "print") == 0)
                            token->type = PRINT;
                        else if (strcmp(tempString, "repeat") == 0)
                            token->type = REPEAT;
                        else {
                            token->type = IDENTTOKEN;
                            token->strVal = (char *) malloc(strlen(tempString) + 1);
                            strcpy(token->strVal, tempString);
                        }
                        return token;
                }
                break;
            default:
                return token;
        }
    }
    if (current == EOF) {
        free(token);
        return NULL;
    }
    return token;
}