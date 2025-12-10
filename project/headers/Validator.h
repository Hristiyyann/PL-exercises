#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <iostream>
#include <limits>

using namespace std;

class Validator {
public:
    static void clearInputBuffer();
    static int getValidInt(const string& prompt);
    static int getValidPositiveInt(const string& prompt);
    static double getValidDouble(const string& prompt);
    static double getValidPositiveDouble(const string& prompt);
    static double getValidNonNegativeDouble(const string& prompt);
    static string getValidString(const string& prompt);

private:
    Validator() = delete;
    Validator(const Validator&) = delete;
    Validator& operator=(const Validator&) = delete;
};

#endif
