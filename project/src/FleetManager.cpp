#include "../headers/FleetManager.h"
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

FleetManager::FleetManager()
    : airplanes_(), destinations_(), planeClasses_(),
      companyName_("Авиокомпания по подразбиране"), dataDirectory_("./data") {}

FleetManager::FleetManager(const string &companyName, const string &dataDirectory)
    : airplanes_(), destinations_(), planeClasses_(), companyName_(companyName),
      dataDirectory_(dataDirectory) {}

FleetManager::FleetManager(const FleetManager &other)
    : airplanes_(other.airplanes_), destinations_(other.destinations_),
      planeClasses_(other.planeClasses_), companyName_(other.companyName_),
      dataDirectory_(other.dataDirectory_) {}

FleetManager::~FleetManager() {}

string FleetManager::getCompanyName() const { return companyName_; }

string FleetManager::getDataDirectory() const { return dataDirectory_; }

size_t FleetManager::getAirplaneCount() const { return airplanes_.size(); }

size_t FleetManager::getDestinationCount() const { return destinations_.size(); }

size_t FleetManager::getPlaneClassCount() const { return planeClasses_.size(); }

const vector<Airplane> &FleetManager::getAirplanes() const { return airplanes_; }

const vector<Destination> &FleetManager::getDestinations() const { return destinations_; }

const vector<PlaneClass> &FleetManager::getPlaneClasses() const { return planeClasses_; }

void FleetManager::setCompanyName(const string &name) { companyName_ = name; }

void FleetManager::setDataDirectory(const string &directory) { dataDirectory_ = directory; }

bool FleetManager::addPlaneClass(const PlaneClass &planeClassToAdd) {
    for (const auto &planeClass : planeClasses_) {
        if (planeClass == planeClassToAdd) {
            return false;
        }
    }
    planeClasses_.push_back(planeClassToAdd);
    return true;
}

bool FleetManager::addAirplane(const Airplane &airplaneToAdd) {
    for (const auto &airplane : airplanes_) {
        if (airplane == airplaneToAdd) {
            return false;
        }
    }
    airplanes_.push_back(airplaneToAdd);
    return true;
}

bool FleetManager::addDestination(const Destination &destinationToAdd) {
    for (const auto &destination : destinations_) {
        if (destination == destinationToAdd) {
            return false;
        }
    }
    destinations_.push_back(destinationToAdd);
    return true;
}

bool FleetManager::removeAirplaneById(const string &id) {
    auto it = remove_if(airplanes_.begin(), airplanes_.end(),
        [&id](const Airplane &a) { return a.getIdentificationNumber() == id; });

    if (it == airplanes_.end()) {
        return false;
    }

    airplanes_.erase(it, airplanes_.end());
    return true;
}

bool FleetManager::removeDestinationByCode(const string &code) {
    auto it = remove_if(destinations_.begin(), destinations_.end(),
        [&code](const Destination &d) { return d.getCode() == code; });

    if (it == destinations_.end()) {
        return false;
    }

    destinations_.erase(it, destinations_.end());
    return true;
}

Airplane *FleetManager::findAirplaneById(const string &id) {
    for (auto &airplane : airplanes_) {
        if (airplane.getIdentificationNumber() == id) {
            return &airplane;
        }
    }
    return nullptr;
}

Destination *FleetManager::findDestinationByCode(const string &code) {
    for (auto &destination : destinations_) {
        if (destination.getCode() == code) {
            return &destination;
        }
    }
    return nullptr;
}

PlaneClass *FleetManager::findPlaneClassById(const string &classId) {
    for (auto &planeClass : planeClasses_) {
        if (planeClass.getClassId() == classId) {
            return &planeClass;
        }
    }
    return nullptr;
}

vector<Airplane *> FleetManager::findAirplanesForDestination(const string &destinationCode) {
    vector<Airplane *> compatibleAirplanes;

    Destination *dest = findDestinationByCode(destinationCode);
    if (dest == nullptr) {
        return compatibleAirplanes;
    }

    for (auto &airplane : airplanes_) {
        if (airplane.canFlyToDestination(dest->getRunwayLengthMeters(),
                                         dest->getDistanceFromBaseKm())) {
            compatibleAirplanes.push_back(&airplane);
        }
    }
    return compatibleAirplanes;
}

