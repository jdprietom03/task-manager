#include <windows.h> 
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream> 
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <algorithm>
#include <Psapi.h>
#include "constants.h"

#pragma comment(lib, "psapi.lib")

using namespace std;
class Task
{
    public:
        string name;
        int priority;
        int burstTime;
        int arrivalTime;
        int subprocesses;
        unsigned int memoryUsage = 0;
        
        Task(string name, DWORD processID){
            this->name = name;
            this->subprocesses = 0;
            this->getMemoryInfo(processID);
        }

        void incr(DWORD processID)
        {
            this->subprocesses++;
            this->getMemoryInfo(processID);
        }

        string toString()
        {
            return this->name + " " + to_string(this->subprocesses) + " " + to_string(this->memoryUsage);
        }

        
        void getMemoryInfo( DWORD processID )
        {
            HANDLE hProcess;
            PROCESS_MEMORY_COUNTERS pmc;

            hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ,
                                    FALSE, processID );
            if (NULL == hProcess)
                return;
            if ( GetProcessMemoryInfo( hProcess, &pmc, sizeof(pmc)) )
            {
                //printf( "Process ID: %u\t\tWorkingSetSize: %uMB \n", processID, pmc.WorkingSetSize/1024/1024 );
                //What is the memory usage of the process
                this->memoryUsage += pmc.WorkingSetSize / 1024 / 1024;
            }
            CloseHandle( hProcess );
        }

        void getCpuInfo()
        {
            FILETIME ftime, fsys, fuser;
            ULARGE_INTEGER now, sys, user;
            double percent;

            GetSystemTimeAsFileTime(&ftime);
            memcpy(&now, &ftime, sizeof(FILETIME));

            GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
            memcpy(&sys, &fsys, sizeof(FILETIME));
            memcpy(&user, &fuser, sizeof(FILETIME));

            percent = (sys.QuadPart - lastSysCPU) +
                    (user.QuadPart - lastUserCPU);
            percent /= (now.QuadPart - lastCPU);
            percent /= numProcessors;
            lastCPU = now.QuadPart;
            lastUserCPU = user.QuadPart;
            lastSysCPU = sys.QuadPart;

            printf("CPU usage: %6.2f%%\n", percent * 100);
        }
};