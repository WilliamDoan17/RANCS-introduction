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

enum DataType { FLOAT = 'f', INT = 'i', STRING = 's' };

sockaddr_in *get_server_addr(char hostname[], char port[]) {
  addrinfo hints = {.ai_family = AF_INET, .ai_socktype = SOCK_DGRAM};
  addrinfo *res;

  if (getaddrinfo(hostname, port, &hints, &res) != 0) {
    cout << "Couldn't get server address info\n";
    return NULL;
  }

  sockaddr_in *server_addr = (sockaddr_in *)malloc(sizeof(sockaddr_in));
  memcpy(server_addr, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);
  return server_addr;
}

size_t pack_data_int(char *dest, int32_t data) {
  *dest = 'i';

  dest[1] = (data >> 24) & 0xFF;
  dest[2] = (data >> 16) & 0xFF;
  dest[3] = (data >> 8) & 0xFF;
  dest[4] = data & 0xFF;

  return 5;
}

size_t pack_data_float(char *dest, float data) {
  *dest = 'f';

  uint32_t data_int;

  memcpy(&data_int, &data, sizeof(data_int));

  dest[1] = (data_int >> 24) & 0xFF;
  dest[2] = (data_int >> 16) & 0xFF;
  dest[3] = (data_int >> 8) & 0xFF;
  dest[4] = data_int & 0xFF;

  return 5;
}

size_t pack_data_string(char *dest, char data[]) {
  *dest = 's';
  size_t len = strlen(data) + 1;
  memcpy(dest + 1, data, len);
  return 1 + len;
}

int main() {
  int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_socket == 0) {
    cout << "Couldn't initiate client socket\n";
    return EXIT_FAILURE;
  }

  char hostname[256], port[256];
  cout << "Enter server hostname: ";
  cin >> hostname;
  cout << "Enter server port: ";
  cin >> port;

  sockaddr_in *server_addr = get_server_addr(hostname, port);
  if (!server_addr) {
    cout << "Couldn't get server address\n";
    return EXIT_FAILURE;
  }

  while (true) {

    char data_buf[1024];
    DataType data_type;
    char type;

    cout
        << "Specify data type to send (f for float, i for int, s for string): ";
    cin >> type;
    cin.ignore();

    data_type = (DataType)type;

    cout << "Enter data: ";
    int data_int;
    float data_float;
    char data_string[sizeof(data_buf) - 1];
    size_t packed_size = 0;

    switch (data_type) {
    case INT:
      cin >> data_int;
      packed_size = pack_data_int(data_buf, data_int);
      break;
    case FLOAT:
      cin >> data_float;
      packed_size = pack_data_float(data_buf, data_float);
      break;
    case STRING:
      cin.getline(data_string, sizeof(data_string));
      packed_size = pack_data_string(data_buf, data_string);
      break;
    }

    int sent = sendto(client_socket, data_buf, packed_size, 0,
                      (sockaddr *)server_addr, sizeof(*server_addr));
    if (sent < 0) {
      cout << "Send error\n";
      continue;
    } else if (sent == 0) {
      cout << "Empty data\n";
      continue;
    }
  }

  free(server_addr);
  close(client_socket);
}
