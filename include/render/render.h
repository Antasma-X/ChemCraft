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

    /*
    Main Render Function
    Renders Elements and Bonds
    */
    void Render();

    /*
    Creates Element Object for every single element in the compound passed in which is then rendered in Render()

    Pass In: Pointer to compound to start being rendered
    */
    void createCompoundObject(Compound* compound);

    ElementObject* getElementClicked(glm::vec2 mousePos);

    void MoveBonds(ElementObject* el,glm::vec2 delta);

    void compoundMovement();

    void bondCreation();

    void bondCleavage();

}
#endif