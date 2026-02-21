
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int overlap(const char* a, const char* b) {
	int lenA = strlen(a);
	int lenB = strlen(b);

	int max = lenA < lenB ? lenA : lenB;

	for(int k = max ; k > 0; k--) {
		if (strncmp(a + lenA - k, b, k) == 0) {
			return k;
		}
	}

	return 0;
}


int solution(char* s1, char* s2) {
    int answer = 0;

		int len1 = strlen(s1); 
	  int len2 = strlen(s2);

		int o1 = overlap(s1, s2);
		int o2 = overlap(s2, s1);

	  int res1 = len1 + len2 - o1;
	  int res2 = len1 + len2 - o2;
	
    return res1 < res2 ? res1 : res2;
}

int main() {
    char* s1 = "ababc";
    char* s2 = "abcdab";
    int ret = solution(s1, s2);


    printf("solution 함수의 반환 값은 %d 입니다.\n", ret);
}