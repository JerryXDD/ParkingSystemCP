#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <stdlib.h>
#include "parkingsystem.h"
using namespace std;
using namespace std::chrono;

int main(){
    Car carData;
    Bike bikeData;
    Van vanData;
    Truck truckData;
    int choice, parkchoice, removechoice;
    bool found = false;
    string vehicletype;
    system("Color 0A");
    system_clock::time_point baseTime = loadBaseTime();

    bool dataLoaded = loadVehicle(carData, bikeData, truckData, vanData);
    
    do {
        printmenu();
        cout << "Enter choice: ";
        cin >> choice;
        if (choice < 1 || choice > 6) {
            cout << "Invalid option! Please enter a choice between 1 and 6." << endl;
            cout << endl;
            continue;
        }
        switch(choice){
            case 1:
                vehicleMenu();
                cout << "Enter Option: ";
                cin >> parkchoice;
                cout << endl;
                switch(parkchoice){
                    case 1:
                        parkCar(carData, baseTime);
                        break;
                    case 2:
                        parkBike(bikeData, baseTime);
                        break;
                    case 3:
                        parkVan(vanData, baseTime);
                        break;
                    case 4:
                        parkTruck(truckData, baseTime);
                        break;
                }
                break;
            case 2:
                vehicleMenu();
                cout << "Enter Option For Exit: ";
                cin >> removechoice;
                cout << endl;
                switch(removechoice){
                    case 1:
                        removeCar(carData, baseTime);
                        break;
                    case 2:
                        removeBike(bikeData, baseTime);
                        break;
                    case 3:
                        removeVan(vanData, baseTime);
                        break;
                    case 4:
                        removeTruck(truckData, baseTime);
                        break;
                }
                break;
            case 3:
                countSlots(carData, bikeData, vanData, truckData);
                cout << endl;
                break;
            case 4:
                if (dataLoaded){
                    cout << endl;
                    cout << "Vehicle Data Loaded Successfully" << endl;
                    cout << endl;
                } else {
                    cout << endl;
                    cout << "No Previous Data" << endl;
                    cout << endl;
                }
                adminPanel(carData, bikeData, vanData, truckData);
                cout << endl;
                break;
            case 5:
                searchVehicle(carData, bikeData, vanData, truckData);
                break;
            case 6:
                cout << "Exiting System......" << endl;
                string exitTime = printParkingTime(system_clock::now(), baseTime);
                saveBaseTime(baseTime);
                return 0;
        }
    } while (choice > 0);
    system("pause");
}   