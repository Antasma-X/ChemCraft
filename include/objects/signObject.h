#ifndef SIGNOBJECT_H
#define SIGNOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "chemistry.h"
#include "graphics.h"
#include "utils.h"

#include "texture.h"


struct SignObject{

    
    static GLuint colorLocation;
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

    //VAO for Sign
    VAO vao;

    //VBO for Sign
    VBO vbo;
  
    //VBO for Sign
    EBO ebo;

    //Texture for Number. The texture is obtained from an atlas
    Texture texture;

    //Shader for Sign. Red if minus, Blue if Plus
    Shader shaderProgram;

    // true if plus, false if minus
    bool isPositive;

    //Position vector of center of element in world space
    glm::vec2 position;

    //Model Matrix of Element. Ngl never understood
    glm::mat4 model; 

    //Because Errors
    SignObject()=default;
 
    /*
    Constructor for Sign Object

    Takes in a vector(x,y) which is the left starting point of the object in world space

    You also pass in if it's positive or or negative
    true if positive
    flase if negative

    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    */
    SignObject(glm::vec2 position,bool isPositive);

    /*
    Used by ChargeObject::Render to render Sign
    */
    void Render();

    /*
    Deletes VAO,VBO,EBO
    */
    void Destroy();

    void Move(glm::vec2 delta);

};
#endif