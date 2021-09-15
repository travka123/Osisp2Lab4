#include "Sort.h"

#include "SortingTask.h"
#include "ThreadPool.h"

void Sort(std::vector<std::string>& words, int threads) {

	//TEST

	ThreadPool pool(1);
	SortingTask task(words, 0, words.size());
	pool.AddTask(&task);
	pool.GetReadyTask();
}