//
// Created by César B. on 4/5/2024.
//

#pragma once

#include <iostream>

#define fail(...) do { std::cerr << __VA_ARGS__ << std::endl; exit(EXIT_FAILURE); } while(false)
