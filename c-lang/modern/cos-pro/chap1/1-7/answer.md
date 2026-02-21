이 코드는 **정렬된 두 배열(arrA, arrB)을 하나의 정렬된 배열로 합치는(merge)** 전형적인 로직이야. (merge sort의 merge 단계랑 동일)

아래에서 흐름대로 설명할게.

---

## solution 함수 동작

### 1) 인덱스/결과 배열 준비

```c
int arrA_idx = 0, arrB_idx = 0;
int* answer = (int*)malloc(sizeof(int)*(arrA_len + arrB_len));
int answer_idx = 0;
```

* `arrA_idx` : arrA에서 현재 읽을 위치
* `arrB_idx` : arrB에서 현재 읽을 위치
* `answer` : 합쳐진 결과를 담을 동적 배열(길이 = arrA_len + arrB_len)
* `answer_idx` : 결과 배열에 쓸 위치

---

### 2) 둘 다 남아있는 동안 작은 값부터 채우기

```c
while(arrA_idx < arrA_len && arrB_idx < arrB_len){
    if(arrA[arrA_idx] < arrB[arrB_idx]) {
        answer[answer_idx++] = arrA[arrA_idx++];
    }
    else {
        answer[answer_idx++] = arrB[arrB_idx++];
    }
}
```

* arrA와 arrB의 “현재 원소”를 비교해서 더 작은 값을 `answer`에 넣고,
* 넣은 쪽 배열의 인덱스를 1 증가.
* `answer_idx++`도 같이 증가해서 다음 칸에 쓰게 됨.

> 참고: 값이 같은 경우(`==`)는 `else`로 들어가서 arrB의 값을 먼저 넣음.
> 안정성(stable)을 따지면 보통 `<=` 쪽 선택을 정하는데, 이건 문제 요구사항에 따라 달라.

---

### 3) 한쪽이 끝나면 나머지 “통째로” 복사

```c
while(arrA_idx < arrA_len)
    answer[answer_idx++] = arrA[arrA_idx++];

while(arrB_idx < arrB_len)
    answer[answer_idx++] = arrB[arrB_idx++];
```

* 위 while이 끝났다는 건 arrA 또는 arrB 둘 중 하나는 끝났다는 뜻.
* 남아있는 배열의 나머지 값들은 이미 정렬되어 있으니 그냥 뒤에 이어 붙이면 됨.

---

### 4) 합쳐진 배열 주소 반환

```c
return answer;
```

* `answer`는 malloc으로 만든 메모리라서 함수 밖에서도 유지됨.
* 호출한 쪽에서 **free(ret)** 해줘야 메모리 누수가 없음.

---

## main 함수 출력 흐름

```c
int arrA[4] = {-2, 3, 5, 9};
int arrB[3] = {0, 1, 5};
int* ret = solution(arrA, arrA_len, arrB, arrB_len);
```

* 두 배열은 이미 오름차순 정렬되어 있음.
* 합치면 총 길이 7.

출력 부분:

```c
for(int i = 0; i < 7; i++){
    ...
    printf("%d", ret[i]);
}
```

* 0~6까지 출력

---

## 실제 결과를 손으로 따라가보면

arrA = `[-2, 3, 5, 9]`
arrB = `[0, 1, 5]`

비교/선택 순서:

1. -2 vs 0 → -2
2. 3 vs 0 → 0
3. 3 vs 1 → 1
4. 3 vs 5 → 3
5. 5 vs 5 → (같음, else) arrB의 5
6. arrB 끝 → arrA의 남은 5, 9

✅ 결과:

`[-2, 0, 1, 3, 5, 5, 9]`

그래서 프로그램 출력은 대략:

`solution 함수의 반환 값은 [-2, 0, 1, 3, 5, 5, 9] 입니다.`

---

## ⚠️ 꼭 고치면 좋은 점 (메모리 누수)

main 끝나기 전에 이거 추가:

```c
free(ret);
```

동적 할당했으면 해제해야 함.

---

원하면, 이 코드에서 **중괄호 들여쓰기 정리** + **동일값 처리 정책(안정 merge)** 까지 “실무 스타일”로 리팩토링한 버전도 같이 만들어줄게.
