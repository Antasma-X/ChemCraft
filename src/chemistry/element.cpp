#include "element.h"

constexpr int NUMBEROFSHELLS=9;

std::array<int,118> Element::numberOfEachElement={};
std::array <std::vector<Element*>,118> Element::elementList={};


std::string Element::findSymbol(int atomicNumber){
	return symbols[atomicNumber-1];
}

std::string Element::findName(int atomicNumber){
	return names[atomicNumber-1];
}

double Element::findMass(int atomicNumber){
	return masses[atomicNumber-1];
}

int Element::electronValue(int& electrons,int subShell){

	int value=2 + subShell*4;
	if (electrons>value){
		electrons-=value;

	}else{
		value=electrons;
		electrons=0;
	}

	return value;
}

std::vector<std::array<int,2>> Element::findCombinations(int n){
	std::vector<std::array<int,2>> combs;

	for(int i=0;i<=n;i++){
		if (i<=n-i){
			continue;
		}
		combs.push_back({i,n-i});
	}
	return combs;
}

std::map<std::string,int> Element::fillShells(int electrons){
	std::map<std::string,int> shells;
	int i=1;

	while(i < NUMBEROFSHELLS ){
		std::vector<std::array<int,2>> combinations=findCombinations(i);

		for (auto [j,k] : combinations){
			shells[std::to_string(j)+subShell[k]]=electronValue(electrons,k);
		}
		i++;
	}

	return shells;
}

std::map<std::string,int> Element::fillShells(int electrons, int exceptionNumber){
	std::map<std::string,int> shells=fillShells(electrons);

	if(exceptionNumber==1){
		int i=3;

		while(shells[std::to_string(i+1)+"d"]!=0){
			i++;
		}
		std::string firstDSubShell=std::to_string(i)+"d";
		std::string firstSSubShell=std::to_string(i+1)+"s";

		shells[firstDSubShell]++;
		shells[firstSSubShell]--;
	}
	else if(exceptionNumber==2){
		shells["4d"]+=2;
		shells["5s"]-=2;
	}
	else if(exceptionNumber==3){
		shells["6d"]--;
		shells["7p"]++;
	}
	else if(exceptionNumber==4){
		int i=4;

		while(shells[std::to_string(i+1)+"f"]!=0){
			i++;
		}
		std::string firstFSubShell=std::to_string(i)+"f";
		std::string firstDSubShell=std::to_string(i+1)+"d";

		shells[firstFSubShell]--;
		shells[firstDSubShell]++;
	}

	return shells;
}

bool Element::isNobleGasConfig(){
	
	if (shells["1s"]==2 && shells["2s"]==0){
		return true;
	}
	else if (shells["2p"]==6 && shells["3s"]==0){
		return true;
	}
	else if (shells["3p"]==6 && shells["4s"]==0){
		return true;
	}
	else if (shells["4p"]==6 && shells["5s"]==0){
		return true;
	}
	else if (shells["5p"]==6 && shells["6s"]==0){
		return true;
	}
	else if (shells["6p"]==6 && shells["7s"]==0){
		return true;
	}
	else if (shells["7p"]==6 && shells["8s"]==0){
		return true;
	}
	else{
		return false;
	}
}

void Element::addElectrons(int n){
	electrons+=n;
	//charge-=n;
	int valenceShell=findValenceShell();

	int i =0;
	while(true){
		if (shells[std::to_string(valenceShell)+subShell[i]]==2+4*i){
			i++;
			continue;
		}
		break;
	}

	while(true){
		if(i>=valenceShell){
			valenceShell++;

			//not sure to check again
			i=0;
		}
		if(shells[std::to_string(valenceShell)+subShell[i]]+n>2+4*i){

			n-=(2+4*i)-(shells[std::to_string(valenceShell)+subShell[i]]);
			shells[std::to_string(valenceShell)+subShell[i]]=2+4*i;
			
			i++;
		}else{
			shells[std::to_string(valenceShell)+subShell[i]]+=n;
			break;
		}
	}

	//to check
	valency[0]+=n;
	valency[1]+=n;


}

int Element::findValenceShell(){
	
	int maxShell=1;
	for (auto [key,value] : shells){
		if(maxShell<key[0]&&value !=0){
			maxShell=std::stoi(key);
		}
	}
	return maxShell;
}

bool Element::doesFollowOctet(int atomicNumber){
	
	if (atomicNumber>18){
		return false;
	}
	return true;
}

