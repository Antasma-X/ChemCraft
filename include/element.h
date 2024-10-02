#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

#include "values.h"

//smart pointers later
//examples too
//benzene
//nh4
//coordinate bond?????? PO$ and stuff will do later
//remove the coordinate bonds for now
	//make nomenclaature a seperate tab that only supports a few elements

	//select copy paste
//compound group creator
//functional group creator
//way to group elemnts
//stable indicator
//hydrogen filler

	//Futre when i figure out exceptions include in h file too
	//indlude errors in comment
	//null for bond in group

class Element{ 

	int atomicNumber;
	std::string symbol;
	std::string name;
	double atomicMass;
	int electrons;
	int charge;

	std::map<std::string,int> shells;
	std::vector<Element*> covalentBonds;

	//-1 means this elemnt took electron
	//positve 1 means this elemt lost electron
	std::vector<std::pair<Element*,int>> ionicBonds;

	//Valency will only be created if atomic number is less than or equal to 18
	//exceptions ake later
	std::array<int,2> valency;

	//Static arrays of elements and addresses
	static std::array <int,118> numberOfEachElement;
	static std::array <std::vector<Element*>,118> elementList;

	/*
	Finds Symbol of Element from list of symbols in values.cpp using atomic number passed in
	Pass In: Atomic Number
	Returns: String of Symbol of Element
	*/
    static std::string findSymbol(int atomicNumber);

	/*
	Finds Name of Element from list of names in values.cpp using atomic number passed in
	Pass In: Atomic Number
	Returns: String of Name of Element
	*/
    static std::string findName(int atomicNumber);

	/*
	Finds Average Atomic Mass of Element from list of names in values.cpp using atomic number passed in
	Pass In: Atomic Number
	Returns: Average Atomic Mass of Element
	*/
    static double findMass(int atomicNumber);

	/*
	Function is called in loop in fillShells()
	Takes the number of electrons and the subshell"s Azimuthal Number those electrons have to fill. Will fill subshell till either no electrons are left or sub shell is full
	Function will also alter the number of electrons passed in so that after the function the elctrons variable will be the number of electrons left yet to be filled
	Pass in: No of Electrons yet to be filled, Sub Shell's Azimuthal Number to be filled
	Returns: Electrons in the sub shell filled
	*/
    static int electronValue(int& electrons,int subShell);

	/*
	Function is called to find the (n+l) combinations of electrons in a sorted order according to Aufbau Principle
	It will find all the combinations of the number passed in. The combinations will be in the format: {n,l} 
	All combinations are valid sub shells
	Pass in: Number Sum
	Returns: Sorted Vector of Combinations that are valid Sub Shells
	*/
    static std::vector<std::array<int,2>> findCombinations(int n);

	/*
	Function is called by constructor to fill all sub shells of atom
	It will return a map with sub shell as key and number of electrons as value
	Pass in: Number of electrons to be in atom
	Returns: Sub Shell and the number of electrons in each


	Idk chemistry so im just doing stuff. change later
	ngl was really annoying to do idc if anyone calls it unoptimized
	*/
    static std::map<std::string,int> fillShells(int electrons);

	/*Function is called by constructor in case of exception in electronic configurations

	Exception Numbers:
		1: In D Block Elements, valence d sub shell sometime borrows one electron from valence s sub shell
		2: In Palladium, 4d has 10 electrons and 5s doesn't have any
		3: In Lawrencium, 6d has no electrons and 7p has one electron
		4: In F Block Elements, valence d sub shell sometimes borrow one electron from valence f sub shell
	
	Pass in: Number of electrons to be in atom, Exception Number that is used
	Returns: Sorted Vector of Combinations that are valid Sub Shells
	*/
	static std::map<std::string,int> fillShells(int electrons, int exceptionNumber);


	/*
	Checks if atom has acheived Noble Gas Configuration
	Returns: true if atom has acheived noble gas configuration
			 false if atom hasn't achieved noble gas configuration

	im lazy as fuck (change later)
	*/
    bool isNobleGasConfig();


	
	/*
	Function will add a number of electrons to the valence shell of the atom
	Function will update electrons and shells variable
	First, function finds first valence shell that isn't filled
	Then it adds the electrons to the sub shell in second while loop
	While loop first checks if sub shell is possible. If it isn't it moves on to next shell
	Then while loop fills elecrons. If sub shell would be overfilled, it fills the current sub shell and moves on to the next
	The Number of electrons passed in can be negative to remove an electron from valence shell
	Pass in: Number of electrons to be added

	btw this func might be completey wrong cause idk hhow chem works
	*/
    void addElectrons(int n);

	/*
	Function is called by addElectrons()
	Finds valence shell of atom
	Function just checks shells in loop and stores valence shell in maxShell
	Returns: Number of Valence shell of atom
	*/
	int findValenceShell();

