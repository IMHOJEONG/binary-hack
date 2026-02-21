#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))


int solution(int board[][4], int board_len) {
    int answer = 0;

    int coins[4][4] = { 0, };
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(i == 0 && j == 0)
                coins[i][j] = board[i][j];
            else if(i == 0 && j != 0)
                coins[i][j] = board[i][j] + coins[i][j-1];
            else if(i != 0 && j == 0)
                coins[i][j] = board[i][j] + coins[i-1][j];
            else
                coins[i][j] = board[i][j] + MAX(coins[i-1][j], coins[i][j-1]);
        }
    }

    answer = coins[3][3];
    return answer;
}


int main() {
    int board[4][4] = {{6, 7, 1, 2}, {3, 5, 3, 9}, {6, 4, 5, 2}, {7, 3, 2, 6}};
    int board_len = 4;
    int ret = solution(board, board_len);

    printf("solution 함수의 반환 값은 %d 입니다.\n", ret);
}