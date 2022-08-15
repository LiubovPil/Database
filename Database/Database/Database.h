#pragma once

#include "Date.h"
#include "Node.h"

#include <functional>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

class Database {
public:
	void Add(const Date& date, const string& event);

	void Print(ostream& out) const;

    template<class Predicate> 
    int RemoveIf(Predicate predicate_){
        int Num = 0;

        for (auto it_date = database_sorted.begin(); it_date != database_sorted.end(); ++it_date) {
            auto predicate_mod = bind(predicate_, it_date->first, placeholders::_1);
            auto it_events_sorted = stable_partition(begin(it_date->second), end(it_date->second), predicate_mod);
            //try auto it_events_sorted = stable_partition(rbegin(it_date->second), rend(it_date->second), predicate_mod);

            if (it_events_sorted != begin(it_date->second)) {
                Num += it_events_sorted - begin(it_date->second);
                for (auto it = begin(it_date->second); it != it_events_sorted; ++it) {
                    database[it_date->first].erase(*it); 
                } 
                (it_date->second).erase(begin(it_date->second), it_events_sorted);
                //try instead for database[it_date->first] = set<string>(begin(it_date->second), end(it_date->second));
            }

            if (database_sorted.count(it_date->first) == 0) {
                database_sorted.erase(it_date->first);
                database.erase(it_date->first);
            }
        }
        return Num;
    }

	void FindIf();

	string Last(const Date& date) const;

private:
	map<Date, set<string>> database;
	map<Date, vector<string>> database_sorted;
};

void TestLastCommand();
void TestRemoveIfCommand();
