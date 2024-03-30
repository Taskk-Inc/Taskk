//
// Created by César B. on 3/25/2024.
//

#pragma once

#include "taskk/c/taskk_api.h"

enum class taskk_data_type { taskk_string, taskk_integer, taskk_real, taskk_boolean, };

TASKK_API void taskk_begin_operation(char * name);
TASKK_API void taskk_attach_string(char * data);
TASKK_API void taskk_attach_integer(int data);
TASKK_API void taskk_attach_real(double data);
TASKK_API void taskk_attach_boolean(bool data);
TASKK_API void taskk_end_operation(char * name);
