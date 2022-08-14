#pragma once

#include "Date.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);

	void Print(ostream& out);

	int RemoveIf(const function<bool(const Date& date, const string& event)>& predicate);

	void FindIf();

	void Last();

private:
	map<Date, set<string>> database;
};
