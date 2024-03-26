//
// Created by César B. on 3/25/2024.
//

#include "logic.hpp"
#include "globals/globals.hpp"
#include "utils/utils.hpp"
#include <iostream>

void logic::ensure_initialization()
{	static bool initialized = false;
	if(!initialized)
	{	init();
		initialized = true;
	}
}

#include "io/io.hpp"
#include "json/json.hpp"
#include <stdio.h>
void logic::init()
{	globals::session.start_timestamp = utils::get_unix_time();
	atexit([] { shutdown(); });
}

void logic::begin_operation(std::string name)
{	std::cout << "Taskk : beginning operation '" << name << "\'\n";
	logic::ensure_initialization();
	// globals::session.
}

void logic::end_operation(std::string name)
{	std::cout << "Taskk : ending operation '" << name << "\'\n";
}

void logic::shutdown()
{	globals::session.end_timestamp = utils::get_unix_time();
	io::save_session(json::encode_session(globals::session));
}
