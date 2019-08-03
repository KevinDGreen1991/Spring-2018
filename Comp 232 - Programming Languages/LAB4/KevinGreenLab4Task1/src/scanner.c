/**
* Name: Kevin Green
* Lab/task: Lab 4 Task 1
* Date: 02/28/18
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include <ctype.h>

const char *token2str[] = {"INVALID", "NUMBER", "IDENT", "ASSIGNMENT", "SEMICOLON", "LPAREN", "RPAREN", "PLUS", "MINUS",
                           "MULT", "DIV", "MOD", "REPEAT", "PRINT", "END_OF_INPUT"};

TRANS_TABLE_TYPE *scan_init(FILE *file) //assumes that first column is whitespace, and last column is token name
{
    TRANS_TABLE_TYPE *new_table = (TRANS_TABLE_TYPE *) malloc(sizeof(TRANS_TABLE_TYPE));
    char temp_str[BUF_SIZE];
    //temp_str[0] = '';
    //int ch;
    int row = 0;
    int column = 0;
    //printf("%d %d\n", i, j);

    new_table->table = malloc(sizeof(char[BUF_SIZE][BUF_SIZE]));
    //gets rows of file and assigns it to new_array, and counts number of rows to ensure no out of bounds later
    while (fgets(temp_str, BUF_SIZE, file) != NULL) {
        //fgets(temp_table[i], 128, file);
        //printf("%s", temp_table[row]);
        new_table->table[row] = malloc(sizeof(temp_str) + 1);
        strcpy(new_table->table[row], temp_str);
        //strcpy(temp_str, "");
        //printf("%s",new_table->table[row]);
        row++;
    }
    //printf("%d", row);
    new_table->number_of_rows = row - 1;
    for (int i = 0; new_table->table[0][i] != '\0'; i++) {
        if (new_table->table[0][i] == ' ')
            column++;
    }
    new_table->number_of_columns = column;
    //printf("ROWS: %d COLUMNS: %d", new_table->number_of_rows, new_table->number_of_columns);
    //printf("%s", new_table->table[row+1]);
    return new_table;
}

TOKEN *
scan(TRANS_TABLE_TYPE *table)//takes trans_table as parameter, then based on current character gets proper sequence of states that leads to accept state
//Assumes table uses full name of TOKEN in last column for assigning token->number
{
    TOKEN *token = (TOKEN *) malloc(sizeof(TOKEN));
    token->type = INVALID_TOKEN;
    token->strVal = NULL;
    int current;
    int state = 1;
    char temp_string[BUF_SIZE] = "";
    char *command;
    int i = 0;
    while ((token->type == INVALID_TOKEN) && (current = getchar()) != EOF) {

        if ((char) current == ' ' || (char) current == '\t' || (char) current == '\n') {
            command = get_command(table->table[state], get_column(table->table[0], 'w'));
        } else if (isdigit(current) != 0) {
            command = get_command(table->table[state], get_column(table->table[0], 'd'));
            temp_string[i] = (char) current;
            i++;
        } else if (isalpha(current) != 0) {
            //printf("%c %s\n", current, get_command(table, state, get_column(first_line, 'l')));
            command = get_command(table->table[state], get_column(table->table[0], 'l'));
            temp_string[i] = (char) current;
            i++;
        } else {
            command = get_command(table->table[state], get_column(table->table[0], (char) current));
        }

        int temp_state = 0;
        if (isdigit(command[0]))
            temp_state = (int) strtol(command, NULL, 10);

        if (temp_state != 0)
            state = temp_state;
        else if (command[0] == 'a') {
            char *temp = malloc(strlen(get_command(table->table[state], table->number_of_columns)));
            strcpy(temp, get_command(table->table[state], table->number_of_columns));
            if (temp[strlen(temp) - 1] == '\n')
                temp[strlen(temp) - 1] = '\0';
            int type = get_token_number(temp);
            token->type = (TOKEN_TYPE) type;
            if (token->type == IDENTTOKEN) {
                if (strcmp(temp_string, "print") == 0) {
                    token->type = PRINT;
                    token->strVal = NULL;
                    //printf("PRINT detected\n");
                } else if (strcmp(temp_string, "repeat") == 0) {
                    token->type = REPEAT;
                    token->strVal = "";
                    //printf("REPEAT detected!\n");
                } else {
                    token->strVal = (char *) malloc(strlen(temp_string) + 1);
                    strcpy(token->strVal, temp_string);
                }
            } else if (token->type == NUMBERTOKEN) {
                token->strVal = (char *) malloc(strlen(temp_string) + 1);
                strcpy(token->strVal, temp_string);
            } else {
                token->strVal = NULL;
            }
            ungetc(current, stdin);
        } else {
            break;
        }

    }
    if (current == EOF &&
        state == 1)//Two different catches to differentiate between true EOF and EOF with one TOKEN left to output
    {
        token->type = END_OF_INPUT_TOKEN;
    } else if (current == EOF) {
        char *temp = malloc(strlen(get_command(table->table[state], table->number_of_columns)));
        strcpy(temp, get_command(table->table[state], table->number_of_columns));
        if (temp[strlen(temp) - 1] == '\n')
            temp[strlen(temp) - 1] = '\0';
        int type = get_token_number(temp);
        token->type = (TOKEN_TYPE) type;
        token->strVal = (char *) malloc(strlen(temp_string) + 1);
        strcpy(token->strVal, temp_string);
        ungetc(current, stdin);
    }

    return token;
}

TOKEN_TYPE
get_token_number(char *line)//takes a string (the name of the TOKEN_TYPE), then finds the proper token2str[] position
{
    char *temp_line = malloc(strlen(line) + 1);
    strcpy(temp_line, line);
    int i = 0;
    for (int x = 0; x < TOKEN_ARRAY_SIZE && i == 0; x++) {
        //printf("%s ", token2str[x]);
        if (strcmp(temp_line, token2str[x]) == 0)
            i = x;
    }
    /*for(int x =0; x<10; x++)
    {
        if(strcmp(temp_line, token2str[x]) == 0)
            i =x;
    }*/
    return (TOKEN_TYPE) i;
}

