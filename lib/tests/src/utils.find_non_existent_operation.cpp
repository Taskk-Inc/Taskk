//
// Created by César B. on 4/5/2024.
//

#include "logic/logic.hpp"
#include "utils/utils.hpp"

int main()
{
	logic::begin_operation("main");
	utils::find_ongoing_operation("invalid label");
	logic::end_operation("main");
	return EXIT_SUCCESS;
}