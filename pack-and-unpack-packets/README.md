# pack-and-unpack-packets
Demonstrates packing and unpacking packets — converting ints, floats, and strings to raw bytes and back, using both little endian and big endian byte order.

## How it works
- The client chooses a data type (int, float, or string), packs it into raw bytes with a type header, and sends it over UDP
- The server receives the packet, reads the type header to infer the data type, and prints:
  - the raw bits as received
  - the bytes after interpreting byte order and type
  - the decoded value (int, float, or string)

## Implementation
Two approaches are demonstrated side by side:
- **manual/** — packing and unpacking using raw bitwise operations (`&`, `|`, `>>`, `<<`) without any serialization library, to show the mechanics directly
- **with-library/** — same functionality using `struct` (Python) and standard types (C++), to show the practical approach

## Structure
## Program architecture

### Client
| Function | Signature |
|----------|-----------|
| `get_server_addr` (C++ only) | `sockaddr_in *get_server_addr(char hostname[], char port[])` |
| `pack_data` | prepends the type byte to the raw data bytes |
| `from_int_to_(endi)` | converts an int to raw bytes in the target byte order |
| `from_float_to_(endi)` | converts a float to raw bytes in the target byte order |

### Server
| Function | Signature |
|----------|-----------|
| `get_server_addr` (C++ only) | `sockaddr_in *get_server_addr(char hostname[], char port[])` |
| `print_binary` | `void print_binary(char data[], int size)` |
| `unpack_data` | `void unpack_data(char dest[], char data[], DataType *data_type, int *size)` |
| `from_(endi)_to_int` | converts raw bytes in the given byte order to an int |
| `from_(endi)_to_float` | converts raw bytes in the given byte order to a float |

Strings require no conversion — they are sent and received as raw bytes directly.

### Packet format
```
[ type byte (1 byte) ][ data bytes (4 bytes for int/float, N bytes for string) ]
```
Type byte: `'i'` for int, `'f'` for float, `'s'` for string.

## Structure
```
pack-and-unpack-packets/
├── manual/
│   ├── big-endian/
│   │   ├── py/
│   │   │   ├── client.py
│   │   │   └── server.py
│   │   └── cpp/
│   │       ├── client.cpp
│   │       └── server.cpp
│   └── little-endian/
│       ├── py/
│       │   ├── client.py
│       │   └── server.py
│       └── cpp/
│           ├── client.cpp
│           └── server.cpp
└── with-library/
    ├── big-endian/
    │   ├── py/
    │   │   ├── client.py
    │   │   └── server.py
    │   └── cpp/
    │       ├── client.cpp
    │       └── server.cpp
    └── little-endian/
        ├── py/
        │   ├── client.py
        │   └── server.py
        └── cpp/
            ├── client.cpp
            └── server.cpp
```