char *get_command(char *line,
                  int column)//Takes the proper row from the trans_table, then finds the corresponding command with the column
{
    char *temp_line = malloc(strlen(line) + 1);
    strcpy(temp_line, line);
    char seps[] = " ";
    char *command;
    //char command[BUF_SIZE];
    //int var;
    //char *input[table->number_of_rows];
    int i = 0;

    command = strtok(temp_line, seps);
    while (command != NULL && i < column) {
        //sscanf (token, "%d", &var);
        //input[i++] = var;
        //printf("%s\n", token);

        command = strtok(NULL, seps);
        i++;
    }
    /*char command[10];
    //char command[BUF_SIZE];
    //int var;
    //char *input[table->number_of_rows];

    int i = 0;

    //command = strtok (table->table[row], seps);
    strcpy(command, strtok(table->table[row], seps));
    while (command != NULL && i < column)
    {
        //sscanf (token, "%d", &var);
        //input[i++] = var;
        printf("%s\n", command);
        strcpy(command, strtok(table->table[row], seps));
        i++;
    }*/
    return command;
}

int get_column(char *first_line,
               char search)//Takes the 1st row of the table, the finds the column that matches with the command that we are searching for, then returns the column
{
    char seps[] = " ";
    char *temp_line = malloc(strlen(first_line) + 1);
    strcpy(temp_line, first_line);
    char *command;
    int i = 0;
    command = strtok(temp_line, seps);
    while (command != NULL && command[0] != search) {
        command = strtok(NULL, seps);
        i++;
    }
    return i;
}

char *token_str(int type)//returns a string of the tokens type
{
    return (char *) token2str[type];
}
