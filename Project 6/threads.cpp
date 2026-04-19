#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <vector>

using namespace std;


int currentNumber = 2;
int totalPrimes = 0;
ofstream outFile("primes.dat");


mutex counterMutex;
mutex fileMutex;


int threadCounts[4] = {0, 0, 0, 0};


bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i <= n / 2; i += 2) {
        if (n % i == 0)
            return false;
    }
    return true;
}


void worker(int threadID) {
    while (true) {
        int num;

        {
            lock_guard<mutex> lock(counterMutex);
            if (currentNumber > 1000000)
                return;

            num = currentNumber;
            currentNumber++;
        }

       
        if (isPrime(num)) {
            // Lock file + total counter together
            lock_guard<mutex> lock(fileMutex);

            outFile << num << "\n";
            totalPrimes++;
            threadCounts[threadID]++;
        }
    }
}

int main() {
    vector<thread> threads;

 
    for (int i = 0; i < 4; i++) {
        threads.push_back(thread(worker, i));
    }


    for (auto &t : threads) {
        t.join();
    }

    outFile.close();

  
    cout << "Total primes found: " << totalPrimes << endl;

    for (int i = 0; i < 4; i++) {
        cout << "Thread " << i << " found: "
             << threadCounts[i] << " primes" << endl;
    }

    return 0;
}