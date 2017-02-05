#include "util.h"
#pragma once
class Task{
	std::string name, accept, reject, slot;
	bool isSlotCount(std::string& s);

public:
	Task(std::vector<std::string>& row);
	void print();
	void graph(std::ofstream& of);
	std::string& getAccept(){ return accept; }
	std::string& getReject(){ return reject; }
	std::string& getName(){ return name; }
};

class TaskManager{
	std::vector<Task> taskList;
public:
	TaskManager(std::vector<std::vector<std::string>> csvData);
	void print();
	void graph(std::string& filename);
	size_t getSize(){ return taskList.size(); }
	std::string& getAccept(int index){ return taskList[index].getAccept(); }
	std::string& getReject(int index){ return taskList[index].getReject(); }
	std::string& getName(int index){ return taskList[index].getName(); }
	Task* find(std::string name){
		for (size_t i = 0; i < taskList.size(); i++){
			if (taskList[i].getName() == name){
				return &taskList[i];
			}
		}
		return 0;
	}
};
