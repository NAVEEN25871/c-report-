#include <stdio.h>  // Added for FILE and printf (good 
practice, even if salary.h includes it) 
#include <stdlib.h> 
#include <string.h> 
#include "salary.h" 
// Compute gross and net. 
// Gross = basic + allowances; Net = gross - deductions 
void compute_salary(Employee *e) { 
e->gross = e->basic + e->allowances; 
e->net = e->gross - e->deductions; 
} 
bool add_employee(const Employee *e, const char *filename) 
{ 
FILE *fp = fopen(filename, "ab"); 
if (!fp) return false; 
if (fwrite(e, sizeof(Employee), 1, fp) != 1) { 
fclose(fp); 
return false; 
} 
    fclose(fp); 
    return true; 
} 
 
bool find_employee(int id, Employee *out, const char 
*filename) { 
    FILE *fp = fopen(filename, "rb"); 
    if (!fp) return false; 
     
    Employee tmp; 
    bool found = false; 
    while (fread(&tmp, sizeof(Employee), 1, fp) == 1) { 
        if (tmp.id == id) { 
            *out = tmp; 
            found = true; 
            break; 
        } 
    } 
    fclose(fp); 
    return found; 
} 
 
bool update_employee(const Employee *e, const char 
*filename) { 
    FILE *fp = fopen(filename, "rb"); 
    if (!fp) return false; 
     
    FILE *tf = fopen("temp.dat", "wb"); 
    if (!tf) {  
        fclose(fp);  
        return false;  
    } 
 
    Employee tmp; 
    bool found = false; 
     
    while (fread(&tmp, sizeof(Employee), 1, fp) == 1) { 
        if (tmp.id == e->id) { 
            // Write the new (updated) employee data 
            fwrite(e, sizeof(Employee), 1, tf); 
            found = true; 
        } else { 
            // Write existing data 
            fwrite(&tmp, sizeof(Employee), 1, tf); 
        } 
    } 
     
    fclose(fp); 
    fclose(tf); 
 
    if (found) { 
        remove(filename); 
        rename("temp.dat", filename); 
        return true; 
    } else { 
        remove("temp.dat"); 
        return false; 
    } 
} 
 
bool delete_employee(int id, const char *filename) { 
    FILE *fp = fopen(filename, "rb"); 
    if (!fp) return false; 
 
    FILE *tf = fopen("temp.dat", "wb"); 
    if (!tf) { 
        fclose(fp); 
        return false; 
    } 
 
    Employee tmp; 
    bool found = false; 
 
    while (fread(&tmp, sizeof(Employee), 1, fp) == 1) { 
        if (tmp.id == id) { 
            found = true; 
            // Do not write this record to temp file (effectively 
deleting it) 
        } else { 
            fwrite(&tmp, sizeof(Employee), 1, tf); 
        } 
    } 
 
    fclose(fp); 
    fclose(tf); 
 
    if (found) { 
        remove(filename); 
        rename("temp.dat", filename); 
        return true; 
    } else { 
        remove("temp.dat"); 
        return false; 
    } 
} 
 
void list_employees(const char *filename) { 
    FILE *fp = fopen(filename, "rb"); 
    if (!fp) { 
        printf("No data found or file error.\n"); 
        return; 
    } 
 
    Employee e; 
    printf("\n%-5s %-20s %-10s %-10s %-10s %-10s %-10s\n",  
           "ID", "Name", "Basic", "Allow", "Deduct", "Gross", 
"Net"); 
    printf("--------------------------------------------------------------------------------\n"); 
    while (fread(&e, sizeof(Employee), 1, fp) == 1) { 
printf("%-5d %-20s %-10.2f %-10.2f %-10.2f %-10.2f %
10.2f\n",  
e.id, e.name, e.basic, e.allowances, e.deductions, 
e.gross, e.net); 
} 
printf("--------------------------------------------------------------------------------\n"); 
fclose(fp); 
}