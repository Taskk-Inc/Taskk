//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <vector>
#include <chrono>
#include <map>
#include <string>

namespace data_types
{	/// a profiled operation
	struct operation
	{	/// this operation's name
		std::string label;
		/// the duration, in microseconds, of this operation
		std::chrono::microseconds duration;
		/// unix time, relative to the session's start timestamp
		std::map<std::chrono::microseconds, operation> sub_operations;
	};

	/// a profiling session
	struct session
	{	/// unix time, session start & end timestamps
		std::chrono::microseconds start_timestamp, end_timestamp;
		/// @see operation::sub_operations
		std::map<std::chrono::microseconds, operation> operations;
	};

	/**
	 * @brief closes the given file on destruction
	 * @details used for cleanup in try/catch blocks when throwing exceptions with open files
	 */
	struct file_guard
	{	public:
			FILE * file;
			file_guard() = delete;
			file_guard(FILE * file) : file(file) {}
			~file_guard() { fclose(file); }
	};

	/**
	 * @brief data structure of globals::current_operation_data
	 * @see globals::current_operation_data
	 */
	struct current_operation_data
	{	std::chrono::microseconds start_timestamp;
		data_types::operation * operation;
	};
}
