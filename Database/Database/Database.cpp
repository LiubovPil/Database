#include "database.h"

void Database::Add(const Date& date, const string& event) {
	if (!event.empty())
		database[date].insert(event);
}
void Database::Print(ostream& out) {
    for (auto it_date = begin(database); it_date != end(database); ++it_date) {
        for (auto it_events = begin(it_date->second); it_events != end(it_date->second); ++it_events) {
            out << it_date->first << " " << *it_events << endl;
        }
    }
}
int Database::RemoveIf(const function<bool(const Date& date, const string& event)>& p) {
    int Num = 0;

    /*auto it = stable_partition(begin(database), end(database), bind2nd(p, ""));
    if (it != end(database)){
        remove_if(begin(database), it, bind2nd(p, ""));
        Num += count(begin(database), it, bind2nd(p, ""));
    }*/
    for (auto it_date = begin(database); it_date != end(database); ++it_date) {
        auto it_event = stable_partition(begin(it_date->second), end(it_date->second), p);
        /*if (it_event != end(it_date->second)) {
            remove_if(begin(it_date->second), it_event, p);
            Num += count(begin(it_date->second), it_event, p);
        }*/
    }

    /*for (auto it_date = begin(database); it_date != end(database); ++it_date) {
        auto p_mod = bind1st(p, it_date->first);
        auto it_event = stable_partition(begin(it_date->second), end(it_date->second), p_mod);
        if (it_event != end(it_date->second)) {
            remove_if(begin(it_date->second), it_event, p);
            Num += count(begin(it_date->second), it_event, p);
        }
    }*/
    return Num;
}