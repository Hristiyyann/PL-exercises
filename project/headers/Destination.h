#ifndef DESTINATION_H
#define DESTINATION_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

class Destination {
private:
    string code_;
    string name_;
    string city_;
    string country_;
    double runwayLengthMeters_;
    double distanceFromBaseKm_;

public:
    Destination();
    Destination(const string& code, const string& name,
                const string& city, const string& country,
                double runwayLength, double distance);
    Destination(const Destination& other);
    ~Destination();

    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    double getRunwayLengthMeters() const;
    double getDistanceFromBaseKm() const;

    void setCode(const string& code);
    void setName(const string& name);
    void setCity(const string& city);
    void setCountry(const string& country);
    void setRunwayLengthMeters(double length);
    void setDistanceFromBaseKm(double distance);

    string getDisplayString() const;

    friend ostream& operator<<(ostream& os, const Destination& destination);
    friend istream& operator>>(istream& is, Destination& destination);
    bool operator==(const Destination& other) const;

    static void displayMenu();
};

#endif
