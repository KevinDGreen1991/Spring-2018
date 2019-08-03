//
// Created by Green, Kevin on 2/14/18.
//
/**
* Name: Your Name(s)
* Lab/task: Lab 2 Task 3
* Date: 02/17/18
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"

TOKEN *nested_scanner() {
    //getchar()
    short state = 1;
    char current; //use int to ensure EOF is read
    while ((current = getchar()) != EOF) {
        current = getchar();
        switch (state) {
            case 1:
                switch (current) {
                    case '0'...'9':
                        state = 2;
                        ungetc(current, stdin);
                        break;
                    case 'a'...'z':
                        state = 3;
                        ungetc(current, stdin);
                        break;
                    case '(':
                        return LPAREN;
                    case ')':
                        return RPAREN;
                    case ';':
                        return SEMICOLON;
                    default:break;
                }
            case 2:
                switch (current)
                {
                    //handle NUMBERTOKEN
                }
            case 3:
                //handle IDENTTOKEN
            default:
                return INVALID_TOKEN;
        }
    }
}