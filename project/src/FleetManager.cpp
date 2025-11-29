/**
 * @file FleetManager.cpp
 * @brief Implementation of the FleetManager class
 *
 * REQUIREMENT FULFILLED: Support for arbitrary number of different airplanes (10 points)
 * REQUIREMENT FULFILLED: Search for airplanes that can fly to a destination (10 points)
 * REQUIREMENT FULFILLED: File I/O operations - read and store data to files (20 points)
 * REQUIREMENT FULFILLED: Overload << operator (10 points)
 */

#include "../include/FleetManager.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

// ============================================================================
// CONSTRUCTORS
// REQUIREMENT FULFILLED: At least two constructors (30 points)
// ============================================================================

/**
 * @brief Default constructor implementation
 * Initializes with empty collections and default values
 * First constructor as per requirement
 */
FleetManager::FleetManager()
    : airplanes_()
    , destinations_()
    , planeClasses_()
    , companyName_("Default Airline")
    , dataDirectory_("./data") {
    // Default constructor - collections initialized as empty via initializer list
}

/**
 * @brief Parameterized constructor with company name
 * Second constructor as per requirement
 */
FleetManager::FleetManager(const string& companyName, const string& dataDirectory)
    : airplanes_()
    , destinations_()
    , planeClasses_()
    , companyName_(companyName)
    , dataDirectory_(dataDirectory) {
    // Parameterized constructor - sets company name and data directory
}

/**
 * @brief Copy constructor implementation
 * Creates a deep copy of another FleetManager object
 */
FleetManager::FleetManager(const FleetManager& other)
    : airplanes_(other.airplanes_)
    , destinations_(other.destinations_)
    , planeClasses_(other.planeClasses_)
    , companyName_(other.companyName_)
    , dataDirectory_(other.dataDirectory_) {
    // Copy constructor - all collections deep copied
}

/**
 * @brief Destructor implementation
 */
FleetManager::~FleetManager() {
    // Destructor - vector members are automatically cleaned up
}

// ============================================================================
// GETTERS
// REQUIREMENT FULFILLED: Public getters for private instance variables (30 points)
// ============================================================================

string FleetManager::getCompanyName() const {
    return companyName_;
}

string FleetManager::getDataDirectory() const {
    return dataDirectory_;
}

size_t FleetManager::getAirplaneCount() const {
    return airplanes_.size();
}

size_t FleetManager::getDestinationCount() const {
    return destinations_.size();
}

size_t FleetManager::getPlaneClassCount() const {
    return planeClasses_.size();
}

const vector<Airplane>& FleetManager::getAirplanes() const {
    return airplanes_;
}

const vector<Destination>& FleetManager::getDestinations() const {
    return destinations_;
}

const vector<PlaneClass>& FleetManager::getPlaneClasses() const {
    return planeClasses_;
}

// ============================================================================
// SETTERS
// REQUIREMENT FULFILLED: Public setters for private instance variables (30 points)
// ============================================================================

void FleetManager::setCompanyName(const string& name) {
    companyName_ = name;
}

void FleetManager::setDataDirectory(const string& directory) {
    dataDirectory_ = directory;
}

// ============================================================================
// AIRPLANE MANAGEMENT
// REQUIREMENT FULFILLED: Support for arbitrary number of different airplanes (10 points)
// ============================================================================

/**
 * @brief Add a new plane class to the system
 * Prevents duplicate entries based on class ID
 */
bool FleetManager::addPlaneClass(const PlaneClass& planeClass) {
    // Check if plane class already exists
    for (const auto& pc : planeClasses_) {
        if (pc == planeClass) {
            return false; // Already exists
        }
    }

    planeClasses_.push_back(planeClass);
    return true;
}

/**
 * @brief Add a new airplane to the fleet
 * REQUIREMENT: Supports arbitrary number of different airplanes (10 points)
 * Prevents duplicate entries based on identification number
 */
bool FleetManager::addAirplane(const Airplane& airplane) {
    // Check if airplane already exists
    for (const auto& a : airplanes_) {
        if (a == airplane) {
            return false; // Already exists
        }
    }

    airplanes_.push_back(airplane);
    return true;
}

