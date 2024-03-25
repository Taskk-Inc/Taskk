//
// Created by César B. on 3/25/2024.
//

#include "io.hpp"
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "data_types/data_types.hpp"

io::save_session_error io::save_session(std::string json)
{	try
	{	std::string file_name = make_session_file_name();

		data_types::file_guard file_guard = fopen(file_name.c_str(), "w");
		if(!file_guard.file)
			throw save_session_error::file_creation_denied;

		size_t bytes_written = fwrite(json.c_str(), 1, json.length(), file_guard.file);
		if(bytes_written != json.length())
			throw save_session_error::file_write_failure;

		return save_session_error::success;
	}
	catch(save_session_error error)
	{
		#ifndef NDEBUG
		switch(error)
		{	case save_session_error::file_creation_denied:
				assert(!"taskk : session file creation failed");
			case save_session_error::file_write_failure:
				assert(!"taskk : session file write operation failed");
		}
		#endif
		return error;
	}
}

std::string io::make_session_file_name()
{	// get current time data
	time_t current_time = time(NULL);
	struct tm * time_info = localtime(&current_time);

	// format time data into a buffer
	std::string result;
	result.resize(50);
	strftime((char *)result.c_str(), 50, "taskk-session-%m-%d-%Y-%I.%M.%S%p.taskk", time_info);
	result.shrink_to_fit();

	return result;
}
