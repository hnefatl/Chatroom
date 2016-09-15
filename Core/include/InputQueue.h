#ifndef _INPUTQUEUE_H
#define _INPUTQUEUE_H

#include "Core.h"

#include <mutex>
#include <queue>
#include <string>
#include <condition_variable>

class InputQueue
{
protected:
	std::queue<std::string> Queue;
	std::mutex QueueLock;
	std::condition_variable QueueVar;

public:
	CORE_API void Push(const std::string &Message);
	CORE_API std::string Pop();
};

#endif
