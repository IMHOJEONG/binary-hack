/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int base;
    int bonus;
} Employee;

int cmp(const void* a, const void* b) {
    
    char* nameA = ((Employee *) a)->name;
    char* nameB = ((Employee *) b)->name;
    int baseA = ((Employee *) a)->base;
    int baseB = ((Employee *) b)->base;
    int sumA = baseA + ((Employee *) a)->bonus;
    int sumB = baseB + ((Employee *) b)->bonus;
    
    if (sumA != sumB) {
        return sumB - sumA; 
    }
    else if (baseA != baseB) {
        return baseB - baseA;
    }
    else {
        return strcmp(nameA, nameB);
    }
    
}

int main()
{
    Employee employee[3] = {
        {
            "Kim", 3000, 500
        },
        {
            "Lee", 3200, 200
        },
        {
           "Park", 3000, 700
        }
    };
    
    qsort(employee, 3, sizeof(Employee), cmp);
    
    for (int i = 0 ; i < 3 ; i++) {
        printf("%s %d %d\n", employee[i].name, employee[i].base, employee[i].bonus);
    }

    return 0;
}