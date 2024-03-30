//
// Created by César B. on 3/25/2024.
//

#pragma once

#include "taskk/c/taskk_api.h"
#include <stdbool.h>

TASKK_API void taskk_begin_operation(char * name);
TASKK_API void taskk_attach_string(char * data);
TASKK_API void taskk_attach_integer(int data);
TASKK_API void taskk_attach_real(double data);
TASKK_API void taskk_attach_boolean(bool data);
TASKK_API void taskk_end_operation(char * name);
