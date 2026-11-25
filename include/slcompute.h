#pragma once

#include <vector>
#include <string>


#ifdef _WIN32
  #define SLCOMPUTE_EXPORT __declspec(dllexport)
#else
  #define SLCOMPUTE_EXPORT
#endif

SLCOMPUTE_EXPORT void slcompute();
SLCOMPUTE_EXPORT void slcompute_print_vector(const std::vector<std::string> &strings);
