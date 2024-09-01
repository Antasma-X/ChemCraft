#include <iostream>
#include <vector>
#include <string>
#include "../includes/values.h"


extern std::vector<std::string> symbols;
extern std::vector<std::string> names;
extern std::vector<double> masses;


//hashmap
class Element{

	std::string symbol;
	std::string name;
	int atomicNumber;
	int atomicMass;
	int electrons;
	int charge;
	std::vector<int> shells;
	std::vector<Element&> bonds;

	static int listofelements;
	static int numberOfElements;

	//int valency number of bonds it wants
	//make nomenclaature a seperate tab that only supports a few elements
	//calculate total molecular mass
	//select copy paste

	Element(unsigned int number, double mass=0,int charge=0){

		if (number<0 || number>118){
			atomicNumber=number;
			symbol=getSymbol(atomicNumber);
			name=getName(atomicNumber);
		}
		else{
			//do smth that causes glitch
			//throw error when i learn how to
		}

		if (mass<=0){
		
			mass=findMass(atomicNumber);
		}
		atomicMass=mass;

		this->charge=charge;

		electrons=atomicNumber-charge;

		shells=fillShells(electrons);

		bonds={};
	}

	std::string getSymbol(int n){
		return symbols[n-1];
	}

	std::string getName(int n){
		return names[n-1];
	}

	static std::vector<int>& fillShells(int electrons){
		//TODO
	}

	static double findMass(int n){
		return masses[n-1];
	}

	static int isNobleGasConfig(Element& element){
		//TODO
	}
	void operator ^ (Element& secondElement){
		if (isNobleGasConfig(*this) && isNobleGasConfig(secondElement)){
			//throw error or smth
		}
		else{
			addElectrons(1);
			secondElement.addElectrons(1);
		}

	}

	void addElectrons(int no){

	}

	public:
		std::string getName(){
			return name;
		}


};

//compound group creator
//functional group creator
//way to group elemnts




int main() {
	std::cout << "Hi" << std::endl;
}