//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <vector>
#include <chrono>
#include <memory>
#include <map>
#include <string>
#include <jansson_config.h>

namespace data_types
{	// forward declarations
	struct operation;

	/// a timestamp/operation pair
	typedef std::pair<std::chrono::microseconds, operation> timestamp_operation_pair;

	/// a timestamp/operation map
	typedef std::map<std::chrono::microseconds, operation> timestamp_operation_map;

	/// a list of attached operation data shared pointers
	typedef std::vector<std::shared_ptr<struct attached_operation_data>> attached_data_list;

	/// a profiled operation
	struct operation
	{	/// this operation's name
		std::string label;
		/// the duration, in microseconds, of this operation
		std::chrono::microseconds duration;
		/// unix time, relative to the session's start timestamp
		timestamp_operation_map sub_operations;
		/// attached operation data
		attached_data_list attached_data;
		/// not encoded into json, this value indicates whether this operation is finished
		bool finished = false;
	};

	/// attached operation data
	struct attached_operation_data
	{	/// valid custom data types
		enum class data_type { string, integer, real, boolean, };
		/// the type op this data
		data_type type;
		/// the label shown in the client
		std::string label;
		// data member
		union
		{	std::string data_string;
			json_int_t data_integer;
			double data_real;
			bool data_boolean;
		};
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
