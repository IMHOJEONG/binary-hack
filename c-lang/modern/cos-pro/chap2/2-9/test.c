#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool solution(char* password) {
    int length = strlen(password);
    for(int i = 0; i < length - 2; ++i){
        int firstCheck = password[i + 1] - password[i];
        int secondCheck = password[i+2] - password[i + 1];
        if(firstCheck == secondCheck && (firstCheck == 1 || firstCheck == -1))
            return false;
    }
    return true;
}