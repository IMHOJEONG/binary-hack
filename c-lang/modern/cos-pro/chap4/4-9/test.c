#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

char* solution(int hour, int minute) {
    char* answer = malloc(10);

	  double hour_angle = (hour % 12) * 30 + minute * 0.5;
		double minute_angle = minute * 6; 

	  // abs, fabs 따로임
		double diff = (double) fabs(hour_angle - minute_angle);

		snprintf(answer, sizeof(answer), "%.1f", diff);

    return answer;
}

int main() {
    int hour = 3;
    int minute = 0;
    char* ret = solution(hour, minute);
    printf("solution 함수의 반환 값은 %s 입니다.\n", ret);
}