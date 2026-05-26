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

void print_binary(char data[], int size) {
  for (int i = 0; i < size; i++) {
    for (int bit = 7; bit >= 0; bit--) {
      cout << (data[i] >> bit & 1);
    }
    cout << " ";
  }
  cout << "\n";
}

void unpack_data(char *dest, char data[], DataType *data_type, int *size) {
  *data_type = (DataType)data[0];
  *size -= 1;

  memcpy(dest, data + 1, *size);
}

int32_t from_le_to_int(char data[]) {
  uint32_t raw;
  memcpy(&raw, data, sizeof(raw));

  return static_cast<int32_t>(le32toh(raw));
}

float from_le_to_float(char data[]) {
  uint32_t raw;
  memcpy(&raw, data, sizeof(raw));
  raw = le32toh(raw);

  float f;
  memcpy(&f, &raw, sizeof(f));

  return f;
}

int main() {
  char hostname[1024];
  gethostname(hostname, sizeof(hostname));

  char port[1024];
  cout << "Assign port to your server: ";
  cin >> port;

  sockaddr_in *server_addr = get_server_addr(hostname, port);
  if (!server_addr) {
    cout << "Couldn't find address\n";
    return EXIT_FAILURE;
  }

  int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_socket == 0) {
    cout << "Couldn't initiate server socket\n";
    return EXIT_FAILURE;
  }

  if (bind(server_socket, (sockaddr *)server_addr, sizeof(*server_addr)) != 0) {
    cout << "Couldn't bind server to address\n";
    return EXIT_FAILURE;
  }

  char server_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &server_addr->sin_addr, server_ip, sizeof(server_ip));

  cout << "Server is running with hostname " << hostname << " at " << server_ip
       << ":" << ntohs(server_addr->sin_port) << "\n";

  while (true) {
    char data[1024];
    sockaddr_in client_addr;
    socklen_t client_addrlen;

    int received = recvfrom(server_socket, data, sizeof(data), 0,
                            (sockaddr *)&client_addr, &client_addrlen);
    if (received == 0) {
      cout << "Empty data\n";
      continue;
    } else if (received < 0) {
      cout << "Receive error\n";
      continue;
    }

    cout << "Bytes received: ";
    print_binary(data, received);

    DataType data_type;
    char unpacked[received - 1];
    unpack_data(unpacked, data, &data_type, &received);

    cout << "Unpacked: ";
    print_binary(unpacked, received);

    cout << "Decoded: ";
    switch (data_type) {
    case INT:
      cout << from_le_to_int(unpacked);
      break;
    case FLOAT:
      cout << from_le_to_float(unpacked);
      break;
    case STRING:
      cout << unpacked;
    }

    cout << "\n";
  }

  free(server_addr);
  close(server_socket);
}
