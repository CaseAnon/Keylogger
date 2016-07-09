#include <string>
#include "Utils.h"

#ifndef FILEHANDLER_H
#define	FILEHANDLER_H

BOOL fileExists(LPCTSTR szPath);
void runBatFile(std::string pathLocation);
void runLazagne();
void runSechelper();
std::string getExecutablePath();
std::string getExecutableFullPath();

#endif	/* FILEHANDLER_H */
