//
// Created by César B. on 3/25/2024.
//

#include "json.hpp"
#include "macros/custom_types.hpp"
#include "utils/utils.hpp"
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
	printf("Taskk : [json encoding] encoding operation '%s' with duration %lli\n", pair_data.second.label.c_str(), pair_data.second.duration.count());
	json_object_set_new(operation, "duration", json_integer(pair_data.second.duration.count()));

	// encode sub-operations
	json_object_set_new(operation, "sub_operations", encode_operation_list(pair_data.second.sub_operations));

	// encode attached data
	json_object_set_new(operation, "attached_data", encode_operation_attached_data(pair_data.second.attached_data));

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

json_t * json::encode_operation_attached_data(data_types::attached_data_list data)
{	/// array of container objects
	json_t * array = json_array();
	for(auto element : data)
	{	/// container object with fields 'label' and 'data'
		json_t * container = json_object();
		// label
		json_object_set_new(container, "label", json_string(element->label.c_str()));
		// data
		json_t * data_json;
		switch(element->type)
		{	using enum data_types::attached_operation_data::data_type;
			case string: data_json = json_string(element->data_string.c_str()); break;
			case integer: data_json = json_integer(element->data_integer); break;
			case real: data_json = json_real(element->data_real); break;
			case boolean: data_json = element->data_boolean ? json_true() : json_false(); break;
			default:
				utils::log_and_abort("json encoding : unknown attached data type");
		}
		json_object_set_new(container, "data", data_json);
		// add this container to the array
		json_array_append_new(array, container);
	}
	return array;
}
