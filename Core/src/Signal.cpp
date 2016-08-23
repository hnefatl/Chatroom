#include "Signal.h"

Signal::Signal()
{
	set = false;
}
Signal::Signal(const bool Set)
{
	set = Set;
}

void Signal::Set()
{
	std::unique_lock<std::mutex> Lock(m);
	set = true;
	var.notify_all();
}
void Signal::Reset()
{
	std::unique_lock<std::mutex> Lock(m);
	set = false;
	var.notify_all();
}

bool Signal::IsSet() const
{
	return set;
}

void Signal::Wait()
{
	std::unique_lock<std::mutex> Lock(m);
	var.wait(Lock, [this] () { return set; });
}
