#ifndef VALUES_H
#define VALUES_H

#include "StdLibDependencies.h"

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
extern std::map<std::string,std::string> superScripts;

// extern std::map<std::string,std::string> molecules;
// extern std::vector<std::string> compoundNumbers;

//kep prefered valency first
extern std::map<int,std::vector<int>> higherValencies;
extern std::map<int,int> atomicity;



extern std::map<std::string,int> anions;
extern std::map<std::string,int> anionValencies;
extern std::map<std::string,int> cations;
extern std::map<std::string,int> cationValencies;
extern std::map<std::string,int> cationAtomicNumbers;
extern std::map<std::string,int> transitionMetalAtomicNumbers;

// extern std::vector<std::string> searchBar;

#endif