#include <iostream>
#include"Time.h"
using namespace std;

    Time::Time() : hours(0), minutes(0), seconds(0) {}

    Time::Time(int h, int m, int s) : hours(0), minutes(0), seconds(0)
    {
        setTime(h, m, s);
    }

   
    void Time::setHour(int h)
    {
        if (!validHour(h)) { std::cout << "Invalid hour (0-23). Hour not changed.\n"; return; }
        hours = h;
    }

    void Time::setMinute(int m)
    {
        if (!validMinMin(m)) { std::cout << "Invalid minute (0-59). Minute not changed.\n"; return; }
        minutes = m;
    }

    void Time::setSecond(int s)
    {
        if (!validMinMin(s)) { std::cout << "Invalid second (0-59). Second not changed.\n"; return; }
        seconds = s;
    }

    void Time::setTime(int h, int m, int s)
    {
        if (!validHour(h) || !validMinMin(m) || !validMinMin(s))
        {
            std::cout << "Invalid time. Time not changed.\n";
            return;
        }
        hours = h;
        minutes = m;
        seconds = s;
    }

    int Time::getHour() const { return hours; }
    int Time::getMinute() const { return minutes; }
    int Time::getSecond() const { return seconds; }
    void Time::incSec(int n)
    {
        if (n < 0) return;
        addSeconds(n);
    }

    void Time::incMin(int n)
    {
        if (n < 0) return;
        addSeconds((long long)n * 60);
    }

    void Time::incHour(int n)
    {
        if (n < 0) return;
        addSeconds((long long)n * 3600);
    }

   
    void Time::printTwelveHourFormat() const
    {
        int h = hours % 12;
        if (h == 0) h = 12;
        printTwoDigits(h);
        std::cout << ':';
        printTwoDigits(minutes);
        std::cout << ':';
        printTwoDigits(seconds);
        std::cout << (hours < 12 ? " AM" : " PM") << '\n';
    }

    void Time::printTwentyFourHourFormat() const
    {
        printTwoDigits(hours);
        std::cout << ':';
        printTwoDigits(minutes);
        std::cout << ':';
        printTwoDigits(seconds);
        std::cout << '\n';
    }