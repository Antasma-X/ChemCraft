#include <vector>
#include <array>
#include <iostream>
#include "../include/element.h"
#include "../include/compound.h"
// int checkSymbolsMassesNumbers(){
// 	int check=1;
// 	Element tech(43);
// 	Element tech2(43);
// 	Element tech3(43);
// 	if(!(tech.getAtomicNumber()==43 &&tech.getName()=="Technetium")){
// 		check=0;
// 		std::cout<<"\t FAIL\n";
// 	}else{

// 	}
	
// 	{
// 	Element tech4(43);
// 	Element calcium1(43);
// 	Element calcium2(43);

// 	}

// }


int main() {



	std::cout << "Hi" << std::endl;

	Element carbon(43);
	Element oxygen(56);
	for(int i =0;i<5;i++)
	carbon^oxygen;
	//carbon %oxygen;

	//carbon.printShells(std::cout);
	std::cout << carbon.getName() << std::endl;

	Element h=Element(1);

	Compound water(h);

//make implicit
	Element h2=Element(1);
	Element o1=Element(8);
	Element o2=Element(8);
	Element o3=Element(8);
	Element o4=Element(8);
	Element o5=Element(8);
	Element o6=Element(8);
	Element o7=Element(8);
	Element o8=Element(8);
	Element o9=Element(8);
	Element o10=Element(8);
	water.addElement(h,o1,0);
	water.addElement(o1,o2,0);
	water.addElement(o2,o3,0);
	water.addElement(o3,o4,0);
	water.addElement(o4,o5,0);
	water.addElement(o5,o6,0);
	water.addElement(o6,o7,0);
	water.addElement(o7,o8,0);
	water.addElement(o8,o9,0);
	water.addElement(o9,o10,0);
	water.addElement(o10,h2,0);

	std::cout<<"hhdhdhd"<<water.getMolecularFormula();

	//water.printCompound();


}