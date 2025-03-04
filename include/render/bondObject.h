#ifndef BONDCOVALENT_H
#define BONDCOVALENT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"

#include "config.h"

struct BondObject{
    /*
    Vertices

    Structure:
    There are 2 vertices
    The first vertice is red
    The last vertice is white

    First vertices belong to side giving 2 electrons

    Each vertice has x and y coordinate
    {
        x,y
        x,y
    }
    */
    std::vector<GLfloat> Vertices;

    //VAO for Bond
    VAO vao;

    //VBO for Bond
    VBO vbo;

    //EBO for Bond. The indices are predefined in constructor for bond
    EBO ebo;

    //Shader for Bond. Uses covalent, dative, ionic shader depending on type of bond. Shader makes first vertex red and second vertex white when dative and makes line dotted when ionic
    Shader shaderProgram;

    /*
    Type of Bond
    0 means covalent
    1 means ionic
    2 means dative

    The first vertice always gives donating atom
    */
    int type;

    /*
    Static Vector to get all bond objects from
    */
    static std::vector<BondObject*> bonds;

    /*
    Constructor for Bond Object

     
    Pass in 2 vertices each with x,y and bond type

    First vertices belong to side gives electrons

    0 means covalent
    1 means ionic
    2 means dative

    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    Throws std::invalid_argument("Invalid Bond Type") if invalid bond type is passed in
    */
    BondObject(std::vector<GLfloat>vertices,int type);

    //Used by Render to render bond
    void Render();

    //Deletes VAO,VBO,EBO and removes from bonds vector
    ~BondObject();

};
#endif