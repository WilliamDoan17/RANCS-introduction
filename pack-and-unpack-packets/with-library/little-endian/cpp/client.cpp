#include <arpa/inet.h>
#include <cstdint>
#include <cstdlib>
#include <endian.h>
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

void pack_data(char *dest, char data[], DataType data_type, int *size) {
  dest[0] = (char)data_type;

  switch (data_type) {
  case INT:
    *size = 4;
    break;
  case FLOAT:
    *size = 4;
    break;
  case STRING:
    *size = strlen(data) + 1;
    break;
  }

  memcpy(dest + 1, data, *size);

  *size += 1;
}

void from_int_to_le(char *dest, int data) {
  uint32_t raw = htole32(static_cast<uint32_t>(data));
  memcpy(dest, &raw, sizeof(raw));
}

void from_float_to_le(char *dest, float data) {
  uint32_t raw;
  memcpy(&raw, &data, sizeof(raw));
  raw = htole32(raw);

  memcpy(dest, &raw, sizeof(raw));
}

int main() {
  char server_hostname[1024];
  cout << "Enter server hostname: ";
  cin.getline(server_hostname, sizeof(server_hostname));

  char server_port[1024];
  cout << "Enter server port: ";
  cin >> server_port;

  sockaddr_in *server_addr = get_server_addr(server_hostname, server_port);
  if (!server_addr) {
    cout << "Couldn't find server address\n";
    return EXIT_FAILURE;
  }

  int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_socket == 0) {
    cout << "Couldn't initiate client socke\n";
    return EXIT_FAILURE;
  }

  while (true) {
    char data_type_char;
    cout << "Specify data type to send ('i' for int, 'f' for float, 's' "
            "string): ";
    cin >> data_type_char;
    DataType data_type = (DataType)data_type_char;

    char data[1024];
    cin.ignore();
    cout << "Enter data: ";
    switch (data_type) {
    case INT: {
      int data_int;
      cin >> data_int;
      from_int_to_le(data, data_int);
      break;
    }
    case FLOAT: {
      float data_float;
      cin >> data_float;
      from_float_to_le(data, data_float);
      break;
    }
    case STRING:
      cin.getline(data, sizeof(data));
      break;
    }

    int send_size;
    char packed[1024];
    pack_data(packed, data, data_type, &send_size);

    sendto(client_socket, packed, send_size, 0, (sockaddr *)server_addr,
           sizeof(*server_addr));
  }

  free(server_addr);
  close(client_socket);
}
