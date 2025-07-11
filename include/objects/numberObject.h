#ifndef NUMBEROBJECT_H
#define NUMBEROBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "chemistry.h"
#include "graphics.h"
#include "utils.h"

#include "texture.h"

struct NumberObject{
    
    /*
    Vertices

    Structure:
    There are 4 vertices
    They represent the 4 corners of rectangle

    1)Bottom Left
    2)Top Left
    3)Top Right
    4)Bottom Right

    Each vertice has x and y coordinate
    {
        x,y,0.0,0.0
        x,y,1.0,0.0
        x,y,1.0,1.0
        x,y,0.0,1.0
    }
    */
    std::vector<GLfloat> Vertices;

    //VAO for Number
    VAO vao;

    //VBO for Number
    VBO vbo;

    //EBO for Number
    EBO ebo;

    //Texture for Number. The texture is obtained from an atlas
    Texture texture;

    //Shader for Number
    Shader shaderProgram;

    //Number being represented
    int number;

    //Position vector of center of element in world space
    glm::vec2 position;

    //Model Matrix of Element. Ngl never understood
    glm::mat4 model;

    //Because Errors
    NumberObject()=default;
    
    /*
    Constructor for Number Object
 
    Takes in a vector(x,y) which is the center of the object in world space

    The constructor will then add texture coords depending on the number because of atlas

    Also takes in the number to be rendered. It can only be one digit and between 1 and 8 or -1 and -8 inclusive 
    The negative controls the color of the object. Red if negative, Blue if positive
 
    Throws std::runtime_error("Invalid Number") if number is not between 8 and 1 or -1 and -8 inclusive
    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    */
    NumberObject(glm::vec2 position, int number);

    /*
    Used by ChargeObject::Render to render number
    */
    void Render();
 
    /*
    Deletes VAO,VBO,EBO
    */ 
    void Destroy();

    void Move(glm::vec2 delta);

};

#endif