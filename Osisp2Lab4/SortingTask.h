#pragma once

#include "Task.h"

#include <vector>
#include <string>

class SortingTask : public Task {
public:
	SortingTask(std::vector<std::string>* words, int start, int end);
	void Execute();
	std::vector<std::string>* GetResult(int &start, int &end);

private:
	std::vector<std::string>* _words;
	int _start;
	int _end;
};

