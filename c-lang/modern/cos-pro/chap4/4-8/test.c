
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int toInt(int arr[], int len) {

	int result = 0; 
	for (int i = 0 ; i < len ; i++) {
		result = result * 10 + arr[i];
	}

	return result;
} 

void perm(bool isVisited[], int len, int start, int card[], int *order, int *answer, int result[], int n) {

	if ( *answer != -1 ) return;
	
	if (start == len) {

		(*order)++;
		
		int value = toInt(result, len);
		// printf("%d\n", value);

		if (value == n) {
			(*answer) = (*order);
		}
		
		return;
	}
	
	for (int i = 0; i < len; i++) {
		if (isVisited[i] == true) continue;

		if (i > 0 && card[i] == card[i-1] && !isVisited[i-1]) {
	    continue;
		}

		isVisited[i] = true;
		result[start] = card[i];
		perm(isVisited, len, start+1, card, order, answer, result, n);
		isVisited[i] = false;
	}

}


int solution(int card[], int card_len, int n) {

		bool isVisited[card_len];
		for (int i = 0; i < card_len; i++) {
		    isVisited[i] = false;
		}
		int result[card_len];
		int cardbox[card_len];
		for (int i = 0 ; i < card_len ; i++) {
				cardbox[i] = card[i];
			}
		qsort(cardbox, card_len, sizeof(int), cmp);

		int order = 0;
		int answer = -1;

		perm(isVisited, card_len, 0, cardbox, &order, &answer, result, n);
	
    return answer;
}


int main() {
    int card1[] = {1, 2, 1, 3};
    int card_len1 = 4;
    int n1 = 1312;
    int ret1 = solution(card1, card_len1, n1);

    printf("solution 함수의 반환 값은 %d 입니다.\n", ret1);
    int card2[] = {1, 1, 1, 2};
    int card_len2 = 4;
    int n2 = 1122;
    int ret2 = solution(card2, card_len2, n2);

    printf("solution 함수의 반환 값은 %d 입니다.\n", ret2);
}