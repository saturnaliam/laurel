#pragma once

#include "../utils.hpp"
#include <cstring>
#include <cstdio>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

/**
 * @brief Starts the client.
 * @param port The port the server is currently running on.
 * @return The socket descriptor.
 */
int start_client(const int &port);

void send_message(const std::string &message, const int &socket_descriptor);