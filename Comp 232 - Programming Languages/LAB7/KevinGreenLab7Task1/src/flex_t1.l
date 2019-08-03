/* NOTE: % must be in the first column (no indentation) */
/**
* Name: Kevin Green
* Lab/task: Lab 7 Task 1
* Date: 03/12/18
**/
%option noyywrap
%option nounput
%option noinput

%{ // must start in the first column
   #include "flex_t1.h"
   double sum_of_numbers= 0; // TODO: complete
   double sum_of_money= 0; // TODO: complete
   double totDol = 0;
   int number_keywords[NUM_OF_WORDS+1];
%} // must start in the first column

/* aliasses */
digit [0-9]
number {digit}+(\.{digit}+)?
letter [a-z]
/* matching rules - NOTE: in the rule section, cannot add comments outside of the C code in brackets */
%%

"bank"{letter}*   {/* match action */ printf("<!> %s <!>", yytext); number_keywords[BANK]++; return BANK;}
"dollar"{letter}* {printf("<!> %s <!>", yytext);number_keywords[DOLLAR]++; return DOLLAR;}
"financ"{letter}* {printf("<!> %s <!>", yytext);number_keywords[FINANC]++; return FINANC;}
"budget"{letter}* {printf("<!> %s <!>", yytext);number_keywords[BUDGET]++; return BUDGET;}
"fund"{letter}* {printf("<!> %s <!>", yytext);number_keywords[FUND]++; return FUND;}
"stock"{letter}* {printf("<!> %s <!>", yytext);number_keywords[STOCK]++; return STOCK;}
"bond"{letter}* {printf("<!> %s <!>", yytext);number_keywords[BOND]++; return BOND;}
"invest"{letter}* {printf("<!> %s <!>", yytext);number_keywords[INVEST]++; return INVEST;}

\${number}  {printf("<$> %s <$>", yytext); sum_of_money += strtod(yytext+1, NULL); sum_of_numbers += strtod(yytext+1, NULL);return MONEY;}
{number} {printf("<#> %s <#>", yytext);sum_of_numbers += atol(yytext); return NUMBER;}
%%

void yyerror(char *s) {/* dummy */}
