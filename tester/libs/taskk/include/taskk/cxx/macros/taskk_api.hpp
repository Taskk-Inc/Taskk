//
// Created by César B. on 3/25/2024.
//

#pragma once

#ifdef TASKK_CXX_API
	#error "Taskk : TASKK_CXX_API has multiple definitions"
#endif

#ifdef TASKK_EXPORT
	#ifdef TASKK_IMPORT
		#error "Taskk : TASKK_IMPORT and TASKK_EXPORT are both defined"
	#endif
	#define TASKK_CXX_API __declspec(dllexport)
#else
	#define TASKK_CXX_API __declspec(dllimport)
#endif
