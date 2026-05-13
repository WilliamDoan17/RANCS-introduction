import socket

IPv4 = socket.AF_INET

UDP_pr = socket.SOCK_DGRAM


hostname = socket.gethostname()
ip = socket.gethostbyname(hostname)
port = 5000
            

def server():
    with socket.socket(IPv4, UDP_pr) as s:
        s.bind((ip, port)) 
        print(f"Server is running on hostname = {hostname} with address {ip}:{port}")
        

        while True:
            data, cli_addr = s.recvfrom(1024)
            if not data:
                break
            print(f"Received package with content {data.decode()} from {cli_addr}")
            s.sendto(b"Data received", cli_addr)


        

if __name__ == "__main__":
    server()
