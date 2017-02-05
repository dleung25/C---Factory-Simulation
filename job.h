#pragma once
#include "order.h"
using namespace std;
class Job :public Order{
	vector<bool> install;
public:
	//default for machine when first created
	Job():Order(){
	}
	//order has a list of items that need to be installed (1+)
	Job(Order& order):Order(order){
		//false for all those items in that order
		for (size_t i = 0; i < order.size(); i++){
			install.push_back(false);
		}
	}
	//
	bool complete(){
		for (size_t i = 0; i < install.size(); i++){
			if (install[i] == false){
				return false;
			}
		}
		return true;
	}
	size_t size(){
		return install.size();
	}
	//install item at that index
	void installed(size_t index){
		install[index] = true;
	}
	//remove item at that index
	void remove(size_t index){
		install[index] = false;
	}
	//check status of item at that index
	bool checkInstall(size_t index){
		return install[index];
	}
};