#include "../headers/Validator.h"

using namespace std;

void Validator::clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int Validator::getValidInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        cout << "Невалиден вход. Моля, въведете валидно число." << endl;
        clearInputBuffer();
    }
}

int Validator::getValidPositiveInt(const string &prompt) {
    int value;
    while (true) {
        value = getValidInt(prompt);
        if (value > 0) {
            return value;
        }
        cout << "Стойността трябва да е по-голяма от 0. Моля, опитайте отново." << endl;
    }
}

double Validator::getValidDouble(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        }
        cout << "Невалиден вход. Моля, въведете валидно число." << endl;
        clearInputBuffer();
    }
}

double Validator::getValidPositiveDouble(const string &prompt) {
    double value;
    while (true) {
        value = getValidDouble(prompt);
        if (value > 0.0) {
            return value;
        }
        cout << "Стойността трябва да е по-голяма от 0. Моля, опитайте отново." << endl;
    }
}

double Validator::getValidNonNegativeDouble(const string &prompt) {
    double value;
    while (true) {
        value = getValidDouble(prompt);
        if (value >= 0.0) {
            return value;
        }
        cout << "Стойността не може да е отрицателна. Моля, опитайте отново." << endl;
    }
}

string Validator::getValidString(const string &prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (!value.empty()) {
            return value;
        }
        cout << "Стойността не може да е празна. Моля, опитайте отново." << endl;
    }
}
