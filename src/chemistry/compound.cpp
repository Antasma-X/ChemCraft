#include "compound.h"

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
	
	std::vector<std::pair<Element*,int>> currentBonds;

	


	std::vector<Element*> currentCovalentBonds=element.getCurrentCovalentBonds();
	
	
	
	for(auto el: currentCovalentBonds){
		
		currentBonds.emplace_back(std::make_pair(el,0));
		
	}
	
	
	std::vector<std::pair<Element*,int>> currentIonic=element.getCurrentIonicBonds();
	std::vector<std::pair<Element*,int>> currentDative=element.getCurrentDativeBonds();
	currentBonds.insert(currentBonds.begin(),currentIonic.begin(),currentIonic.end());
	currentBonds.insert(currentBonds.begin(),currentDative.begin(),currentDative.end());
	bonds[&element]=currentBonds;

	for(auto nextElement: currentBonds){
		if(std::find(atoms.begin(),atoms.end(),nextElement.first)==atoms.end()){

			createCompoundFromElementUtil(*nextElement.first,atoms,bonds);
		}
	}
}

//fail
void Compound::printCompoundUtil(Element* current,std::vector<Element*>& traversed,std::vector<std::string>& structure, std::array<int,2> location){

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

Compound::Compound(int atomicNumber, double atomicMass, int charge,int v){
	Element* element;
	try{
		element=new Element(atomicNumber,atomicMass,charge,v);
	}
	catch(std::invalid_argument& e){
		throw;
	}

	atoms.emplace_back(element);
	bonds[element];

	listOfCompounds.emplace_back(this);

}

Compound::Compound(std::string compound){

	std::string allowedChars="0123456789-/;&.+)";
	bool isValid =std::all_of(compound.begin(), compound.end(), [&](char c) {
		return allowedChars.find(c) != std::string::npos;});

	if(!isValid){
		throw std::invalid_argument("String is Invalid");
	}

	int index=std::distance(compound.begin(),std::find(compound.begin(),compound.end(),';'));
	std::string name=compound.substr(0,index);
	std::string bondString=compound.substr(index+1,compound.size()-index-1);
	std::vector<std::string> atomList={};
	std::vector<std::string> bondList={};

	std::string individual="";
	for(auto txt: name){
		if(txt=='/'){
			atomList.emplace_back(individual);
			individual="";
			continue;
		}
		individual+=txt;
	}
	individual	="";
	for(auto txt: bondString){
		if(txt=='/'){
			bondList.emplace_back(individual);
			individual="";
			continue;
		}
		individual+=txt;
	}

	for(auto atom:atomList){

		//atomic Number
		std::string atomicNumber="";
		auto it=atom.begin();
		for(;it !=atom.end();it++){
			if(*it=='&'){
				it++;
				break;
			}
			atomicNumber+=*it;
		}
		//atomic mass
		std::string atomicMass="";
		for(;it !=atom.end();it++){
			if(*it=='&'){
				it++;
				break;
			}
			atomicMass+=*it;
		}

				//charge
		std::string charge="";
		for(;it !=atom.end();it++){
			if(*it=='&'|| it==atom.end()){
				it++;
				break;
			}
			charge+=*it;
		}

		//v
		std::string v="";
		for(;it !=atom.end();it++){
			if(*it=='&'|| it==atom.end()){
				it++;
				break;
			}
			v+=*it;
		}

		Element* el;
		try{
			
			el=new Element(stoi(atomicNumber),stof(atomicMass),stoi(charge),stoi(v));
		}
		catch(std::invalid_argument& e){
			throw;
		}
		
		atoms.emplace_back(el);
	}

	int i =0;
	individual="";
	index=0;
	std::string bondTypeString="";
	std::string indexString="";

	//from jhere
	for(auto atomBonds :bondList){

		std::vector<std::string> individualAtomBonds={};
		for(auto txt: atomBonds){
			if(txt==')'){
				individualAtomBonds.emplace_back(individual);
				individual="";
			}
			else{
			individual+=txt;		}	
		}
		Element* currentEl=atoms[i];
		for(auto bond:individualAtomBonds){
			//index
			auto it=bond.begin();
			for(;it !=bond.end();it++){
				if(*it=='&'){
					it++;
					break;
				}
				indexString+=*it;
			
			}
			//bond type
			for(;it !=bond.end();it++){
				if(*it=='&'|| it==bond.end()){
					it++;
					break;
				}
				bondTypeString+=*it;
				

			}
			int bondType=stoi(bondTypeString);
			int index=stoi(indexString);
			
			if(i<index){
				if(bondType==0){
					if((*currentEl * *atoms[index])==0){
						throw std::invalid_argument("Covalent Bond could not form");
					}
					
				}
				else if(bondType==-1){
					if((*currentEl ^ *atoms[index])==0){
						throw std::invalid_argument("Ionic Bond could not form");
					}
				}
				else if(bondType==1){
					if((*atoms[index] ^ *currentEl)==0){
						throw std::invalid_argument("Ionic Bond could not form");
					}
				}
				else if(bondType==-2){
					if((*currentEl && *atoms[index])==0){
						throw std::invalid_argument("Dative Bond could not form");
	
					}
				}
				else if(bondType==2){
					if((*atoms[index] && *currentEl)==0){
						throw std::invalid_argument("Dative Bond could not form");
					}
				}
				else{
					throw std::invalid_argument("Invalid Bond Type");
				}
			}


			bonds[currentEl].emplace_back(std::make_pair(atoms[index],bondType));
			indexString="";
			bondTypeString="";
		}
		i++;
	}

}

Compound::~Compound(){

	auto it=std::find(listOfCompounds.begin(),listOfCompounds.end(),this);
	if (it != listOfCompounds.end()){
		listOfCompounds.erase(it);
	}
	

	//desyory every element somehow idk
}

int Compound::addElement(Element& firstElement, Element& secondElement,int typeOfBond){

	if (!isAtomInCompound(firstElement) || isAtomInCompound(secondElement)){
		return 0;
	}

	if (typeOfBond==0){
		if((firstElement*secondElement)==0){
			return 0;
		}
	}
	else if(typeOfBond==-1){
		if((firstElement^secondElement)==0){
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((secondElement^firstElement)==0){
			return 0;
		}		
	}
	else if(typeOfBond==-2){
		if((firstElement&&secondElement)==0){
			return 0;
		}		
	}
	else if(typeOfBond==+2){
		if((secondElement&&firstElement)==0){
			return 0;
		}		
	}
	else{
		return 0;
	}

	atoms.emplace_back(&secondElement);
	bonds[&firstElement].emplace_back(std::make_pair(&secondElement,typeOfBond));
	bonds[&secondElement].emplace_back(std::make_pair(&firstElement,-typeOfBond));

	return 1;
}



int Compound::addElement(Element& firstElement, int atomicNumber, int typeOfBond){
	Element* newElement;
	try{
		newElement=new Element(atomicNumber);
	}
	catch(std::invalid_argument& e){
		return 0;
	} 
	if(addElement(firstElement,*newElement,typeOfBond)==0){
		free(newElement);
		return 0;
	}
	return addElement(firstElement,*newElement,typeOfBond);
}
 
int Compound::addElement(Element& firstElement, Element& secondElement, Compound& secondCompound,int typeOfBond){

	if((!isAtomInCompound(firstElement)) || (!secondCompound.isAtomInCompound(secondElement)) || this==&secondCompound){
		return 0;
	}

	if (typeOfBond==0){
		if((firstElement*secondElement)==0){
			return 0;
		}
	}
	else if(typeOfBond==-1){
		if((firstElement^secondElement)==0){
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((secondElement^firstElement)==0){
			return 0;
		}		
	}
	else if(typeOfBond==-2){
		if((firstElement&&secondElement)==0){
			return 0;
		}		
	}
	else if(typeOfBond==+2){
		if((secondElement&&firstElement)==0){
			return 0;
		}		
	}
	else{
		return 0;
	}

	atoms.insert(atoms.end(),secondCompound.atoms.begin(),secondCompound.atoms.end());
	bonds.insert(secondCompound.bonds.begin(),secondCompound.bonds.end());

	bonds[&firstElement].emplace_back(std::make_pair(&secondElement,typeOfBond));
	bonds[&secondElement].emplace_back(std::make_pair(&firstElement,-typeOfBond));

	return 1;
}

std::vector<Compound> Compound::removeElement(Element& firstElement){
	std::vector<Compound> newCompounds;
	std::vector<Element*> firstElementBonds=firstElement.getCurrentBonds();

	atoms.erase(std::find(atoms.begin(),atoms.end(),&firstElement));
	bonds.erase(bonds.find(&firstElement));

	if(!isAtomInCompound(firstElement)){
		return newCompounds;
	}
	
	for(auto bond: firstElement.getCurrentCovalentBonds()){
		if(((firstElement)/(*bond))==0){
			return newCompounds;
		}
	}

	for(auto bond: firstElement.getCurrentIonicBonds()){
		if(bond.second==-1){
			if(((firstElement)%(*bond.first))==0){
				return newCompounds;
			}
		}
		else if(bond.second==1){
			if(((*bond.first)%(firstElement))==0){
				return newCompounds;
			}
		}
		else{
			throw std::runtime_error("Ionic Bond has invalid number. Compound is corrupted");
		}
	}

	for(auto bond: firstElement.getCurrentDativeBonds()){
		if(bond.second==-2){
			if(((firstElement)||(*bond.first))==0){
				return newCompounds;
			}
		}
		else if(bond.second==2){
			if(((*bond.first)||(firstElement))==0){
				return newCompounds;
			}
		}
		else{
			throw std::runtime_error("Dative Bond has invalid number. Compound is corrupted");
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

			newCompounds.push_back(createCompoundFromElement(*bond));

		}
	}

	return newCompounds;
}

int Compound::createBond(Element& firstElement, Element& secondElement,	int typeOfBond){
	if(!isAtomInCompound(firstElement) || !isAtomInCompound(secondElement)){
		return 0;

	}

	if (typeOfBond==0){
		if((firstElement*secondElement)==0){
			return 0;
		}
	}
	else if(typeOfBond==-1){
		if((firstElement^secondElement)==0){
			return 0;
		}
	}
	else if(typeOfBond==1){
		if((secondElement^firstElement)==0){

			return 0;
		}		
	}
	else if(typeOfBond==-2){
		if((firstElement&&secondElement)==0){
			return 0;
		}		
	}
	else if(typeOfBond==+2){
		if((secondElement&&firstElement)==0){
			return 0;
		}		
	}
	else{
		return 0;
	}

	bonds[&firstElement].emplace_back(std::make_pair(&secondElement,typeOfBond));
	bonds[&secondElement].emplace_back(std::make_pair(&firstElement,-typeOfBond));

	return 1;
}

std::vector<Compound> Compound::removeBond(Element& firstElement, Element& secondElement, int typeOfBond){
	std::vector<Compound> newCompounds;

	if(!isAtomInCompound(firstElement) || !isAtomInCompound(secondElement)){
		return newCompounds;
	}

	if(typeOfBond==0){
		if(firstElement/secondElement==0){
			return newCompounds;

		}
	}
	else if(typeOfBond==1){
		if(firstElement%secondElement==0){
			return newCompounds;

		}		
	}
	else if(typeOfBond==-1){
		if((secondElement%firstElement)==0){

			return newCompounds;
		}		
	}
	else if(typeOfBond==-2){
		if((firstElement||secondElement)==0){

			return newCompounds;
		}		
	}
	else if(typeOfBond==2){
		if((secondElement||firstElement)==0){

			return newCompounds;
		}		
	}
	else{
		return newCompounds;
	}


	//erase stuff
	bonds[&firstElement].erase(std::find(bonds[&firstElement].begin(),bonds[&firstElement].end(),std::make_pair(&secondElement,typeOfBond)));
	bonds[&secondElement].erase(std::find(bonds[&secondElement].begin(),bonds[&secondElement].end(),std::make_pair(&firstElement,-typeOfBond)));
	

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

int Compound::hydrogenFiller(){
	std::vector<Element*> unstableAtoms=getUnstableAtoms();

	for(auto atom: unstableAtoms){
		if(atom->getValency()[0]==0 && atom->getValency()[1]==0){
			//destroy
			throw std::runtime_error("Unstable atoms contains Stable Atoms somehow");
		}
		else if(atom->getValency()[0]==1){
			Element* H1=new Element(1);

			if(addElement(*atom,*H1,1)==0){
				return 0;
			}
		}
		else if(atom->getValency()[1]==-1){
			Element* H1=new Element(1);

			if(addElement(*atom,*H1,-1)==0){
				return 0;
			}
		}
		else if(atom->getValency()[0]==2){
			Element* H1=new Element(1);
			Element* H2=new Element(1);
			if(addElement(*atom,*H1,1)==0){
				return 0;
			}
			if(addElement(*atom,*H2,1)==0){
				return 0;
			}
		}
		else{
			while(atom->getValency()[1]<0){
				Element* H1=new Element(1);
				
				if(addElement(*atom,*H1,0)==0){
					return 0;
				}
			}
		}
	}
	return 1;
}

bool Compound::isStable(){

	for(auto atom: atoms){
		if(atom->isStable()){
			continue;
		}
		return false;
	}
	return true;
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
	int charge=0;

	for (auto atom :atoms){
		if(listOfElements.find(atom->getAtomicNumber())==listOfElements.end()){
			listOfElements[atom->getAtomicNumber()]=1;
		}
		else{
			listOfElements[atom->getAtomicNumber()]++;
		}
		charge+=atom->getCharge();
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
	std::string superScript="";

	if(charge==0){
		superScript="";
	}
	else{
		if(charge>0){
			superScript+="⁺";
		}
		else{
			superScript+="⁻";
		}
		std::string temp = std::to_string(std::abs(charge));
		for(std::size_t i =0;i<temp.length();i++){
			//istg why is the compiler crying about string and char theyre the same thing
			superScript+=superScripts[temp.substr(i,1)];
		}
	}
	formula+=superScript;
	return formula;
}

std::string Compound::getCompoundString(){
	std::string name="";
	std::string bondString="";

	for(auto atom: atoms){
		int atomicNumber=atom->getAtomicNumber();
		int atomicMass=atom->getAtomicMass();
		int charge=atom->getCharge();
		int v=atom->getValency()[0]+charge-atom->getCurrentCovalentBonds().size();

		for(auto bond: atom->getCurrentDativeBonds()){
			if(bond.second==+2){
				v-=2;
			}
		}
//ngl this is ineffiecint but im not touching it
		for (auto bond: bonds[atom]){
			if(bond.second==0){
				bondString.append(std::to_string(std::distance(atoms.begin(),std::find(atoms.begin(),atoms.end(),bond.first))));
				bondString.append("&");
				bondString.append("0");
				bondString.append(")");
			}
			else if(bond.second==-1){
				bondString.append(std::to_string(std::distance(atoms.begin(),std::find(atoms.begin(),atoms.end(),bond.first))));
				bondString.append("&");
				bondString.append("-1");
				bondString.append(")");
				charge++;
				//because reveral required when actual bonding code
			}
			else if(bond.second==+1){
				bondString.append(std::to_string(std::distance(atoms.begin(),std::find(atoms.begin(),atoms.end(),bond.first))));
				bondString.append("&");
				bondString.append("1");
				bondString.append(")");
				charge--;
			}
			else if(bond.second==-2){
				bondString.append(std::to_string(std::distance(atoms.begin(),std::find(atoms.begin(),atoms.end(),bond.first))));
				bondString.append("&");
				bondString.append("-2");
				bondString.append(")");
			}
			else if(bond.second==+2){
				bondString.append(std::to_string(std::distance(atoms.begin(),std::find(atoms.begin(),atoms.end(),bond.first))));
				bondString.append("&");
				bondString.append("2");
				bondString.append(")");
			}
			else{
				throw std::runtime_error("Invalid bond value. Compound Corrupted");
			}
		}
		bondString.append("/");

		name.append(std::to_string(atom->getAtomicNumber()));
		name.append("&");
		if(atom->getAtomicMass()+0.01>masses[atom->getAtomicNumber()-1]&&atom->getAtomicMass()-0.01<masses[atom->getAtomicNumber()-1]){
			name.append("0");
		}
		else{
			name.append(std::to_string(atom->getAtomicMass()));
		}
		
		name.append("&");
		name.append(std::to_string(charge));
		name.append("&");
		name.append(std::to_string(v));
		name.append("/");
	}

	std::string compoundString=name+";"+bondString;

	return compoundString;
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
		if(!atom->isStable()){
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


 



// std::vector<Element*> Compound::getUnstableAtoms(){
// 	std::vector<Element*> ions;
// 	for(auto atom:atoms){
// 		if((atom->getValency()[0]!=0 && atom->getValency()[1]!=0)||atom->getAtomicNumber()>18){
// 			ions.emplace_back(atom);
// 		}
// 	}
// 	return ions;
// }










