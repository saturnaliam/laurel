#include "include/repl.hpp"
#include "include/network.hpp"

int main(void) {
  message_header_t h = { .magic_number = "LRL", .command_type = 'p', .version = 0, .body_length = 13,};
  message_t m = { h };
  std::cout << serialize_message(m);
}