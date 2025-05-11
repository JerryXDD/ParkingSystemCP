#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

auto baseTime = steady_clock::now();

int simulateTime(steady_clock::time_point entryTime, steady_clock::time_point baseTime) {
    auto now = steady_clock::now();
    auto realSeconds = duration_cast<seconds>(now - baseTime).count();
    int codeMinutes = (realSeconds / 10); 
    return codeMinutes;
}

string printParkingTime(steady_clock::time_point entryTime, steady_clock::time_point baseTime) {
    string parkTime;
    int codeMinutes = simulateTime(entryTime, baseTime);
    int baseHours = 10;
    int baseMinutes = 0;
    int totalMinutes = baseHours * 60 + baseMinutes + codeMinutes;
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    parkTime = to_string(hours) + ":" + (minutes < 10 ? "0" : "") + to_string(minutes);
    return parkTime;
}

struct Car{
    int slots = 40;
    string plates[40];
    steady_clock::time_point carEntry[40];
    float carFee = 3.00;
    float carTotal = 0;
};

struct Bike{
    int slots = 30;
    string plates[30];
    steady_clock::time_point bikeEntry[30];
    float bikeFee = 1.50;
    float bikeTotal = 0;
};

struct Van{
    int slots = 20;
    string plates[20];
    steady_clock::time_point vanEntry[20];
    const float vanFee = 4.50;
    float vanTotal = 0; 
};

struct Truck{
    int slots = 10;
    string plates[10];
    steady_clock::time_point truckEntry[10];
    const float truckFee = 6.00;
    float truckTotal = 0;
};

void printmenu()
{
cout << "---Smart Parking Lot System---" << endl;
cout << "1.Park Vehicle" << endl;
cout << "2.Remove Vehicle" << endl;
cout << "3.View Available Slots" << endl;
cout << "4.View Parking Log" << endl;
cout << "5.Search Vehicle" << endl;
cout << "6.Exit" << endl;
}

void parkCar(Car &carData) {
    string plate, carTime;
    bool parked = false;
    ofstream parkingfile("parkinglog.txt", ios::app);
    if(!parkingfile.is_open()){
        cout << "Unable to open File" << endl;
        return;
    }
        for (int i = 0; i < carData.slots; i++) {
            if (carData.plates[i] == "") {
                cout << "Enter plate number for Car: ";
                cin >> plate;
                carData.plates[i] = plate;
                carData.carEntry[i] = steady_clock::now();
                carTime = printParkingTime(carData.carEntry[i], baseTime);
                cout << "Car Plate: " << plate << " parked at Slot " << i + 1 << " at time: " << printParkingTime(carData.carEntry[i], baseTime) << endl;
                parkingfile << "PARKED | Vehicle Type: Car | Plate: " << plate << " | Slot: " << i + 1 << " | Time: " << carTime << endl;
                parked = true;
                break;
            }
    }
    parkingfile.close();
    if (!parked){
            cout << "No car slots available." << endl;
        }
}

void parkBike(Bike &bikeData) {
    string plate, bikeTime;
    bool parked = false;
    ofstream parkingfile("parkinglog.txt", ios::app);
    if(!parkingfile.is_open()){
        cout << "Unable to open File" << endl;
        return;
    }
    for (int i = 0; i < bikeData.slots; i++) {
        if (bikeData.plates[i] == "") {
            cout << "Enter plate number for Bike: ";
            cin >> plate;
            bikeData.plates[i] = plate;
            bikeData.bikeEntry[i] = steady_clock::now();
            bikeTime = printParkingTime(bikeData.bikeEntry[i], baseTime);
            cout << "Bike Plate: " << plate << " parked at Slot " << i + 1 << " at time: " << printParkingTime(bikeData.bikeEntry[i], baseTime) << endl;
            parkingfile << "PARKED | Vehicle Type: Bike | Plate: " << plate << " | Slot: " << i + 1 << " | Time: " << bikeTime << endl;
            parked = true;
            break;
        }
    }
    if (!parked){
    cout << "No Bike slots available." << endl;
    }
}

