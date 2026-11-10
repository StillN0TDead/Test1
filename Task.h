#ifndef TASK_H
#define TASK_H

#include <iostream>
#include "String.h"
#include "Date.h"
#include "Time.h"

// A Task is composed of a Date, a Time and a String (composition).
// String has its own copy constructor / operator= / destructor that do deep
// copies, so the compiler-generated versions for Task are correct and no
// user-defined copy constructor or destructor is needed here.
class Task
{
    Date taskDate;
    Time taskTime;
    String taskMsg;

public:
    Task() {}

    Task(const Date& d, const Time& t, const String& m)
        : taskDate(d), taskTime(t), taskMsg(m)
    {
    }

    void setTask(const Date& d, const Time& t, const String& m)
    {
        taskDate = d;
        taskTime = t;
        taskMsg = m;      // safe: String::operator= does a deep copy
    }

    void updateDate(const Date& nd) { taskDate = nd; }
    void updateTime(const Time& nt) { taskTime = nt; }
    void updateMessage(const String& m) { taskMsg = m; }

    Date getDate() const { return taskDate; }
    Time getTime() const { return taskTime; }
    String getMessage() const { return taskMsg; }

    void display() const
    {
        taskDate.printFormat1();
        std::cout.fill(' ');          // printFormat1 may leave fill as '0'
        std::cout << "  ";
        taskTime.printTwelveHourFormat();
        std::cout << "  -  ";
        taskMsg.display();
        std::cout << std::endl;
    }
};

#endif