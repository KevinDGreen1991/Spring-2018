#include <stdio.h>
#include "person.h"
#include <stdlib.h>
#include <string.h>
#include "list.h"
//typedef struct person employees[10];
/*
 * Name: Kevin Green
 * Lab/task: LAB2 Task 1
 * Date: 2/7/18
 */
void add_employee(PERSON *add) {
    //printf("Testing add_employee\n");
    printf("Name: ");
    //NAME name[41];
    scanf("%s", add->name);
    printf("Age: ");
    scanf("%d", &add->age);
    printf("Height: ");
    scanf("%f", &add->height);
    printf("Birthday (#/#/#): ");
    scanf("%d/%d/%d\n", &add->bday.day, &add->bday.month, &add->bday.year);

    //printf("%s", name);
    //*add->name = name;
    //*add->name = (char *) malloc(strlen(name)+1);
    //add->name = (char *) malloc(strlen(name)+1);
    //strcpy(word, words[count]);
    //strcpy(add->name, name);
    //add->name = name;
    //printf(add->name);
}

void display_employee(PERSON *dis) {
    //printf("Testing display_employee\n");
    printf("%s Age: %d, Height: %.2f, Birthday: %d/%d/%d\n", dis->name, dis->age, dis->height, dis->bday.day,
           dis->bday.month, dis->bday.year);
    //printf("%d", dis->age);
}

/*
void display_all_employees(PERSON list[], int size)
{
    //printf("Testing display_all_employees\n");
    //display_employee(&list[0]);
    //display_employee(&list[1]);
    for(int x = 0; x < size; x++)
    {
        display_employee(&list[x]);
    }
}
*/
void display_list_of_employee() {
    LIST *start = get_start();
    if (start == NULL) {
        printf("LIST is empty!\n");
    } else
        while (start != NULL) {
            //display_employee((PERSON*)delete());
            display_employee((PERSON *) start->data);
            start = start->next;
        }
}

void add_employee_to_list() {
    PERSON *temp1;
    temp1 = malloc(sizeof(PERSON));
    add_employee(temp1);
    add((void *) temp1);
}

void delete_employee_from_list() {
    PERSON *temp2 = (PERSON *) delete();
    if ((int) temp2 != -1) {
        printf("Deleting:\n");
        display_employee(temp2);
    } else {
        printf("LIST is empty!\n");
    }
}