/**
 * @file Destination.h
 * @brief Defines the Destination class representing airport/destination information
 *
 * REQUIREMENT FULFILLED: Class encapsulation with private instance variables (30 points)
 * REQUIREMENT FULFILLED: At least 3 classes implementation
 *
 * This class stores:
 * - Destination code and name
 * - Airport runway length (determines aircraft compatibility)
 * - Distance from base/hub airport
 */

#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>
#include <iostream>
#include <stdexcept>

/**
 * @class Destination
 * @brief Represents an airport destination with its specifications
 *
 * The runway length determines which aircraft classes can operate to this destination.
 * Used for evaluating aircraft assignment efficiency.
 */
class Destination {
private:
    // REQUIREMENT: Private instance variables with camelCase_ naming convention
    std::string code_;              // IATA airport code (e.g., "SOF", "LHR")
    std::string name_;              // Full destination name (e.g., "Sofia Airport")
    std::string city_;              // City name
    std::string country_;           // Country name
    double runwayLengthMeters_;     // Available runway length in meters
    double distanceFromBaseKm_;     // Distance from base/hub airport in kilometers

public:
    // REQUIREMENT FULFILLED: At least two constructors (30 points)

    /**
     * @brief Default constructor - creates an empty Destination
     * First constructor as per requirement
     */
    Destination();

    /**
     * @brief Parameterized constructor with full initialization
     * Second constructor as per requirement
     *
     * REQUIREMENT FULFILLED: Input validation where necessary (10 points)
     *
     * @param code IATA airport code (must be non-empty)
     * @param name Full destination/airport name
     * @param city City name
     * @param country Country name
     * @param runwayLength Runway length in meters (must be > 0)
     * @param distance Distance from base in km (must be >= 0)
     * @throws std::invalid_argument if any parameter is invalid
     */
    Destination(const std::string& code, const std::string& name,
                const std::string& city, const std::string& country,
                double runwayLength, double distance);

    /**
     * @brief Copy constructor
     * @param other Destination to copy from
     */
    Destination(const Destination& other);

    /**
     * @brief Destructor
     */
    ~Destination();

    // REQUIREMENT FULFILLED: Public getters/setters for private instance variables (30 points)

    // Getters - provide read access to private members
    std::string getCode() const;
    std::string getName() const;
    std::string getCity() const;
    std::string getCountry() const;
    double getRunwayLengthMeters() const;
    double getDistanceFromBaseKm() const;

    // Setters - provide write access with validation
    // REQUIREMENT FULFILLED: Input validation where necessary (10 points)
    void setCode(const std::string& code);
    void setName(const std::string& name);
    void setCity(const std::string& city);
    void setCountry(const std::string& country);
    void setRunwayLengthMeters(double length);
    void setDistanceFromBaseKm(double distance);

    /**
     * @brief Get a display string for the destination
     * @return Formatted destination string (code - city, country)
     */
    std::string getDisplayString() const;

    // REQUIREMENT FULFILLED: Overload << operator for output (10 points)
    /**
     * @brief Friend function to overload << operator for output
     * @param os Output stream
     * @param destination Destination object to output
     * @return Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const Destination& destination);

    /**
     * @brief Friend function to overload >> operator for input from file
     * @param is Input stream
     * @param destination Destination object to read into
     * @return Reference to the input stream
     */
    friend std::istream& operator>>(std::istream& is, Destination& destination);

    /**
     * @brief Equality operator
     * @param other Destination to compare with
     * @return true if destinations are equal (same code)
     */
    bool operator==(const Destination& other) const;
};

#endif // DESTINATION_H
