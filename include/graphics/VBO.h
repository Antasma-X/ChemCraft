#ifndef VBO_H
#define VBO_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

struct VBO{

    //ID of VBO
    GLuint ID;

    //Because errors
    VBO()=default;

    // //Not Allowed
    // VBO(const VBO&)=delete;
    // VBO& operator=(const VBO&)=delete;

    //Creates VBO using vertices passed in. Does not unbind vbo
    VBO(std::vector<GLfloat> vertices);

    // // Move constructor and assignment
    // VBO(VBO&& other) noexcept; 
    // VBO& operator=(VBO&& other) noexcept;

    // //Destroys VBO
    // ~VBO();

    //Sets vertices to vertices passed in
    void SetVertices(std::vector<GLfloat> vertices);

    //Updates vertices to new vertices passed in. new vertices must have same structure as previous vertices
    void UpdateVertices(std::vector<GLfloat> vertices);

    //Binds VBO
    void Bind();

    //Unbinds VBO
    void UnBind();

    //Destroys VBO
    void Delete();
};

#endif