# Toralizer
**Toralizer** is a light-weight library forlinux tat intercepts outgoing TCP connections and rerouts them through a tor proxy server.
It uses `LD_PRELOAD` to hijack the `connect()` system call and replaces it with custom logic that communicates with the proxy.

It uses the SOCKS4 protocol to communicate and connect with the proxy.
## Compilation and Usage
### Linux
- Make sure you have `gcc` insalled.
``` bash
make
```
- Give the `toralize` bash script the permissions.
``` bash
chmod 744 toralize
```
- All done
``` bash
./toralize curl example.com
```
## Macos
Even though some tweakes were made to the code (like replacing LD\_PRELOAD with DYLD\_INSERT\_LIBRARIES), and turning off SIP, it didn't work on my m2 mac-mini.
  

