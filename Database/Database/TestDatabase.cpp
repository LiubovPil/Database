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

		//db_test.Print(cout);

		AssertEqual(db_test.RemoveIf(test_remove_date), 1, "RemoveIfTest 3");

		//db_test.Print(cout);

		AssertEqual(db_test.RemoveIf(test_true), 1, "RemoveIfTest 4");
}
void TestFindIfCommand(){
		Database db_test;

		db_test.Add({ 2017, 01, 04 }, "Wednesday");
		db_test.Add({ 2017, 01, 04 }, "Holiday");
		db_test.Add({ 2017, 01, 04 }, "Wednesday");
		db_test.Add({ 2017, 01, 11 }, "Wednesday");
		db_test.Add({ 2017, 01, 11 }, "Working Day");

		auto test_find_wednesday = [](const Date& date, const string& event) { return event == "Wednesday"; };
		auto test_date_holiday = [](const Date& date, const string& event) { return date < Date{ 2017, 01, 11 } && event == "Holiday"; };
		auto test_no_working_day = [](const Date& date, const string& event) { return event != "Working Day"; };

		vector<pair<Date, string>> map_test_find_wednesday = { {{2017, 01, 04}, "Wednesday"},
													{{2017, 01, 11}, "Wednesday"} };

		vector<pair<Date, string>> map_test_date_holiday = { {{2017, 01, 04}, "Holiday"}};
		
		vector<pair<Date, string>> map_test_no_working_day = { {{2017, 01, 04}, "Holiday"},
													{{2017, 01, 04}, "Wednesday"},
													{{2017, 01, 11}, "Wednesday"} };

		AssertEqual(db_test.FindIf(test_find_wednesday), map_test_find_wednesday, "FindIfTest 1");
		AssertEqual(db_test.FindIf(test_date_holiday), map_test_date_holiday, "FindIfTest 2");
		AssertEqual(db_test.FindIf(test_no_working_day), map_test_no_working_day, "FindIfTest 3");
}