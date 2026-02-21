#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int func_a(char* times) {
    char first_num[10] = {0};
    char second_num[10] = {0};
    strncpy(first_num, times, 2);
    strncpy(second_num, times+3,3);
    int hour = atoi(first_num);
    int minute = atoi(second_num);

    return hour * 60 + minute;
}

int solution(char* subway_times[], 
    int subway_times_len, 
    char* current_time
) {
    int current_minute = func_a(current_time);
    int INF = 1000000000;
    int answer = INF;
    for (int i = 0; i < subway_times_len; ++i) {
        int subway_minute =
            func_a(subway_times[i]);
        
        if (subway_minute - current_minute >= 0
            && answer >= subway_minute - current_minute
        ) {
            answer = subway_minute - current_minute;
            break;
        }
    }

    if (answer == INF) {
        return -1;
    }

    return answer;
}