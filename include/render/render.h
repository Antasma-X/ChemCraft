#ifndef RENDER_H
#define RENDER_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "chemistry.h"
#include "graphics.h"
#include "utils.h"

#include "bondObject.h"
#include "chargeObject.h"
#include "electronObject.h"
#include "elementObject.h"
#include "numberObject.h" 
#include "signObject.h"

class Compound;
class Camera;

namespace Render{
  
    /*
    Vector containing all compounds being rendered
    */
 
    static std::vector<Compound*> compoundList;

    static std::map<BondObject*,Compound*> bondObjectToCompound;

    static std::map<Compound*,std::set<BondObject*>> compoundToBondObjects;

    static std::map<ElementObject*,Compound*> elementObjectToCompound;
    
std::vector<Compound*> getCompoundList();
    /*
    Creates Element Object for every single element in the compound passed in which is then rendered in Render()

    Pass In: Pointer to compound to start being rendered
    */ 
    void createCompoundObject(Compound* compound);

    /*
    Main Render Function 
    Renders Elements and Bonds
    */
    void render();

    /*
    Moves all elementObjects in the compound passed in by delta passed in

    Pass In:Pointer to compound whose elements will be moved, delta to move by
    */
    void moveCompound(Compound* comp,glm::vec2 delta);

    /*
    Moves the bonds whose ends has ElementObject's element in them by delta passed in 
    It only moves that end, so the line is produced properly between the 2 elements

    Pass In: ElementObject whose bonds are being moved, delta to move by
    */
    void moveBonds(ElementObject* el,glm::vec2 delta);

    /*
    Moves the dative object passed in by delta and also moves the 2 electrons it's between towards it
    If the dative object isn't actually a dative, nothing happens

    Pass In: Pointer to dative object to be moved with its 2 surroudning electrons, delta to move by
    */
    void moveDative(ElectronObject* dative,glm::vec2 delta);

    /*
    Checks if the electron passed in is on 
        i) another electron(opaque or transparent) of the same element. In that case electron is shifted around the atom
        ii) another transparent electron of another atom. In that case bonding is attempted
        iii) another charge object of not the same element. In that case an ionic bond is attempted

    Pass in: electron whose position will be checked to see if its shifted it's parent atoms electrons or formed a new bond
    Returns: 0 If nothing happens, i.e. electron doesnt shift or bond
             1 If electron shifts to new electron
             2 If electron creates covalent bond with another element
             3 if electron creates ionic with another element where this electron is donated to the other element
             -1 if something went wrong
    */
    int checkElectronShiftingOrBonding(ElectronObject* electron);

    /*
    Checks if the dative passed in is on anotheer dative of another element
    If yes, a dative bond is attempted

    Pass in: dative whose position will be checked to see if its bonded to another atom
    Returns: 0 If nothing happens
             1 if bonding happens
             -1 if something went wrong
    */
    int checkDativeBonding(ElectronObject* dative);

    /*
    Creates a covalent or dative bond between ElementObjects passed in on the 2 electron positions of the type passed in
    This function has to alter all the maps and stuff and might destroy a compound if necessary

    Pass In: First ElementObject, second ElementObject, type of bond(1 if covalent, 2 if dative), first ElementObject's electron, second ElementObject's electron
    Returns: 1 if successful
             0 if not successful
    */
    int createBond(ElementObject* elObj1,ElementObject* elObj2, int type, ElectronObject* electron, ElectronObject* otherElectron);

    /*
    Creates an ionic bond between ElementObjects passed in on the first electron position and charge object of second elementObject
    This function has to alter all the maps and stuff and might destroy a compound if necessary

    Pass In: First ElementObject, second ElementObject, first ElementObject's electron
    Returns: 1 if successful
             0 if not successful
    */   
    int createBond(ElementObject* elObj1,ElementObject* elObj2, ElectronObject* electron);

    /*
    Destroys the bondObject passed in along with the bond in the compound. Also removes from all the maps and stuff
    New compounds may be created too btw and might destroy the current compound

    Pass In: Pointer To BondObject to be destroyed
    Returns: 1 if successful
             0 if not successful
    */
    int removeBond(BondObject* bondObj);

    /*
    Destroys the elementObject passed in along with the element in the compound. Also removes from all the maps and stuff
    New compounds may be created too btw and might destroy the current compound
    
    Pass In: Pointer to ElementObject to be destroyed
    Returns: 1 if successful
             0 if not successful
    */
    int removeElement(ElementObject* elementObj);

    /*
    Deletes all ElementObjects and BondObjects belonging to the compound passed in
    */
    void deleteCompound(Compound* comp);
    
    /*
    Resets the position of the electron passed in to the position it belongs to on the elementObject its part of
    */
    void resetElectronPos(ElectronObject* electron);

    /*
    Resets the position of the dative passed in to the position it belongs to on the elementObject its part of along with the 2 electrons it's between
    */
    void resetDativePos(ElectronObject* dative);

    /*
    Checks if the set of ElementObjects passed in all belong to the same compound
    */
    bool isPartOfOneCompound(std::set<ElementObject*> elementObjects);

    /*
    Checks if the set of ElementObjects passed in's elements aare the same as a compound's
    If yes, it returns the compound pointer
    If no, returns nullptr

    Every element of the compound must be present in the set passed in and the set can't have extra elementObjects

    Pass In: Set of pointers to ElementObjects that you wanna check
    Returns: nullptr if a compound containing each element of the ElementObjects passed in and ElementObjects contains each element of the compound doesn't exist
             Pointer to compound if it does exist
    */
    Compound* getCompoundIfExists(std::set<ElementObject*> elementObjects);

    //Returns set of ElementObjects containing vec passed in
    std::set<ElementObject*> getElementObjectsOn(glm::vec2 pos);
    
    //Returns set of Electrons(not including datives) containing vec passed in
    std::set<ElectronObject*> getElectronObjectsOn(glm::vec2 pos);

    //Returns set of datives containing vec passed in
    std::set<ElectronObject*> getDativeObjectsOn(glm::vec2 pos);

    //Returns set of BondObjects containing vec passed in
    std::set<BondObject*> getBondsObjectsOn(glm::vec2 pos);
    
    /*
    Finds a compound whose elements has atleast one ElementObject covering the vec passed in

    Pass in: pos to check being contained
    Returns: Pointer to compound with any element containing pos passed in
             nullptr if no such compound exists
    */
    Compound* getCompoundSelected(glm::vec2 pos);

    //Returns compound of the element of the ElementObject passed in
    Compound* getCompoundWithElementObject(ElementObject* elObj);

    //Returns compound that contains the bondObject passed in
    std::set<ElementObject*> getCompoundElementObjectsWithBondObject(BondObject* bondObj);

    //Returns compound that contains the ElementObject passed in
    std::set<BondObject*> getCompoundBondObjectsWithElementObject(ElementObject* elObj);
}


#endif