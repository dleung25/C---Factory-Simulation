#include "machine.h"

Machine::Machine(Task& task, TaskManager& tm):Task(task),installer(false),remover(false),sink(false),source(false),numberOfInputs(0),job(){
	classify(tm);
}
void Machine::push(Job&& job){
	input.push(move(job));
}
//check queue empty
bool Machine::empty(){
	return input.empty();
}
void Machine::print(ostream& os){
	os << this->getName();
	if (sink){
			os << " This machine is sink" << endl;
		}
	if (installer)
	{
		os << " This is an installer"<<endl;
	}
	else if (remover){
		os << " This is a remover"<<endl;
	}
	else if (source){
		os << " This machine is source" << endl;
	}

	
}
// check if this machine is an installer or a remover for any other machine, source/sink
void Machine::classify(TaskManager& tm){
	string task = this->getName();
	//check if this machine is an installer or remover
	for (size_t i = 0; i < tm.getSize(); i++){
		if (tm.getAccept(i) == task){
			installer = true;
		}
		if (tm.getReject(i) == task){
			remover = true;
		}
	}
	//if both flags true
	if (installer && remover){
		throw("Cannot have Installer/remover both true") + getName();
	}
	//check if sink
	if (installer || remover){
		if (this->getAccept() == "" && this->getReject() == ""){
			sink = true;
		}
	}
	//this is a sourece
	if (this->getAccept() != "" || this->getReject() != ""){
		source = true;
		installer = true;
	}
}
void Machine::run(ItemManager& im, vector<Machine>& machines){
	if (empty()){
		return;
	}
	else{
		//move job from job queue to machine
		job = (move(input.front()));
		input.pop();
		cout << "Have to install for the order for "<<job.getCustomer()<< ": ";
		for (size_t aw = 0; aw < job.size(); aw++){
			if (!job.checkInstall(aw)){
				cout<< job.getItem(aw) <<",";
			}
		}
		cout << endl;
		
		//if reached end of node job is either "complete" or at sink node but not complete
		if (sink){
			if (job.complete()){
				cout << "Job complete!" << endl;
				return;
			}
			else{
				cout << job.getCustomer();
				cout << "'s Job at sink node, but not complete" << endl;
				return;
			}
		}
		auto moveJob = [&machines, this](Job& jobs, string machineName){
			for (size_t i = 0; i < machines.size(); i++){
				if (machines[i].getName() == machineName){
					machines[i].push(move(jobs));
					machines[i].increaseInput();
					break;
					//machine moved
				}
			}
		};
		
		bool machineWorked = false;
		if (installer){

			for (size_t i = 0; i < job.size(); i++){
				if (job.checkInstall(i)){
					continue;
					
				}
				cout << "Trying to install " << job.getItem(i) <<endl;
				string itemToInstall = job.getItem(i);
				Item* item = im.find(itemToInstall);
				//if our itemmanager has this item from our job order, and its equal to this machine, install this
				if (item && item->getInstaller() == getName()){
					job.installed(i);
					cout << "item installed from this machine installs ";
					machineWorked = true;
				}
				else{
					cout << "did not install from this machine that installs ";
				}
				cout << this->getName() << endl;
			}
		}
		if (remover){
			for (size_t i = 0; i < job.size(); i++){
				if (job.checkInstall(i)==false){
					continue;
				}
				cout << "Trying to remove " << job.getItem(i) << endl;
				string itemToRemove = job.getItem(i);
				Item* item = im.find(itemToRemove);
				if (item && item->getRemover() == getName()){
					job.remove(i);
					cout << "item removed from this machine removes ";
					machineWorked = true;
				}
				else{
					cout << "did not remove from this machine that removes ";
				}
				cout << this->getName() << endl;
			}
		}
		string acceptName = getAccept();
		string rejectName = getReject();

		
		//if there is no accept task, pass it on to reject
		if (acceptName ==""){
			moveJob(job, rejectName);
			return;
		}
		//if there is no reject task, pass it on to accept
		if (rejectName == ""){
			moveJob(job, acceptName);
			return;
		}
		//randomized on which of the two paths it will pass it onto, simulating failure rate
		if (rand() % 2){
			moveJob(job, acceptName);
			return;
		}
		else{
			moveJob(job, rejectName);
			return;
		}
	}
}