//
// Created by César B. on 3/25/2024.
//

#include "include/taskk.h"
#include "logic/logic.hpp"

__declspec(dllexport) void taskk_begin_operation(char * name)
{	logic::begin_operation(name);
}

__declspec(dllexport) void taskk_attach_string(char * data)
{	logic::attach_operation_string(data);
}

__declspec(dllexport) void taskk_attach_integer(int data)
{	logic::attach_operation_integer(data);
}

__declspec(dllexport) void taskk_attach_real(double data)
{	logic::attach_operation_real(data);
}

__declspec(dllexport) void taskk_attach_boolean(bool data)
{	logic::attach_operation_boolean(data);
}

__declspec(dllexport) void taskk_end_operation(char * name)
{	logic::end_operation(name);
}
