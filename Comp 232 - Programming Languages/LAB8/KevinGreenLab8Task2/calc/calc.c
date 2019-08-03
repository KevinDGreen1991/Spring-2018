#include "calc.h"
/**
* Name: Kevin Green
* Lab/task: Lab 8 Task 2
* Date: 03/14/18
 * Task 1 and 2 are included in these files
*/
void yyerror(char *s) {
    printf("\nERROR: %s\n", s);
    // note stderr that normally defaults to stdout, but can be redirected: ./calc 2> calc.log
    // CLion will display stderr in a different color from stdin and stdout
}

/*
 * The function to resolve a name of a function; i.e., to translate it to an int equivalent (if possible)
 * that can be used conveniently in the calc() function.
 */
int resolveFunc(char *func) {
    // all functions are exacty as they appear in math.h; use man to get details
    char *funcs[] = {"neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min",
                     "exp2", "hypot", "cbrt",
                     ""};

    int i = 0;
    while (funcs[i][0] != '\0') {
        if (!strcmp(funcs[i], func))
            return i;

        i++;
    }
    yyerror("invalid function"); // paranoic -- should never happen
    return -1;
}

/*
 * The function to calculate simple math operation.
 *
 * The values of op1 and op2 may be omitted for functions that tke one or none parameters.
 */
double calc(char *func, double op1, double op2) {

// TODO: implement the function, so it returns correct values for each set of parameters
    double temp = 0.0;
    /*if(op2 == 0)
        printf("TESTING!\n");*/
    switch (resolveFunc(func)) {
        case 0:
            temp = -op1;
            break; //neg
        case 1:
            temp = fabs(op1);
            break; //abs
        case 2:
            temp = exp(op1);
            break; // exp
        case 3:
            temp = sqrt(op1);
            break; // sqrt
        case 4:
            temp = op1 + op2;
            break; //add
        case 5:
            temp = op1 - op2;
            break; //sub
        case 6:
            temp = op1 * op2;
            break; //mult
        case 7:
            if (op2 == 0) //div
                printf("Divide By Cucumber Error. Please Reinstall Universe And Reboot\n");
            else
                temp = op1 / op2;
            break;
        case 8:
            temp = remainder(op1, op2);
            break; // remainder
        case 9:
            if (op2 == 0) // log
                temp = log10(op1);
            else if (op1 == 10)
                temp = log10(op2);
            else if (op1 == 2)
                temp = log2(op2); //log10(op2) / log10(2);
            else
                printf("Oneoneoneoneoneoneone\n");
            break;
        case 10:
            temp = pow(op1, op2);
            break; //pow
        case 11:
            temp = fmax(op1, op2);
            break; //max
        case 12:
            temp = fmin(op1, op2);
            break; //min
        case 13:
            temp = exp2(op1);
            break; // exp2
        case 14:
            temp = hypot(op1, op2);
            break; //hypot
        case 15:
            temp = cbrt(op1);
            break; //cbrt
        default:
            break;
    }
    return temp;

}  
