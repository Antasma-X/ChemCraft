#include "numberObject.h"

NumberObject::NumberObject(glm::vec2 pos, int num){

    if(!(num<=8 &&num>=-8)){
        throw std::runtime_error("Invalid Number");
    }

    this->number=num; 
    this->position=pos;
    zIndex=Z_NORMAL;
    if(number>=0){
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
    vertices={
        -1.0f,-1.0f,w*0.2f,h+0.0f,
        -1.0f,1.0f,w*0.2f,h+0.5f,
        1.0f,1.0f,(w+1)*0.2f,h+0.5f,
        1.0f,-1.0f,(w+1)*0.2f,h+0.0f,
    };
    
    std::vector<GLuint> indices={
        0,1,2,
        2,3,0
    };

    shaderProgram=shaders["number"];
 
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
    model=glm::scale(model, glm::vec3(numberTextureWidth/2.0f,numberTextureHeight/2.0f,1.0f));
}

NumberObject::NumberObject(NumberObject&& other) noexcept{
    vertices=std::move(other.vertices);
    vao=std::move(other.vao);
    vbo=std::move(other.vbo);
    ebo=std::move(other.ebo);
    texture=std::move(other.texture);
    shaderProgram=other.shaderProgram;

    number=other.number;
    position=other.position;
    zIndex=other.zIndex;
    model=other.model; 
}

NumberObject& NumberObject::operator=(NumberObject&& other) noexcept{
    if(this!=&other){
        vertices=std::move(other.vertices);
        vao=std::move(other.vao);
        vbo=std::move(other.vbo);
        ebo=std::move(other.ebo);
        texture=std::move(other.texture);
        shaderProgram=other.shaderProgram;

        number=other.number;
        position=other.position;
        zIndex=other.zIndex;
        model=other.model;
    }
    return *this;
}

NumberObject::~NumberObject(){
    // vao.Delete();
    // vbo.Delete();
    // ebo.Delete();
    // texture.Delete();
}  

void NumberObject::render(){
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

void NumberObject::move(glm::vec2 delta){
    position+=delta;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(numberTextureHeight/2.0f,numberTextureHeight/2.0f,1.0f));
}

bool NumberObject::contains(glm::vec2 pos){
    if (pos.x >= position.x - numberTextureWidth/2.0f && pos.x <= position.x + numberTextureWidth/2.0f &&
        pos.y >= position.y - numberTextureHeight/2.0f && pos.y <= position.y + numberTextureHeight/2.0f
    ){
        return true;
    }
    return false;
}

void NumberObject::setNumber(int n){
    if(!(n<=8&&n>=-8)){
        throw std::runtime_error("Invalid Number");
    }
  
    if(n>=0){
        texture=Texture(numberBlueFilePath);
    }
    else if(n<0){
        texture=Texture(numberRedFilePath); 
    }
    else{
        throw std::runtime_error("Invalid Number");
    } 

    number=n; 
}

void NumberObject::shift(GLfloat i){
    zIndex=i;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(numberTextureHeight/2.0f,numberTextureHeight/2.0f,1.0f));
}

glm::vec2 NumberObject::getPosition(){
    return position;
}

int NumberObject::getNumber(){
    return number;
}