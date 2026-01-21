#include <dlfcn.h>
#include <stdio.h>

int main(void) {

    void *lib = dlopen("./libhello.so", RTLD_LAZY);
    if (lib == NULL) {
        printf("dlopen failed: %s\n", dlerror());
        return 1;
    }

    int (*hello)(void);

    // dlsym으로 hello 함수의 주소 얻기
    hello = dlsym(lib, "hello"); 

    if (hello == NULL) {
        printf("dlsym failed: %s\n", dlerror());
        return 1;
    }

    // libhello.so 안에 정의된 hello 함수를 호출함 
    hello();

    // libhello.so를 언로드
    int ret = dlclose(lib);
    if (ret != 0) {
        printf("dlclose failed: %s\n", dlerror());
        return 1;
    }

    return 0;
}

