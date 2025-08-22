#include "VBO.h"

VBO::VBO(std::vector<GLfloat> vertices){
    glGenBuffers(1,&ID);
    glBindBuffer(GL_ARRAY_BUFFER,ID);
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(GLfloat),vertices.data(),GL_DYNAMIC_DRAW);
}

// VBO::VBO(VBO&& other) noexcept{
//     ID=other.ID;
//     other.ID=0;
// }

// VBO& VBO::operator=(VBO&& other) noexcept{
//     if (this != &other){
//         // Delete(); 
//         ID=other.ID;
//         other.ID=0;
//     }
//     return *this;
// }

// VBO::~VBO(){
//     Delete();
// }

void VBO::SetVertices(std::vector<GLfloat> vertices){
    glBufferData(GL_ARRAY_BUFFER,vertices.size()*sizeof(GLfloat),vertices.data(),GL_DYNAMIC_DRAW);
}

void VBO::UpdateVertices(std::vector<GLfloat> vertices){
    glBufferSubData(GL_ARRAY_BUFFER,0,vertices.size()*sizeof(GLfloat),vertices.data());
}

void VBO::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER,ID);
}

void VBO::UnBind(){
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VBO::Delete(){
    if(ID!=0){
        glDeleteBuffers(1,&ID);
        ID=0;
    }
}