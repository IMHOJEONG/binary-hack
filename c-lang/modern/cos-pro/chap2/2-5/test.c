int solution(int arr[], int arr_len) {
    int answer = -1;
		int p1 = 0, p2 = 1; 
		int count = 0; 

		for (int i = 0; i < arr_len-1; i++) {
			int nowV = arr[i];
			for (int j = i+1; j < arr_len; j++) {
				  int nextV = arr[j];
					answer = max(nextV, nowV);
			}
		}
	
    return answer;
}