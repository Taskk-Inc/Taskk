//
// Created by César B. on 3/25/2024.
//

#include "include/taskk.hpp"
#include "include/taskk.h"

__declspec(dllexport) void taskk::begin_operation(std::string name)
{	taskk_begin_operation((char *)name.c_str());
}

__declspec(dllexport) void taskk::end_operation(std::string name)
{	taskk_end_operation((char *)name.c_str());
}

