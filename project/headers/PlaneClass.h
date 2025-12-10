#ifndef PLANE_CLASS_H
#define PLANE_CLASS_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class PlaneClass {
private:
    string manufacturer_;
    string model_;
    int seatCount_;
    double minRunwayLength_;
    double fuelConsumptionPerKmPerSeat_;
    double tankVolumeLiters_;
    double averageSpeedKmh_;
    int requiredCrewCount_;

public:
    PlaneClass();
    PlaneClass(const string& manufacturer, const string& model,
               int seatCount, double minRunwayLength, double fuelConsumption,
               double tankVolume, double avgSpeed, int crewCount);
    PlaneClass(const PlaneClass& other);
    ~PlaneClass();

    string getManufacturer() const;
    string getModel() const;
    int getSeatCount() const;
    double getMinRunwayLength() const;
    double getFuelConsumptionPerKmPerSeat() const;
    double getTankVolumeLiters() const;
    double getAverageSpeedKmh() const;
    int getRequiredCrewCount() const;

    void setManufacturer(const string& manufacturer);
    void setModel(const string& model);
    void setSeatCount(int count);
    void setMinRunwayLength(double length);
    void setFuelConsumptionPerKmPerSeat(double consumption);
    void setTankVolumeLiters(double volume);
    void setAverageSpeedKmh(double speed);
    void setRequiredCrewCount(int count);

    string getClassId() const;
    double calculateMaxRange() const;
    double calculateFlightDuration(double distanceKm) const;
    double calculateFuelConsumption(double distanceKm, int passengers) const;
    bool isCompatibleWithRunway(double runwayLength) const;

    friend ostream& operator<<(ostream& os, const PlaneClass& planeClass);
    friend istream& operator>>(istream& is, PlaneClass& planeClass);
    bool operator==(const PlaneClass& other) const;

    static void displayMenu();
};

#endif
