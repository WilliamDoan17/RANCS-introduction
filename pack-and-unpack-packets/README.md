# pack-and-unpack-packets
Demonstrates packing and unpacking packets — converting ints, floats, and strings to raw bytes and back, using both little endian and big endian byte order.

## How it works
- A UDP client packs values into raw bytes and sends them to a server
- The server receives the data and displays:
  - the raw bits as received
  - the bytes after interpreting byte order
  - the unpacked values as int, float, and string

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
