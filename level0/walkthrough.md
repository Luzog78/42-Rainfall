# Level 0


<br>

### >> [Flag file](./flag) <<

<br>

### >> [Source file](./source.c) <<

<br>


## TL;DR:

```bash
./level0 423 <<< 'cat /home/user/level1/.pass > /tmp/.pass' && cat /tmp/.pass
```

<br>


## Explanation:


#### Step 1:

- What's in the home directory:
```bash
ls -la
```

> ```
> total 737
> dr-xr-x---+ 1 level0 level0     60 Mar  6  2016 .
> dr-x--x--x  1 root   root      340 Sep 23  2015 ..
> -rw-r--r--  1 level0 level0    220 Apr  3  2012 .bash_logout
> -rw-r--r--  1 level0 level0   3530 Sep 23  2015 .bashrc
> -rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0
> -rw-r--r--  1 level0 level0    675 Apr  3  2012 .profile
> ```


#### Step 2:

- Let's see what the `level0` binary does:
```bash
gdb -q ./level0
disassemble main
```

> ```asm
> Dump of assembler code for function main:
>    0x08048ec0 <+0>:     push   %ebp
>    0x08048ec1 <+1>:     mov    %esp,%ebp
>    0x08048ec3 <+3>:     and    $0xfffffff0,%esp
>    0x08048ec6 <+6>:     sub    $0x20,%esp
>    0x08048ec9 <+9>:     mov    0xc(%ebp),%eax
>    0x08048ecc <+12>:    add    $0x4,%eax
>    0x08048ecf <+15>:    mov    (%eax),%eax
>    0x08048ed1 <+17>:    mov    %eax,(%esp)
>    0x08048ed4 <+20>:    call   0x8049710 <atoi>      ; atoi(argv[1])
>    0x08048ed9 <+25>:    cmp    $0x1a7,%eax           ; compare with 423
>    0x08048ede <+30>:    jne    0x8048f58 <main+152>  ; if !=, goto <main+152>
> 
>    0x08048ee0 <+32>:    movl   $0x80c5348,(%esp)     ; (char *) 0x80c5348 == "/bin/sh"
>    0x08048ee7 <+39>:    call   0x8050bf0 <strdup>    ; strdup("/bin/sh")
>    0x08048eec <+44>:    mov    %eax,0x10(%esp)
>    0x08048ef0 <+48>:    movl   $0x0,0x14(%esp)
>    0x08048ef8 <+56>:    call   0x8054680 <getegid>   ; getegid()
>    0x08048efd <+61>:    mov    %eax,0x1c(%esp)
>    0x08048f01 <+65>:    call   0x8054670 <geteuid>   ; geteuid()
>    0x08048f06 <+70>:    mov    %eax,0x18(%esp)
>    0x08048f0a <+74>:    mov    0x1c(%esp),%eax
>    0x08048f0e <+78>:    mov    %eax,0x8(%esp)
>    0x08048f12 <+82>:    mov    0x1c(%esp),%eax
>    0x08048f16 <+86>:    mov    %eax,0x4(%esp)
>    0x08048f1a <+90>:    mov    0x1c(%esp),%eax
>    0x08048f1e <+94>:    mov    %eax,(%esp)
>    0x08048f21 <+97>:    call   0x8054700 <setresgid> ; setresgid(...)
>    0x08048f26 <+102>:   mov    0x18(%esp),%eax
>    0x08048f2a <+106>:   mov    %eax,0x8(%esp)
>    0x08048f2e <+110>:   mov    0x18(%esp),%eax
>    0x08048f32 <+114>:   mov    %eax,0x4(%esp)
>    0x08048f36 <+118>:   mov    0x18(%esp),%eax
>    0x08048f3a <+122>:   mov    %eax,(%esp)
>    0x08048f3d <+125>:   call   0x8054690 <setresuid> ; setresuid(...)
>    0x08048f42 <+130>:   lea    0x10(%esp),%eax
>    0x08048f46 <+134>:   mov    %eax,0x4(%esp)
>    0x08048f4a <+138>:   movl   $0x80c5348,(%esp)
>    0x08048f51 <+145>:   call   0x8054640 <execv>     ; execv("/bin/sh", ...)
>    0x08048f56 <+150>:   jmp    0x8048f80 <main+192>  ; goto <main+192> if execv fails
> 
>    0x08048f58 <+152>:   mov    0x80ee170,%eax
>    0x08048f5d <+157>:   mov    %eax,%edx
>    0x08048f5f <+159>:   mov    $0x80c5350,%eax       ; (char *) 0x80c5350 == "No !\n"
>    0x08048f64 <+164>:   mov    %edx,0xc(%esp)
>    0x08048f68 <+168>:   movl   $0x5,0x8(%esp)
>    0x08048f70 <+176>:   movl   $0x1,0x4(%esp)
>    0x08048f78 <+184>:   mov    %eax,(%esp)
>    0x08048f7b <+187>:   call   0x804a230 <fwrite>    ; fwrite("No !\n", 1, 5, stderr)
>
>    0x08048f80 <+192>:   mov    $0x0,%eax
>    0x08048f85 <+197>:   leave  
>    0x08048f86 <+198>:   ret                          ; return 0
> End of assembler dump.
> ```
> So basically, if we give the number `423` as an argument to the `level0` binary, it will execute `/bin/sh` with the effective user ID of `level1`. This means we can get a shell as `level1` and then retrieve the flag for that level.


#### Step 3:

- Let's try it:
```bash
./level0 423
```
> ```
> $ id
> uid=2030(level1) gid=2020(level0) groups=2030(level1),100(users),2020(level0)
> ```

- Now we can retrieve the flag for `level1`:
```bash
$ cat /home/user/level1/.pass
```


<br>

---

<< &nbsp; [[Back to main page]](/Readme.md) &nbsp; [[>>]](/level1/walkthrough.md)
