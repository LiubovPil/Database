#include "Database.h"
#include "Date.h"
#include "test_runner.h"

#include <sstream>
using namespace std;

void TestLastCommand() {
		Database db_test;

		db_test.Add({ 2017, 01, 01 }, "Sunday");
		db_test.Add({ 2017, 01, 01 }, "Holiday");

		AssertEqual(db_test.Last({ 2017, 01, 10 }), "2017-01-01 Holiday", "LastTest 1");

		db_test.Add({ 2017, 01, 04 }, "Holiday");
		db_test.Add({ 2017, 01, 04 }, "Wednesday");
		db_test.Add({ 2017, 01, 04 }, "Holiday");
		db_test.Add({ 2017, 01, 11 }, "Wednesday");
		db_test.Add({ 2017, 01, 11 }, "Working Day");

		AssertEqual(db_test.Last({ 2017, 01, 05 }), "2017-01-04 Wednesday", "LastTest 2");
		AssertEqual(db_test.Last({ 2017, 01, 12 }), "2017-01-11 Working Day", "LastTest 3");
		AssertEqual(db_test.Last({ 2017, 01, 02 }), "2017-01-01 Holiday", "LastTest 4");
		
		//AssertEqual(db_test.Last({ 2016, 01, 01 }), "No entries", "LastTest 5");
}
void TestRemoveIfCommand(){
		Database db_test;

		db_test.Add({ 2017, 01, 04 }, "Wednesday");
		db_test.Add({ 2017, 01, 04 }, "Holiday");
		db_test.Add({ 2017, 01, 04 }, "Wednesday");
		db_test.Add({ 2017, 01, 11 }, "Holiday");
		db_test.Add({ 2017, 01, 11 }, "Wednesday");
		db_test.Add({ 2017, 01, 11 }, "Working Day");

		auto test_remove_holiday = [](const Date& date, const string& event) { return date == Date{ 2017, 01, 11 } && event == "Holiday"; };
		auto test_remove_wednesday = [](const Date& date, const string& event) { return event == "Wednesday"; };
		auto test_remove_date = [](const Date& date, const string& event) { return date == Date{ 2017, 01, 11 }; };
		auto test_true = [](const Date& date, const string& event) { return true; };

		AssertEqual(db_test.RemoveIf(test_remove_holiday), 1, "RemoveIfTest 1");
		AssertEqual(db_test.RemoveIf(test_remove_wednesday), 2, "RemoveIfTest 2");

		db_test.Print(cout);

		AssertEqual(db_test.RemoveIf(test_remove_date), 1, "RemoveIfTest 3");
		AssertEqual(db_test.RemoveIf(test_true), 1, "RemoveIfTest 4");

		db_test.Print(cout);
}