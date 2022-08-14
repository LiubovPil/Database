#include "database.h"

void Database::Add(const Date& date, const string& event) {
	if (!event.empty())
		database[date].insert(event);
}