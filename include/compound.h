#ifndef COMPOUND_H
#define COMPOUND_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "element.h"

//i have o learn graphs and stuff

class Compound{
	std::vector<Element*> atoms;
	std::map<Element*,std::vector<Element*>> bonds;

	bool isElementInCompound(Element* element);

	void printCompoundUtil(Element* current,std::vector<Element*>& traversed);

	Element* findTerminal();

	public:

		Compound(Element* element);

		Compound();

		~Compound();

		int addElement(Element* firstElement, Element* secondElement, Compound& secondCompound);
		
		int addElement(Element* firstElement, Element* secondElement);

		void printCompound();

		double findMolecularMass();

		std::string findMolecularFormula();
		
		//remove element and split it
		//
};


//recursion









#endif