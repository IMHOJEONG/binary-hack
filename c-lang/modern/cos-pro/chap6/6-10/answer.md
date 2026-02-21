이 코드는 **피자 목록에서**

1️⃣ 가장 큰 사이즈
2️⃣ 가장 싼 가격

을 각각 찾아서 `{size, price}` 형태로 반환하는 코드입니다.

---

# 📌 구조 설명

```c
typedef struct Pizza {
	int size;
	int price;
} Pizza;
```

→ 피자 한 개를 구조체로 표현
→ size와 price를 함께 관리

---

# 📌 비교 함수 설명

## 🔹 compare_a (사이즈 기준 정렬)

```c
if(first.size > second.size)
	return -1;
```

✔️ 내림차순 정렬
✔️ 가장 큰 size가 맨 앞에 오도록 정렬

즉,

```
40, 30, 20, 10
```

---

## 🔹 compare_b (가격 기준 정렬)

```c
if(first.price < second.price)
	return -1;
```

✔️ 오름차순 정렬
✔️ 가장 싼 가격이 맨 앞

즉,

```
1, 3, 4, 5
```

---

# 📌 solution 함수 동작

### 1️⃣ 구조체 배열 생성

```c
Pizza* pizzas = malloc(sizeof(Pizza) * len);
```

size / price 배열을 하나의 Pizza 배열로 합침

---

### 2️⃣ 사이즈 기준 정렬

```c
qsort(pizzas, len, sizeof(Pizza), compare_a);
```

정렬 후:

```
{40,4}
{30,5}
{20,1}
{10,3}
```

```c
answer[0] = pizzas[0].size;
```

→ 가장 큰 size = 40

---

### 3️⃣ 가격 기준 정렬

```c
qsort(pizzas, len, sizeof(Pizza), compare_b);
```

정렬 후:

```
{20,1}
{10,3}
{40,4}
{30,5}
```

```c
answer[1] = pizzas[0].price;
```

→ 가장 싼 가격 = 1

---

# 📌 최종 출력

```c
{40, 1}
```

---

# ⚠️ 중요한 논리 문제

이 코드에는 **논리적 버그**가 있습니다.

현재 반환값:

```
가장 큰 피자의 size
+
가장 싼 피자의 price
```

👉 하지만 이 두 값은 **같은 피자가 아닐 가능성**이 큽니다.

예제에서:

* 가장 큰 피자 = (40,4)
* 가장 싼 피자 = (20,1)

즉, `{40,1}` 은 실제 존재하지 않는 피자 조합입니다.

---

# 📌 시간복잡도

qsort 두 번 수행:

```
O(n log n) + O(n log n)
= O(n log n)
```

---

# 📌 메모리 문제

이 코드에는 작은 메모리 누수 있음:

```c
Pizza* pizzas = malloc(...)
```

→ free 안 함

---

# 📌 더 좋은 방법

이 문제는 정렬이 필요 없음.

한 번의 반복으로 해결 가능:

```c
int max_size = size[0];
int min_price = price[0];

for(int i = 1; i < len; i++){
    if(size[i] > max_size)
        max_size = size[i];
    if(price[i] < min_price)
        min_price = price[i];
}
```

👉 O(n)으로 해결 가능
👉 정렬보다 훨씬 효율적

---

# 📌 개선 버전 요약

| 방식       | 시간복잡도      | 추천 여부 |
| -------- | ---------- | ----- |
| qsort 2번 | O(n log n) | ❌     |
| 단순 반복    | O(n)       | ✅     |

---

# 📌 핵심 요약

이 코드는:

✔️ 구조체 정렬 사용 예제
✔️ qsort comparator 작성 연습용
✔️ 하지만 실제 문제 해결 방식으로는 비효율적

---

원하면:

* 🔥 같은 피자 중에서 "가성비 최고" 찾는 코드로 바꿔줄까?
* 🔥 compare 함수 더 안전하게 작성하는 법 설명해줄까?
* 🔥 qsort 내부 동작 원리까지 깊게 설명해줄까?

어디까지 갈까 😎
