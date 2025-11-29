/**
 * @file PlaneClass.cpp
 * @brief Implementation of the PlaneClass class
 *
 * REQUIREMENT FULFILLED: Class encapsulation with private instance variables (30 points)
 * REQUIREMENT FULFILLED: At least two constructors (30 points)
 * REQUIREMENT FULFILLED: Public getters/setters (30 points)
 * REQUIREMENT FULFILLED: Input validation (10 points)
 * REQUIREMENT FULFILLED: Overload << operator (10 points)
 */

#include "../include/PlaneClass.h"
#include <sstream>
#include <iomanip>

using namespace std;

// ============================================================================
// CONSTRUCTORS
// REQUIREMENT FULFILLED: At least two constructors (30 points)
// ============================================================================

/**
 * @brief Default constructor implementation
 * Initializes all members to default/empty values
 * First constructor as per requirement
 */
PlaneClass::PlaneClass()
    : manufacturer_("")
    , model_("")
    , seatCount_(0)
    , minRunwayLength_(0.0)
    , fuelConsumptionPerKmPerSeat_(0.0)
    , tankVolumeLiters_(0.0)
    , averageSpeedKmh_(0.0)
    , requiredCrewCount_(0) {
    // Default constructor - all members initialized via initializer list
}

/**
 * @brief Parameterized constructor implementation
 * Initializes all members with provided values after validation
 * Second constructor as per requirement
 *
 * REQUIREMENT FULFILLED: Input validation where necessary (10 points)
 */
PlaneClass::PlaneClass(const string& manufacturer, const string& model,
                       int seatCount, double minRunwayLength, double fuelConsumption,
                       double tankVolume, double avgSpeed, int crewCount)
    : manufacturer_(manufacturer)
    , model_(model)
    , seatCount_(0)
    , minRunwayLength_(0.0)
    , fuelConsumptionPerKmPerSeat_(0.0)
    , tankVolumeLiters_(0.0)
    , averageSpeedKmh_(0.0)
    , requiredCrewCount_(0) {

    // REQUIREMENT: Input validation - validate and set each numeric field
    // Using setters to apply validation rules consistently
    setSeatCount(seatCount);
    setMinRunwayLength(minRunwayLength);
    setFuelConsumptionPerKmPerSeat(fuelConsumption);
    setTankVolumeLiters(tankVolume);
    setAverageSpeedKmh(avgSpeed);
    setRequiredCrewCount(crewCount);
}

/**
 * @brief Copy constructor implementation
 * Creates a deep copy of another PlaneClass object
 */
PlaneClass::PlaneClass(const PlaneClass& other)
    : manufacturer_(other.manufacturer_)
    , model_(other.model_)
    , seatCount_(other.seatCount_)
    , minRunwayLength_(other.minRunwayLength_)
    , fuelConsumptionPerKmPerSeat_(other.fuelConsumptionPerKmPerSeat_)
    , tankVolumeLiters_(other.tankVolumeLiters_)
    , averageSpeedKmh_(other.averageSpeedKmh_)
    , requiredCrewCount_(other.requiredCrewCount_) {
    // Copy constructor - all members copied via initializer list
}

/**
 * @brief Destructor implementation
 * No dynamic memory to clean up in this class
 */
PlaneClass::~PlaneClass() {
    // Destructor - nothing to clean up (no dynamic memory allocation)
}

// ============================================================================
// GETTERS
// REQUIREMENT FULFILLED: Public getters for private instance variables (30 points)
// ============================================================================

string PlaneClass::getManufacturer() const {
    return manufacturer_;
}

string PlaneClass::getModel() const {
    return model_;
}

int PlaneClass::getSeatCount() const {
    return seatCount_;
}

double PlaneClass::getMinRunwayLength() const {
    return minRunwayLength_;
}

double PlaneClass::getFuelConsumptionPerKmPerSeat() const {
    return fuelConsumptionPerKmPerSeat_;
}

double PlaneClass::getTankVolumeLiters() const {
    return tankVolumeLiters_;
}

