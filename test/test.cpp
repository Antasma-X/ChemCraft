#include <vector>
#include <array>
#include <iostream>
#include "../include/element.h"

int checkSymbolsMassesNumbers(){
	int check=1;
	Element tech(43);
	Element tech2(43);
	Element tech3(43);
	if(!(tech.getAtomicNumber()==43 &&tech.getName()=="Technetium")){
		check=0;
		std::cout<<"\t FAIL\n";
	}else{

	}
	
	{
	Element tech4(43);
	Element calcium1(43);
	Element calcium2(43);

	}

}


int main() {



	std::cout << "Hi" << std::endl;

	Element carbon(43);
	Element oxygen(56);
	for(int i =0;i<5;i++)
	carbon^oxygen;
	//carbon %oxygen;

	carbon.printShells();
	carbon.getNumberOfBonds();
	std::cout << carbon.getName() << std::endl;

}