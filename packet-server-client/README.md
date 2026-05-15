# packet-server-client

This folder is for the first task of onboarding RANCS.

## Goals

- Send both UDP and TCP/IP packets between a Python server and Python client
- Learn about UDP and TCP/IP protocols
- Learn about server/client architecture in Python
- Do the same in C++

## Files

### Python

| File | Description |
|------|-------------|
| `server_udp.py` | UDP server — binds to port 5000, receives packets and echoes an acknowledgment back to the client |
| `client_udp.py` | UDP client — prompts for a message, sends it to the server at port 5000, and prints the response |
| `server_tcp.py` | TCP server — binds to port 3000, spawns a new thread per connection to handle multiple clients concurrently |
| `client_tcp.py` | TCP client — connects to the TCP server at port 3000, sends messages, and prints responses |

### C++

| File | Description |
|------|-------------|
| `server_tcp.cpp` | TCP server — resolves own hostname, binds to port 3000, spawns a detached thread per client to handle multiple connections concurrently |
| `client_tcp.cpp` | TCP client — resolves server hostname `archlinux`, connects to port 3000, sends messages in a loop and prints server responses |
| `server_udp.cpp` | UDP server — resolves own hostname, binds to port 3000, receives datagrams and echoes an acknowledgment back to each sender |
| `client_udp.cpp` | UDP client — resolves server hostname `archlinux`, sends datagrams to port 3000 and prints server responses |

### Running

Start the server first, then the client.

**Python UDP**
```bash
python server_udp.py
python client_udp.py
```

**Python TCP**
```bash
python server_tcp.py
python client_tcp.py
```

**C++ UDP**
```bash
g++ server_udp.cpp -o server_udp
g++ client_udp.cpp -o client_udp
./server_udp
./client_udp
```

**C++ TCP**
```bash
g++ server_tcp.cpp -o server_tcp -lpthread
g++ client_tcp.cpp -o client_tcp
./server_tcp
./client_tcp
```

> Both C++ and Python client files default to connecting to hostname `archlinux`. Change `server_hostname` if running on a different machine.
