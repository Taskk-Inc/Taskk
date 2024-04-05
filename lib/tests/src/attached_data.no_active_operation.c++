//
// Created by César B. on 4/5/2024.
//

#include "logic/logic.hpp"

int main()
{
	logic::begin_operation("main");
	logic::end_operation("main");
	logic::attach_operation_integer("value", 42);
	return 0;
}
