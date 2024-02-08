#include "repl.hpp"

void sanitize_input(std::string &input);
void run_input(const std::string &input, const int &socket_descriptor);

void run_repl(const int &port) {
  const int socket_descriptor = start_client(port);

  while (1) {
    std::cout << ">> ";
    std::string user_input;
    getline(std::cin, user_input);
    sanitize_input(user_input);

    if (user_input == "exit") break;
    run_input(user_input, socket_descriptor);
  }

  close(socket_descriptor);
}

void sanitize_input(std::string &input) {
  std::string buffer;

  for (char c : input) {
    if (!iscntrl(c)) buffer += c;
  }

  input = buffer;
}

void run_input(const std::string &input, const int &socket_descriptor) {
  if (input == "") return;

  std::stringstream s_input(input);
  std::string line;
  std::vector<std::string> arguments;
  while (getline(s_input, line, ' ')) arguments.push_back(line);

  message_header_t header = { .magic_number = "LRL", .version = VERSION,  };
  message_t message;

  if (arguments[0] == "help") {
    UNIMPLEMENTED;
  } else if (arguments[0] == "play") {
    if (arguments.size() != 2) {
      panic("incorrect usage!");
      return;
    }

    header.command_type = Command::PLAY;
    header.body_length = arguments[1].length();
    message.body = arguments[1];
  } else {
    panic("unknown command!");
    return;
  }

  message.header = header;

  std::string serialized = serialize_message(message);
  send_message(serialized, socket_descriptor);
  std::cout << serialized << "\n";
// TODO send the message
}