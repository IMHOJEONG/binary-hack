이 코드는 `s`의 **모든 부분문자열(substring)** 중에서

1. **팰린드롬(회문)** 인 것만 모으고
2. **중복 제거**한 뒤
3. **사전순 정렬**해서
4. **k번째(1-indexed)** 를 리턴 (없으면 `"NULL"`)

을 하는 로직이야.

다만 지금 구현은 **메모리 누수 + 반환값 위험 + 시간폭발**이 꽤 심해. 핵심 문제부터 짚고, “최소 수정으로 안전하게” 고쳐줄게.

---

## 1) 현재 코드의 치명 포인트

### ✅ (1) `substr()`로 만든 문자열을 거의 다 `free` 안 함 → 누수 폭발

`sub_s`는 매 반복마다 malloc인데,

* 팰린드롬이 아니면 버려지는데 free 안 함
* 팰린드롬인데 중복이면 버려지는데 free 안 함

즉 대부분이 누수.

### ✅ (2) `func_c`가 `"NULL"` 리터럴을 반환

이건 “문자열 포인터”로는 괜찮지만, 호출자가 `free()`하면 터짐.
(리터럴은 free하면 안 됨)

### ✅ (3) 중복 체크 `func_a`가 O(M)이고, substring 전체가 O(n²)개라서

전체가 대충:

* substring 생성: O(n²)
* 각 substring palindrome 검사: O(len) → 총 O(n³)
* 중복 체크까지 포함하면 더 커짐 (최악 O(n⁴) 느낌)

n 조금만 커져도 매우 느려짐.

### ✅ (4) `palindromes[5050]` 고정 크기

입력 길이가 커지면 팰린드롬 종류가 5050개 넘을 수도 있어 (특히 서로 다른 문자가 많을 때 unique substring이 많이 나옴). 그러면 **배열 범위 초과**.

---

## 2) “일단 안전하게” 만들기 (메모리 누수 해결 + 반환 규칙 명확)

### 핵심 정책

* `sub_s`가 **배열에 저장되지 않는다면 즉시 free**
* `k`번째가 없을 때는 `"NULL"` 같은 리터럴 대신 `NULL` 포인터 반환 추천

  * 문제 요구가 문자열 `"NULL"`이면, 그 문자열을 **malloc해서** 반환하거나,
  * 문서로 “free 하면 안 되는 상수 문자열”이라고 명확히 해야 함

여기서는 기존 요구를 유지하되, 실수 방지를 위해 **`NULL` 포인터 반환**을 추천 버전으로 줄게.

---

## ✅ 최소 수정 버전 (누수 제거 + k없으면 NULL)

```c
char* func_c(char* palindromes[], int palindromes_cnt, int k) {
    qsort(palindromes, palindromes_cnt, sizeof(char*), compare);
    if (palindromes_cnt < k) return NULL;
    return palindromes[k - 1];
}

char* solution(char* s, int k) {    
    char* palindromes[5050];
    int palindromes_cnt = 0;
    int length = strlen(s);

    for (int start_idx = 0; start_idx < length; start_idx++) {
        for (int cnt = 1; cnt <= length - start_idx; cnt++) {
            char* sub_s = substr(s, start_idx, cnt);

            if (func_b(sub_s)) {
                if (!func_a(palindromes, palindromes_cnt, sub_s)) {
                    if (palindromes_cnt < 5050) {
                        palindromes[palindromes_cnt++] = sub_s; // 소유권 저장
                        continue; // 저장했으니 free 하면 안 됨
                    }
                    // 용량 초과면 저장 못하니 버림
                }
            }

            // 저장 안 했으면 반드시 free
            free(sub_s);
        }
    }

    char* answer = func_c(palindromes, palindromes_cnt, k);

    // ⚠️ answer를 반환하면, palindromes에 들어있는 나머지 문자열들은 누가 free?
    // - “k번째만 필요”라면, 반환하기 전에 나머지는 free하고 answer만 남겨야 함.
    // - 그런데 answer도 palindromes 중 하나라서 free하면 안 됨.
    // 아래는 그 처리:

    for (int i = 0; i < palindromes_cnt; i++) {
        if (palindromes[i] != answer) free(palindromes[i]);
    }

    return answer; // 호출자가 free 해야 함 (answer != NULL일 때)
}
```

### 이 버전의 규칙

* 반환값이 `NULL`이면 없음
* 반환값이 non-NULL이면 **호출자가 free 해야 함**
* 내부에서 다른 문자열들은 다 정리함 (누수 크게 줄임)

---

## 3) `"NULL"` 문자열을 꼭 반환해야 한다면?

그럼 `NULL` 대신 **동적 할당된 "NULL"**을 반환하면 안전해 (호출자가 free 가능)

```c
if (palindromes_cnt < k) {
    char* ret = (char*)malloc(5);
    strcpy(ret, "NULL");
    return ret;
}
```

---

## 4) 성능을 제대로 개선하려면

지금 구조 자체가 너무 비싸서, 보통은:

* 팰린드롬 판정: center expansion으로 O(n²)로 모두 찾고
* 중복 제거: 해시(set) 사용
* k번째 사전순: 트라이/정렬 + unique

같은 방식으로 가.

원하면 “입력 길이 최대가 얼마인지” 기준으로:

* 그냥 통과용(간단)
* 빡센 제약용(해시/롤링해시/KMP/Palindromic Tree)

중에 맞춰서 최적화 버전 짜줄게.

지금 문제의 `s` 최대 길이(제한) 알아? (예: 200, 2000, 100000)
