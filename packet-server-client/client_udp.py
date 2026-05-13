import socket

IPv4 = socket.AF_INET

UDP_pr = socket.SOCK_DGRAM

server_hostname = "archlinux"
server_ip = socket.gethostbyname(server_hostname)
server_port = 5000
server_addr = (server_ip, server_port)

client_hostname = socket.gethostname()
client_ip = socket.gethostbyname(client_hostname)

def client():
    with socket.socket(IPv4, UDP_pr) as s:
        print(f"Client is running on {client_ip}")
        while True: 
            message = input("Your message to the server: ")
            s.sendto(message.encode(), server_addr)
            
            data, sender_addr = s.recvfrom(1024)
            print(f"{data.decode()}")




if __name__ == "__main__":
    client()
