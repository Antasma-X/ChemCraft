#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

//smart pointers later
	// static int listofelements;
	// static int numberOfElements;

	//make nomenclaature a seperate tab that only supports a few elements
	//calculate total molecular mass
	//select copy paste
//compound group creator
//functional group creator
//way to group elemnts
//its good till 2nd period
//quit from 2nd period


	//Futre when i figure out exceptions include in h file too
	// static std::vector<int> fillShells(int electrons, int exceptionNumber){
	// 	std::vector<int> shells;


	// }
		//ststaic check electron config
//verify shells and electrons and charge and valency



class Element{ 

	int atomicNumber;
	std::string symbol;
	std::string name;
	int atomicMass;
	int electrons;
	int charge;
	// std::array <int,2> valency;
	std::map<std::string,int> shells;
	std::vector<Element*> bonds;

    std::string findSymbol(int n);

    std::string findName(int n);

    static double findMass(int n);

	//Idk chemistry so im just doing stuff. change later
    static std::map<std::string,int> fillShells(int electrons);

    static int electronValue(int& electrons,int subShell);

    static std::vector<std::array<int,2>> findCombinations(int n);

	//im lazy (change later)
	//combine with distance from noblegas config
    int isNobleGasConfig();

	//can be negative
    void addElectrons(int n);

	int findValenceShell();

	static int doesFollowOctet(int atomicNumber);

	int doesBondExist(const Element* secondElement);
	public:
		Element(unsigned int number, double mass=0,int charge=0);

        int getAtomicNumber();

        std::string getSymbol();

        std::string getName();

        int getAtomicMass();

        int getNumberOfElectrons();

        int getCharge();



        // std::array <int,2> getValency();

		//creates bond between 2 atoms
		//returns 1 if succesful
		//if not successful returns 0
		int operator ^ (Element& secondElement);


		//removes bond between 2 atoms
		//returns 1 if succesful
		//if not successful returns 0
		int operator % (Element& secondElement);


	//temp to check
	void getNumberOfBonds();

	void printShells();


};



















#endif