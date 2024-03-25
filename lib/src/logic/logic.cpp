//
// Created by César B. on 3/25/2024.
//

#include "logic.hpp"
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
#include <stdio.h>
void logic::init()
{	globals::session.start_timestamp = utils::get_unix_time();
	atexit([] { shutdown(); });
}

void logic::shutdown()
{	io::save_session("test data");
}
