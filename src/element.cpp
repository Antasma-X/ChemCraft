#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "../include/element.h"
#include "../include/values.h"
constexpr int NUMBEROFSHELLS=7;

std::array<int,118> Element::numberOfEachElement={};
std::array <std::vector<Element*>,118> Element::elementList={};



std::string Element::findSymbol(int n){
	return symbols[n-1];
}

std::string Element::findName(int n){
	return names[n-1];
}

double Element::findMass(int n){
	return masses[n-1];
}


std::map<std::string,int> Element::fillShells(int electrons){
	std::map<std::string,int> shells;

	int i =1;

	while(i < NUMBEROFSHELLS ){
		std::vector<std::array<int,2>> combinations=findCombinations(i);



		for (auto [j,k] : combinations){
			
			shells[std::to_string(j)+subShell[k]]=electronValue(electrons,k);
		}
		i++;
		
	}

	return shells;
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




int Element::isNobleGasConfig(){
	if (shells["1s"]==2 && shells["2s"]==0){
		return 1;
	}
	else if (shells["2p"]==6 && shells["3s"]==0){
		return 1;
	}
	else if (shells["3p"]==6 && shells["4s"]==0){
		return 1;
	}
	else if (shells["4p"]==6 && shells["5s"]==0){
		return 1;
	}
	else if (shells["5p"]==6 && shells["6s"]==0){
		return 1;
	}
	else if (shells["6p"]==6 && shells["7s"]==0){
		return 1;
	}
	else if (shells["7p"]==6 && shells["8s"]==0){
		return 1;
	}
	else{
		return 0;

	}
}






void Element::addElectrons(int n){
	electrons+=n;
	charge-=n;

	int valenceShell=findValenceShell();
	std::cout<<valenceShell;
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
	
Element::Element(unsigned int number, double mass,int charge){


	if (number<1 || number>118){
		//do smth that causes glitch
		//throw error when i learn how to
	}
	else{


		atomicNumber=number;
		symbol=findSymbol(atomicNumber);
		name=findName(atomicNumber);
	}

	if (mass<=0){

		mass=findMass(atomicNumber);
	}
	atomicMass=mass;

	this->charge=charge;

	electrons=atomicNumber-charge;

	shells=fillShells(electrons);

	numberOfEachElement[atomicNumber-1]++;
	elementList[atomicNumber-1].emplace_back(this);

}
int Element::getNumberOfElements(int atomicNumber){
	return numberOfEachElement[atomicNumber-1];
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

int Element::getAtomicMass(){
	return atomicMass;
}

int Element::getNumberOfElectrons(){
	return electrons;
}

int Element::getCharge(){
	return charge;
}



//covalent bond

//while i know noble gases can form compounds, im focussing on simpler compounds without exceptipns becase im stupid 
//has to be changed to allow after 3rd period or odd stuff
int Element::operator ^ (Element& secondElement){

	if ((isNobleGasConfig() && doesFollowOctet(atomicNumber) )|| (secondElement.isNobleGasConfig() && secondElement.doesFollowOctet(secondElement.atomicNumber))){
		//throw error or smth
		return 0;
	}
	else{

		addElectrons(1);
		secondElement.addElectrons(1);
		bonds.push_back(&secondElement);
		secondElement.bonds.push_back(this);
		return 1;
	}


}


int Element::doesFollowOctet(int atomicNumber){
	if (atomicNumber>20){
		return 0;
	}
	return 1;
	
}

int Element::operator % (Element& secondElement){
	
	int FirstElement_Index=doesBondExist(&secondElement);
	int SecondElement_Index=secondElement.doesBondExist(this);

	if (FirstElement_Index==-1 || SecondElement_Index==-1){
		std::cout<<"hnjsfnjf";
		return 0;

		//throw erroes and stuff
	}




	addElectrons(-1);
	secondElement.addElectrons(-1);

	bonds.erase(bonds.begin() + FirstElement_Index);
	secondElement.bonds.erase(secondElement.bonds.begin() + SecondElement_Index);
	return 1;
}


int Element::doesBondExist(const Element* secondElement){

	int index=-1;
	for(auto it=bonds.begin();it !=bonds.end();it++){
		if (*it==secondElement){
			index++;
			break;
		}
		index++;
	}

	return index;
}


void Element::getNumberOfBonds(){
	std::cout<<bonds.size();
}

void Element::printShells(){

	for(auto [key,value]: shells){
		std::cout<<key<<":"<<value<<std::endl;
	}
}