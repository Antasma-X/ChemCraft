#ifndef COMPOUND_H
#define COMPOUND_H



#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "../include/element.h"

class Compound{
	std::vector<Element> atoms;
	std::map<Element,std::vector<Element*>> bonds;
};












#endif