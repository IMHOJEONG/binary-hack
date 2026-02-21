
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

char* solution(char* phrases, int second) {
    char* answer = "";

		char arr[15];
		memset(arr, '_', 14);
	  arr[14] = '\0';

	  int len = strlen(phrases);
		int base = abs(strlen(arr) - second);
	
		for (int i = 0 ; i < second ; i++) {
			int pos = (base + i) % 14; 
			arr[pos] = phrases[i % len];
			// printf("%s\n", arr);
		}
		
		answer = arr;
    return answer;
}

int main() {
    char* phrases = "happy-birthday";
    int second = 3;
    char* ret = solution(phrases, second);
    printf("solution 함수의 반환 값은 %s 입니다.\n", ret);
}