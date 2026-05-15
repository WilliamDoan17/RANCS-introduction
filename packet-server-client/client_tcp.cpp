#include <arpa/inet.h>
#include <cstddef>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

struct sockaddr_in *get_server_addr(char *server_hostname, char *port) {
  struct addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_STREAM};
  struct addrinfo *res;

  if (getaddrinfo(server_hostname, port, &hints, &res) != 0) {
    cout << "Couldn't get host device address from hostname\n";
    return NULL;
  }

  struct sockaddr_in *server_addr =
      (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in));
  memcpy(server_addr, res->ai_addr, sizeof(struct sockaddr_in));

  freeaddrinfo(res);

  return server_addr;
}

void client() {
  char server_hostname[] = "archlinux";
  char port[] = "3000";

  struct sockaddr_in *server_addr = get_server_addr(server_hostname, port);
  if (server_addr == NULL) {
    cout << "Cannot find server with address specified\n";
    return;
  }

  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0) {
    cout << "Couldn't create socket\n";
    free(server_addr);
    return;
  }
  int connected = connect(client_socket, (struct sockaddr *)server_addr,
                          sizeof(*server_addr));

  if (connected < 0) {
    cout << "Couldn't connect to server\n";
    free(server_addr);
    return;
  }

  char server_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &(server_addr->sin_addr), server_ip, sizeof(server_ip));

  cout << "Connected to server at " << server_ip << ":" << server_addr->sin_port
       << "\n";

  while (1) {
    cout << "Your message to the server: ";
    char message[1024];
    cin.getline(message, 1024);
    if (send(client_socket, message, strlen(message), 0) < 0) {
      cout << "Send failed\n";
      break;
    }
  }

  free(server_addr);
  close(client_socket);
}

int main() { client(); }
