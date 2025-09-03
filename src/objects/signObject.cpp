#include "signObject.h"

SignObject::SignObject(glm::vec2 pos,bool isPositive){

    if(isPositive){
        pos.x+=plusSignTextureWidth/2;
        texture=Texture(plusFilePath);

        width=plusSignTextureWidth;
        height=plusSignTextureHeight;
    }
    else{
        pos.x+=minusSignTextureWidth/2;
        texture=Texture(minusFilePath);
 
        width=minusSignTextureWidth;
        height=minusSignTextureHeight;
    }

    vertices={
        -1.0f,-1.0f,0.0,0.0,
        -1.0f,1.0f,0.0,1.0,
        1.0f,1.0f,1.0,1.0,
        1.0f,-1.0f,1.0,0.0
    };

    std::vector<GLuint> indices={
        0,1,2,
        2,3,0
    };

    this->isPositive=isPositive;
    position=pos;
    zIndex=Z_NORMAL;

    shaderProgram=shaders["sign"];

    vao=VAO();
    vao.Bind();
    vbo=VBO(vertices);
    ebo=EBO(indices);

    vao.LinkVBO(vbo,0,2,GL_FLOAT,4*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,2,GL_FLOAT,4*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();
    
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(width/2.0f,height/2.0f,1.0f));
}

SignObject::SignObject(SignObject&& other) noexcept{
    vertices=std::move(other.vertices);
    vao=std::move(other.vao);
    vbo=std::move(other.vbo);
    ebo=std::move(other.ebo);
    texture=std::move(other.texture);
    shaderProgram=other.shaderProgram;

    isPositive=other.isPositive;
    position=other.position;
    width=other.width;
    height=other.height;
    model=other.model;
}

SignObject& SignObject::operator=(SignObject&& other) noexcept{
    if(this!=&other){
        vertices=std::move(other.vertices);
        vao=std::move(other.vao);
        vbo=std::move(other.vbo);
        ebo=std::move(other.ebo);
        texture=std::move(other.texture);
        shaderProgram=other.shaderProgram;

        isPositive=other.isPositive;
        position=other.position; 
        width=other.width;
        height=other.height;
        model=other.model;
    }
    return *this;
}

SignObject::~SignObject(){ 
    // vao.Delete();
    // vbo.Delete();
    // ebo.Delete();
    // texture.Delete();
}

void SignObject::render(){
    shaderProgram.Activate();

    shaderProgram.SetMat4Uniform(model,"model");
    shaderProgram.SetMat4Uniform(camera->GetView(),"view");
    shaderProgram.SetMat4Uniform(camera->GetProj(),"proj");
    
    vao.Bind();
    texture.BindAndSetTexUnit(shaderProgram,"ourTexture");

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate(); 
    texture.UnBind();
}

void SignObject::move(glm::vec2 delta){
    position+=delta;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(width/2.0f,height/2.0f,1.0f));
} 

bool SignObject::contains(glm::vec2 pos){
    if (pos.x >= position.x - width/2.0f && pos.x <= position.x + width/2.0f &&
        pos.y >= position.y - height/2.0f && pos.y <= position.y + height/2.0f
    ){
        return true;
    }
    return false;
}

void SignObject::setCharge(bool isPositive){
    if(this->isPositive!=isPositive){
        if(isPositive){
            position.x+=plusSignTextureWidth/2;
            texture=Texture(plusFilePath);

            width=plusSignTextureWidth;
            height=plusSignTextureHeight;
        }
        else{
            position.x+=minusSignTextureWidth/2;
            texture=Texture(minusFilePath);
    
            width=minusSignTextureWidth;
            height=minusSignTextureHeight;
        }

        this->isPositive=isPositive;
        model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
        model=glm::scale(model, glm::vec3(width/2.0f,height/2.0f,1.0f));
    }
}


void SignObject::shift(GLfloat i){
    zIndex=i;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(width/2.0f,height/2.0f,1.0f));
}

bool SignObject::isPlus(){
    return isPositive;
}