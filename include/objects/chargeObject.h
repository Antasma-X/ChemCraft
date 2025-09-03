#ifndef CHARGEOBJECT_H
#define CHARGEOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "chemistry.h"
#include "graphics.h"
#include "utils.h"

#include "numberObject.h"
#include "signObject.h"
 
class ChargeObject{

    //Number Texture Object
    NumberObject numberObj;

    //Sign Object
    SignObject signObj;

    public:
        //Because Errors
        ChargeObject()=default;

        //Not Allowed
        ChargeObject(const ChargeObject&) = delete;
        ChargeObject& operator=(const ChargeObject&) = delete;

        /*
        Constructor for Charge Object

        Takes in a vector(x,y) which is the center of the object in world space

        You pass in the bottom left positon of the number to be generated (Check NumberObject(glm::vec2 position,int number))
        and the number to be rendered

        Note: You must pass in the bottom left of the obejct. The construcptr handles internal logic for centering number and sign
        Note: 0 counts as positive

        It generates Number and Sign
        Also takes in the number to be rendered. It can only be one digit and between -8 and 8 inclusive 
        The negative controls the color of the objects. Red if negative, Blue if positive

        Throws std::runtime_error("Invalid Number") if number is not between -8 and 8 inclusive
        Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
        */
        ChargeObject(glm::vec2 position,int number);

        // Move constructor and assignment  
        ChargeObject(ChargeObject&& other) noexcept;
        ChargeObject& operator=(ChargeObject&& other) noexcept;

        //Destroys charge object
        ~ChargeObject();

        /* 
        Used by ElementObject::render to Render NumberObject and SignObject
        */
        void render();

        //Moves chargeObject by delta passed in
        void move(glm::vec2 delta);

        //Checks if sign or number object covers the world position passed in 
        bool contains(glm::vec2 pos);

        /*
        Sets number
        
        It can only be one digit and between -8 and 8 inclusive 
        The negative controls the color of the object. Red if negative, Blue if positive
        Note: 0 counts as positive
    
        Throws std::runtime_error("Invalid Number") if number is not between 8 and 1 or -1 and -8 inclusive       
        */ 
        void setNumber(int n);

        /*
        Pass in: Z Index you want sign and number objects to have
        Changes Z index of sign and number objects to value passed in. Used to put the sign and number objects in front or below other objects. Calls each object's shift function
        */ 
        void shift(GLfloat i); 

        //Returns position of charge object(left side middle)
        glm::vec2 getPosition();
        
        //Returns number being represented
        int getNumber();
};
#endif