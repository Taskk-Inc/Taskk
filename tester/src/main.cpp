//
// Created by César B. on 3/25/2024.
//

#include <taskk/taskk.hpp>

int main()
{
	taskk::begin_operation("begin_task_name");
	taskk::end_operation("begin_task_name");
	return 0;
}

