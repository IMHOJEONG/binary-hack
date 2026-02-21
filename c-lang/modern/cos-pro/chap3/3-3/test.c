
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void init(int matrix[8][8]) {

		int count = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++){
				matrix[i][j] = 0;
			}
		}
		return;
}

int getCount(int matrix[8][8]) {
		int count = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (matrix[i][j] == 0) {
					count++;
				}
			}
		}

		return count;
	
}

int getIndex(char data[], char result){
	for (int i = 0; i < 8; i++){
		if(data[i] == result) {
			return i;
		}
	}
	return -1;
}
	
int solution(char* bishops[], int bishops_len) {
    int answer = 0;
		char alphabet[8] = {'A','B','C','D','E','F','G','H'};
		int dr[4] = {-1, -1, 1, 1};
		int dc[4] = {-1, 1, -1, 1};
	
		int (*matrix)[8] = malloc(sizeof(int) * 8 * 8);

		init(matrix);
		for (int k = 0; k < bishops_len; k++) {
			int nowR = '8' - bishops[k][1];
			int nowC = getIndex(alphabet, bishops[k][0]);

			matrix[nowR][nowC] = -1;
			int curR = nowR;
			int curC = nowC;
			// printf("%d %d", nowR, nowC);
			
			for (int i = 0; i < 4; i++) {
				for (int j = 1; j < 8; j++) {
					int nextR = curR + j * dr[i];
					int nextC = curC + j * dc[i];
					if (
						nextR >= 0 && nextR < 8 &&
						nextC >= 0 && nextC < 8
					) {
						matrix[nextR][nextC] = -1;
					}					

					curR = nowR;
					curC = nowC;
				}					
				
			}
		}
	
	  answer = getCount(matrix);

		// free(matrix);
	
    return answer;
}

int main() {
    char* bishops1[1] = {"D5"};
    int bishops1_len = 1;
    int ret1 = solution(bishops1, bishops1_len);
    

    printf("solution 함수의 반환 값은 %d 입니다.\n", ret1);

    char* bishops2[3] = {"D5", "E8", "G2"};
    int bishops2_len = 3;
    int ret2 = solution(bishops2, bishops2_len);
    

    printf("solution 함수의 반환 값은 %d 입니다.\n", ret2);
}