vector<Airplane *> FleetManager::findCompatibleAirplanes(double runwayLength, double distance) {
    vector<Airplane *> compatibleAirplanes;
    for (auto &airplane : airplanes_) {
        if (airplane.canFlyToDestination(runwayLength, distance)) {
            compatibleAirplanes.push_back(&airplane);
        }
    }
    return compatibleAirplanes;
}

vector<Airplane *> FleetManager::getOperationalAirplanes() {
    vector<Airplane *> operationalAirplanes;
    for (auto &airplane : airplanes_) {
        if (airplane.isOperational()) {
            operationalAirplanes.push_back(&airplane);
        }
    }
    return operationalAirplanes;
}

void FleetManager::displayAllAirplanes(ostream &os) const {
    os << "\nСАМОЛЕТИ ВЪВ ФЛОТА" << endl;
    os << "Общ брой самолети: " << airplanes_.size() << "\n" << endl;

    if (airplanes_.empty()) {
        os << "Няма самолети във флота." << endl;
        return;
    }

    int count = 1;
    for (const auto &airplane : airplanes_) {
        os << "[" << count++ << "] ";
        os << airplane << endl;
    }
}

void FleetManager::displayAllDestinations(ostream &os) const {
    os << "\nДЕСТИНАЦИИ" << endl;
    os << "Общ брой дестинации: " << destinations_.size() << "\n" << endl;

    if (destinations_.empty()) {
        os << "Няма регистрирани дестинации." << endl;
        return;
    }

    int count = 1;
    for (const auto &destination : destinations_) {
        os << "[" << count++ << "] ";
        os << destination << endl;
    }
}

void FleetManager::displayAllPlaneClasses(ostream &os) const {
    os << "\nКЛАСОВЕ САМОЛЕТИ" << endl;
    os << "Общ брой класове: " << planeClasses_.size() << "\n" << endl;

    if (planeClasses_.empty()) {
        os << "Няма регистрирани класове самолети." << endl;
        return;
    }

    int count = 1;
    for (const auto &planeClass : planeClasses_) {
        os << "[" << count++ << "] ";
        os << planeClass << endl;
    }
}

bool FleetManager::savePlaneClassesToFile(const string &filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto &pc : planeClasses_) {
        file << pc.getManufacturer() << " " << pc.getModel() << " "
             << pc.getSeatCount() << " " << pc.getMinRunwayLength() << " "
             << pc.getFuelConsumptionPerKmPerSeat() << " "
             << pc.getTankVolumeLiters() << " " << pc.getAverageSpeedKmh()
             << " " << pc.getRequiredCrewCount() << endl;
    }
    file.close();
    return true;
}

bool FleetManager::loadPlaneClassesFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    PlaneClass pc;
    while (file >> pc) {
        if (!pc.getManufacturer().empty()) {
            addPlaneClass(pc);
        }
    }
    file.close();
    return true;
}

bool FleetManager::saveAirplanesToFile(const string &filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto &airplane : airplanes_) {
        file << airplane.getIdentificationNumber() << "\t"
             << airplane.getPlaneClassRef().getClassId() << "\t"
             << (airplane.isOperational() ? 1 : 0) << "\t"
             << airplane.getBaseAirportCode() << "\t"
             << airplane.getTotalFlightHours() << endl;
    }
    file.close();
    return true;
}

bool FleetManager::loadAirplanesFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        string id, planeClassId, baseAirport;
        int operational, flightHours;

        if (!getline(iss, id, '\t')) continue;
        if (!getline(iss, planeClassId, '\t')) continue;

        string operationalStr, flightHoursStr;
        if (!getline(iss, operationalStr, '\t')) continue;
        if (!getline(iss, baseAirport, '\t')) continue;
        if (!getline(iss, flightHoursStr)) continue;

        operational = stoi(operationalStr);
        flightHours = stoi(flightHoursStr);

        PlaneClass *pc = findPlaneClassById(planeClassId);
        if (pc == nullptr) {
            continue;
        }
        Airplane airplane(id, *pc, operational == 1, baseAirport, flightHours);
        addAirplane(airplane);
    }
    file.close();
    return true;
}

bool FleetManager::saveDestinationsToFile(const string &filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto &dest : destinations_) {
        file << dest.getCode() << "\t" << dest.getName() << "\t" << dest.getCity()
             << "\t" << dest.getCountry() << "\t" << dest.getRunwayLengthMeters()
             << "\t" << dest.getDistanceFromBaseKm() << endl;
    }
    file.close();
    return true;
}

