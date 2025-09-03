#include "electronObject.h"

ElectronObject::ElectronObject(glm::vec2 pos,GLfloat transparency){

    vertices={
        -1.0f,-1.0f,transparency,
        -1.0f,1.0f,transparency,
        1.0f,1.0f,transparency,
        1.0f,-1.0f,transparency
    };

    std::vector<GLuint> indices={
        0,1,2,
        2,3,0
    }; 

    this->position=pos;
    this->transparency=transparency;
    isSelected=false;
    isHovered=false;
    zIndex=Z_NORMAL;

    shaderProgram=shaders["electron"];
    glowShaderProgram=shaders["glowElectron"];

    vao=VAO();
    vao.Bind();
    vbo=VBO(vertices);
    ebo=EBO(indices);

    vao.LinkVBO(vbo,0,2,GL_FLOAT,3*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,1,GL_FLOAT,3*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(electronRadius));
} 

ElectronObject::ElectronObject(ElectronObject&& other) noexcept{
    vertices=std::move(other.vertices);
    vao=std::move(other.vao);
    vbo=std::move(other.vbo);
    ebo=std::move(other.ebo);
    shaderProgram=other.shaderProgram;
    position=other.position;
    transparency=other.transparency;
    zIndex=other.zIndex;
    isSelected=other.isSelected;
    isHovered=other.isHovered;
    model=other.model;
} 

ElectronObject& ElectronObject::operator=(ElectronObject&& other) noexcept{
    if(this!=&other){
        vertices=std::move(other.vertices);
        vao=std::move(other.vao);
        vbo=std::move(other.vbo);
        ebo=std::move(other.ebo);
        shaderProgram=other.shaderProgram;
        position=other.position;
        transparency=other.transparency;
        zIndex=other.zIndex;
        isSelected=other.isSelected;
        isHovered=other.isHovered;
        model=other.model;
    }
    return *this;
}

ElectronObject::~ElectronObject(){
    // vao.Delete();
    // vbo.Delete(); 
    // ebo.Delete();
} 

void ElectronObject::render(){

    if(isSelected||isHovered||true){
        glm::mat4 glowModel = glm::translate(glm::mat4(1.0f), glm::vec3(position, zIndex));
        glowModel = glm::scale(glowModel, glm::vec3(electronRadius * 10.1f, electronRadius * 10.1f, 1.0f));

        glowShaderProgram.Activate();

        glowShaderProgram.SetMat4Uniform(glowModel, "model");
        glowShaderProgram.SetMat4Uniform(camera->GetView(), "view");
        glowShaderProgram.SetMat4Uniform(camera->GetProj(), "proj");
        if(isSelected){
            glowShaderProgram.Set1fUniform(elementSelectedGlowLevel, "glow");
        } 
        else if(isHovered||true){
            glowShaderProgram.Set1fUniform(elementHoveredGlowLevel, "glow");
        }

        vao.Bind();

        glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

        vao.UnBind();
        glowShaderProgram.Deactivate();
    }

    shaderProgram.Activate();

    shaderProgram.SetMat4Uniform(model,"model");
    shaderProgram.SetMat4Uniform(camera->GetView(),"view");
    shaderProgram.SetMat4Uniform(camera->GetProj(),"proj");

    vao.Bind();

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate();
}

void ElectronObject::move(glm::vec2 delta){
    position+=delta;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));
    model=glm::scale(model,glm::vec3(electronRadius));
}

bool ElectronObject::contains(glm::vec2 pos){
    return glm::distance(pos, position) <= electronRadius + electronSelectionBuffer;
} 

void ElectronObject::setTransparency(GLfloat transparency){
    this->transparency=transparency;

    vertices={
        -1.0f,-1.0f,transparency,
        -1.0f,1.0f,transparency,
        1.0f,1.0f,transparency,
        1.0f,-1.0f,transparency
    };

    vbo.Bind();
    vbo.UpdateVertices(vertices);
    vbo.UnBind();
}

void ElectronObject::select(bool b){
    isSelected=b;
 
    if(isSelected){
        zIndex=Z_SELECTED;
    }
    else{
        if(!isHovered){
            zIndex=Z_NORMAL;
        }
    }

    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(electronRadius));
}

void ElectronObject::hover(bool b){
    isHovered=b;

    if(!isSelected){
        if(isHovered){
            zIndex=Z_HOVERED;
        }
        else{
            zIndex=Z_NORMAL;
        }
    }

    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(electronRadius));
}

void ElectronObject::shift(GLfloat i){
    zIndex=i;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,zIndex));
    model=glm::scale(model, glm::vec3(electronRadius));
}
 
glm::vec2 ElectronObject::getPosition(){
    return position;
} 

GLfloat ElectronObject::getTransparency(){
    return transparency;
}

bool ElectronObject::isTransparent(){
    if(transparency<0.02f&&transparency>-0.02f){
        return true;
    }
    return false;
}