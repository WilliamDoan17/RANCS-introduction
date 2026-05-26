#include <arpa/inet.h>
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

void pack_data(char *dest, char *data, int *size, DataType data_type) {
  *dest = (char)data_type;
  memcpy(dest + 1, data, *size);
  (*size)++;
}

void from_int_to_be(char *dest, int32_t data, int *size) {
  uint32_t be = htobe32(static_cast<uint32_t>(data));
  memcpy(dest, &be, sizeof(data));
  *size = sizeof(data);
}

void from_float_to_be(char *dest, float data, int *size) {
  uint32_t raw;
  memcpy(&raw, &data, sizeof(data));
  raw = htobe32(raw);
  memcpy(dest, &raw, sizeof(raw));
  *size = sizeof(data);
}

void from_string_to_be(char *dest, char *data, int *size) {
  strcpy(dest, data);
  *size = strlen(data) + 1;
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
    cout << "Couldn't initiate client socket\n";
    return EXIT_FAILURE;
  }

  while (true) {
    char data_type_char;
    cout << "Specify type of data to send ('i' for integer, 'f' for float, 's' "
            "for string): ";
    cin >> data_type_char;

    DataType data_type = (DataType)data_type_char;

    char data[1024];
    int send_size;

    cout << "Enter data: ";
    cin.ignore();

    switch (data_type) {
    case INT:
      int data_int;
      cin >> data_int;
      from_int_to_be(data, data_int, &send_size);
      break;
    case FLOAT:
      float data_float;
      cin >> data_float;
      from_float_to_be(data, data_float, &send_size);
      break;
    case STRING:
      char data_string[1024];
      cin.getline(data_string, sizeof(data_string));
      from_string_to_be(data, data_string, &send_size);
      break;
    }

    char packed[1024];
    pack_data(packed, data, &send_size, data_type);

    sendto(client_socket, packed, send_size, 0, (sockaddr *)server_addr,
           sizeof(*server_addr));
  }

  free(server_addr);
  close(client_socket);
}