	/*
	Basically checks if atom obeys octet rule and if its a small element thats easy to deal with since there are many exceptions in higher elements
	Pass in: atomic number of element
	Returns: true if atomic number is less or equal to than 18
			 false if atomic number is greater than 18
	*/
	static bool doesFollowOctet(int atomicNumber);

	/*
	Checks if covalent bond exists between element and element passed in
	If bond exists it returns index of bond in covalentBonds vector of first element
	Pass in: Second Element pointer
	Returns: Index of bond in covalentBonds vector of first element if bond exists
			-1 if bond doesn't exists
	*/
	int doesCovalentBondExist(const Element* secondElement);

	/*
	Checks if ionic bond exists between element and element passed in
	If bond exists it returns index of ionic bond in ionicBonds vector of first element
	Pass in: Secood Element pointer
	Returns: Index of bond in ionicBonds vector of first element if bond exists
			-1 if bond doesn't exists
	*/
	int doesIonicBondExist(const Element* secondElement);

	/*
	Used in Constructor
	Function finds the valencies of an atom as long as its element is less than or equal to 18
	If the element is greater than 18 then the array returned is {0,0} 

	Pass in: Atomic Number of Element
	Returns: Size 2 Array of valencies(First element is positive valency and second element is negative element)
	*/
	static std::array<int,2> findValency(int atomicNumber);

	public:
		
		/*
		Constructor for Element
		You have to pass in the atomic number of the element
		If you want you can pass in the atomic mass and/or charge of atom
		If you don't pass them in, then atomic mass is set as average atomic mass(present in values.cpp) of element and charge is set as 0
		
		Pass in: Atomic Number, Atomic Mass(optional), charge(optional)
		Returns: New Element
		*/
		Element(unsigned int atomicNumber, double atomicMass=0,int charge=0);

		/*
		This is not allowed(Check Definition)
		*/
		Element()=delete;

		/*
		Destructor for element
		First removes elements from static variables
		Then removes all covalent bonds
		*/
		~Element();

		/*
		Operator Overloading
		Creates Covalent Bond between 2 atoms
		If any of the atoms in the bond have acheived noble gas configuration and has an atomic number less than or equal to 18, then bond is not created

		Returns: 1 if bond is successful
				 0 if bond isn't successful
		im kinda supid and dont kbow how elements after 18 work might change a bit too
		*/
		int operator * (Element& secondElement);


		//removes bond between 2 atoms

		/*
		Operator Overloading
		Removes Covalent Bond between 2 atoms		

		Returns: 1 if bond removal is successful
				 0 if bond removal isn't successful
		*/
		int operator / (Element& secondElement);

		/*
		Operator Overloading
		Creates Ionic Bond between 2 atoms
		If any of the atoms in the bond have acheived noble gas configuration and has an atomic number less than or equal to 18, then bond is not created
		First atom gains an electron, and second atom loses an electron

		Returns: 1 if bond is successful
				 0 if bond isn't successful

		basically just copy pasted covalent bond
		*/
		int operator ^ (Element& secondElement);

		/*
		Operator Overloading
		Removes Ionic Bond between 2 atoms		

		Returns: 1 if bond removal is successful
				 0 if bond removal isn't successful
		*/
		int operator % (Element& secondElement);
		//Getters:

		/*
		Returns: Atomic Number of element
		*/
        int getAtomicNumber();

		/*
		Returns: Symbol of Element
		*/
        std::string getSymbol();
		/*
		Returns: Name of Element
		*/
        std::string getName();

		/*
		Returns: Atomic Mass of Element
		*/
        double getAtomicMass();

		/*
		Returns: Number of Electrons in atom
		*/
        int getNumberOfElectrons();

		/*
		Returns: Charge of atom
		*/
        int getCharge();

		/*
		Returns: Array of Valencies of atom(first positive valency then negative valency)
				 If atom has atomic number greater than 18 then array will be {0,0}
		*/
		std::array<int,2> getValency();

		/*
		Returns: Copy of Vector of all current covalent bonds
		*/
		std::vector<Element*> getCurrentCovalentBonds();

		/*
		Returns: Number of Covalent Bonds that atom has formed
		*/
		int getNumberOfCovalentBonds();

		/*
		Returns: Copy of Vector of all current ionic bonds
		*/
		std::vector<std::pair<Element*,int>> getCurrentIonicBonds();

		/*
		Returns: Number of Ionic Bonds that atom has formed
		*/
		int getNumberOfIonicBonds();

		/*
		Returns: Vector of all the elements the atom is bonded to
		*/
		std::vector<Element*> getCurrentBonds();
		/*
		Prints Number of Electrons in each sub shell of atom
		*/
		void printShells(std::ofstream output);


		//static methods

		/*
		Pass in: Atomic Number whose number of elements is to be returned
		Returns: Number of Elements of passed in Atomic Number
		*/
		static int getNumberOfElements(int atomicNumber);

		/*
		Prints Number of each element
		*/
		static void printNumberOfEachElement(std::ofstream output);



};

#endif