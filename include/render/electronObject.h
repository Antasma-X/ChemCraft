#ifndef ELECTRONOBJECT_H
#define ELECTRONOBJECT_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "shader.h"

#include "config.h"


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
    /*
    Note: There is no EBO
    */
    /*
    Shader for Electron. Draws point that is or is not transparent. Discards to make point
    */
    Shader shaderProgram;

    //Because Errors
    ElectronObject()=default;
    /*
    Constructor for Electron
    Takes one Vertice with 3 values: x,y,transparency

    Throws std::invalid_argument("Vertices are Invalid") if invalid vertices are passed in
    */
    ElectronObject(std::vector<GLfloat>vertices);

    /*
    Used by Render to Render electron
    */
    void Render();

    /*
    Deletes VAO,VBO,EBO
    */
    void Destroy();
};
#endif