import socket

IPv4 = socket.AF_INET

TCP_pr = socket.SOCK_STREAM

server_hostname = "archlinux"
server_ip = socket.gethostbyname(server_hostname)
server_port = 3000

client_hostname = socket.gethostname()
client_ip = socket.gethostbyname(client_hostname)

def client():
    with socket.socket(IPv4, TCP_pr) as s:
        print(f"Client is running with ip {client_ip}")
        s.connect((server_ip, server_port))
        while True: 
            data_send = input("Your message to the server: ")
            s.sendall(data_send.encode())
            data = s.recv(1024)
            if not data: 
                break
            print(data.decode())


if __name__ == "__main__":
    client()
