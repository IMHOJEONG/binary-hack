// 다음과 같이 include를 사용할 수 있습니다.
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static int nx[] = {-1,1,0,0};
static int ny[] = {0,0,-1,1};

int** copyGarden(int **garden, int R, int C) {
    int **g = (int**) malloc(sizeof(int*) * R);
    for (int i = 0; i < R; i++) {
        
        g[i] = (int*) malloc(sizeof(int) * C);
        
        for(int j = 0; j < C; j++) {
            g[i][j] = garden[i][j];
        }
        
    }
    return g;
}

void freeGarden(int **garden, int R) {
    for(int i = 0; i < R; i++) {
        free(garden[i]);
    }
    free(garden);
}

bool isFull(int **garden, int R, int C) {
     for (int i = 0 ; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (garden[i][j] == 0) {
                return false;
            }
        }
    }
    
    return true;
}

int countOne(int **garden, int R, int C) {
    
    int cnt = 0;
    
    for (int i = 0 ; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (garden[i][j] == 1) {
                cnt++;
            }   
        }
    }
    return cnt;
}

int** setOne(int **garden, int R, int C) {
    int **newArr = copyGarden(garden, R, C);
    
    for (int i = 0 ; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (garden[i][j] == 1) {
                
                for (int k = 0; k < 4 ; k++) {
                    int nextR = i + nx[k]; 
                    int nextC = j + ny[k];
                    if (
                        nextR >= 0 &&
                        nextR < R &&
                        nextC >= 0 &&
                        nextC < C
                    ) {
                        newArr[nextR][nextC] = 1;
                    }
                }
            }
        }
    }
    
    return newArr;
}

int solution(int **garden, int garden_row_len, int garden_col_len) {
    if(countOne(garden, garden_row_len, garden_col_len) == 0) return -1;
    int answer = 0;
    int **cur = copyGarden(garden, garden_row_len, garden_col_len);
    
    while(!isFull(cur, garden_row_len, garden_col_len)) 
    {
        int **next = setOne(cur, garden_row_len, garden_col_len); 
        freeGarden(cur, garden_row_len);
        cur = next;
        answer++;
    }
    return answer;
}


// 아래는 테스트케이스 출력을 해보기 위한 main 함수입니다.
int main() {
    int garden1_row_len = 3;
    int garden1_col_len = 3;
    int **garden1 = (int**)malloc(sizeof(int*) * garden1_row_len);
    for(int i = 0; i < garden1_row_len; i++)
        garden1[i] = (int*)malloc(sizeof(int) * garden1_col_len);

    garden1[0][0] = 0;
    garden1[0][1] = 0;
    garden1[0][2] = 0;
    garden1[1][0] = 0;
    garden1[1][1] = 1;
    garden1[1][2] = 0;
    garden1[2][0] = 0;
    garden1[2][1] = 0;
    garden1[2][2] = 0;

    int ret1 = solution(garden1, garden1_row_len, garden1_col_len);

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    printf("solution 함수의 반환 값은 %d 입니다.\n", ret1);

    int garden2_row_len = 2;
    int garden2_col_len = 2;
    int **garden2 = (int**)malloc(sizeof(int*) * garden2_row_len);
    for(int i = 0; i < garden2_row_len; i++)
        garden2[i] = (int*)malloc(sizeof(int) * garden2_col_len);

    garden2[0][0] = 1;
    garden2[0][1] = 1;
    garden2[1][0] = 1;
    garden2[1][1] = 1;

    int ret2 = solution(garden2, garden2_row_len, garden2_col_len);

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    printf("solution 함수의 반환 값은 %d 입니다.\n", ret2);
}