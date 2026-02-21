
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int solution(int n, int garden[][n]) {
    int answer = 0;
	  int dr[4] = {-1,1,0, 0};
	  int dc[4] = {0,0, -1, 1};
		int sum = 0; 
		for (int i = 0 ; i < n ; i++) {
			for (int j = 0 ; j < n ; j++) {
				if (garden[i][j] == 1) {
					sum += 1;
				}
			}
		}
		while (sum < n * n) {
			
			for (int i = 0 ; i < n ; i++) {
				for (int j = 0 ; j < n ; j++) {
					if (garden[i][j] == 1) {
						
						for (int k = 0 ; k < 4 ; k++) {
							int nextR = i + dr[k];
							int nextC = j + dc[k];

							if (
								nextR >= 0 && nextR < n &&
								nextC >= 0 && nextC < n
								) {
									garden[nextR][nextC] = 1;
								}
						}
					}
				}
			}

			answer++;
			sum = 0;
			for (int i = 0 ; i < n ; i++) {
				for (int j = 0 ; j < n ; j++) {
					if (garden[i][j] == 1) {
						sum += 1;
					}
				}
			}
			
		}
	
    return answer;
}

int main() {
    int n1 = 3;
    int garden1[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    int ret1 = solution(n1, garden1);
    
    printf("solution 함수의 반환 값은 %d 입니다.\n", ret1);
    
    int n2 = 2;
    int garden2[2][2] = {{1, 1}, {1, 1}};
    int ret2 = solution(n2, garden2);
    
    printf("solution 함수의 반환 값은 %d 입니다.\n", ret2);
}