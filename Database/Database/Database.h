#pragma once

#include "Date.h"
#include "Node.h"

#include <functional>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <vector>
#include <set>

using namespace std;

ostream& operator << (ostream& out, const pair<Date, string>& date_event);

bool operator ==(const vector<pair<Date, string>>& rhs_date_event, const vector<pair<Date, string>>& lhs_date_event);

bool operator ==(const pair<Date, string>& lhs_date_event, const pair<Date, string>& rhs_date_event);

class Database {
public:
	void Add(const Date& date, const string& event);

	void Print(ostream& out) const;

    template<class Predicate> 
    int RemoveIf(Predicate predicate_){
        int Num = 0;

        for (auto& item: database_sorted) {
            auto predicate_mod = bind(predicate_, item.first, placeholders::_1);
            auto it_events_sorted = stable_partition(begin(item.second), end(item.second), predicate_mod);

            if (it_events_sorted != begin(item.second)) {
                Num += it_events_sorted - begin(item.second);
                for (auto it = begin(item.second); it != it_events_sorted; ++it) {
                    database[item.first].erase(*it);
                } 
                (item.second).erase(begin(item.second), it_events_sorted);
            }
        }
        for (auto it = database_sorted.begin(); it != database_sorted.end();) {
            if (database_sorted[(it->first)].size() == 0) {
                database.erase(it->first);
                database_sorted.erase(it++);
            }
            else
                ++it;
        }
        return Num;
    }

    template<class Predicate>
    vector<pair<Date, string>> FindIf(Predicate predicate_) {
        vector<pair<Date, string>> dates_events;
        for (auto it_date = begin(database); it_date != end(database); ++it_date) {
            auto predicate_mod = bind(predicate_, it_date->first, placeholders::_1);

            auto it_event = begin(it_date->second);
            while (it_event != end(it_date->second)) {
                it_event = find_if(it_event, end(it_date->second), predicate_mod);
                
                if (it_event != end(it_date->second)) {
                    dates_events.push_back({ it_date->first, *it_event });
                    ++it_event;
                }
            }
        }
        return dates_events;
    }

    pair<Date, string> Last(const Date& date) const;

private:
	map<Date, set<string>> database;
	map<Date, vector<string>> database_sorted;
};

void TestLastCommand();
void TestRemoveIfCommand();
void TestFindIfCommand();
