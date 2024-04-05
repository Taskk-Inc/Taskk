//
// Created by César B. on 4/5/2024.
//

#include "logic/logic.hpp"
#include "utils/utils.hpp"

/// looks for an operation that's been marked as finished in the ongoing operations
int main()
{	logic::begin_operation("main");
	logic::begin_operation("sub");
	logic::end_operation("sub");
	utils::find_ongoing_operation("sub");
	logic::end_operation("main");
}
