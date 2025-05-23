#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
#include <cstdio>
using namespace std;
using namespace std::chrono;

//this function will load the last time from last_exit_time.txt, and resume the program from the time where we exitted
system_clock::time_point loadBaseTime() {
    ifstream file("last_exit_time.txt");
    time_t savedTime;
    if (file >> savedTime) {
        return system_clock::from_time_t(savedTime);
    } else {
        return system_clock::now();
    }
}
// program exit par, this function will save the time in last_exit_time.txt, so it can be read again to resume from the previous time, instead of being resetted
void saveBaseTime(system_clock::time_point timeToSave) {
    ofstream file("last_exit_time.txt");
    time_t t = system_clock::to_time_t(timeToSave);
    file << t;
}

//speed up our time i.e 10 seconds real life to 1 minute in code time;
int simulateTime(system_clock::time_point entryTime, system_clock::time_point baseTime) {
    auto now = system_clock::now();
    auto realSeconds = duration_cast<seconds>(now - baseTime).count();
    int codeMinutes = (realSeconds / 10); 
    return codeMinutes;
}

//prints the time jab bhi vehicle parks or exits. Park krne par this will get stored in the array
string printParkingTime(system_clock::time_point entryTime, system_clock::time_point baseTime) {
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
    const int slots = 40;
    string plates[40];
    system_clock::time_point carEntry[40];
    float carFee = 3.00;
    float carTotal = 0;
};

struct Bike{
    const int slots = 30;
    string plates[30];
    system_clock::time_point bikeEntry[30];
    float bikeFee = 1.50;
    float bikeTotal = 0;
};

struct Van{
    const int slots = 20;
    string plates[20];
    system_clock::time_point vanEntry[20];
    const float vanFee = 4.50;
    float vanTotal = 0; 
};

struct Truck{
    const int slots = 10;
    string plates[10];
    system_clock::time_point truckEntry[10];
    const float truckFee = 6.00;
    float truckTotal = 0;
};

void printmenu(){
cout << "---Smart Parking Lot System---" << endl;
cout << "1. Park Vehicle" << endl;
cout << "2. Remove Vehicle" << endl;
cout << "3. View Available Slots" << endl;
cout << "4. Admin Panel" << endl;
cout << "5. Search Vehicle" << endl;
cout << "6. Exit" << endl;
}

void adminMenu(){
    cout << "ADMIN MENU" << endl;
    cout << endl;
    cout << "1. View Vehicles" << endl;
    cout << "2. View Revenue" << endl;
    cout << "3. Return To Main Menu" << endl;
    cout << endl;
}

void vehicleMenu(){
    cout << "1. Car" << endl;
    cout << "2. Bike" << endl;
    cout << "3. Van" << endl;
    cout << "4. Truck" << endl;
    cout << endl;
}

// ye wala function will load our previous data back into the program so we stay within our alloted slot limits because arrays reset upon exit.
// incase koi data nahi milega, it wont load anything
bool loadVehicle(Car &carData, Bike &bikeData, Truck &truckData, Van &vanData) {
	string type, plate, line, time, status;
    int carCount = 0, bikeCount = 0, truckCount = 0, vanCount = 0;
    int logHour, logMinute;
    bool loaded = false;
    ifstream parkinglog("parkinglog.txt");
    if (!parkinglog.is_open()){
        return false;
    }
    // Get the current system time here
    system_clock::time_point now = system_clock::now();

    while (getline(parkinglog, line)) {
        stringstream ss(line);
        ss >> status >> type >> plate >> time;

        if (sscanf(time.c_str(), "%d:%d", &logHour, &logMinute) != 2) { // This line will parse our Time string wali value, into hour and minute integers. First %d is for logHour and Second %d is for logMinute
            cout << "Invalid time format in log: " << time << endl;    // If the Format is not valid which is, the time string doesnt have a : in between, it will skip the current entry.
            continue;
        }

        // Calculate entryMinutes since base time 10:00
        int entryMinutes = (logHour - 10) * 60 + logMinute;

        // yahan par entry minutes ko hamaray scale se convert kareinge
        // 1 simulated minute = 10 real seconds
        auto entryTime = now - minutes(entryMinutes * 10);
        // Relevant Totals & Data will be added back to the arrays
        if(status == "EXIT"){
            if (type == "Car") {
                carData.carTotal += carData.carFee; 
            } else if (type == "Bike") {
                bikeData.bikeTotal += bikeData.bikeFee;
            } else if (type == "Truck"){
                truckData.truckTotal += truckData.truckFee;
            } else if (type == "Van"){
                vanData.vanTotal += vanData.vanFee;
            }
            loaded = true;
        } else if (status == "PARKED"){
            if (type == "Car" && carCount < carData.slots){
                carData.plates[carCount] = plate;
                carData.carEntry[carCount] = entryTime;
                carCount++;
                loaded = true;
            } else if (type == "Bike" && bikeCount < bikeData.slots){
                bikeData.plates[bikeCount] = plate;
                bikeData.bikeEntry[bikeCount] = entryTime;
                bikeCount++;
                loaded = true;
            } else if (type == "Truck" && truckCount < truckData.slots){
                truckData.plates[truckCount] = plate;
                truckData.truckEntry[truckCount] = entryTime;
                truckCount++;
                loaded = true;
            } else if (type == "Van" && vanCount < vanData.slots){
                vanData.plates[vanCount] = plate;
                vanData.vanEntry[vanCount] = entryTime;
                vanCount++;
                loaded = true;
            }
        }
    }
    parkinglog.close();
    return loaded;
}

