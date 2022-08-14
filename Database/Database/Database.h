#pragma once

#include "Date.h"

#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);

	void FindIf();

	int RemoveIf();

	void Last();

	ostream& Print(ostream& out);

private:
	map<Date, set<string>> database;
};
