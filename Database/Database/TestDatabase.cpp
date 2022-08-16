#include "Database.h"
#include "Date.h"
#include "test_runner.h"

using namespace std;

void TestLastCommand() {

		auto start = chrono::high_resolution_clock::now();

		Database db_test;

		db_test.Add({ 2017, 01, 01 }, "Sunday");
		db_test.Add({ 2017, 01, 01 }, "Holiday");

		pair<Date, string> test_pair_1 = make_pair(Date{ 2017, 01, 01 }, "Holiday");

		AssertEqual(db_test.Last({ 2017, 01, 10 }), test_pair_1, "LastTest 1");

		db_test.Add({ 2017, 01, 04 }, "Holiday");
		db_test.Add({ 2017, 01, 04 }, "Wednesday");
		db_test.Add({ 2017, 01, 04 }, "Holiday");
		db_test.Add({ 2017, 01, 11 }, "Wednesday");
		db_test.Add({ 2017, 01, 11 }, "Working Day");

		pair<Date, string> test_pair_2 = make_pair(Date{ 2017, 01, 04 }, "Wednesday");
		pair<Date, string> test_pair_3 = make_pair(Date{ 2017, 01, 11 }, "Working Day");

		AssertEqual(db_test.Last({ 2017, 01, 05 }), test_pair_2, "LastTest 2");
		AssertEqual(db_test.Last({ 2017, 01, 12 }), test_pair_3, "LastTest 3");
		AssertEqual(db_test.Last({ 2017, 01, 02 }), test_pair_1, "LastTest 4");
		
		auto test_remove_dates_holiday = [](const Date& date, const string& event) { return date > Date{ 2017, 01, 03 } || event == "Holiday"; };
		db_test.RemoveIf(test_remove_dates_holiday);

		pair<Date, string> test_pair_5 = make_pair(Date{ 2017, 01, 01 }, "Sunday");

		AssertEqual(db_test.Last({ 2017, 01, 02 }), test_pair_5, "LastTest 5");

		auto end = chrono::high_resolution_clock::now();

		chrono::duration<float> duration = end - start;
		cout << "Duration = " << duration.count() << "sec" << endl;
}
void TestRemoveIfCommand(){

		auto start = chrono::high_resolution_clock::now();

		Database db_test;

		auto test_remove_holiday = [](const Date& date, const string& event) { return date == Date{ 2017, 01, 11 } && event == "Holiday"; };
		auto test_remove_wednesday = [](const Date& date, const string& event) { return event == "Wednesday"; };
		auto test_remove_date = [](const Date& date, const string& event) { return date == Date{ 2017, 01, 11 }; };
		auto test_true = [](const Date& date, const string& event) { return true; };

		db_test.Add({ 2017, 01, 04 }, "Monday");
		AssertEqual(db_test.RemoveIf(test_true), 1, "RemoveIfTest 1");

		db_test.Add({ 2017, 01, 04 }, "Wednesday");
		db_test.Add({ 2017, 01, 04 }, "Holiday");
		db_test.Add({ 2017, 01, 04 }, "Wednesday");
		db_test.Add({ 2017, 01, 11 }, "Holiday");
		db_test.Add({ 2017, 01, 11 }, "Wednesday");
		db_test.Add({ 2017, 01, 11 }, "Working Day");

		AssertEqual(db_test.RemoveIf(test_remove_holiday), 1, "RemoveIfTest 2");
		AssertEqual(db_test.RemoveIf(test_remove_wednesday), 2, "RemoveIfTest 3");

		AssertEqual(db_test.RemoveIf(test_remove_date), 1, "RemoveIfTest 4");

		AssertEqual(db_test.RemoveIf(test_true), 1, "RemoveIfTest 5");

		auto end = chrono::high_resolution_clock::now();

		chrono::duration<float> duration = end - start;
		cout << "Duration = " << duration.count() << "sec" << endl;
}
void TestFindIfCommand(){

		auto start = chrono::high_resolution_clock::now();

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

		auto end = chrono::high_resolution_clock::now();

		chrono::duration<float> duration = end - start;
		cout << "Duration = " << duration.count() << "sec" << endl;
}