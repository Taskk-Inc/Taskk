//
// Created by César B. on 3/26/2024.
//

#pragma once

#include "utils.hpp"

/// creates a scope-bound taskk operation with the given name
#define taskk_make_scope_operation(name) TASKK_CONCAT(taskk::operation_guard ___taskk_operation_guard_, __COUNTER__)(name)
