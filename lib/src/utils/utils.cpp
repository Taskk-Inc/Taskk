//
// Created by César B. on 3/25/2024.
//

#include "utils.hpp"
#include <cstdio>
#include <functional>
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
{
	// *INDENT-OFF*

	// result declaration
	data_types::timestamp_operation_pair * found_pair = nullptr;

	/**
	 * @brief
	 * recursive lambda that does the actual search and sets found_pair
	 * to the latest (and deepest) unfinished operation with the given name
	 * in the whole operation tree
	 */
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

	// search
	search((data_types::timestamp_operation_pair &)*globals::session.operations.rbegin());

	// error checking
	if(!found_pair)
		utils::log_and_abort(make_string("invalid operation label '" << label << "'"));

	return *found_pair;

	// *INDENT-ON*
}

data_types::timestamp_operation_pair * utils::find_latest_ongoing_operation()
{	// if there are no main operations, or the last operation has been finished, return nullptr
	if(!globals::session.operations.size() || globals::session.operations.rbegin()->second.finished)
		return nullptr;

	// latest pair, last main operation by default
	auto * latest_pair = &*globals::session.operations.rbegin();

	// look for the latest sub-operation in latest_pair
	while(latest_pair->second.sub_operations.size())
	{	auto & latest_sub_operation_pair = *latest_pair->second.sub_operations.rbegin();
		if(!latest_sub_operation_pair.second.finished)
			latest_pair = &latest_sub_operation_pair;
		else
			// break out of the loop if all of latest_pair's sub-operations are finished
			break;
	}

	return (data_types::timestamp_operation_pair *)latest_pair;
}