bool FleetManager::loadDestinationsFromFile(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        istringstream iss(line);
        string code, name, city, country, runwayStr, distanceStr;

        if (!getline(iss, code, '\t')) continue;
        if (!getline(iss, name, '\t')) continue;
        if (!getline(iss, city, '\t')) continue;
        if (!getline(iss, country, '\t')) continue;
        if (!getline(iss, runwayStr, '\t')) continue;
        if (!getline(iss, distanceStr)) continue;

        double runwayLength = stod(runwayStr);
        double distance = stod(distanceStr);

        Destination dest(code, name, city, country, runwayLength, distance);
        addDestination(dest);
    }
    file.close();
    return true;
}

bool FleetManager::saveAllData() const {
    savePlaneClassesToFile(dataDirectory_ + "/plane_classes.txt");
    saveAirplanesToFile(dataDirectory_ + "/airplanes.txt");
    saveDestinationsToFile(dataDirectory_ + "/destinations.txt");
    return true;
}

bool FleetManager::loadAllData() {
    loadPlaneClassesFromFile(dataDirectory_ + "/plane_classes.txt");
    loadAirplanesFromFile(dataDirectory_ + "/airplanes.txt");
    loadDestinationsFromFile(dataDirectory_ + "/destinations.txt");
    return true;
}

void FleetManager::clearAllData() {
    airplanes_.clear();
    destinations_.clear();
    planeClasses_.clear();
}

ostream &operator<<(ostream &os, const FleetManager &manager) {
    os << "\nСИСТЕМА ЗА УПРАВЛЕНИЕ НА ФЛОТА" << endl;
    os << "Име на компанията:   " << manager.companyName_ << endl;
    os << "Директория с данни:  " << manager.dataDirectory_ << endl;
    os << "Общо класове:        " << manager.planeClasses_.size() << endl;
    os << "Общо самолети:       " << manager.airplanes_.size() << endl;
    os << "Общо дестинации:     " << manager.destinations_.size() << endl;
    return os;
}

void FleetManager::displayMainMenu() {
    cout << "\nСИСТЕМА ЗА УПРАВЛЕНИЕ НА АВИОФЛОТА" << endl;
    cout << "1. Управление на класове самолети" << endl;
    cout << "2. Управление на самолети" << endl;
    cout << "3. Управление на дестинации" << endl;
    cout << "4. Търсене на самолети за дестинация" << endl;
    cout << "5. Преглед на флота" << endl;
    cout << "6. Запазване на данните" << endl;
    cout << "7. Зареждане на данните" << endl;
    cout << "8. Добавяне на примерни данни" << endl;
    cout << "0. Изход" << endl;
    cout << "Въведете избор: ";
}

void FleetManager::viewPlaneClassDetails() {
    if (getPlaneClassCount() == 0) {
        cout << "\nНяма регистрирани класове самолети." << endl;
        return;
    }

    displayAllPlaneClasses(cout);

    string classId = Validator::getValidString("Въведете ID на класа (Производител Модел): ");
    PlaneClass* pc = findPlaneClassById(classId);

    if (pc == nullptr) {
        cout << "\nКласът самолет не е намерен." << endl;
        return;
    }

    cout << "\n" << *pc;
    cout << "\nИзчислени стойности:" << endl;
    cout << "Максимален обхват: " << fixed << setprecision(2)
              << pc->calculateMaxRange() << " км" << endl;
    cout << "Продължителност на полет за 1000 км: "
              << pc->calculateFlightDuration(1000) << " часа" << endl;
}

