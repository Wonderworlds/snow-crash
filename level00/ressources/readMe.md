# Security Issue Discovery Process

This document outlines the steps taken to discover a potential security issue on the SnowCrash system during a penetration testing or CTF-style challenge.

---

## Step 1: Initial Environment Reconnaissance

Start by examining the home directory of the current user (`level00`) for any useful files or clues:

```bash
level00@SnowCrash:~$ ls -la
total 12
dr-xr-x---+ 1 level00 level00  100 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-xr-x---+ 1 level00 level00  220 Apr  3  2012 .bash_logout
-r-xr-x---+ 1 level00 level00 3518 Aug 30  2015 .bashrc
-r-xr-x---+ 1 level00 level00  675 Apr  3  2012 .profile
```

No unusual files were found in the user's home directory.

---

## Step 2: File Discovery

Use `find` to locate files owned by either the current user or other target users (e.g., `flag00`).

### Files owned by `level00`:

```bash
level00@SnowCrash:~$ find / -path /proc -prune -o -user level00 -print 2> /dev/null
/dev/pts/0
```

Only the current pseudo-terminal device was found.

### Files owned by `flag00`:

```bash
level00@SnowCrash:~$ find / -path /proc -prune -o -user flag00 -print 2> /dev/null
/usr/sbin/john
/rofs/usr/sbin/john
```

We discovered a binary named `john` owned by `flag00`.

---

## Step 3: Investigating the Binary

Let's read the contents of the `john` binary to see if there's something hidden:

```bash
level00@SnowCrash:~$ cat /usr/sbin/john
cdiiddwpgswtgt
```

The output is not readable text. It may be encoded.

---

## Step 4: Decoding the Cipher Text

We suspect the output is encoded with a Caesar cipher. Using [dcode.fr Caesar Cipher tool](https://www.dcode.fr/caesar-cipher), we attempt decryption.

- **Cipher text**: `cdiiddwpgswtgt`
- **Decryption result**: `nottoohardhere`

This string appears to be a password or flag.

---

## Step 5: Switching User and Retrieving the Flag

We try logging in as `flag00` using the decrypted password:

```bash
level00@SnowCrash:~$ su flag00
Password: nottoohardhere
Don't forget to launch getflag !
```

Then, we run the `getflag` command to retrieve the token:

```bash
flag00@SnowCrash:~$ getflag
Check flag.Here is your token : x24ti5gi3x0ol2eh4esiuxias
```

---

## ✅ Summary

- Discovered an owned binary `/usr/sbin/john` from user `flag00`
- Decoded a Caesar cipher message inside the binary: `nottoohardhere`
- Used it to switch to user `flag00`
- Ran `getflag` and retrieved the token:  
  **`x24ti5gi3x0ol2eh4esiuxias`**

Success!
