#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int bankMoney = 20000;
string bankMode = "depositing";
mutex bankMoneyMutex;

void clientDeposit(int money) {
    while (true) {
        bankMoneyMutex.lock();

        if (bankMode == "depositing") {
            for (int index = 0; index < 4; index++) {
                bankMoney += money;
                cout << "Bank money after depositing: " << bankMoney << endl;
                this_thread::sleep_for(chrono::milliseconds(250));
                
                if (bankMoney >= 40000) {
                    bankMode = "crediting";
                    cout << "**** The bank stops depositing money ****" << endl;
                    break;
                }
            }

        }

        bankMoneyMutex.unlock();
    }
}

void clientCredit(int money) {
    while (true) {
        bankMoneyMutex.lock();

        if (bankMode == "crediting") {
            for (int index = 0; index < 4; index++) {
                bankMoney -= money;
                cout << "Bank money after crediting: " << bankMoney << endl;
                this_thread::sleep_for(chrono::milliseconds(250));

                if (bankMoney < 20000) {
                    bankMode = "depositing";
                    cout << "**** The bank stops crediting money ****" << endl;
                    break;
                }
            }
        }

        bankMoneyMutex.unlock();
    }
}

int main() {
    thread depositer(clientDeposit, 1000);

    thread creditor(clientCredit, 1500);

    depositer.join();
    creditor.join();

    return 0;
}