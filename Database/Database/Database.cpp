#include "database.h"

ostream& operator << (ostream& out, const pair<Date, string>& date_event) {
    out << date_event.first << " " << date_event.second;
    return out;
}
bool operator ==(const vector<pair<Date, string>>& lhs_dates_events, const vector<pair<Date, string>>& rhs_dates_events) {
    if (lhs_dates_events.size() == rhs_dates_events.size()) {
        for (size_t i = 0; i < lhs_dates_events.size(); ++i) {
            if (lhs_dates_events[i].first != rhs_dates_events[i].first ||
                lhs_dates_events[i].second != rhs_dates_events[i].second)
                return false;
        }
        return true;
    }
    return false;
}

void Database::Add(const Date& date, const string& event) {
    if (!event.empty())
    {
        auto is_increase = database[date].insert(event);
        
        if(is_increase.second)
            database_sorted[date].push_back(event);
    }
}
void Database::Print(ostream& out) const {
    for (auto it_date = begin(database); it_date != end(database); ++it_date) {
        for (auto it_events = begin(it_date->second); it_events != end(it_date->second); ++it_events) {
            out << it_date->first << " " << *it_events << endl;
        }
    }
}
string Database::Last(const Date& date) const {
    stringstream sout;

    auto it = database_sorted.lower_bound(date);
    if (it == begin(database_sorted)) {
        //sout << "No entries";
        //return sout.str();
        throw invalid_argument("No entries");
    }
    --it;
    sout << it->first
        << " " << *rbegin(it->second);
    return sout.str();
}