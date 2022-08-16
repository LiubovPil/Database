#include "Date.h"

Date::Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
        throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
        throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
}
int Date::GetYear() const {
    return year;
};
int Date::GetMonth() const {
    return month;
};
int Date::GetDay() const {
    return day;
};

ostream& operator << (ostream& out, const Date& date) {
    out << setw(4) << setfill('0') << date.GetYear() << "-" <<
        setw(2) << setfill('0') << date.GetMonth() << "-" <<
        setw(2) << setfill('0') << date.GetDay();
    return out;
}

bool operator < (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetYear() < rhs.GetYear();
};
bool operator <= (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() <= rhs.GetDay();
        }
        return lhs.GetMonth() <= rhs.GetMonth();
    }
    return lhs.GetYear() <= rhs.GetYear();
};
bool operator > (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() > rhs.GetDay();
        }
        return lhs.GetMonth() > rhs.GetMonth();
    }
    return lhs.GetYear() > rhs.GetYear();
};
bool operator >= (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() >= rhs.GetDay();
        }
        return lhs.GetMonth() >= rhs.GetMonth();
    }
    return lhs.GetYear() >= rhs.GetYear();
};
bool operator == (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() == rhs.GetDay())
                return true;
        }
    }
    return false;
};
bool operator != (const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            if (lhs.GetDay() == rhs.GetDay())
                return false;
        }
    }
    return true;
};

void DetermineNextSymbolAndSkip(istringstream& is) {
    if (is.peek() != '-') {
        throw logic_error("Invalid date format!" + is.str());
    }
    is.ignore(1);
}

Date ParseDate(istringstream& is) {
    int year = 0, month = 0, day = 0;

    is >> year;
    DetermineNextSymbolAndSkip(is);

    is >> month;
    DetermineNextSymbolAndSkip(is);

    is >> day;

    return Date(year, month, day);
}
