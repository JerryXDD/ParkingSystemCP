#include<iostream>
using namespace std;

const int Carslots = 40, Bikeslots = 30, Vanslots = 20, Truckslots = 10;
string Car[Carslots], Bike[Bikeslots], Truck[Truckslots], Van[Vanslots];

void printmenu()
{
cout << "---Smart Parking Lot System---" << endl;
cout << "1.Park Vehicle" << endl;
cout << "2.Remove Vehicle" << endl;
cout << "3.View Available Slots" << endl;
cout << "4.View Parked Vehicles" << endl;
cout << "5.Search Vehicle" << endl;
cout << "6.Exit" << endl;
}
int main() {
    int choice;
    string vehicletype, platenumber;
    bool found = false;
    
    do {
        printmenu();
        cout << "Enter choice: ";
        cin >> choice;

        if (choice < 1 || choice > 6) {
            cout << "Invalid option! Please enter a choice between 1 and 2.\n";
            break;
        }
        switch (choice) {
        case 1:
        cout << "Enter vehicle type (car/bike/truck/van): ";
        cin >> vehicletype;
    
        if (vehicletype == "car" || vehicletype == "Car") {
            bool parked = false;
            for (int i = 0; i < Carslots; i++) {
                if (Car[i] == "") {
                    cout << "Enter plate number for car: ";
                    cin >> platenumber;
                    Car[i] = platenumber;
                    cout << "Success. Your car with plate number " << platenumber << " is Parked at Car Slot No. " << i + 1 << "." << endl;
                    parked = true;
                    break;
                }
            }
            if (!parked) {
                cout << "No car slots are available currently." << endl;
            }
        }
        else if (vehicletype == "bike" || vehicletype == "Bike") {
            bool parked = false;
            for (int i = 0; i < Bikeslots; i++) {
                if (Bike[i] == "") {
                    cout << "Enter plate number for bike: ";
                    cin >> platenumber;
                    Bike[i] = platenumber;
                    cout << "Success. Your bike with plate number " << platenumber << " is Parked at Bike Slot No. " << i + 1 << "." << endl;
                    parked = true;
                    break;
                }
            }
            if (!parked) {
                cout << "No bike slots are available currently." << endl;
            }
        }
        else if (vehicletype == "truck" || vehicletype == "Truck") {
            bool parked = false;
            for (int i = 0; i < Truckslots; i++) {
                if (Truck[i] == "") {
                    cout << "Enter plate number for truck: ";
                    cin >> platenumber;
                    Truck[i] = platenumber;
                    cout << "Success. Your truck with plate number " << platenumber << " is Parked at Truck Slot No. " << i + 1 << "." << endl;
                    parked = true;
                    break;
                }
            }
            if (!parked) {
                cout << "No truck slots are available currently." << endl;
            }
        }
        else if (vehicletype == "van" || vehicletype == "Van") {
            bool parked = false;
            for (int i = 0; i < Vanslots; i++) {
                if (Van[i] == "") {
                    cout << "Enter plate number for van: ";
                    cin >> platenumber;
                    Van[i] = platenumber;
                    cout << "Your van with plate number " << platenumber << " is Parked at Van Slot No. " << i + 1 << "." << endl;
                    parked = true;
                    break;
                }
            }
            if (!parked) {
                cout << "No van slots are available currently." << endl;
            }
        }
        else {
            cout << "Invalid vehicle type! Please enter car, bike, truck, or van." << endl;
        }
        break;
    
        case 2:
            cout << "Enter vehicle type you want to remove (car/bike/truck/van): ";
            cin >> vehicletype;
            found = false;

            if (vehicletype == "car" || vehicletype == "Car") {
                cout << "Enter the car plate number you want to remove: ";
                cin >> platenumber;

                for (int i = 0; i < Carslotcounter; i++) {
                    if (Car[i] == platenumber) {
                        for (int j = i; j < Carslotcounter - 1; j++) {
                            Car[j] = Car[j + 1];
                        }
                        Carslotcounter--;
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << "Your car with plate number " << platenumber << " is successfully removed." << endl;
                } else {
                    cout << "Vehicle with plate " << platenumber << " not found!" << endl;
                }
            } else if (vehicletype == "bike" || vehicletype == "Bike") {
                cout << "Enter the bike plate number you want to remove: ";
                cin >> platenumber;

                for (int i = 0; i < Bikeslotcounter; i++) {
                    if (Bike[i] == platenumber) {
                        for (int j = i; j < Bikeslotcounter - 1; j++) {
                            Bike[j] = Bike[j + 1];
                        }
                        Bikeslotcounter--;
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << "Your bike with plate number " << platenumber << " is successfully removed." << endl;
                } else {
                    cout << "Vehicle with plate " << platenumber << " not found!" << endl;
                }
            } else if (vehicletype == "truck" || vehicletype == "Truck") {
                cout << "Enter the truck plate number you want to remove: ";
                cin >> platenumber;

                for (int i = 0; i < Truckslotcounter; i++) {
                    if (Truck[i] == platenumber) {
                        for (int j = i; j < Truckslotcounter - 1; j++) {
                            Truck[j] = Truck[j + 1];
                        }
                        Truckslotcounter--;
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << "Your truck with plate number " << platenumber << " is successfully removed." << endl;
                } else {
                    cout << "Vehicle with plate " << platenumber << " not found!" << endl;
                }
            } else if (vehicletype == "van" || vehicletype == "Van") {
                cout << "Enter the van plate number you want to remove: ";
                cin >> platenumber;

                for (int i = 0; i < Vanslotcounter; i++) {
                    if (Van[i] == platenumber) {
                        for (int j = i; j < Vanslotcounter - 1; j++) {
                            Van[j] = Van[j + 1];
                        }
                        Vanslotcounter--;
                        found = true;
                        break;
                    }
                }

                if (found) {
                    cout << "Your van with plate number " << platenumber << " is successfully removed." << endl;
                } else {
                    cout << "Vehicle with plate " << platenumber << " not found!" << endl;
                }
            } else {
                cout << "Invalid input! Please enter the correct vehicle type." << endl;
            }
            break;
        case 3:
            break;
        
        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        default:
            break;
        }

    } while ( choice != 6);
    system("pause");
    return 0;
}

