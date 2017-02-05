#include "util.h"
#include "task.h"
using namespace std;
bool Task::isSlotCount(std::string& s){
	if (s.empty())
		return false;
	for (auto c : s)
		if (not isdigit(c))
			return false;
	return true;
}
Task::Task(std::vector<std::string>& row) :slot("1"){
	switch (row.size()){
	case 4:
		if (validateTaskName(row[3]))
			reject = row[3];
		else
			throw std::string("Expected a reject task, found --> ") + row[3] + " <--";
	case 3:
		if (validateTaskName(row[2]))
			accept = row[2];
		else
			throw std::string("Expected a accept task, found --> ") + row[2] + " <--";
	case 2:
		if (isSlotCount(row[1]))
			slot = row[1];
		else
			throw std::string("Expected a slot task, found --> ") + row[1] + " <--";
	case 1:
		if (validateTaskName(row[0]))
			name = row[0];
		else
			throw std::string("Expected a task, found --> ") + row[0] + " <--";
		//default:
		//	throw std::string("Expected 1,2,3, or 4 fields, found ") + std::to_string(row.size());
	}
}
void Task::print(){
	std::cout << "name, slots, accept, reject = "
		<< name << " / " << slot << " / " << accept << " / " << reject << " / \n";
}
void Task::graph(std::ofstream& of){
	if (not accept.empty())
		of << '"' << name << '"' << "->" << '"' << accept << '"' << " [color=green];\n";
	//cout << '"' << name << '"' << "-->" << '"' << accept << '"' << " [color=green];\n";
	if (not reject.empty())
		of << '"' << name << '"' << "->" << '"' << reject << '"' << " [color=red];\n";
	//cout << '"' << name << '"' << "-->" << '"' << reject << '"' << " [color=red];\n";

	if (accept.empty() && reject.empty())
		of << '"' << name << '"' << std::endl;
	//cout<< '"' << name << '"' << std::endl;
}



TaskManager::TaskManager(std::vector<std::vector<std::string>> csvData){
	int rowCount = 0;
	for (auto row : csvData){
		try{
			rowCount++;
			taskList.push_back(Task(row));
		}
		catch (std::string& e){
			std::cerr << "Problem with row " << rowCount << " : " << e << std::endl;
		}
	}
}
void TaskManager::print(){
	for (auto t : taskList)
		t.print();
}
void TaskManager::graph(std::string& filename){
	std::ofstream of(filename);
	if (of.is_open()){
		of << "Digraph myGraph { \n";
		//cout << "Digraph myGraph { \n";
		for (auto t : taskList)
			t.graph(of);
		of << "} \n";
		//cout << "} \n";
		of.close();
	}

	std::string cmd = "dot -Tpng " + filename + " > " + filename + ".png";
	std::cout << std::endl << cmd << std::endl;

	system(cmd.c_str());
}
;
/*using namespace std;

int main(int argc, char* argv[]){
if (argc != 3){
cerr << "Usage : " << argv[0] << "csv-file csv-seperator\n";
return 1;
}
string filename = argv[1];
char   seperator = argv[2][0];

try{
vector<vector<string>> csvData;

csvread(filename, seperator, csvData);

TaskManager tm(csvData);

tm.print();

string f = filename + string(".gv");
tm.graph(f);
}
catch (string& e){
cerr << e << "\n";
}
return 0;
}
*/