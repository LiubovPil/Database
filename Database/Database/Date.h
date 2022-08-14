#pragma once

#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

class Date {
public:
    Date(int new_year, int new_month, int new_day);

    int GetYear() const;

    int GetMonth() const;

    int GetDay() const;

private:
    int year, month, day;
};

ostream& operator << (ostream& out, const Date& date);

bool operator < (const Date& lhs, const Date& rhs);

bool operator <= (const Date& lhs, const Date& rhs);

bool operator > (const Date& lhs, const Date& rhs);

bool operator >= (const Date& lhs, const Date& rhs);

bool operator == (const Date& lhs, const Date& rhs);

bool operator != (const Date& lhs, const Date& rhs);

void DetermineNextSymbolAndSkip(istringstream& is);

Date ParseDate(istringstream& is);
