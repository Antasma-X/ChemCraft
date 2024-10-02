#ifndef MOLECULES_H
#define MOLECULES_H

#include <map>
#include <algorithm>
#include <cstdlib>
#include <numeric>

#include "compound.h"
#include "values.h"

Compound* makeMolecule(std::string name);

Compound* makeMolecule(int n);

Compound* generateMoleculeOfElement(int atomicNumber);

std::pair<Compound*,std::vector<std::pair<Element*,int>>> makeAnion(std::string name);

std::pair<Compound*,std::vector<std::pair<Element*,int>>> makeAnion(int n);

//1-118 for elelemnts than actual ions
std::pair<Compound*,std::vector<std::pair<Element*,int>>> makeCation(std::string name,int valency);

std::pair<Compound*,std::vector<std::pair<Element*,int>>> makeCation(int n,int valency);

//stock notation
Compound* makeSalt(std::string name);


#endif