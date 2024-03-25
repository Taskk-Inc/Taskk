//
// Created by César B. on 3/25/2024.
//

#pragma once



namespace logic
{	/// calls init() if not called already
	void ensure_initialization();
	/// initialize the session, bind shutdown() to atexit()
	void init();
	/// exit callback, saves the profiling session into a file named correspondingly to the current time and date
	void shutdown();
}
