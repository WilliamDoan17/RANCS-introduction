import socket
import struct 
from enum import Enum

class DataType(Enum):
    INT = ord('i')
    FLOAT = ord('f')
    STRING = ord('s')

def pack_data(data: bytes, data_type: DataType) -> bytes:
    return bytes([data_type.value]) + data

def from_int_to_le(data: int) -> bytes:
    return struct.pack('<i', data)

def from_float_to_le(data: float) -> bytes:
    return struct.pack('<f', data)

if __name__ == "__main__":
    server_hostname = input("Enter sever hostname: ")
    server_port = int(input("Enter server port: "))

    server_addr = (server_hostname, server_port)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        while 1:
            data_type = DataType(ord(input("Specify data type to send data ('i' for int, 'f' for float, 's' for string): ")))

            print("Enter data: ", end = "")
            data = bytes()

            match(data_type): 
                case DataType.INT:
                    data = from_int_to_le(int(input())) 
                case DataType.FLOAT:
                    data = from_float_to_le(float(input()))
                case DataType.STRING:
                    data = input().encode()

            unpacked = pack_data(data, data_type)

            s.sendto(unpacked, server_addr)




