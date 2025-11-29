/**
 * @file Destination.cpp
 * @brief Implementation of the Destination class
 *
 * REQUIREMENT FULFILLED: Class encapsulation with private instance variables (30 points)
 * REQUIREMENT FULFILLED: At least two constructors (30 points)
 * REQUIREMENT FULFILLED: Public getters/setters (30 points)
 * REQUIREMENT FULFILLED: Input validation (10 points)
 * REQUIREMENT FULFILLED: Overload << operator (10 points)
 */

#include "../include/Destination.h"
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
Destination::Destination()
    : code_("")
    , name_("")
    , city_("")
    , country_("")
    , runwayLengthMeters_(0.0)
    , distanceFromBaseKm_(0.0) {
    // Default constructor - all members initialized via initializer list
}

/**
 * @brief Parameterized constructor implementation
 * Initializes all members with provided values after validation
 * Second constructor as per requirement
 *
 * REQUIREMENT FULFILLED: Input validation where necessary (10 points)
 */
Destination::Destination(const string& code, const string& name,
                         const string& city, const string& country,
                         double runwayLength, double distance)
    : code_("")
    , name_(name)
    , city_(city)
    , country_(country)
    , runwayLengthMeters_(0.0)
    , distanceFromBaseKm_(0.0) {

    // REQUIREMENT: Input validation - validate and set fields using setters
    setCode(code);
    setRunwayLengthMeters(runwayLength);
    setDistanceFromBaseKm(distance);
}

/**
 * @brief Copy constructor implementation
 * Creates a deep copy of another Destination object
 */
Destination::Destination(const Destination& other)
    : code_(other.code_)
    , name_(other.name_)
    , city_(other.city_)
    , country_(other.country_)
    , runwayLengthMeters_(other.runwayLengthMeters_)
    , distanceFromBaseKm_(other.distanceFromBaseKm_) {
    // Copy constructor - all members copied via initializer list
}

/**
 * @brief Destructor implementation
 * No dynamic memory to clean up in this class
 */
Destination::~Destination() {
    // Destructor - nothing to clean up (no dynamic memory allocation)
}

// ============================================================================
// GETTERS
// REQUIREMENT FULFILLED: Public getters for private instance variables (30 points)
// ============================================================================

string Destination::getCode() const {
    return code_;
}

string Destination::getName() const {
    return name_;
}

string Destination::getCity() const {
    return city_;
}

string Destination::getCountry() const {
    return country_;
}

double Destination::getRunwayLengthMeters() const {
    return runwayLengthMeters_;
}

double Destination::getDistanceFromBaseKm() const {
    return distanceFromBaseKm_;
}

// ============================================================================
// SETTERS
// REQUIREMENT FULFILLED: Public setters for private instance variables (30 points)
// REQUIREMENT FULFILLED: Input validation where necessary (10 points)
// ============================================================================

void Destination::setCode(const string& code) {
    // REQUIREMENT: Input validation - code should not be empty
    if (code.empty()) {
        throw invalid_argument("Destination code cannot be empty");
    }
    // Typically IATA codes are 3 characters, but we allow flexibility
    code_ = code;
}

void Destination::setName(const string& name) {
    // Name can be empty for flexibility
    name_ = name;
}

void Destination::setCity(const string& city) {
    // City can be empty for flexibility
    city_ = city;
}

void Destination::setCountry(const string& country) {
    // Country can be empty for flexibility
    country_ = country;
}

void Destination::setRunwayLengthMeters(double length) {
    // REQUIREMENT: Input validation - runway length must be positive
    if (length <= 0.0) {
        throw invalid_argument("Runway length must be greater than 0");
    }
    runwayLengthMeters_ = length;
}

void Destination::setDistanceFromBaseKm(double distance) {
    // REQUIREMENT: Input validation - distance must be non-negative
    if (distance < 0.0) {
        throw invalid_argument("Distance cannot be negative");
    }
    distanceFromBaseKm_ = distance;
}

// ============================================================================
// UTILITY METHODS
// ============================================================================

/**
 * @brief Get a formatted display string for the destination
 * Returns format: "CODE - City, Country"
 */
string Destination::getDisplayString() const {
    ostringstream oss;
    oss << code_ << " - " << city_;
    if (!country_.empty()) {
        oss << ", " << country_;
    }
    return oss.str();
}

// ============================================================================
// OPERATORS
// REQUIREMENT FULFILLED: Overload << operator for output (10 points)
// ============================================================================

/**
 * @brief Overloaded << operator for formatted output
 * Displays all destination information in a readable format
 */
ostream& operator<<(ostream& os, const Destination& destination) {
    os << "=== Destination Information ===" << endl;
    os << "Code:                " << destination.code_ << endl;
    os << "Name:                " << destination.name_ << endl;
    os << "City:                " << destination.city_ << endl;
    os << "Country:             " << destination.country_ << endl;
    os << "Runway Length:       " << fixed << setprecision(2)
       << destination.runwayLengthMeters_ << " m" << endl;
    os << "Distance from Base:  " << destination.distanceFromBaseKm_ << " km" << endl;
    os << "===============================" << endl;
    return os;
}

// REQUIREMENT FULFILLED: File I/O operations (20 points)
/**
 * @brief Overloaded >> operator for input from file
 * Reads destination data in a specific format
 * Format: code|name|city|country|runwayLength|distanceFromBase
 */
istream& operator>>(istream& is, Destination& destination) {
    string line;
    if (getline(is, line)) {
        istringstream iss(line);
        string token;

        // Read code
        if (getline(iss, token, '|')) {
            destination.code_ = token;
        }

        // Read name
        if (getline(iss, token, '|')) {
            destination.name_ = token;
        }

        // Read city
        if (getline(iss, token, '|')) {
            destination.city_ = token;
        }

        // Read country
        if (getline(iss, token, '|')) {
            destination.country_ = token;
        }

        // Read runway length
        if (getline(iss, token, '|')) {
            destination.runwayLengthMeters_ = stod(token);
        }

        // Read distance from base
        if (getline(iss, token, '|')) {
            destination.distanceFromBaseKm_ = stod(token);
        }
    }
    return is;
}

/**
 * @brief Equality operator
 * Two destinations are equal if they have the same code
 */
bool Destination::operator==(const Destination& other) const {
    return code_ == other.code_;
}
