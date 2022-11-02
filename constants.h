#include <windows.h> 
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream> 
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <algorithm>
#include <Psapi.h>


#pragma comment(lib, "psapi.lib")

using namespace std;

typedef unsigned long long ull;

static int numProcessors;
static ull lastCPU, lastSysCPU, lastUserCPU;
static HANDLE self;

static void init(){
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&lastCPU, &ftime, sizeof(FILETIME));

    cout<<"Number of processors: "<<numProcessors<<endl;
}