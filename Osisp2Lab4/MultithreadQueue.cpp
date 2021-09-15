#include "MultithreadQueue.h"

MultithreadQueue::MultithreadQueue() {
	_empty = true;
	_closed = false;
}

void MultithreadQueue::Add(Task* task) {
	const std::lock_guard<std::mutex> lock(_operationMutex);
	_tasks.push_back(task);

	_empty = false;
	_emptyCheck.notify_one();
}

void MultithreadQueue::Close() {
	_closed = true;
	_emptyCheck.notify_all();
}

Task* MultithreadQueue::Extract() {
	std::unique_lock<std::mutex> emptyLock(_emptyMutex);
	while (_empty && !_closed) _emptyCheck.wait(emptyLock);

	const std::lock_guard<std::mutex> lock(_operationMutex);

	if (_closed && !_tasks.size()) {
		return nullptr;
	}

	Task* task = _tasks.front();
	_tasks.erase(_tasks.begin());

	if (!_tasks.size()) {
		_empty = true;
	}

	return task;
}
