#ifndef VALUES_H
#define VALUES_H

#include <string>
#include <vector>
#include <iostream>
#include <set>

//weird segfaults happening so i pit extern
extern std::vector<std::string> symbols;
extern std::vector<std::string> names;
extern std::vector<double> masses;

//Azimuthal Number
extern std::vector<std::string> subShell;

extern std::set<int> dBlockExceptions;
extern std::set<int> fBlockExceptions;

extern std::array<std::string,3> BONDSYMBOL;
extern std::map<std::string,std::string> subScripts;
#endif