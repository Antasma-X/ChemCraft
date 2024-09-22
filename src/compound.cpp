#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "../include/compound.h"
#include "../include/values.h"

std::array<std::string,3> BONDSYMBOL={"-","=","\u2261"};

bool Compound::isElementInCompound(Element* element){
    //maybe change to check vector
    return !(bonds.find(element)==bonds.end());
}

Compound::Compound(Element* element){
	atoms.emplace_back(element);
	bonds[element];
}

int Compound::addElement(Element* firstElement, Element* secondElement, Compound& secondCompound){

	if((!isElementInCompound(firstElement)) || (!secondCompound.isElementInCompound(secondElement)) ){
		//Throe error an stuff
		return 0;
	}

	if((*firstElement**secondElement)==0){
		//throe and stuff
		return 0;
	}

	atoms.insert(atoms.end(),secondCompound.atoms.begin(),secondCompound.atoms.end());
	bonds.insert(secondCompound.bonds.begin(),secondCompound.bonds.end());

	bonds[firstElement].emplace_back(secondElement);
	bonds[secondElement].emplace_back(firstElement);
	//~secondCompound();
}

	int Compound::addElement(Element* firstElement, Element* secondElement){


	if((*firstElement^*secondElement)==0){
		//throe and stuff
		return 0;
	}
	atoms.emplace_back(secondElement);
	bonds[firstElement].emplace_back(secondElement);
	bonds[secondElement].emplace_back(firstElement);
	}

Compound::Compound()=delete;

Element* Compound::findTerminal(){

}
void Compound::printCompound(){
    Element* terminal=findTerminal();
	std::vector<Element*> traversed={};
	printCompoundUtil(terminal,traversed);


}
//supports 9 bonds at a time
//no cyclic
void Compound::printCompoundUtil(Element* current,std::vector<Element*>& traversed){
	std::cout<<current->getSymbol();

	std::map<Element*,int> edges;
	for(auto bond: current->bonds){
		if(std::find(traversed.begin(), traversed.end(), bond) != traversed.end()){
			continue;
		}
		if(edges.find(bond)==edges.end()){
			edges[bond]=1;
		}
		else{
			edges[bond]++;
		}
	}

	if(edges.size()>4){
		//no support
		return;
	}

	for(auto [key,value]: edges){
		std::cout<<BONDSYMBOL[value-1]<<key->getSymbol();
	}
	//extend for more bonds later rn just basic

	traversed.push_back(current);

	for(auto bond: current->bonds){
		if(std::find(traversed.begin(), traversed.end(), bond) != traversed.end()){
			continue;
		}
		printCompoundUtil(bond,traversed);
	}
}

double Compound::findMolecularMass(){

	double molecularMass=0;
	for(auto atom: atoms){
		molecularMass+=atom->getAtomicMass();
	}
}

std::string Compound::findMolecularFormula(){
	std::map<int,int> listOfElements;

	for (auto atom :atoms){
		if(listOfElements.find(atom->getAtomicNumber())==listOfElements.end()){
			listOfElements[atom->getAtomicNumber()]=1;
		}
		else{
			listOfElements[atom->getAtomicNumber()]++;
		}
	}
	std::string formula="";
	for(auto [key,value]: listOfElements){
		formula+=symbols[key] + std::to_string(value) + " ";
	}
	return formula;
}