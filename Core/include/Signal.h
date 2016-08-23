#ifndef _SIGNAL_H
#define _SIGNAL_H

#include "Core.h"

#include <mutex>
#include <condition_variable>

class Signal
{
protected:
	std::mutex m;
	std::condition_variable var;
	bool set;

public:
	CORE_API Signal();
	CORE_API Signal(const bool Set);

	CORE_API void Set();
	CORE_API void Reset();

	CORE_API bool IsSet() const;

	CORE_API void Wait();
};

#endif
