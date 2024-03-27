//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <chrono>
#include <string>
#include <assert.h>
#include "data_types/data_types.hpp"

namespace utils
{	std::chrono::microseconds get_unix_time();
	/// puts the given message into stderr and aborts the program
	void log_and_abort(std::string);
	/// marks the given operation and its whole sub-operation tree as finished
	void finish_operation(data_types::timestamp_operation_pair &);
	/// obtains the latest ongoing operation with a given label's timestamp/operation pair, or throws an exception
	data_types::timestamp_operation_pair & find_ongoing_operation(std::string label);
	/// attempts to obtain the latest ongoing operation's timestamp/operation pair
	data_types::timestamp_operation_pair * find_latest_ongoing_operation();
}
