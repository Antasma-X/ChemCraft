#ifndef COMPOUND_H
#define COMPOUND_H



#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "element.h"

class Compound{
	std::vector<Element> atoms;
	std::map<Element,std::vector<Element*>> bonds;

	public:

	Compound(Element element){
		atoms.emplace_back(element);
		bonds[element];
	}

	int addElement(Element& firstElement, Element& secondElement, Compound& secondCompound){


		if((firstElement^secondElement)==0){
			//throe and stuff
			return 0;
		}
		//also if second element nit in secondcompoung get mad
		
		atoms.emplace_back(secondElement);
		bonds[firstElement].emplace_back(&secondElement);
		bonds[secondElement].emplace_back(&firstElement);
	}

	int addElement(Element& firstElement, Element& secondElement){


		if((firstElement^secondElement)==0){
			//throe and stuff
			return 0;
		}
		atoms.emplace_back(secondElement);
		bonds[firstElement].emplace_back(&secondElement);
		bonds[secondElement].emplace_back(&firstElement);
	}
};


//recursion









#endif