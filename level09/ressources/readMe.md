# Level 09 - Character Transformation Reversal

This level uses a **simple character transformation algorithm** that can be reversed to extract the hidden flag from an encoded file.

---

## Step 1: Inspect the Binary

```bash
level09@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level09 level09  140 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level09 level09  220 Apr  3  2012 .bash_logout
-r-x------ 1 level09 level09 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag09  level09 7640 Mar  5  2016 level09
-r-x------ 1 level09 level09  675 Apr  3  2012 .profile
----r--r-- 1 flag09  level09   26 Mar  5  2016 token
level09@SnowCrash:~$ ./level09
You need to provied only one arg.

level09@SnowCrash:~$ ./level09 ./token
.0vrojt

level09@SnowCrash:~$ ./level09 abcde
acegi
scp -P 4242 level09@192.168.1.78:token token
➜  ressources git:(main) ✗ cc main.c
➜  ressources git:(main) ✗ ./a.out $(cat token)
f3iji1ju5yuevaus41q1afiuq
```
