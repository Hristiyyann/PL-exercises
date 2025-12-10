#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

int poolSize = 2000;
string poolMode = "leaking";  // Започваме с изтичане
mutex poolSizeMutex;

void waterPouring(int rate) {
    while (true) {
        poolSizeMutex.lock();
        
        // Влива само в режим "pouring"
        if (poolMode == "pouring") {
            poolSize += rate;  // УВЕЛИЧАВА водата
            cout << "Вливане " << rate << " m³/h - Ниво: " << poolSize << " m³" << endl;
            
            // Ако достигне 2000, премини в режим изтичане
            if (poolSize >= 2000) {
                poolSize = 2000;
                poolMode = "leaking";
                cout << "*** Достигнато ниво 2000 - Спира вливането ***" << endl;
            }
        }
        
        poolSizeMutex.unlock();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

void waterLeaking(int rate, int pipeId) {
    while (true) {
        poolSizeMutex.lock();
        
        // Изтича само в режим "leaking"
        if (poolMode == "leaking") {
            poolSize -= rate;  // НАМАЛЯВА водата
            cout << "Изтичане " << rate << " m³/h (тръба " << pipeId << ") - Ниво: " 
                 << poolSize << " m³" << endl;
            
            // Ако достигне 800, премини в режим вливане
            if (poolSize <= 800) {
                poolSize = 800;
                poolMode = "pouring";
                cout << "*** Достигнато ниво 800 - Спира изтичането ***" << endl;
            }
        }
        
        poolSizeMutex.unlock();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    cout << "Начално ниво: " << poolSize << " m³" << endl;
    cout << "Начален режим: " << poolMode << endl << endl;
    
    thread pour(waterPouring, 20);
    thread leak1(waterLeaking, 10, 1);
    thread leak2(waterLeaking, 5, 2);

    pour.join();
    leak1.join();
    leak2.join();
    
    return 0;
}