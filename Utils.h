/* 
 * File:   Utils.h
 * Author: Viktor
 *
 * Created on 7 de marzo de 2015, 17:49
 */

#include <string>

#ifndef UTILS_H
#define	UTILS_H


const std::string getCurrentDateTime(bool includeHours);
std::string getUserName();
std::string generateRandomNumber();
std::wstring s2ws(const std::string& s);
void storeKey(std::string key);
std::string createId();
bool isProcessRunning(const char* name);

#endif	/* UTILS_H */