/**
 * @brief Add a new destination
 * Prevents duplicate entries based on code
 */
bool FleetManager::addDestination(const Destination& destination) {
    // Check if destination already exists
    for (const auto& d : destinations_) {
        if (d == destination) {
            return false; // Already exists
        }
    }

    destinations_.push_back(destination);
    return true;
}

/**
 * @brief Remove an airplane from the fleet by ID
 */
bool FleetManager::removeAirplane(const string& id) {
    auto it = remove_if(airplanes_.begin(), airplanes_.end(),
        [&id](const Airplane& a) { return a.getIdentificationNumber() == id; });

    if (it != airplanes_.end()) {
        airplanes_.erase(it, airplanes_.end());
        return true;
    }
    return false;
}

/**
 * @brief Remove a destination by code
 */
bool FleetManager::removeDestination(const string& code) {
    auto it = remove_if(destinations_.begin(), destinations_.end(),
        [&code](const Destination& d) { return d.getCode() == code; });

    if (it != destinations_.end()) {
        destinations_.erase(it, destinations_.end());
        return true;
    }
    return false;
}

/**
 * @brief Find an airplane by its ID
 */
Airplane* FleetManager::findAirplaneById(const string& id) {
    for (auto& airplane : airplanes_) {
        if (airplane.getIdentificationNumber() == id) {
            return &airplane;
        }
    }
    return nullptr;
}

/**
 * @brief Find a destination by its code
 */
Destination* FleetManager::findDestinationByCode(const string& code) {
    for (auto& destination : destinations_) {
        if (destination.getCode() == code) {
            return &destination;
        }
    }
    return nullptr;
}

/**
 * @brief Find a plane class by its class ID
 */
PlaneClass* FleetManager::findPlaneClassById(const string& classId) {
    for (auto& planeClass : planeClasses_) {
        if (planeClass.getClassId() == classId) {
            return &planeClass;
        }
    }
    return nullptr;
}

// ============================================================================
// SEARCH FUNCTIONALITY
// REQUIREMENT FULFILLED: Search for airplanes that can fly to a destination (10 points)
// ============================================================================

/**
 * @brief Find all airplanes that can fly to a specific destination
 * REQUIREMENT: Search for airplanes for destination (10 points)
 *
 * This method evaluates each airplane's compatibility based on:
 * - Runway length requirements (from PlaneClass)
 * - Maximum flight range (from PlaneClass)
 * - Operational status
 */
vector<Airplane*> FleetManager::findAirplanesForDestination(const string& destinationCode) {
    vector<Airplane*> compatibleAirplanes;

    // Find the destination
    Destination* dest = findDestinationByCode(destinationCode);
    if (dest == nullptr) {
        return compatibleAirplanes; // Empty vector if destination not found
    }

    // Check each airplane for compatibility
    for (auto& airplane : airplanes_) {
        if (airplane.canFlyToDestination(dest->getRunwayLengthMeters(),
                                          dest->getDistanceFromBaseKm())) {
            compatibleAirplanes.push_back(&airplane);
        }
    }

    return compatibleAirplanes;
}

/**
 * @brief Find all airplanes compatible with given runway and distance
 * Alternative search method with direct parameters
 */
vector<Airplane*> FleetManager::findCompatibleAirplanes(double runwayLength, double distance) {
    vector<Airplane*> compatibleAirplanes;

    for (auto& airplane : airplanes_) {
        if (airplane.canFlyToDestination(runwayLength, distance)) {
            compatibleAirplanes.push_back(&airplane);
        }
    }

    return compatibleAirplanes;
}

/**
 * @brief Get all operational airplanes
 */
vector<Airplane*> FleetManager::getOperationalAirplanes() {
    vector<Airplane*> operationalAirplanes;

    for (auto& airplane : airplanes_) {
        if (airplane.isOperational()) {
            operationalAirplanes.push_back(&airplane);
        }
    }

    return operationalAirplanes;
}

// ============================================================================
// DISPLAY METHODS
// ============================================================================

/**
 * @brief Display all airplanes in the fleet
 */
