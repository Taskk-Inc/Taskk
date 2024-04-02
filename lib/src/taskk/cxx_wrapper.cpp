//
// Created by César B. on 3/25/2024.
//

#include "include/taskk.hpp"
#include "logic/logic.hpp"

__declspec(dllexport) void taskk::begin_operation(std::string name)
{	logic::begin_operation(name);
}

__declspec(dllexport) void taskk::attach_string(std::string label, std::string data)
{	logic::attach_operation_string(label, data);
}

__declspec(dllexport) void taskk::attach_integer(std::string label, int data)
{	logic::attach_operation_integer(label, data);
}

__declspec(dllexport) void taskk::attach_real(std::string label, double data)
{	logic::attach_operation_real(label, data);
}

__declspec(dllexport) void taskk::attach_boolean(std::string label, bool data)
{	logic::attach_operation_boolean(label, data);
}

__declspec(dllexport) void taskk::end_operation(std::string name)
{	logic::end_operation(name);
}
