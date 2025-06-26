#ifndef SIGNOBJECT_H
#define SIGNOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"

#include "element.h"

#include "config.h"


struct SignObject{


    static GLuint colorLocation;
    /*
    Vertices

    Structure:
    We Use GL_LINES 

    There are 2 or 4 vertices depending on sign

    Minus has 2 vertices:
        1)Left
        2)Right

        Each vertice has x and y coordinate
        {
            x,y,
            x,y
        }

    OR

    Plus has 4 vertices:
        1)Left
        2)Right
        3)Top
        4)Bottom

        Each vertice has x and y coordinate
        {
            x,y,
            x,y,
            x,y,
            x,y
        }
    */
    std::vector<GLfloat> Vertices;

    //VAO for Sign
    VAO vao;

    //VBO for Sign
    VBO vbo;

    //VBO for Sign
    EBO ebo;

    //Shader for Sign. Red if minus, Blue if Plus
    Shader shaderProgram;

    // true if plus, false if minus
    bool isPositive;

    glm::vec2 position;
    glm::mat3 model;
    //Because Errors
    SignObject()=default;
    /*
    Constructor for Sign Object

    You pass in the first vertice of the sign. The function extrapolates from there. 
    
    There are 2 or 4 vertices depending on sign

    Minus has 2 vertices:
        1)Left
        2)Right

        Each vertice has x and y coordinate
        {
            x,y,
            x,y
        }

    OR

    Plus has 4 vertices:
        1)Left
        2)Right
        3)Top
        4)Bottom

        Each vertice has x and y coordinate
        {
            x,y,
            x,y,
            x,y,
            x,y
        }
    
    You also pass in if it's positive or or negative
    true if positive
    flase if negative

    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    */
    SignObject(glm::vec2 position,bool isPositive);

    /*
    Used by IonObject::Render to render Sign
    */
    void Render();

    /*
    Deletes VAO,VBO,EBO
    */
    void Destroy();
};
#endif