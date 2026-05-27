import struct
import socket
from enum import Enum

class DataType(Enum):
    INT = ord('i')
    FLOAT = ord('f')
    STRING = ord('s')

def print_binary(data: bytes) -> None:
    for i in range(len(data)):
        for bit in range(7, -1, -1):
            print(data[i] >> bit & 1, end="")
        print(end=" ")
    print()

def unpack_data(data: bytes) -> tuple[bytes, DataType]:
    data_type = DataType(data[0])
    unpacked = data[1:]

    return (unpacked, data_type)

def from_le_to_int(data: bytes) -> int:
    return struct.unpack('<i', data)[0]

def from_le_to_float(data: bytes) -> float:
    return struct.unpack('<f', data)[0]

if __name__ == "__main__":
    hostname = socket.gethostname()
    port = int(input("Assign port to your server: "))
    ip = socket.gethostbyname(hostname)

    server_addr = (ip, port)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind(server_addr)
        print(f"Server is running with hostname {hostname} at {ip}:{port}")

        while True:
            data = s.recv(1024)
            print("Received bytes: ", end="")
            print_binary(data)

            unpacked, data_type = unpack_data(data)
            print("Unpacked: ", end="")
            print_binary(unpacked)

            print("Decoded: ", end="")
            match data_type:
                case DataType.INT:
                    print(from_le_to_int(unpacked))
                case DataType.FLOAT:
                    print(from_le_to_float(unpacked))
                case DataType.STRING:
                    print(unpacked.decode())
