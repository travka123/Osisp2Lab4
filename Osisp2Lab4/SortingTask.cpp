#include "SortingTask.h"

#include <algorithm>

SortingTask::SortingTask(std::vector<std::string>& words, int start, int end) : _words(words), _start(start), _end(end) {	}

void SortingTask::Execute() {
	std::sort(std::next(_words.begin(), _start), std::next(_words.begin(), _end));
}

std::vector<std::string>& SortingTask::GetResult(int& start, int& end) {
	start = _start;
	end = _end;
	return _words;
}
