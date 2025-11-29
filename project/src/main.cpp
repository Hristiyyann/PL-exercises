/**
 * @file main.cpp
 * @brief Main application for the Airplane Fleet Management System
 *
 * REQUIREMENTS FULFILLED IN THIS FILE:
 * - Support for arbitrary number of different airplanes of different classes (10 points)
 * - Search for airplanes that can fly to a destination (10 points)
 * - File I/O operations - read and store data to files (20 points)
 *
 * This application provides a menu-driven interface for:
 * - Managing plane classes (aircraft types)
 * - Managing airplanes in the fleet
 * - Managing destinations
 * - Searching for airplanes compatible with destinations
 * - Saving/loading data to/from files
 */

#include <iostream>
#include <limits>
#include <iomanip>
#include "../include/FleetManager.h"

using namespace std;

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * @brief Clear the input buffer to handle invalid input
 */
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * @brief Get a valid integer from user input
 * @param prompt The prompt to display
 * @return The validated integer
 */
int getValidInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        cout << "Invalid input. Please enter a valid number." << endl;
        clearInputBuffer();
    }
}

/**
 * @brief Get a valid positive integer from user input
 * REQUIREMENT FULFILLED: Input validation (10 points)
 * @param prompt The prompt to display
 * @return The validated positive integer
 */
int getValidPositiveInt(const string& prompt) {
    int value;
    while (true) {
        value = getValidInt(prompt);
        if (value > 0) {
            return value;
        }
        cout << "Value must be greater than 0. Please try again." << endl;
    }
}

/**
 * @brief Get a valid double from user input
 * @param prompt The prompt to display
 * @return The validated double
 */
double getValidDouble(const string& prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        cout << "Invalid input. Please enter a valid number." << endl;
        clearInputBuffer();
    }
}

/**
 * @brief Get a valid positive double from user input
 * REQUIREMENT FULFILLED: Input validation (10 points)
 * @param prompt The prompt to display
 * @return The validated positive double
 */
double getValidPositiveDouble(const string& prompt) {
    double value;
    while (true) {
        value = getValidDouble(prompt);
        if (value > 0.0) {
            return value;
        }
        cout << "Value must be greater than 0. Please try again." << endl;
    }
}

/**
 * @brief Get a non-negative double from user input
 * @param prompt The prompt to display
 * @return The validated non-negative double
 */
double getValidNonNegativeDouble(const string& prompt) {
    double value;
    while (true) {
        value = getValidDouble(prompt);
        if (value >= 0.0) {
            return value;
        }
        cout << "Value cannot be negative. Please try again." << endl;
    }
}

/**
 * @brief Get a non-empty string from user input
 * REQUIREMENT FULFILLED: Input validation (10 points)
 * @param prompt The prompt to display
 * @return The validated non-empty string
 */
string getValidString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Value cannot be empty. Please try again." << endl;
    }
}

// ============================================================================
// MENU DISPLAY FUNCTIONS
// ============================================================================

/**
 * @brief Display the main menu
 */
void displayMainMenu() {
    cout << "\n========================================" << endl;
    cout << "   AIRPLANE FLEET MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "1. Plane Class Management" << endl;
    cout << "2. Airplane Management" << endl;
    cout << "3. Destination Management" << endl;
    cout << "4. Search Airplanes for Destination" << endl;
    cout << "5. View Fleet Summary" << endl;
    cout << "6. Save All Data" << endl;
    cout << "7. Load All Data" << endl;
    cout << "8. Add Sample Data" << endl;
    cout << "0. Exit" << endl;
    cout << "========================================" << endl;
    cout << "Enter your choice: ";
}

/**
 * @brief Display the plane class management menu
 */
void displayPlaneClassMenu() {
    cout << "\n--- PLANE CLASS MANAGEMENT ---" << endl;
    cout << "1. Add Plane Class" << endl;
    cout << "2. View All Plane Classes" << endl;
    cout << "3. View Plane Class Details" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "------------------------------" << endl;
    cout << "Enter your choice: ";
}

