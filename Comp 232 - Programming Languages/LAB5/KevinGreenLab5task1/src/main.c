#include <stdio.h>
#include "parser.h"

//typedef enum {IDENTIFIER = 1, NUMBER, EXPR, TERM, ASSIGN_STMT, REPEAT_STMT, PRINT_STMT, FACTOR, ADDOP, MULTOP, PROGRAM, STATEMENT} AST_NODE_TYPE;
char *node2str[] = {"idNode", "numberNode", "expr", "term", "assignStmt", "repeatStmt", "printStmt", "factor", "addOP",
                    "multOP", "program", "statement"};

int get_children(AST_NODE *program) {
    if (program->right_node)
        return 2;
    else if (program->left_node)
        return 1;
    else
        return 0;
}

void print_node(AST_NODE *program) {
    //int temp = get_children(program);
    printf("%s: children %d", node2str[program->type], get_children(program));
    if (program->type == IDENTIFIER)
        printf(", data: %s", program->data.identifier);
    else if (program->type == NUMBER)
        printf(", data: %.lf", program->data.number);
    else if (program->type == ADDOP)
        printf(", data: %c", program->data.addOp);
    else if (program->type == MULTOP)
        printf(", data: %c", program->data.multOp);
    printf("\n");
}

void print_program(AST_NODE *program) {
    //printf("%s\n", node2str[program->type]);
    if (program != NULL) {
        //printf("Traversing tree.. %s: children %d\n", node2str[program->type], get_children(program));
        printf("Traversing Tree.. ");
        print_node(program);
        print_program(program->left_node);
        print_program(program->right_node);
    }

}

void abstract_print(AST_NODE *program) {
    if (program != NULL) {
        if (program->type == ASSIGN_STMT || program->type == REPEAT_STMT || program->type == PRINT_STMT ||
            program->type == MULTOP || program->type == ADDOP || program->type == IDENTIFIER ||
            program->type == NUMBER) {
            printf("Abstract Traverse.. ");
            print_node(program);
        }
        abstract_print(program->left_node);
        abstract_print(program->right_node);
    }
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        freopen(argv[1], "r", stdin);
    }
    AST_NODE *fullProgram = program();
    //printf("%s\n", node2str[fullProgram->type]);
    printf("---FULL TREE---\n");
    print_program(fullProgram);
    printf("\n---ABSTRACT TREE---\n");
    abstract_print(fullProgram);
    //printf("%s\n", node2str[fullProgram->type]);
    return 0;
}