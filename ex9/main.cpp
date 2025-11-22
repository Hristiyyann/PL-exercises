/*
 * Exercise 9:
 * - Да се дефинира базов клас за електронни компоненти зададени с
 *   номенклатурен номер, наименование (например — съпротивление, кондензатор
 *   и т.н.), стойност (например 50,100 и т.н.) и мерна единица (pF, oM и т.н.)
 * - Да се дефинира производен клас за конкретен електронен компонент зададен
 *   с държава производител и цена.
 * - Класовете да включват конструктори, деструктори и член функции за извеждане.
 * - Да се добавят и изтриват елементи.
 * - Да се намерят кондензаторите, които имат стойност в зададени граници и да
 *   се изведе на екрана информацията за тези обекти.
 * - Да се предефинира операцията <<, която да се използва за извеждане на данните.
 * - Данните да се съхраняват във файл.
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

class Component
{
private:
    string itemNumber_;
    string name_;
    string measureUnit_;
    double value_;

public:
    Component(string itemNumber, string name, string measureUnit, double value)
        : itemNumber_(itemNumber), name_(name), measureUnit_(measureUnit), value_(value)
    {
    }

    ~Component() {}

    virtual string print() const
    {
        stringstream ss;

        ss << "Item number: " << itemNumber_ << endl;
        ss << "Name:" << name_ << endl;
        ss << "Measure unit" << measureUnit_ << endl;
        ss << "Value:" << value_ << endl;

        return ss.str();
    }

    friend ostream &operator<<(ostream &out, const Component &comp)
    {
        out << comp.print();
        return out;
    }

    string getItemNumber() const { return itemNumber_; }
    string getUnit() const { return measureUnit_; }
    double getValue() const { return value_; }
};

class ElectronicComponent : public Component
{
private:
    string producerCountry_;
    double price_;

public:
    ElectronicComponent(string itemNumber, string name, double value,
                        string unit, string country, double price)
        : Component(itemNumber, name, unit, value),
          producerCountry_(country), price_(price) {}

    ~ElectronicComponent() {}

    string print() const override
    {
        stringstream ss;
        ss << Component::print();
        ss << "Country producer: " << producerCountry_ << endl;
        ss << "Price: " << price_ << " BGN" << endl;
        return ss.str();
    }
};

class ElectronicComponentsManager
{
private:
    vector<ElectronicComponent> components_;

public:
    ElectronicComponentsManager() {}
    ~ElectronicComponentsManager() {}

    void addComponent(const ElectronicComponent &component)
    {
        components_.push_back(component);
    }

    void removeComponent(string itemNumber)
    {

        for (int index = 0; index < components_.size(); index++)
        {
            if (components_.at(index).getItemNumber() != itemNumber)
            {
                continue;
            }

            components_.erase(components_.begin() + index);
            cout << "The component was successfully removed! " << endl;
            return;
        }
    }

    void findCapacitorsWithin(double minValue, double maxValue)
    {
        for (const ElectronicComponent &component : components_)
        {
            if (component.getUnit().find("F") == string::npos)
            {
                continue;
            }

            const double componentValue = component.getValue();
            if (componentValue >= minValue && componentValue <= maxValue)
            {
                cout << component << endl;
            }
        }
    }

    void printAll()
    {
        cout << "\n=== All Components ===" << endl;
        for (const auto &comp : components_)
        {
            cout << comp << endl;
        }
    }

    void saveToFile(const string &filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const auto &comp : components_)
            {
                file << comp.print();
            }
            file.close();
            cout << "Data saved to " << filename << endl;
        }
    }
};

int main()
{
    ElectronicComponentsManager manager;

    manager.addComponent(ElectronicComponent("C001", "Ceramic Capacitor", 100, "pF", "Japan", 2.50));
    manager.addComponent(ElectronicComponent("R001", "Carbon Resistor", 1000, "Ohm", "Germany", 1.20));
    manager.addComponent(ElectronicComponent("C002", "Electrolytic Capacitor", 220, "uF", "China", 3.80));
    manager.addComponent(ElectronicComponent("C003", "Film Capacitor", 150, "nF", "USA", 4.00));

    manager.printAll();
    manager.findCapacitorsWithin(100, 250);

    manager.removeComponent("R001");
    manager.printAll();

    manager.saveToFile("components.txt");

    return 0;
}