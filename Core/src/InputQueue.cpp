#include "InputQueue.h"

void InputQueue::Push(const std::string &Message)
{
	{
		std::unique_lock<std::mutex> Lock(QueueLock);
		Queue.push(Message);
	}
	QueueVar.notify_one();
}

std::string InputQueue::Pop()
{
	std::unique_lock<std::mutex> Lock(QueueLock);
	QueueVar.wait(Lock, [this] { return !Queue.empty(); });
	std::string Result = Queue.front();
	Queue.pop();
	return Result;
}
