#ifndef SIGNOBJECT_H
#define SIGNOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "chemistry.h"
#include "graphics.h"
#include "utils.h"

#include "texture.h"


class SignObject{

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

    //Height of the texture
    GLfloat height;

    //Width of the texture
    GLfloat width;

    //Z index used to placed sign object above other objects when selected
    GLfloat zIndex;

    public:
        //Because Errors
        SignObject()=default;
    
        //Not Allowed
        SignObject(const SignObject&) = delete;
        SignObject& operator=(const SignObject&) = delete;

        /*
        Constructor for Sign Object

        Takes in a vector(x,y) which is the left starting point of the object in world space

        You also pass in if it's positive or or negative
        true if positive
        false if negative 

        Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
        */
        SignObject(glm::vec2 position,bool isPositive);

        // Move constructor and assignment  
        SignObject(SignObject&& other) noexcept;
        SignObject& operator=(SignObject&& other) noexcept;

        /*
        Destroys vao stuff
        */
        ~SignObject();

        /*
        Used by ChargeObject::Render to render Sign
        */
        void render();

        //Moves by delta passed in
        void move(glm::vec2 delta); 

        //Checks if sign object covers the world position passed in 
        bool contains(glm::vec2 pos);

        //Sets charge to positive if true passed in else. else set to negative if false passed in
        void setCharge(bool isPositive);

        /*
        Pass in: Z Index you want sign object to have
        Changes Z index of sign object to value passed in. Used to put the sign object in front or below other objects
        */
        void shift(GLfloat i);

        //Checks if sign being represented is positive
        bool isPlus();
};

#endif