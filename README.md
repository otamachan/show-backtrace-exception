# show exception backtrace

## build

```bash
mkdr build
cd build
cmake ..
make
cd ..
g++ -g test.cpp
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
$ LD_PRELOAD=./build/libhook.so ./a.out
hello
terminate called after throwing an instance of 'std::out_of_range'
  what():  vector::_M_range_check: __n (which is 2) >= this->size() (which is 0)
backtrace [0] ./build/libhook.so(show_backtrace+0x2d) [0x7fba58078536]
backtrace [1] ./build/libhook.so(signal_handler+0x14) [0x7fba58078691]
backtrace [2] /lib/x86_64-linux-gnu/libc.so.6(killpg+0x40) [0x7fba57c830c0]
backtrace [3] /lib/x86_64-linux-gnu/libc.so.6(gsignal+0xcb) [0x7fba57c8303b]
backtrace [4] /lib/x86_64-linux-gnu/libc.so.6(abort+0x12b) [0x7fba57c62859]
backtrace [5] /lib/x86_64-linux-gnu/libstdc++.so.6(__cxa_throw_bad_array_new_length+0x560) [0x7fba57eeb911]
backtrace [6] /lib/x86_64-linux-gnu/libstdc++.so.6(std::rethrow_exception()+0x7c) [0x7fba57ef738c]
backtrace [7] /lib/x86_64-linux-gnu/libstdc++.so.6(std::terminate()+0x17) [0x7fba57ef73f7]
backtrace [8] /lib/x86_64-linux-gnu/libstdc++.so.6(__cxa_throw+0x49) [0x7fba57ef76a9]
backtrace [9] /lib/x86_64-linux-gnu/libstdc++.so.6(std::__throw_out_of_range()+0x6e) [0x7fba57eee3ab]
backtrace [10] ./a.out(std::vector<>::_M_range_check()+0x52) [0x56149b4db652]
backtrace [11] ./a.out(std::vector<>::at()+0x27) [0x56149b4db50f]
backtrace [12] ./a.out(test()+0x61) [0x56149b4db2aa]
backtrace [13] ./a.out(main+0xd) [0x56149b4db338]
backtrace [14] /lib/x86_64-linux-gnu/libc.so.6(__libc_start_main+0xf3) [0x7fba57c640b3]
backtrace [15] ./a.out(_start+0x2e) [0x56149b4db18e]
Aborted (core dumped)
```