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

void print_binary(char *data, size_t size) {
  for (size_t i = 0; i < size; i++) {
    for (int bit = 7; bit >= 0; bit--) {
      cout << ((data[i] >> bit) & 1);
    }
    cout << " ";
  }
  cout << "\n";
}

void unpack_data(char *dest, char *src, DataType *data_type, size_t size) {
  *data_type = (DataType)src[0];
  memcpy(dest, src + 1, size - 1);
}

int32_t from_binary_to_int(char bin[]) {
  int32_t result = 0;
  for (int byte = 0; byte <= 3; byte++) {
    result <<= 8;
    result |= (uint8_t)bin[byte];
  }
  return result;
}

float from_binary_to_float(char bin[]) {
  uint32_t raw = 0;
  for (int byte = 0; byte <= 3; byte++) {
    raw <<= 8;
    raw |= (uint8_t)bin[byte];
  }

  float result;
  memcpy(&result, &raw, sizeof(result));

  return result;
}

void print_decoded_data(char bin[], DataType data_type) {
  switch (data_type) {
  case INT:
    cout << from_binary_to_int(bin) << "\n";
    break;
  case FLOAT:
    cout << from_binary_to_float(bin) << "\n";
    break;
  case STRING:
    cout << bin << "\n";
  }
}

int main() {
  char hostname[256];
  gethostname(hostname, sizeof(hostname));

  char port[256];
  cout << "Assign a port for your server: ";

  cin >> port;

  sockaddr_in *server_addr = get_server_addr(hostname, port);

  if (!server_addr) {
    cout << "Couldn't get server address\n";
    return EXIT_FAILURE;
  }

  int server_socket = socket(AF_INET, SOCK_DGRAM, 0);

  if (server_socket == 0) {
    cout << "Cannot initiate server socket\n";
    free(server_addr);
    return EXIT_FAILURE;
  }

  if (bind(server_socket, (sockaddr *)server_addr, sizeof(*server_addr)) != 0) {
    cout << "Cannot bind server socket to address\n";
    return EXIT_FAILURE;
  }

  char server_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &server_addr->sin_addr, server_ip, sizeof(server_ip));

  cout << "Server is running with hostname " << hostname << " at " << server_ip
       << ":" << ntohs(server_addr->sin_port) << "\n";

  while (true) {
    char buf[1024];
    struct sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

    int received = recvfrom(server_socket, buf, sizeof(buf), 0,
                            (struct sockaddr *)&client_addr, &client_addrlen);
    if (received < 0) {
      cout << "Receive error\n";
      break;
    } else if (received == 0) {
      cout << "Empty data\n";
      continue;
    }

    cout << "Data received: ";
    print_binary(buf, received);

    char raw_unpacked[sizeof(buf)];
    DataType data_type;

    unpack_data(raw_unpacked, buf, &data_type, received);

    cout << "Raw unpacked binary: ";
    print_binary(raw_unpacked, received - 1);

    cout << "Decoded data: ";
    print_decoded_data(raw_unpacked, data_type);
  }

  close(server_socket);
  return EXIT_SUCCESS;
}
