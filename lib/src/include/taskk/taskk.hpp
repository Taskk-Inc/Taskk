//
// Created by César B. on 3/25/2024.
//

#pragma once

#include "taskk_api.hpp"
#include <string>

namespace taskk
{	TASKK_CXX_API void begin_operation(std::string name);
	TASKK_CXX_API void end_operation(std::string name);
}
