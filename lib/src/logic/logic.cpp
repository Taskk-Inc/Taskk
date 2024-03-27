//
// Created by César B. on 3/25/2024.
//

#include "logic.hpp"
#include <iostream>
#include <functional>
#include "globals/globals.hpp"
#include "utils/utils.hpp"

void logic::ensure_initialization()
{	static bool initialized = false;
	if(!initialized)
	{	init();
		initialized = true;
	}
}

#include "io/io.hpp"
#include "json/json.hpp"
#include "macros/functions.hpp"
#include <stdio.h>
void logic::init()
{	globals::session.start_timestamp = utils::get_unix_time();
	atexit([] { shutdown(); });
}

void logic::begin_operation(std::string label)
{	std::cout << "Taskk : beginning operation '" << label << '\'' << std::endl;
	// ensure the library in initialized
	logic::ensure_initialization();

	// obtain this operation's timestamp
	std::chrono::microseconds timestamp = utils::get_unix_time() - globals::session.start_timestamp;

	// create the operation
	data_types::operation operation;
	operation.label = label;

	// push the operation into the required list
	data_types::timestamp_operation_pair * latest_pair = utils::find_latest_ongoing_operation();
	if(latest_pair)
	{	std::cout << "latest_operation '" << latest_pair->second.label << '\'' << std::endl;
		latest_pair->second.sub_operations[timestamp] = operation;
	}
	else
		globals::session.operations[timestamp] = operation;

}

void logic::end_operation(std::string label)
{	std::cout << "Taskk : ending operation '" << label << "\'\n";

	std::function print_tabs = [](int amount) { for(int i = 0; i < amount; ++i) fputs("    ", stdout); };

	std::function<void(std::string, data_types::timestamp_operation_map, int)> log_list = [&](std::string label, data_types::timestamp_operation_map list, int depth)
	{	print_tabs(depth); puts(label.c_str());
		for(auto pair : list)
			log_list(pair.second.label, pair.second.sub_operations, depth + 1);
	};

	puts("-----------------------------------------------------");
	log_list("", globals::session.operations, 0);

	utils::finish_operation(utils::find_ongoing_operation(label));
}

void logic::shutdown()
{	globals::session.end_timestamp = utils::get_unix_time();
	io::save_session(json::dump(json::encode_session(globals::session)));
}
