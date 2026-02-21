좋은 코드네 👍
`구조체 + qsort + 포인터` 개념이 다 들어있어서 실무 C 감각 기르기 좋다.

아래에서 **위에서부터 한 줄씩** 설명해줄게.

---

## 🔹 헤더 파일

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
```

* `stdio.h` → printf 같은 입출력 함수
* `stdbool.h` → bool 타입 사용 가능
* `stdlib.h` → malloc, qsort 같은 함수
* `string.h` → strcpy 같은 문자열 함수

---

## 🔹 구조체 정의

```c
typedef struct Student{
    char name[20];
    int score;
}Student;
```

### 의미

* `Student`라는 자료형을 정의
* 안에는:

  * `name` : 최대 19글자 + '\0'
  * `score` : 정수 점수

### 왜 typedef?

원래는 이렇게 써야 함:

```c
struct Student s;
```

하지만 `typedef`를 써서:

```c
Student s;
```

로 간단하게 사용 가능하게 만든 것.

---

## 🔹 비교 함수 (qsort용)

```c
int compare(const void *a, const void * b){
```

* `qsort`에서 사용하는 비교 함수
* 반드시 이런 형식을 따라야 함
* `void*`는 어떤 타입이든 받을 수 있음

---

```c
Student first = *(Student *)a;
Student second = *(Student *)b;
```

### 동작 순서

1. `a`는 `void*`
2. `(Student*)a` → Student 포인터로 형변환
3. `*(Student*)a` → 실제 Student 값 복사

즉:

```c
Student first = *(Student *)a;
```

는
👉 `a가 가리키는 Student를 복사해서 first에 저장`

---

```c
if(first.score > second.score)
    return -1;
```

### qsort 규칙

| 반환값 | 의미    |
| --- | ----- |
| 음수  | a가 앞에 |
| 0   | 동일    |
| 양수  | b가 앞에 |

여기선 점수 **내림차순 정렬**

* 점수가 더 크면 앞에 와야 하므로 `-1`

---

```c
else if(first.score < second.score)
    return 1;
```

점수가 작으면 뒤로 → 1 반환

---

```c
else
    return 0;
```

점수 같으면 순서 유지

---

## 🔹 solution 함수

```c
char* solution(char* names[], int names_len, int scores[], int scores_len, int K)
```

### 의미

* `names[]` → 학생 이름 배열
* `scores[]` → 점수 배열
* `K` → K번째 학생 찾기
* 반환값 → K번째 학생의 이름 (char*)

---

## 🔹 길이 저장

```c
int len = names_len;
```

학생 수 저장

---

## 🔹 동적 메모리 할당

```c
Student* students = (Student*)malloc(sizeof(Student)*len);
```

### 의미

* Student 구조체 `len`개 만큼 메모리 확보
* students는 배열처럼 사용 가능

메모리 구조:

```
students → [Student][Student][Student]...
```

---

## 🔹 이름과 점수 복사

```c
for(int i = 0; i < len; i++){
    strcpy(students[i].name, names[i]);
    students[i].score = scores[i];
}
```

### 동작

* 이름 복사 (문자열이므로 strcpy 사용)
* 점수 저장

여기까지 하면 구조체 배열 완성됨:

```
이름  점수
철수  90
영희  70
민수  100
```

---

## 🔹 정렬

```c
qsort(students, len, sizeof(Student), compare);
```

### 의미

* students 배열을 정렬
* 개수: len
* 각 원소 크기: sizeof(Student)
* 비교 함수: compare

정렬 후:

```
민수 100
철수 90
영희 70
```

---

## 🔹 K번째 학생 반환

```c
return students[K-1].name;
```

* 배열은 0부터 시작
* K번째 = 인덱스 K-1
* 해당 학생의 name 반환

---

# ⚠️ 매우 중요한 문제

이 코드는 **위험한 코드**야.

왜?

```c
students는 malloc으로 만든 메모리
```

근데 함수 끝나면:

* students 메모리는 해제되지 않음 (memory leak)
* 반환하는 `students[K-1].name`은 malloc 영역 내부

→ 이건 당장은 동작하지만 **좋은 코드 아님**

---

# 🔥 안전한 버전 예시

```c
char* result = (char*)malloc(20);
strcpy(result, students[K-1].name);
free(students);
return result;
```

이렇게 해야 안전.

---

# 🧠 핵심 개념 정리

이 코드에서 배우는 것:

1. typedef 구조체 정의
2. void* → 형변환
3. qsort 비교 함수 규칙
4. 구조체 배열 동적 할당
5. 문자열 복사
6. 정렬 후 특정 순위 추출

---

원하면 내가

* 메모리 그림으로 더 자세히
* qsort 내부 동작 원리
* 왜 void*를 쓰는지
* compare 함수 더 깔끔하게 쓰는 법

까지 깊게 설명해줄까? 😄