void parkVan(Van &vanData) {
    string plate, vanTime;
    bool parked = false;
    ofstream parkingfile("parkinglog.txt", ios::app);
    if(!parkingfile.is_open()){
        cout << "Unable to open File" << endl;
        return;
    }
    for (int i = 0; i < vanData.slots; i++) {
        if (vanData.plates[i] == "") {
            cout << "Enter plate number for Van: ";
            cin >> plate;
            vanData.plates[i] = plate;
            vanData.vanEntry[i] = steady_clock::now();
            vanTime = printParkingTime(vanData.vanEntry[i], baseTime);
            cout << "Van Plate: " << plate << " parked at Slot " << i + 1 << " at time: " << printParkingTime(vanData.vanEntry[i], baseTime) << endl;
            parkingfile << "PARKED | Vehicle Type: Van | Plate: " << plate << " | Slot: " << i + 1 << " | Time: " << vanTime << endl;
            parked = true;
            break;
        }
    }
    if (!parked){
    cout << "No Van slots available." << endl;
    }
}

void parkTruck(Truck &truckData) {
    string plate, truckTime;
    bool parked = false;
    ofstream parkingfile("parkinglog.txt", ios::app);
    if(!parkingfile.is_open()){
        cout << "Unable to open File" << endl;
        return;
    }
    for (int i = 0; i < truckData.slots; i++) {
        if (truckData.plates[i] == "") {
            cout << "Enter plate number for Truck: ";
            cin >> plate;
            truckData.plates[i] = plate;
            truckData.truckEntry[i] = steady_clock::now();
            truckTime = printParkingTime(truckData.truckEntry[i], baseTime);
            cout << "Truck Plate: " << plate << " parked at Slot " << i + 1 << " at time: " << printParkingTime(truckData.truckEntry[i], baseTime) << endl;
            parkingfile << "PARKED | Vehicle Type: Truck | Plate: " << plate << " | Slot: " << i + 1 << " | Time: " << truckTime << endl;
            parked = true;
            break;
        }
    }
    if (!parked){
    cout << "No Truck slots available." << endl;
    }
}

void removeCar(Car &carData){
    string plate, carExit;
    cout << "Enter the car plate number you want to remove: ";
    cin >> plate;
    bool found = false;
    ofstream parkingfile("parkinglog.txt", ios::app);
    if(!parkingfile.is_open()){
        cout << "Unable to open File" << endl;
        return;
    }
    for (int i = 0; i < carData.slots; i++) {
        if (carData.plates[i] == plate) {
            found = true;
            carExit = printParkingTime(steady_clock::now(), baseTime);
            carData.plates[i] = ""; 
            carData.carEntry[i] = steady_clock::time_point();
            cout << "Your Car with plate number " << plate << " removed from Slot " << i + 1 << "at " << carExit << endl;
            cout << "Fee is: $" << carData.carFee;
            carData.carTotal += carData.carTotal;
            parkingfile << "EXIT | Vehicle Type: Car | Plate: " << plate << " | Slot: " << i + 1 << " | Exit Time: " << carExit << endl;
            break;
        }
    }
    if (!found) {
        cout << "Car not found!" << endl;
    }
}

void removeBike(Bike &bikeData){
    string plate, bikeExit;
    cout << "Enter the car plate number you want to remove: ";
    cin >> plate;
    bool found = false;
    ofstream parkingfile("parkinglog.txt", ios::app);
    if(!parkingfile.is_open()){
        cout << "Unable to open File" << endl;
        return;
    }
    for (int i = 0; i < bikeData.slots; i++) {
        if (bikeData.plates[i] == plate) {
            found = true;
            bikeExit = printParkingTime(steady_clock::now(), baseTime);
            bikeData.plates[i] = ""; 
            bikeData.bikeEntry[i] = steady_clock::time_point();
            cout << "Your Bike with plate number " << plate << " removed from Slot " << i + 1 << "at " << bikeExit << endl;
            cout << "Fee is : $" << bikeData.bikeFee;
            bikeData.bikeTotal += bikeData.bikeFee;
            parkingfile << "EXIT | Vehicle Type: Bike | Plate: " << plate << " | Slot: " << i + 1 << " | Exit Time: " << bikeExit << endl;
            break;
        }
    }
    if (!found) {
        cout << "Bike not found!" << endl;
    }
}

