## LD_PRELOAD 

- LD_PRELOAD = malloc, free와 같은 표준 C 라이브러리 함수도 덮어쓸 수 있음 

- tcmalloc이나 jemalloc와 같은 비표준 메모리 할당자를 사용하고 싶을 때 활용됨 

## LD_DEBUG 

- ld-linux.so의 동작을 관찰 가능 

`LD_DEBUG=symbols` : 표준 에러 출력에서 심벌 해결 과정 확인 가능 

- symbol resolution = 외부 함수나 변수 이름(심벌)을 실제로 정의된 공유 라이브러리(.so 파일) 안의 메모리 주소에 연결하는 과정 

man ld-linux.so 

- 모든 출력은 LD_DEBUG=all

## LD_AUDIT 

- ld-linux.so의 감사용 인터페이스, ld-linux.so가 새롭게 심벌을 바인딩했을 때나 PLT(procedure linkage table) 엔트리 내의 함수가 호출되었을 때 사용자가 등록한 콜백을 호출 가능 

- 