int Element::doesCovalentBondExist(const Element* secondElement){

	int index=-1;
	for(auto it=covalentBonds.begin();it!=covalentBonds.end();it++){
		if (*it==secondElement){
			index++;
			break;
		}
		index++;
	}
	return index;
}

int Element::doesIonicBondExist(const Element* secondElement){
	int index=-1;
	for(auto it=ionicBonds.begin();it!=ionicBonds.end();it++){
		if ((*it).first==secondElement){
			index++;
			break;
		}
		index++;
	}

	return index;
}

int Element::doesDativeBondExist(const Element* secondElement){
	int index=-1;
	for(auto it=dativeBonds.begin();it!=dativeBonds.end();it++){
		if ((*it).first==secondElement){
			index++;
			break;
		}
		index++;
	}

	return index;
}

std::array<int,2> Element::findValency(int atomicNumber,int charge,int v){
	//here
	std::array<int,2> valency;
	//std::cout<<atomicNumber<<"  "<<v<<std::endl;
	//v-=charge;
	if(doesFollowOctet(atomicNumber)){
		if (atomicNumber<=2){
			valency={atomicNumber,atomicNumber-2};
		}
		else if(atomicNumber<=10){
			valency={atomicNumber-2,atomicNumber-10};
		}
		else if(atomicNumber<=18){
			valency={atomicNumber-10,atomicNumber-18};
		}
	}
	//fuck the other weird valencies im loyal
	else if(atomicNumber==35||atomicNumber==53||atomicNumber==85||atomicNumber==117){
		valency={7,-1};
	}
	else{
		if(std::find(higherValencies[atomicNumber].begin(),higherValencies[atomicNumber].end(),v)!=higherValencies[atomicNumber].end()){
			valency={v,1000};
			//std::cout<<"hhsd"<<std::endl;
		}
		else{
			error->Push("Valency could not be found. Default valency will be used");
			//std::cout<<"sexxxyyyyyyy"<<v<<"   "<<atomicNumber<<std::endl;
			valency={higherValencies[atomicNumber][0],1000};
		}
	}
	//ceck
	valency[0]-=charge;
	valency[1]-=charge;

	return valency;
}
	
Element::Element(unsigned int atomicNumber, double atomicMass,int charge,int v){

	bool validMass=true;
	bool validCharge=true;
	//Sets Atomic Number, Symbol and Name
	if (atomicNumber<1 || atomicNumber>118){
		throw std::invalid_argument("Invalid Atomic Number");
	}
	else{
		this->atomicNumber=atomicNumber;
		symbol=findSymbol(atomicNumber);
		name=findName(atomicNumber);
	}

	//Sets Atomic Mass
	if (atomicMass<=atomicNumber && atomicNumber!=1){
		if(!(atomicMass<0.01&&atomicMass>-0.01)){
			validMass=false;
		}
		atomicMass=findMass(this->atomicNumber);
	}
	this->atomicMass=atomicMass;

	this->valency=findValency(atomicNumber, charge,v);

	//here
	if(this->valency[0]-charge<0 || (this->valency[1]+charge>0&&this->valency[1]!=1000)){
		validCharge=false;
		charge=0;
	}
	this->charge=charge;
	

	electrons=atomicNumber-charge;
	
	//Checks if element is an exception in shell filling
	int exceptionNumber=0;
	if(dBlockExceptions.find(atomicNumber)!=dBlockExceptions.end()){
		exceptionNumber=1;
	}
	else if(atomicNumber==46){
		exceptionNumber=2;
	}
	else if(atomicNumber==103){
		exceptionNumber=3;
	}
	else if(fBlockExceptions.find(atomicNumber)!=fBlockExceptions.end()){
		exceptionNumber=4;
	}

	if(exceptionNumber==0){
		shells=fillShells(electrons);
	}
	else{
		shells=fillShells(electrons,exceptionNumber);
	}
 
	numberOfEachElement[atomicNumber-1]++;
	elementList[atomicNumber-1].emplace_back(this);


	if(!validMass && !validCharge){
		error->Push("Invalid Mass and Charge. They have been reset");
		// isError=true;
		// errorMessage=;
	}
	else if(!validMass){
		error->Push("Invalid Mass. It has been reset");
		// isError=true;
		// errorMessage="Invalid Mass. It has been reset";
	}
	else if(!validCharge){
		error->Push("Invalid Charge. It has been reset");
		// isError=true;
		// errorMessage="Invalid Charge. It has been reset";
	}
}


