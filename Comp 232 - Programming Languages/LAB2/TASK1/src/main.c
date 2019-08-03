#include <stdio.h>
#include "list.h"
#include "person.h"
#include <string.h>
#include <stdlib.h>

const int BUFFER_SIZE = 10;
/*
 * Name: Kevin Green
 * Lab/task: LAB2 Task 1
 * Date: 2/13/18
 */
//void display_database();
int main() {
    //printf("Hello, World!\n");

    /*add_person();
    display_all();
    // Doesn't work, adds second person twice
    PERSON temp1;
    add_employee(&temp1);
    //display_employee(&temp1);
    add((void*)&temp1);
    //add((void*)5);
    add_employee(&temp1);
    add((void*)&temp1);
    PERSON *temp2 = (PERSON*) delete();
    display_employee(temp2);
    temp2 = (PERSON*)delete();
    display_employee(temp2);
    */
    printf("PLEASE CHOOSE WHAT YOU WANT TO DO\n"
                   "-------------------------------\n"
                   "ADD\nDELETE\nDISPLAY\nEND\n"
                   "-------------------------\n");
    char input_buffer[BUFFER_SIZE];
    while (1) {
        int space = 0;
        char temp = 0;
        //PERSON new;
        while (temp != '\n' && space < BUFFER_SIZE) {
            scanf("%c", &temp);
            input_buffer[space] = temp;
            space++;
        }
        if (strstr(input_buffer, "END")) {
            printf("Quiting Program");
            break;
        } else if (strstr(input_buffer, "ADD")) {
            /*PERSON *temp1;
            temp1 = malloc(sizeof(PERSON));
            add_employee(temp1);
            add((void *) temp1);*/
            //free(&temp1);
            add_employee_to_list();
        } else if (strstr(input_buffer, "DELETE")) {
            PERSON *temp2;
            //temp2 = malloc(sizeof(PERSON));
            /*temp2 = (PERSON *) delete();
            if ((int) temp2 != -1) {
                printf("Deleting:\n");
                display_employee(temp2);
            } else {
                printf("LIST is empty!\n");
            }*/
            delete_employee_from_list();
            //display_employee((PERSON*)delete());
        } else if (strstr(input_buffer, "DISPLAY")) {
            display_list_of_employee();
        } else {
            printf("COMMAND NOT IMPLEMENTED!\n");
        }
    }
    //For testing LIST with simple data structures
    /*
    add((void*)5);
    add((void*)6);
    printf("%d", (int)delete());
    printf("%d", (int)delete());
    */
    return 0;
}
/*void display_database()
{
    LIST *start = get_start();
    if(start == NULL)
    {
        printf("LIST is empty!\n");
    }
    else
        while(start != NULL){
            //display_employee((PERSON*)delete());
            display_employee((PERSON*)start->data);
            start = start->next;
        }
}*/