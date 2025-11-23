/* 1. Банкови вложители и дати
Клас Date:

Полета за ден, месец, година (точният тип не е указан)
Get/set методи
Конструктор по подразбиране и с параметри

Клас BankDepositor:

char* или string - ЕГН
char* или string - Име на вложител
double/float - Сума пари (точният тип не е указан)
Date - Дата на попълване на влога
Методи за въвеждане, корекция и изтриване на данни
Предефиниране на operator<< за извеждане
Съхранение във файл

Допълнителни подусловия:

Изчисляване увеличение на капитала при годишна лихва 5%
При корекция да се преизчислява лихвата
Извеждане на вложители в нарастващ ред на сумата */

#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

const uint maxYear = 2025;

class Date {
  private:
    uint day_;
    uint month_;
    uint year_;

    bool isLeapYear(uint year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    uint validateDay(uint day, uint month, uint year) const {
        int monthsDays[12] = {
            31, isLeapYear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
            31};

        if (month < 1 || month > 12) {

            return 1;
        }

        uint maxDay = monthsDays[month - 1];
        return (day >= 1 && day <= maxDay) ? day : 1;
    }

    uint validateMonth(uint month) const {
        if (month >= 1 && month <= 12) {
            return month;
        }

        return 1;
    }

    uint validateYear(uint year) {
        if (year >= 1 && year <= maxYear) {
            return year;
        }

        return maxYear;
    }

  public:
    Date(uint day = 23, uint month = 11, uint year = maxYear)
        : month_(month), year_(year), day_(validateDay(day, month, year)) {}

    ~Date() {}

    uint getDay() const { return day_; }
    uint getMonth() const { return month_; }
    uint getYear() const { return year_; }

    void setDate(uint day, uint month, uint year) {
        month_ = validateMonth(month);
        year_ = validateYear(year);
        day_ = validateDay(day, month_, year_);
    }

    friend ostream &operator<<(ostream &out, const Date &date) {
        out << "Day: " << date.day_ << endl;
        out << "Month: " << date.month_ << endl;
        out << "Year: " << date.year_ << endl;

        return out;
    }
};

class BankDepositor {
  private:
    char *egn_;
    char *name_;
    double money_;
    double initialMoney_;
    Date date_;

  public:
    BankDepositor(const char *egn = nullptr, const char *name = nullptr,
                  double money = 0, Date date = Date())
        : egn_(nullptr), name_(nullptr), initialMoney_(money) {
        setEgn(egn);

        setName(name);

        money_ = money;
        date_ = date;
    }

    BankDepositor(const BankDepositor &other)
        : egn_(nullptr), name_(nullptr), money_(other.money_),
          date_(other.date_), initialMoney_(other.initialMoney_) {
        setEgn(other.egn_);
        setName(other.name_);
    }

    BankDepositor &operator=(const BankDepositor &other) {
        if (this != &other) {
            setEgn(other.egn_);
            setName(other.name_);
            money_ = other.money_;
            initialMoney_ = other.initialMoney_;
            date_ = other.date_;
        }
        return *this;
    }

    double getMoney() const { return money_; }

    void setEgn(const char *egn) {
        if (egn_ != nullptr) {
            delete[] egn_;
        }

        if (egn == nullptr || strlen(egn) == 0) {
            egn_ = new char[1];
            egn_[0] = '\0';
        } else {
            egn_ = new char[strlen(egn) + 1];
            strcpy(egn_, egn);
        }
    }

    void setName(const char *name) {
        if (name_ != nullptr) {
            delete[] name_;
        }

        if (name == nullptr || strlen(name) == 0) {
            name_ = new char[1];
            name_[0] = '\0';
        } else {
            name_ = new char[strlen(name) + 1];
            strcpy(name_, name);
        }
    }

    void depositMoney(double money) {
        if (money <= 0) {
            cout << "Invalid money amount. Money should be greater than 0"
                 << endl;
            return;
        }

        money_ += money;
    }

    void withdrawMoney(double money) {
        if (money > money_) {
            cout << "You cannot withdraw more than you have" << endl;
            return;
        }

        money_ -= money;
    }

    friend ostream &operator<<(ostream &out,
                               const BankDepositor &bankDepositor) {
        out << "Name: " << bankDepositor.name_ << endl;
        out << "EGN: " << bankDepositor.egn_ << endl;
        out << "Money: " << bankDepositor.money_ << endl;
        out << bankDepositor.date_ << endl;

        return out;
    }

    double calculateInterest() const { return money_ * 0.05; }
    void applyInterest() { money_ += calculateInterest(); }

    void updateMoney(double newAmount) {
        initialMoney_ = newAmount;
        money_ = newAmount;
        applyInterest();
    }

    void saveToFile(const string &filename) {
        ofstream file(filename, ios::app);
        if (!file.is_open()) {
            cout << "Cannot open this file: File name: " << filename << endl;
            return;
        }

        file << name_ << "|" << egn_ << "|" << money_ << "|" << date_.getDay()
             << "/" << date_.getMonth() << "/" << date_.getYear() << endl;

        file.close();
    }

    ~BankDepositor() {
        delete[] egn_;
        delete[] name_;
    }
};

void sortDepositorsByMoney(BankDepositor *depositors, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (depositors[j].getMoney() > depositors[j + 1].getMoney()) {
                BankDepositor temp = depositors[j];
                depositors[j] = depositors[j + 1];
                depositors[j + 1] = temp;
            }
        }
    }
}

int main() {
    ofstream clearFile("depositors.txt", ios::trunc);
    clearFile.close();

    BankDepositor depositors[3] = {
        BankDepositor("1234567890", "Ivan Petrov", 1000, Date(1, 1, 2024)),
        BankDepositor("0987654321", "Maria Georgieva", 2500, Date(15, 3, 2024)),
        BankDepositor("5555555555", "Georgi Dimitrov", 750, Date(10, 6, 2024))};

    cout << "Преди лихва:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << depositors[i] << endl;
    }

    for (int i = 0; i < 3; i++) {
        depositors[i].applyInterest();
    }

    cout << "\nСлед лихва (5%):" << endl;
    for (int i = 0; i < 3; i++) {
        cout << depositors[i] << endl;
    }

    sortDepositorsByMoney(depositors, 3);

    cout << "\nСортирани по сума:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << depositors[i] << endl;
    }

    for (int i = 0; i < 3; i++) {
        depositors[i].saveToFile("depositors.txt");
    }

    return 0;
}
