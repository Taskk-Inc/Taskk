//
// Created by César B. on 3/26/2024.
//

#pragma once

/// scanned token concatenation macro
#define TASKK_CONCAT_IMPL(a, b) a##b
#define TASKK_CONCAT(a, b) TASKK_CONCAT_IMPL(a, b)
