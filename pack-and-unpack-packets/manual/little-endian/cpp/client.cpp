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
};

void pack_data_int(char dest[], int32_t data, size_t *size) {
  *dest = 'i';

  dest[1] = data & 0xFF;
  dest[2] = data >> 8 & 0xFF;
  dest[3] = data >> 16 & 0xFF;
  dest[4] = data >> 24 & 0xFF;

  *size = 5;
}

void pack_data_float(char dest[], float data, size_t *size) {
  *dest = 'f';

  uint32_t raw;
  memcpy(&raw, &data, sizeof(raw));

  dest[1] = raw & 0xFF;
  dest[2] = raw >> 8 & 0xFF;
  dest[3] = raw >> 16 & 0xFF;
  dest[4] = raw >> 24 & 0xFF;

  *size = 5;
}

void pack_data_string(char dest[], char data[], size_t *size) {
  *dest = 's';

  strcpy(dest + 1, data);

  *size = strlen(dest) + 1;
}

int main() {
  char hostname[1024];
  cout << "Enter server hostname: ";
  cin.getline(hostname, sizeof(hostname));

  char port[1024];
  cout << "Enter server port: ";
  cin >> port;

  int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_socket == 0) {
    cout << "Couldn't initiate client socket\n";
    return EXIT_FAILURE;
  }

  sockaddr_in *server_addr = get_server_addr(hostname, port);
  if (!server_addr) {
    cout << "Couldn't get server address\n";
    close(client_socket);
    return EXIT_FAILURE;
  }

  while (true) {
    char type;
    DataType data_type;
    cout << "Specify data type to send to server ('i' for int, 'f' for float, "
            "'s' for string): ";
    cin >> type;
    data_type = (DataType)type;

    int32_t data_int;
    float data_float;
    char data_string[1024];
    cout << "Enter data: ";
    cin.ignore();

    switch (data_type) {
    case INT:
      cin >> data_int;
      break;
    case FLOAT:
      cin >> data_float;
      break;
    case STRING:
      cin.getline(data_string, sizeof(data_string));
      break;
    }

    char packed_data[1024];
    size_t packed_size;
    switch (data_type) {
    case INT:
      pack_data_int(packed_data, data_int, &packed_size);
      break;
    case FLOAT:
      pack_data_float(packed_data, data_float, &packed_size);
      break;
    case STRING:
      pack_data_string(packed_data, data_string, &packed_size);
      break;
    }

    int sent = sendto(client_socket, packed_data, packed_size, 0,
                      (sockaddr *)server_addr, sizeof(*server_addr));

    if (sent > 0) {
      cout << "Sent " << sent << " bytes to server\n";
    } else if (sent == 0) {
      cout << "Empty data sent\n";
    } else {
      cout << "Error sending data\n";
    }
  }

  free(server_addr);
  close(client_socket);
}