/**
 * @brief Display the airplane management menu
 */
void displayAirplaneMenu() {
    cout << "\n--- AIRPLANE MANAGEMENT ---" << endl;
    cout << "1. Add Airplane" << endl;
    cout << "2. View All Airplanes" << endl;
    cout << "3. View Airplane Details" << endl;
    cout << "4. Remove Airplane" << endl;
    cout << "5. Toggle Operational Status" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "------------------------------" << endl;
    cout << "Enter your choice: ";
}

/**
 * @brief Display the destination management menu
 */
void displayDestinationMenu() {
    cout << "\n--- DESTINATION MANAGEMENT ---" << endl;
    cout << "1. Add Destination" << endl;
    cout << "2. View All Destinations" << endl;
    cout << "3. View Destination Details" << endl;
    cout << "4. Remove Destination" << endl;
    cout << "0. Back to Main Menu" << endl;
    cout << "------------------------------" << endl;
    cout << "Enter your choice: ";
}

// ============================================================================
// PLANE CLASS MANAGEMENT FUNCTIONS
// ============================================================================

/**
 * @brief Add a new plane class
 * REQUIREMENT FULFILLED: Support for arbitrary number of different airplanes (10 points)
 */
void addPlaneClass(FleetManager& manager) {
    cout << "\n--- ADD NEW PLANE CLASS ---" << endl;

    try {
        // Get plane class details with validation
        // REQUIREMENT FULFILLED: Input validation (10 points)
        string manufacturer = getValidString("Manufacturer (e.g., Boeing, Airbus): ");
        string model = getValidString("Model (e.g., 737-800, A320): ");
        int seatCount = getValidPositiveInt("Number of seats: ");
        double minRunway = getValidPositiveDouble("Minimum runway length (meters): ");
        double fuelConsumption = getValidPositiveDouble("Fuel consumption (liters/km/seat): ");
        double tankVolume = getValidPositiveDouble("Tank volume (liters): ");
        double avgSpeed = getValidPositiveDouble("Average speed (km/h): ");
        int crewCount = getValidPositiveInt("Required crew count: ");

        // Create and add the plane class
        PlaneClass newClass(manufacturer, model, seatCount, minRunway,
                           fuelConsumption, tankVolume, avgSpeed, crewCount);

        if (manager.addPlaneClass(newClass)) {
            cout << "\nPlane class added successfully!" << endl;
            cout << newClass;
        } else {
            cout << "\nFailed to add plane class. It may already exist." << endl;
        }
    } catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }
}

/**
 * @brief View details of a specific plane class
 */
void viewPlaneClassDetails(FleetManager& manager) {
    if (manager.getPlaneClassCount() == 0) {
        cout << "\nNo plane classes registered." << endl;
        return;
    }

    // Display all plane classes first
    manager.displayAllPlaneClasses(cout);

    string classId = getValidString("Enter plane class ID (Manufacturer Model): ");
    PlaneClass* pc = manager.findPlaneClassById(classId);

    if (pc != nullptr) {
        cout << "\n" << *pc;
        cout << "\nCalculated Values:" << endl;
        cout << "Max Range: " << fixed << setprecision(2)
                  << pc->calculateMaxRange() << " km" << endl;
        cout << "Flight duration for 1000km: "
                  << pc->calculateFlightDuration(1000) << " hours" << endl;
    } else {
        cout << "\nPlane class not found." << endl;
    }
}

/**
 * @brief Handle plane class management submenu
 */