void FleetManager::handlePlaneClassMenu() {
    int choice;
    do {
        PlaneClass::displayMenu();
        choice = Validator::getValidInt("");

        switch (choice) {
            case 1: {
                cout << "\nДОБАВЯНЕ НА НОВ КЛАС САМОЛЕТ" << endl;
                try {
                    string manufacturer = Validator::getValidString("Производител (напр. Boeing, Airbus): ");
                    string model = Validator::getValidString("Модел (напр. 737-800, A320): ");
                    int seatCount = Validator::getValidPositiveInt("Брой места: ");
                    double minRunway = Validator::getValidPositiveDouble("Минимална дължина на пистата (метри): ");
                    double fuelConsumption = Validator::getValidPositiveDouble("Разход на гориво (литри/км/място): ");
                    double tankVolume = Validator::getValidPositiveDouble("Обем на резервоара (литри): ");
                    double avgSpeed = Validator::getValidPositiveDouble("Средна скорост (км/ч): ");
                    int crewCount = Validator::getValidPositiveInt("Необходим екипаж: ");

                    PlaneClass newClass(manufacturer, model, seatCount, minRunway,
                                       fuelConsumption, tankVolume, avgSpeed, crewCount);

                    if (!addPlaneClass(newClass)) {
                        cout << "\nНеуспешно добавяне. Класът вероятно вече съществува." << endl;
                    } else {
                        cout << "\nКласът самолет е добавен успешно!" << endl;
                        cout << newClass;
                    }
                } catch (const exception& e) {
                    cout << "\nГрешка: " << e.what() << endl;
                }
                break;
            }
            case 2:
                displayAllPlaneClasses(cout);
                break;
            case 3:
                viewPlaneClassDetails();
                break;
            case 0:
                cout << "Връщане към главното меню..." << endl;
                break;
            default:
                cout << "Невалиден избор. Моля, опитайте отново." << endl;
        }
    } while (choice != 0);
}

void FleetManager::viewAirplaneDetails() {
    if (getAirplaneCount() == 0) {
        cout << "\nНяма самолети във флота." << endl;
        return;
    }

    string id = Validator::getValidString("Въведете ID на самолета: ");
    Airplane* airplane = findAirplaneById(id);

    if (airplane == nullptr) {
        cout << "\nСамолетът не е намерен." << endl;
        return;
    }

    cout << "\n" << *airplane;
    cout << "\nДанни за класа:" << endl;
    cout << airplane->getPlaneClassRef();
}

void FleetManager::toggleOperationalStatus() {
    if (getAirplaneCount() == 0) {
        cout << "\nНяма самолети във флота." << endl;
        return;
    }

    string id = Validator::getValidString("Въведете ID на самолета: ");
    Airplane* airplane = findAirplaneById(id);

    if (airplane == nullptr) {
        cout << "Самолетът не е намерен." << endl;
        return;
    }

    airplane->setOperational(!airplane->isOperational());
    cout << "Оперативният статус е променен на: "
              << (airplane->isOperational() ? "Оперативен" : "Неоперативен") << endl;
}

void FleetManager::handleAirplaneMenu() {
    int choice;
    do {
        Airplane::displayMenu();
        choice = Validator::getValidInt("");

        switch (choice) {
            case 1: {
                cout << "\nДОБАВЯНЕ НА НОВ САМОЛЕТ" << endl;
                if (getPlaneClassCount() == 0) {
                    cout << "Няма налични класове самолети. Моля, първо добавете клас." << endl;
                    break;
                }
                cout << "\nНалични класове самолети:" << endl;
                displayAllPlaneClasses(cout);
                try {
                    string id = Validator::getValidString("ID на самолета (регистрационен номер): ");
                    string classId = Validator::getValidString("ID на класа (Производител Модел): ");
                    PlaneClass* pc = findPlaneClassById(classId);
                    if (pc == nullptr) {
                        cout << "Класът самолет не е намерен." << endl;
                        break;
                    }
                    string baseAirport = Validator::getValidString("Код на базовото летище: ");
                    Airplane newAirplane(id, *pc, true, baseAirport, 0);
                    if (!addAirplane(newAirplane)) {
                        cout << "\nНеуспешно добавяне. Самолетът вероятно вече съществува." << endl;
                    } else {
                        cout << "\nСамолетът е добавен успешно!" << endl;
                        cout << newAirplane;
                    }
                } catch (const exception& e) {
                    cout << "\nГрешка: " << e.what() << endl;
                }
                break;
            }
            case 2:
                displayAllAirplanes(cout);
                break;
            case 3:
                viewAirplaneDetails();
                break;
            case 4: {
                if (getAirplaneCount() == 0) {
                    cout << "\nНяма самолети във флота." << endl;
                    break;
                }
                displayAllAirplanes(cout);
                string id = Validator::getValidString("Въведете ID на самолета за премахване: ");
                if (!removeAirplaneById(id)) {
                    cout << "Самолетът не е намерен." << endl;
                } else {
                    cout << "Самолетът е премахнат успешно." << endl;
                }
                break;
            }
            case 5:
                toggleOperationalStatus();
                break;
            case 6: {
                if (getAirplaneCount() == 0) {
                    cout << "\nНяма самолети във флота." << endl;
                    break;
                }
                string id = Validator::getValidString("Въведете ID на самолета: ");
                Airplane* airplane = findAirplaneById(id);
                if (airplane == nullptr) {
                    cout << "Самолетът не е намерен." << endl;
                    break;
                }
                int hours = Validator::getValidPositiveInt("Въведете брой часове за добавяне: ");
                airplane->addFlightHours(hours);
                cout << "Добавени " << hours << " летателни часа." << endl;
                cout << "Общо летателни часове: " << airplane->getTotalFlightHours() << endl;
                break;
            }
            case 0:
                cout << "Връщане към главното меню..." << endl;
                break;
            default:
                cout << "Невалиден избор. Моля, опитайте отново." << endl;
        }
    } while (choice != 0);
}

