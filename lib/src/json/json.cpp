//
// Created by César B. on 3/25/2024.
//

#include "json.hpp"
#include "macros/custom_types.hpp"
#include <jansson.h>

#define encode_session_timestamp(name) json_object_set_new(session, #name"_timestamp", json_integer(session_data.name##_timestamp.count()))

std::string json::dump(json_t * session)
{	freed char * dump = json_dumps(session, JSON_INDENT(4) | JSON_PRESERVE_ORDER);
	json_decref(session);
	return dump;
}

void json::destroy(json_t * j)
{	json_decref(j);
}

json_t * json::encode_session(data_types::session session_data)
{	// create the session's json object
	json_t * session = json_object();

	// encode session timestamps
	encode_session_timestamp(start);
	encode_session_timestamp(end);

	// encode operations
	json_object_set_new(session, "operations", encode_operation_list(session_data.operations));

	// return the encoded session
	return session;
}

json_t * json::encode_operation(data_types::timestamp_operation_pair pair_data)
{	// create the pair's json object
	json_t * pair = json_object();

	// encode the timestamp into the pair
	json_object_set_new(pair, "timestamp", json_integer(pair_data.first.count()));

	// create the operation's json object
	json_t * operation = json_object();

	// encode the label
	json_object_set_new(operation, "label", json_string(pair_data.second.label.c_str()));

	// encode the duration
	json_object_set_new(operation, "duration", json_integer(pair_data.second.duration.count()));

	// encode sub-operations
	json_object_set_new(operation, "sub_operations", encode_operation_list(pair_data.second.sub_operations));

	// encode the operation into the pair
	json_object_set_new(pair, "operation", operation);

	// return the pair
	return pair;
}

json_t * json::encode_operation_list(data_types::timestamp_operation_map list)
{	// create the list's json array
	json_t * operations = json_array();

	// encode and push all operations into the json array
	for(auto pair : list)
		json_array_append_new(operations, encode_operation(pair));

	// return the json array
	return operations;
}
