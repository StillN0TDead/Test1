#include<iostream>
#include"Date.h"
using namespace std;

Date::Date() : day(1), month(1), year(2000) {}

Date::Date(int d, int m, int y) : day(1), month(1), year(2000)
{
    setDate(d, m, y);
}

void Date::setDate(int d, int m, int y)
{
    if (!validYear(y)) { std::cout << "Invalid year (1500-3000). Date not changed.\n"; return; }
    if (!validMonth(m)) { std::cout << "Invalid month (1-12). Date not changed.\n"; return; }
    if (d < 1 || d > daysIn(m, y)) { std::cout << "Invalid day for this month. Date not changed.\n"; return; }
    day = d;
    month = m;
    year = y;
}

void Date::setDay(int d)
{
    if (d < 1 || d > daysIn(month, year))
    {
        std::cout << "Invalid day for this month. Day not changed.\n";
        return;
    }
    day = d;
}

void Date::setMonth(int m)
{
    if (!validMonth(m)) { std::cout << "Invalid month (1-12). Month not changed.\n"; return; }
    if (day > daysIn(m, year))
    {
        std::cout << "Current day does not exist in that month. Month not changed.\n";
        return;
    }
    month = m;
}

void Date::setYear(int y)
{
    if (!validYear(y)) { std::cout << "Invalid year (1500-3000). Year not changed.\n"; return; }
    if (day > daysIn(month, y))   // 29-Feb moved to a non-leap year
    {
        std::cout << "Current date does not exist in that year. Year not changed.\n";
        return;
    }
    year = y;
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

void Date::incDay(int n)
{
    if (n < 0) return;
    int d = day, m = month, y = year;
    while (n > 0)
    {
        d++;
        if (d > daysIn(m, y))
        {
            d = 1;
            m++;
            if (m > 12) { m = 1; y++; }
        }
        n--;
    }
    if (!validYear(y)) { std::cout << "Year would exceed 3000. Date not changed.\n"; return; }
    day = d; month = m; year = y;
}

void Date::incMonth(int n)
{
    if (n < 0) return;
    int total = (month - 1) + n;
    int m = total % 12 + 1;
    int y = year + total / 12;
    if (!validYear(y)) { std::cout << "Year would exceed 3000. Date not changed.\n"; return; }
    month = m;
    year = y;
    if (day > daysIn(month, year)) day = daysIn(month, year);   // e.g. 31-Jan + 1 month
}

void Date::incYear(int n)
{
    if (n < 0) return;
    int y = year + n;
    if (!validYear(y)) { std::cout << "Year would exceed 3000. Date not changed.\n"; return; }
    year = y;
    if (day > daysIn(month, year)) day = daysIn(month, year);   // 29-Feb in non-leap year
}

// 12/25/2012
String Date::getDateInFormat1() const
{
    String r, t;
    r.setNumber(month);
    r.concatEqual("/");
    t.setNumber(day);
    r.concatEqual(t);
    r.concatEqual("/");
    t.setNumber(year);
    r.concatEqual(t);
    return r;
}

// December 25, 2012
String Date::getDateInFormat2() const
{
    String r(monthNames[month]), t;
    r.concatEqual(" ");
    t.setNumber(day);
    r.concatEqual(t);
    r.concatEqual(", ");
    t.setNumber(year);
    r.concatEqual(t);
    return r;
}

// 25-Dec-2012
String Date::getDateInFormat3() const
{
    String r, t;
    r.setNumber(day);
    r.concatEqual("-");
    String name(monthNames[month]);
    r.concatEqual(name.left(3));
    r.concatEqual("-");
    t.setNumber(year);
    r.concatEqual(t);
    return r;
}

void Date::printFormat1() const { getDateInFormat1().display(); std::cout << '\n'; }
void Date::printFormat2() const { getDateInFormat2().display(); std::cout << '\n'; }
void Date::printFormat3() const { getDateInFormat3().display(); std::cout << '\n'; }
