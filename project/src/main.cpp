#include <iostream>
#include "../headers/FleetManager.h"
#include "../headers/Validator.h"

using namespace std;

int main() {
    FleetManager manager("България Еър Флот", "./data");

    cout << "СИСТЕМА ЗА УПРАВЛЕНИЕ НА АВИОФЛОТА" << endl;
    cout << "Добре дошли в системата за управление на флота!" << endl;
    cout << "Управление на флота за: " << manager.getCompanyName() << endl;

    cout << "\nОпит за зареждане на съществуващи данни..." << endl;
    if (!manager.loadAllData()) {
        cout << "Не са намерени съществуващи данни или зареждането е неуспешно." << endl;
        cout << "Използвайте опция 8 за добавяне на примерни данни." << endl;
    } else {
        cout << "Данните са заредени успешно!" << endl;
        cout << manager;
    }

    int choice;
    do {
        FleetManager::displayMainMenu();
        choice = Validator::getValidInt("");

        switch (choice) {
            case 1:
                manager.handlePlaneClassMenu();
                break;
            case 2:
                manager.handleAirplaneMenu();
                break;
            case 3:
                manager.handleDestinationMenu();
                break;
            case 4:
                manager.searchAirplanesForDestination();
                break;
            case 5:
                cout << manager;
                break;
            case 6:
                cout << "\nЗапазване на данните..." << endl;
                if (!manager.saveAllData()) {
                    cout << "Внимание: Някои данни може да не са запазени." << endl;
                    break;
                }
                cout << "Всички данни са запазени успешно!" << endl;
                break;
            case 7:
                cout << "\nЗареждане на данните..." << endl;
                manager.clearAllData();
                if (!manager.loadAllData()) {
                    cout << "Внимание: Някои данни може да не са заредени." << endl;
                    break;
                }
                cout << "Всички данни са заредени успешно!" << endl;
                cout << manager;
                break;
            case 8:
                manager.addSampleData();
                break;
            case 0: {
                cout << "\nЖелаете ли да запазите данните преди изход? (1=Да, 0=Не): ";
                int saveChoice = Validator::getValidInt("");
                if (saveChoice == 1 && manager.saveAllData()) {
                    cout << "Данните са запазени успешно!" << endl;
                }
                cout << "\nБлагодарим ви, че използвахте системата за управление на флота!" << endl;
                cout << "Довиждане!" << endl;
                break;
            }
            default:
                cout << "Невалиден избор. Моля, опитайте отново." << endl;
        }
    } while (choice != 0);

    return 0;
}
