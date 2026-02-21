int* solution(char* commands) {
    int* answer = malloc(sizeof(int) * 2);
		answer[0] = 0;
		answer[1] = 0;

		char* arr = "LRUD";

		int dr[4] = { -1, 1, 0 , 0};
		int dc[4] = { 0, 0, 1 , -1};
		int len = strlen(commands);
		// printf("%d %d", answer[0], answer[1]);

		for(int i = 0; i < len; i++) {
				if (commands[i] == 'L') {
					answer[0] += dr[0];
					answer[1] += dc[0];
				}
				if (commands[i] == 'R') {
					answer[0] += dr[1];
					answer[1] += dc[1];
				}
				if (commands[i] == 'U') {
					answer[0] += dr[2];
					answer[1] += dc[2];
				}
				if (commands[i] == 'D') {
					answer[0] += dr[3];
					answer[1] += dc[3];
				}
			
		}

    return answer;
}