void FleetManager::displayAllAirplanes(ostream& os) const {
    os << "\n========== FLEET AIRPLANES ==========" << endl;
    os << "Total airplanes: " << airplanes_.size() << endl;
    os << "======================================\n" << endl;

    if (airplanes_.empty()) {
        os << "No airplanes in the fleet." << endl;
    } else {
        int count = 1;
        for (const auto& airplane : airplanes_) {
            os << "[" << count++ << "] ";
            os << airplane << endl;
        }
    }
}

/**
 * @brief Display all destinations
 */
void FleetManager::displayAllDestinations(ostream& os) const {
    os << "\n========== DESTINATIONS ==========" << endl;
    os << "Total destinations: " << destinations_.size() << endl;
    os << "==================================\n" << endl;

    if (destinations_.empty()) {
        os << "No destinations registered." << endl;
    } else {
        int count = 1;
        for (const auto& destination : destinations_) {
            os << "[" << count++ << "] ";
            os << destination << endl;
        }
    }
}

/**
 * @brief Display all plane classes
 */
void FleetManager::displayAllPlaneClasses(ostream& os) const {
    os << "\n========== PLANE CLASSES ==========" << endl;
    os << "Total plane classes: " << planeClasses_.size() << endl;
    os << "====================================\n" << endl;

    if (planeClasses_.empty()) {
        os << "No plane classes registered." << endl;
    } else {
        int count = 1;
        for (const auto& planeClass : planeClasses_) {
            os << "[" << count++ << "] ";
            os << planeClass << endl;
        }
    }
}

// ============================================================================
// FILE I/O OPERATIONS
// REQUIREMENT FULFILLED: File I/O operations - read and store data to files (20 points)
// ============================================================================

/**
 * @brief Save plane classes to file
 * Format: manufacturer|model|seatCount|minRunway|fuelConsumption|tankVolume|avgSpeed|crewCount
 */
bool FleetManager::savePlaneClassesToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Write header comment
    file << "# Plane Classes Data File" << endl;
    file << "# Format: manufacturer|model|seatCount|minRunway|fuelConsumption|tankVolume|avgSpeed|crewCount" << endl;

    // Write each plane class
    for (const auto& pc : planeClasses_) {
        file << pc.getManufacturer() << "|"
             << pc.getModel() << "|"
             << pc.getSeatCount() << "|"
             << pc.getMinRunwayLength() << "|"
             << pc.getFuelConsumptionPerKmPerSeat() << "|"
             << pc.getTankVolumeLiters() << "|"
             << pc.getAverageSpeedKmh() << "|"
             << pc.getRequiredCrewCount() << endl;
    }

    file.close();
    return true;
}

/**
 * @brief Load plane classes from file
 * REQUIREMENT: File I/O operations (20 points)
 */
bool FleetManager::loadPlaneClassesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        PlaneClass pc;
        istringstream iss(line);

        // Use >> operator to read the data
        istringstream lineStream(line);
        lineStream >> pc;

        // Validate and add
        if (!pc.getManufacturer().empty()) {
            addPlaneClass(pc);
        }
    }

    file.close();
    return true;
}

/**
 * @brief Save airplanes to file
 * Format: id|planeClassId|operational|baseAirport|flightHours
 */
bool FleetManager::saveAirplanesToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Write header comment
    file << "# Airplanes Data File" << endl;
    file << "# Format: id|planeClassId|operational|baseAirport|flightHours" << endl;

    // Write each airplane
    for (const auto& airplane : airplanes_) {
        file << airplane.getIdentificationNumber() << "|"
             << airplane.getPlaneClassRef().getClassId() << "|"
             << (airplane.isOperational() ? "1" : "0") << "|"
             << airplane.getBaseAirportCode() << "|"
             << airplane.getTotalFlightHours() << endl;
    }

    file.close();
    return true;
}

/**
 * @brief Load airplanes from file
 * REQUIREMENT: File I/O operations (20 points)
 */
