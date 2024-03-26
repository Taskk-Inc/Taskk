//
// Created by César B. on 3/26/2024.
//

#include "taskk.hpp"

__declspec(dllexport) taskk::operation_guard::operation_guard(std::string name)
	: name(name)
{	begin_operation(name);
}

__declspec(dllexport) taskk::operation_guard::~operation_guard()
{	end_operation(name);
}
