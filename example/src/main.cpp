//
// Created by César B. on 3/25/2024.
//

#include "switch.h"
#include <taskk.hpp>
#include <iostream>

void spin_wait(clock_t ms) { clock_t target = clock() + ms; while(clock() < target); }

int cxx_main()
{	std::cout << "running the c++ tester" << std::endl;

	taskk_make_scope_operation("my_task");
	spin_wait(20);

	auto my_other_task = taskk::operation_guard("my_other_task");
	spin_wait(20);

	{	taskk::begin_operation("my_subtask");
		spin_wait(20);
		taskk::attach_string("string_value", "lorem ipsum dolor sit amet");
		spin_wait(5);
		taskk::attach_real("real_value", 12345.6789);
		spin_wait(5);
		taskk::attach_boolean("boolean_true_value", true);
		spin_wait(5);
		taskk::attach_boolean("boolean_false_value", false);
		spin_wait(5);
		taskk::attach_auto("string_auto_value", "sample text");
		taskk::end_operation("my_subtask");
	}

	spin_wait(20);
	return 0;
}
