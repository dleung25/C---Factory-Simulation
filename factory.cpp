#pragma once
using namespace std;
#include "job.h"
#include "machine.h"
class Factory
{
	ItemManager im;
	OrderManager om;
	TaskManager tm;
	vector<Job> jobs;
	vector<Machine> machines;
	
public:
	Factory(ItemManager&& imTwo, OrderManager&& omTwo, TaskManager&& tmTwo) :im(move(imTwo)), om(move(omTwo)), tm(move(tmTwo)) {
		//for every task in taskmanager, put it into machine vector
		cout << "Start creating machines!" << endl;
		for (size_t i = 0; i < tm.getSize(); i++){
			Machine temp(*tm.find(tm.getName(i)), tm);
			machines.push_back(temp);
			machines[i].print(cout);
		}
		//find source machine, look for a machine that is a source AND not a sink (size_t index) set index to where the source machine is
		size_t sourceIndex = 1000000;
		bool sourceError = false;
		for (size_t j = 0; j < machines.size(); j++){
			if (!machines[j].isSink()){
				if (machines[j].isSource()){
					if (sourceIndex == 1000000){
						sourceIndex = j;

					}
				}
			}
		}
		//throw error if more than 1 source machine
		//throw error if can't find any source machine
		
		if (sourceIndex == 1000000){
			throw string("Can't find any source machine");
		}
		else if (sourceError){
			throw string("There is more than one source machine");
		}
		else{
			cout << "Source machine is at index " << sourceIndex << endl;
		}
		//go through all orders in order manager
		//push each order into the source machine in order
		cout << "Start pushing orders through!" << endl;
		for (size_t k = 0; k < om.size(); k++){
			Job temporary(*om.find(k));
			jobs.push_back(temporary);
		}
		for (size_t w = 0; w < jobs.size(); w++){
			machines[sourceIndex].push(move(jobs[w]));
			machines[sourceIndex].increaseInput();
		}
		//run each job until all jobs are done
		while (machines[sourceIndex].getNoInputs() != 0){
			machines[sourceIndex].run(im, machines);
			bool currentJobComplete = false;
			size_t indexSink;
			Job temp;
			//run current tracking job until it reaches sink
			while (!currentJobComplete){
				for (size_t zq = 0; zq < machines.size(); zq++){
					while (!machines[zq].empty() && zq!=sourceIndex){
						machines[zq].run(im, machines);
						if (machines[zq].isSink()){ 
							indexSink = zq;
							currentJobComplete = true;
						}
					}
				}
			}
			temp = *machines[indexSink].returnJob();
			//check if the job was complete at sink
			if (temp.complete()){
				machines[sourceIndex].decreaseinput();
			}
			//if it isn't complete, push it back into the source machine at the back of the queue
			else{
				machines[sourceIndex].push(move(temp));
			}
		}
		//run each job at the next machine
		
		//create infinite loop + counter
		//flag = true; 
		cout << "All jobs are complete, factory will now shut down. Goodbye!" << endl;
		//go through each machine , if queue empty, break; (empty());

		//set to false if you have jobs left to do
		//loop for all machines, execute run(im, machines)
		

		

	}
};


int validate(ItemManager &im, OrderManager &om, TaskManager &tm){
	int errors = 0;
	//check order, that items in order exist in itemlist
	for (size_t h = 0; h < om.size(); h++){
		for (size_t k = 0; k < om.itemSize(h); k++){
			string item = "";
			item = om.itemListItem(h, k);
			bool itemCheck = false;
			//cout << "Check item " << item <<" for customer " << om.getCustomer(h);
			for (size_t j = 0; j < im.getSize(); j++){
				if (im.find(item)->getName() == item){
					itemCheck = true;
				}
			}
			if (itemCheck){
				//cout << " | Passed!";
			}
			else{
				//cout << " | Failed, item not in item list.";
				errors++;
			}
			//cout << endl;
		}
	}
	//check items, that the installer remover exist in task
	for (size_t i = 0; i < im.getSize(); i++){
		string installer = im.getInstaller(i);
		string remover = im.getRemover(i);
		bool installerCheck = false;
		bool removerCheck = false;
		//cout << "Check installer/remover " << installer << "/"<<remover <<" for item " << im.getName(i);
		for (size_t z = 0; z < tm.getSize(); z++){
			if (tm.getName(z) == installer){
				installerCheck = true;
			}
			if (tm.getName(z) == remover){
				removerCheck = true;
			}
		}
		if (installerCheck){
		}
		else{
			errors++;
		}
		if (removerCheck){
		}
		else{
			errors++;
		}
		if (installerCheck && removerCheck){
			//cout << " | Passed!";
		}
		//cout << endl;
	}
	// task checks for accept task
	for (size_t a = 0; a < tm.getSize(); a++){
		string taskAccept = "";
		bool acceptCheck = false;
		if (tm.getAccept(a) != ""){
			taskAccept = tm.getAccept(a);
		}
		else{
			acceptCheck = true;
		}
		//cout << "Check accept " << taskAccept << " for task " << tm.getName(a) << endl;
		for (size_t b = 0; b < tm.getSize(); b++){
			if (tm.getName(b) == taskAccept){
				acceptCheck = true;
			}
			//cout << "Compare accept task " << taskAccept << " with " << tm.getName(b) << endl;
		}
		if (!acceptCheck){
			errors++;
			//cout << "Accept error" << endl;
		}
	}
	//task checks for reject task
	for (size_t c = 0; c < tm.getSize(); c++){
		string taskReject = "";
		bool rejectCheck = false;
		if (tm.getReject(c) != ""){
			taskReject = tm.getReject(c);
		}
		else{
			rejectCheck = true;
		}
		//cout << "Check reject " << taskReject << " for task " << tm.getName(c) << endl;
		for (size_t d = 0; d < tm.getSize(); d++){
			if (tm.getName(d) == taskReject){
				rejectCheck = true;
			}
			//cout << "Compare reject task " << taskReject << " with " << tm.getName(d) << endl;
		}
		if (!rejectCheck){
			errors++;
			//cout << "Reject error" << endl;
		}
	}
	return errors;
}

int main(int argc, char* argv[]){
	if (argc != 5){
		cerr << "Usage : " << argv[0] << "Item-csv order-csv task-csv csv-seperator\n";
		return 1;
	}
	string itemFile = argv[1];
	string orderFile = argv[2];
	string taskFile = argv[3];
	char   seperator = argv[4][0];

	try{
		string f;

		vector<vector<string>> ItemCsvData;
		vector<vector<string>> OrderCsvData;
		vector<vector<string>> TaskCsvData;

		csvread(itemFile, seperator, ItemCsvData);
		csvread(orderFile, seperator, OrderCsvData);
		csvread(taskFile, seperator, TaskCsvData);

		TaskManager tm(TaskCsvData);
		tm.print();
		f = taskFile + string(".gv");
		tm.graph(f);

		ItemManager im(ItemCsvData);
		im.print();
		f = itemFile + string(".gv");
		im.graph(f);

		OrderManager om(OrderCsvData);
		om.print();
		f = orderFile + string(".gv");
		om.graph(f);

		int errors = validate(im, om, tm);
		if (errors){
			throw string("Bad data files - fix and resubmit");
		}
		Factory factory(move(im), move(om), move(tm));
	}

	catch (string& e){
		cerr << argv[0] << " : ";
		cerr << e << "\n";
	}
	return 0;
}