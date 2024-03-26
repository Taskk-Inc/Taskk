//
// Created by César B. on 3/26/2024.
//

#pragma once

#include <string>
#include "taskk/cxx/macros/taskk_api.hpp"

namespace taskk
{	struct operation_guard
	{	private:
		std::string name;
	public:
		operation_guard() = delete;
		TASKK_CXX_API operation_guard(std::string name);
		TASKK_CXX_API ~operation_guard();
	};
}
