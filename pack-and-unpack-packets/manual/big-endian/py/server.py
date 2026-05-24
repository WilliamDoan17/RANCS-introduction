import socket
from enum import Enum
import struct

class DataType(Enum):
    INT = ord('i')
    FLOAT = ord('f')
    STRING = ord('s')

def print_binary(data: bytes) -> None :
    for i in range(len(data)):
        for bit in range(7, -1, -1):
            print(f"{data[i] >> bit & 1}", end = "")
        
        print(" ", end = "")

    print()

def unpack_data(data: bytes) -> tuple[bytes, DataType]:
    data_type = DataType(data[0])
    raw_data = data[1:]

    return (raw_data, data_type)

def from_binary_to_int(bin: bytes) -> int:
    result = 0

    for i in range(4):
       result |= bin[i] << (24 - 8 * i) 

    if result & 0x80000000:
        result -= 0x100000000

    return result  

def from_binary_to_float(bin: bytes) -> float:
    return struct.unpack('>f', bin)[0]

def from_binary_to_string(bin: bytes) -> str:
    return ''.join([chr(byte) for byte in bin])

if __name__ == "__main__":
    hostname = socket.gethostname()
    ip = socket.gethostbyname(hostname)
    port = int(input("Assign port to server: "))
    
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s: 
        s.bind((ip, port))
        print(f"Server is running with hostname {hostname} at {ip}:{port}")

        while (1):
            data_buf, client_addr = s.recvfrom(1024)
            
            if not data_buf:
                print("Error on receive")
                continue

            print("Data received: ", end = "")
            print_binary(data_buf)
            
            raw_data, data_type = unpack_data(data_buf)

            print("Unpacked binary: ", end="")
            print_binary(raw_data)

            print("Decoded data: ", end = "")
            match(data_type):
                case DataType.INT:
                    print(from_binary_to_int(raw_data))
                case DataType.FLOAT:
                    print(from_binary_to_float(raw_data))
                case DataType.STRING:
                    print(from_binary_to_string(raw_data))







    
        
        


        

