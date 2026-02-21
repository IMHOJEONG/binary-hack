#include <stdlib.h>

static int max2(
    int a, 
    int b
) {
    return a > b ? a : b;
}

int solution(int number, int target) {
    
    if (number == target) {
        return 0;
    }

    int maxv = max2(number, target);

    // 이 부분 어려움 
    int LIMIT = 2 * maxv + 2;
    if (LIMIT < 10) LIMIT = 10;


    int *dist = (int*)malloc(sizeof(int) * (LIMIT + 1));
    for (int i = 0; i < LIMIT; i++) {
        dist[i] = -1;
    }

    // queue 
    // int *q = malloc(sizeof *q * (LIMIT + 1));
    // if (!q) return -1;
    
    int *q = (int*)malloc(sizeof(int) * (LIMIT + 1));
    int head = 0, tail = 0;


    // start
    dist[number] = 0; 
    q[tail++] = number;

    while (head < tail) {
        int x = q[head++];

        int cand[3] = { x - 1, x + 1, x * 2};

        for (int k = 0; k < 3 ; k++) {

            int nx = cand[k];

            if (nx < 0 || nx > LIMIT) continue;
            if (dist[nx] != -1) continue;

            dist[nx] = dist[x] + 1;

            if (nx == target) {
                int ans = dist[nx];
                free(dist);
                free(q);
                return ans;
            }

            q[tail++] = nx;
        }
    }

    // 
    free(dist);
    free(q);
    return -1;

}