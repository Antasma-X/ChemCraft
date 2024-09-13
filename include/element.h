#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

//smart pointers later


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

	std::map<std::string,int> shells;
	std::vector<Element*> bonds;

	static std::array <int,118> numberOfEachElement;
	static std::array <std::vector<Element*>,118> elementList;




    std::string findSymbol(int n);

    std::string findName(int n);

    static double findMass(int n);

	//Idk chemistry so im just doing stuff. change later
    static std::map<std::string,int> fillShells(int electrons);

    static int electronValue(int& electrons,int subShell);

    static std::vector<std::array<int,2>> findCombinations(int n);

	//im lazy (change later)
    int isNobleGasConfig();

	//can be negative
    void addElectrons(int n);

	int findValenceShell();

	static int doesFollowOctet(int atomicNumber);

	int doesBondExist(const Element* secondElement);
	public:
		Element(unsigned int number, double mass=0,int charge=0);

		~Element();
		
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

	static int getNumberOfElements(int atomicNumber);

};



















#endif