void parkCar(Car &carData, system_clock::time_point baseTime) {
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
                carData.carEntry[i] = system_clock::now();
                carTime = printParkingTime(carData.carEntry[i], baseTime);
                cout << "PARKED | Vehicle Type: Car | Plate: " << plate << " | Slot: " << i + 1 << " | Time: " << carTime << endl;
                parkingfile << "PARKED" << " " << "Car" << " " << plate << " " << carTime << endl;
                parked = true;
                break;
            }
    }
    if (!parked){
            cout << "No car slots available." << endl;
    }
    parkingfile.close();
}

void parkBike(Bike &bikeData, system_clock::time_point baseTime) {
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
            bikeData.bikeEntry[i] = system_clock::now();
            bikeTime = printParkingTime(bikeData.bikeEntry[i], baseTime);
            cout << "PARKED | Vehicle Type: Bike | Plate: " << plate << " | Slot: " << i + 1 << " | Time: " << bikeTime << endl;
            parkingfile << "PARKED" << " " << "Bike" << " " << plate << " " << bikeTime << endl;
            parked = true;
            break;
        }
    }
    if (!parked){
    cout << "No Bike slots available." << endl;
    }
    parkingfile.close();
}

void parkVan(Van &vanData, system_clock::time_point baseTime) {
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
            vanData.vanEntry[i] = system_clock::now();
            vanTime = printParkingTime(vanData.vanEntry[i], baseTime);
            cout << "PARKED | Vehicle Type: Van | Plate: " << plate << " | Slot: " << i + 1 << " | Time: " << vanTime << endl;
            parkingfile << "PARKED" << " " << "Van" << " " << plate << " " << vanTime << endl;
            parked = true;
            break;
        }
    }
    if (!parked){
    cout << "No Van slots available." << endl;
    }
    parkingfile.close();
}

void parkTruck(Truck &truckData, system_clock::time_point baseTime) {
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
            truckData.truckEntry[i] = system_clock::now();
            truckTime = printParkingTime(truckData.truckEntry[i], baseTime);
            cout << "PARKED | Vehicle Type: Truck | Plate: " << plate << " | Slot: " << i + 1 << " | Time: " << truckTime << endl;
            parkingfile << "PARKED" << " " << "Truck" << " " << plate << " " << truckTime << endl;
            parked = true;
            break;
        }
    }
    if (!parked){
    cout << "No Truck slots available." << endl;
    }
}

void removeCar(Car &carData, system_clock::time_point baseTime){
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
            carExit = printParkingTime(system_clock::now(), baseTime);
            parkingfile << "EXIT" << " " << "Car" << plate << " " << carExit << endl;
            carData.plates[i] = ""; 
            carData.carEntry[i] = system_clock::time_point();
            cout << "---------------------------" << endl;
            cout << "       Parking Receipt" << endl;
            cout << endl;
            cout << "Vehicle Type: Car" << endl;
            cout << "Plate: " << plate << endl;
            cout << "Fee: $" << carData.carFee << endl;
            cout << "    Thank You For Parking" << endl;
            cout << "---------------------------" << endl;
            cout << endl;
            carData.carTotal += carData.carFee;
            break;
        }
    }
    if (!found) {
        cout << "Car not found!" << endl;
    }
    parkingfile.close();
}

