# Level 02 - Network Capture File Analysis

This document details the steps to retrieve the password for `flag02` using a `.pcap` file found in the `level02` home directory.

---

## Step 1: Initial Directory Inspection

```bash
level02@SnowCrash:~$ ls -la
total 24
dr-x------ 1 level02 level02  120 Mar  5  2016 .
d--x--x--x 1 root    users    340 Aug 30  2015 ..
-r-x------ 1 level02 level02  220 Apr  3  2012 .bash_logout
-r-x------ 1 level02 level02 3518 Aug 30  2015 .bashrc
----r--r-- 1 flag02  level02 8302 Aug 30  2015 level02.pcap
-r-x------ 1 level02 level02  675 Apr  3  2012 .profile
```

The file `level02.pcap` is readable and belongs to `flag02`. It's a packet capture and likely contains credentials or other useful data.

---

## Step 2: Copy the `.pcap` File for Analysis

On your local machine, copy the `.pcap` file using SCP:

```bash
scp -P 4242 level02@127.0.0.1:level02.pcap level02.pcap
```

---

## Step 3: Analyze the File with Wireshark

Open `level02.pcap` in **Wireshark** and inspect the traffic.

- Filter using protocols like `tcp` or `http`, or follow TCP streams.
- Look for transmitted credentials in plaintext.

### ✅ Discovered String in Packet Data:

```
Password: ft_wandr...NDRel.L0L
```

The `.` characters are non-printable (e.g. delete or control characters), but when cleaned up, the correct password becomes:

```text
ft_waNDReL0L
```

---

## Step 4: Use the Password to Switch User and Get the Flag

```bash
level02@SnowCrash:~$ su flag02
Password: ft_waNDReL0L
Don't forget to launch getflag !
```

```bash
flag02@SnowCrash:~$ getflag
Check flag.Here is your token : kooda2puivaav1idi4f57q8iq
```

---

## ✅ Summary

- Discovered `.pcap` file: `level02.pcap`
- Analyzed with Wireshark → found credentials in captured traffic.
- Extracted password: **`ft_waNDReL0L`**
- Used password to access `flag02`
- Retrieved token using `getflag`

### Flag Token:

```text
kooda2puivaav1idi4f57q8iq
```

Mission accomplished!
