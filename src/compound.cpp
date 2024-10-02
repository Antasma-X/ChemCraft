#include "../include/compound.h"

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

void Compound::createCompoundFromElementUtil(Element& element,std::vector<Element*>& atoms,std::map<Element*,std::vector<std::pair<Element*,int>>>& bonds){
	atoms.emplace_back(&element);
	
	std::vector<Element*> currentCovalentBonds=element.getCurrentCovalentBonds();
	std::vector<std::pair<Element*,int>> currentBonds;

	for(auto el: currentCovalentBonds){
		currentBonds.emplace_back(std::make_pair(el,0));
	}

	std::vector<std::pair<Element*,int>> currentIonic=element.getCurrentIonicBonds();
	currentBonds.insert(currentBonds.begin(),currentIonic.begin(),currentIonic.end());
	bonds[&element]=currentBonds;

	for(auto nextElement: currentBonds){
		if(std::find(atoms.begin(),atoms.end(),nextElement.first)!=atoms.end()){
			createCompoundFromElementUtil(*nextElement.first,atoms,bonds);
		}
	}
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

Compound::Compound(int atomicNumber, double atomicMass, int charge){
	//try combininjg
	Element* element=new Element(atomicNumber,atomicMass,charge);
	atoms.emplace_back(element);
	bonds[element];

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
	else if(typeOfBond==-1){
		if((firstElement^secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((secondElement^firstElement)==0){
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
	Element* newElement=new Element(atomicNumber);
	return addElement(firstElement,*newElement,typeOfBond);
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
	else if(typeOfBond==-1){
		if((firstElement^secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((secondElement^firstElement)==0){
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

std::vector<Compound> Compound::removeElement(Element& firstElement){
	std::vector<Compound> newCompounds;
	std::vector<Element*> firstElementBonds=firstElement.getCurrentBonds();

	atoms.erase(std::find(atoms.begin(),atoms.end(),&firstElement));
	bonds.erase(bonds.find(&firstElement));

	if(!isAtomInCompound(firstElement)){
		//error
	}
	
	for(auto bond: firstElement.getCurrentCovalentBonds()){
		(firstElement)/(*bond);
	}

	for(auto bond: firstElement.getCurrentIonicBonds()){
		if(bond.second==-1){
			(firstElement)%(*bond.first);
		}
		else if(bond.second==1){
			(*bond.first)%(firstElement);
		}
		else{
			//error
		}
	}

//fucking crybaby compiler
	for(auto bond:firstElementBonds){
		for(int i=-1;i<2;i++){
			auto it = std::find(bonds[bond].begin(),bonds[bond].end(),std::make_pair(&firstElement,i));
			if(it !=bonds[bond].end()){
				bonds[bond].erase(it);
			}
		}
	}

	if(isFullyConnected()){
		newCompounds.emplace_back(*this);
	}
	else{
		for(auto bond: firstElementBonds){
			newCompounds.emplace_back(createCompoundFromElement(*bond));
		}
	}

	return newCompounds;
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
	else if(typeOfBond==-1){
		if((firstElement^secondElement)==0){
			//throe and stuff
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((secondElement^firstElement)==0){
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

std::vector<Compound> Compound::removeBond(Element& firstElement, Element& secondElement, int typeOfBond){
	std::vector<Compound> newCompounds;

	if(!isAtomInCompound(firstElement) || !isAtomInCompound(secondElement)){
		return newCompounds;
		//throw error and stuff
	}

	if(typeOfBond==0){
		if(firstElement/secondElement==0){
			return newCompounds;
			//error
		}
	}
	else if(typeOfBond==1){
		if(firstElement%secondElement==0){
			return newCompounds;
			//error
		}		
	}
	else if(typeOfBond==-1){
		if((secondElement%firstElement)==0){
			//throe and stuff
			return newCompounds;
		}		
	}
	else{
		return newCompounds;
		//error
	}

	bonds[&firstElement].erase(std::find(bonds[&firstElement].begin(),bonds[&firstElement].end(),std::make_pair(&secondElement,typeOfBond)));
	bonds[&secondElement].erase(std::find(bonds[&firstElement].begin(),bonds[&firstElement].end(),std::make_pair(&firstElement,typeOfBond)));
	
	if(isFullyConnected()){
		newCompounds.emplace_back(*this);
	}
	else{
		newCompounds.emplace_back(createCompoundFromElement(firstElement));
		newCompounds.emplace_back(createCompoundFromElement(secondElement));
	}
	
	return newCompounds;
}

Compound Compound::createCompoundFromElement(Element& element){
	std::vector<Element*> atoms;
	std::map<Element*,std::vector<std::pair<Element*,int>>> bonds;

	createCompoundFromElementUtil(element,atoms,bonds);

	Compound newCompound(*atoms[0]);
	newCompound.atoms=atoms;
	newCompound.bonds=bonds;

	return newCompound;
}

int Compound::isStable(){

	for(auto atom: atoms){
		if (atom->getValency()[0]!=0 && atom->getValency()[1]!=0){
			return 0;
		}
	}
	return 1;
}

bool Compound::isFullyConnected(){
	// std::vector<Element*> terminals=findTerminals();
	// for(Element* element1: terminals){
	// 	terminals.erase(terminals.begin());
	// 	for(Element* element2: terminals){
	// 		if (!isConnected(element1,element2)){
	// 			return false;
	// 		}
	// 	}
	// }

	Element* current=atoms[0];

	std::vector<Element*> visited;
	visited.emplace_back(current);

	std::queue<Element*> q;
	q.push(current);

	while(!q.empty()){
		current=q.front();
		q.pop();

		for(auto node: current->getCurrentBonds()){
			if(std::find(visited.begin(),visited.end(),node) !=visited.end()){
				q.push(node);
				visited.emplace_back(node);
			}
		}
	}

	return visited.size()==atoms.size();
}

bool Compound::isConnected(Element* element1, Element* element2){

	if(element1==element2){
		return true;
	}

	Element* current=element1;
	std::stack<Element*> s;
	s.push(current);

	std::vector<Element*> visited;
	visited.emplace_back(current);

	while(!s.empty()){
		current=s.top();
		s.pop();

		for(auto node: current->getCurrentBonds()){
			if(std::find(visited.begin(),visited.end(),node) !=visited.end()){
				if(node==element2){
					return true;
				}

				s.push(node);
				visited.emplace_back(node);
			}
		}
	}
	return false;
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
			for(std::size_t i =0;i<temp.length();i++){
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

std::vector<Element*> Compound::getUnstableAtoms(){

	std::vector<Element*> unstableAtoms;
	for(auto atom:atoms){
		if(atom->getValency()[0]!=0 && atom->getValency()[1]!=0){
			unstableAtoms.emplace_back(atom);
		}
	}
	return unstableAtoms;
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
