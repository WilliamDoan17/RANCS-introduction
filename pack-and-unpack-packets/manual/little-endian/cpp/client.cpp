#include <arpa/inet.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

enum DataType {
  INT = 'i',
  FLOAT = 'f',
  STRING = 's',
};

sockaddr_in *get_server_addr(char hostname[], char port[]) {
  addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_DGRAM};
  addrinfo *res;

  if (getaddrinfo(hostname, port, &hints, &res) != 0) {
    return NULL;
  }

  sockaddr_in *server_addr = (sockaddr_in *)malloc(sizeof(sockaddr_in));
  memcpy(server_addr, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);
  return server_addr;
}

void from_int_to_le(char dest[], int32_t data) {}

void from_float_to_le(char dest[], float data) {}

void pack_data(char dest[], char data[], DataType data_type, int *size) {}

int main() {
  char server_hostname[1024];
  cout << "Enter server hostname: ";
  cin >> server_hostname;

  char server_port[1024];
  cout << "Enter server port: ";
  cin >> server_port;

  sockaddr_in *server_addr = get_server_addr(server_hostname, server_port);
  if (!server_addr) {
    cout << "Couldn't get server address\n";
    return EXIT_FAILURE;
  }

  int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_socket == 0) {
    cout << "Couldn't initiate client socket\n";
    return EXIT_FAILURE;
  }

  while (true) {
    char type;
    cout << "Specify data type ('i' for int, 'f' for float, 's' for string): ";
    cin >> type;
    DataType data_type = (DataType)type;

    char data[1024];
    int size = 0;
    cout << "Enter data: ";
    cin.ignore();

    switch (data_type) {
    case INT: {
      int32_t data_int;
      cin >> data_int;
      from_int_to_le(data, data_int);
      size = 4;
      break;
    }
    case FLOAT: {
      float data_float;
      cin >> data_float;
      from_float_to_le(data, data_float);
      size = 4;
      break;
    }
    case STRING:
      cin.getline(data, sizeof(data));
      size = strlen(data) + 1;
      break;
    }

    char packed[1024];
    pack_data(packed, data, data_type, &size);

    sendto(client_socket, packed, size, 0, (sockaddr *)server_addr,
           sizeof(*server_addr));
  }

  free(server_addr);
  close(client_socket);
}
