# Level 13 - Debugging and Exploiting with GDB

This level demonstrates how to use GDB to manipulate program execution and retrieve a token.

---

## Step 1: Inspect the Binary

```bash
ls
level13
```

Step 2: Inspect the binary in dog bolt

```cpp
int32_t main(int32_t argc, char** argv, char** envp)
{
    if (getuid() == 0x1092)
        return printf("your token is %s\n", ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I"));

    printf("UID %d started us but we we expe…", getuid(), 0x1092);
    exit(1);
    /* no return */
}
```

we want to fake the UID of 0x1092

Step 3: Disassemble the Main Function

```bash
gdb level13
(gdb) disas main
Dump of assembler code for function main:
   0x0804858c <+0>:	push   %ebp
   0x0804858d <+1>:	mov    %esp,%ebp
   0x0804858f <+3>:	and    \$0xfffffff0,%esp
   0x08048592 <+6>:	sub    \$0x10,%esp
   0x08048595 <+9>:	call   0x8048380 <getuid@plt>
   0x0804859a <+14>:	cmp    \$0x1092,%eax
   0x0804859f <+19>:	je     0x80485cb <main+63>
   0x080485a1 <+21>:	call   0x8048380 <getuid@plt>
   0x080485a6 <+26>:	mov    \$0x80486c8,%edx
   0x080485ab <+31>:	movl   \$0x1092,0x8(%esp)
   0x080485b3 <+39>:	mov    %eax,0x4(%esp)
   0x080485b7 <+43>:	mov    %edx,(%esp)
   0x080485ba <+46>:	call   0x8048360 <printf@plt>
   0x080485bf <+51>:	movl   \$0x1,(%esp)
   0x080485c6 <+58>:	call   0x80483a0 <exit@plt>
   0x080485cb <+63>:	movl   \$0x80486ef,(%esp)
   0x080485d2 <+70>:	call   0x8048474 <ft_des>
   0x080485d7 <+75>:	mov    \$0x8048709,%edx
   0x080485dc <+80>:	mov    %eax,0x4(%esp)
   0x080485e0 <+84>:	mov    %edx,(%esp)
   0x080485e3 <+87>:	call   0x8048360 <printf@plt>
   0x080485e8 <+92>:	leave
   0x080485e9 <+93>:	ret
End of assembler dump.
```

We identify the getUID that serves as auth

Step 4: Set a Breakpoint and Run

```bash
(gdb) break getuid
Breakpoint 1 at 0x8048380

(gdb) run
Starting program: /home/user/level13/level13
Breakpoint 1, 0xb7ee4cc0 in getuid () from /lib/i386-linux-gnu/libc.so.6
```

Step 5: Manipulate the Execution

```bash
(gdb) step
Single stepping until exit from function getuid,
which has no line number information.
0x0804859a in main ()

(gdb) print \$eax
\$1 = 2013

(gdb) set \$eax=4242

(gdb) step
Single stepping until exit from function main,
which has no line number information.
your token is 2A31L79asukciNyi8uppkEuSx
0xb7e454d3 in __libc_start_main () from /lib/i386-linux-gnu/libc.so.6
```

✅ Summary

    Debugging with GDB: We used GDB to set a breakpoint and manipulate the execution flow.
    The level13 binary was manipulated to bypass a check and retrieve the token.
    This demonstrated how debugging tools can be used to exploit program logic.
