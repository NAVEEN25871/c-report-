#ifndef SALARY_H
#define SALARY_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h> // Added for potential string operations in implementations
#define NAME_LEN 50
 typedef struct {
int id;
char name[NAME_LEN]; double basic;
double allowances; // other allowances 
 double deductions; // other deductions
    double gross;      // Computed gross salary
double net;       // Computed net salary
double gross;
} Employee;

// File operations
bool add_employee (const Employee *e, const char *filename);
bool find employee (int id, Employee out, const char *filename); 
bool update employee (const Employee *e, const char *filename); 
bool delete_employee (int id, const char *filename);
void list_employees (const char *filename);
// Calculations
void compute_salary (Employee *e);
#endif // SALARY_H