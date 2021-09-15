#pragma once

#include <thread>

#include "Task.h"
#include "MultithreadQueue.h"

class ThreadPool {
public:
	ThreadPool(int threads);
	~ThreadPool();

	void AddTask(Task* task);
	Task* GetReadyTask();

private:
	void ThreadFunc();
	std::vector<std::thread*> _threads;
	MultithreadQueue _taskQueue;
	MultithreadQueue _readyTaskQueue;
};

