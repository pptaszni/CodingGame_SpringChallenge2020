#pragma once

#include <iostream>

#define ENABLE_DEBUG true

#define DEBUG(x) do { \
  if (ENABLE_DEBUG) { std::cerr << x << std::endl; } \
} while (0)
