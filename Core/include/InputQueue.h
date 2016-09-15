#ifndef _INPUTQUEUE_H
#define _INPUTQUEUE_H

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
	void Push(const std::string &Message);
	std::string Pop();
};

#endif
