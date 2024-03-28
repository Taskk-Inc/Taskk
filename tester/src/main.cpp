//
// Created by César B. on 3/25/2024.
//

#include "switch.h"
#include <taskk.hpp>
#include <iostream>
#include <unistd.h>

int cxx_main()
{	std::cout << "running the c++ tester" << std::endl;

	taskk_make_scope_operation("my_task");
	usleep(1000);

	auto my_other_task = taskk::operation_guard("my_other_task");
	usleep(1000);

	{	taskk::begin_operation("my_subtask");
		usleep(1000);
		taskk::end_operation("my_subtask");
	}

	usleep(1000);
	return 0;
}
