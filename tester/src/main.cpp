//
// Created by César B. on 3/25/2024.
//

#include <taskk.hpp>

int main()
{	taskk_make_scope_operation("my_task");
	auto my_other_task = taskk::operation_guard("my_other_task");
	{	taskk::begin_operation("my_subtask");
		taskk::end_operation("my_subtask");
	}
	return 0;
}
