#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

using namespace std;

mutex bankMutex;

int balance = 10000;
bool stopCredits = false;

int getRandomAmount ( int max ) {
    static random_device rd;
    static mt19937 gen ( rd () );
    uniform_int_distribution<> dist ( 1, max );
    return dist ( gen );
}

void depositorThread () {
    while ( true ) {
        this_thread::sleep_for ( chrono::milliseconds ( 500 ) );

        int amount = getRandomAmount ( 400 );

        lock_guard<mutex> lock ( bankMutex );
        balance += amount;

        cout << "[DEPOSIT] +" << amount << " | Balance = " << balance << endl;

        if ( balance >= 10000 ) {
            stopCredits = false;
        }
    }
}

void creditThread () {
    while ( true ) {
        this_thread::sleep_for ( chrono::milliseconds ( 700 ) );

        lock_guard<mutex> lock ( bankMutex );

        if ( stopCredits ) {
            continue;
        }

        int amount = getRandomAmount ( 500 );
        balance -= amount;

        cout << "[CREDIT] -" << amount << " | Balance = " << balance << endl;

        if ( balance <= 4000 ) {
            cout << "\n*** CREDITING PAUSED FOR 6 MONTHS ***\n\n";
            stopCredits = true;

            // simulate 6 months
            this_thread::sleep_for ( chrono::seconds ( 5 ) );
        }
    }
}

int main () {
    thread depositor ( depositorThread );
    thread creditor ( creditThread );

    depositor.join ();
    creditor.join ();

    return 0;
}
