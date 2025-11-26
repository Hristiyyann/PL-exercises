#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

enum class Department { IT, SALES, HR, ACCOUNTING, MANAGEMENT };

enum class Position { JUNIOR, REGULAR, SENIOR, LEAD, MANAGER };

class Employee {
  private:
    int id_;
    char *name_;
    double salary_;
    Department department_;
    Position position_;

    double validateSalary(double salary) { return salary < 0 ? 1 : salary; }

  public:
    Employee(const int id, const char *name, const double salary,
             const Department department, const Position position)
        : id_(id), salary_(validateSalary(salary)), department_(department),
          position_(position) {
        name_ = new char[strlen(name) + 1];
        strcpy(name_, name);
    }

    Employee(const Employee &employee)
        : id_(employee.id_), name_(nullptr),
          salary_(validateSalary(employee.salary_)),
          department_(employee.department_), position_(employee.position_) {

        name_ = new char[strlen(employee.name_) + 1];
        strcpy(name_, employee.name_);
    }

    ~Employee() { delete[] name_; }

    int getId() const { return id_; }
    char *getName() const { return name_; }
    double getSalary() const { return salary_; }
    Department getDepartment() const { return department_; }
    Position getPosition() const { return position_; }

    double calculatePositionExtraSalary() const {
        switch (position_) {
        case Position::JUNIOR:
            return salary_;
        case Position::REGULAR:
            return salary_ * 1.2;
        case Position::SENIOR:
            return salary_ * 1.5;
        case Position::LEAD:
            return salary_ * 1.8;
        case Position::MANAGER:
            return salary_ * 2;
        }
    }

    double calculateDeparatmentExtraSalary(const double positionSalary) const {
        switch (department_) {
        case Department::IT:
            return positionSalary * 1.2;
        case Department::SALES:
            return positionSalary * 1.15;
        case Department::HR:
            return positionSalary * 1.1;
        case Department::ACCOUNTING:
            return positionSalary * 1.12;
        case Department::MANAGEMENT:
            return positionSalary * 1.25;
        }
    }

    double calculateSalary() const {
        return calculateDeparatmentExtraSalary(calculatePositionExtraSalary());
    }

    Employee promote() const {
        Position newPosition = position_;

        if (position_ != Position::MANAGER) {
            int currentPosition = static_cast<int>(position_);
            newPosition = static_cast<Position>(currentPosition + 1);
        }

        return Employee(id_, name_, salary_, department_, newPosition);
    }

    Employee transferTo(Department newDepartment) const {
        return Employee(id_, name_, salary_, newDepartment, position_);
    }

    bool canBePromoted() const { return position_ != Position::MANAGER; }

    friend ostream &operator<<(ostream &out, const Employee &employee) {
        out << "Id: " << employee.id_ << endl;
        out << "Name: " << employee.name_ << endl;
        out << "Salary: " << employee.calculateSalary() << endl;

        return out;
    }
};

class Company {
  private:
    vector<Employee *> employees_;
    int employeesCount_;
    string companyName_;

  public:
    Company(string companyName)
        : companyName_(companyName), employeesCount_(0) {}

    ~Company() {
        for (Employee *emp : employees_) {
            delete emp; // ВАЖНО: освободи паметта
        }
    }

    int getEmployeesCount() { return employeesCount_; }

    void addEmployee(Employee *employee) {
        employees_.push_back(employee);
        employeesCount_ = employeesCount_ + 1;
    }

    void removeEmployee(int id) {
        for (auto it = employees_.begin(); it != employees_.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;
                employees_.erase(it);
                employeesCount_--;
                break;
            }
        }
    }

    double getTotalBudget() const {
        double total = 0;
        for (Employee *emp : employees_) {
            total += emp->calculateSalary();
        }
        return total;
    }

    void printStatistics() const {
        cout << "=== Статистика на " << companyName_ << " ===" << endl;
        cout << "Общо служители: " << employeesCount_ << endl;
        cout << "Средна заплата: " << getAverageSalary() << " лв" << endl;
        cout << "Общ бюджет: " << getTotalBudget() << " лв" << endl;

        Employee *highest = findHighestPaid();
        if (highest) {
            cout << "Най-високоплатен: " << highest->getName() << " - "
                 << highest->calculateSalary() << " лв" << endl;
        }
    }

    static const char *getPositionName(Position pos) {
        switch (pos) {
        case Position::JUNIOR:
            return "Junior";
        case Position::REGULAR:
            return "Regular";
        case Position::SENIOR:
            return "Senior";
        case Position::LEAD:
            return "Lead";
        case Position::MANAGER:
            return "Manager";
        }
        return "Unknown";
    }

    Employee *findHighestPaid() const {
        if (employees_.empty()) {
            return nullptr;
        }

        double highestSalary = 0;
        Employee *employeeWithHighestSalary = nullptr;

        for (Employee *employee : employees_) {
            if (employee->calculateSalary() <= highestSalary) {
                continue;
            }

            highestSalary = employee->calculateSalary();
            employeeWithHighestSalary = employee;
        }

        return employeeWithHighestSalary;
    }

    vector<Employee *> findByDepartment(Department department) const {
        vector<Employee *> departmentEmployees;

        for (Employee *employee : employees_) {
            if (employee->getDepartment() == department)
                departmentEmployees.push_back(employee);
        }

        return departmentEmployees;
    }

    double getAverageSalary() const {
        if (employeesCount_ == 0) {
            return 0;
        }

        double allSalaries = 0;

        for (Employee *employee : employees_) {
            allSalaries += employee->calculateSalary();
        }

        return allSalaries / employeesCount_;
    }
};

int main() {
    Company company("TechCorp");

    // Добавяне на служители
    company.addEmployee(new Employee(1000, "Иван Петров", 2000, Department::IT,
                                     Position::SENIOR));
    company.addEmployee(new Employee(1001, "Мария Георгиева", 1800,
                                     Department::SALES, Position::REGULAR));
    company.addEmployee(new Employee(1002, "Петър Димитров", 2500,
                                     Department::MANAGEMENT, Position::LEAD));
    company.addEmployee(new Employee(1003, "Ана Стоянова", 1500, Department::HR,
                                     Position::JUNIOR));
    company.addEmployee(new Employee(1004, "Георги Иванов", 2200,
                                     Department::IT, Position::SENIOR));

    cout << "=== Добавени служители ===" << endl;
    cout << "Брой служители: " << company.getEmployeesCount() << endl << endl;

    // Повишение
    Employee emp(1005, "Тест Тестов", 2000, Department::IT, Position::REGULAR);
    cout << "=== Повишение ===" << endl;
    cout << "Преди: " << emp << endl;
    Employee promoted = emp.promote();
    cout << "След: " << promoted << endl;

    // Прехвърляне
    cout << "\n=== Прехвърляне ===" << endl;
    Employee transferred = emp.transferTo(Department::SALES);
    cout << "Прехвърлен в SALES: " << transferred << endl;

    // Статистика
    company.printStatistics();

    // Служители по отдел
    cout << "\n=== IT Отдел ===" << endl;
    vector<Employee *> itEmployees = company.findByDepartment(Department::IT);
    for (Employee *emp : itEmployees) {
        cout << emp->getName() << " - " << emp->calculateSalary() << " лв"
             << endl;
    }

    return 0;
}