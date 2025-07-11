#include "electronObject.h"

ElectronObject::ElectronObject(glm::vec2 position,GLfloat transparency){

    Vertices={
        -1.0f,-1.0f,transparency,
        1.0f,-1.0f,transparency,
        -1.0f,1.0f,transparency,
        1.0f,1.0f,transparency
    };
    shaderProgram=shaders["electron"];

        std::vector<GLuint> Indices={
        0,1,2,
        2,3,0
    };
    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);
    ebo=EBO(Indices);

 
    vao.LinkVBO(vbo,0,2,GL_FLOAT,3*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,1,GL_FLOAT,3*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    this->position=position;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
    model = glm::scale(model, glm::vec3(2 * 0.5f));
} 

void ElectronObject::Render(){
    shaderProgram.Activate();
    vao.Bind();

    shaderProgram.SetMat4Uniform(model,"model");
    shaderProgram.SetMat4Uniform(camera->GetView(),"view");
    shaderProgram.SetMat4Uniform(camera->GetProj(),"proj");

    // glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    // glDrawArrays(GL_POINTS, 0,1);

    vao.UnBind();
    shaderProgram.Deactivate();

}

void ElectronObject::Destroy(){
    vao.Delete();
    vbo.Delete();
} 

void ElectronObject::Move(glm::vec2 delta){
    position+=delta;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
    model = glm::scale(model, glm::vec3(2 * 0.5f));


}
