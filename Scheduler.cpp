//#include <iostream>
//#include <ctime>
//#include "Scheduler.h"
//
//using namespace std;
//
//// ---------- helpers (file-local) ----------
//static Date getSystemDate()
//{
//    time_t t = time(0);
//    tm curTime = *localtime(&t);
//    // tm_mday (not tm_day), tm_mon is 0-based, tm_year counts from 1900
//    return Date(curTime.tm_mday, curTime.tm_mon + 1, curTime.tm_year + 1900);
//}
//
//static bool sameDate(const Date& a, const Date& b)
//{
//    return a.getDay() == b.getDay()
//        && a.getMonth() == b.getMonth()
//        && a.getYear() == b.getYear();
//}
//
//// ---------- Scheduler ----------
//Scheduler::Scheduler()
//{
//    capacity = 0;
//    noOfTasks = 0;
//    taskList = nullptr;
//}
//
//void Scheduler::copyFrom(const Scheduler& other)
//{
//    capacity = other.capacity;
//    noOfTasks = other.noOfTasks;
//    taskList = (capacity > 0) ? new Task[capacity] : nullptr;
//    for (int i = 0; i < noOfTasks; i++)
//        taskList[i] = other.taskList[i];
//}
//
//Scheduler::Scheduler(const Scheduler& other)
//{
//    copyFrom(other);
//}
//
//Scheduler& Scheduler::operator=(const Scheduler& other)
//{
//    if (this != &other)
//    {
//        delete[] taskList;
//        copyFrom(other);
//    }
//    return *this;
//}
//
//Scheduler::~Scheduler()
//{
//    delete[] taskList;
//    taskList = nullptr;
//}
//
//void Scheduler::reSize(int newCapacity)
//{
//    if (newCapacity < noOfTasks)    // never lose stored tasks
//        newCapacity = noOfTasks;
//
//    Task* newList = (newCapacity > 0) ? new Task[newCapacity] : nullptr;
//    for (int i = 0; i < noOfTasks; i++)
//        newList[i] = taskList[i];
//
//    delete[] taskList;
//    taskList = newList;
//    capacity = newCapacity;
//}
//
//void Scheduler::addTask(const Task& t)
//{
//    if (noOfTasks == capacity)
//        reSize(capacity == 0 ? 2 : capacity * 2);
//
//    taskList[noOfTasks] = t;
//    noOfTasks++;
//}
//
//void Scheduler::displayTask(const Date& d) const
//{
//    Date target = d;
//    if (sameDate(d, Date(1, 1, 1500)))      // sentinel -> today
//        target = getSystemDate();
//
//    cout << "Tasks on ";
//    target.printFormat1();
//    cout.fill(' ');
//    cout << ":" << endl;
//
//    bool found = false;
//    for (int i = 0; i < noOfTasks; i++)
//    {
//        if (sameDate(taskList[i].getDate(), target))
//        {
//            cout << "  ";
//            taskList[i].display();
//            found = true;
//        }
//    }
//    if (!found)
//        cout << "  No tasks found." << endl;
//}
//
//void Scheduler::displayTodaysTasks() const
//{
//    displayTask(getSystemDate());
//}
//
//void Scheduler::displayAllTasks() const
//{
//    if (noOfTasks == 0)
//    {
//        cout << "No tasks saved." << endl;
//        return;
//    }
//    for (int i = 0; i < noOfTasks; i++)
//    {
//        cout << (i + 1) << ". ";
//        taskList[i].display();
//    }
//}
//
//int Scheduler::getNoOfTasks() const
//{
//    return noOfTasks;
//}