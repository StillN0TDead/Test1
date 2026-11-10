#include <iostream>
#include <ctime>
#include "Task.h"
#include "Date.h"
#include"Time.h"
#include"String.h"

using namespace std;

class Scheduler
{
    Task* taskList;
    int noOfTasks;
    int capacity;

    // Checks whether two dates are equal
    static bool sameDate(const Date& d1, const Date& d2)
    {
        return d1.getDay() == d2.getDay() &&
            d1.getMonth() == d2.getMonth() &&
            d1.getYear() == d2.getYear();
    }

public:

    // Default constructor
    Scheduler()
    {
        taskList = nullptr;
        noOfTasks = 0;
        capacity = 0;
    }

    // Copy constructor (deep copy)
    Scheduler(const Scheduler& obj)
    {
        noOfTasks = obj.noOfTasks;
        capacity = obj.capacity;

        if (capacity == 0)
            taskList = nullptr;
        else
        {
            taskList = new Task[capacity];

            for (int i = 0; i < noOfTasks; i++)
                taskList[i] = obj.taskList[i];
        }
    }

    // Assignment operator (deep copy)
    Scheduler& operator=(const Scheduler& obj)
    {
        if (this == &obj)
            return *this;

        Task* newList = nullptr;

        if (obj.capacity > 0)
        {
            newList = new Task[obj.capacity];

            for (int i = 0; i < obj.noOfTasks; i++)
                newList[i] = obj.taskList[i];
        }

        delete[] taskList;

        taskList = newList;
        noOfTasks = obj.noOfTasks;
        capacity = obj.capacity;

        return *this;
    }

    // Destructor
    ~Scheduler()
    {
        delete[] taskList;
        taskList = nullptr;
    }

    // Resize dynamic array
    void reSize(int newCapacity)
    {
        if (newCapacity < noOfTasks || newCapacity < 0)
            return;

        if (newCapacity == capacity)
            return;

        if (newCapacity == 0)
        {
            delete[] taskList;
            taskList = nullptr;
            capacity = 0;
            return;
        }

        Task* newList = new Task[newCapacity];

        for (int i = 0; i < noOfTasks; i++)
            newList[i] = taskList[i];

        delete[] taskList;

        taskList = newList;
        capacity = newCapacity;
    }

    // Add a task
    void addTask(const Task& t)
    {
        if (noOfTasks == capacity)
        {
            if (capacity == 0)
                reSize(2);
            else
                reSize(capacity * 2);
        }

        taskList[noOfTasks] = t;
        noOfTasks++;
    }

    // Display tasks of a particular date
    void displayTask(const Date& d) const
    {
        bool found = false;

        for (int i = 0; i < noOfTasks; i++)
        {
            if (sameDate(taskList[i].getDate(), d))
            {
                taskList[i].display();
                found = true;
            }
        }

        if (!found)
            cout << "No tasks found for this date.\n";
    }

    // Display today's tasks
    void displayTodaysTasks() const
    {
        time_t t = time(0);
        tm curTime = *localtime(&t);

        Date today(
            curTime.tm_mday,
            curTime.tm_mon + 1,
            curTime.tm_year + 1900
        );

        cout << "\nToday's Tasks: ";
        today.printFormat1();
        cout << "\n\n";

        displayTask(today);
    }

    // Display all saved tasks
    void displayAllTasks() const
    {
        if (noOfTasks == 0)
        {
            cout << "No tasks saved.\n";
            return;
        }

        for (int i = 0; i < noOfTasks; i++)
        {
            cout << "\nTask " << i + 1 << "\n";
            taskList[i].display();
        }
    }

    // Number of saved tasks
    int getNoOfTasks() const
    {
        return noOfTasks;
    }
};