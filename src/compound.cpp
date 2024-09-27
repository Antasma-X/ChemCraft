#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "../include/compound.h"
#include "../include/values.h"

std::vector<Compound*> Compound::listOfCompounds={};

bool Compound::isAtomInCompound(Element& element){
    return !(bonds.find(&element)==bonds.end());
}

std::vector<Element*>Compound::findTerminals(){
	std::vector<Element*> terminals;

	for(auto [key,value]: bonds){
		if (value.size()==1){
			terminals.emplace_back(key);
		}
	}

	return terminals;
}

//fail
void Compound::printCompoundUtil(Element* current,std::vector<Element*>& traversed,std::vector<std::string>& structure, std::array<int,2> location){
	//std::cout<<current->getSymbol();
	location[1]++;
	traversed.push_back(current);
	std::map<Element*,int> edges;

	for(auto bond: current->getCurrentCovalentBonds()){
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

	
	int pos=0;
	for(auto [key,value]: edges){
		//std::cout<<BONDSYMBOL[value-1]<<key->getSymbol();
		if(pos==0){
			structure[location[0]].insert(location[1],BONDSYMBOL[value-1]+key->getSymbol());
			location[1]+=1+key->getSymbol().size();
			printCompoundUtil(key,traversed,structure,location);
			location[1]-=1+key->getSymbol().size();

			location[0]++;
			location[1]-=1+key->getSymbol().size();
			
			pos++;
		}
		else if(pos==1){
			structure[location[0]].insert(location[1],BONDSYMBOL[value-1]);
			structure[location[0]+1].insert(location[1],key->getSymbol());
			location[0]++;
			location[1]+=key->getSymbol().size();
			printCompoundUtil(key,traversed,structure,location);
			location[0]--;
			location[1]-=key->getSymbol().size();

			location[0]-=1;
			pos++;
		}
		else if(pos==2){
			structure[location[0]].insert(location[1],BONDSYMBOL[value-1]);
			structure[location[0]-1].insert(location[1],key->getSymbol());
			printCompoundUtil(key,traversed,structure,location);
			location[0]--;
			location[1]--;
			pos++;
		}
		else if(pos==3){
			structure[location[0]].insert(location[1],(key->getSymbol())+BONDSYMBOL[value-1]);
			printCompoundUtil(key,traversed,structure,location);
			location[1]+=2;
			pos++;
		}
	}
	//extend for more bonds later rn just basic

}

//Public Functions
Compound::Compound(Element& element){
	atoms.emplace_back(&element);
	bonds[&element];

	listOfCompounds.emplace_back(this);
}

Compound::Compound(int atomicNumber){
	//try combininjg
	Element element(atomicNumber);
	atoms.emplace_back(&element);
	bonds[&element];

	listOfCompounds.emplace_back(this);
}


Compound::~Compound(){
	listOfCompounds.erase(std::find(listOfCompounds.begin(),listOfCompounds.end(),this));

	//desyory every element somehow idk
}

int Compound::addElement(Element& firstElement, Element& secondElement,int typeOfBond){

	if (!isAtomInCompound(firstElement) || isAtomInCompound(secondElement)){
		return 0;
	}

	if (typeOfBond==0){
		if((firstElement*secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((firstElement^secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else{
		return 0;
	}

	atoms.emplace_back(&secondElement);
	bonds[&firstElement].emplace_back(std::make_pair(&secondElement,typeOfBond));
	bonds[&secondElement].emplace_back(std::make_pair(&firstElement,typeOfBond));

	return 1;
}

int Compound::addElement(Element& firstElement, int atomicNumber, int typeOfBond){
	Element newElement(atomicNumber);
	return addElement(firstElement,newElement,typeOfBond);
}

int Compound::addElement(Element& firstElement, Element& secondElement, Compound& secondCompound,int typeOfBond){

	if((!isAtomInCompound(firstElement)) || (!secondCompound.isAtomInCompound(secondElement)) || this==&secondCompound){
		//Throe error an stuff
		return 0;
	}

	if (typeOfBond==0){
		if((firstElement*secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((firstElement^secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else{
		return 0;
	}

	atoms.insert(atoms.end(),secondCompound.atoms.begin(),secondCompound.atoms.end());
	bonds.insert(secondCompound.bonds.begin(),secondCompound.bonds.end());

	bonds[&firstElement].emplace_back(std::make_pair(&secondElement,typeOfBond));
	bonds[&secondElement].emplace_back(std::make_pair(&firstElement,typeOfBond));

	return 1;
	//~secondCompound(); idk how to
}

int Compound::createBond(Element& firstElement, Element& secondElement,	int typeOfBond){
	if(!isAtomInCompound(firstElement) || !isAtomInCompound(secondElement)){
		return 0;
		//throw error and stuff
	}

	if (typeOfBond==0){
		if((firstElement*secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((firstElement^secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else{
		return 0;
	}

	bonds[&firstElement].emplace_back(std::make_pair(&secondElement,typeOfBond));
	bonds[&secondElement].emplace_back(std::make_pair(&firstElement,typeOfBond));

	return 1;
}

int Compound::isStable(){

	for(auto atom: atoms){
		if (atom->getValency()[0]!=0 && atom->getValency()[1]!=0){
			return 0;
		}
	}
	return 1;
}

double Compound::getMolecularMass(){

	double molecularMass=0;
	for(auto atom: atoms){
		molecularMass+=atom->getAtomicMass();
	}

	return molecularMass;
}

std::string Compound::getMolecularFormula(){
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
		std::string number;
		if(value==1){
			number="";
		}
		else{
			std::string temp = std::to_string(value);
			for(int i =0;i<temp.length();i++){
				//istg why is the compiler crying about string and char theyre the same thing
				number=number+subScripts[temp.substr(i,1)];
			}
			
		}
		formula+=symbols[key-1] + number;
	}
	return formula;
}

std::vector<Element*> Compound::getAtoms(){
	return atoms;
}

std::map<Element*,std::vector<std::pair<Element*,int>>> Compound::getBonds(){
	return bonds;
}

std::vector<Compound*> Compound::getListOfCompounds(){
	return listOfCompounds;
}





void Compound::printCompound(){
    Element* terminal=findTerminals()[0];
	std::vector<Element*> traversed={};
	std::vector<std::string> structure={"","","","",""};
	structure[2].insert(0,terminal->getSymbol());
	printCompoundUtil(terminal,traversed,structure,{2,0});

	for(auto line: structure){
		std::cout<<line<<std::endl;
	}
}


std::vector<Compound> Compound::removeBond(Element& firstElement, Element& secondElement, int typeOfBond){

	if(!isAtomInCompound(firstElement) || !isAtomInCompound(secondElement)){
		return {};
		//throw error and stuff
	}

	if(typeOfBond==0){
		if(firstElement/secondElement==0){
			return {};
			//error
		}
	}
	else if(typeOfBond==1){
		if(firstElement%secondElement==0){
			return {};
			//error
		}		
	}
	else{
		return {};
		//error
	}

	bonds[&firstElement].erase()
	std::vector<Compound> newCompounds;
	

}

int Compound::isConnected(){

}