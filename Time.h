#ifndef TIME_H
#define TIME_H
class Time
{
    int hours;      // 0 - 23
    int minutes;    // 0 - 59
    int seconds;    // 0 - 59

    static bool validHour(int h) { return h >= 0 && h <= 23; }
    static bool validMinMin(int v) { return v >= 0 && v <= 59; }

    // prints a number with at least two digits (e.g. 5 -> 05)
    static void printTwoDigits(int n)
    {
        if (n < 10) std::cout << '0';
        std::cout << n;
    }

    // Adds 'secs' seconds to the time, wrapping around after 23:59:59
    void addSeconds(long long secs)
    {
        const long long DAY = 24LL * 3600;
        long long total = (long long)hours * 3600 + minutes * 60 + seconds + secs;
        total %= DAY;
        hours = (int)(total / 3600);
        minutes = (int)((total % 3600) / 60);
        seconds = (int)(total % 60);
    }

public:
    Time();
    Time(int h, int m, int s);
    void setHour(int h);
    void setMinute(int m);
    void setSecond(int s);
    void setTime(int h, int m, int s);
    int getHour() const;
    int getMinute() const;
    int getSecond() const;
    void incSec(int = 1);
    void incMin(int = 1);
    void incHour(int = 1);
    void printTwelveHourFormat() const;
    void printTwentyFourHourFormat() const;
};

#endif