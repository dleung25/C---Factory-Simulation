#pragma once
#include "util.h"

class Item{
	std::string name, installer, code, remover, description;
	bool validCode(std::string& s);

public:
	Item(std::vector<std::string>& row);
	void print();
	void graph(std::ofstream& of);
	std::string& getInstaller(){ return installer; }
	std::string& getRemover() { return remover; }
	std::string& getName() { return name; }
};

class ItemManager{
	std::vector<Item> ItemList;
public:
	ItemManager(std::vector<std::vector<std::string>>& csvData);
	void print();
	void graph(std::string& filename);
	//implement these
	std::size_t getSize(){ return ItemList.size(); }
	std::string getInstaller(int index){ return ItemList[index].getInstaller(); }
	std::string getRemover(int index){ return ItemList[index].getRemover(); }
	std::string getName(int index){ return ItemList[index].getName(); }
	//std::vector <Item> list();
	Item* find(std::string name);
};
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

ItemManager tm(csvData);

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