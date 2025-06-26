#ifndef CHARGEOBJECT_H
#define CHARGEOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "texture.h"
#include "shader.h"

#include "element.h"

#include "config.h"

#include "numberObject.h"
#include "signObject.h"


struct ChargeObject{

    //Number Texture Object
    NumberObject numberObj;

    //Sign Object
    SignObject signObj;

    //Because Errors
    ChargeObject()=default;
    /*
    Constructor for Charge Object
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

    You pass in the Vertices for the number to be generated (Check NumberObject(std::vector<GLfloat> vertices,int number))
    and the number to be rendered

    It generates Number and Sign
    Also takes in the number to be rendered. It can only be one digit and between 1 and 8 or -1 and -8 inclusive 
    The negative controls the color of the objects. Red if negative, Blue if positive

    Throws std::runtime_error("Invalid Number") if number is not between 8 and 1 or -1 and -8 inclusive
    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    */
    ChargeObject(glm::vec2 position,int number);

    /* 
    Used by Render to Render Charges 
    */
    void Render();

    /*
    Destroys number and sign objects
    */
    void Destroy();

};
#endif