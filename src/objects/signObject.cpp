#include "signObject.h"

// GLuint SignObject::colorLocation;
SignObject::SignObject(glm::vec2 position,bool isPositive){

    this->isPositive=isPositive;

    if(isPositive){

        position.x+=plusSignTextureWidth/2;

        texture=Texture(plusFilePath);
        Vertices={
            -plusSignTextureWidth/2,-plusSignTextureHeight/2,0.0,0.0,
            -plusSignTextureWidth/2,plusSignTextureHeight/2,0.0,1.0,
            plusSignTextureWidth/2,plusSignTextureHeight/2,1.0,1.0,
            plusSignTextureWidth/2,-plusSignTextureHeight/2,1.0,0.0
        };
    }
    else{

        position.x+=minusSignTextureWidth/2;

        texture=Texture(minusFilePath);
        Vertices={
            -minusSignTextureWidth/2,-minusSignTextureHeight/2,0.0,0.0,
            -minusSignTextureWidth/2,minusSignTextureHeight/2,0.0,1.0,
            minusSignTextureWidth/2,minusSignTextureHeight/2,1.0,1.0,
            minusSignTextureWidth/2,-minusSignTextureHeight/2,1.0,0.0
        };
    }

    std::vector<GLuint> Indices={
        0,1,2,
        2,3,0
    };

    shaderProgram=shaders["sign"];

    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);
    ebo=EBO(Indices);

    vao.LinkVBO(vbo,0,2,GL_FLOAT,2*sizeof(GLfloat),0);

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    
    this->position=position;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
    model=glm::scale(model,glm::vec3(1.0f,1.0f,1.0f));
}

void SignObject::Render(){
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

void SignObject::Destroy(){ 
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
}

void SignObject::Move(glm::vec2 delta){
    position+=delta;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
}