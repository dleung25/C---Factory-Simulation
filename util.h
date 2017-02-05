#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <ciso646>
#include <cctype>



std::string& trimSpace(std::string& s, char trimChar = ' ');

void csvprint(std::vector<std::vector<std::string>>& csvData);

void csvread(std::string& filename, char delim, std::vector< std::vector<std::string> > &csv);

bool validateTaskName(std::string& name);

bool validateItemName(std::string& name);

//void csvdump(std::string& filename, char separator, vector< vector<string> >& csvData);