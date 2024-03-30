//
// Created by César B. on 3/25/2024.
//

#include "logic.hpp"
#include <iostream>
#include <functional>
#include <cstdio>
#include "globals/globals.hpp"
#include "utils/utils.hpp"
#include "io/io.hpp"
#include "json/json.hpp"

void logic::ensure_initialization()
{	static bool initialized = false;
	if(!initialized)
	{	init();
		initialized = true;
	}
}

void logic::init()
{	globals::session.start_timestamp = utils::get_unix_time();
	atexit([] { shutdown(); });
}

void logic::begin_operation(std::string label)
{	// ensure the library in initialized
	logic::ensure_initialization();

	// obtain this operation's timestamp
	std::chrono::microseconds timestamp = utils::get_unix_time() - globals::session.start_timestamp;

	// log
	std::cout << "Taskk : beginning operation '" << label << "' with timestamp " << timestamp.count() << "ns" << std::endl;

	// create the operation
	data_types::operation operation;
	operation.label = label;

	// push the operation into the required list
	data_types::timestamp_operation_pair * latest_pair = utils::find_latest_ongoing_operation();
	if(latest_pair)
		latest_pair->second.sub_operations[timestamp] = operation;
	else
		globals::session.operations[timestamp] = operation;
}

void logic::end_operation(std::string label)
{	std::function print_tabs = [](int amount) { for(int i = 0; i < amount; ++i) fputs("    ", stdout); };

	// operation architecture log
	/*
	std::function<void(std::string, data_types::timestamp_operation_map, int)> log_list = [&](std::string label, data_types::timestamp_operation_map list, int depth)
	{	print_tabs(depth); puts(label.c_str());
		for(auto pair : list)
			log_list(pair.second.label, pair.second.sub_operations, depth + 1);
	};
	puts("-----------------------------------------------------");
	log_list("", globals::session.operations, 0);
	*/

	utils::finish_operation(utils::find_ongoing_operation(label));
}

void logic::shutdown()
{	globals::session.end_timestamp = utils::get_unix_time();
	io::save_session(json::dump(json::encode_session(globals::session)));
}
