import socket
from enum import Enum
import struct 

class DataType(Enum):
    INT = ord('i')
    FLOAT = ord('f')
    STRING = ord('s')

def pack_data_int(data: int) -> bytes: 
    return bytes([ord('i')]) + bytes([data >> (byte * 8) & 0xFF for byte in range(4)]) 

def pack_data_float(data: float) -> bytes:
    return bytes([ord('f')]) + struct.pack('<f', data)

def pack_data_string(data: str) -> bytes:
    return bytes([ord('s')]) + bytes([ord(char) for char in data])

if __name__ == "__main__":
    server_hostname = input("Enter server hostname: ")
    server_ip = socket.gethostbyname(server_hostname)
    server_port = int(input("Enter server port: "))
    server_addr = (server_ip, server_port)

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        while (1):
            data_type = DataType(ord(input("Specify type of data to send ('i' for int, 'f' for float, 's' for string): ")))
        
            data = input("Enter data: ")
            match(data_type):
                case DataType.INT:
                    s.sendto(pack_data_int(int(data)), server_addr)
                case DataType.FLOAT:
                    s.sendto(pack_data_float(float(data)), server_addr)
                case DataType.STRING:
                    s.sendto(pack_data_string(str(data)), server_addr)
                


