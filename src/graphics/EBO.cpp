#include "EBO.h"


EBO::EBO(std::vector<GLuint> indices){

    glGenBuffers(1,&ID);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(GLuint),indices.data(),GL_DYNAMIC_DRAW);
    noOfIndices=indices.size();
}

// EBO::EBO(EBO&& other) noexcept{
//     ID=other.ID;
//     noOfIndices=other.noOfIndices;

//     other.noOfIndices=0;
//     other.ID=0;
// }

// EBO& EBO::operator=(EBO&& other) noexcept{
//     if (this != &other){
//         Delete();
//         ID=other.ID;
//         other.ID=0;
//     }
//     return *this;
// }

// EBO::~EBO(){
//     Delete();
// }

void EBO::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ID);
}

void EBO::UnBind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void EBO::Delete(){
    if(ID!=0){
        glDeleteBuffers(1,&ID);
        ID=0;
    }
}