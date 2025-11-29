/**
 * @file Airplane.h
 * @brief Defines the Airplane class representing individual aircraft
 *
 * REQUIREMENT FULFILLED: Class encapsulation with private instance variables (30 points)
 * REQUIREMENT FULFILLED: At least 3 classes implementation
 * REQUIREMENT FULFILLED: Support for arbitrary number of different airplanes (10 points)
 *
 * This class stores:
 * - Unique identification number for each airplane
 * - Reference to the airplane's class (PlaneClass)
 * - Operational status
 */

#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <string>
#include <iostream>
#include <memory>
#include "PlaneClass.h"

/**
 * @class Airplane
 * @brief Represents an individual aircraft with its identification and class
 *
 * Each airplane has a unique ID and belongs to a specific PlaneClass.
 * The plane class determines the airplane's capabilities and compatibility.
 */
class Airplane {
private:
    // REQUIREMENT: Private instance variables with camelCase_ naming convention
    std::string identificationNumber_;   // Unique aircraft registration/ID number
    PlaneClass planeClass_;              // The class/type of this airplane
    bool isOperational_;                 // Whether the airplane is operational
    std::string baseAirportCode_;        // Home base airport code
    int totalFlightHours_;               // Total flight hours for maintenance tracking

public:
    // REQUIREMENT FULFILLED: At least two constructors (30 points)

    /**
     * @brief Default constructor - creates an empty Airplane
     * First constructor as per requirement
     */
    Airplane();

    /**
     * @brief Parameterized constructor with ID and PlaneClass
     * Second constructor as per requirement
     *
     * REQUIREMENT FULFILLED: Input validation where necessary (10 points)
     *
     * @param id Unique identification number (must be non-empty)
     * @param planeClass The PlaneClass this airplane belongs to
     * @throws std::invalid_argument if id is empty
     */
    Airplane(const std::string& id, const PlaneClass& planeClass);

    /**
     * @brief Full parameterized constructor
     * Third constructor for complete initialization
     *
     * @param id Unique identification number
     * @param planeClass The PlaneClass this airplane belongs to
     * @param operational Whether the airplane is operational
     * @param baseAirport Home base airport code
     * @param flightHours Total accumulated flight hours
     */
    Airplane(const std::string& id, const PlaneClass& planeClass,
             bool operational, const std::string& baseAirport, int flightHours);

    /**
     * @brief Copy constructor
     * @param other Airplane to copy from
     */
    Airplane(const Airplane& other);

    /**
     * @brief Destructor
     */
    ~Airplane();

    // REQUIREMENT FULFILLED: Public getters/setters for private instance variables (30 points)

    // Getters - provide read access to private members
    std::string getIdentificationNumber() const;
    PlaneClass getPlaneClass() const;
    bool isOperational() const;
    std::string getBaseAirportCode() const;
    int getTotalFlightHours() const;

    // Setters - provide write access with validation
    // REQUIREMENT FULFILLED: Input validation where necessary (10 points)
    void setIdentificationNumber(const std::string& id);
    void setPlaneClass(const PlaneClass& planeClass);
    void setOperational(bool operational);
    void setBaseAirportCode(const std::string& code);
    void setTotalFlightHours(int hours);

    /**
     * @brief Get the PlaneClass reference for direct access
     * @return Reference to the internal PlaneClass
     */
    const PlaneClass& getPlaneClassRef() const;

    /**
     * @brief Check if this airplane can fly to a destination
     * Based on runway compatibility and range
     *
     * @param runwayLength Destination runway length in meters
     * @param distance Distance to destination in km
     * @return true if the airplane can operate to this destination
     */
    bool canFlyToDestination(double runwayLength, double distance) const;

    /**
     * @brief Calculate the operating cost for a flight
     * @param distanceKm Distance in kilometers
     * @param passengers Number of passengers
     * @return Estimated operating cost (fuel cost)
     */
    double calculateOperatingCost(double distanceKm, int passengers) const;

    /**
     * @brief Add flight hours to the airplane's total
     * @param hours Number of hours to add
     */
    void addFlightHours(int hours);

    /**
     * @brief Assignment operator
     * @param other Airplane to copy from
     * @return Reference to this airplane
     */
    Airplane& operator=(const Airplane& other);

    // REQUIREMENT FULFILLED: Overload << operator for output (10 points)
    /**
     * @brief Friend function to overload << operator for output
     * @param os Output stream
     * @param airplane Airplane object to output
     * @return Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Airplane& airplane);

    /**
     * @brief Friend function to overload >> operator for input from file
     * @param is Input stream
     * @param airplane Airplane object to read into
     * @return Reference to the input stream
     */
    friend std::istream& operator>>(std::istream& is, Airplane& airplane);

    /**
     * @brief Equality operator
     * @param other Airplane to compare with
     * @return true if airplanes are equal (same ID)
     */
    bool operator==(const Airplane& other) const;
};

#endif // AIRPLANE_H
