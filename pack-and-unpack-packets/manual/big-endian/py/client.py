import socket
import struct 
from enum import Enum

class DataType(Enum):
    INT = ord('i')
    FLOAT = ord('f')
    STRING = ord('s')

def pack_data_int(data: int) -> bytes:
    data = data & 0xFFFFFFFF
    result = bytearray([ord('i')])
    for i in range(4):
        result.append(data >> (24 - 8 * i) & 0xFF) 
    return bytes(result);

def pack_data_float(data: float) -> bytes:
    return bytes([ord('f')]) + struct.pack('>f', data)

def pack_data_string(data: str) -> bytes:
    return bytes([ord('s')]) + bytes([ord(ch) for ch in data])

if __name__ == "__main__":
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        server_hostname = input("Enter server hostname: ")
        server_port = int(input("Enter server port: "))

        server_ip = socket.gethostbyname(server_hostname)

        server_addr = (server_ip, server_port)

        while (1):
            data_type = DataType(ord(input("Specify type of data ('i' for int, 'f' for float, 's' for string): ")))

            data_bytes = bytearray() 

            match(data_type):
                case DataType.INT:
                    data_int = int(input("Enter data: "))
                    data_bytes = pack_data_int(data_int)
                case DataType.FLOAT:
                    data_float = float(input("Enter data: "))
                    data_bytes = pack_data_float(data_float)
                case DataType.STRING:
                    data_string = input("Enter data: ")
                    data_bytes = pack_data_string(data_string)

            s.sendto(data_bytes, server_addr)





