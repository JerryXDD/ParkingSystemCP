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