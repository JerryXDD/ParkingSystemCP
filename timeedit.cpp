#include <iostream>
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int car_slot = 40;

int simulateTime(steady_clock::time_point entryTime, steady_clock::time_point baseTime) {
    auto now = steady_clock::now();
    auto realSeconds = duration_cast<seconds>(now - baseTime).count();
    int codeMinutes = (realSeconds / 10); 
    return codeMinutes;
}

void printParkingTime(steady_clock::time_point entryTime, steady_clock::time_point baseTime) {
    int codeMinutes = simulateTime(entryTime, baseTime);
    int baseHours = 10;
    int baseMinutes = 0;
    int totalMinutes = baseHours * 60 + baseMinutes + codeMinutes;
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    cout << hours << minutes << endl;
    cout << hours << ":" << (minutes < 10 ? "0" : "") << minutes << endl;
}

int main() {
    string plateremove;
    string carPlate[car_slot];
    steady_clock::time_point carEntry[car_slot];

    auto baseTime = steady_clock::now();  

    for (int i = 0; i < 2; i++) {
        if (carPlate[i] == "") {
            cout << "Enter Car Plate: ";
            cin >> carPlate[i];
            carEntry[i] = steady_clock::now();  
            cout << "Car Plate: " << carPlate[i] << " Parked at Slot " << i + 1 << " At Time: ";
            printParkingTime(carEntry[i], baseTime);  
        }
    }

    cout << "Enter the plate number of the car to remove: ";
    cin >> plateremove;
    
    bool found = false;
    for (int i = 0; i < car_slot; i++) {
        if (carPlate[i] == plateremove) {
            found = true;
            auto now = steady_clock::now();
            int removalMinutes = simulateTime(carEntry[i], baseTime); 
            int hours = 10 + removalMinutes / 60;  
            int minutes = removalMinutes % 60;
            cout << "Vehicle removed at: " << hours << ":" << (minutes < 10 ? "0" : "") << minutes << endl;
            carPlate[i] = "";  
            break;
        }
    }

    if (!found) {
        cout << "Vehicle not found in the system!" << endl;
    }

    system("pause");
    return 0;
}