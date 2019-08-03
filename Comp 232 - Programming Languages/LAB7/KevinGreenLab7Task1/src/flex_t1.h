#ifndef __flex_bis_t1_h_
#define __flex_bis_t1_h_

#include <stdio.h>
/**
* Name: Kevin Green
* Lab/task: Lab 7 Task 1
* Date: 03/12/18
**/
#define NUM_OF_WORDS 8
typedef enum {
    NO_TOK = 0, BANK, DOLLAR, FINANC, BUDGET, FUND, STOCK, BOND, INVEST, MONEY, NUMBER
} WORD; // TODO: complete

// function computing a sum of all element of an array
// the second parameter is the size of the array
int sum(int[], int);

int yylex(void);

#endif