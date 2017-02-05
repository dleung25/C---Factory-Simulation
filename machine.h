#pragma once
#include <queue>
#include "item.h"
#include "task.h"
#include "job.h"
using namespace std;
class Machine :public Task {
	bool installer, remover, sink, source;
	size_t numberOfInputs;
	queue <Job> input;
	Job job;
public:
	Machine(Task& task, TaskManager& tm);

	void push(Job&& job);
	//check queue empty
	bool empty();
	void print(ostream& os);
	void classify(TaskManager& tm);
	void run(ItemManager& im, vector<Machine>& machines);
	void increaseInput(){numberOfInputs++;}
	void decreaseinput(){ numberOfInputs--; }
	size_t getNoInputs(){return numberOfInputs;}
	//function ONLY used when job is not complete but at sink
	Job* returnJob(){ return &job; }
	bool isSource(){return source;}
	//detect if this is a sink or not
	bool isSink(){return sink;}
};