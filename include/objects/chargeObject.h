#ifndef CHARGEOBJECT_H
#define CHARGEOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "chemistry.h"
#include "graphics.h"
#include "utils.h"

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

    Takes in a vector(x,y) which is the center of the object in world space

    You pass in the bottom left positon of the number to be generated (Check NumberObject(glm::vec2 position,int number))
    and the number to be rendered

    Note: You must pass in the bottom left of the obejct. The construcptr handles internal logic for centering number and sign

    It generates Number and Sign
    Also takes in the number to be rendered. It can only be one digit and between 1 and 8 or -1 and -8 inclusive 
    The negative controls the color of the objects. Red if negative, Blue if positive

    Throws std::runtime_error("Invalid Number") if number is not between 8 and 1 or -1 and -8 inclusive
    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    */
    ChargeObject(glm::vec2 position,int number);

    /* 
    Used by ElementObject to Render Charges 
    */
    void Render();

    /*
    Destroys number and sign objects
    */
    void Destroy();

    void Move(glm::vec2 delta);
};
#endif