//
// Created by César B. on 3/27/2024.
//

#pragma once

#include <stdbool.h>

#define USE_CXX 0

#if USE_CXX
	#define c_main disabled_main
	#define cxx_main main
#else
	#define c_main main
	#define cxx_main disabled_main
#endif
