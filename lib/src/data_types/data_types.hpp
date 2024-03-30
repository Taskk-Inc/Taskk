//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <vector>
#include <chrono>
#include <map>
#include <string>

namespace data_types
{	struct operation;
	/// a timestamp/operation pair
	typedef std::pair<std::chrono::microseconds, operation> timestamp_operation_pair;

	/// a timestamp/operation map
	typedef std::map<std::chrono::microseconds, operation> timestamp_operation_map;

	/// a profiled operation
	struct operation
	{	/// this operation's name
		std::string label;
		/// the duration, in microseconds, of this operation
		std::chrono::microseconds duration;
		/// unix time, relative to the session's start timestamp
		timestamp_operation_map sub_operations;
		/// not encoded into json, this value indicates whether this operation is finished
		bool finished = false;
	};

	/// a profiling session
	struct session
	{	/// unix time, session start & end timestamps
		std::chrono::microseconds start_timestamp, end_timestamp;
		/// @see operation::sub_operations
		timestamp_operation_map operations;
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
}
