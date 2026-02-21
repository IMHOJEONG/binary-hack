이 코드는 의도 자체는 “**서로 다른 소수 3개의 합이 n이 되는 조합 개수**”를 세는 건데, 지금 구현은 두 군데가 크게 문제야.

---

## 1) 지금 코드의 문제점

### ✅ (1) 소수 판별이 너무 느림 (O(n²))

```c
for (int j = 2; j < i; j++)
```

이건 `i`가 커질수록 최악이야. 최소한 `j*j <= i`까지만 보면 됨.

### ✅ (2) `primes[168]`은 n이 커지면 터짐

168은 “1000 이하 소수 개수” 정도 수준이라, n이 1000 넘어가면 소수 개수가 168보다 커져서 **배열 오버플로우** 날 수 있어.

---

## 2) 빠르고 안전한 버전 (추천)

### 핵심 개선

* 소수 목록은 **에라토스테네스의 체**로 O(n log log n)
* primes 배열은 동적 할당(최대 n개까지 가능)

```c
#include <stdlib.h>
#include <stdbool.h>

int solution(int n) {
    int answer = 0;
    if (n < 2) return 0;

    // sieve
    bool* isPrime = (bool*)malloc((n + 1) * sizeof(bool));
    if (!isPrime) return 0;

    for (int i = 0; i <= n; i++) isPrime[i] = true;
    if (n >= 0) isPrime[0] = false;
    if (n >= 1) isPrime[1] = false;

    for (int p = 2; p * p <= n; p++) {
        if (isPrime[p]) {
            for (int x = p * p; x <= n; x += p) {
                isPrime[x] = false;
            }
        }
    }

    // collect primes
    int* primes = (int*)malloc((n + 1) * sizeof(int)); // 넉넉히
    if (!primes) { free(isPrime); return 0; }

    int prime_len = 0;
    for (int i = 2; i <= n; i++) {
        if (isPrime[i]) primes[prime_len++] = i;
    }

    // count combinations (i<j<k)
    for (int i = 0; i < prime_len - 2; i++) {
        for (int j = i + 1; j < prime_len - 1; j++) {
            int partial = primes[i] + primes[j];
            if (partial >= n) break; // 이후 k는 더 커지므로 조기 종료 가능

            for (int k = j + 1; k < prime_len; k++) {
                int sum = partial + primes[k];
                if (sum == n) answer++;
                else if (sum > n) break; // primes[k]는 증가하므로 더 보면 무조건 커짐
            }
        }
    }

    free(primes);
    free(isPrime);
    return answer;
}
```

---

## 3) “원래 코드”를 최소 수정만 해서 살리면

소수 판별만이라도 이렇게 바꾸면 훨씬 나아져:

```c
for (int j = 2; j * j <= i; j++)
```

그리고 `primes[168]` 대신 `malloc(n*sizeof(int))` 같은 식으로 바꿔야 안전.

---

## 4) 이 함수가 세는 것

* **서로 다른 소수 3개** (인덱스 i<j<k라서 중복/순열 아님)
* 예: n=33이면 3+7+23 같은 조합을 카운트

---

원하는 게 “중복 허용(예: 11+11+11)”까지 포함인지, 아니면 지금처럼 “서로 다른 3개”인지도 확인해줘. 지금 코드는 **중복 불허**로 세고 있어.
