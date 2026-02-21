이 코드는 `prices[]`에서 **한 번 사고(과거), 나중에 한 번 파는(미래)** 상황을 가정했을 때 얻을 수 있는 **최대 이익(= prices[j] - prices[i], j > i)** 을 구하는 전형적인 문제 풀이야.
(“Best Time to Buy and Sell Stock” 1회 거래 버전)

아래 흐름대로 설명할게.

---

## max / min 함수

```c
int max(int a, int b){
    return a < b ? b : a;
}
int min(int a, int b){
    return a < b ? a : b;
}
```

* `max(a,b)` : 둘 중 큰 값 반환
* `min(a,b)` : 둘 중 작은 값 반환
  (삼항 연산자 사용)

---

## solution 함수

```c
int solution(int prices[], int prices_len) {
```

* `prices`: 가격 배열
* `prices_len`: 길이

---

### 초기값 세팅

```c
    int INF = 1000000001;
    int tmp = INF;
    int answer = -INF;
```

* `INF`는 엄청 큰 값(“아직 최소값이 없다” 표시용)
* `tmp`는 **지금까지 본 가격 중 최솟값(= 가장 싼 매수 후보)** 을 저장할 변수

  * 처음엔 INF로 시작
* `answer`는 **최대 이익**을 저장

  * 처음엔 매우 작은 값으로 시작 (`-INF`)

---

### 배열을 한 번만 순회

```c
    for(int i = 0; i < prices_len; i++){
```

각 시점 i의 가격을 보면서:

#### (1) 현재 가격에 팔았다고 가정한 이익 갱신

```c
        if(tmp != INF)
            answer = max(answer, prices[i] - tmp);
```

* `tmp`는 “이전까지 등장한 가장 싼 가격”
* `prices[i] - tmp`는
  “이전에 tmp에 샀다가 지금 prices[i]에 판 이익”
* 그중 최대를 `answer`에 저장

사실 `tmp != INF` 체크는 i=0일 때만 의미가 있는데, i=0에서도 `prices[0] - INF` 계산을 피하려는 안전장치 느낌이야.

#### (2) 최소 매수 가격 갱신

```c
        tmp = min(tmp, prices[i]);
```

* 현재 가격이 더 싸면 `tmp`를 교체
* 즉, 앞으로의 판매를 대비해 “가장 싼 매수 후보”를 계속 유지

---

### 결과 반환

```c
    return answer;
}
```

---

## 예시로 따라가 보기

### 테스트 1: `{1,2,3}`

* i=0: tmp=min(INF,1)=1, answer 갱신은 사실상 의미 없음
* i=1: 이익 = 2-1 = 1 → answer=1, tmp=1
* i=2: 이익 = 3-1 = 2 → answer=2, tmp=1

✅ 결과: `2`

---

### 테스트 2: `{3,1}`

* i=0: tmp=3
* i=1: 이익 = 1-3 = -2 → answer=-2, tmp=1

✅ 결과: `-2`

---

## ⚠️ 중요한 포인트: “손해도 허용”하는 해석

이 코드의 반환값은 “최대 이익”이긴 한데, **반드시 거래를 1번 해야 한다**는 전제에 가깝게 동작해.
그래서 가격이 계속 떨어지면 `-2`처럼 **음수(손해)** 가 나와.

많은 문제(예: LeetCode 121)는 “거래를 안 해도 된다”가 기본이라, 그 경우 정답은 최소 0이야.
그 버전이면 이렇게 바꿔야 해:

```c
answer = 0;                  // 손해면 거래 안 함
answer = max(answer, prices[i] - tmp);
```

---

## 정리

* `tmp`: 지금까지의 최저가(매수 후보)
* 매 순간 `prices[i] - tmp`로 “지금 팔면 이익” 계산
* 그중 최대를 `answer`에 저장
* 시간복잡도 O(n), 공간 O(1)

원하면 “거래 안 해도 되는 버전(최소 0)” / “여러 번 거래(무제한)” / “수수료/쿨다운 포함” 버전까지 확장해서 설명해줄게.