void removeBike(Bike &bikeData, system_clock::time_point baseTime){
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
            bikeExit = printParkingTime(system_clock::now(), baseTime);
            parkingfile << "EXIT" << " " << "Bike" << plate << " " << bikeExit << endl;
            bikeData.plates[i] = ""; 
            bikeData.bikeEntry[i] = system_clock::time_point();
            cout << "---------------------------" << endl;
            cout << "       Parking Receipt" << endl;
            cout << endl;
            cout << "Vehicle Type: Bike" << endl;
            cout << "Plate: " << plate << endl;
            cout << "Fee: $" << bikeData.bikeFee << endl;
            cout << "    Thank You For Parking" << endl;
            cout << "---------------------------" << endl;
            cout << endl;
            bikeData.bikeTotal += bikeData.bikeFee;
            break;
        }
    }
    if (!found) {
        cout << "Bike not found!" << endl;
    }
    parkingfile.close();
}

void removeVan(Van &vanData, system_clock::time_point baseTime){
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
            vanExit = printParkingTime(system_clock::now(), baseTime);
            parkingfile << "EXIT" << " " << "Van" << plate << " " << vanExit << endl;
            vanData.plates[i] = ""; 
            vanData.vanEntry[i] = system_clock::time_point();
            cout << "---------------------------" << endl;
            cout << "       Parking Receipt" << endl;
            cout << endl;
            cout << "Vehicle Type: Van" << endl;
            cout << "Plate: " << plate << endl;
            cout << "Fee: $" << vanData.vanFee << endl;
            cout << "    Thank You For Parking" << endl;
            cout << "---------------------------" << endl;
            cout << endl;
            vanData.vanTotal += vanData.vanFee;
            break;
        }
    }
    if (!found) {
        cout << "Van not found!" << endl;
    }
    parkingfile.close();
}

void removeTruck(Truck &truckData, system_clock::time_point baseTime){
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
            truckExit = printParkingTime(system_clock::now(), baseTime);
            parkingfile << "EXIT" << " " << "Truck" << plate << " " << truckExit << endl;
            truckData.plates[i] = ""; 
            truckData.truckEntry[i] = system_clock::time_point();
            cout << "---------------------------" << endl;
            cout << "       Parking Receipt" << endl;
            cout << endl;
            cout << "Vehicle Type: Truc" << endl;
            cout << "Plate: " << plate << endl;
            cout << "Fee: $" << truckData.truckFee << endl;
            cout << "    Thank You For Parking" << endl;
            cout << "---------------------------" << endl;
            cout << endl;
            truckData.truckTotal += truckData.truckFee;
            break;
        }
    }
    if (!found) {
        cout << "Truck not found!" << endl;
    }
    parkingfile.close();
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
    cout << endl;
    cout << "--- Remaining Parking Slots ---" << endl;
    cout << "Car Slots Available: " << carCounter << " out of " << carData.slots << endl;
    cout << "Bike Slots Available: " << bikeCounter << " out of " << bikeData.slots << endl;
    cout << "Truck Slots Available: " << truckCounter << " out of " << truckData.slots << endl;
    cout << "Van Slots Available: " << vanCounter << " out of " << vanData.slots << endl;
    cout << endl;
}

void printlog(){
    ifstream parkinglog("parkinglog.txt");
    string line;
    if(parkinglog.is_open()){
        while(getline(parkinglog, line)){
            cout << line << endl;
        }
        parkinglog.close();
    } else {
        cout << "Unable To Open Parking File" << endl;
    }
}

