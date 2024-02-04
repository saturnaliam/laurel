#include "serialize.hpp"

#define MESSAGE_ERROR() message.header.error = true;

void validate_message(message_t &message);

std::string serialize_message(const message_t &message) {
  std::string serialized_message;

  // serializing header
  serialized_message += message.header.magic_number + '\t' + 
    message.header.command_type + '\t' +
    std::to_string(message.header.version) + '\t' +
    std::to_string(message.header.body_length);

  // serializing body
  if (message.body != "" && message.header.body_length != 0) serialized_message += '\t' + message.body;

  return serialized_message;
}

message_t deserialize_message(const std::string &serialized) {
  std::vector<std::string> tokens;
  std::stringstream s_serialized(serialized);
  std::string buffer;
  while (getline(s_serialized, buffer, '\t')) tokens.push_back(buffer);

  message_t message;

  for (size_t i = 0; i < tokens.size(); i++) {
    switch (i) {
      case 0:
        message.header.magic_number = tokens[i];
        break;
      case 1:
        message.header.command_type = (tokens[i].c_str())[0];
        break;
      case 2:
        message.header.version = atoi(tokens[i].c_str());
        break;
      case 3:
        message.header.body_length = atoi(tokens[i].c_str());
        break;
      case 4:
        message.body = tokens[i];
        break;
      default:
      // if we ever get a value thats not between 0 and 4 then we should kill the process to prevent ub
        panic("invalid token index in message!", true);
        break;
    }
  }

  validate_message(message);

  return message;
}

void validate_message(message_t &message) {
  // ensuring we have the correct magic number
  if (message.header.magic_number != "LRL") MESSAGE_ERROR();

  // ensuring we have the correct version
  if (message.header.version != VERSION) MESSAGE_ERROR();

  // ensuring the body size is the same
  if (message.header.body_length != message.body.size()) MESSAGE_ERROR();
}