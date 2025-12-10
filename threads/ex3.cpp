#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int value = 1;
mutex valueMutex;

void comparator(int k) {
    while (true) {
        int sleepTime = 0;
        valueMutex.lock();

        cout << "Old value: " << value << endl;

        if (value % k != 0) {
            value++;
            sleepTime = k;
        } else if (value % (k * k) == 0) {
            value += (2 * k) + 1;
        } else if (value % k == 0) {
            value += k + 1;
            sleepTime = 1;
        }

        cout << "New value: " << value << endl;

        valueMutex.unlock();
        
        cout << "Thread with value: " << k
             << " start sleeping for: " << sleepTime << endl << endl;

        this_thread::sleep_for(chrono::seconds(sleepTime));
    }
}

int main() {
    cout << "Starting with value = " << value << "\n" << endl;

    thread t1(comparator, 3);
    thread t2(comparator, 5);
    thread t3(comparator, 7);
    thread t4(comparator, 17);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}