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

    // //Not Allowed
    // EBO(const EBO&)=delete;
    // EBO& operator=(const EBO&)=delete;

    //Creates EBO object and does not unbind
    EBO(std::vector<GLuint> indices);

    // // Move constructor and assignment
    // EBO(EBO&& other) noexcept;
    // EBO& operator=(EBO&& other) noexcept;

    // //Destroys EBO
    // ~EBO();

    //Binds EBO
    void Bind();

    //Unbinds EBO
    void UnBind();

    //Destroys EBO
    void Delete();
};
#endif