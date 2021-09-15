#pragma once

#include <mutex>
#include <vector>

#include "Task.h"

class MultithreadQueue {
public:
	MultithreadQueue();

	void Add(Task *task);
	void Close();
	Task* Extract();

private:
	std::vector<Task*> _tasks;
	bool _closed;
	std::mutex _operationMutex;
	bool _empty;
	std::condition_variable _emptyCheck;
	std::mutex _emptyMutex;
};

