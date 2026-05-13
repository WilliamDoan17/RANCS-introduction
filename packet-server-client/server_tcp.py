import socket 
import threading

IPv4 = socket.AF_INET
IPv6 = socket.AF_INET6
Local = socket.AF_UNIX

Backlog = 5

UDP_pr = socket.SOCK_DGRAM
TCP_pr = socket.SOCK_STREAM

# uses thread to handle many client at a time

def handle_client(conn, addr):
    with conn:
        while True:
            data = conn.recv(1024)
            if not data: 
                conn.sendall(b"package lost")
                return
            print(f"Received data packet with content {data.decode()} from address {addr[0]}:{addr[1]}\n")
            conn.sendall(b"received data");


def server():
    with socket.socket(IPv4, TCP_pr) as s:
        hostname = socket.gethostname()
        ip = socket.gethostbyname(hostname)
        port = 3000
        s.bind((ip, port))
        print(f"Server is running on {ip}:{port} with hostname = {hostname}")
        
        s.listen(Backlog)
        
        while True: 
            conn, addr = s.accept()
            # each connection opens a thread
            thread = threading.Thread(target=handle_client, args=(conn, addr), daemon=True)
            thread.start()



if __name__ == "__main__":
    server()
