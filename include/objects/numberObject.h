#ifndef NUMBEROBJECT_H
#define NUMBEROBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "chemistry.h"
#include "graphics.h"
#include "utils.h"

#include "texture.h"

class NumberObject{
    
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
    std::vector<GLfloat> vertices;

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

    //Z index used to placed number object above other objects when selected
    GLfloat zIndex;
 
    public:
        //Because Errors
        NumberObject()=default;

        //Not Allowed
        NumberObject(const NumberObject&) = delete;
        NumberObject& operator=(const NumberObject&) = delete;
        
        /*
        Constructor for Number Object
    
        Takes in a vector(x,y) which is the center of the object in world space

        The constructor will then add texture coords depending on the number because of atlas

        Also takes in the number to be rendered. It can only be one digit and between -8 and 8 inclusive 
        The negative controls the color of the object. Red if negative, Blue if positive
        Note: 0 counts as positive
    
        Throws std::runtime_error("Invalid Number") if number is not between -8 and 8 inclusive
        Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
        */
        NumberObject(glm::vec2 pos, int number);

        // Move constructor and assignment  
        NumberObject(NumberObject&& other) noexcept;
        NumberObject& operator=(NumberObject&& other) noexcept;

        /* 
        Desttroys vao stuff
        */
        ~NumberObject();

        /*
        Used by ChargeObject::render to render number
        */
        void render();
    
        //Moves number by delta passed in
        void move(glm::vec2 delta);

        //Checks if number object covers the world position passed in 
        bool contains(glm::vec2 pos);
 
        /*
        Sets number
        
        It can only be one digit and between -8 and 8 inclusive 
        The negative controls the color of the object. Red if negative, Blue if positive
        Note: 0 counts as positive
    
        Throws std::runtime_error("Invalid Number") if number is not between -8 and 8 inclusive       
        */
        void setNumber(int n);

        /*
        Pass in: Z Index you want number object to have
        Changes Z index of number object to value passed in. Used to put the number object in front or below other objects
        */
        void shift(GLfloat i);

        //Returns number being represented
        int getNumber();
};

#endif