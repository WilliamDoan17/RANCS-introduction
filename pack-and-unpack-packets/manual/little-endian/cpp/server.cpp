#include <arpa/inet.h>
#include <cstddef>
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

void print_binary(char bin[], size_t size) {
  for (int i = 0; i < size; i++) {
    for (int bit = 7; bit >= 0; bit--) {
      cout << (bin[i] >> bit & 1);
    }
    cout << " ";
  }
  cout << "\n";
}

void unpack_data(char dest[], char src[], DataType *data_type, size_t *size) {
  *data_type = (DataType)src[0];
  *size -= 1;

  if (*data_type == STRING) {
    strcpy(dest, src + 1);
  } else {
    for (int i = 0; i < *size; i++) {
      dest[i] = src[*size - i];
    }
  }
}

int32_t from_binary_to_int(char data[]) {
  int32_t result = 0;

  for (int i = 0; i < 4; i++) {
    result |= (uint8_t)data[i] << (24 - 8 * i);
  }

  return result;
}

float from_binary_to_float(char data[]) {
  uint32_t raw = 0;

  for (int i = 0; i < 4; i++) {
    raw |= (uint32_t)((uint8_t)data[i] << (24 - 8 * i));
  }

  float result;
  memcpy(&result, &raw, sizeof(result));

  return result;
}

void from_binary_to_string(char dest[], char data[]) { strcpy(dest, data); }

int main() {
  char hostname[1024];
  gethostname(hostname, sizeof(hostname));

  char port[1024];
  cout << "Assign port to your server: ";
  cin >> port;

  int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (server_socket == 0) {
    cout << "Couldn't initiate server socket\n";
    return EXIT_FAILURE;
  }

  sockaddr_in *server_addr = get_server_addr(hostname, port);
  if (!server_addr) {
    cout << "Couldn't get server address information\n";
    close(server_socket);
    return EXIT_FAILURE;
  }

  if (bind(server_socket, (sockaddr *)server_addr, sizeof(*server_addr)) != 0) {
    cout << "Couldn't bind server socket to address\n";
    free(server_addr);
    close(server_socket);
    return EXIT_FAILURE;
  }

  char server_ip[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &server_addr->sin_addr, server_ip, sizeof(server_ip));

  cout << "Server is running with hostname " << hostname << " at " << server_ip
       << ":" << ntohs(server_addr->sin_port) << "\n";

  while (true) {
    char buf[1024];

    sockaddr_in client_addr;
    socklen_t client_addrlen = sizeof(client_addr);

    size_t received = recvfrom(server_socket, buf, sizeof(buf), 0,
                               (sockaddr *)&client_addr, &client_addrlen);

    if (received == 0) {
      cout << "Empty data\n";
      continue;
    } else if (received < 0) {
      cout << "Receive error\n";
      continue;
    }

    cout << "Binary received: ";

    print_binary(buf, received);

    DataType data_type;
    char unpacked[received];
    unpack_data(unpacked, buf, &data_type, &received);

    cout << "Unpacked binary: ";
    print_binary(unpacked, received);

    cout << "Decoded data: ";

    switch (data_type) {
    case INT: {
      int32_t data_int = from_binary_to_int(unpacked);
      cout << data_int << "\n";
      break;
    }
    case FLOAT: {
      float data_float = from_binary_to_float(unpacked);
      cout << data_float << "\n";
      break;
    }
    case STRING: {
      char data_string[received];
      from_binary_to_string(data_string, unpacked);
      cout << data_string << "\n";
      break;
    }
    }
  }

  free(server_addr);
  close(server_socket);
}
