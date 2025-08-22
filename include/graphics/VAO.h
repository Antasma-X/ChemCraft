#ifndef VAO_H
#define VAO_H

#include"GUIDependencies.h"
#include "StdLibDependencies.h"

#include "VBO.h"

struct VAO{

    //ID of VAO
    GLuint ID;

    // //Not Allowed
    // VAO(const VAO&)=delete;
    // VAO& operator=(const VAO&)=delete;

    //Creates VAO but does not link it
    VAO();

    // // Move constructor and assignment
    // VAO(VAO&& other) noexcept;
    // VAO& operator=(VAO&& other) noexcept;

    // //Destroys VAO
    // ~VAO();
    
    /*
    Links the VBO to the VAO. Does not bind the VAO automatically but does bind and unbind the VBO automatically
    Needs to be called multpiple times for each property

    Pass in: VBO Reference, layout, size,type,stride,offset
    */
    void LinkVBO(VBO& vbo, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, void* offset);

    //Binds VAO
    void Bind();

    //Unbinds VAO
    void UnBind();

    //Destroys VAO
    void Delete();
};

#endif