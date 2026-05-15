#include <arpa/inet.h>
#include <cstddef>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
using namespace std;

struct client_info {
  int client_socket;
  char client_ip[INET_ADDRSTRLEN];
};

void *handle_client(void *c_info) {
  struct client_info *c_inf = (struct client_info *)c_info;
  int client_socket = c_inf->client_socket;
  char client_ip[INET_ADDRSTRLEN];
  strcpy(client_ip, c_inf->client_ip);

  free(c_inf);

  char data[1024];

  while (1) {
    int received = recv(client_socket, data, 1024, 0);

    if (received < 0) {
      cout << "recv failed\n";
    } else if (received == 0) {
      cout << "client disconnected\n";
      return NULL;
    } else {
      data[received] = '\0';
      cout << "Received: " << data << " from " << client_ip << "\n";
    }
  }

  close(client_socket);
  return NULL;
}

void server() {
  char hostname[256];
  gethostname(hostname, sizeof(hostname));

  struct addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_STREAM};
  struct addrinfo *res;

  char port[] = "3000";

  if (getaddrinfo(hostname, port, &hints, &res) != 0) {
    cout << "Couldn't get host device address from hostname\n";
    return;
  };

  sockaddr_in server_addr;
  memcpy(&server_addr, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);

  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    cout << "Couldn't initiate a socket\n";
    return;
  }

  int opt = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) != 0) {
    cout << "Cannot bind server to hostname\n";
    return;
  };

  char server_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &server_addr.sin_addr, server_ip, sizeof(server_ip));

  cout << "Server is running on hostname " << hostname << " with address "
       << server_ip << ":" << port << "\n";

  if (listen(server_socket, 5) < 0) {
    cout << "listen failed\n";
    return;
  }

  while (true) {
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);

    int client_socket =
        accept(server_socket, (struct sockaddr *)&client_addr, &client_len);

    if (client_socket < 0) {
      cout << "accept failed\n";
      continue;
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));

    struct client_info *c_info = (client_info *)malloc(sizeof(client_info));

    c_info->client_socket = client_socket;
    strcpy(c_info->client_ip, client_ip);

    pthread_t thread;
    pthread_create(&thread, NULL, handle_client, c_info);
    pthread_detach(thread);
  }
  close(server_socket);
}

int main() { server(); }
