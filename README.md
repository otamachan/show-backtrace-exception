# show exception backtrace

## build

```bash
g++ -shared -fPIC -o hook.so hook.cpp
g++ -g -rdynamic test.cpp
```

## test

```bash
$ ./a.out 
hello
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 2) >= this->size() (which is 0)
Aborted (core dumped)
```

```bash
$ LD_PRELOAD=./hook.so ./a.out 
hello
./hook.so(__cxa_allocate_exception+0x78)[0x7fc247f2c2b1]
/lib/x86_64-linux-gnu/libstdc++.so.6(_ZSt24__throw_out_of_range_fmtPKcz+0x114)[0x7fc247ddd6f4]
./a.out(_ZNKSt6vectorIiSaIiEE14_M_range_checkEm+0x52)[0x55d144f90652]
./a.out(_ZNSt6vectorIiSaIiEE2atEm+0x27)[0x55d144f9050f]
./a.out(_Z4testv+0x61)[0x55d144f902aa]
./a.out(main+0xd)[0x55d144f90338]
/lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3)[0x7fc247b230b3]
./a.out(_start+0x2e)[0x55d144f9018e]
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 2) >= this->size() (which is 0)
Aborted (core dumped)
```