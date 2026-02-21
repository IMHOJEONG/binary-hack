좋아. “서로 다른 3개를 골라 합이 **K의 배수**인 조합 개수”면 O(n³) 대신 **O(n²)**로 줄일 수 있어.

핵심은 **나머지(모듈러)만 보면 된다**는 점.

---

## 아이디어

세 수 `a, b, c`에 대해

[
(a+b+c) \bmod K = 0
]

`a`와 `b`를 고르면 필요한 `c`의 나머지는 자동으로 결정돼:

[
c \bmod K = (- (a+b)) \bmod K
]
즉
[
need = (K - ((a+b)\bmod K)) \bmod K
]

그래서

* i, j를 고정하고
* j 뒤에 있는 원소들 중 `need` 나머지를 가진 개수를 더하면 됨.

---

## 구현 전략 (가장 쉬운 형태)

* `freq[r]` = “현재 j 뒤(오른쪽)에 있는 수들 중 나머지 r 개수”
* i를 고정할 때마다 freq를 초기화하고,
* j를 움직이면서 freq를 갱신/조회

---

## O(n²) C 코드

```c
#include <stdlib.h>

long long solution(int arr[], int n, int K) {
    long long ans = 0;

    for (int i = 0; i < n - 2; i++) {
        // j보다 오른쪽에 있는 원소들의 나머지 빈도
        int *freq = (int*)calloc(K, sizeof(int));

        // 초기 상태: k = i+2 .. n-1 를 freq에 넣어둠
        for (int k = i + 2; k < n; k++) {
            int r = arr[k] % K;
            if (r < 0) r += K;
            freq[r]++;
        }

        for (int j = i + 1; j < n - 1; j++) {
            int ri = arr[i] % K; if (ri < 0) ri += K;
            int rj = arr[j] % K; if (rj < 0) rj += K;

            int sum = (ri + rj) % K;
            int need = (K - sum) % K;

            ans += freq[need];

            // 다음 j로 넘어가면, k 후보 집합은 (j+2..끝) 이 되어야 함
            // 지금 freq에는 (j+1)도 포함되어 있으므로 제거
            if (j + 1 < n) {
                int rremove = arr[j + 1] % K;
                if (rremove < 0) rremove += K;
                freq[rremove]--;
            }
        }

        free(freq);
    }

    return ans;
}
```

### 왜 이게 O(n²)?

* i 루프: n
* 각 i마다

  * freq 초기화 O(n)
  * j 루프 O(n)
    → 합쳐서 O(n²)

---

## 더 간단한 (하지만 상수 큰) O(n²*K)도 가능

K가 최대 30 같은 작으면, 나머지 카운트만 가지고 조합 공식으로 O(K²)로도 풀 수 있지만(=arr 나머지 빈도만 세서 조합 계산), 그건 “서로 다른 인덱스 3개” 조건을 잘 처리해야 해서 조금 더 조심스러워.

---

## 체크 포인트

* 반환형은 `long long` 추천 (조합 수가 커질 수 있음)
* `arr`에 음수가 있을 수 있으면 `%` 보정(`if (r < 0) r += K`) 필요

---

원하는 방향이 뭐야?

1. **위 O(n²) 구현을 네 스타일로 더 단순화** 해줄까,
2. 아니면 **나머지 빈도만 세서 O(n+K²)**로 푸는 더 수학적인 풀이로 갈까?
