#ifndef PERSON_H_ /* to prevent re-definitions */
#define PERSON_H_ /* that cause errors */
/*
 * Name: Kevin Green
 * Lab/task: Lab 2 Task 1
 * Date: 2/7/18
 */
typedef char NAME[41];

typedef struct date {
    int month;
    int day;
    int year;
} DATE;

typedef struct person {
    NAME name;
    int age;
    float height;
    DATE bday;
} PERSON;

void add_employee(PERSON *);

//void display_all_employees(PERSON [], int);
void display_employee(PERSON *);

void display_list_of_employee();

void add_employee_to_list();

void delete_employee_from_list();

#endif