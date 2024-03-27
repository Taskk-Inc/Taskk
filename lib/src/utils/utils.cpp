//
// Created by César B. on 3/25/2024.
//

#include "utils.hpp"
#include <stdio.h>
#include <functional>
#include <cassert>
#include "globals/globals.hpp"
#include "macros/functions.hpp"

std::chrono::microseconds utils::get_unix_time()
{	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
}

void utils::log_and_abort(std::string msg)
{	fprintf(stderr, "Taskk : %s\n", msg.c_str());
	abort();
}

void utils::finish_operation(data_types::timestamp_operation_pair & pair)
{	auto & [timestamp, operation] = pair;
	operation.finished = true;
	operation.duration = utils::get_unix_time() - (timestamp + globals::session.start_timestamp);
	for(auto & sub_operation_pair : operation.sub_operations)
		finish_operation((data_types::timestamp_operation_pair &)sub_operation_pair);
}

data_types::timestamp_operation_pair & utils::find_ongoing_operation(std::string label)
{	// result declaration
	data_types::timestamp_operation_pair * found_pair = nullptr;

	// recursive lambda that does the actual search
	// *INDENT-OFF*
	std::function<void(data_types::timestamp_operation_pair&)> search =
		[&](data_types::timestamp_operation_pair& pair)
		{	auto & operation = pair.second;
			if(operation.finished)
				return;
			if(operation.label == label)
				found_pair = &pair;
			for(auto & sub_operation_pair : operation.sub_operations)
				search((data_types::timestamp_operation_pair&)sub_operation_pair);
		};
	// *INDENT-ON*

	// search
	search((data_types::timestamp_operation_pair &)*globals::session.operations.rbegin());

	// error checking
	if(!found_pair)
		utils::log_and_abort(make_string("invalid operation label '" << label << "'"));

	return *found_pair;
}

data_types::timestamp_operation_pair * utils::find_latest_ongoing_operation()
{	if(!globals::session.operations.size())
		return nullptr;

	auto * latest_pair = &*globals::session.operations.rbegin();

	while(latest_pair->second.sub_operations.size())
	{	auto & latest_sub_operation_pair = *latest_pair->second.sub_operations.rbegin();
		if(latest_sub_operation_pair.second.finished)
			break;
		else
			latest_pair = &latest_sub_operation_pair;
	}

	return (data_types::timestamp_operation_pair *)latest_pair;
}
