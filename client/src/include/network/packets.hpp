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

struct message_header_t {
  std::string magic_number;
  char command_type;
  u8 version;
  u8 body_length;
};

struct message_t {
  message_header_t header;
  std::string_view body;
};