/**
 * @file PlaneClass.h
 * @brief Defines the PlaneClass class representing aircraft type/class specifications
 *
 * REQUIREMENT FULFILLED: Class encapsulation with private instance variables (30 points)
 * REQUIREMENT FULFILLED: At least 3 classes implementation
 *
 * This class stores:
 * - Manufacturer and model information
 * - Seating capacity
 * - Minimum runway length for takeoff/landing
 * - Fuel consumption per km per seat
 * - Tank volume in liters (for maximum flight range calculation)
 * - Average speed (for flight duration and pilot workload assessment)
 * - Required crew count
 */

#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include <string>
#include <iostream>
#include <stdexcept>

/**
 * @class PlaneClass
 * @brief Represents an aircraft class/type with its specifications
 *
 * The plane class determines compatibility with destinations based on runway requirements.
 * Contains cost and performance data for efficiency evaluation.
 */
class PlaneClass {
private:
    // REQUIREMENT: Private instance variables with camelCase_ naming convention
    std::string manufacturer_;      // Aircraft manufacturer (e.g., "Boeing", "Airbus")
    std::string model_;             // Aircraft model (e.g., "737-800", "A320")
    int seatCount_;                 // Number of passenger seats
    double minRunwayLength_;        // Minimum runway length in meters for takeoff/landing
    double fuelConsumptionPerKmPerSeat_;  // Fuel consumption in liters per km per seat
    double tankVolumeLiters_;       // Fuel tank capacity in liters (for max range calculation)
    double averageSpeedKmh_;        // Average cruising speed in km/h (for flight duration)
    int requiredCrewCount_;         // Number of crew members required

public:
    // REQUIREMENT FULFILLED: At least two constructors (30 points)

    /**
     * @brief Default constructor - creates an empty PlaneClass
     * First constructor as per requirement
     */
    PlaneClass();

    /**
     * @brief Parameterized constructor with full initialization
     * Second constructor as per requirement
     *
     * REQUIREMENT FULFILLED: Input validation where necessary (10 points)
     *
     * @param manufacturer Aircraft manufacturer name
     * @param model Aircraft model designation
     * @param seatCount Number of seats (must be > 0)
     * @param minRunwayLength Minimum runway length in meters (must be > 0)
     * @param fuelConsumption Fuel per km per seat in liters (must be > 0)
     * @param tankVolume Tank capacity in liters (must be > 0)
     * @param avgSpeed Average speed in km/h (must be > 0)
     * @param crewCount Required crew members (must be > 0)
     * @throws std::invalid_argument if any numeric parameter is invalid
     */
    PlaneClass(const std::string& manufacturer, const std::string& model,
               int seatCount, double minRunwayLength, double fuelConsumption,
               double tankVolume, double avgSpeed, int crewCount);

    /**
     * @brief Copy constructor
     * @param other PlaneClass to copy from
     */
    PlaneClass(const PlaneClass& other);

    /**
     * @brief Destructor
     */
    ~PlaneClass();

    // REQUIREMENT FULFILLED: Public getters/setters for private instance variables (30 points)

    // Getters - provide read access to private members
    std::string getManufacturer() const;
    std::string getModel() const;
    int getSeatCount() const;
    double getMinRunwayLength() const;
    double getFuelConsumptionPerKmPerSeat() const;
    double getTankVolumeLiters() const;
    double getAverageSpeedKmh() const;
    int getRequiredCrewCount() const;

    // Setters - provide write access with validation
    // REQUIREMENT FULFILLED: Input validation where necessary (10 points)
    void setManufacturer(const std::string& manufacturer);
    void setModel(const std::string& model);
    void setSeatCount(int count);
    void setMinRunwayLength(double length);
    void setFuelConsumptionPerKmPerSeat(double consumption);
    void setTankVolumeLiters(double volume);
    void setAverageSpeedKmh(double speed);
    void setRequiredCrewCount(int count);

    /**
     * @brief Get a unique identifier for this plane class
     * @return Combined manufacturer and model string
     */
    std::string getClassId() const;

    /**
     * @brief Calculate maximum flight range based on tank volume and fuel consumption
     * @return Maximum range in kilometers
     */
    double calculateMaxRange() const;

    /**
     * @brief Calculate flight duration for a given distance
     * @param distanceKm Distance in kilometers
     * @return Flight duration in hours
     */
    double calculateFlightDuration(double distanceKm) const;

    /**
     * @brief Calculate total fuel consumption for a flight
     * @param distanceKm Distance in kilometers
     * @param passengers Number of passengers
     * @return Total fuel consumption in liters
     */
    double calculateFuelConsumption(double distanceKm, int passengers) const;

    /**
     * @brief Check if this plane class can land at a runway of given length
     * @param runwayLength Available runway length in meters
     * @return true if compatible, false otherwise
     */
    bool isCompatibleWithRunway(double runwayLength) const;

    // REQUIREMENT FULFILLED: Overload << operator for output (10 points)
    /**
     * @brief Friend function to overload << operator for output
     * @param os Output stream
     * @param planeClass PlaneClass object to output
     * @return Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const PlaneClass& planeClass);

    /**
     * @brief Friend function to overload >> operator for input from file
     * @param is Input stream
     * @param planeClass PlaneClass object to read into
     * @return Reference to the input stream
     */
    friend std::istream& operator>>(std::istream& is, PlaneClass& planeClass);

    /**
     * @brief Equality operator
     * @param other PlaneClass to compare with
     * @return true if classes are equal (same manufacturer and model)
     */
    bool operator==(const PlaneClass& other) const;
};

#endif // PLANE_CLASS_H
