#include <windows.h> 
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream> 
#include <bits/stdc++.h>
#include "task.h"
#include <string>
#include <vector>
#include <algorithm>
#include <Psapi.h>
#include "constants.h"
#pragma comment(lib, "psapi.lib")

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forsn(i, s, n) for (int i = int(s); i < int(n); i++)

typedef unsigned long long ull;

using namespace std;

struct Comparator
{
    bool operator()(string a, string b){ 
        for(char &c : a){ 
            c=tolower(c);
        };

        for(char &c : b){ 
            c=tolower(c);
        };
        return a < b;
    };
};

int main( ){
    init();
	system("color F"); 
	// INTRODUCTION STRING #############################################################################################
	cout<<"################################################################################"<<endl;
	cout<<"######################### Task Process Manager ##############################"<<endl; 
	cout<<"################################################################################"<<endl;
    cout<<"#                                                                              #"<<endl;

	int run_this_program=1; 
	while(run_this_program==1){ 

		HANDLE hProcessSnap;
	  	HANDLE hProcess; 
	 	PROCESSENTRY32 pe32; 
	 	DWORD dwPriorityClass; 
	 	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 ); 
	 	pe32.dwSize = sizeof( PROCESSENTRY32 );
		
        map<string, Task*, Comparator> processes;
        while( Process32Next( hProcessSnap, &pe32 ) ){
            string processName = pe32.szExeFile;
            DWORD processID = pe32.th32ProcessID;

            if(processes.find(processName) == processes.end()){
                processes[processName] = new Task(processName, processID);
            }

			processes[processName]->incr(processID); 
		};
		
		cout<<"\t\t\tProcesses that are running"<<endl; 
		cout<<"Process Name || Number of calls || Memory Usage"<<endl; 
		for(auto process: processes){
            cout<<process.second->toString()<<endl;
		};
		cout<<""<<endl; 
		
		// cout<<"<PRESS ENTER TO GET UPDATED LIST OF RUNNING PROCESSES (the program will re-run)>."<<endl; // string added for UI purposes
		// cout<<"Otherwise, exit the program if you are finished."<<endl;
		// system("pause"); 
        break;
	};
	
    return 0;
}

void killTask(){
    string p2t; 
    cin>>p2t; 
    string namep = p2t;
    string cmmdtsk="taskkill /IM "+namep+" /F"; 
    system(cmmdtsk.c_str()); 
}
// run with: g++ -o main task.cpp -lkernel32 -lpsapi