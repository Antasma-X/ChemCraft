#include "numberObject.h"

NumberObject::NumberObject(glm::vec2 position, int number){

    if(!((number<=8 &&number>=1)||(number>=-8&&number<=-1))){
        throw std::runtime_error("Invalid Number");
    }

    this->number=number;
 
    if(number>0){
        texture=Texture(numberBlueFilePath);
    }
    else if(number<0){
        texture=Texture(numberRedFilePath);
    }
    else{
        throw std::runtime_error("Invalid Number");
    } 
 
    float h=std::abs(number)<5?0.0f:0.5f;
    float w=std::abs(number)%5;
    Vertices={
        -numberTextureWidth/2,-numberTextureHeight/2,w*0.2f,h+0.0f,
        -numberTextureWidth/2,numberTextureHeight/2,w*0.2f,h+0.5f,
        numberTextureWidth/2,numberTextureHeight/2,(w+1)*0.2f,h+0.5f,
        numberTextureWidth/2,-numberTextureHeight/2,(w+1)*0.2f,h+0.0f,
    };
    
    std::vector<GLuint> Indices={
        0,1,2,
        2,3,0
    };

    shaderProgram=shaders["number"];
 
    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);
    ebo=EBO(Indices);

    vao.LinkVBO(vbo,0,2,GL_FLOAT,4*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,2,GL_FLOAT,4*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    this->position=position;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
    model=glm::scale(model,glm::vec3(1.0f,1.0f,1.0f));
}

void NumberObject::Render(){
    shaderProgram.Activate();
    vao.Bind();

    shaderProgram.SetMat4Uniform(model,"model");
    shaderProgram.SetMat4Uniform(camera->GetView(),"view");
    shaderProgram.SetMat4Uniform(camera->GetProj(),"proj");
    
    texture.BindAndSetTexUnit(shaderProgram,"ourTexture");

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate(); 
    texture.UnBind();
}

void NumberObject::Destroy(){
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    texture.Delete();
} 

void NumberObject::Move(glm::vec2 delta){
    position+=delta;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
}