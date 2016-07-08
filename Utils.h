/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Utils.h
 * Author: nezzar
 *
 * Created on 6 de julio de 2016, 20:32
 */

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
