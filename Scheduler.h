#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "Task.h"

class Scheduler
{
    Task* taskList;     // dynamic array of Task objects
    int noOfTasks;      // tasks currently stored
    int capacity;       // size of the array pointed to by taskList

    void copyFrom(const Scheduler& other);

public:
    Scheduler();
    Scheduler(const Scheduler& other);              // deep copy
    Scheduler& operator=(const Scheduler& other);   // deep copy
    ~Scheduler();

    void addTask(const Task& t);

    // Default argument Date(1,1,1500) is a sentinel meaning "use today".
    void displayTask(const Date& d = Date(1, 1, 1500)) const;
    void displayTodaysTasks() const;
    void displayAllTasks() const;

    void reSize(int newCapacity);   // resizes the array whenever it gets full
    int getNoOfTasks() const;
};

#endif