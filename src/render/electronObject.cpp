#include "electronObject.h"

ElectronObject::ElectronObject(glm::vec2 position,GLfloat transparency){

    // if(vertices.size()!=3){
    //     throw std::invalid_argument("Vertices are Invalid");
    // }
    // Vertices=vertices;

    Vertices={0.0f,0.0f,transparency};
    shaderProgram=shaders["electron"];
    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);

    vao.LinkVBO(vbo,0,2,GL_FLOAT,3*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,1,GL_FLOAT,3*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();

    this->position=position;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
} 

void ElectronObject::Render(){
    shaderProgram.Activate();
    vao.Bind();

    shaderProgram.SetMat4Uniform(model,"model");
    shaderProgram.SetMat4Uniform(cam.view,"view");
    shaderProgram.SetMat4Uniform(cam.proj,"proj");

    glDrawArrays(GL_POINTS, 0,1);

    vao.UnBind();
    shaderProgram.Deactivate();
}

void ElectronObject::Destroy(){
    vao.Delete();
    vbo.Delete();
} 