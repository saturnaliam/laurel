#include "serialize.hpp"

std::string serialize_message(const message_t &message) {
  std::string serialized_message;

  // serializing header
  serialized_message += message.header.magic_number + '\t' + 
    message.header.command_type + '\t' +
    std::to_string(message.header.version) + '\t' +
    std::to_string(message.header.body_length);

  // serializing body
  if (message.body != "") serialized_message += message.body;

  return serialized_message;
}