#ifndef DATE_H
#define DATE_H
#include "String.h"

static const char* monthNames[13] = {
    "", "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};


class Date
{
    int day;
    int month;
    int year;
    static const int daysInMonth[13];

    bool isLeapYear() const { return isLeap(year); }

    static bool isLeap(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static int daysIn(int m, int y)
    {
        if (m == 2 && isLeap(y)) return 29;
        return daysInMonth[m];
    }

    static bool validYear(int y) { return y >= 1500 && y <= 3000; }
    static bool validMonth(int m) { return m >= 1 && m <= 12; }

public:
    Date();

    Date(int d, int m, int y);

    void setDate(int d, int m, int y);
    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);
    int getDay() const;
    int getMonth() const;
    int getYear() const;
    void incDay(int = 1);
    void incMonth(int = 1);
    void incYear(int = 1);
    String getDateInFormat1() const;
    String getDateInFormat2() const;
    String getDateInFormat3() const;
    void printFormat1() const;
    void printFormat2() const;
    void printFormat3() const;
};

const int Date::daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
#endif