void FleetManager::viewDestinationDetails() {
    if (getDestinationCount() == 0) {
        cout << "\nНяма регистрирани дестинации." << endl;
        return;
    }

    string code = Validator::getValidString("Въведете код на дестинацията: ");
    Destination* dest = findDestinationByCode(code);

    if (dest == nullptr) {
        cout << "\nДестинацията не е намерена." << endl;
        return;
    }

    cout << "\n" << *dest;
}

void FleetManager::handleDestinationMenu() {
    int choice;
    do {
        Destination::displayMenu();
        choice = Validator::getValidInt("");

        switch (choice) {
            case 1: {
                cout << "\nДОБАВЯНЕ НА НОВА ДЕСТИНАЦИЯ" << endl;
                try {
                    string code = Validator::getValidString("IATA код (напр. SOF, LHR): ");
                    string name = Validator::getValidString("Име на летището: ");
                    string city = Validator::getValidString("Град: ");
                    string country = Validator::getValidString("Държава: ");
                    double runwayLength = Validator::getValidPositiveDouble("Дължина на пистата (метри): ");
                    double distance = Validator::getValidNonNegativeDouble("Разстояние от базата (км): ");

                    Destination newDest(code, name, city, country, runwayLength, distance);

                    if (!addDestination(newDest)) {
                        cout << "\nНеуспешно добавяне. Дестинацията вероятно вече съществува." << endl;
                    } else {
                        cout << "\nДестинацията е добавена успешно!" << endl;
                        cout << newDest;
                    }
                } catch (const exception& e) {
                    cout << "\nГрешка: " << e.what() << endl;
                }
                break;
            }
            case 2:
                displayAllDestinations(cout);
                break;
            case 3:
                viewDestinationDetails();
                break;
            case 4: {
                if (getDestinationCount() == 0) {
                    cout << "\nНяма регистрирани дестинации." << endl;
                    break;
                }
                displayAllDestinations(cout);
                string code = Validator::getValidString("Въведете код на дестинацията за премахване: ");
                if (!removeDestinationByCode(code)) {
                    cout << "Дестинацията не е намерена." << endl;
                } else {
                    cout << "Дестинацията е премахната успешно." << endl;
                }
                break;
            }
            case 0:
                cout << "Връщане към главното меню..." << endl;
                break;
            default:
                cout << "Невалиден избор. Моля, опитайте отново." << endl;
        }
    } while (choice != 0);
}

