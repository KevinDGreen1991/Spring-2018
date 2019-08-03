#include "ciLisp.h"

/**
* Name: Kevin Green
* Lab/task: ciLisp
* Date: 05/07/18
**/

//code for testing purposes, to be copy and pasted where needed
/*printf("ELEMENT %s ", addition->ident);
switch(addition->type)
{
    case VARIABLE_TYPE: printf("VARIABLE!\n");
        break;
    case LAMBDA_TYPE: printf("LAMBDA!\n");break;
    case ARG_TYPE: printf("ARGUMENT\n");break;
    default: break;
}*/


//
// find out which function it is
//
int resolveFunc(char *func) {
    char *funcs[] = {"neg", "abs", "exp", "sqrt", "add", "sub", "mult", "div", "remainder", "log", "pow", "max", "min",
                     "exp2", "cbrt", "hypot", "print", "equal", "smaller", "larger", "rand", "read", ""};

    int i = 0;
    while (funcs[i][0] != '\0') {
        if (!strcmp(funcs[i], func))
            return i;

        i++;
    }
    yyerror("invalid function");
    return INVALID_OPER;
}

//
// create a node for a number
//
AST_NODE *number(double value) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(NUMBER_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = NUM_TYPE;
    p->data.number.value = value;

    return p;
}

