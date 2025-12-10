#include "../headers/Airplane.h"
#include <iomanip>
#include <sstream>

using namespace std;

Airplane::Airplane()
    : identificationNumber_(""), planeClass_(), isOperational_(false),
      baseAirportCode_(""), totalFlightHours_(0) {}

Airplane::Airplane(const string &id, const PlaneClass &planeClass)
    : identificationNumber_(""), planeClass_(planeClass), isOperational_(true),
      baseAirportCode_(""), totalFlightHours_(0) {
    setIdentificationNumber(id);
}

Airplane::Airplane(const string &id, const PlaneClass &planeClass,
                   bool operational, const string &baseAirport, int flightHours)
    : identificationNumber_(""), planeClass_(planeClass),
      isOperational_(operational), baseAirportCode_(baseAirport),
      totalFlightHours_(0) {
    setIdentificationNumber(id);
    setTotalFlightHours(flightHours);
}

Airplane::Airplane(const Airplane &other)
    : identificationNumber_(other.identificationNumber_),
      planeClass_(other.planeClass_), isOperational_(other.isOperational_),
      baseAirportCode_(other.baseAirportCode_),
      totalFlightHours_(other.totalFlightHours_) {}

Airplane::~Airplane() {}

string Airplane::getIdentificationNumber() const {
    return identificationNumber_;
}

PlaneClass Airplane::getPlaneClass() const { return planeClass_; }

bool Airplane::isOperational() const { return isOperational_; }

string Airplane::getBaseAirportCode() const { return baseAirportCode_; }

int Airplane::getTotalFlightHours() const { return totalFlightHours_; }

const PlaneClass &Airplane::getPlaneClassRef() const { return planeClass_; }

void Airplane::setIdentificationNumber(const string &id) {
    if (id.empty()) {
        throw invalid_argument("Идентификационният номер на самолета не може да е празен");
    }
    identificationNumber_ = id;
}

void Airplane::setPlaneClass(const PlaneClass &planeClass) {
    planeClass_ = planeClass;
}

void Airplane::setOperational(bool operational) {
    isOperational_ = operational;
}

void Airplane::setBaseAirportCode(const string &code) {
    baseAirportCode_ = code;
}

void Airplane::setTotalFlightHours(int hours) {
    if (hours < 0) {
        throw invalid_argument("Общите летателни часове не могат да са отрицателни");
    }
    totalFlightHours_ = hours;
}

bool Airplane::canFlyToDestination(double runwayLength, double distance) const {
    if (!isOperational_) {
        return false;
    }
    if (!planeClass_.isCompatibleWithRunway(runwayLength)) {
        return false;
    }
    if (distance > planeClass_.calculateMaxRange()) {
        return false;
    }
    return true;
}

double Airplane::calculateOperatingCost(double distanceKm, int passengers) const {
    if (distanceKm < 0.0) {
        throw invalid_argument("Разстоянието не може да е отрицателно");
    }
    if (passengers < 0) {
        throw invalid_argument("Броят пътници не може да е отрицателен");
    }
    return planeClass_.calculateFuelConsumption(distanceKm, passengers) * 0.80;
}

void Airplane::addFlightHours(int hours) {
    if (hours < 0) {
        throw invalid_argument("Не могат да се добавят отрицателни летателни часове");
    }
    totalFlightHours_ += hours;
}

Airplane &Airplane::operator=(const Airplane &other) {
    if (this == &other) {
        return *this;
    }
    identificationNumber_ = other.identificationNumber_;
    planeClass_ = other.planeClass_;
    isOperational_ = other.isOperational_;
    baseAirportCode_ = other.baseAirportCode_;
    totalFlightHours_ = other.totalFlightHours_;
    return *this;
}

ostream &operator<<(ostream &os, const Airplane &airplane) {
    os << "Информация за самолет" << endl;
    os << "ID номер:            " << airplane.identificationNumber_ << endl;
    os << "Клас самолет:        " << airplane.planeClass_.getClassId() << endl;
    os << "Оперативен:          " << (airplane.isOperational_ ? "Да" : "Не") << endl;
    os << "Базово летище:       "
       << (airplane.baseAirportCode_.empty() ? "Неопределено" : airplane.baseAirportCode_) << endl;
    os << "Общо летателни часове: " << airplane.totalFlightHours_ << " часа" << endl;
    os << "Капацитет места:     " << airplane.planeClass_.getSeatCount() << endl;
    os << "Максимален обхват:   " << fixed << setprecision(2)
       << airplane.planeClass_.calculateMaxRange() << " км" << endl;
    os << "Мин. необх. писта:   " << airplane.planeClass_.getMinRunwayLength() << " м" << endl;
    return os;
}

istream &operator>>(istream &is, Airplane &airplane) {
    string planeClassId;
    int operational;
    is >> airplane.identificationNumber_ >> planeClassId >> operational >>
        airplane.baseAirportCode_ >> airplane.totalFlightHours_;
    airplane.isOperational_ = (operational == 1);
    return is;
}

bool Airplane::operator==(const Airplane &other) const {
    return identificationNumber_ == other.identificationNumber_;
}

void Airplane::displayMenu() {
    cout << "\nУПРАВЛЕНИЕ НА САМОЛЕТИ" << endl;
    cout << "1. Добавяне на самолет" << endl;
    cout << "2. Преглед на всички самолети" << endl;
    cout << "3. Детайли за самолет" << endl;
    cout << "4. Премахване на самолет" << endl;
    cout << "5. Превключване на оперативен статус" << endl;
    cout << "6. Добавяне на летателни часове" << endl;
    cout << "0. Назад към главното меню" << endl;
    cout << "Въведете избор: ";
}
