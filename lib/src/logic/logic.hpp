//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <string>
#include "data_types/data_types.hpp"

namespace logic
{	/// calls init() if not called already
	void ensure_initialization();
	/// initialize the session, bind shutdown() to atexit()
	void init();
	///  begin a recorded taskk operation
	void begin_operation(std::string label);
	///  end a recorded taskk operation
	void end_operation(std::string label);
	/// exit callback, saves the profiling session into a file named correspondingly to the current time and date
	void shutdown();
}