Element::~Element(){
	numberOfEachElement[atomicNumber-1]--;
	elementList[atomicNumber-1].erase(std::find(elementList[atomicNumber-1].begin(),elementList[atomicNumber-1].end(),this));

	for(auto bond: covalentBonds){
		
		if(((*this)/(*bond))==0){
			error->Push("Atoms Do Not Have Covalent Bond. Compound should be destroyed immediately");
			// isError=true;
			// errorMessage="Atoms Do Not Have Covalent Bond. Compound should be destroyed immediately";
			// std::runtime_error("Atoms Do Not Have Covalent Bond");
		}
		
	}

	for(auto bond: ionicBonds){
		if(bond.second==-1){
			if(((*this)%(*bond.first))==0){
				error->Push("Atoms Do Not Have Ionic Bond. Compound should be destroyed immediately");
				// isError=true;
				// errorMessage="Atoms Do Not Have Ionic Bond. Compound should be destroyed immediately";
				// std::runtime_error("Atoms Do Not Have Ionic Bond");
			}
				
		}
		else if(bond.second==1){
			if(((*bond.first)%(*this))==0){
				error->Push("Atoms Do Not Have Ionic Bond. Compound should be destroyed immediately");

				//std::runtime_error("Atoms Do Not Have Ionic Bond");
			}
		}
		else{
			error->Push("Atoms Have Invalid Bond. Compound should be destroyed immediately");
			// isError=true;
			// errorMessage="Atoms Have Invalid Bond. Compound should be destroyed immediately";
			// throw std::runtime_error("Invalid Ionic Bond");
		}
	}

	for(auto bond: dativeBonds){
		if(bond.second==-2){
			if(((*this)||(*bond.first))==0){
				error->Push("Atoms Do Not Have Dative Bond. Compound should be destroyed immediately");
				// isError=true;
				// errorMessage="Atoms Do Not Have Dative Bond. Compound should be destroyed immediately";
				//std::runtime_error("Atoms Do Not Have Dative Bond");
			}
		}
		else if(bond.second==2){
			if(((*bond.first)||(*this))==0){
				error->Push("Atoms Do Not Have Dative Bond. Compound should be destroyed immediately");
				// isError=true;
				// errorMessage="Atoms Do Not Have Dative Bond. Compound should be destroyed immediately";
				//std::runtime_error("Atoms Do Not Have Dative Bond");
			}
		}
		else{
			error->Push("Atoms Have Invalid Bond. Compound should be destroyed immediately");
			// isError=true;
			// errorMessage="Atoms Have Invalid Bond. Compound should be destroyed immediately";
			//throw std::runtime_error("Invalid Dative Bond");
		}
	}
}

int Element::operator * (Element& secondElement){
 
	// if ((isNobleGasConfig() && doesFollowOctet(atomicNumber) )|| (secondElement.isNobleGasConfig() && secondElement.doesFollowOctet(secondElement.atomicNumber))||(getNumberOfValenceElectrons()<1)||(secondElement.getNumberOfValenceElectrons()<1)){
	if(isStable()||secondElement.isStable()||(getNumberOfValenceElectrons()<1)||(secondElement.getNumberOfValenceElectrons()<1)){
		return 0;
	}
	else{
		addElectrons(1);
		secondElement.addElectrons(1);
		covalentBonds.push_back(&secondElement);
		secondElement.covalentBonds.push_back(this);
		return 1;
	}
}

int Element::operator / (Element& secondElement){
	
	int FirstElement_Index=doesCovalentBondExist(&secondElement);
	int SecondElement_Index=secondElement.doesCovalentBondExist(this);

	if (FirstElement_Index==-1 || SecondElement_Index==-1){
		return 0;
	}

	addElectrons(-1);
	secondElement.addElectrons(-1);

	covalentBonds.erase(covalentBonds.begin() + FirstElement_Index);
	secondElement.covalentBonds.erase(secondElement.covalentBonds.begin() + SecondElement_Index);
	return 1;
}

int Element::operator ^ (Element& secondElement){
	// if ((isNobleGasConfig() && doesFollowOctet(atomicNumber) )|| (secondElement.isNobleGasConfig() && secondElement.doesFollowOctet(secondElement.atomicNumber))||(secondElement.getNumberOfValenceElectrons()<1)){
	// 	return 0;
	// }
	if(isStable()||secondElement.isStable()||(getNumberOfValenceElectrons()<1)||(secondElement.getNumberOfValenceElectrons()<1)){
		return 0;
	}
	else{
		addElectrons(1);
		secondElement.addElectrons(-1);

		charge-=1;
		secondElement.charge+=1;

		ionicBonds.push_back(std::make_pair(&secondElement,-1));
		secondElement.ionicBonds.push_back(std::make_pair(this,+1));
		return 1;
	}
}

