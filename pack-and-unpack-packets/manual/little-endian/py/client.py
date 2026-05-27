import socket
from enum import Enum

class DataType(Enum):
    INT = ord('i')
    FLOAT = ord('f')
    STRING = ord('s')

def from_int_to_le(data: int) -> bytes:
    pass

def from_float_to_le(data: float) -> bytes:
    pass

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
                    data = from_int_to_le(int(input()))
                case DataType.FLOAT:
                    data = from_float_to_le(float(input()))
                case DataType.STRING:
                    data = input().encode()

            packed = pack_data(data, data_type)
            s.sendto(packed, server_addr)
