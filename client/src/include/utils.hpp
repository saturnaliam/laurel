#pragma once

#include <cstdint>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#define VERSION 0

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

/**
 * @brief Panics, and if needed, kills the program.
 * @param message The message to be displayed.
 * @param kill If the program should be killed.
 */
static void panic(std::string_view message, bool kill = false) {
  std::cerr << message << "\n";
  if (kill) exit(1);
}

#define UNIMPLEMENTED panic("unimplemented!", true);