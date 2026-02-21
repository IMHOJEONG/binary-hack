#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


//  Union-Find 
int find(int parent[], int u) {
	if(u == parent[u])
		return u;

	parent[u] = find(parent, parent[u]);
	return parent[u];
}

int merge(int parent[], int u, int v) {
	u = find(parent, u);
	v = find(parent, v);

	if(u == v)
		return 1;

	parent[u] = v;
	return 0;
}

int solution(int n, int connections[][2], int connections_len) {
    int answer = 0;

    int *parent = (int *) malloc(sizeof(int) * (n+1));
    for(int i = 1; i <= n; i++)
    	parent[i] = i;

    for(int i = 0; i < connections_len; i++)
    	if(merge(parent, connections[i][0], connections[i][1])) {
    		answer = i + 1;
    		break;
    	}

    return answer;
}

int main() {
	int n = 3;
	int connections[][2] = {{1, 2}, {1, 3}, {2, 3}};
	int connections_len = 3;
	int ret = solution(n, connections, connections_len);

	printf("solution 함수의 반환 값은 %d 입니다.\n", ret);
}