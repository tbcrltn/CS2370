#include <iostream>
#include <windows.h>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

string cpuline = "LOADING CPU.....\n";
string ramline = "LOADING RAM.....\n";
mutex mtx;

uint64_t FileTimeToInt64(const FILETIME& ft) {
    return (static_cast<uint64_t>(ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
}

double GetCPUUsage() {
    FILETIME idle1, kernel1, user1;
    FILETIME idle2, kernel2, user2;

    // First sample
    GetSystemTimes(&idle1, &kernel1, &user1);
    Sleep(100); // sample window (100ms is good)

    // Second sample
    GetSystemTimes(&idle2, &kernel2, &user2);

    uint64_t idleDiff   = FileTimeToInt64(idle2)   - FileTimeToInt64(idle1);
    uint64_t kernelDiff = FileTimeToInt64(kernel2) - FileTimeToInt64(kernel1);
    uint64_t userDiff   = FileTimeToInt64(user2)   - FileTimeToInt64(user1);

    uint64_t total = kernelDiff + userDiff;

    // CPU usage = 1 - (idle / total)
    double usage = 1.0 - (double(idleDiff) / double(total));
    return usage * 100.0;
}


void MonitorCPU(){
    while(true){
        {
        lock_guard<mutex> lock(mtx);
        cpuline = ("CPU: " + to_string(GetCPUUsage()) + "\n\n");
        }
        Sleep(500);
    }
}


void MonitorRam(){
    while(true){
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);

        if (GlobalMemoryStatusEx(&memInfo)) {
            DWORDLONG totalPhys = memInfo.ullTotalPhys;
            DWORDLONG availPhys = memInfo.ullAvailPhys;
            DWORDLONG usedPhys  = totalPhys - availPhys;

            double percentUsed = (double)usedPhys / (double)totalPhys * 100.0;

            {
            lock_guard<mutex> lock(mtx);

            ramline = ("Total RAM: " + to_string(totalPhys / (1024 * 1024)) + " MB\n" +
            "Used RAM: " + to_string(usedPhys / (1024 * 1024)) + " MB\n" +
            "Free RAM: " + to_string(availPhys / (1024 * 1024)) + " MB\n" +
            "Usage:     " + to_string(percentUsed) + "%\n\n");
            }
        }
        Sleep(500);
    }
}

void PrintContents(){
    while(true){
        {
        lock_guard<mutex> lock(mtx);
        cout << "\n\n\n" << "------------------------------------------------------------\n";
        cout << cpuline << ramline;
        }
        Sleep(500);
    }
}
//void MonitorNetwork();
//void MonitorUI();


int main(){
    thread cpu(MonitorCPU);
    thread ram(MonitorRam);
    //thread network(MonitorNetwork);
    //thread ui(MonitorUI);
    thread print(PrintContents);

    cpu.join();
    ram.join();
    //network.join();
    //ui.join();
    print.join();

    return 0;
}