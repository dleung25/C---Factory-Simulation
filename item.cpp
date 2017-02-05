#include "util.h"
#include "item.h"
using namespace std;
//add this

bool Item::validCode(std::string& s){
	if (s.size() > 0)
		return true;
	return false;
}


Item::Item(std::vector<std::string>& row){
	switch (row.size()){
	case 5:
		description = row[4];
	case 4:
		if (validCode(row[3]))
			code = row[3];
		else
			throw std::string("Expected a code, found --> ") + row[3] + " <--";
	case 3:
		if (validateTaskName(row[2]))
			remover = row[2];
		else
			throw std::string("Expected a remover task name, found --> ") + row[2] + " <--";
	case 2:
		if (validateTaskName(row[1]))
			installer = row[1];
		else
			throw std::string("Expected a installer task slot, found --> ") + row[1] + " <--";
	case 1:
		if (validateItemName(row[0]))
			name = row[0];
		else
			throw std::string("Expected a item name, found --> ") + row[0] + " <--";
		//default:
		//throw std::string("Expected 4 or 5 fields, found ") + std::to_string(row.size());
	}
}
void Item::print(){
	std::cout << "name, slots, accept, reject = "
		<< name << " , "
		<< installer << " , "
		<< remover << " , "
		<< code << " , ";
	if (not description.empty())
		std::cout << description << "\n";
	std::cout << "\n";

}
void Item::graph(std::ofstream& of){
	of << '"' << name << '"' << "->" << '"' << " " << installer << '"' << " [color=green];\n";
	of << '"' << name << '"' << "->" << '"' << " " << remover << '"' << " [color=red];\n";
	of << "\n";
}


ItemManager::ItemManager(std::vector<std::vector<string>>& csvData){
	int rowCount = 0;
	for (auto row : csvData){
		try{
			rowCount++;
			ItemList.push_back(Item(row));
		}
		catch (std::string& e){
			std::cerr << "Problem with row " << rowCount << " : " << e << std::endl;
		}
	}
}
void ItemManager::print(){
	for (auto e : ItemList)
		e.print();
}
void ItemManager::graph(std::string& filename){
	std::ofstream of(filename);
	if (of.is_open()){
		of << "Digraph myGraph {\n";
		for (auto t : ItemList)
			t.graph(of);
		of << "}\n";
		of.close();
	}

	std::string cmd = "dot -Tpng " + filename + " > " + filename + ".png";
	std::cout << std::endl << cmd << std::endl;

	system(cmd.c_str());
}
//match name with itemlist name and return item with that name
Item* ItemManager::find(std::string name){

	for (size_t i = 0; i < ItemList.size(); i++){
		if (ItemList[i].getName() == name){
			return &ItemList[i];
		}
	}
	return &ItemList[1];
}