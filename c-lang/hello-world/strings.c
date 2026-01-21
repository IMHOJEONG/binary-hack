#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int main() {
    
    char * first_name = "John";
    char last_name[20] = "Doe";

    char *full_name = NULL;

    int len = snprintf(full_name, 0, "%s%s", first_name, last_name);

    full_name = malloc(len + 1);
    snprintf(full_name, len + 1, "%s %s", first_name, last_name);

    printf("name : %s\n", full_name);
    return 0;
}