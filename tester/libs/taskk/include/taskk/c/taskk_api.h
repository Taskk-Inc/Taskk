//
// Created by César B. on 3/25/2024.
//

#pragma once

#ifdef TASKK_API
	#error "Taskk : TASKK_API has multiple definitions"
#endif

#ifdef TASKK_API_CPP_GUARD
	#error "Taskk : TASKK_API_CPP_GUARD has multiple definitions"
#else
	#ifdef __cplusplus
		#define TASKK_API_CPP_GUARD extern "C"
	#else
		#define TASKK_API_CPP_GUARD
	#endif
#endif

#ifdef TASKK_EXPORT
	#ifdef TASKK_IMPORT
		#error "Taskk : TASKK_IMPORT and TASKK_EXPORT are both defined"
	#endif
	#define TASKK_API TASKK_API_CPP_GUARD __declspec(dllexport)
#else
	#define TASKK_API TASKK_API_CPP_GUARD __declspec(dllimport)
#endif
