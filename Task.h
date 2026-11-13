#include"Time.h"
#include"String.h"
#include"Date.h"

class Task
{
    Date taskDate;
    Time taskTime;
    String taskMsg;

public:
    Task()
    {
    }

    Task(const Date& d, const Time& t, const String& m)
        : taskDate(d), taskTime(t), taskMsg(m)
    {
    }

    void setTask(const Date& d, const Time& t, const String& m)
    {
        taskDate = d;
        taskTime = t;
        taskMsg = m;
    }

    void updateDate(const Date& nd)
    {
        taskDate = nd;
    }

    void updateTime(const Time& nt)
    {
        taskTime = nt;
    }

    void updateMessage(const String& m)
    {
        taskMsg = m;
    }

    Date getDate() const
    {
        return taskDate;
    }

    Time getTime() const
    {
        return taskTime;
    }

    String getMessage() const
    {
        return taskMsg;
    }

    void display() const
    {
        cout << "Date: ";
        taskDate.printFormat1();

        cout << "\nTime: ";
        taskTime.printTwentyFourHourFormat();

        cout << "\nTask: ";
        taskMsg.display();

        cout << "\n-----------------------------\n";
    }
};