//
// Created by César B. on 3/25/2024.
//

#pragma once

#include "taskk/cxx/include_all.hpp"
#include <string>

namespace taskk
{	TASKK_CXX_API void begin_operation(std::string name);
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
