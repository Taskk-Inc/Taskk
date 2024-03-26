//
// Created by César B. on 3/25/2024.
//

#include "include/taskk.h"
#include "logic/logic.hpp"

__declspec(dllexport) void taskk_begin_operation(char * name)
{	logic::begin_operation(name);
}

__declspec(dllexport) void taskk_end_operation(char * name)
{	logic::end_operation(name);
}
