#include "flex_t1.h"

/**
* Name: Kevin Green
* Lab/task: Lab 7 Task 1
* Date: 03/12/18
**/
extern double sum_of_numbers; // TODO: complete
extern double sum_of_money; // TODO: complete

extern FILE *yyin; /* needed if using yyin in here */

char *targetWords[NUM_OF_WORDS] = {"bank", "dollar", "financ", "budget", "fund", "stock", "bond",
                                   "invest"};  // TODO: complete
int number_keywords[NUM_OF_WORDS + 1];

//double totDol;
//double amount;
int sum_keywords() {
    int temp = 0;
    for (int x = 0; x <= NUM_OF_WORDS; x++) {
        temp += number_keywords[x];
    }
    return temp;
}

int main(int argc, char *argv[]) {
    yyin = freopen(argv[1], "r", stdin);

    WORD word = NO_TOK;
    while ((word = yylex()) != NO_TOK) {
        /*if ((word > 0) && (word < NUM_OF_WORDS))
        {
           printf("<!> %s <!>", targetWords[word-BANK]);
           //number_keywords[word-BANK]++;
        }
        else if(word == MONEY)
        {
           printf("<!> $%.2f <!>", amount);
        }*/
    }
    printf("\n");
    if (sum_of_money >= 1000) {
        printf("VERY INTERESTING READING!\n");
        printf("Reported sum of dollars: %g\n", sum_of_money);
    } else if (sum_of_numbers >= 1000 && sum_keywords() >= 3) {
        printf("POTENTIALLY INTERESTING READING!\n");
        printf("Reported sum of numbers: %g\n", sum_of_numbers);
        printf("Concordance:\n");
        for (int x = 0; x <= NUM_OF_WORDS; x++) {
            if (number_keywords[x] > 0)
                printf("%d %s\n", number_keywords[x], targetWords[x]);
        }
    } else {
        printf("BORING READING!\n");
    }
    //printf("%f", totDol);
    /*for(int x = 0; x <= NUM_OF_WORDS; x++)
    {
       printf("%d\n", number_keywords[x]);
    }*/
    //printf("%d", totDol);
}