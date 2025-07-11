#ifndef ELECTRONOBJECT_H
#define ELECTRONOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "graphics.h"
#include "utils.h"

struct ElectronObject{

    /*
    Vertices

    Structure:
    There is 1 vertice

    Each vertice has x and y coordinate and a transparency value
    {
        x,y,transparency
    }
    */
    std::vector<GLfloat> Vertices;

    //VAO for Electron
    VAO vao;

    //VBO for Electron 
    VBO vbo;

    EBO ebo;
    /*
    Note: There is no EBO
    */

    /*
    Shader for Electron. Draws point that is or is not transparent. Discards to make point
    */
    Shader shaderProgram;

    //Position vector of center of element in world space
    glm::vec2 position;

    //Model Matrix of Element. Ngl never understood
    glm::mat4 model;
    
    //Because Errors
    ElectronObject()=default;

    /*
    Constructor for Electron
    
    Takes in a vector(x,y) which is the center of the object in world space

    Takes in transparency value, 1.0f if opaque, 0.0f if transparent

    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    */
    ElectronObject(glm::vec2 position,GLfloat transparency);
 
    /*
    Used by ElementObject::Render Render to Render electron
    */
    void Render();

    /*
    Deletes VAO,VBO,EBO
    */
    void Destroy();

    
    void Move(glm::vec2 delta);

};
#endif