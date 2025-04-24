#include<iostream>
using namespace std;
int main()
{
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
			cout << "Congratulatons you choose 1\n";
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
	} while (choice != 6);
    system("pause");
    return 0;
}