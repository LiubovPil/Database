#include "database.h"

ostream& operator << (ostream& out, const pair<Date, string>& date_event) {
    out << date_event.first << " " << date_event.second;
    return out;
}
bool operator ==(const vector<pair<Date, string>>& lhs_dates_events, const vector<pair<Date, string>>& rhs_dates_events) {
    if (lhs_dates_events.size() == rhs_dates_events.size()) {
        for (size_t i = 0; i < lhs_dates_events.size(); ++i) {
            if (lhs_dates_events[i] != rhs_dates_events[i])
                return false;
        }
        return true;
    }
    return false;
}
bool operator ==(const pair<Date, string>& lhs_date_event, const pair<Date, string>& rhs_date_event) {
    if (lhs_date_event.first != rhs_date_event.first ||
        lhs_date_event.second != rhs_date_event.second)
        return false;
    else
        return true;
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
pair<Date, string> Database::Last(const Date& date) const {
    auto it = database_sorted.lower_bound(date);
    if (it == begin(database_sorted)) {
        throw invalid_argument("No entries");
    }
    --it;
    return make_pair(it->first, *rbegin(it->second));
}