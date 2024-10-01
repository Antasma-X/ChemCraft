#ifndef COMPOUND_H
#define COMPOUND_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "element.h"


//does bond exist between them

//remove atom too
//find unstable and bond
class Compound{
	std::vector<Element*> atoms;

	//0 is covalent
	//-1 means current element took electron(anion)
	//+1 means current element gave electron(cation)
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
	Called by createCompoundFromElement()
	Function is Recursive and finds all the elements present bonded to each other and gets the information about the compound the element is a part of

	Pass in: Element from which compound is formed, atoms vector to which atoms in compound is added, map of bonds of all atoms 
	*/
	static void createCompoundFromElementUtil(Element& element,std::vector<Element*>& atoms,std::map<Element*,std::vector<std::pair<Element*,int>>>& bonds);
	
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
		Compound(int atomicNumber,double atomicMass=0,int charge=0);

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
		+1 means ionic bond where first elemnt loses an electron
		-1 means ionic bond where first elemnt gains an electron
		
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
		+1 means ionic bond where first elemnt loses an electron
		-1 means ionic bond where first elemnt gains an electron

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
		+1 means ionic bond where first elemnt loses an electron
		-1 means ionic bond where first elemnt gains an electron

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
		Removes Element from Compound
		You pass in element which is removed

		Since it's possible that the element removal results in multiple seperate compounds forming, a vector of compounds is created
		Function uses isFullyConnected() to check if compound is still fully connected

		Pass in: Element to be removed
		Returns: Vector of Compounds that are formed from element removal if it is successful
				 Empty Vector if it isn't successful
		*/
		std::vector<Compound> removeElement(Element& firstElement);
		/*
		Creates a bond between 2 elements already present within the compound
		You pass in 2 elements which already part of the compound and an integer signifying the type of bond
		0 means covalent bond
		+1 means ionic bond where first elemnt loses an electron
		-1 means ionic bond where first elemnt gains an electron

		Pass in: 2 elements already present in the compound, Type of Bond(0 is covalent, 1 is ionic)
		Returns: 0 if it isn't successful
				 1 if it is successful

		*/
		int createBond(Element& firstElement, Element& secondElement, int typeOfBond);

		/*
		Removes a bond between 2 elements already present within the compound
		You pass in 2 elements which already part of the compound and an integer signifying the type of bond
		0 means covalent bond
		+1 means ionic bond where first elemnt loses an electron
		-1 means ionic bond where first elemnt gains an electron

		Since it's possible that the bond removal results in 2 seperate compounds forming, a vector of compounds is formed
		Function uses isFullyConnected() to check if compound is still fully connected

		Pass in: 2 elements between which bond exists, and type of bond between them
		Returns: Vector of Compounds that form from bond removal if it is successful
				 Empty Vector if it isn't successful
		*/
		std::vector<Compound> removeBond(Element& firstElement, Element& secondElement, int typeOfBond);
		
		/* 
		Calls createCompoundFromElementUtil()
		Creates Compound from element passed in
		Uses information from element passed in to form compound object

		Pass in: Element from which you want to form its compound
		Returns: Compound object with the atoms and bonds variables filled with information gathered from element passed in
		*/
		static Compound createCompoundFromElement(Element& element);

		/*
		Checks if all the atoms in the compound have valecnies of 0 and are stable

		Returns: 1 if compound is stable
				 0 if compound is not stable
		*/
		int isStable();

		/*
		Checks if all elements are bonded to each other in the compound (I.E. if you can access every element from any element in graph through bonds)
		Does this by traversing Compound from first atom in atoms[] and counting the number of atoms found
		If the number of atoms found is equal to the suze of atoms vector, it returns true
		Else it returns false

		Returns: True if all elements are bonded to each other in the compound
				 False if all elements are not bonded to each other in the compound(I.E. you can not access every element from any element in graph through bonds)
		*/
		bool isFullyConnected();

		/*
		Uses DFS algorithm to check if 2 elements are connected in compound

		Pass in: Pointers to 2 elements to be checked if connected
		Returns: True if 2 elements in compound is connected
				 False if 2 elements in compound aren't connected

		Basically copied ngl
		*/
		bool isConnected(Element* element1, Element* element2);
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
		Returns: Vector of all unstable atoms in compound(Valencies not 0)
		*/
		std::vector<Element*> getUnstableAtoms();
	
		/*
		Returns: List of Compounds
		*/
		static std::vector<Compound*> getListOfCompounds();

		//quit
		void printCompound();

};

#endif