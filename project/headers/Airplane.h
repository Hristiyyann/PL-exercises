#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <string>
#include <iostream>
#include <memory>
#include "PlaneClass.h"

using namespace std;

class Airplane {
private:
    string identificationNumber_;
    PlaneClass planeClass_;
    bool isOperational_;
    string baseAirportCode_;
    int totalFlightHours_;

public:
    Airplane();
    Airplane(const string& id, const PlaneClass& planeClass);
    Airplane(const string& id, const PlaneClass& planeClass,
             bool operational, const string& baseAirport, int flightHours);
    Airplane(const Airplane& other);
    ~Airplane();

    string getIdentificationNumber() const;
    PlaneClass getPlaneClass() const;
    bool isOperational() const;
    string getBaseAirportCode() const;
    int getTotalFlightHours() const;

    void setIdentificationNumber(const string& id);
    void setPlaneClass(const PlaneClass& planeClass);
    void setOperational(bool operational);
    void setBaseAirportCode(const string& code);
    void setTotalFlightHours(int hours);

    const PlaneClass& getPlaneClassRef() const;
    bool canFlyToDestination(double runwayLength, double distance) const;
    double calculateOperatingCost(double distanceKm, int passengers) const;
    void addFlightHours(int hours);

    Airplane& operator=(const Airplane& other);
    friend ostream& operator<<(ostream& os, const Airplane& airplane);
    friend istream& operator>>(istream& is, Airplane& airplane);
    bool operator==(const Airplane& other) const;

    static void displayMenu();
};

#endif
