//
// Created by César B. on 3/27/2024.
//

#pragma once

#include <sstream>

#define make_string(...) ((std::stringstream() << __VA_ARGS__).str())
