//
// Created by César B. on 3/25/2024.
//

#include "utils.hpp"

std::chrono::microseconds utils::get_unix_time()
{	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch());
}
