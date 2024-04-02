//
// Created by César B. on 3/25/2024.
//

#pragma once

#include <string>
#include <chrono>
#include <map>
#include "data_types/data_types.hpp"

struct json_t;

namespace json
{	/// also destroys the given object
	std::string dump(json_t *);
	void destroy(json_t*);
	json_t * encode_session(data_types::session);
	json_t * encode_operation(data_types::timestamp_operation_pair);
	json_t * encode_operation_list(data_types::timestamp_operation_map);
	json_t * encode_operation_attached_data(data_types::attached_data_list);
}
