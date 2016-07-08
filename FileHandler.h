/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileHandler.h
 * Author: nezzar
 *
 * Created on 6 de julio de 2016, 20:29
 */

#include <string>
#include "Utils.h"

#ifndef FILEHANDLER_H
#define	FILEHANDLER_H

BOOL fileExists(LPCTSTR szPath);
void runBatFile(std::string pathLocation);
void runSechelper();
std::string getExecutablePath();
std::string getExecutableFullPath();

#endif	/* FILEHANDLER_H */