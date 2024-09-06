#include <iostream>
#include <vector>
#include <string>
#include <map>




struct Compound{
	std::vector<Element> atoms;
	std::map<Element,std::vector<Element*>> bonds;
};