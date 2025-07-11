#ifndef BONDCOVALENT_H
#define BONDCOVALENT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "elementObject.h"
#include "graphics.h"
#include "utils.h"

struct BondObject{

    //VAO for Bond
    VAO vao;

    //VBO for Bond
    VBO vbo;

    //EBO for Bond. The indices are predefined in constructor for bond
    EBO ebo;

    //Shader for Bond. Uses covalent, dative, ionic shader depending on type of bond. Shader makes first vertex red and second vertex white when dative and makes line dotted when ionic
    Shader shaderProgram;

    /*
    Vertices
 
    Structure:
    There are 2 vertices
    The first vertice is red
    The last vertice is white

    First vertice belong to side giving electrons if thee is a side giving electrons

    Each vertice has x and y coordinate
    {
        x,y
        x,y
    }

    These vertices must be in world space, since the bond is basically just connecting 2 points
    */
    std::vector<glm::vec2> ends;

    std::vector<ElementObject*> elements;

    std::vector<GLfloat> Vertices;

    glm::mat4 model;

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
    These vertices are in world space

    First vertices belong to side giving electrons

    0 means covalent
    1 means ionic
    2 means dative 
 
    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    Throws std::invalid_argument("Invalid Bond Type") if invalid bond type is passed in
    */
    BondObject(std::vector<glm::vec2> ends,std::vector<ElementObject*> elements,int type);

    void Move(glm::vec2 delta, int i);
    
    //Used by Render to render bond
    void Render();

    //Deletes VAO,VBO,EBO and removes from bonds vector
    ~BondObject();
};
#endif 