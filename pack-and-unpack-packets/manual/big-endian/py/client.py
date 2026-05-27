import socket
import struct
from enum import Enum

class DataType(Enum):
    INT = ord('i')
    FLOAT = ord('f')
    STRING = ord('s')

def from_int_to_be(data: int) -> bytes:
    return bytes([data >> (24 - 8 * i) & 0xFF for i in range(4)])

def from_float_to_be(data: float) -> bytes:
    return struct.pack('>f', data)

def pack_data(data: bytes, data_type: DataType) -> bytes:
    return bytes([data_type.value]) + data

if __name__ == "__main__":
    server_hostname = input("Enter server hostname: ")
    server_port = int(input("Enter server port: "))
    server_addr = (server_hostname, server_port)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        while True:
            data_type = DataType(ord(input("Specify data type ('i' for int, 'f' for float, 's' for string): ")))
            data = bytes()

            print("Enter data: ", end="")
            match data_type:
                case DataType.INT:
                    data = from_int_to_be(int(input()))
                case DataType.FLOAT:
                    data = from_float_to_be(float(input()))
                case DataType.STRING:
                    data = input().encode()

            packed = pack_data(data, data_type)
            s.sendto(packed, server_addr)
