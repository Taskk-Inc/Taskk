//
// Created by César B. on 3/25/2024.
//

#include "include/taskk.h"
#include "logic/logic.hpp"

__declspec(dllexport) void taskk_begin_operation(char * name)
{	logic::begin_operation(name);
}

__declspec(dllexport) void taskk_attach_string(char * label, char * data)
{	logic::attach_operation_string(label, data);
}

__declspec(dllexport) void taskk_attach_integer(char * label, int data)
{	logic::attach_operation_integer(label, data);
}

__declspec(dllexport) void taskk_attach_real(char * label, double data)
{	logic::attach_operation_real(label, data);
}

__declspec(dllexport) void taskk_attach_boolean(char * label, bool data)
{	logic::attach_operation_boolean(label, data);
}

__declspec(dllexport) void taskk_end_operation(char * name)
{	logic::end_operation(name);
}
