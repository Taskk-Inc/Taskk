//
// Created by César B. on 3/25/2024.
//

#include "include/taskk.h"
#include "logic/logic.hpp"
#include <iostream>

__declspec(dllexport) void taskk_begin_operation(char * name)
{	std::cout << "Taskk : beginning operation '" << name << "\'\n";
	logic::ensure_initialization();
}

__declspec(dllexport) void taskk_end_operation(char * name)
{	std::cout << "Taskk : ending operation '" << name << "\'\n";
}

