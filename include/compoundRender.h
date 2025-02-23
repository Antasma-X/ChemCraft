#ifndef COMPOUND_RENDER_H
#define COMPOUND_RENDER_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include"compound.h"
#include"elementRender.h"



class CompoundObject{
    Compound* compound;
    
    static std::vector<CompoundObject*> compoundsOnScreen;

    void drawCompounds();

    void drawCompound();

    public:
    CompoundObject(std::string compoundString);

    CompoundObject(int atomicNumber);

    CompoundObject(int atomicNumber, double atomicMass,int charge);

    CompoundObject(int compoundNumber,char dummy);

    ~CompoundObject();

    CompoundObject()=delete;

    static std::vector<CompoundObject*> getListOfCompoundObjects();

//any list should the original check lost every framw 


};
#endif