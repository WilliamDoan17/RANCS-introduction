#include <arpa/inet.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

struct sockaddr_in *get_server_addr(char hostname[], char port[]) {
  struct addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_DGRAM};
  struct addrinfo *res;
  struct sockaddr_in *server_addr =
      (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
  if (getaddrinfo(hostname, port, &hints, &res) != 0) {
    freeaddrinfo(res);
    return NULL;
  }
  memcpy(server_addr, res->ai_addr, res->ai_addrlen);
  freeaddrinfo(res);
  return server_addr;
}

void server() {
  char hostname[1024];
  gethostname(hostname, sizeof(hostname));
  char port[] = "3000";

  struct sockaddr_in *server_addr = get_server_addr(hostname, port);
  if (!server_addr) {
    cout << "Couldn't retrieve address from the hostname provided\n";
    return;
  }

  int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_socket < 0) {
    cout << "Couldn't initiate server socket\n";
    free(server_addr);
    return;
  }

  int opt = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  if (bind(server_socket, (struct sockaddr *)server_addr,
           sizeof(*server_addr)) != 0) {
    cout << "Cannot bind server to hostname\n";
    free(server_addr);
    return;
  };

  char server_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &server_addr->sin_addr, server_ip, sizeof(server_ip));

  cout << "Server is running with hostname " << hostname << " at " << server_ip
       << ":" << port << "\n";

  while (true) {
    char data[1024];
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

    int received = recvfrom(server_socket, data, sizeof(data) - 1, 0,
                            (struct sockaddr *)&client_addr, &client_addrlen);
    if (received < 0) {
      cout << "Receive error\n";
      break;
    } else if (received == 0) {
      cout << "Empty data\n";
      continue;
    }

    data[received] = '\0';

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

    cout << "Received: " << data << " from " << client_ip << "\n";

    char server_msg[] = "Data received";
    sendto(server_socket, server_msg, sizeof(server_msg), 0,
           (struct sockaddr *)&client_addr, client_addrlen);
  }

  free(server_addr);
  close(server_socket);
}

int main() { server(); }
