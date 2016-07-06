#include <string>

#ifndef UTILS_H
#define	UTILS_H

const std::string getCurrentDateTime(bool includeHours);
std::string getUserName();
std::string generateRandomNumber();
std::wstring s2ws(const std::string& s);
const wchar_t* s2wct(std::string path);
void storeKey(std::string key);
std::string createId();
bool isProcessRunning(const char* name);

#endif	/* UTILS_H */
