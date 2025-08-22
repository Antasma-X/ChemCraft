#ifndef ELECTRONOBJECT_H
#define ELECTRONOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "graphics.h"
#include "utils.h"

class ElectronObject{

    /*
    Vertices

    Structure:
    There are 4 vertices representing the 4 corners

    1)Bottom Left
    2)Top Left 
    3)Top Right
    4)Bottom Right

    Each vertice has x and y coordinate and a transparency value
    {
        x,y,transparency
        x,y,transparency
        x,y,transparency
        x,y,transparency
    }
    */
    std::vector<GLfloat> vertices;

    //VAO for Electron
    VAO vao;

    //VBO for Electron 
    VBO vbo;

    //EBO for Electron
    EBO ebo;

    /*
    Shader for Electron. Draws point that is or is not transparent. Discards to make point
    */
    Shader shaderProgram;

    //Shader for the glow surrounding electron when selected or hovered
    Shader glowShaderProgram;

    //Position vector of center of electron in world space
    glm::vec2 position;

    //Model Matrix of Electron. Ngl never understood
    glm::mat4 model;

    //Transparency of electron
    GLfloat transparency;

    //Z index used to placed electron object above other objects when selected
    GLfloat zIndex;

    //true if selected, false if not. Takes precedences over hovering. if true, glow shader is used with selection amount of glow
    bool isSelected;

    //true if hovered over, false if not. if true, glow shader is used with hover amount of glow
    bool isHovered;

    public:
        //Because Errors
        ElectronObject()=default;

        //Not Allowed
        ElectronObject(const ElectronObject&) = delete;
        ElectronObject& operator=(const ElectronObject&) = delete;

        /*
        Constructor for Electron
        
        Takes in a vector(x,y) which is the center of the object in world space

        Takes in transparency value, 1.0f if opaque, 0.0f if transparent

        Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
        */
        ElectronObject(glm::vec2 pos,GLfloat transparency);
    
        // Move constructor and assignment  
        ElectronObject(ElectronObject&& other) noexcept;
        ElectronObject& operator=(ElectronObject&& other) noexcept;

        /*
        Destructor for Electron Object

        Destroys vao stuff 
        */
        ~ElectronObject();

        /*
        Used by ElementObject::render to Render electron
        */
        void render();

        //Moves electron by delta passed in
        void move(glm::vec2 delta);

        //Checks if electronObject covers the world position passed in 
        bool contains(glm::vec2 pos);

        //Sets Transparency to Glfloat passed in
        void setTransparency(GLfloat transparency);

        /*
        Pass in: true if selecting
                 false if unselecting

        Note: passing in false or true twice in a row is fine

        This causes a selection level glow to surround the electron by allowing the glowShader to be used and increases the z index to Z_SELECTED
        Takes precedence over hover in any behaviour
        */
        void select(bool b);

        /*
        Pass in: true if hovering
                 false if unhovering

        Note: passing in false or true twice in a row is fine

        This causes a hover level glow to surround the element by allowing the glowShader to be used and increases the z index to Z_HOVERED
        */
        void hover(bool b);

        /*
        Pass in: Z Index you want electron to have
        Changes Z index of electron to i passed in. Used to put the electron in front or below other objects
        */
        void shift(GLfloat i);

        //Returns position of electron
        glm::vec2 getPosition();

        //Returns transparency of electron. 1.0f if opaque,0.0f if transparent
        GLfloat getTransparency();

        //Checks if electron is transparent
        bool isTransparent();

}; 
#endif