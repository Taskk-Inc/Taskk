//
// Created by César B. on 3/27/2024.
//

#include "switch.h"
#include <taskk.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

void spin_wait(clock_t ms) { clock_t target = clock() + ms; while(clock() < target); }

int c_main()
{	puts("running the c tester");
	// operation 1
	taskk_begin_operation("operation_1");
	spin_wait(20);
	{	// operation 1.1
		taskk_begin_operation("operation_1_1");
		taskk_end_operation("operation_1_1");
		// operation 1.2
		taskk_begin_operation("operation_1_2");
		taskk_attach_string("my very cool log", "some useful info");
		spin_wait(30);
		taskk_attach_integer("counter", 1875);
		spin_wait(25);
		taskk_attach_real("math function result", M_PI);
		spin_wait(45);
		taskk_attach_boolean("some flag", false);
		spin_wait(100);
		taskk_attach_boolean("some other flag", true);
		taskk_end_operation("operation_1_2");
	}
	taskk_end_operation("operation_1");
	// operation 2
	taskk_begin_operation("operation_2");
	spin_wait(60);
	taskk_end_operation("operation_2");
	return 0;
}
