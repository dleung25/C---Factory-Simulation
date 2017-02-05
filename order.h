//need to fix
#pragma once

#include "util.h"
using namespace std;
class Order{
	string customerName, productName;
	vector<std::string> itemList;
	bool validCustomerName(std::string name);
	bool validProductName(std::string name);

public:
	Order(){
		customerName = "";
		productName = "";
	}
	Order(std::vector<std::string>& row);
	void print();
	void graph(std::ofstream& of);
	std::string& getProduct(){ return productName; }
	size_t size(){ return itemList.size(); }
	std::string& getItem(size_t itemIndex) { return itemList[itemIndex]; }
	std::string& getCustomer(){ return customerName; }
};

class OrderManager{
	std::vector<Order> OrderList;
public:
	OrderManager(std::vector<std::vector<string>> csvData);
	void print();
	void graph(std::string& filename);
	size_t size(){ return OrderList.size(); }
	size_t itemSize(size_t orderIndex){ return OrderList[orderIndex].size(); }
	std::string& itemListItem(size_t orderIndex, size_t itemIndex){
		return OrderList[orderIndex].getItem(itemIndex);
	}
	//return customer 
	std::string& getCustomer(size_t orderIndex){
		return OrderList[orderIndex].getCustomer();
	}
	Order* find(size_t i){
		return &OrderList[i];
	}
};