int Element::operator % (Element& secondElement){
	int FirstElement_Index=doesIonicBondExist(&secondElement);
	int SecondElement_Index=secondElement.doesIonicBondExist(this);

	if (FirstElement_Index==-1 || SecondElement_Index==-1){
		return 0;
		// throw std::runtime_error("Atoms Do Not Have Ionic Bond");
	}

	if(ionicBonds[FirstElement_Index].second==-1){
		addElectrons(-1);
		secondElement.addElectrons(1);

		charge+=1;
		secondElement.charge-=1;
	}
	else{
		addElectrons(1);
		secondElement.addElectrons(-1);		

		charge-=1;
		secondElement.charge+=1;
	}

	ionicBonds.erase(ionicBonds.begin() + FirstElement_Index);
	secondElement.ionicBonds.erase(secondElement.ionicBonds.begin() + SecondElement_Index);
	return 1;
}

int Element::operator && (Element& secondElement){
	//rule altered here because chmiestry
	// if ((isNobleGasConfig() && doesFollowOctet(atomicNumber))||(secondElement.getNumberOfValenceElectrons()<2)){
	// 	return 0;
	// }
	if(isStable()||(secondElement.getNumberOfValenceElectrons()<2)){
		return 0;
	}
	else{
		addElectrons(1);
		addElectrons(1);
		dativeBonds.push_back(std::make_pair(&secondElement,-2));
		secondElement.dativeBonds.push_back(std::make_pair(this,2));
		return 1;
	}
}

int Element::operator || (Element& secondElement){
	int FirstElement_Index=doesDativeBondExist(&secondElement);
	int SecondElement_Index=secondElement.doesDativeBondExist(this);

	if (FirstElement_Index==-1 || SecondElement_Index==-1){
		return 0;
	}

	if(dativeBonds[FirstElement_Index].second==2){
		addElectrons(-2);
	}
	else{
		secondElement.addElectrons(-2);
	}

	dativeBonds.erase(dativeBonds.begin() + FirstElement_Index);
	secondElement.dativeBonds.erase(secondElement.dativeBonds.begin() + SecondElement_Index);
	return 1;
}

bool Element::isStable(){
	return isNobleGasConfig()||valency[0]==0||valency[1]==0;
}

int Element::getAtomicNumber(){
	return atomicNumber;
}

std::string Element::getSymbol(){
	return symbol;
}
std::string Element::getName(){
	return name;
}

double Element::getAtomicMass(){
	return atomicMass;
}

int Element::getNumberOfElectrons(){
	return electrons;
}

int Element::getCharge(){
	return charge;
}

std::array<int,2> Element::getValency(){
	return valency;
}

std::vector<Element*> Element::getCurrentCovalentBonds(){
	return covalentBonds;
}

int Element::getNumberOfCovalentBonds(){
	
	return covalentBonds.size();
}

std::vector<std::pair<Element*,int>> Element::getCurrentIonicBonds(){
	return ionicBonds;
}

int Element::getNumberOfIonicBonds(){
	return ionicBonds.size();
}

std::vector<std::pair<Element*,int>> Element::getCurrentDativeBonds(){
	return dativeBonds;
}

int Element::getNumberOfDativeBonds(){
	return dativeBonds.size();
}

std::vector<Element*> Element::getCurrentBonds(){
	std::vector<Element*> bonds= covalentBonds;
	
	for(auto ionicBond: ionicBonds){
		bonds.emplace_back(ionicBond.first);
	}

	for(auto dativeBond: dativeBonds){
		bonds.emplace_back(dativeBond.first);
	}
	return bonds;
}
 

int Element::getNumberOfValenceElectrons(){
	//check
	int n=getValency()[0]-2*covalentBonds.size()-2*dativeBonds.size();

	// for(auto bond: dativeBonds){
	// 	if(bond.second==+2){
	// 		n-=2;
	// 	}
	// }

	return n;
}

void Element::printShells(std::ostream output){

	for(auto [key,value]: shells){
		output<<key<<":"<<value<<std::endl;
	}
}

int Element::getNumberOfElements(int atomicNumber){
	return numberOfEachElement[atomicNumber-1];
}

void Element::printNumberOfEachElement(std::ostream output){

	for(int i=0;i<118;i++){
		output<<"Number of Elements of "<<names[i]<<":"<<numberOfEachElement[i]<<std::endl;
	}
}

