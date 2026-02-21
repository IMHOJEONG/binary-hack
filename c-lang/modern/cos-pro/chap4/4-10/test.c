
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool only(int a) {
	bool isTrue = true;
	for (int i = 2; i < a ; i++) {

			if (a % i == 0) {
				isTrue = false;
				break;
			}
	}
	
	return isTrue;
}

int solution(int a, int b) { 
    int answer = 0;

		int pow2 = 0, pow3 = 0;

		// a이상 b이하인 자연수 중 소수의 제곱수, 세제곱수의 개수는?
	
		for (int i = a ; i <= b ; i++) {
				double pow1_2 = pow(i, 1.0/2.0);
			  double intPow1 = pow1_2 - (int) pow1_2;
				if (intPow1 == 0.0) {
					bool result1_2 = only(pow1_2);
					pow2 += result1_2 ? 1 : 0;
				}
			
				double pow1_3 = pow(i, 1.0/3.0);
				double intPow2 = pow1_3 - (int) pow1_3;
				if (intPow2 == 0.0) {
					bool result1_3 = only(pow1_3);
					pow3 += result1_3 ? 1 : 0;
				}
			

				// printf("%.1f %.1f %d %d\n", intPow1, intPow2, intPow1 == 0.0, intPow2 == 0.0);
				// printf("------ %d ----- %.1f %d %.1f %d\n", i, pow1_2, only(pow1_2),  pow1_3, only(pow1_3));
		}

		answer = pow2 + pow3;
			
    return answer;
}
	
int main() {
    int a = 6;
    int b = 30;
    int ret = solution(a, b);

    printf("solution 함수의 반환 값은 %d 입니다.\n", ret);
}