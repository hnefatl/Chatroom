#ifndef _SIGNAL_H
#define _SIGNAL_H

#include "Core.h"

#include <mutex>
#include <condition_variable>

class CORE_API Signal
{
protected:
	std::mutex m;
	std::condition_variable var;
	bool set;

public:
	Signal();
	Signal(const bool Set);

	void Set();
	void Reset();

	bool IsSet() const;

	void Wait();
};

#endif
