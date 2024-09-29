#ifndef COMPOUND_H
#define COMPOUND_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "element.h"

//is path between 
//remove bond
//does bond exist between them
//ionic bond direction
//remove atom too
class Compound{
	std::vector<Element*> atoms;
	std::map<Element*,std::vector<std::pair<Element*,int>>> bonds;

	static std::vector<Compound*> listOfCompounds;

	/*
	Checks if element passed in is part of compound on which method is performed

	Pass in: Element to be checked
	Returns: true if element is in compound
			 false if element is not in compound
	*/
	bool isAtomInCompound(Element& element);

	/*
	Returns: Vector of atoms which are only bonded to one other atom
	*/
	std::vector<Element*> findTerminals();

	/*
	failed miserabaly
	*/
	void printCompoundUtil(Element* current,std::vector<Element*>& traversed,std::vector<std::string>& structure,std::array<int,2> location);

	public:

		/*
		Constructor for Compound
		You pass in one element that will be part of the compound(the compound will only consist of that element)

		Pass in: Element to be first added to compound
		*/
		Compound(Element& element);


		/*
		Constructor for Compound (Calls Compound(Element& element) internally)
		You pass in the atomic number that will be part of the compound(the compound will only consist of that element)

		Pass in: Atomic Number of element to be first added to compound
		*/
		Compound(int atomicNumber);

		/*
		This is not allowed
		*/
		Compound()=delete;

		/*
		Destructor for Compound
		Removes Compound from listOfCompounds
		*/
		~Compound();

		/*
		Adds Element to Compound
		You pass in 2 elements and an integer signifying the type of bond
		0 means covalent bond
		1 means ionic bond

		The first element passed in must be part of the compound
		The second element passed in can not be part of any compound(including this one)
		The second element bonds to the first element present in the compound

		Function will add second element to list of elements and add to both atoms' bonds
		Pass in: First Element which is part of the compound, Second element which isnt part of any compound, Type of Bond(0 is covalent, 1 is ionic)
		Returns: 0 if it isn't successful
				 1 if it is successful
		*/
		int addElement(Element& firstElement, Element& secondElement, int typeOfBond);

		/*
		Adds Element to Compound(Calls addElement(Element& firstElement, Element& secondElement, int typeOfBond))
		You pass in 1 element, an integer signifying atomic number and an integer signifying the type of bond
		0 means covalent bond
		1 means ionic bond

		The first element passed in must be part of the compound
		The atomic number will be used to create second element which is added to compound
		The second element bonds to the first element present in the compound

		Function will add second element to list of elements and add to both atoms' bonds map
		Pass in: First Element which is part of the compound, Atomic number of second element , Type of Bond(0 is covalent, 1 is ionic)
		Returns: 0 if it isn't successful
				 1 if it is successful
		*/
		int addElement(Element& firstElement, int atomicNumber, int typeOfBond);

		/*
		Adds Element to Compound
		You pass in 2 elements, a second compound and an integer signifying the type of bond
		0 means covalent bond
		1 means ionic bond

		The first element passed in must be part of the compound on which the method is called
		The second element passed in must be part of the compound passed in
		The second element bonds to the first element present in the compound on which the method passed in
		This bond will be the link in which the 2 compounds will be joined
		Then the second compound's atoms and bonds information will be merged into the first compound's

		Pass in: First Element which is part of the compound, Second Element which is part of second compound, Second Compound Type of Bond(0 is covalent, 1 is ionic)
		Returns: 0 if it isn't successful
				 1 if it is successful
		*/
		int addElement(Element& firstElement, Element& secondElement, Compound& secondCompound,int typeOfBond);

		/*
		Creates a bond between 2 elements already present within the compound
		You pass in 2 elements which already part of the compound and an integer signifying the type of bond
		0 means covalent bond
		1 means ionic bond

		Pass in: 2 elements already present in the compound, Type of Bond(0 is covalent, 1 is ionic)
		Returns: 0 if it isn't successful
				 1 if it is successful

		*/
		int createBond(Element& firstElement, Element& secondElement, int typeOfBond);

		/*
		Checks if all the atoms in the compound have valecnies of 0 and are stable

		Returns: 1 if compound is stable
				 0 if compound is not stable
		*/
		int isStable();

		/*
		Returns: Total Molecular mass of compound
		*/
		double getMolecularMass();

		/*
		Uses subscripts map in values.h for unicode subscipts
		First counts number of each element
		Then adds it to a string each iteration

		Returns: std::string of Molecular Formula
		*/
		std::string getMolecularFormula();

		/*
		Returns: Copy of vector of all atoms present in compound
		*/
		std::vector<Element*> getAtoms();

		/*
		Returns: Copy of Bonds map
		*/
		std::map<Element*,std::vector<std::pair<Element*,int>>> getBonds();
	
		/*
		Returns: List of Compounds
		*/
		static std::vector<Compound*> getListOfCompounds();

		std::vector<Compound> removeBond(Element& firstElement, Element& secondElement, int typeOfBond);

		bool isConnected(Element* element1, Element* element2);

		std::vector<Compound> removeElement(Element& firstElement, Element& secondElement, int typeOfBond);

		Compound createCompoundFromElement(Element& element);

		bool isFullyConnected();

		//quit
		void printCompound();

};

#endif