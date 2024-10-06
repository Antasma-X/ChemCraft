#include "../include/element.h"


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
	else{
		//error
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
	valency[0]-=n;
	valency[1]+=n;
	//std::cout<<valency[0]<<valency[1]<<std::endl;
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

std::array<int,2> Element::findValency(int atomicNumber){
	std::array<int,2> valency;

	if(doesFollowOctet(atomicNumber)){
		if (atomicNumber<2){
			valency={1,-1};
		}
		else if(atomicNumber<10){
			valency={atomicNumber-2,atomicNumber-10};
		}
		else if(atomicNumber<18){
			valency={atomicNumber-10,atomicNumber-18};
		}
	}
	else{
		valency={0,0};
	}
	//std::cout<<valency[1]<<"fjfj \n";
	return valency;
}
	
Element::Element(unsigned int atomicNumber, double atomicMass,int charge){

	//Sets Atomic Number, Symbol and Name
	if (atomicNumber<1 || atomicNumber>118){
		//do smth that causes glitch
		//throw error when i learn how to
	}
	else{
		this->atomicNumber=atomicNumber;
		symbol=findSymbol(atomicNumber);
		name=findName(atomicNumber);
	}

	//Sets Atomic Mass
	if (atomicMass<=0){

		atomicMass=findMass(this->atomicNumber);
	}
	this->atomicMass=atomicMass;

	valency=findValency(atomicNumber);

	if(valency[0]-charge<0 || valency[1]+charge>0){
		//error and stuff
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

}


Element::~Element(){
	numberOfEachElement[atomicNumber-1]--;
	elementList[atomicNumber-1].erase(std::find(elementList[atomicNumber-1].begin(),elementList[atomicNumber-1].end(),this));

	for(auto bond: covalentBonds){
		(*this)/(*bond);
	}

	for(auto bond: ionicBonds){
		if(bond.second==-1){
			(*this)%(*bond.first);
		}
		else if(bond.second==1){
			(*bond.first)%(*this);
		}
		else{
			//error
		}
		
	}
}

int Element::operator * (Element& secondElement){

	if ((isNobleGasConfig() && doesFollowOctet(atomicNumber) )|| (secondElement.isNobleGasConfig() && secondElement.doesFollowOctet(secondElement.atomicNumber))){
		//throw error or smth
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
		//throw erroes and stuff
	}

	addElectrons(-1);
	secondElement.addElectrons(-1);

	covalentBonds.erase(covalentBonds.begin() + FirstElement_Index);
	secondElement.covalentBonds.erase(secondElement.covalentBonds.begin() + SecondElement_Index);
	return 1;
}

int Element::operator ^ (Element& secondElement){
		if ((isNobleGasConfig() && doesFollowOctet(atomicNumber) )|| (secondElement.isNobleGasConfig() && secondElement.doesFollowOctet(secondElement.atomicNumber))){
		//throw error or smth
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
		//throw erroes and stuff
	}

	addElectrons(-1);
	secondElement.addElectrons(1);

	ionicBonds.erase(ionicBonds.begin() + FirstElement_Index);
	secondElement.ionicBonds.erase(secondElement.ionicBonds.begin() + SecondElement_Index);
	return 1;
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
	std::cout<<"hehehehe"<<std::endl;
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

std::vector<Element*> Element::getCurrentBonds(){
	std::vector<Element*> bonds= covalentBonds;
	
	for(auto ionicBond: ionicBonds){
		bonds.emplace_back(ionicBond.first);
	}
	return bonds;
}

void Element::printShells(std::ofstream output){

	for(auto [key,value]: shells){
		output<<key<<":"<<value<<std::endl;
	}
}

int Element::getNumberOfElements(int atomicNumber){
	return numberOfEachElement[atomicNumber-1];
}

void Element::printNumberOfEachElement(std::ofstream output){

	for(int i=0;i<118;i++){
		output<<"Number of Elements of "<<names[i]<<":"<<numberOfEachElement[i]<<std::endl;
	}
}
