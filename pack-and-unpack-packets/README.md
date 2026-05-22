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
