#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int max(int a, int b){
    return a < b ? b : a;
}

int solution(int grid[][4], int grid_len) {
    int answer = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            for(int k = j + 1; k < 4; k += 2)
                answer = max(answer, max(grid[i][j] + grid[j][k], grid[i][j] + grid[k][i]));
    return answer;
}

int main() {
	int grid[][4] = {{1, 4, 16, 1}, {20, 5, 15, 8}, {6, 13, 36, 14}, {20, 7, 19, 15}};
	int grid_len = 4;
	int ret = solution(grid, grid_len);

	printf("solution 함수의 반환 값은 %d 입니다.\n", ret);
}