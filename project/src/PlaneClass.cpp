#include "../headers/PlaneClass.h"
#include <iomanip>
#include <sstream>

using namespace std;

PlaneClass::PlaneClass()
    : manufacturer_(""), model_(""), seatCount_(0), minRunwayLength_(0.0),
      fuelConsumptionPerKmPerSeat_(0.0), tankVolumeLiters_(0.0),
      averageSpeedKmh_(0.0), requiredCrewCount_(0) {}

PlaneClass::PlaneClass(const string &manufacturer, const string &model,
                       int seatCount, double minRunwayLength,
                       double fuelConsumption, double tankVolume,
                       double avgSpeed, int crewCount)
    : manufacturer_(manufacturer), model_(model), seatCount_(0),
      minRunwayLength_(0.0), fuelConsumptionPerKmPerSeat_(0.0),
      tankVolumeLiters_(0.0), averageSpeedKmh_(0.0), requiredCrewCount_(0) {

    setSeatCount(seatCount);
    setMinRunwayLength(minRunwayLength);
    setFuelConsumptionPerKmPerSeat(fuelConsumption);
    setTankVolumeLiters(tankVolume);
    setAverageSpeedKmh(avgSpeed);
    setRequiredCrewCount(crewCount);
}

PlaneClass::PlaneClass(const PlaneClass &other)
    : manufacturer_(other.manufacturer_), model_(other.model_),
      seatCount_(other.seatCount_), minRunwayLength_(other.minRunwayLength_),
      fuelConsumptionPerKmPerSeat_(other.fuelConsumptionPerKmPerSeat_),
      tankVolumeLiters_(other.tankVolumeLiters_),
      averageSpeedKmh_(other.averageSpeedKmh_),
      requiredCrewCount_(other.requiredCrewCount_) {}

PlaneClass::~PlaneClass() {}

string PlaneClass::getManufacturer() const { return manufacturer_; }

string PlaneClass::getModel() const { return model_; }

int PlaneClass::getSeatCount() const { return seatCount_; }

double PlaneClass::getMinRunwayLength() const { return minRunwayLength_; }

double PlaneClass::getFuelConsumptionPerKmPerSeat() const {
    return fuelConsumptionPerKmPerSeat_;
}

double PlaneClass::getTankVolumeLiters() const { return tankVolumeLiters_; }

double PlaneClass::getAverageSpeedKmh() const { return averageSpeedKmh_; }

int PlaneClass::getRequiredCrewCount() const { return requiredCrewCount_; }

void PlaneClass::setManufacturer(const string &manufacturer) {
    if (manufacturer.empty()) {
        throw invalid_argument("Името на производителя не може да е празно");
    }
    manufacturer_ = manufacturer;
}

void PlaneClass::setModel(const string &model) {
    if (model.empty()) {
        throw invalid_argument("Името на модела не може да е празно");
    }
    model_ = model;
}

void PlaneClass::setSeatCount(int count) {
    if (count <= 0) {
        throw invalid_argument("Броят места трябва да е по-голям от 0");
    }
    seatCount_ = count;
}

void PlaneClass::setMinRunwayLength(double length) {
    if (length <= 0.0) {
        throw invalid_argument("Минималната дължина на пистата трябва да е по-голяма от 0");
    }
    minRunwayLength_ = length;
}

void PlaneClass::setFuelConsumptionPerKmPerSeat(double consumption) {
    if (consumption <= 0.0) {
        throw invalid_argument("Разходът на гориво трябва да е по-голям от 0");
    }
    fuelConsumptionPerKmPerSeat_ = consumption;
}

void PlaneClass::setTankVolumeLiters(double volume) {
    if (volume <= 0.0) {
        throw invalid_argument("Обемът на резервоара трябва да е по-голям от 0");
    }
    tankVolumeLiters_ = volume;
}

void PlaneClass::setAverageSpeedKmh(double speed) {
    if (speed <= 0.0) {
        throw invalid_argument("Средната скорост трябва да е по-голяма от 0");
    }
    averageSpeedKmh_ = speed;
}

void PlaneClass::setRequiredCrewCount(int count) {
    if (count <= 0) {
        throw invalid_argument("Необходимият екипаж трябва да е по-голям от 0");
    }
    requiredCrewCount_ = count;
}

string PlaneClass::getClassId() const { return manufacturer_ + " " + model_; }

double PlaneClass::calculateMaxRange() const {
    if (fuelConsumptionPerKmPerSeat_ <= 0.0 || seatCount_ <= 0) {
        return 0.0;
    }
    double fuelPerKm = fuelConsumptionPerKmPerSeat_ * seatCount_;
    return tankVolumeLiters_ / fuelPerKm;
}

double PlaneClass::calculateFlightDuration(double distanceKm) const {
    if (distanceKm < 0.0) {
        throw invalid_argument("Разстоянието не може да е отрицателно");
    }
    if (averageSpeedKmh_ <= 0.0) {
        return 0.0;
    }
    return distanceKm / averageSpeedKmh_;
}

double PlaneClass::calculateFuelConsumption(double distanceKm, int passengers) const {
    if (distanceKm < 0.0) {
        throw invalid_argument("Разстоянието не може да е отрицателно");
    }
    if (passengers < 0 || passengers > seatCount_) {
        throw invalid_argument("Невалиден брой пътници");
    }
    return fuelConsumptionPerKmPerSeat_ * distanceKm * passengers;
}

bool PlaneClass::isCompatibleWithRunway(double runwayLength) const {
    return runwayLength >= minRunwayLength_;
}

ostream &operator<<(ostream &os, const PlaneClass &planeClass) {
    os << "Информация за клас самолет" << endl;
    os << "Производител:        " << planeClass.manufacturer_ << endl;
    os << "Модел:               " << planeClass.model_ << endl;
    os << "ID на класа:         " << planeClass.getClassId() << endl;
    os << "Брой места:          " << planeClass.seatCount_ << endl;
    os << "Мин. дължина писта:  " << fixed << setprecision(2)
       << planeClass.minRunwayLength_ << " м" << endl;
    os << "Разход на гориво:    " << planeClass.fuelConsumptionPerKmPerSeat_
       << " л на км за 1 място" << endl;
    os << "Обем на резервоара:  " << planeClass.tankVolumeLiters_ << " л" << endl;
    os << "Средна скорост:      " << planeClass.averageSpeedKmh_ << " км/ч" << endl;
    os << "Необходим екипаж:    " << planeClass.requiredCrewCount_ << endl;
    os << "Максимален обхват:   " << fixed << setprecision(2)
       << planeClass.calculateMaxRange() << " км" << endl;
    return os;
}

istream &operator>>(istream &is, PlaneClass &planeClass) {
    is >> planeClass.manufacturer_ >> planeClass.model_ >>
        planeClass.seatCount_ >> planeClass.minRunwayLength_ >>
        planeClass.fuelConsumptionPerKmPerSeat_ >>
        planeClass.tankVolumeLiters_ >> planeClass.averageSpeedKmh_ >>
        planeClass.requiredCrewCount_;
    return is;
}

bool PlaneClass::operator==(const PlaneClass &other) const {
    return manufacturer_ == other.manufacturer_ && model_ == other.model_;
}

void PlaneClass::displayMenu() {
    cout << "\nУПРАВЛЕНИЕ НА КЛАСОВЕ САМОЛЕТИ" << endl;
    cout << "1. Добавяне на клас самолет" << endl;
    cout << "2. Преглед на всички класове" << endl;
    cout << "3. Детайли за клас самолет" << endl;
    cout << "0. Назад към главното меню" << endl;
    cout << "Въведете избор: ";
}
