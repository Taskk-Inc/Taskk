//
// Created by César B. on 3/25/2024.
//

#include "include/taskk.hpp"
#include "logic/logic.hpp"

__declspec(dllexport) void taskk::begin_operation(std::string name)
{	logic::begin_operation(name);
}

__declspec(dllexport) void taskk::end_operation(std::string name)
{	logic::end_operation(name);
}

