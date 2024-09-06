#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "../includes/element.h"
#include "../includes/values.h"

#define NUMBEROFSHELLS 7


class Element{

	std::string symbol;
	std::string name;
	int atomicNumber;
	int atomicMass;
	int electrons;
	int charge;
	//std::vector <int> valency;
	std::map<std::string,int> shells;
	std::vector<Element*> bonds;

	// static int listofelements;
	// static int numberOfElements;

	//make nomenclaature a seperate tab that only supports a few elements
	//calculate total molecular mass
	//select copy paste



	std::string getSymbol(int n){
		return symbols[n-1];
	}

	std::string getName(int n){
		return names[n-1];
	}

	//Idk chemistry so im just doing stuff. change later
	static std::map<std::string,int> fillShells(int electrons){
		std::map<std::string,int> shells;

		int i =0;

		while(i < NUMBEROFSHELLS ){
			std::vector<std::array<int,2>> combinations=findCombinations(i);

			for (int j=0;j>0;j++){
				shells[std::to_string(combinations[j][0])+std::to_string(subShell[combinations[j][1]])]=electronValue(electrons,subShell[combinations[j][1]]);
			}
			i++;
			
		}

		return shells;
	}

	static int electronValue(int& electrons,int subShell){
		int value=2 + subShell*4;
		if (electrons>value){
			electrons-=value;

		}else{
			value=electrons;
			electrons=0;
		}

		return value;

	}
	static std::vector<std::array<int,2>> findCombinations(int n){
		std::vector<std::array<int,2>> combs;


		for(int i=0;i<=n;i++){
            if (i<=n-i){
                continue;
            }
			combs.push_back({i,n-i});
		}
        return combs;
	}

	//Futre when i figure out exceptions
	// static std::vector<int> fillShells(int electrons, int exceptionNumber){
	// 	std::vector<int> shells;


	// }

	//ststaic check electron config
	static double findMass(int n){
		return masses[n-1];
	}

	//im lazy (change later)
	//combine with distance from noblegas config
	int isNobleGasConfig(){
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


	// std::vector<int> getValency(){
	// 	if (isNobleGasConfig()){
	// 		return {0,0};
	// 	}

	// 	std::string emptySubShell=findFirstEmptySubShell(shells);



	// }













	//covalent bond
	//create remove bond later
	//while i know noble gases can form compounds, im focussing on simpler compounds without exceptipns becase im stupid 
	// void operator ^ (Element& secondElement){
	// 	if (isNobleGasConfig() || secondElement.isNobleGasConfig()){
	// 		//throw error or smth
	// 	}
	// 	else{
	// 		addElectrons(1);
	// 		secondElement.addElectrons(1);
	// 		bonds.push_back(&secondElement);
	// 		secondElement.bonds.push_back(this);
	// 	}

	// }

	//can be negative
	void addElectrons(int n){
		electrons+=n;
		charge-=n;
		fillShells(electrons);
	}

	public:
		Element(unsigned int number, double mass=0,int charge=0){

		std::cout<<"hi";
		if (number<1 || number>118){
			//do smth that causes glitch
			//throw error when i learn how to
		}
		else{


			atomicNumber=number;
			std::cout<<"hi";
			symbol=getSymbol(atomicNumber);
			name=getName(atomicNumber);
		}

		if (mass<=0){
		
			mass=findMass(atomicNumber);
		}
		atomicMass=mass;

		this->charge=charge;

		electrons=atomicNumber-charge;

		shells=fillShells(electrons);

		//valency=getValency();
		//bonds={};
	}
		std::string getName(){
			return name;
		}


};

//compound group creator
//functional group creator
//way to group elemnts




