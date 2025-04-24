#include<iostream>
using namespace std;

void printmenu()
{
    cout << "---Smart Parking Lot System---\n";
    cout << "1.Park Vehicle\n";
    cout << "2.Remove Vehicle\n";
    cout << "3.View Available Slots\n";
    cout << "4.View Parked Vehicles\n";
    cout << "5.Search Vehicle\n";
    cout << "6.Exit\n";
}

int main()
{
    int choice;

    do
    {
        printmenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if(choice==1)
        {
            cout << "Let`s find a safe and cozy spot for parking your vehicle\n";
        }
        else if(choice==2)
        {
            cout << "Now, let`s remove the vehicle from the parking lot!\n";
        }
        else if(choice == 3)
        {
            cout << "Let me show you which slots are still open!\n";
        }
        else if(choice == 4)
        {
            cout << "Here we go! These are all the vehicles that are currently parked.\n";
        }
        else if(choice == 5)
        {
            cout << "Kindly wait! We`re searching for that vehicle for you\n";
        }
        else if(choice == 6)
        {
            cout << "Thanks alot for using our parking system. Hope to see you again. Have an amazing day!\n";
        }
        else
        {
            cout << "Oops! The option doesn`t seem right. Pick a number between 1 and 6.\n";
        }

    } while (choice!=6);

    return 0;
    
}