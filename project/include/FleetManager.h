/**
 * @file FleetManager.h
 * @brief Defines the FleetManager class for managing the fleet of airplanes
 *
 * REQUIREMENT FULFILLED: Support for arbitrary number of different airplanes (10 points)
 * REQUIREMENT FULFILLED: Search for airplanes that can fly to a destination (10 points)
 * REQUIREMENT FULFILLED: File I/O operations (20 points)
 *
 * This class provides:
 * - Management of multiple airplanes
 * - Management of destinations
 * - Search functionality for compatible airplanes
 * - File persistence (save/load operations)
 */

#ifndef FLEET_MANAGER_H
#define FLEET_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Airplane.h"
#include "Destination.h"
#include "PlaneClass.h"

/**
 * @class FleetManager
 * @brief Manages a fleet of airplanes and destinations
 *
 * Provides functionality for:
 * - Adding/removing airplanes of various classes
 * - Managing destinations
 * - Searching for airplanes compatible with destinations
 * - Persisting data to files
 */
class FleetManager {
private:
    // REQUIREMENT: Private instance variables with camelCase_ naming convention
    std::vector<Airplane> airplanes_;           // Collection of all airplanes in the fleet
    std::vector<Destination> destinations_;      // Collection of all destinations
    std::vector<PlaneClass> planeClasses_;       // Collection of all registered plane classes
    std::string companyName_;                    // Name of the airline company
    std::string dataDirectory_;                  // Directory for data files

    // Private helper methods for file operations
    bool saveAirplanesToFile(const std::string& filename) const;
    bool loadAirplanesFromFile(const std::string& filename);
    bool saveDestinationsToFile(const std::string& filename) const;
    bool loadDestinationsFromFile(const std::string& filename);
    bool savePlaneClassesToFile(const std::string& filename) const;
    bool loadPlaneClassesFromFile(const std::string& filename);

public:
    // REQUIREMENT FULFILLED: At least two constructors (30 points)

    /**
     * @brief Default constructor
     * First constructor as per requirement
     */
    FleetManager();

    /**
     * @brief Parameterized constructor with company name
     * Second constructor as per requirement
     *
     * @param companyName Name of the airline company
     * @param dataDirectory Directory path for data files
     */
    FleetManager(const std::string& companyName, const std::string& dataDirectory);

    /**
     * @brief Copy constructor
     * @param other FleetManager to copy from
     */
    FleetManager(const FleetManager& other);

    /**
     * @brief Destructor
     */
    ~FleetManager();

    // REQUIREMENT FULFILLED: Public getters/setters for private instance variables (30 points)

    // Getters
    std::string getCompanyName() const;
    std::string getDataDirectory() const;
    size_t getAirplaneCount() const;
    size_t getDestinationCount() const;
    size_t getPlaneClassCount() const;
    const std::vector<Airplane>& getAirplanes() const;
    const std::vector<Destination>& getDestinations() const;
    const std::vector<PlaneClass>& getPlaneClasses() const;

    // Setters
    void setCompanyName(const std::string& name);
    void setDataDirectory(const std::string& directory);

    // REQUIREMENT FULFILLED: Support for arbitrary number of different airplanes (10 points)
    /**
     * @brief Add a new plane class to the system
     * @param planeClass The PlaneClass to add
     * @return true if added successfully, false if already exists
     */
    bool addPlaneClass(const PlaneClass& planeClass);

    /**
     * @brief Add a new airplane to the fleet
     * @param airplane The Airplane to add
     * @return true if added successfully, false if already exists
     */
    bool addAirplane(const Airplane& airplane);

    /**
     * @brief Add a new destination
     * @param destination The Destination to add
     * @return true if added successfully, false if already exists
     */
    bool addDestination(const Destination& destination);

    /**
     * @brief Remove an airplane from the fleet by ID
     * @param id The identification number of the airplane to remove
     * @return true if removed successfully, false if not found
     */
    bool removeAirplane(const std::string& id);

    /**
     * @brief Remove a destination by code
     * @param code The IATA code of the destination to remove
     * @return true if removed successfully, false if not found
     */
    bool removeDestination(const std::string& code);

    /**
     * @brief Find an airplane by its ID
     * @param id The identification number to search for
     * @return Pointer to the airplane if found, nullptr otherwise
     */
    Airplane* findAirplaneById(const std::string& id);

    /**
     * @brief Find a destination by its code
     * @param code The IATA code to search for
     * @return Pointer to the destination if found, nullptr otherwise
     */
    Destination* findDestinationByCode(const std::string& code);

    /**
     * @brief Find a plane class by manufacturer and model
     * @param classId The class identifier (manufacturer + model)
     * @return Pointer to the plane class if found, nullptr otherwise
     */
    PlaneClass* findPlaneClassById(const std::string& classId);

    // REQUIREMENT FULFILLED: Search for airplanes that can fly to a destination (10 points)
    /**
     * @brief Find all airplanes that can fly to a specific destination
     *
     * This method evaluates each airplane's compatibility based on:
     * - Runway length requirements
     * - Maximum flight range
     * - Operational status
     *
     * @param destinationCode The IATA code of the destination
     * @return Vector of pointers to compatible airplanes
     */
    std::vector<Airplane*> findAirplanesForDestination(const std::string& destinationCode);

    /**
     * @brief Find all airplanes that can fly to a destination with specific runway length
     * @param runwayLength The runway length in meters
     * @param distance The distance in kilometers
     * @return Vector of pointers to compatible airplanes
     */
    std::vector<Airplane*> findCompatibleAirplanes(double runwayLength, double distance);

    /**
     * @brief Get all operational airplanes
     * @return Vector of pointers to operational airplanes
     */
    std::vector<Airplane*> getOperationalAirplanes();

    /**
     * @brief Display all airplanes in the fleet
     * @param os Output stream to write to
     */
    void displayAllAirplanes(std::ostream& os) const;

    /**
     * @brief Display all destinations
     * @param os Output stream to write to
     */
    void displayAllDestinations(std::ostream& os) const;

    /**
     * @brief Display all plane classes
     * @param os Output stream to write to
     */
    void displayAllPlaneClasses(std::ostream& os) const;

    // REQUIREMENT FULFILLED: File I/O operations (20 points)
    /**
     * @brief Save all data to files
     * @return true if all files saved successfully
     */
    bool saveAllData() const;

    /**
     * @brief Load all data from files
     * @return true if all files loaded successfully
     */
    bool loadAllData();

    /**
     * @brief Clear all data from memory
     */
    void clearAllData();

    // REQUIREMENT FULFILLED: Overload << operator for output (10 points)
    /**
     * @brief Friend function to overload << operator for output
     * @param os Output stream
     * @param manager FleetManager object to output
     * @return Reference to the output stream
     */
    friend std::ostream& operator<<(std::ostream& os, const FleetManager& manager);
};

#endif // FLEET_MANAGER_H
