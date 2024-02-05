#include "repl.hpp"

void sanitize_input(std::string &input);

void run_repl() {
  while (1) {
    std::cout << ">> ";
    std::string user_input;
    getline(std::cin, user_input);
    user_input = "\t\t\tf\ta\tsdf \n";
    sanitize_input(user_input);
    std::cout << user_input;
  }
}

void sanitize_input(std::string &input) {
  std::string buffer;

  for (char c : input) {
    if (!iscntrl(c)) buffer += c;
  }

  input = buffer;
}