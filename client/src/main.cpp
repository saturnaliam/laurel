#include "include/repl.hpp"
#include "include/network.hpp"
#include <string.h>

void test_serialization();

int main(int argc, char **argv) {
  if (argc > 1) {
    if (!strcmp(argv[1], "test")) {
      test_serialization();
    }
  } else {
    run_repl();
  }
}

void test_serialization() {
  std::cout << "SERIALIZATION TESTS:\n";
  // a basic test to make sure we get expected data.
  message_header_t no_error_header = { .magic_number = "LRL", .command_type = 'p', .version = 0, .body_length = 5 };
  message_t no_error = { .header = no_error_header, .body = "12345" };
  std::string no_error_serialized = serialize_message(no_error);
  message_t no_error_deserialized = deserialize_message(no_error_serialized);
  
  std::cout << "\tTest 1... ";
  if (no_error_deserialized.header.error) {
    std::cout << "Failed!\n";
  } else {
    std::cout << "Passed!\n";
  }

  // ensures bad magic numbers are flagged
  message_header_t magic_number_error_header = { .magic_number = "LRR", .command_type = 'p', .version = 0, .body_length = 5 };
  message_t magic_number_error = { .header = magic_number_error_header, .body = "12345" };
  std::string magic_number_error_serialized = serialize_message(magic_number_error);
  message_t magic_number_error_deserialized = deserialize_message(magic_number_error_serialized);

  std::cout << "\tTest 2... ";
  if (!magic_number_error_deserialized.header.error) {
    std::cout << "Failed!\n";
  } else {
    std::cout << "Passed!\n";
  }

  // makes sure invalid versions are detected
  message_header_t version_error_header = { .magic_number = "LRL", .command_type = 'p', .version = 1, .body_length = 5 };
  message_t version_error = { .header = version_error_header, .body = "12345" };
  std::string version_error_serialized = serialize_message(version_error);
  message_t version_error_deserialized = deserialize_message(version_error_serialized);

  std::cout << "\tTest 3... ";
  if (!version_error_deserialized.header.error) {
    std::cout << "Failed!\n";
  } else {
    std::cout << "Passed!\n";
  }

  // makes sure body length is equal to the actuals bodys size
  message_header_t size_error_header = { .magic_number = "LRL", .command_type = 'p', .version = 0, .body_length = 7 };
  message_t size_error = { .header = size_error_header, .body = "12345" };
  std::string size_error_serialized = serialize_message(size_error);
  message_t size_error_deserialized = deserialize_message(size_error_serialized);

  std::cout << "\tTest 4... ";
  if (!size_error_deserialized.header.error) {
    std::cout << "Failed!\n";
  } else {
    std::cout << "Passed!\n";
  }
}