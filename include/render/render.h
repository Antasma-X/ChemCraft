#ifndef RENDER_H
#define RENDER_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "compound.h"
#include "bondObject.h"
#include "elementObject.h"
#include "numberObject.h"

class Compound;
//merge files
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

    void createCompoundObject(Compound* compound);

    static std::vector <GLfloat> getVertices(std::vector <GLfloat> vertices, std::set<std::array<GLfloat,2>>& spawned,GLfloat width);

    static void createElementObjects(Compound& comp,Element& el, std::vector<Element*> visited,std::vector <GLfloat> vertices,std::set<std::array<GLfloat,2>>& spawned);

    void elementMovement();

    void compoundMovement();

    void bondCreation();

    void bondCleavage();

}
#endif