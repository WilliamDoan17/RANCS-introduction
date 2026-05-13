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

### Running

Start the server first, then the client.

**UDP**
```bash
python server_udp.py
python client_udp.py
```

**TCP**
```bash
python server_tcp.py
python client_tcp.py
```

> Both client files default to connecting to hostname `archlinux`. Change `server_hostname` if running on a different machine.