void removeVan(Van &vanData){
    string plate, vanExit;
    cout << "Enter the car plate number you want to remove: ";
    cin >> plate;
    bool found = false;
    ofstream parkingfile("parkinglog.txt", ios::app);
    if(!parkingfile.is_open()){
        cout << "Unable to open File" << endl;
        return;
    }
    for (int i = 0; i < vanData.slots; i++) {
        if (vanData.plates[i] == plate) {
            found = true;
            vanExit = printParkingTime(steady_clock::now(), baseTime);
            vanData.plates[i] = ""; 
            vanData.vanEntry[i] = steady_clock::time_point();
            cout << "Your Van with plate number " << plate << " removed from Slot " << i + 1 << "at " << vanExit << endl;
            cout << "Fee is: $" << vanData.vanFee;
            vanData.vanTotal += vanData.vanFee;
            parkingfile << "EXIT | Vehicle Type: Van | Plate: " << plate << " | Slot: " << i + 1 << " | Exit Time: " << vanExit << endl;
            
            break;
        }
    }
    if (!found) {
        cout << "Van not found!" << endl;
    }
}

void removeTruck(Truck &truckData){
    string plate, truckExit;
    cout << "Enter the car plate number you want to remove: ";
    cin >> plate;
    bool found = false;
    ofstream parkingfile("parkinglog.txt", ios::app);
    if(!parkingfile.is_open()){
        cout << "Unable to open File" << endl;
        return;
    }
    for (int i = 0; i < truckData.slots; i++) {
        if (truckData.plates[i] == plate) {
            found = true;
            truckExit = printParkingTime(steady_clock::now(), baseTime);
            truckData.plates[i] = ""; 
            truckData.truckEntry[i] = steady_clock::time_point();
            cout << "Your Truck with plate number " << plate << " removed from Slot " << i + 1 << "at " << truckExit << endl;
            cout << "Fee is: $" << truckData.truckFee;
            truckData.truckTotal += truckData.truckFee;
            parkingfile << "EXIT | Vehicle Type: Truck | Plate: " << plate << " | Slot: " << i + 1 << " | Exit Time: " << truckExit << endl;
            break;
        }
    }
    if (!found) {
        cout << "Truck not found!" << endl;
    }
}

void countSlots(Car &carData, Bike &bikeData, Van &vanData, Truck &truckData){
    int carCounter = 0, bikeCounter = 0, truckCounter = 0, vanCounter = 0;
    for (int i = 0; i < carData.slots; i++)
    {
        if (carData.plates[i] == ""){ 
            carCounter++;
        }
    }
    for (int i = 0; i < bikeData.slots; i++) {
        if (bikeData.plates[i] == ""){
            bikeCounter++;
        }
    }
    for (int i = 0; i < truckData.slots; i++) {
        if (truckData.plates[i] == ""){ 
            truckCounter++;
        }
    }
    for (int i = 0; i < vanData.slots; i++) {
        if (vanData.plates[i] == ""){ 
            vanCounter++;
        }
    }
    cout << "--- Remaining Parking Slots ---" << endl;
    cout << "Car Slots Available: " << carCounter << " out of " << carData.slots << endl;
    cout << "Bike Slots Available: " << bikeCounter << " out of " << bikeData.slots << endl;
    cout << "Truck Slots Available: " << truckCounter << " out of " << truckData.slots << endl;
    cout << "Van Slots Available: " << vanCounter << " out of " << vanData.slots << endl;
}

void viewParkingLog(Car &carData, Bike &bikeData, Van &vanData, Truck &truckData){
    const string username = "admin12?";
    const string password = "parkingview34?";
    const int maxtries = 3;
    int usercounter = 0, pwcounter = 0;
    string userinput, passwordinput;
    do{
    cout << "Enter Username :";
    cin.ignore();
    getline(cin, userinput);
    if (username == userinput){
        cout << "Enter Password: ";
        cin.ignore();
        getline(cin, passwordinput);
        if (password == passwordinput){
            ifstream parkingfile("parkinglog.txt");
            string linex;
            if(parkingfile.is_open()){
                while (getline(parkingfile, linex)){
                cout << linex;
                cout << endl;
            }
            parkingfile.close();
            cout << endl;
            cout << "-----Revenue-----" << endl;
            cout << "Car Revenue: $" << carData.carTotal << endl;
            cout << "Bike Revenue: $" << bikeData.bikeTotal << endl;
            cout << "Van Revenue: $" << vanData.vanTotal << endl;
            cout << "Truck Revenue: $" << truckData.truckTotal << endl;
            cout << "Total Revenue: $" << carData.carTotal + bikeData.bikeTotal + vanData.vanTotal + truckData.truckTotal << endl;
            return;
            } else{
                cout << "Unable to Open Parking Log" << endl;
            }
        } else{
            cout << "Wrong Password. Try Again";
            pwcounter++;
            break;
        }
        } else{
            cout << "Wrong Username. Try Again";
            usercounter++;
            break;
        }
    if (usercounter > maxtries || pwcounter > maxtries){
        cout << "Too Many Attempts. Try Later" << endl;
        return;
    }
    } while (usercounter <= maxtries || pwcounter <= maxtries);
}

