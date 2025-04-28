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
    const int carmaxsize = 40;
    const int bikemaxsize = 30;
    const int vanmaxsize = 20;
    const int truckmaxsize = 10;
    string carplates[carmaxsize];
    string bikeplates[bikemaxsize];
    string vanplates[vanmaxsize];
    string truckplates[truckmaxsize];
    int carsize = 0;
    int bikesize = 0;
    int vansize = 0;
    int trucksize = 0;
    
    string vehicletype, platenum;
    bool found = false;
	printmenu();
int choice;
do {
cout << "Enter choice:(1-6):";
cin >> choice;
if (choice <1||choice>6)
{
cout << "Invalid option!Please enter choice between 1 and 6.\n";
}
switch (choice)
{
case 1:
{
break;
}
case 2:
{
    cout << "Enter vehicle type you want to remove: ";
            cin >> vehicletype;
            
            if (vehicletype == "car")
            {
                cout << "Enter the " << vehicletype << " plate number you want to remove: ";
                cin >> platenum;
                
                for (int i = 0; i < carsize; i++)
                {
                    if (carplates[i] == platenum)
                    {
                        for (int j = i; j < carsize - 1; j++)
                        {
                            carplates[j] = carplates[j + 1];
                        }
                        carsize--;
                        found = true;
                        break;
                    }
                }
                
                if (found)
                {
                    cout << "Your " << vehicletype << " with " << platenum << " is successfully removed! Thanks for parking\n";
                }
                else
                {
                    cout << "Vehicle with plate " << platenum << " not found!\n";
                }
            }
            else if (vehicletype == "bike")
            {
                cout << "Enter the " << vehicletype << " plate number you want to remove: ";
                cin >> platenum;
                
                
                for (int i = 0; i < bikesize; i++)
                {
                    if (bikeplates[i] == platenum)
                    {
                        for (int j = i; j < bikesize - 1; j++)
                        {
                            bikeplates[j] = bikeplates[j + 1];
                        }
                        bikesize--;
                        found = true;
                        break;
                    }
                }
                
                if (found)
                {
                    cout << "Your " << vehicletype << " with " << platenum << " is successfully removed! Thanks for parking\n";
                }
                else
                {
                    cout << "Vehicle with plate " << platenum << " not found!\n";
                }
            }
            else if (vehicletype == "truck")
            {
                cout << "Enter the " << vehicletype << " plate number you want to remove: ";
                cin >> platenum;
                
                
                for (int i = 0; i < trucksize; i++)
                {
                    if (truckplates[i] == platenum)
                    {
                        for (int j = i; j < trucksize - 1; j++)
                        {
                            truckplates[j] = truckplates[j + 1];
                        }
                        trucksize--;
                        found = true;
                        break;
                    }
                }
                
                if (found)
                {
                    cout << "Your " << vehicletype << " with " << platenum << " is successfully removed! Thanks for parking\n";
                }
                else
                {
                    cout << "Vehicle with plate " << platenum << " not found!\n";
                }
            }
            else if (vehicletype == "van")
            {
                cout << "Enter the " << vehicletype << " plate number you want to remove: ";
                cin >> platenum;
                
                
                for (int i = 0; i < vansize; i++)
                {
                    if (vanplates[i] == platenum)
                    {
                        for (int j = i; j < vansize - 1; j++)
                        {
                            vanplates[j] = vanplates[j + 1];
                        }
                        vansize--;
                        found = true;
                        break;
                    }
                }
                
                if (found)
                {
                    cout << "Your " << vehicletype << " with " << platenum << " is successfully removed! Thanks for parking\n";
                }
                else
                {
                    cout << "Vehicle with plate " << platenum << " not found!\n";
                }
            }
            else
            {
                cout << "Invalid input! Please enter correct vehicle type!\n";
            }
break;
}
case 3:
{
break;
}
case 4:
{
break;
}
case 5:
{
break;
}
case 6:
{
break;
}
default:
{
break;
}
}
}
while (choice != 6);
system("pause");
    return 0;
}