// username and password will get validated through another file, just simple reading and comparison as miss fatima suggested this when i asked her
void adminPanel(Car &carData, Bike &bikeData, Van &vanData, Truck &truckData){
    string storeduser, storedpw;
	string userinput, pwinput;
	int tries = 0, choice;
    ifstream parkLog("parkinglogin.txt");
	if(!parkLog.is_open()){
		cout << "Error. Credentials Could Not be Fetched" << endl;
		return;
	}
    getline(parkLog, storeduser);
	getline(parkLog, storedpw);
	parkLog.close();
    while(tries < 3){
        cout << "Enter Username: ";
        cin.ignore();
		getline(cin, userinput);
		cout << "Enter Password: ";
		getline(cin, pwinput);
		if (storeduser == userinput && storedpw == pwinput) {
		cout << endl;
        cout << "Login Successfull" << endl;
        cout << endl;
        adminMenu();
            do{
                cout << "Enter Option: ";
                cin >> choice;
                switch (choice){
                case 1:
                    cout << endl;
                    printlog();
                    cout << endl;
                    break;
                case 2:
                    cout << endl;
                    cout << "-----Revenue-----" << endl;
                    cout << "Car Revenue: $" << carData.carTotal << endl;
                    cout << "Bike Revenue: $" << bikeData.bikeTotal << endl;
                    cout << "Van Revenue: $" << vanData.vanTotal << endl;
                    cout << "Truck Revenue: $" << truckData.truckTotal << endl;
                    cout << "Total Revenue: $" << carData.carTotal + bikeData.bikeTotal + vanData.vanTotal + truckData.truckTotal << endl;
                    cout << endl;
                    break;
                case 3:
                    cout << "Exiting..." << endl;
                    return;
                }
            } while (choice != 3);
            } else {
                tries++;
			    cout << "Wrong Username or Password. Try Again" << endl;
			    if (tries >= 3) {
				    cout << "Maximum attempts reached. Returning to Main Menu...." << endl;
                    return;
                }
            } 
        }  
}

void searchVehicle(Car &carData, Bike &bikeData, Van &vanData, Truck &truckData){
    string platenumber;
    cout << "Enter the Plate Number of the vehicle you are searching: ";
    cin >> platenumber;
    bool found = false;
    
    for (int i = 0; i < carData.slots; i++){
            if (carData.plates[i] == platenumber){
                cout << "FOUND" << endl;
                cout << "Vehicle Type: Car | Plate number " << platenumber << " | Slot: " << i + 1 << endl;
                cout << endl;
                found = true;
                break;
            }
        }
        if (!found){
            for (int j = 0; j < bikeData.slots; j++){
                if (bikeData.plates[j] == platenumber){
                    cout << "FOUND" << endl;
                    cout << "Vehicle Type: Bike | Plate number " << platenumber << " | Slot: " << j + 1 << endl;
                    cout << endl;
                    break;
                }
            }
        }
        if (!found){
            for (int x = 0; x < truckData.slots; x++){
                if (truckData.plates[x] == platenumber){
                    cout << "Vehicle Type: Truck | Plate number " << platenumber << " | Slot: " << x + 1 << endl;
                    cout << endl;
                    break;
                }
            }
        }
        if (!found){
            for (int y = 0; y < vanData.slots; y++){
                if (vanData.plates[y] == platenumber){
                    cout << "Vehicle Type: Van | Plate number " << platenumber << " | Slot: " << y + 1 << endl;
                    cout << endl;
                    break;
                }
            }
        }
        if (!found){
            cout << "Vehicle Doesn't Exist" << endl;
            cout << endl;
        }
}

int main(){
    Car carData;
    Bike bikeData;
    Van vanData;
    Truck truckData;
    int choice, parkchoice, removechoice;
    bool found = false;
    string vehicletype;
    // Check if Any Previous Time is saved and start from there, otherwise it will start from 10:00
    system_clock::time_point baseTime = loadBaseTime();
    // Previous Data to be loaded
    bool dataLoaded = loadVehicle(carData, bikeData, truckData, vanData);
    do {
        printmenu();
        cout << "Enter choice: ";
        cin >> choice;
        if (choice < 1 || choice > 6) {
            cout << "Invalid option! Please enter a choice between 1 and 6." << endl;
            break;
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
                    cout << "Vehicle Data Loaded Successfully" << endl;
                } else {
                    cout << "No Previous Data" << endl;
                }
                adminPanel(carData, bikeData, vanData, truckData);
                cout << endl;
                break;
            case 5:
                searchVehicle(carData, bikeData, vanData, truckData);
                break;
            case 6:
                // As Soon as User Exits, code ka current time gets saved in last_exit_time.txt
                // Beware that time can get a little buggy at certain periods, not our fault as compiler mein inconsistencies hongi in interpreting time
                cout << "Exiting System......" << endl;
                string exitTime = printParkingTime(system_clock::now(), baseTime);
                saveBaseTime(baseTime);
                return 0;
        }
    } while (choice > 0);
    system("pause");
}   