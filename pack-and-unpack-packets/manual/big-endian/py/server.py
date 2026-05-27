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
    return (data[1:], data_type)

def from_be_to_int(data: bytes) -> int:
    pass

def from_be_to_float(data: bytes) -> float:
    pass

if __name__ == "__main__":
    hostname = socket.gethostname()
    ip = socket.gethostbyname(hostname)
    port = int(input("Assign port to your server: "))

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind((ip, port))
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
                    print(from_be_to_int(unpacked))
                case DataType.FLOAT:
                    print(from_be_to_float(unpacked))
                case DataType.STRING:
                    print(unpacked.decode())
