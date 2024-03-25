//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <string>

namespace io
{	enum class save_session_error
	{	success,
		file_creation_denied,
		file_write_failure
	};
	save_session_error save_session(std::string json);
	// ie. "taskk-session-03-25-2024-08.35.10PM.taskk"
	std::string make_session_file_name();
}
