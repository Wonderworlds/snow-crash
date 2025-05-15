# Level 01 - Security Issue Discovery Process

This document outlines the steps taken to escalate privileges from `level01` by analyzing the system, discovering weakly protected data, and exploiting it using password cracking tools.

---

## Step 1: Initial Environment Reconnaissance

Inspect the home directory:

```bash
level01@SnowCrash:~$ ls -la
total 12
dr-x------ 1 level01 level01  100 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level01 level01  220 Apr  3  2012 .bash_logout
-r-x------ 1 level01 level01 3518 Aug 30  2015 .bashrc
-r-x------ 1 level01 level01  675 Apr  3  2012 .profile
```

---

## Step 2: File Discovery

Try to find files owned by this or target users:

```bash
level01@SnowCrash:~$ find / -path /proc -prune -o -user level01 -print 2> /dev/null
level01@SnowCrash:~$ find / -path /proc -prune -o -user flag01 -print 2> /dev/null
```

No interesting files were found.

---

## Step 3: Inspecting `/etc/passwd` for Password Hashes

```bash
level01@SnowCrash:~$ cat /etc/passwd
...
flag01:42hDRfypTqqnw:3001:3001::/home/flag/flag01:/bin/bash
...
```

We discover a password hash stored directly in `/etc/passwd`, an old and insecure configuration. The hash format is classic DES crypt.

---

## Step 4: Cracking the Password with John the Ripper

### 1. Copy the password hash locally

```bash
scp -P 4242 level01@127.0.0.1:/etc/passwd passwd.txt
```

### 2. Pull the Docker image (only needed the first time)

```bash
sudo docker pull obscuritylabs/johntheripper:latest
```

### 3. Run John the Ripper in Docker

```bash
sudo docker run -it --rm -v ./passwd.txt:/passwd.txt obscuritylabs/johntheripper:latest /passwd.txt
```

John successfully cracks the password:

```bash
abcdefg          (flag01)
```

---

## Step 5: Switching to `flag01` and Getting the Flag

```bash
level01@SnowCrash:~$ su flag01
Password: abcdefg
Don't forget to launch getflag !
```

```bash
flag01@SnowCrash:~$ getflag
Check flag. Here is your token : f2av5il02puano7naaf6adaaf
```

---

## ✅ Summary

- Found password hash in `/etc/passwd`: `42hDRfypTqqnw`
- Cracked it using John the Ripper: **`abcdefg`**
- Switched to `flag01` successfully
- Retrieved token with `getflag`

### Flag Token:

```text
f2av5il02puano7naaf6adaaf
```

Mission accomplished!
