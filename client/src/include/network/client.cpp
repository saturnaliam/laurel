#include "client.hpp"

int start_client(const int &port) {
  const int socket_descriptor = socket(PF_INET, SOCK_STREAM, 0);

  sockaddr_in address_in;
  address_in.sin_family = AF_INET;
  address_in.sin_port = htons((short) port);

  char address_string[NI_MAXHOST + NI_MAXSERV + 1];
  snprintf(address_string, sizeof(address_string), "127.0.0.1:%d", port);

  inet_pton(AF_INET, address_string, &address_in.sin_addr);

  if (connect(socket_descriptor, (struct sockaddr*) &address_in, sizeof(address_in))) {
    perror("connect error:");
    return -1;
  }


  return socket_descriptor;
}

void send_message(const std::string &message, const int &socket_descriptor) {
  const char *msg = message.c_str();
  send(socket_descriptor, msg, strlen(msg) + 1, 0);
}