# Sanitizer example

This is a very simple CMake project that demonstrates the most basic use of the address sanitizer from clang.

## Prerequisites

* Ubuntu 22.04 (other distros might work, I haven't tested)
* a Clang compiler (tested on 14.0.0)
  ```
  sudo apt install clang
  ```

## Building
```
cd {repo_root}
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_BUILD_TYPE=RelWithDebInfo ../
```

## Running

Go to the build folder and run the executable

```
cd build
./main
```

This will produce the following output:

```
lvk88@dell:~/dev/sanitizer_example/build$ ./main 
=================================================================
==11947==ERROR: AddressSanitizer: stack-use-after-scope on address 0x7fff6317ba40 at pc 0x55e608218dfa bp
 0x7fff6317ba00 sp 0x7fff6317b9f8
READ of size 4 at 0x7fff6317ba40 thread T0
    #0 0x55e608218df9 in create_dangling()::$_0::operator()() const /home/lvk88/dev/sanitizer_example/ma
in.cpp:11:57
    #1 0x55e608218df9 in int std::__invoke_impl<int, create_dangling()::$_0&>(std::__invoke_other, create
_dangling()::$_0&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/invoke.h:61:14
    #2 0x55e608218df9 in std::enable_if<__and_<std::__not_<std::is_void<int> >, std::is_convertible<std::
__invoke_result<create_dangling()::$_0&>::type, int> >::value, int>::type std::__invoke_r<int, create_dan
gling()::$_0&>(create_dangling()::$_0&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/1
1/bits/invoke.h:142:14
    #3 0x55e608218df9 in std::_Function_handler<int (), create_dangling()::$_0>::_M_invoke(std::_Any_data
 const&) /usr/bin/../lib/gcc/x86_64-linux-gnu/11/../../../../include/c++/11/bits/std_function.h:290:9
    #4 0x55e608218934 in std::function<int ()>::operator()() const /usr/bin/../lib/gcc/x86_64-linux-gnu/1
1/../../../../include/c++/11/bits/std_function.h:590:9
    #5 0x55e608218934 in main /home/lvk88/dev/sanitizer_example/main.cpp:27:25
    #6 0x7f4d24a29d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #7 0x7f4d24a29e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #8 0x55e6081583f4 in _start (/home/lvk88/dev/sanitizer_example/build/main+0x1f3f4) (BuildId: 40543cb
4bdceea14ef8415800bb338cd5640cee1)

Address 0x7fff6317ba40 is located in stack of thread T0 at offset 32 in frame
    #0 0x55e6082187af in main /home/lvk88/dev/sanitizer_example/main.cpp:25

  This frame has 2 object(s):
    [32, 36) 'a.i' (line 9) <== Memory access at offset 32 
    [48, 80) 'foo' (line 26)
HINT: this may be a false positive if your program uses som
r vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-use-after-scope /home/lasz
ate_dangling()::$_0::operator()() const
Shadow bytes around the buggy address:
  0x10006c6276f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10006c627700: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10006c627710: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10006c627720: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10006c627730: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x10006c627740: 00 00 00 00 f1 f1 f1 f1[f8]f2 00 00 00 00
  0x10006c627750: f3 f3 f3 f3 00 00 00 00 00 00 00 00 00 00
  0x10006c627760: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10006c627770: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10006c627780: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10006c627790: 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 applicatio
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==11947==ABORTING
```
