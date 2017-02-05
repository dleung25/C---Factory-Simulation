#include "util.h"
using namespace std;

bool validateTaskName(string& s){
	if (s.size() > 0 && isalpha(s[0]))
		return true;
	return false;
}

bool validateItemName(string& s){
	return ((not s.empty()) and isalpha(s[0]));
}
void csvprint(vector<vector<string>>& csvData){
	for (size_t row = 0; row < csvData.size(); row++){
		for (size_t col = 0; col < csvData[row].size(); col++)
			cout << csvData[row][col];
		cout << endl;
	}
	cout << endl;
}
string& trimSpace(string& s, char trimChar)
{
	while (not s.empty() and s[0] == trimChar)
		s.erase(0, 1);

	while (not s.empty() and s[s.size() - 1] == trimChar)
		s.erase(s.size() - 1, 1);

	return s;
}

#define PROCESS_DOUBLE_QUOTES

void csvread(string& filename, char delim, std::vector< std::vector<std::string> > &csv)
{
	std::ifstream is(filename);
	if (is) {
		std::string line;
		std::vector<std::string> fields;

		while (getline(is, line)) {
			auto cr = line.find('\r');
			if (cr != std::string::npos) line.erase(cr, 1);

			std::string field;
			for (size_t i = 0; i < line.size(); i++) {
#ifdef PROCESS_DOUBLE_QUOTES
				if (line[i] == '"') {
					field += line[i];        // copy 1st "
					for (i++; i < line.size(); i++) {
						field += line[i];
						if (line[i] == '"')     // found 2nd "
							break;
					}
				}
				else
#endif
					if (line[i] != delim) {
						field += line[i];
					}
					else {
						trimSpace(field);
						fields.push_back(field);
						field.clear();
					}
			}
			trimSpace(field);
			fields.push_back(field);
			csv.push_back(fields);
			fields.clear();
		}
		is.close();
	}
	else {
		std::cerr << "cannot open file " << filename << "\n";
	}
}

/*
void csvdump(string& filename, char separator, vector< vector<string> >& csvData){
ifstream is(filename);
if (not is.is_open()){
throw string("Cannot open file '") + filename + "'";
}
string line;
while (getline(is, line)){
auto cr = line.find('\r');
if (cr != string::npos){
line.erase(cr, 1);
}
//cout << line << "\n";

string field;
vector <string> columns;
size_t index = 0;
while (index < line.size()) {
while (line[index] != separator) {
field += line[index];
index++;
}
index++; // skip sep
trimSpace(field);
columns.push_back(field);
//cout << "field =" << field << "\n";
field.clear();
}
csvData.push_back(columns);
columns.clear();
}
is.close();
}*/
