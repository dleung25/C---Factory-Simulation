//need to fix
#include "util.h"
#include "order.h"
using namespace std;

bool Order::validCustomerName(std::string name)
{
	if (name.size() > 0 && isalpha(name[0]))
		return true;
	return false;
}
bool Order::validProductName(std::string name)
{
	if (name.size() > 0 && isalpha(name[0]))
		return true;
	return false;
}
Order::Order(std::vector<std::string>& row){
	if (row.size() < 3){
		throw std::string("Expected 2 or more fields, found --> ") + to_string(row.size());
	}
	if (validCustomerName(row[0])){
		customerName = row[0];
	}
	else{
		throw std::string("Expected a customer name, found --> ") + row[0] + " <--";
	}
	if (validProductName(row[1])){
		productName = row[1];
	}
	else{
		throw std::string("Expected a product name, found --> ") + row[1] + " <--";
	}

	for (size_t item = 2; item < row.size(); item++){
		if (validateItemName(row[item]))
			itemList.push_back(row[item]);
	}
}
void Order::print(){
	std::cout << "customer name, product name, [items] = "
		<< customerName << " , "
		<< productName;
	static int number = 1;
	for (auto e : itemList)
		cout << " , " << e;
	cout << "\n";
	number++;
}
void Order::graph(std::ofstream& of){
	for (auto e : itemList)
		of << '"' << customerName << '"' << "->" << '"' << " Item " << e << '"' << " [color=green];\n";
	of << "\n";
}


OrderManager::OrderManager(std::vector<std::vector<string>> csvData){
	int rowCount = 0;
	for (auto row : csvData){
		try{
			rowCount++;
			OrderList.push_back(Order(row));
		}
		catch (std::string& e){
			std::cerr << "Problem with row " << rowCount << " : " << e << std::endl;
		}
	}
}
void OrderManager::print(){
	for (auto e : OrderList)
		e.print();
}
void OrderManager::graph(std::string& filename){
	std::ofstream of(filename);
	if (of.is_open()){
		of << "Digraph myGraph {\n";
		for (auto t : OrderList)
			t.graph(of);
		of << "}\n";
		of.close();
	}

	std::string cmd = "dot -Tpng " + filename + " > " + filename + ".png";
	std::cout << std::endl << cmd << std::endl;

	system(cmd.c_str());
}

/*
using namespace std;

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

OrderManager tm(csvData);

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