#ifndef EBO_H
#define EBO_H

#include "GUIDependencies.h"
#include "StdLibDependencies.h"

struct EBO{

    //ID of EBO
    GLuint ID;
    
    //Number of Indices to pass in
    int noOfIndices;

    //Because errors
    EBO()=default;

    //Creates EBO object and does not unbind
    EBO(std::vector<GLuint> indices);

    //Binds EBO
    void Bind();

    //Unbinds EBO
    void UnBind();

    //Destroys EBO
    void Delete();
};
#endif