//
// create a node for a function
//
AST_NODE *function(char *funcName, AST_NODE *op_list, AST_NODE_TYPE type) {
    AST_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(FUNCTION_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = type;
    p->data.function.name = funcName;
    p->data.function.opList = op_list;

    while (op_list != NULL) {
        op_list->parent = p;
        op_list = op_list->next;
    }

    return p;
}

//AST_NODE *user_function(*)
SYMBOL_TABLE_NODE *
build_element(char *name, AST_NODE *op, DATA_TYPE type, SYMBOL_TABLE_NODE *arg_list, SUB_SYMBOL_TYPE type2) {
    SYMBOL_TABLE_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(SYMBOL_TABLE_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->val_type = type;
    p->ident = name;
    p->val = op;
    p->type = type2;
    double temp;
    //TODO: READ function works properly however has a small non-fatal bug
    //code seems to imply that new line of input is read immediately after resulting in result of
    // NULL NODE RECIEVED which only occurs if the user input a blank line to be parsed
    if (op->type == FUNC_TYPE && resolveFunc(op->data.function.name) == READ) {
        printf("read %s := ", name);
        scanf("%lf", &temp);
        //printf("TESTING!");
        AST_NODE *new_val = number(temp);
        p->val = new_val;
    } else if (type2 == LAMBDA_TYPE) {
        temp = 0;
    } else {
        temp = eval(p->val).value;
    }

    if (type == INTEGER_TYPE && round(temp) != temp) {
        printf("WARNING: incompatible type assignment for variables <%s>\n", p->ident);
    }
    p->next = NULL;

    //If element is a function
    if (type2 == LAMBDA_TYPE && op && arg_list) {
        SYMBOL_TABLE_NODE *temp2 = op->scope;
        if (temp2 == NULL)
            op->scope = arg_list;
        else {
            while (temp2->next != NULL) {
                temp2 = temp2->next;
            }
            temp2->next = arg_list;
        }
    }
    return p;
}

SYMBOL_TABLE_NODE *add_argument(char *name, SYMBOL_TABLE_NODE *table) {
    SYMBOL_TABLE_NODE *p;
    size_t nodeSize;

    // allocate space for the fixed sie and the variable part (union)
    nodeSize = sizeof(AST_NODE) + sizeof(SYMBOL_TABLE_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->val_type = REAL_TYPE;
    p->type = ARG_TYPE;
    p->ident = name;
    p->val = NULL;
    p->next = table;
    return p;

}

//SYMBOL_TABLE_NODE *build_function(char )
AST_NODE *build_list(AST_NODE *op, AST_NODE *list) {
    if (list == NULL)
        return op;
    op->next = list;

    return op;
}

//builds table nodes
AST_NODE *table_node(SYMBOL_TABLE_NODE *table, AST_NODE *op) {
    AST_NODE *p;
    size_t nodeSize;

    nodeSize = sizeof(AST_NODE) + sizeof(SYMBOL_TABLE_NODE);

    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->type = SYMBOL_TABLE_TYPE;
    op->parent = p;
    p->data.function.opList = op;
    p->scope = table;

    return p;

}

SYMBOL_TABLE_NODE *add_element(SYMBOL_TABLE_NODE *table, SYMBOL_TABLE_NODE *addition) {
    if (table == NULL) {
        return addition;
    }
    SYMBOL_TABLE_NODE *p = table;
    while (p->next != NULL) {
        if (strcmp(p->ident, addition->ident) == 0) {
            printf("%s is already defined", p->ident);
            return table;
        }
        p = p->next;
    }
    size_t nodeSize;
    nodeSize = sizeof(AST_NODE) + sizeof(SYMBOL_TABLE_NODE);

    if ((p->next = malloc(nodeSize)) == NULL)
        yyerror("out of memory");

    p->next->val = addition->val;
    p->next->ident = addition->ident;
    p->next->val_type = addition->val_type;
    p->next->type = addition->type;
    p->next->next = NULL;

    return table;
}

//
AST_NODE *symbol(char *symbolName) {
    AST_NODE *p;
    size_t nodeSize;

    nodeSize = sizeof(AST_NODE) + sizeof(SYMBOL_AST_NODE);
    if ((p = malloc(nodeSize)) == NULL)
        yyerror("out of memory");
    p->type = SYMBOL_TYPE;
    p->data.symbol.name = symbolName;
    return p;
}

//
// free a node
//
void freeNode(AST_NODE *p) {
    if (!p)
        return;

    switch (p->type) {
        case FUNC_TYPE:
            free(p->data.function.name);
            freeNode(p->data.function.opList);
            break;
        case SYMBOL_TYPE:
            free(p->data.symbol.name);
            break;
        case SYMBOL_TABLE_TYPE:
            free(p->scope);
            break;
        default:
            break;
    }
    /*if (p->type == FUNC_TYPE)
    {
        free(p->data.function.name);
        freeNode(p->data.function.opList);
        //freeNode(p->data.function.op2);
    }*/

    free(p);
}

//
// evaluate an abstract syntax tree
//
// p points to the root
//
//Function for getting the value for a symbol, sets up the recursive call for finding the value
RETURN_VALUE get_val(char *symbol, AST_NODE *p) {
    //printf("%s\n", p->data.symbol.name);
    return get_val_helper(symbol, p, p);
}

//the recursive call for finding the value of a symbol; takes the symbol we are looking for, the node we are currently on, and the original node we started from which is necessary for when we evaluate lambda expressions
RETURN_VALUE get_val_helper(char *symbol, AST_NODE *p, AST_NODE *orig) {
    if (p == NULL) {
        printf("%s SYMBOL not found!\n", symbol);
        RETURN_VALUE not_found;
        not_found.type = NO_TYPE;
        not_found.value = 0;
        return not_found;
    } else {
        //printf("Searching current Node_table!\n");
        SYMBOL_TABLE_NODE *element = p->scope;
        while (element != NULL) {
            /*if(element->type == VARIABLE_TYPE)
                printf("VARIABLE FOUND: %s\n", element->ident);*/
            if (strcmp(element->ident, symbol) == 0) {
                RETURN_VALUE temp;
                //printf("FOUND ELEMENT %s\n", element->ident);
                //TODO: HERE IS WHERE WE WANT TO IMPLEMENT GET EVAL FOR FUNCTIONS
                switch (element->type) {
                    case VARIABLE_TYPE:
                        temp.type = element->val_type;
                        temp.value = eval(element->val).value;
                        //if(resolveFunc(element->val->data)
                        if (temp.type == INTEGER_TYPE)
                            temp.value = round(temp.value);
                        break;
                    case LAMBDA_TYPE: {
                        //printf("FUNCTION %s FOUND!\n", element->ident);
                        temp.value = eval_lambda(orig->data.function.opList, element->val).value;
                        break;
                    }
                    case ARG_TYPE: {
                        //printf("FOUND ARGUMENT %s!\n", element->ident);
                        if (!isEmpty(element->stack)) {
                            temp.value = eval(peek(element->stack)).value;
                            //printf("VALUE: %lf\n", temp.value);
                            pop(element->stack);
                        } else {
                            printf("EMPTY STACK!\n");
                            temp.value = 0;
                        }
                        temp.type = REAL_TYPE;
                        break;
                    }
                        //orig->data.function.opList;
                    default:
                        temp.value = 0;
                        break;
                }
                return temp;
            }

            element = element->next;
        }
        return get_val_helper(symbol, p->parent, orig);
    }

}

//evaluates a node and returns its type and value
RETURN_VALUE eval(AST_NODE *p) {
    //p->data.function.opList->data
    RETURN_VALUE return_val;
    return_val.type = REAL_TYPE;
    if (!p) {
        return_val.type = NO_TYPE;
        return_val.value = 0;
        return return_val;
    }
// TBD: implement
    //double val = 0;
    if (p->type == NUM_TYPE) {
        return_val.value = p->data.number.value;
        //return_val.
    }
        //if(strcmp(p->data.function.name, "add") == 0)
        //if(resolveFunc(p->data.function.name) == ADD
    else if (p->type == SYMBOL_TYPE) {
        //val = get_val(p->data.symbol.name, p);
        //printf("%s\n", p->data.symbol.name);
        /*if(p->data.function.opList) {
            AST_NODE *temp = p->data.function.opList;
            while(temp != NULL) {
                printf("TESTING %lf\n", eval(temp));
                temp = temp->next; }}*/

        return_val = get_val(p->data.symbol.name, p);
        if (return_val.type == INTEGER_TYPE) {
            //printf("TESTING!\n");
            return_val.value = round(return_val.value);
        }
        //printf("SYMBOL %s = %f\n", p->data.symbol.name, val);
        //p->scope->val;
        //val = eval(p->data.d)
    } else if (p->type == FUNC_TYPE) {
        AST_NODE *temp = p->data.function.opList;
        //temp->next;
        switch (resolveFunc(p->data.function.name)) {
            case NEG:
                //return_val = eval(p->data.function.op1);
                //val = -eval(p->data.function.op1);
                if (temp == NULL) {
                    printf("ERROR: too few parameters for the function <NEG>\n");
                    return_val.value = 0;
                } else {
                    return_val = eval(temp);
                    return_val.value = -return_val.value;
                }
                //p->data.function.opList->next;
                if (temp != NULL && temp->next != NULL)
                    printf("WARNING: too many parameters for the function <NEG>\n");

                break;
            case ABS:
                //val = abs((int) eval(p->data.function.op1));
                //return_val = eval(p->data.function.op1);
                if (temp == NULL) {
                    printf("ERROR: too few parameters for the function <NEG>\n");
                    return_val.value = 0;
                } else {
                    return_val = eval(temp);
                    return_val.value = abs((int) return_val.value);
                }
                //p->data.function.opList->next;
                if (temp != NULL && temp->next != NULL) {
                    printf("WARNING: too many parameters for the function <NEG>\n");
                }

                break;
            case EXP:
                //val = exp(eval(p->data.function.op1));
                //return_val = eval(p->data.function.op1);
                if (temp == NULL) {
                    printf("ERROR: too few parameters for the function <EXP>\n");
                    return_val.value = exp(0);
                } else {
                    return_val.value = exp(eval(temp).value);
                }
                //p->data.function.opList->next;
                if (temp != NULL && temp->next != NULL) {
                    printf("WARNING: too many parameters for the function <NEG>\n");
                }
                //return_val.value = exp(eval(p->data.function.op1).value);
                break;
            case SQRT:
                if (temp == NULL) {
                    printf("ERROR: too few parameters for the function <SQRT>\n");
                    return_val.value = sqrt(0);
                } else {
                    return_val.value = sqrt(eval(temp).value);
                }
                //p->data.function.opList->next;
                if (temp != NULL && temp->next != NULL) {
                    printf("WARNING: too many parameters for the function <SQRT>\n");
                }
                //return_val.value = sqrt(eval(p->data.function.op1).value);
                //return_val = eval(p->data.function.op1);
                //return_val.value = sqrt(return_val.value);
                break;
            case SUB:
                //RETURN_VALUE temp1 = eval(p->data.function.op1);
                //if(eval(p->data.function.op1).)
                //if((return_val = eval(p->data.function.op1)).type == REAL)
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <SUB>\n");
                    return_val.value = 0;
                } else {
                    /*RETURN_VALUE temp_val = eval(temp);
                    //return_val = temp_val;
                    if(temp_val.type == INTEGER_TYPE)
                        return_val.type = INTEGER_TYPE;
                    return_val.value = temp_val.value;
                    while(temp->next != NULL)
                    {
                        temp = temp->next;
                        temp_val = eval(temp);
                        if(return_val.type == INTEGER_TYPE && temp_val.type == REAL_TYPE)
                            return_val.type = REAL_TYPE;
                        return_val.value -= temp_val.value;
                    }*/
                    if (eval(temp).type == INTEGER_TYPE && eval(temp->next).type == INTEGER_TYPE) {
                        return_val.type = INTEGER_TYPE;
                    }
                    return_val.value = eval(temp).value - eval(temp->next).value;
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <SUB>\n");
                }
                break;
            case ADD:
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <ADD>\n");
                    return_val.value = 0;
                } else {
                    RETURN_VALUE temp_val = eval(temp);
                    //return_val = temp_val;
                    if (temp_val.type == INTEGER_TYPE)
                        return_val.type = INTEGER_TYPE;
                    return_val.value = temp_val.value;
                    while (temp->next != NULL) {
                        temp = temp->next;
                        temp_val = eval(temp);
                        if (return_val.type == INTEGER_TYPE && temp_val.type == REAL_TYPE)
                            return_val.type = REAL_TYPE;
                        return_val.value += temp_val.value;
                    }
                }
                break;
            case MULT:
                /*if(eval(p->data.function.op1).type == INTEGER_TYPE && eval(p->data.function.op2).type == INTEGER_TYPE)
                {
                    return_val.type = INTEGER_TYPE;
                }
                return_val.value = eval(p->data.function.op1).value * eval(p->data.function.op2).value;*/
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <ADD>\n");
                    return_val.value = 0;
                } else {
                    RETURN_VALUE temp_val = eval(temp);
                    //return_val = temp_val;
                    if (temp_val.type == INTEGER_TYPE)
                        return_val.type = INTEGER_TYPE;
                    return_val.value = temp_val.value;
                    while (temp->next != NULL) {
                        temp = temp->next;
                        temp_val = eval(temp);
                        if (return_val.type == INTEGER_TYPE && temp_val.type == REAL_TYPE)
                            return_val.type = REAL_TYPE;
                        return_val.value *= temp_val.value;
                    }
                }
                break;
            case DIV:
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <DIV>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = eval(temp).value / eval(temp->next).value;
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <DIV>\n");
                }
                //return_val.value = eval(p->data.function.op1).value / eval(p->data.function.op2).value;
                break;
            case REMAINDER:
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <REMAINDER>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = remainder(eval(temp).value, eval(temp->next).value);
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <REMAINDER>\n");
                }
                //return_val.value = remainder(eval(p->data.function.op1).value, eval(p->data.function.op2).value);
                break;
            case LOG:
                if (temp == NULL) {
                    printf("ERROR: too few parameters for the function <LOG>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = log(eval(temp).value);
                    if (temp->next != NULL)
                        printf("WARNING: too many parameters for the function <LOG>\n");
                }
                //return_val.value = log10(eval(p->data.function.op1).value);
                break;
            case POW:
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <POW>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = pow(eval(temp).value, eval(temp->next).value);
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <POW>\n");
                }
                //return_val.value = pow(eval(p->data.function.op1).value, eval(p->data.function.op2).value);
                break;
            case MAX:
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <MAX>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = fmax(eval(temp).value, eval(temp->next).value);
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <MAX>\n");
                }
                //return_val.value = fmax(eval(p->data.function.op1).value, eval(p->data.function.op2).value);
                break;
            case MIN:
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <MIN>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = fmin(eval(temp).value, eval(temp->next).value);
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <MIN>\n");
                }
                //return_val.value = fmin(eval(p->data.function.op1).value, eval(p->data.function.op2).value);
                break;
            case EXP2:
                if (temp == NULL) {
                    printf("ERROR: too few parameters for the function <EXP2>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = exp2(eval(temp).value);
                    if (temp->next != NULL)
                        printf("WARNING: too many parameters for the function <LOG>\n");
                }
                //return_val.value = exp2(eval(p->data.function.op1).value);
                break;
            case CBRT:
                if (temp == NULL) {
                    printf("ERROR: too few parameters for the function <CBRT>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = cbrt(eval(temp).value);
                    if (temp->next != NULL)
                        printf("WARNING: too many parameters for the function <CBRT>\n");
                }
                //return_val.value = cbrt(eval(p->data.function.op1).value);
                break;
            case HYPOT:
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <EXP2>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = hypot(eval(temp).value, eval(temp).value);
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <LOG>\n");
                }
                //return_val.value = hypot(eval(p->data.function.op1).value, eval(p->data.function.op2).value);
                break;
            case PRINT:
                if (temp == NULL) {
                    printf("ERROR: too few parameters for the function <PRINT>\n");
                    return_val.value = 0;
                } else {
                    while (temp != NULL) {
                        return_val = eval(temp);
                        /*if(temp->next != NULL)
                            printf("WARNING: too many parameters for the function <EQUAL>\n");*/
                        if (return_val.type == INTEGER_TYPE) {
                            printf("%.0f\n", return_val.value);
                        } else {
                            printf("%.2f\n", return_val.value);
                        }
                        temp = temp->next;
                    }
                }
                break;
            case EQUAL: {
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <EQUAL>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = eval(temp).value == eval(temp->next).value;
                    //return_val.value = 1;
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <EQUAL>\n");
                }

                //printf("%f\n", return_val.value);
                break;
            }
            case SMALLER: {
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <SMALLER>\n");
                    return_val.value = 0;
                } else {
                    //printf("%s %s \n", temp.)
                    return_val.value = eval(temp).value < eval(temp->next).value;
                    //return_val.value = 1;
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <SMALLER>\n");
                }
                //return_val.value = eval(p->data.function.op1).value < eval(p->data.function.op2).value;
                break;
            }
            case LARGER: {
                if (temp == NULL || temp->next == NULL) {
                    printf("ERROR: too few parameters for the function <LARGER>\n");
                    return_val.value = 0;
                } else {
                    return_val.value = eval(temp).value > eval(temp->next).value;
                    //return_val.value = 1;
                    if (temp->next->next != NULL)
                        printf("WARNING: too many parameters for the function <LARGER>\n");
                }
                //return_val.value = eval(p->data.function.op1).value > eval(p->data.function.op2).value;
                break;
            }
            case RAND: {
                return_val.value = rand();
                if (temp != NULL)
                    printf("WARNING: too many parameters for the function <RAND>\n");
                break;
            }
            default:
                return_val.value = 0;
                break;
        }
    } else if (p->type == SYMBOL_TABLE_TYPE) {
        return_val = eval(p->data.function.opList);
    }

    //return eval(p->data.function.op1) + eval(p->data.function.op2); //testing with ADD
    return return_val;
}

