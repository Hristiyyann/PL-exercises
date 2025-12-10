#include "../headers/Destination.h"
#include <iomanip>
#include <sstream>

using namespace std;

Destination::Destination()
    : code_(""), name_(""), city_(""), country_(""), runwayLengthMeters_(0.0),
      distanceFromBaseKm_(0.0) {}

Destination::Destination(const string &code, const string &name,
                         const string &city, const string &country,
                         double runwayLength, double distance)
    : code_(""), name_(name), city_(city), country_(country),
      runwayLengthMeters_(0.0), distanceFromBaseKm_(0.0) {

    setCode(code);
    setRunwayLengthMeters(runwayLength);
    setDistanceFromBaseKm(distance);
}

Destination::Destination(const Destination &other)
    : code_(other.code_), name_(other.name_), city_(other.city_),
      country_(other.country_), runwayLengthMeters_(other.runwayLengthMeters_),
      distanceFromBaseKm_(other.distanceFromBaseKm_) {}

Destination::~Destination() {}

string Destination::getCode() const { return code_; }

string Destination::getName() const { return name_; }

string Destination::getCity() const { return city_; }

string Destination::getCountry() const { return country_; }

double Destination::getRunwayLengthMeters() const {
    return runwayLengthMeters_;
}

double Destination::getDistanceFromBaseKm() const {
    return distanceFromBaseKm_;
}

void Destination::setCode(const string &code) {
    if (code.empty()) {
        throw invalid_argument("Кодът на дестинацията не може да е празен");
    }
    code_ = code;
}

void Destination::setName(const string &name) { name_ = name; }

void Destination::setCity(const string &city) { city_ = city; }

void Destination::setCountry(const string &country) { country_ = country; }

void Destination::setRunwayLengthMeters(double length) {
    if (length <= 0.0) {
        throw invalid_argument("Дължината на пистата трябва да е по-голяма от 0");
    }
    runwayLengthMeters_ = length;
}

void Destination::setDistanceFromBaseKm(double distance) {
    if (distance < 0.0) {
        throw invalid_argument("Разстоянието не може да е отрицателно");
    }
    distanceFromBaseKm_ = distance;
}

string Destination::getDisplayString() const {
    ostringstream oss;
    oss << code_ << " - " << city_;
    if (!country_.empty()) {
        oss << ", " << country_;
    }
    return oss.str();
}

ostream &operator<<(ostream &os, const Destination &destination) {
    os << "Информация за дестинация" << endl;
    os << "Код:                 " << destination.code_ << endl;
    os << "Име:                 " << destination.name_ << endl;
    os << "Град:                " << destination.city_ << endl;
    os << "Държава:             " << destination.country_ << endl;
    os << "Дължина на пистата:  " << fixed << setprecision(2)
       << destination.runwayLengthMeters_ << " м" << endl;
    os << "Разстояние от базата: " << destination.distanceFromBaseKm_ << " км" << endl;
    return os;
}

istream &operator>>(istream &is, Destination &destination) {
    is >> destination.code_ >> destination.name_ >> destination.city_ >>
        destination.country_ >> destination.runwayLengthMeters_ >>
        destination.distanceFromBaseKm_;
    return is;
}

bool Destination::operator==(const Destination &other) const {
    return code_ == other.code_;
}

void Destination::displayMenu() {
    cout << "\nУПРАВЛЕНИЕ НА ДЕСТИНАЦИИ" << endl;
    cout << "1. Добавяне на дестинация" << endl;
    cout << "2. Преглед на всички дестинации" << endl;
    cout << "3. Детайли за дестинация" << endl;
    cout << "4. Премахване на дестинация" << endl;
    cout << "0. Назад към главното меню" << endl;
    cout << "Въведете избор: ";
}
