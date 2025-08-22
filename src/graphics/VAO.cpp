#include "VAO.h"

VAO::VAO(){
    glGenVertexArrays(1,&ID);
}

// VAO::VAO(VAO&& other) noexcept{
//     ID=other.ID;
//     other.ID=0;
// }

// VAO& VAO::operator=(VAO&& other) noexcept{
//     if (this != &other){
//         // Delete();
//         ID=other.ID;
//         other.ID=0;
//     }
//     return *this;
// }

// VAO::~VAO(){
//     Delete();
// }

void VAO::LinkVBO(VBO& vbo, GLuint layout, GLuint size, GLenum type, GLsizeiptr stride, void* offset){
    vbo.Bind(); 
    glVertexAttribPointer(layout,size,type,GL_FALSE,stride,offset);
    glEnableVertexAttribArray(layout);
    vbo.UnBind();
}

void VAO::Bind(){
    glBindVertexArray(ID);
}

void VAO::UnBind(){
    glBindVertexArray(0);
}

void VAO::Delete(){
    if(ID!=0){
        glDeleteVertexArrays(1,&ID);
        ID=0;
    }
}

//ok so:
//layout is the layout number of where we feed the data to in the shader
//numberOFproperties is the number of variables describing a property
// idk type
// stride is the total length of data describing a vertice 
// offset is the offset needed to reach the property we want
//the buffer is the actual raw data
//vao tells the compiler how to interpet the vertices and how to gert what indo