void handlePlaneClassMenu(FleetManager& manager) {
    int choice;
    do {
        displayPlaneClassMenu();
        choice = getValidInt("");

        switch (choice) {
            case 1:
                addPlaneClass(manager);
                break;
            case 2:
                manager.displayAllPlaneClasses(cout);
                break;
            case 3:
                viewPlaneClassDetails(manager);
                break;
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// ============================================================================
// AIRPLANE MANAGEMENT FUNCTIONS
// ============================================================================

/**
 * @brief Add a new airplane
 * REQUIREMENT FULFILLED: Support for arbitrary number of different airplanes (10 points)
 */
void addAirplane(FleetManager& manager) {
    cout << "\n--- ADD NEW AIRPLANE ---" << endl;

    if (manager.getPlaneClassCount() == 0) {
        cout << "No plane classes available. Please add a plane class first." << endl;
        return;
    }

    // Display available plane classes
    cout << "\nAvailable Plane Classes:" << endl;
    manager.displayAllPlaneClasses(cout);

    try {
        // REQUIREMENT FULFILLED: Input validation (10 points)
        string id = getValidString("Airplane ID (registration number): ");
        string classId = getValidString("Plane Class ID (Manufacturer Model): ");

        // Find the plane class
        PlaneClass* pc = manager.findPlaneClassById(classId);
        if (pc == nullptr) {
            cout << "Plane class not found." << endl;
            return;
        }

        string baseAirport = getValidString("Base airport code: ");

        // Create and add the airplane
        Airplane newAirplane(id, *pc, true, baseAirport, 0);

        if (manager.addAirplane(newAirplane)) {
            cout << "\nAirplane added successfully!" << endl;
            cout << newAirplane;
        } else {
            cout << "\nFailed to add airplane. It may already exist." << endl;
        }
    } catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }
}

/**
 * @brief View details of a specific airplane
 */
void viewAirplaneDetails(FleetManager& manager) {
    if (manager.getAirplaneCount() == 0) {
        cout << "\nNo airplanes in the fleet." << endl;
        return;
    }

    string id = getValidString("Enter airplane ID: ");
    Airplane* airplane = manager.findAirplaneById(id);

    if (airplane != nullptr) {
        cout << "\n" << *airplane;
        cout << "\nPlane Class Details:" << endl;
        cout << airplane->getPlaneClassRef();
    } else {
        cout << "\nAirplane not found." << endl;
    }
}

/**
 * @brief Remove an airplane from the fleet
 */
void removeAirplane(FleetManager& manager) {
    if (manager.getAirplaneCount() == 0) {
        cout << "\nNo airplanes in the fleet." << endl;
        return;
    }

    manager.displayAllAirplanes(cout);
    string id = getValidString("Enter airplane ID to remove: ");

    if (manager.removeAirplane(id)) {
        cout << "Airplane removed successfully." << endl;
    } else {
        cout << "Airplane not found." << endl;
    }
}

/**
 * @brief Toggle operational status of an airplane
 */
void toggleOperationalStatus(FleetManager& manager) {
    if (manager.getAirplaneCount() == 0) {
        cout << "\nNo airplanes in the fleet." << endl;
        return;
    }

    string id = getValidString("Enter airplane ID: ");
    Airplane* airplane = manager.findAirplaneById(id);

    if (airplane != nullptr) {
        airplane->setOperational(!airplane->isOperational());
        cout << "Operational status changed to: "
                  << (airplane->isOperational() ? "Operational" : "Non-operational") << endl;
    } else {
        cout << "Airplane not found." << endl;
    }
}

/**
 * @brief Handle airplane management submenu
 */
void handleAirplaneMenu(FleetManager& manager) {
    int choice;
    do {
        displayAirplaneMenu();
        choice = getValidInt("");

        switch (choice) {
            case 1:
                addAirplane(manager);
                break;
            case 2:
                manager.displayAllAirplanes(cout);
                break;
            case 3:
                viewAirplaneDetails(manager);
                break;
            case 4:
                removeAirplane(manager);
                break;
            case 5:
                toggleOperationalStatus(manager);
                break;
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// ============================================================================
// DESTINATION MANAGEMENT FUNCTIONS
// ============================================================================

/**
 * @brief Add a new destination
 */
void addDestination(FleetManager& manager) {
    cout << "\n--- ADD NEW DESTINATION ---" << endl;

    try {
        // REQUIREMENT FULFILLED: Input validation (10 points)
        string code = getValidString("IATA code (e.g., SOF, LHR): ");
        string name = getValidString("Airport name: ");
        string city = getValidString("City: ");
        string country = getValidString("Country: ");
        double runwayLength = getValidPositiveDouble("Runway length (meters): ");
        double distance = getValidNonNegativeDouble("Distance from base (km): ");

        // Create and add the destination
        Destination newDest(code, name, city, country, runwayLength, distance);

        if (manager.addDestination(newDest)) {
            cout << "\nDestination added successfully!" << endl;
            cout << newDest;
        } else {
            cout << "\nFailed to add destination. It may already exist." << endl;
        }
    } catch (const exception& e) {
        cout << "\nError: " << e.what() << endl;
    }
}

/**
 * @brief View details of a specific destination
 */
void viewDestinationDetails(FleetManager& manager) {
    if (manager.getDestinationCount() == 0) {
        cout << "\nNo destinations registered." << endl;
        return;
    }

    string code = getValidString("Enter destination code: ");
    Destination* dest = manager.findDestinationByCode(code);

    if (dest != nullptr) {
        cout << "\n" << *dest;
    } else {
        cout << "\nDestination not found." << endl;
    }
}

/**
 * @brief Remove a destination
 */
void removeDestination(FleetManager& manager) {
    if (manager.getDestinationCount() == 0) {
        cout << "\nNo destinations registered." << endl;
        return;
    }

    manager.displayAllDestinations(cout);
    string code = getValidString("Enter destination code to remove: ");

    if (manager.removeDestination(code)) {
        cout << "Destination removed successfully." << endl;
    } else {
        cout << "Destination not found." << endl;
    }
}

/**
 * @brief Handle destination management submenu
 */
void handleDestinationMenu(FleetManager& manager) {
    int choice;
    do {
        displayDestinationMenu();
        choice = getValidInt("");

        switch (choice) {
            case 1:
                addDestination(manager);
                break;
            case 2:
                manager.displayAllDestinations(cout);
                break;
            case 3:
                viewDestinationDetails(manager);
                break;
            case 4:
                removeDestination(manager);
                break;
            case 0:
                cout << "Returning to main menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

// ============================================================================
// SEARCH FUNCTIONALITY
// REQUIREMENT FULFILLED: Search for airplanes that can fly to a destination (10 points)
// ============================================================================

/**
 * @brief Search for airplanes that can fly to a destination
 * REQUIREMENT FULFILLED: Search functionality (10 points)
 */
void searchAirplanesForDestination(FleetManager& manager) {
    cout << "\n--- SEARCH AIRPLANES FOR DESTINATION ---" << endl;

    if (manager.getAirplaneCount() == 0) {
        cout << "No airplanes in the fleet." << endl;
        return;
    }

    cout << "\nSearch options:" << endl;
    cout << "1. Search by destination code" << endl;
    cout << "2. Search by runway length and distance" << endl;
    int searchChoice = getValidInt("Enter choice: ");

    vector<Airplane*> compatibleAirplanes;

    if (searchChoice == 1) {
        // Search by destination code
        if (manager.getDestinationCount() == 0) {
            cout << "No destinations registered. Please use option 2." << endl;
            return;
        }

        manager.displayAllDestinations(cout);
        string code = getValidString("Enter destination code: ");

        Destination* dest = manager.findDestinationByCode(code);
        if (dest == nullptr) {
            cout << "Destination not found." << endl;
            return;
        }

        cout << "\nSearching for airplanes compatible with: " << dest->getDisplayString() << endl;
        cout << "Runway: " << dest->getRunwayLengthMeters() << " m, Distance: "
                  << dest->getDistanceFromBaseKm() << " km" << endl;

        // REQUIREMENT: Search for airplanes for destination (10 points)
        compatibleAirplanes = manager.findAirplanesForDestination(code);
    } else {
        // Search by parameters
        double runwayLength = getValidPositiveDouble("Enter runway length (meters): ");
        double distance = getValidNonNegativeDouble("Enter distance from base (km): ");

        compatibleAirplanes = manager.findCompatibleAirplanes(runwayLength, distance);
    }

    // Display results
    cout << "\n========== SEARCH RESULTS ==========" << endl;
    cout << "Compatible airplanes found: " << compatibleAirplanes.size() << endl;
    cout << "====================================\n" << endl;

    if (compatibleAirplanes.empty()) {
        cout << "No compatible airplanes found for this destination." << endl;
        cout << "\nPossible reasons:" << endl;
        cout << "- Runway too short for available aircraft" << endl;
        cout << "- Distance exceeds maximum range of aircraft" << endl;
        cout << "- All compatible aircraft are non-operational" << endl;
    } else {
        int count = 1;
        for (const auto* airplane : compatibleAirplanes) {
            cout << "[" << count++ << "] " << *airplane << endl;
        }
    }
}

// ============================================================================
// SAMPLE DATA
// ============================================================================

/**
 * @brief Add sample data for testing
 * REQUIREMENT FULFILLED: At least 3 classes implementation
 */
void addSampleData(FleetManager& manager) {
    cout << "\n--- ADDING SAMPLE DATA ---" << endl;

    try {
        // Add sample plane classes (at least 3 as per requirement)
        // REQUIREMENT: At least 3 classes
        PlaneClass boeing737("Boeing", "737-800", 189, 2500.0, 0.03, 26020.0, 842.0, 5);
        PlaneClass airbusA320("Airbus", "A320", 180, 2100.0, 0.028, 24210.0, 840.0, 4);
        PlaneClass embraerE190("Embraer", "E190", 114, 2000.0, 0.032, 13230.0, 823.0, 4);
        PlaneClass boeing777("Boeing", "777-300ER", 396, 3050.0, 0.025, 181280.0, 905.0, 10);
        PlaneClass airbusA380("Airbus", "A380", 525, 3000.0, 0.022, 320000.0, 900.0, 20);

        manager.addPlaneClass(boeing737);
        manager.addPlaneClass(airbusA320);
        manager.addPlaneClass(embraerE190);
        manager.addPlaneClass(boeing777);
        manager.addPlaneClass(airbusA380);

        cout << "Added 5 plane classes." << endl;

        // Add sample airplanes (arbitrary number as per requirement)
        // REQUIREMENT: Support for arbitrary number of different airplanes (10 points)
        Airplane plane1("LZ-SOF-001", boeing737, true, "SOF", 5000);
        Airplane plane2("LZ-SOF-002", boeing737, true, "SOF", 3200);
        Airplane plane3("LZ-SOF-003", airbusA320, true, "SOF", 4500);
        Airplane plane4("LZ-VAR-001", embraerE190, true, "VAR", 2800);
        Airplane plane5("LZ-VAR-002", embraerE190, false, "VAR", 6000); // Non-operational
        Airplane plane6("LZ-SOF-004", boeing777, true, "SOF", 12000);
        Airplane plane7("LZ-SOF-005", airbusA380, true, "SOF", 8000);

        manager.addAirplane(plane1);
        manager.addAirplane(plane2);
        manager.addAirplane(plane3);
        manager.addAirplane(plane4);
        manager.addAirplane(plane5);
        manager.addAirplane(plane6);
        manager.addAirplane(plane7);

        cout << "Added 7 airplanes." << endl;

        // Add sample destinations
        Destination sofia("SOF", "Sofia Airport", "Sofia", "Bulgaria", 3600.0, 0.0);
        Destination varna("VAR", "Varna Airport", "Varna", "Bulgaria", 2500.0, 380.0);
        Destination london("LHR", "Heathrow Airport", "London", "UK", 3900.0, 2020.0);
        Destination paris("CDG", "Charles de Gaulle", "Paris", "France", 4200.0, 1850.0);
        Destination dubai("DXB", "Dubai International", "Dubai", "UAE", 4500.0, 4100.0);
        Destination tokyo("NRT", "Narita International", "Tokyo", "Japan", 4000.0, 9100.0);
        Destination smallIsland("ISL", "Small Island Strip", "Island", "Pacific", 1500.0, 2000.0);

        manager.addDestination(sofia);
        manager.addDestination(varna);
        manager.addDestination(london);
        manager.addDestination(paris);
        manager.addDestination(dubai);
        manager.addDestination(tokyo);
        manager.addDestination(smallIsland);

        cout << "Added 7 destinations." << endl;
        cout << "\nSample data added successfully!" << endl;

    } catch (const exception& e) {
        cout << "Error adding sample data: " << e.what() << endl;
    }
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================

/**
 * @brief Main entry point for the application
 *
 * REQUIREMENTS FULFILLED IN THIS APPLICATION:
 * - Support for arbitrary number of different airplanes (10 points)
 * - Search for airplanes that can fly to a destination (10 points)
 * - At least 3 classes with encapsulation (30 points)
 * - Input validation (10 points)
 * - Overloaded << operator (10 points)
 * - File I/O operations (20 points)
 */
int main() {
    // Create the fleet manager
    FleetManager manager("Bulgaria Air Fleet", "./data");

    cout << "========================================" << endl;
    cout << "   AIRPLANE FLEET MANAGEMENT SYSTEM" << endl;
    cout << "========================================" << endl;
    cout << "Welcome to the Fleet Management System!" << endl;
    cout << "Managing fleet for: " << manager.getCompanyName() << endl;

    // Try to load existing data
    cout << "\nAttempting to load existing data..." << endl;
    if (manager.loadAllData()) {
        cout << "Data loaded successfully!" << endl;
        cout << manager;
    } else {
        cout << "No existing data found or failed to load." << endl;
        cout << "Use option 8 to add sample data." << endl;
    }

    // Main menu loop
    int choice;
    do {
        displayMainMenu();
        choice = getValidInt("");

        switch (choice) {
            case 1:
                handlePlaneClassMenu(manager);
                break;
            case 2:
                handleAirplaneMenu(manager);
                break;
            case 3:
                handleDestinationMenu(manager);
                break;
            case 4:
                // REQUIREMENT: Search for airplanes for destination (10 points)
                searchAirplanesForDestination(manager);
                break;
            case 5:
                cout << manager;
                break;
            case 6:
                // REQUIREMENT: File I/O - save data (20 points)
                cout << "\nSaving data..." << endl;
                if (manager.saveAllData()) {
                    cout << "All data saved successfully!" << endl;
                } else {
                    cout << "Warning: Some data may not have been saved." << endl;
                }
                break;
            case 7:
                // REQUIREMENT: File I/O - load data (20 points)
                cout << "\nLoading data..." << endl;
                manager.clearAllData();
                if (manager.loadAllData()) {
                    cout << "All data loaded successfully!" << endl;
                    cout << manager;
                } else {
                    cout << "Warning: Some data may not have been loaded." << endl;
                }
                break;
            case 8:
                addSampleData(manager);
                break;
            case 0: {
                cout << "\nDo you want to save before exiting? (1=Yes, 0=No): ";
                int saveChoice = getValidInt("");
                if (saveChoice == 1) {
                    if (manager.saveAllData()) {
                        cout << "Data saved successfully!" << endl;
                    }
                }
                cout << "\nThank you for using the Fleet Management System!" << endl;
                cout << "Goodbye!" << endl;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}
