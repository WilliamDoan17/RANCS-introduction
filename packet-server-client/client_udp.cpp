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

  if (getaddrinfo(hostname, port, &hints, &res) < 0) {
    freeaddrinfo(res);
    return NULL;
  }

  struct sockaddr_in *server_addr =
      (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
  memcpy(server_addr, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);
  return server_addr;
}

void client() {
  char server_hostname[] = "archlinux";
  char server_port[] = "3000";

  int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_socket < 0) {
    cout << "Couldn't create client socket\n";
    return;
  }

  struct sockaddr_in *server_address =
      get_server_addr(server_hostname, server_port);
  if (!server_address) {
    cout << "Couldn't resolve server hostname and port\n";
    return;
  }

  char server_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &server_address->sin_addr, server_ip, sizeof(server_ip));

  while (1) {
    char data[1024];
    cout << "Send a message to the server: ";
    cin.getline(data, sizeof(data));

    int sent =
        sendto(client_socket, data, sizeof(data), 0,
               (struct sockaddr *)server_address, sizeof(*server_address));

    if (sent < 0) {
      cout << "Send error\n";
      continue;
    } else if (sent == 0) {
      cout << "Empty data\n";
      continue;
    }

    char server_msg[1024];
    socklen_t server_addrlen = sizeof(*server_address);
    int received =
        recvfrom(client_socket, server_msg, sizeof(server_msg) - 1, 0,
                 (struct sockaddr *)server_address, &server_addrlen);
    server_msg[received] = '\0';
    cout << server_msg << "\n";
  }

  free(server_address);
  close(client_socket);
}

int main() { client(); }