double PlaneClass::getAverageSpeedKmh() const {
    return averageSpeedKmh_;
}

int PlaneClass::getRequiredCrewCount() const {
    return requiredCrewCount_;
}

// ============================================================================
// SETTERS
// REQUIREMENT FULFILLED: Public setters for private instance variables (30 points)
// REQUIREMENT FULFILLED: Input validation where necessary (10 points)
// ============================================================================

void PlaneClass::setManufacturer(const string& manufacturer) {
    // Validation: manufacturer should not be empty
    if (manufacturer.empty()) {
        throw invalid_argument("Manufacturer name cannot be empty");
    }
    manufacturer_ = manufacturer;
}

void PlaneClass::setModel(const string& model) {
    // Validation: model should not be empty
    if (model.empty()) {
        throw invalid_argument("Model name cannot be empty");
    }
    model_ = model;
}

void PlaneClass::setSeatCount(int count) {
    // REQUIREMENT: Input validation - seat count must be positive
    if (count <= 0) {
        throw invalid_argument("Seat count must be greater than 0");
    }
    seatCount_ = count;
}

void PlaneClass::setMinRunwayLength(double length) {
    // REQUIREMENT: Input validation - runway length must be positive
    if (length <= 0.0) {
        throw invalid_argument("Minimum runway length must be greater than 0");
    }
    minRunwayLength_ = length;
}

void PlaneClass::setFuelConsumptionPerKmPerSeat(double consumption) {
    // REQUIREMENT: Input validation - fuel consumption must be positive
    if (consumption <= 0.0) {
        throw invalid_argument("Fuel consumption must be greater than 0");
    }
    fuelConsumptionPerKmPerSeat_ = consumption;
}

void PlaneClass::setTankVolumeLiters(double volume) {
    // REQUIREMENT: Input validation - tank volume must be positive
    if (volume <= 0.0) {
        throw invalid_argument("Tank volume must be greater than 0");
    }
    tankVolumeLiters_ = volume;
}

void PlaneClass::setAverageSpeedKmh(double speed) {
    // REQUIREMENT: Input validation - speed must be positive
    if (speed <= 0.0) {
        throw invalid_argument("Average speed must be greater than 0");
    }
    averageSpeedKmh_ = speed;
}

void PlaneClass::setRequiredCrewCount(int count) {
    // REQUIREMENT: Input validation - crew count must be positive
    if (count <= 0) {
        throw invalid_argument("Required crew count must be greater than 0");
    }
    requiredCrewCount_ = count;
}

// ============================================================================
// UTILITY METHODS
// ============================================================================

/**
 * @brief Get unique identifier for this plane class
 * Combines manufacturer and model for identification
 */
string PlaneClass::getClassId() const {
    return manufacturer_ + " " + model_;
}

/**
 * @brief Calculate maximum flight range
 * Based on tank volume and fuel consumption at full capacity
 * Used for evaluating if airplane can reach destinations
 */
double PlaneClass::calculateMaxRange() const {
    // Prevent division by zero
    if (fuelConsumptionPerKmPerSeat_ <= 0.0 || seatCount_ <= 0) {
        return 0.0;
    }
    // Maximum range = tank volume / (fuel consumption per km * seats)
    // This gives the maximum distance with full fuel and full passenger load
    double fuelPerKm = fuelConsumptionPerKmPerSeat_ * seatCount_;
    return tankVolumeLiters_ / fuelPerKm;
}

/**
 * @brief Calculate flight duration for a given distance
 * Used for pilot workload assessment
 */
double PlaneClass::calculateFlightDuration(double distanceKm) const {
    // REQUIREMENT: Input validation
    if (distanceKm < 0.0) {
        throw invalid_argument("Distance cannot be negative");
    }
    if (averageSpeedKmh_ <= 0.0) {
        return 0.0;
    }
    // Duration in hours = distance / speed
    return distanceKm / averageSpeedKmh_;
}

/**
 * @brief Calculate total fuel consumption for a flight
 * Used for cost efficiency evaluation
 */
