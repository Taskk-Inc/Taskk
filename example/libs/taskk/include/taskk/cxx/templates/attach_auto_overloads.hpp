//
// Created by César B. on 4/2/2024.
//

#pragma once

#include <string>
#include <cstdint>
#include <iostream>

#pragma push_macro("DEFINE_OVERLOAD")

#define DEFINE_OVERLOAD(json_type, cxx_type) inline void attach_auto(std::string label, cxx_type const & data) { attach_##json_type(label, data); }

namespace taskk
{	DEFINE_OVERLOAD(real, float)
	DEFINE_OVERLOAD(integer, int8_t)
	DEFINE_OVERLOAD(integer, int16_t)
	DEFINE_OVERLOAD(integer, int32_t)
	DEFINE_OVERLOAD(integer, int64_t)
	DEFINE_OVERLOAD(integer, uint8_t)
	DEFINE_OVERLOAD(integer, uint16_t)
	DEFINE_OVERLOAD(integer, uint32_t)
	DEFINE_OVERLOAD(integer, uint64_t)
	DEFINE_OVERLOAD(string, char const *)
	template<typename _type> void attach_auto(std::string label, _type data)
	{	std::cerr << "Taskk : unsupported type '" << typeid(_type).name() << "' passed to attach_auto()";
		abort();
	}
}

#pragma pop_macro("DEFINE_OVERLOAD")
