#ifndef ELEMENT_RENDER_H
#define ELEMENT_RENDER_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"
#include "element.h"

class ElementObject{
    Element* element;
    static std::vector<Element*> elementsOnScreen;
    // std::array<,8> valenceElectrons;
    // std::array<,4> dativeBonds;
    // std::array<,8> ionicicBonds;

    public:
    ElementObject(int atomicNumber, double atomicMass=0, int valency=0);

    void drawElement();

    void drawElectronsAndBondsOfElement();

    void Inserelementiselementobject();
    //electrons
    //staus of bonds
    //
};
 

#endif