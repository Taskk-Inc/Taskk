//
// Created by César B. on 3/26/2024.
//

#pragma once

#ifdef freed
	#error "freed is already defined"
#endif
#include <malloc.h>
void ___freed_cb(void * ptr) { free(*(void **)ptr); }
#define freed __attribute__((cleanup(___freed_cb)))
