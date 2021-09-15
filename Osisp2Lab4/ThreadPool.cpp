#include "ThreadPool.h"

ThreadPool::ThreadPool(int threads) {
	for (int i = 0; i < threads; i++) {
		_threads.push_back(new std::thread(&ThreadPool::ThreadFunc, this));
	}
}

ThreadPool::~ThreadPool() {
	_taskQueue.Close();
	_readyTaskQueue.Close();
	for (int i = 0; i < _threads.size(); i++) {
		_threads[i]->join();
		delete _threads[i];
	}
}

void ThreadPool::ThreadFunc() {
	Task *task;
	while (task = _taskQueue.Extract()) {
		task->Execute();
		_readyTaskQueue.Add(task);
	}
}

void ThreadPool::AddTask(Task* task) {
	_taskQueue.Add(task);
}

Task* ThreadPool::GetReadyTask() {
	return _readyTaskQueue.Extract();
}


