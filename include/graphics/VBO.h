#ifndef VBO_H
#define VBO_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

struct VBO{

    //ID of VBO
    GLuint ID;

    //Because errors
    VBO()=default;

    //Creates VBO using vertices passed in. Does not unbind vbo
    VBO(std::vector<GLfloat> vertices);

    //Binds VBO
    void Bind();

    //Unbinds VBO
    void UnBind();

    //Destroys VBO
    void Delete();

};

#endif