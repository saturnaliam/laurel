#pragma once

#include "../utils.hpp"

enum class Codes {
OK = 200,
BAD_REQUEST = 400,
UNAUTHORIZED = 401,
PRECONDITION_FAILED = 412,
PAYLOAD_TOO_LARGE = 413,
NOT_IMPLEMENTED = 501,
};

enum class Command : char {
PLAY = 'p',
};

struct message_header_t {
  std::string magic_number;
  Command command_type;
  u8 version;
  u8 body_length;
  bool error;
};

struct message_t {
  message_header_t header;
  std::string body;
};