//evaluates a lambda expression
RETURN_VALUE eval_lambda(AST_NODE *orig_op_list, AST_NODE *p) {
    //printf("EVALUATING LAMBDA!\n");
    RETURN_VALUE temp;
    temp.value = 0;
    temp.type = REAL_TYPE;

    SYMBOL_TABLE_NODE *arg_count = p->scope;
    AST_NODE *op_list = orig_op_list;
    while (arg_count) {
        if (arg_count->type == ARG_TYPE) {
            //printf("FOUND ARGUMENT for assignment %s\n", arg_count->ident);
            if (!op_list) {
                printf("TOO FEW ARGUMENTS!\n");
                break;
            }
            //TODO: FIX Bug where you pass entire op_list to argument
            //printf("%s = %lf\n", arg_count->ident, eval(orig_op_list));
            /*if(arg_count->val == NULL)
                printf("%s is EMPTY\n", arg_count->ident);*/

            push(&arg_count->stack, op_list);

            op_list = op_list->next;
            //AST_NODE *test = arg_count->val;
            /*while(test)
            {
                printf("TESTING %s = %lf\n", arg_count->ident, eval(test).value);
                test = test->next;
            }*/
        }
        arg_count = arg_count->next;
    }
    //p->type
    if (op_list != NULL)
        printf("TOO MANY ARGUMENTS!\n");
    //printf("%s\n", p->data.function.name);
    //if(!op_list)
    temp = eval(p);

    //printf("%lf\n", temp.value);
    return temp;
}

//checks to see if a stack is empty
int isEmpty(STACK_NODE *root) {
    return !root;
}

//creates new stack
STACK_NODE *newNode(AST_NODE *data) {
    STACK_NODE *stackNode = (STACK_NODE *) malloc(sizeof(STACK_NODE));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

//pop the top of a stack and return it to the user
AST_NODE *pop(STACK_NODE *root) {
    if (isEmpty(root))
        return NULL;
    STACK_NODE *temp = root;
    root = root->next;
    AST_NODE *popped = temp->data;
    //free(temp);
    return popped;
}

//pushes a AST_NODE onto a given stack
void push(STACK_NODE **root, AST_NODE *data) {
    STACK_NODE *stack_node = newNode(data);
    stack_node->next = *root;
    *root = stack_node;
    //printf("PUSHING \n");
}

AST_NODE *peek(STACK_NODE *root) {
    if (isEmpty(root))
        return NULL;
    return root->data;
}