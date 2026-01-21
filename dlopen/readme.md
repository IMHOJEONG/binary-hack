# dlopen과 dlsym

- 공유 라이브러리를 사용하는 프로그램 작성 

    - 빌드 환경, 실행 환경 둘 다 동일한 라이브러리가 존재해야 함 

- 때로는 빌드 시점에는 존재하지 않는 라이브러리를 실행 시점에 링크하거나 로드하고 싶을 때가 있을 것 

    - dlopen, dlsym이 실현 가능 

`dlopen`

- 공유 라이브러리의 파일명을 인수로 받아 해당 라이브러리를 로드하는 함수 

- 로드에 성공하면, 해당 라이브러리의 심벌 테이블 핸들을 반환함 

`dlsym`

- dlopen으로 로드한 라이브러리의 핸들과 심벌명을 인수로 받아 해당 심벌의 주소를 반환하는 함수 

- dlopen, dlsym 두 함수를 조합하면 공유 라이브러리를 실행 시점에 로드하고 그 안에 정의된 함수에 대한 포인터를 얻을 수 있음 

- ex: 여러 라이브러리 구현을 유연하게 전환하고 싶을 때 유용 

    - dlopen (공유 라이브러리 내 함수 단위로 전환할 수 있어 더 유연)

- ex: 애플리케이션의 플러그인 기능을 제공할 때도 유용 

    - 애플리케이션 본체 = 플러그인이 제공해야 할 함수의 인터페이스를 정의 & 이에 따라 dlopen으로 플러그인을 로드해 실행하는 로직을 구현 

    - 사용자는 공유 라이브러리 형태의 플러그인을 활용해 이후에 기능 확장 가능 

- 또한, 프로그래밍 언어 인터프리터에서 FFI(Foreign Function Interface)를 실현

## dlopen으로 libhello.so를 동적으로 링크하는 과정 

- dlopen??? 주어진 오브젝트 파일의 심벌 테이블을 해석하고, mmap을 사용해 PROT_EXEC 플래그를 지정해 메모리에 매핑

    - 다른 오브젝트에 의존하는 경우, 해당 오브젝트도 함께 로드됨 

```c
// RTLD_LAZY - 함수 참조를 실행 시점까지 지연시키는 플래그
    // 이 플래그가 지정된 경우, 참조할 수 없는 함수가 있어도 그것이 실행되지 않는 한 에러가 발생하지 않음 
// RTLD_NOW 플래그를 지정하면, dlopen 내에서 모든 참조가 즉시 해결됨 

```

- dlopen의 반환값 = 로드된 공유 라이브러리의 핸들

    - 이 핸들과 주소를 얻고자 하는 심벌 이름을 dlsym에 전달하면, 해당 심벌의 주소를 얻을 수 있음 

```shell
gcc dlopen-sample.c -o dlopen-sample.out

./dlopen-sample.out
```


- libhello.so가 실행 중에 로드되는 것을 확인 - dlopen-sample.out은 그대로 두고, libhello.so만 변경하여 실행 

```shell
sed -i "s/from libhello/Binary Hacks\!/" ./libhello.c

gcc -fPIC libhello.c -o libhello.so -shared

./dlopen-sample.out
```



