//
// Created by César B. on 3/25/2024.
//

#include "json.hpp"
#include "macros/custom_types.hpp"
#include <jansson.h>

std::string json::encode_session(data_types::session)
{	json_auto_t * object = json_object();
	json_object_set_new(object, "la grosse pute de mere a pyerre", json_integer(24));
	freed char * dump = (char *)malloc(25); //json_dumps(object, JSON_INDENT(JSON_MAX_INDENT) | JSON_PRESERVE_ORDER);
	return dump;
}