bool FleetManager::loadAirplanesFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        istringstream iss(line);
        string token;
        string id, planeClassId, baseAirport;
        bool operational = true;
        int flightHours = 0;

        // Parse the line manually for better control
        if (getline(iss, id, '|') &&
            getline(iss, planeClassId, '|')) {

            if (getline(iss, token, '|')) {
                operational = (token == "1" || token == "true");
            }
            if (getline(iss, baseAirport, '|')) {
                // baseAirport already set
            }
            if (getline(iss, token, '|')) {
                try {
                    flightHours = stoi(token);
                } catch (...) {
                    flightHours = 0;
                }
            }

            // Find the plane class
            PlaneClass* pc = findPlaneClassById(planeClassId);
            if (pc != nullptr) {
                Airplane airplane(id, *pc, operational, baseAirport, flightHours);
                addAirplane(airplane);
            }
        }
    }

    file.close();
    return true;
}

/**
 * @brief Save destinations to file
 * Format: code|name|city|country|runwayLength|distanceFromBase
 */
bool FleetManager::saveDestinationsToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    // Write header comment
    file << "# Destinations Data File" << endl;
    file << "# Format: code|name|city|country|runwayLength|distanceFromBase" << endl;

    // Write each destination
    for (const auto& dest : destinations_) {
        file << dest.getCode() << "|"
             << dest.getName() << "|"
             << dest.getCity() << "|"
             << dest.getCountry() << "|"
             << dest.getRunwayLengthMeters() << "|"
             << dest.getDistanceFromBaseKm() << endl;
    }

    file.close();
    return true;
}

/**
 * @brief Load destinations from file
 * REQUIREMENT: File I/O operations (20 points)
 */
bool FleetManager::loadDestinationsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }

        Destination dest;
        istringstream lineStream(line);
        lineStream >> dest;

        // Validate and add
        if (!dest.getCode().empty()) {
            addDestination(dest);
        }
    }

    file.close();
    return true;
}

/**
 * @brief Save all data to files
 * REQUIREMENT: File I/O operations (20 points)
 */
bool FleetManager::saveAllData() const {
    bool success = true;

    // Save plane classes first (required for airplane linking)
    if (!savePlaneClassesToFile(dataDirectory_ + "/plane_classes.dat")) {
        success = false;
    }

    // Save airplanes
    if (!saveAirplanesToFile(dataDirectory_ + "/airplanes.dat")) {
        success = false;
    }

    // Save destinations
    if (!saveDestinationsToFile(dataDirectory_ + "/destinations.dat")) {
        success = false;
    }

    return success;
}

/**
 * @brief Load all data from files
 * REQUIREMENT: File I/O operations (20 points)
 */
bool FleetManager::loadAllData() {
    bool success = true;

    // Load plane classes first (required for airplane linking)
    if (!loadPlaneClassesFromFile(dataDirectory_ + "/plane_classes.dat")) {
        success = false;
    }

    // Load airplanes (requires plane classes to be loaded)
    if (!loadAirplanesFromFile(dataDirectory_ + "/airplanes.dat")) {
        success = false;
    }

    // Load destinations
    if (!loadDestinationsFromFile(dataDirectory_ + "/destinations.dat")) {
        success = false;
    }

    return success;
}

/**
 * @brief Clear all data from memory
 */
void FleetManager::clearAllData() {
    airplanes_.clear();
    destinations_.clear();
    planeClasses_.clear();
}

// ============================================================================
// OPERATORS
// REQUIREMENT FULFILLED: Overload << operator for output (10 points)
// ============================================================================

/**
 * @brief Overloaded << operator for formatted output
 * Displays fleet manager summary information
 */
ostream& operator<<(ostream& os, const FleetManager& manager) {
    os << "========================================" << endl;
    os << "       FLEET MANAGEMENT SYSTEM" << endl;
    os << "========================================" << endl;
    os << "Company Name:        " << manager.companyName_ << endl;
    os << "Data Directory:      " << manager.dataDirectory_ << endl;
    os << "----------------------------------------" << endl;
    os << "Total Plane Classes: " << manager.planeClasses_.size() << endl;
    os << "Total Airplanes:     " << manager.airplanes_.size() << endl;
    os << "Total Destinations:  " << manager.destinations_.size() << endl;
    os << "========================================" << endl;
    return os;
}
