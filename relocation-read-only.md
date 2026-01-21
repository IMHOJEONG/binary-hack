## Relocation Read-Only (RELRO)

- Global Offset Table(GOT) Overwrite 종류 공격에 효과적 

- 최근에는, 프로그램 시작 시 GOT의 내용을 확정하고, 그 후 쓰기를 불가능하게 만드는 RELRO가 널리 사용됨 

- PT_GNU_RELRO로 GOT에 해당하는 메모리 범위를 지정 후, GOT의 내용을 확정한 후, 그 범위를 읽기 전용으로 만드는 방식으로 RELRO가 구현됨 


