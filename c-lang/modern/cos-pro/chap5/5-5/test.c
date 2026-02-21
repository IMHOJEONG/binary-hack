
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int compare(const int* a, const int* b) {
	return (*a - *b);
}


int solution(int enemies[], int enemies_len, int armies[], int armies_len) {
    int answer = 0;

		int count = 0;
		int newEnemies[enemies_len];
		int newArmies[armies_len];
		for (int i = 0; i < enemies_len ; i++) {
			newEnemies[i] = enemies[i];	
		}
		for (int i = 0; i < armies_len ; i++) {
			newArmies[i] = armies[i];	
		}
	
		qsort(newEnemies, enemies_len, sizeof(int), compare);
		qsort(newArmies, armies_len, sizeof(int), compare);
		// for (int i = 0; i < enemies_len ; i++) {
		// 	printf("%d", 	newEnemies[i]);
		// }
		// for (int i = 0; i < armies_len ; i++) {
		// 	printf("%d", 	armies[i]);
		// }
		// printf("\n");
		for(int i = 0 ; i < armies_len; i++) {
			int armiesData = newArmies[i];
			for(int j = 0 ; j < enemies_len; j++) {
					int enemiesData = newEnemies[j];

					if (armiesData >= enemiesData && enemiesData != -1) {
						count++;
						newEnemies[j] = -1;
					}
					
			}
		}
		answer = count;
	
    return answer;
}

int main() {
    int enemies1[] = {1, 4, 3};
    int enemies_len1 = 3;
    int armies1[] = {1, 3};
    int armies_len1 = 2;
    int ret1 = solution(enemies1, enemies_len1, armies1, armies_len1);

    printf("solution 함수의 반환 값은 %d 입니다.\n", ret1);

    int enemies2[] = {1, 1, 1};
    int enemies_len2 = 3;
    int armies2[] = {1, 2, 3, 4};
    int armies_len2 = 4;
    int ret2 = solution(enemies2, enemies_len2, armies2, armies_len2);

    printf("solution 함수의 반환 값은 %d 입니다.\n", ret2);
}