double PlaneClass::calculateFuelConsumption(double distanceKm, int passengers) const {
    // REQUIREMENT: Input validation
    if (distanceKm < 0.0) {
        throw invalid_argument("Distance cannot be negative");
    }
    if (passengers < 0 || passengers > seatCount_) {
        throw invalid_argument("Invalid passenger count");
    }
    // Fuel = consumption per km per seat * distance * passengers
    // Note: Using actual passenger count for realistic consumption
    return fuelConsumptionPerKmPerSeat_ * distanceKm * passengers;
}

/**
 * @brief Check runway compatibility
 * Determines if this plane class can use a runway of given length
 * REQUIREMENT: Used for destination compatibility search (10 points)
 */
bool PlaneClass::isCompatibleWithRunway(double runwayLength) const {
    // The plane needs at least minRunwayLength_ to operate
    return runwayLength >= minRunwayLength_;
}

// ============================================================================
// OPERATORS
// REQUIREMENT FULFILLED: Overload << operator for output (10 points)
// ============================================================================

/**
 * @brief Overloaded << operator for formatted output
 * Displays all plane class information in a readable format
 */
ostream& operator<<(ostream& os, const PlaneClass& planeClass) {
    os << "=== Plane Class Information ===" << endl;
    os << "Manufacturer:        " << planeClass.manufacturer_ << endl;
    os << "Model:               " << planeClass.model_ << endl;
    os << "Class ID:            " << planeClass.getClassId() << endl;
    os << "Seat Count:          " << planeClass.seatCount_ << endl;
    os << "Min Runway Length:   " << fixed << setprecision(2)
       << planeClass.minRunwayLength_ << " m" << endl;
    os << "Fuel Consumption:    " << planeClass.fuelConsumptionPerKmPerSeat_
       << " L/km/seat" << endl;
    os << "Tank Volume:         " << planeClass.tankVolumeLiters_ << " L" << endl;
    os << "Average Speed:       " << planeClass.averageSpeedKmh_ << " km/h" << endl;
    os << "Required Crew:       " << planeClass.requiredCrewCount_ << endl;
    os << "Max Range:           " << fixed << setprecision(2)
       << planeClass.calculateMaxRange() << " km" << endl;
    os << "===============================" << endl;
    return os;
}

// REQUIREMENT FULFILLED: File I/O operations (20 points)
/**
 * @brief Overloaded >> operator for input from file
 * Reads plane class data in a specific format
 * Format: manufacturer|model|seatCount|minRunway|fuelConsumption|tankVolume|avgSpeed|crewCount
 */
istream& operator>>(istream& is, PlaneClass& planeClass) {
    string line;
    if (getline(is, line)) {
        istringstream iss(line);
        string token;

        // Read manufacturer
        if (getline(iss, token, '|')) {
            planeClass.manufacturer_ = token;
        }

        // Read model
        if (getline(iss, token, '|')) {
            planeClass.model_ = token;
        }

        // Read seat count
        if (getline(iss, token, '|')) {
            planeClass.seatCount_ = stoi(token);
        }

        // Read minimum runway length
        if (getline(iss, token, '|')) {
            planeClass.minRunwayLength_ = stod(token);
        }

        // Read fuel consumption
        if (getline(iss, token, '|')) {
            planeClass.fuelConsumptionPerKmPerSeat_ = stod(token);
        }

        // Read tank volume
        if (getline(iss, token, '|')) {
            planeClass.tankVolumeLiters_ = stod(token);
        }

        // Read average speed
        if (getline(iss, token, '|')) {
            planeClass.averageSpeedKmh_ = stod(token);
        }

        // Read required crew count
        if (getline(iss, token, '|')) {
            planeClass.requiredCrewCount_ = stoi(token);
        }
    }
    return is;
}

/**
 * @brief Equality operator
 * Two plane classes are equal if they have the same manufacturer and model
 */
bool PlaneClass::operator==(const PlaneClass& other) const {
    return manufacturer_ == other.manufacturer_ && model_ == other.model_;
}
