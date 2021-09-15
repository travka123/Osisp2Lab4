#include "Sort.h"

#include "SortingTask.h"
#include "ThreadPool.h"

void MergeTasks(ThreadPool* threadPool, std::vector<std::string>* out, int tasksLeft);

void Sort(std::vector<std::string>* in, std::vector<std::string>* out, int threads, int minElemInTask) {
	ThreadPool pool(threads);
	

	if (!(in->size() && threads)) {
		return;
	}

	int taskCount;
	float taskElemCount;
	if (threads > (int)in->size() / minElemInTask) {
		taskCount = (in->size() / minElemInTask) ? in->size() / minElemInTask : 1;
		taskElemCount = minElemInTask;
	}
	else {
		taskCount = threads;
		taskElemCount = (float)in->size() / threads;
	}

	std::thread outThread(MergeTasks, &pool, out, taskCount);

	std::vector<SortingTask*> stv;
	for (float i = 0;;) {
		SortingTask* newTask;
		if (i + taskElemCount + taskElemCount <= in->size()) {
			newTask = new SortingTask(in, (int)i, (int)(i + taskElemCount));
			pool.AddTask(newTask);
			i += taskElemCount;
		}
		else {
			newTask = new SortingTask(in, (int)i, in->size());
			pool.AddTask(newTask);
			break;
		}
		stv.push_back(newTask);
	}

	outThread.join();

	for(int i = 0; i < stv.size(); i++) delete stv[i];
}

void MergeVectors(std::vector<std::string>* vec1, int i1, int end1, 
	std::vector<std::string>* vec2, int i2, int end2, std::vector<std::string>* out) {

	while ((i1 != end1) && (i2 != end2)) {
		if (vec1->at(i1).compare(vec2->at(i2)) > 0) {
			out->push_back(vec2->at(i2));
			i2++;
		}
		else {
			out->push_back(vec1->at(i1));
			i1++;
		}
	}

	if (i1 != end1) {
		for (int i = i1; i < end1; i++) out->push_back(vec1->at(i));
	}
	else {
		for (int i = i2; i < end2; i++) out->push_back(vec2->at(i));
	}
}

void MergeTasks(ThreadPool* threadPool, std::vector<std::string>* out, int tasksLeft) {
	if (tasksLeft == 1) {
		int i1, end1;
		SortingTask* t1 = ((SortingTask*)threadPool->GetReadyTask());
		std::vector<std::string>* vec1 = t1->GetResult(i1, end1);

		for (int i = i1; i < end1; i++) out->push_back(vec1->at(i));
	}
	else if (tasksLeft == 2) {
		int i1, end1;
		SortingTask* t1 = ((SortingTask*)threadPool->GetReadyTask());
		std::vector<std::string>* vec1 = t1->GetResult(i1, end1);

		int i2, end2;
		SortingTask* t2 = ((SortingTask*)threadPool->GetReadyTask());
		std::vector<std::string>* vec2 = t2->GetResult(i2, end2);

		MergeVectors(vec1, i1, end1, vec2, i2, end2, out);
	}
	else if (tasksLeft / 2 == 1) {
		int i1, end1;
		SortingTask* t1 = ((SortingTask*)threadPool->GetReadyTask());
		std::vector<std::string>* vec1 = t1->GetResult(i1, end1);

		std::vector<std::string> out1;
		MergeTasks(threadPool, &out1, 2); // tasksLeft - tasksLeft / 2 = 2

		MergeVectors(vec1, i1, end1, &out1, 0, out1.size(), out);
	}
	else {
		std::vector<std::string> out1;
		MergeTasks(threadPool, &out1, tasksLeft / 2);
		std::vector<std::string> out2;
		MergeTasks(threadPool, &out2, tasksLeft - tasksLeft / 2);
		MergeVectors(&out1, 0, out1.size(), &out2, 0, out2.size(), out);
	}
}