void FleetManager::searchAirplanesForDestination() {
    cout << "\nТЪРСЕНЕ НА САМОЛЕТИ ЗА ДЕСТИНАЦИЯ" << endl;

    if (getAirplaneCount() == 0) {
        cout << "Няма самолети във флота." << endl;
        return;
    }

    cout << "\nОпции за търсене:" << endl;
    cout << "1. Търсене по код на дестинация" << endl;
    cout << "2. Търсене по дължина на пистата и разстояние" << endl;
    int searchChoice = Validator::getValidInt("Въведете избор: ");

    vector<Airplane*> compatibleAirplanes;

    if (searchChoice == 1) {
        if (getDestinationCount() == 0) {
            cout << "Няма регистрирани дестинации. Моля, използвайте опция 2." << endl;
            return;
        }

        displayAllDestinations(cout);
        string code = Validator::getValidString("Въведете код на дестинацията: ");

        Destination* dest = findDestinationByCode(code);
        if (dest == nullptr) {
            cout << "Дестинацията не е намерена." << endl;
            return;
        }

        cout << "\nТърсене на съвместими самолети за: " << dest->getDisplayString() << endl;
        cout << "Писта: " << dest->getRunwayLengthMeters() << " м, Разстояние: "
                  << dest->getDistanceFromBaseKm() << " км" << endl;

        compatibleAirplanes = findAirplanesForDestination(code);
    } else {
        double runwayLength = Validator::getValidPositiveDouble("Въведете дължина на пистата (метри): ");
        double distance = Validator::getValidNonNegativeDouble("Въведете разстояние от базата (км): ");

        compatibleAirplanes = findCompatibleAirplanes(runwayLength, distance);
    }

    cout << "\nРЕЗУЛТАТИ ОТ ТЪРСЕНЕТО" << endl;
    cout << "Намерени съвместими самолети: " << compatibleAirplanes.size() << "\n" << endl;

    if (compatibleAirplanes.empty()) {
        cout << "Не са намерени съвместими самолети за тази дестинация." << endl;
        cout << "\nВъзможни причини:" << endl;
        cout << "- Пистата е твърде къса за наличните самолети" << endl;
        cout << "- Разстоянието надвишава максималния обхват" << endl;
        cout << "- Всички съвместими самолети са неоперативни" << endl;
        return;
    }

    int count = 1;
    for (const auto* airplane : compatibleAirplanes) {
        cout << "[" << count++ << "] " << *airplane << endl;
    }
}

void FleetManager::addSampleData() {
    cout << "\nДОБАВЯНЕ НА ПРИМЕРНИ ДАННИ" << endl;

    try {
        PlaneClass boeing737("Boeing", "737-800", 189, 2500.0, 0.03, 26020.0, 842.0, 5);
        PlaneClass airbusA320("Airbus", "A320", 180, 2100.0, 0.028, 24210.0, 840.0, 4);
        PlaneClass embraerE190("Embraer", "E190", 114, 2000.0, 0.032, 13230.0, 823.0, 4);
        PlaneClass boeing777("Boeing", "777-300ER", 396, 3050.0, 0.025, 181280.0, 905.0, 10);
        PlaneClass airbusA380("Airbus", "A380", 525, 3000.0, 0.022, 320000.0, 900.0, 20);

        addPlaneClass(boeing737);
        addPlaneClass(airbusA320);
        addPlaneClass(embraerE190);
        addPlaneClass(boeing777);
        addPlaneClass(airbusA380);

        cout << "Добавени 5 класа самолети." << endl;

        Airplane plane1("LZ-SOF-001", boeing737, true, "SOF", 5000);
        Airplane plane2("LZ-SOF-002", boeing737, true, "SOF", 3200);
        Airplane plane3("LZ-SOF-003", airbusA320, true, "SOF", 4500);
        Airplane plane4("LZ-VAR-001", embraerE190, true, "VAR", 2800);
        Airplane plane5("LZ-VAR-002", embraerE190, false, "VAR", 6000);
        Airplane plane6("LZ-SOF-004", boeing777, true, "SOF", 12000);
        Airplane plane7("LZ-SOF-005", airbusA380, true, "SOF", 8000);

        addAirplane(plane1);
        addAirplane(plane2);
        addAirplane(plane3);
        addAirplane(plane4);
        addAirplane(plane5);
        addAirplane(plane6);
        addAirplane(plane7);

        cout << "Добавени 7 самолета." << endl;

        Destination sofia("SOF", "Летище София", "София", "България", 3600.0, 0.0);
        Destination varna("VAR", "Летище Варна", "Варна", "България", 2500.0, 380.0);
        Destination london("LHR", "Heathrow Airport", "London", "UK", 3900.0, 2020.0);
        Destination paris("CDG", "Charles de Gaulle", "Paris", "France", 4200.0, 1850.0);
        Destination dubai("DXB", "Dubai International", "Dubai", "UAE", 4500.0, 4100.0);
        Destination tokyo("NRT", "Narita International", "Tokyo", "Japan", 4000.0, 9100.0);
        Destination smallIsland("ISL", "Small Island Strip", "Island", "Pacific", 1500.0, 2000.0);

        addDestination(sofia);
        addDestination(varna);
        addDestination(london);
        addDestination(paris);
        addDestination(dubai);
        addDestination(tokyo);
        addDestination(smallIsland);

        cout << "Добавени 7 дестинации." << endl;
        cout << "\nПримерните данни са добавени успешно!" << endl;

    } catch (const exception& e) {
        cout << "Грешка при добавяне на примерни данни: " << e.what() << endl;
    }
}
