#pragma once

#include "../utils.hpp"
#include "packets.hpp"
#include <sstream>

std::string serialize_message(const message_t &message);
message_t deserialize_message(const std::string &serialized);