void searchVehicle(Car &carData, Bike &bikeData, Van &vanData, Truck &truckData){
    string platenumber;
    cout << "Enter the platenumber of the vehicle you are searching: ";
    cin >> platenumber;
    bool found = false;
    
    for (int i = 0; i < carData.slots; i++){
            if (carData.plates[i] == platenumber){
                cout << "Your Car with plate number " << platenumber << " is found at Slot: " << i + 1 << endl;
                found = true;
                break;
            }
        }
        if (!found){
            for (int j = 0; j < bikeData.slots; j++){
                if (bikeData.plates[j] == platenumber){
                    cout << "Your Bike with plate number " << platenumber << " is found at Slot: " << j + 1 << endl;
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            for (int x = 0; x < truckData.slots; x++){
                if (truckData.plates[x] == platenumber){
                    cout << "Your Truck with plate number " << platenumber << " is found at Slot: " << x + 1 << endl;
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            for (int y = 0; y < vanData.slots; y++){
                if (vanData.plates[y] == platenumber){
                    cout << "Your Van with plate number " << platenumber << " is found at Slot: " << y + 1 << endl;
                    found = true;
                    break;
                }
            }
        }
        if (!found){
            cout << "Sorry! We can`t find any vehicle with plate number " << platenumber << " in the parking lot." << endl;
        }
}

int main(){
    Car carData;
    Bike bikeData;
    Van vanData;
    Truck truckData;
    int choice;
    bool found = false;
    string vehicletype;
    
    do {
        printmenu();
        cout << "Enter choice: ";
        cin >> choice;
        cout << endl;
        if (choice < 1 || choice > 6) {
            cout << "Invalid option! Please enter a choice between 1 and 6.\n";
            break;
        }
        switch(choice){
            case 1:
                cout << "Enter vehicle type (car/bike/truck/van): ";
                cin >> vehicletype;
                cout << endl;
                if (vehicletype == "car" || vehicletype == "Car") {
                    parkCar(carData);
                    break;
                }
                else if (vehicletype == "bike" || vehicletype == "Bike") {
                    parkBike(bikeData);
                    break;
                }
                else if (vehicletype == "truck" || vehicletype == "Truck") {
                    parkTruck(truckData);
                    break;
                    }
                else if (vehicletype == "van" || vehicletype == "Van") {
                    parkVan(vanData);
                    break;
                }
                else {
                    cout << "Invalid vehicle type! Please enter car, bike, truck, or van." << endl;
                }
            case 2:
                cout << "Enter vehicle type (car/bike/truck/van): ";
                    cin >> vehicletype;
                if (vehicletype == "car" || vehicletype == "Car") {
                    removeCar(carData);
                }
                else if (vehicletype == "bike" || vehicletype == "Bike") {
                    removeBike(bikeData);
                    break;
                }
                else if (vehicletype == "truck" || vehicletype == "Truck") {
                    removeTruck(truckData);
                    break;
                    }
                else if (vehicletype == "van" || vehicletype == "Van") {
                    removeVan(vanData);
                    break;
                }
                else {
                    cout << "Invalid vehicle type! Please enter car, bike, truck, or van." << endl;
                }
            case 3:
                countSlots(carData, bikeData, vanData, truckData);
                cout << endl;
                break;
            case 4:
                viewParkingLog(carData, bikeData, vanData, truckData);
                break;
            case 5:
                searchVehicle(carData, bikeData, vanData, truckData);
                break;
            case 6:
                cout << "Exiting System......" << endl;
                return 0;
        }
    } while (choice > 0);
    system("pause");
}   