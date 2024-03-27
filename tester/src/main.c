//
// Created by César B. on 3/27/2024.
//

#include "switch.h"
#include <taskk.h>
#include <stdio.h>

int c_main()
{	puts("running the c tester");
	// operation 1
	taskk_begin_operation("operation_1");
	{	// operation 1.1
		taskk_begin_operation("operation_1_1");
		taskk_end_operation("operation_1_1");
		// operation 1.2
		taskk_begin_operation("operation_1_2");
		taskk_end_operation("operation_1_2");
	}
	taskk_end_operation("operation_1");
	// operation 2
	taskk_begin_operation("operation_2");
	taskk_end_operation("operation_2");
	return 0;
}
