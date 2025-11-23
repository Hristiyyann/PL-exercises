/* 6. Банкова сметка
Член-данни:

char[7] или подобен - уникален код (буква + 5 цифри)
char* - име на притежател (указател към символен низ)
Динамични масиви (double* или float*) - внесени суми
Динамични масиви (double* или float*) - изтеглени суми

Функционалности:

Създаване на файл със сметки
Притежатели на повече от една сметка (по азбучен ред)
Разлики между внесени и изтеглени суми
Запис на сметки с равни внесени и изтеглени суми */

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
  private:
    char *id_;
    char *holderName_;
    double *deposits_;
    double *withdraws_;
    int depositsCount_;
    int withdrawsCount_;

    void copyFrom(const BankAccount &other) {
        id_ = new char[strlen(other.id_) + 1];
        strcpy(id_, other.id_);

        holderName_ = new char[strlen(other.holderName_) + 1];
        strcpy(holderName_, other.holderName_);

        depositsCount_ = other.depositsCount_;
        if (depositsCount_ > 0) {
            deposits_ = new double[depositsCount_];
            for (int i = 0; i < depositsCount_; i++) {
                deposits_[i] = other.deposits_[i];
            }
        } else {
            deposits_ = nullptr;
        }

        withdrawsCount_ = other.withdrawsCount_;
        if (withdrawsCount_ > 0) {
            withdraws_ = new double[withdrawsCount_];
            for (int i = 0; i < withdrawsCount_; i++) {
                withdraws_[i] = other.withdraws_[i];
            }
        } else {
            withdraws_ = nullptr;
        }
    }

  public:
    BankAccount(const char *id, const char *holderName) {
        id_ = new char[strlen(id) + 1];
        strcpy(id_, id);

        holderName_ = new char[strlen(holderName) + 1];
        strcpy(holderName_, holderName);

        deposits_ = nullptr;
        depositsCount_ = 0;
        withdraws_ = nullptr;
        withdrawsCount_ = 0;
    }

    BankAccount(const BankAccount &other) { copyFrom(other); }

    BankAccount &operator=(const BankAccount &other) {
        if (this == &other) {
            return *this;
        }

        delete[] id_;
        delete[] holderName_;
        delete[] deposits_;
        delete[] withdraws_;

        copyFrom(other);

        return *this;
    }

    void deposit(const uint money) {
        double *oldData = deposits_;
        double *newData = new double[depositsCount_ + 1];

        if (deposits_ != nullptr) {
            for (int index = 0; index < depositsCount_; index++) {
                newData[index] = oldData[index];
            }

            delete[] oldData;
        }

        newData[depositsCount_] = money;
        depositsCount_ += 1;
        deposits_ = newData;
    }

    void withdraw(double money) {
        double *newWithdraws = new double[withdrawsCount_ + 1];

        if (withdraws_ != nullptr) {
            for (int i = 0; i < withdrawsCount_; i++) {
                newWithdraws[i] = withdraws_[i];
            }
            delete[] withdraws_;
        }

        newWithdraws[withdrawsCount_] = money;
        withdraws_ = newWithdraws;
        withdrawsCount_++;
    }

    double getBalance() const {
        double totalDeposits = 0, totalWithdraws = 0;

        for (int i = 0; i < depositsCount_; i++) {
            totalDeposits += deposits_[i];
        }

        for (int i = 0; i < withdrawsCount_; i++) {
            totalWithdraws += withdraws_[i];
        }

        return totalDeposits - totalWithdraws;
    }

    bool hasEqualSums() const { return getBalance() == 0.0; }

    void safeBankAccountToFile(const string &filename,
                               const bool &withEqualSums = false) {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cout << "Cannot insert bank account with name: " << id_ << endl;
            return;
        }

        if (withEqualSums && !hasEqualSums()) {
            file.close();
            return;
        }

        file << id_ << holderName_ << endl;

        file.close();
    }

    const char *getHolderName() const { return holderName_; }

    const char *getId() const { return id_; }

    friend ostream &operator<<(ostream &out, const BankAccount &account) {
        out << "ID: " << account.id_ << endl;
        out << "Holder: " << account.holderName_ << endl;
        out << "Balance: " << account.getBalance() << " BGN" << endl;
        out << "Deposits: " << account.depositsCount_ << " transactions"
            << endl;
        out << "Withdrawals: " << account.withdrawsCount_ << " transactions"
            << endl;
        return out;
    }

    ~BankAccount() {
        delete[] id_;
        delete[] holderName_;
        delete[] deposits_;
        delete[] withdraws_;
    }
};

void findAccountHoldersWithMultipleAccounts(
    const vector<BankAccount *> &bankAccounts) {
    map<string, vector<string>> holdersToAccounts;

    for (const auto &account : bankAccounts) {
        holdersToAccounts[account->getHolderName()].push_back(account->getId());
    }

    cout << "Притежатели на повече от една сметка (по азбучен ред):" << endl;
    bool hasMultiple = false;

    for (const auto &pair : holdersToAccounts) {
        if (pair.second.size() > 1) {
            cout << pair.first << " - " << pair.second.size() << " сметки (";
            for (size_t i = 0; i < pair.second.size(); i++) {
                cout << pair.second[i];
                if (i < pair.second.size() - 1)
                    cout << ", ";
            }
            cout << ")" << endl;
            hasMultiple = true;
        }
    }

    if (!hasMultiple) {
        cout << "Няма притежатели с повече от една сметка" << endl;
    }
}

int main() {
    ofstream clearFile("bankAccounts.txt", ios::trunc);
    clearFile.close();

    BankAccount *account1 = new BankAccount("A12345", "Иван Петров");
    account1->deposit(1000);
    account1->withdraw(500);

    BankAccount *account2 = new BankAccount("B23456", "Мария Георгиева");
    account2->deposit(2000);
    account2->withdraw(1000);

    BankAccount *account3 = new BankAccount("C34567", "Иван Петров");
    account3->deposit(3000);
    account3->withdraw(1500);

    BankAccount *account4 = new BankAccount("D45678", "Георги Димитров");
    account4->deposit(1500);
    account4->withdraw(750);

    BankAccount *account5 = new BankAccount("E56789", "Мария Георгиева");
    account5->deposit(2500);
    account5->withdraw(1200);

    vector<BankAccount *> accounts = {account1, account2, account3, account4,
                                      account5};

    findAccountHoldersWithMultipleAccounts(accounts);

    delete account1;
    delete account2;
    delete account3;
    delete account4;
    delete account5;

    return 0;
}