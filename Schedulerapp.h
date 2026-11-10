#ifndef SCHEDULERAPP_H
#define SCHEDULERAPP_H

#include <iostream>
#include <limits>
#include "Scheduler.h"

class SchedulerApp
{
    static void clearInput()
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Reads a date; re-asks until it is valid.
    // Date::setDate rejects bad values, so we compare what we get back.
    static Date readDate()
    {
        int d, m, y;
        while (true)
        {
            std::cout << "  Enter date (day month year): ";
            if (!(std::cin >> d >> m >> y)) { clearInput(); continue; }
            Date dt(d, m, y);
            if (dt.getDay() == d && dt.getMonth() == m && dt.getYear() == y)
                return dt;
            std::cout << "  Invalid date, try again." << std::endl;
        }
    }

    static Time readTime()
    {
        int h, m, s = 0;
        while (true)
        {
            std::cout << "  Enter time (hour[0-23] minute): ";
            if (!(std::cin >> h >> m)) { clearInput(); continue; }
            Time t(h, m, s);
            if (t.getHour() == h && t.getMinute() == m)
                return t;
            std::cout << "  Invalid time, try again." << std::endl;
        }
    }

    static void addNewTask(Scheduler& sch)
    {
        Date d = readDate();
        Time t = readTime();
        clearInput();                       // discard leftover newline
        std::cout << "  Enter task message: ";
        String msg;
        msg.input();
        sch.addTask(Task(d, t, msg));
        std::cout << "  Task saved." << std::endl;
    }

public:
    static void startApp()
    {
        Scheduler sch;
        int choice = -1;

        while (choice != 0)
        {
            std::cout << "\n===== SCHEDULER =====\n"
                << "1. Add task\n"
                << "2. Show today's tasks\n"
                << "3. Show tasks of a date\n"
                << "4. Show all tasks\n"
                << "0. Exit\n"
                << "Choice: ";
            if (!(std::cin >> choice)) { clearInput(); choice = -1; continue; }

            switch (choice)
            {
            case 1: addNewTask(sch); break;
            case 2: sch.displayTodaysTasks(); break;
            case 3: sch.displayTask(readDate()); break;
            case 4: sch.displayAllTasks(); break;
            case 0: std::cout << "Goodbye!" << std::endl; break;
            default: std::cout << "Invalid choice." << std::endl;
            }
        }
    }
};

#endif