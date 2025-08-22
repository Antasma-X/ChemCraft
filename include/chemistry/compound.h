#ifndef COMPOUND_H
#define COMPOUND_H

#include "StdLibDependencies.h"
#include "utils.h"

#include "element.h"
#include "values.h"

class Element;

class Compound{
	std::vector<Element*> atoms;

	//0 is covalent
	//-1 means current element took electron(anion)
	//+1 means current element gave electron(cation)
	//-2 means current element gains 2 electrons from the bond
	//+2 means current element donates 2 electrons to the bond
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
		You can also pass Atomic Mass and/or charge and/or valency if it is a higher level element
		If you don't pass them in, then atomic mass is set as average atomic mass(present in values.cpp) of element and charge is set as 0
		If you don't pass anything for v or pass an incorrect valency then it is reset to a default valency depending on the valency

		Note: the valency passed must be the valency of the atom without charge

		If invalid Atomic Mass or Charge is passed, they are set to default
		If it is not fine that mass or charge is reset, then call destructor.

		Throws std::invalid_argument("Invalid Atomic Number") when Atomic Number is invalid

		If atomic mass or charge passed is invalid, error popup occurs
		if invalid valency is also passed in, error popup occurs

		Pass in: Atomic Number of element to be first added to compound, atomic mass(optional), charge (optional), v (optional)
		*/
		Compound(int atomicNumber,double atomicMass=0,int charge=0,int v=1000);

		/*
		Constructor for Compound
		You pass in the Compound string for the compound and it creates the compounnd from that info

		Throws std::invalid_argument("String is Invalid") when invalid characters are in string
		Throws std::invalid_argument("Covalent Bond could not form") when any covalent bond is not formed
		Throws std::invalid_argument("Ionic Bond could not form") when any ionic bond can not be formed
		Throws std::invalid_argument("Dative Bond could not form") when any dative bond can not be found
		Throws std::invalid_argument("Invalid Bond Type") when an invalid bond type number is in the string

		Pass in: Compound String of Compound to be Created
		*/
		Compound(std::string compound);

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
		+2 means dative bond where first element gains 2 electrons
		-2 means dative bond where first element donates 2 electrons

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
		+2 means dative bond where first element gains 2 electrons
		-2 means dative bond where first element donates 2 electrons

		The first element passed in must be part of the compound
		The atomic number will be used to create second element which is added to compound
		The second element bonds to the first element present in the compound

		Throws std::invalid_argument("Invalid Atomic Number") when Atomic Number is invalid
		
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
		+2 means dative bond where first element gains 2 electrons
		-2 means dative bond where first element donates 2 electrons

		The first element passed in must be part of the compound on which the method is called
		The second element passed in must be part of the compound passed in
		The second element bonds to the first element present in the compound on which the method passed in
		This bond will be the link in which the 2 compounds will be joined
		Then the second compound's atoms and bonds information will be merged into the first compound's

		Note: Second Compound should be destroyed if bond is made

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

		Throws std::runtime_error("X Bond has invalid number. Compound is corrupted") where X is bond type when a wrong bond type is there. Compound should be destroyed if this exception is raised

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
		+2 means dative bond where first element gains 2 electrons
		-2 means dative bond where first element donates 2 electrons

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
		Calls getUnstableAtoms()
		Bonds all atoms to Hydrogen atoms till valencies are filled
		For alkali and alkali earth metals it form ionic bonds
		Otherwise forms covalent bonds only

		Throws std::runtime_error("Unstable atoms contains Stable Atoms somehow")  This should not happen

		Returns:0 if not successful
				1 if successful
		*/
		int hydrogenFiller();
		/*
		Checks if all the atoms in the compound have valecnies of 0 and are stable
		Returns: true if compound is stable
				 false if compound is not stable
		*/
		bool isStable();

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
		Throws std::runtime_error("Invalid bond value. Compound Corrupted") when bonds map is corrupted and compound string can not be created

		Returns: Compound String for Compound. This Compound String can be used to create the same compound again
		*/
		std::string getCompoundString();

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