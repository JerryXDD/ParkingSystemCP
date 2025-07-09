# Smart Parking Lot System

As Part of my 1st Semester Project for the Computer Programming Course, we deisgned a comprehensive C++ console-based parking management system that handles multiple vehicle types with persistent data storage and time simulation features.

## Features

### Core Functionality
- **Multi-vehicle support**: Cars, Bikes, Vans, and Trucks
- **Real-time slot management**: Track available parking slots for each vehicle type
- **Persistent data storage**: Automatic saving and loading of parking data
- **Time simulation**: Simulates parking time (10 real seconds = 1 minute in system)
- **Revenue tracking**: Comprehensive revenue management per vehicle type
- **Duplicate prevention**: Prevents parking of vehicles with duplicate license plates

### Vehicle Capacity
- **Cars**: 40 slots (Fee: $3.00)
- **Bikes**: 30 slots (Fee: $1.50)
- **Vans**: 20 slots (Fee: $4.50)
- **Trucks**: 10 slots (Fee: $6.00)

### Advanced Features
- **Admin Panel**: Secure login system for administrative access
- **Search Functionality**: Find vehicles by license plate number
- **Parking Logs**: Complete history of all parking activities
- **Receipt Generation**: Automatic receipt printing on vehicle exit
- **Data Persistence**: System remembers state between sessions

## Prerequisites

- C++ compiler (GCC, Clang, or MSVC)
- C++11 or later standard
- Windows OS (for `system("Color 0A")` command)

## Usage

### Main Menu Options
1. **Park Vehicle** - Add a new vehicle to the parking lot
2. **Remove Vehicle** - Remove a vehicle and generate receipt
3. **View Available Slots** - Check remaining capacity for each vehicle type
4. **Admin Panel** - Access administrative features (requires login)
5. **Search Vehicle** - Find a vehicle by license plate
6. **Exit** - Close the application

### Admin Panel Features
- **View Vehicles**: Display complete parking log
- **View Revenue**: Show revenue breakdown by vehicle type
- **Return to Main Menu**: Exit admin panel

### Default Admin Credentials
- **Username**: `admin12`
- **Password**: `parking57`

## Configuration Files

### parkinglogin.txt
```
admin12
parking57
```

### Sample parkinglog.txt
```
PARKED Car ABC-123 10:05
PARKED Bike XYZ-789 10:15
EXIT Car ABC-123 11:30
```

## Technical Details

### Time Simulation
- Real time is converted to simulated parking time
- 10 real seconds = 1 minute in system
- Base time starts at 10:00 AM
- System maintains time persistence between sessions

### Data Persistence
- Parking data is automatically saved to `parkinglog.txt`
- System state is preserved between application runs
- Last exit time is stored for continuous time simulation

### Error Handling
- Duplicate license plate detection
- Invalid input validation
- File operation error handling
- Maximum login attempt restrictions (3 attempts)

### Key Functions
- `parkCar()`, `parkBike()`, `parkVan()`, `parkTruck()` - Vehicle parking functions
- `removeCar()`, `removeBike()`, `removeVan()`, `removeTruck()` - Vehicle removal functions
- `searchVehicle()` - Search functionality
- `adminPanel()` - Admin access control
- `loadVehicle()` - Data loading from files
- `countSlots()` - Available slot calculation

### Data Structures
- `Car`, `Bike`, `Van`, `Truck` structs with slot management
- Time point arrays for entry tracking
- Revenue tracking variables

## Future Enhancements

- [ ] GUI interface implementation
- [ ] Database integration
- [ ] Reservation system
- [ ] Multi-location support
- [ ] Real-time monitoring dashboard

## Known Issues

- Windows-specific terminal color commands
- Fixed time simulation ratio (10:1)
- Console-based interface limitations

**Note**: This system is designed for educational purposes and may require modifications for production use.
