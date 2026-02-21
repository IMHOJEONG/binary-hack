
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
	
int sum10 (char* s, int p) {
	int sum = 0; 
	int len = strlen(s);
	for (int i = 0 ; i < len ; i++) {
		int num = s[len-1-i] - '0';
		// printf("%d : %d\n", i, num);
		sum += num * pow(p, i);
	}
	// printf("%d\n", sum);
	return sum;
}



char* toQ(int sum, int q) {

	char* box = malloc(50);
	int index = 0; 
	while(sum > 0) {
		box[index++] = '0' + sum % q;
		sum /= q;
	}
	int len = index;
	for (int i = 0 ; i < len / 2  ; i++) {
		char temp = box[i];
		box[i] = box[len - 1 - i];
		box[len - 1 - i] = temp;
	}

	// printf("%d %s\n", sum, box);
	return box;
} 
	

char* solution(char* s1, char* s2, int p, int q) {
    char* answer = "";

		int value = sum10(s1, p) + sum10(s2, p);

		answer = toQ(value, q);
			
    return answer;
}

int main() {
    char* s1 = "112001";
    char* s2 = "12010";
    int p = 3;
    int q = 8;
    char* ret = solution(s1, s2, p, q);

    printf("solution 함수의 반환 값은 %s 입니다.\n", ret);
}