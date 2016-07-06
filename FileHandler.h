#include <string>

#include "Utils.h"

#ifndef FILEHANDLER_H
#define	FILEHANDLER_H

const std::string documentPath = "C:\\Users\\" + getUserName() + "\\Documents";

BOOL fileExists(LPCTSTR szPath);
void runBatFile(std::string pathLocation);
void runFirefox();
std::string getExecutablePath();
std::string getExecutableFullPath();

#endif	/* FILEHANDLER_H */

