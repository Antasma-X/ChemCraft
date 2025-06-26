#ifndef NUMBEROBJECT_H
#define NUMBEROBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "shader.h"

#include "element.h"

#include "config.h"


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

    Each vertice has x and y coordinate and texture coordinate
    The texture coordinate various depending on number due to a texture atlas
    {
        x,y,tex,tex,
        x,y,tex,tex,
        x,y,tex,tex,
        x,y,tex,tex
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


    glm::vec2 position;
    glm::mat4 model;
    //Because Errors
    NumberObject()=default;
    
    /*
    Constructor for Number Object
    Takes in 4 Vertices in the style:
        {
            x,y
            x,y
            x,y
            x,y
        }
 
        1)Bottom Left
        2)Top Left
        3)Top Right
        4)Bottom Right

    The constructor will then add texture coords depending on the number because of atlas

    Also takes in the number to be rendered. It can only be one digit and between 1 and 8 or -1 and -8 inclusive 
    The negative controls the color of the object. Red if negative, Blue if positive

    Throws std::runtime_error("Invalid Number") if number is not between 8 and 1 or -1 and -8 inclusive
    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    */
    NumberObject(glm::vec2 position, int number);

    /*
    Used by IonObject::Render to render number
    */
    void Render();
 
    /*
    Deletes VAO,VBO,EBO
    */ 
    void Destroy();
};

#endif