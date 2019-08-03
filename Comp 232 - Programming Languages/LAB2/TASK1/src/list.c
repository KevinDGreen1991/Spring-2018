#include <stdio.h>
#include <stdlib.h>
#include "list.h"
//#include "person.h"

/*int main(void){
	start=end=NULL;
	add(&start, &end, 2);
	add(&start, &end, 3);
	printf("First element: %d\n", delete(&start, &end));
	printf("Second element: %d\n", delete(&start, &end));
	printf("Third element: %d\n", delete(&start, &end));
}*/
LIST *start, *end;

void add(void *data) {
    if (end == NULL) {
        start = end = (LIST *) malloc(sizeof(LIST));
        start->data = data;
        start->next = NULL;
    } else {
        end->next = (LIST *) malloc(sizeof(LIST));
        end = end->next;
        end->data = data;
        end->next = NULL;
    }
}

void *delete() {
    LIST *temp;

    if (start == NULL)
        return (void *) -1;

    void *retVal = (start)->data;

    if (start == end) {
        free(start);
        start = end = NULL;
    } else {
        temp = start->next;
        free(start);
        start = temp;
    }

    return retVal;
}

LIST *get_start() {
    return start;
}

