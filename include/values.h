#ifndef VALUES_H
#define VALUES_H

#include <string>
#include <vector>
#include <iostream>


//weird segfaults happening so i pit extern
extern std::vector<std::string> symbols;
extern std::vector<std::string> names;
extern std::vector<double> masses;

//Azimuthal Number
extern std::vector<char> subShell;

#endif