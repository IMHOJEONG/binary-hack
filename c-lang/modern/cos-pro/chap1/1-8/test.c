#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int* solution(int N, int votes[], int votes_len) {
    int vote_counter[11] = {0};
    for (int i = 0; i < votes_len; i++) {
        vote_counter[votes[i]] += 1;
    }
    int max_val = 0;
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (max_val < vote_counter[i]) {
            max_val = vote_counter[i];
            cnt = 1;
        }
        else if(max_val == vote_counter[i]){
            cnt += 1;
        }
    }
    
    int* answer = (int*)malloc(sizeof(int)*cnt);
    for(int i = 0; i < cnt; i++)
        answer[i] = 0;
    
    for (int i = 1, idx = 0; i <= N; i++){
        if (vote_counter[i] == max_val) {
            answer[idx] = i;
            idx += 1;
        }
    }
    return answer;
}

int main() {
    int N1 = 5;
    int votes1[10] = {1,5,4,3,2,5,2,5,5,4};
    int votes_len1 = 10;
    int* ret1 = solution(N1, votes1, votes_len1);

 
    printf("solution 함수의 반환 값은 [");
    for(int i = 0; i < 1; i++){
        if (i != 0) printf(", ");
        printf("%d", ret1[i]);
    }
    printf("] 입니다.\n");

    int N2 = 4;
    int votes2[5] = {1,3,2,3,2};
    int votes_len2 = 5;
    int* ret2 = solution(N2, votes2, votes_len2);

 
    printf("solution 함수의 반환 값은 [");
    for(int i = 0; i < 2; i++){
        if (i != 0) printf(",");
        printf("%d", ret2[i]);
    }
    printf("] 입니다.\n");
}