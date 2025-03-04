#include "electronObject.h"

ElectronObject::ElectronObject(std::vector<GLfloat> vertices){

    if(vertices.size()!=3){
        throw std::invalid_argument("Vertices are Invalid");
    }
    Vertices=vertices;

    shaderProgram=shaders["electron"];
    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);

    vao.LinkVBO(vbo,0,2,GL_FLOAT,3*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,1,GL_FLOAT,3*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
} 

void ElectronObject::Render(){
    shaderProgram.Activate();
    vao.Bind();

    glDrawArrays(GL_POINTS, 0,1);

    vao.UnBind();
    shaderProgram.Deactivate();
}

void ElectronObject::Destroy(){
    vao.Delete();
    vbo.Delete();
}