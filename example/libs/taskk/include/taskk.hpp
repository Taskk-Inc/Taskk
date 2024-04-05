//
// Created by César B. on 3/25/2024.
//

#pragma once

#include "taskk/cxx/include_all.hpp"

namespace taskk
{	TASKK_CXX_API void begin_operation(std::string name);
	TASKK_CXX_API void attach_string(std::string label, std::string data);
	TASKK_CXX_API void attach_integer(std::string label, int data);
	TASKK_CXX_API void attach_real(std::string label, double data);
	TASKK_CXX_API void attach_boolean(std::string label, bool data);
	template<typename _type> void attach_auto(std::string label, _type data);
	TASKK_CXX_API void end_operation(std::string name);
	/**
	 * @brief a guard struct for taskk operations
	 * @details
	 * automatically begins and ends a taskk operation on
	 * struct construction/destruction. \n
	 * use this struct to assign tasks to scopes.
	 */
	struct operation_guard;
}

#include "taskk/cxx/templates/attach_auto_overloads.hpp"
