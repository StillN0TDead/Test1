#include <iostream>
#include <ctime>
#include"Scheduler.h"
#include"Task.h"
using namespace std;

class SchedulerApp
{
public:

    static void startApp()
    {
        Scheduler scheduler;

        int choice;

        do
        {
            cout << "\n========== SCHEDULER ==========\n";
            cout << "1. Add New Task\n";
            cout << "2. Display Today's Tasks\n";
            cout << "3. Display Tasks By Date\n";
            cout << "4. Display All Tasks\n";
            cout << "5. Exit\n";

            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                int d, m, y;
                int h, min, s;

                cout << "\nEnter Task Date (DD MM YYYY): ";
                cin >> d >> m >> y;

                cout << "Enter Task Time (HH MM SS): ";
                cin >> h >> min >> s;

                Date date(d, m, y);
                Time taskTime(h, min, s);

                cin.ignore(10000, '\n');

                char message[1000];

                cout << "Enter Task Message: ";
                cin.getline(message, 1000);

                String taskMessage(message);

                Task newTask(date, taskTime, taskMessage);

                scheduler.addTask(newTask);

                cout << "\nTask added successfully!\n";

                break;
            }

            case 2:
            {
                scheduler.displayTodaysTasks();
                break;
            }

            case 3:
            {
                int d, m, y;

                cout << "\nEnter Date (DD MM YYYY): ";
                cin >> d >> m >> y;

                Date date(d, m, y);

                scheduler.displayTask(date);

                break;
            }

            case 4:
            {
                scheduler.displayAllTasks();
                break;
            }

            case 5:
            {
                cout << "\nExiting Scheduler...\n";
                break;
            }

            default:
            {
                cout << "\nInvalid choice! Try again.\n";
            }

            }

        } while (choice != 5);
    }
};