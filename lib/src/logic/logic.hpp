//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <string>
#include <jansson_config.h>
#include <memory>
#include "data_types/data_types.hpp"

namespace logic
{	/// calls init() if not called already
	void ensure_initialization();
	/// initialize the session, bind shutdown() to atexit()
	void init();
	///  begin a recorded taskk operation
	void begin_operation(std::string label);
	// custom data attachment functions
	void attach_operation_string(std::string data);
	void attach_operation_integer(json_int_t data);
	void attach_operation_real(double data);
	void attach_operation_boolean(bool data);
	void attach_operation_data(std::shared_ptr<data_types::custom_operation_data> data);
	///  end a recorded taskk operation
	void end_operation(std::string label);
	/// exit callback, saves the profiling session into a file named correspondingly to the current time and date
	void shutdown();
}
