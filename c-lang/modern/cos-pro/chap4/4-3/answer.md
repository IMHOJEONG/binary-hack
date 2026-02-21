이 코드는 “1일권 vs `multi_day`일권(묶음권)” 중에서 **총 n일을 가장 싸게 사는 비용**을 구하려는 거야.
근데 현재 로직은 **항상 `(n/multi_day)`개 묶음 + 나머지는 1일권**만 고려해서, 어떤 경우엔 최적이 아니야.

---

## 1) 지금 코드가 틀릴 수 있는 반례

묶음권이 1일권보다 “일당”은 싸더라도, **나머지 처리에서 묶음권을 하나 더 사는 게 더 싸**질 수 있어.

예:

* 1일권 3원
* 5일권 14원
* n = 9

현재 코드:

* (9/5)=1개 묶음(14) + 4일권(12) = 26

하지만:

* 묶음 2개(28)로 10일 커버 → 28 (더 비싸네) 이 반례는 아님

다른 예:

* 1일권 4
* 5일권 10
* n=6

현재 코드:

* 1묶음 10 + 1일권 4 = 14
  하지만:
* 2묶음 20 (더 비싸)
  여기도 아님.

진짜 반례는 “나머지 일수 * 1일권”이 묶음권 1개보다 비쌀 때:

* 1일권 6
* 5일권 14
* n = 9
  현재: 1묶음 14 + 4*6=24 → 38
  대안: 2묶음 28 → 28 ✅ 훨씬 쌈

즉, **묶음권을 ‘올림’해서 하나 더 사는 경우**도 비교해야 함.

---

## 2) 정답 로직(핵심)

최소 비용은 아래 두 후보 중 최소야:

1. `floor` 묶음 + 나머지 1일권
2. `ceil` 묶음 (묶음권만으로 커버, 남는 날은 버림)

그리고 “묶음권이 아예 손해”면 전부 1일권.

---

## ✅ 수정된 정답 코드

```c
#include <stdlib.h>

long long solution(int one_day_price, int multi_day, int multi_day_price, long long n) {
    long long one = one_day_price;
    long long mday = multi_day;
    long long mp = multi_day_price;

    // 묶음이 일당으로도 이득이 없으면 무조건 1일권
    if (one * mday <= mp) return n * one;

    long long bundles = n / mday;
    long long rem = n % mday;

    long long cost_floor = bundles * mp + rem * one;
    long long cost_ceil  = (bundles + 1) * mp; // 남는 날 버리는 케이스

    if (rem == 0) return bundles * mp;
    return (cost_floor < cost_ceil) ? cost_floor : cost_ceil;
}
```

---

## 3) 네 테스트 케이스 결과는?

### 케이스 1

* 1일 3, 5일 14, n=6
* floor: 1묶음(14) + 1일(3)=17
* ceil: 2묶음(28)
  → 최소 = **17**

### 케이스 2

* 1일 2, 3일 5, n=11
* floor: 3묶음(15) + 2일(4)=19
* ceil: 4묶음(20)
  → 최소 = **19**

즉 출력은:

* 17
* 19

(이 두 케이스는 기존 코드도 우연히 맞음)

---

## 4) 추가로 안전성

현재 원본 코드의

```c
one_day_price * multi_day
```

는 int 오버플로우 가능성 있어서 위처럼 `long long`로 올리는 게 안전해.

---

원하면 “묶음권 종류가 여러 개(예: 7일권/30일권)”일 때 최저 비용 구하는 DP 버전도 만들어줄까?
