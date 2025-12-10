#ifndef FLEET_MANAGER_H
#define FLEET_MANAGER_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "Airplane.h"
#include "Destination.h"
#include "PlaneClass.h"
#include "Validator.h"

using namespace std;

class FleetManager {
private:
    vector<Airplane> airplanes_;
    vector<Destination> destinations_;
    vector<PlaneClass> planeClasses_;
    string companyName_;
    string dataDirectory_;

    bool saveAirplanesToFile(const string& filename) const;
    bool loadAirplanesFromFile(const string& filename);
    bool saveDestinationsToFile(const string& filename) const;
    bool loadDestinationsFromFile(const string& filename);
    bool savePlaneClassesToFile(const string& filename) const;
    bool loadPlaneClassesFromFile(const string& filename);

public:
    FleetManager();
    FleetManager(const string& companyName, const string& dataDirectory);
    FleetManager(const FleetManager& other);
    ~FleetManager();

    string getCompanyName() const;
    string getDataDirectory() const;
    size_t getAirplaneCount() const;
    size_t getDestinationCount() const;
    size_t getPlaneClassCount() const;
    const vector<Airplane>& getAirplanes() const;
    const vector<Destination>& getDestinations() const;
    const vector<PlaneClass>& getPlaneClasses() const;

    void setCompanyName(const string& name);
    void setDataDirectory(const string& directory);

    bool addPlaneClass(const PlaneClass& planeClass);
    bool addAirplane(const Airplane& airplane);
    bool addDestination(const Destination& destination);
    bool removeAirplaneById(const string& id);
    bool removeDestinationByCode(const string& code);

    Airplane* findAirplaneById(const string& id);
    Destination* findDestinationByCode(const string& code);
    PlaneClass* findPlaneClassById(const string& classId);

    vector<Airplane*> findAirplanesForDestination(const string& destinationCode);
    vector<Airplane*> findCompatibleAirplanes(double runwayLength, double distance);
    vector<Airplane*> getOperationalAirplanes();

    void displayAllAirplanes(ostream& os) const;
    void displayAllDestinations(ostream& os) const;
    void displayAllPlaneClasses(ostream& os) const;

    bool saveAllData() const;
    bool loadAllData();
    void clearAllData();

    friend ostream& operator<<(ostream& os, const FleetManager& manager);

    static void displayMainMenu();

    void viewPlaneClassDetails();
    void handlePlaneClassMenu();

    void viewAirplaneDetails();
    void toggleOperationalStatus();
    void handleAirplaneMenu();

    void viewDestinationDetails();
    void handleDestinationMenu();

    void searchAirplanesForDestination();
    void addSampleData();
};

#endif
