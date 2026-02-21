int solution(int arr[], int arr_len, int K) {
    int answer = 0;

		for (int i = 0; i < arr_len-2; i++) {
			for (int j = i+1; j < arr_len-1; j++) {
				for (int k = j+1; k < arr_len; k++) {
						int sum = arr[i] + arr[j] + arr[k];
						if (sum % k == 0) {
							answer++;
						}
				}
			}
		}

	
	
    return answer;
}