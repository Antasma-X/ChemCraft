#include "bondObject.h"

std::vector<BondObject*> BondObject::bonds={};

void BondObject::updateModel(){

    //Thanks chatgpt
    glm::vec2 dir = ends[1] - ends[0];
    float len = glm::length(dir);
    float angle = atan2(dir.y, dir.x);

    model = glm::mat4(1.0f);
    glm::vec2 center = 0.5f * (ends[0] + ends[1]);
    model = glm::translate(glm::mat4(1.0f), glm::vec3(center, zIndex));
    model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(len, bondThickness, 1.0f));
}

BondObject::BondObject(std::vector<glm::vec2> ends,std::vector<ElementObject*> els,int type){

    if(ends.size()!=2){
        throw std::invalid_argument("Vertices are Invalid");
    } 
     
    if(type==0){
        shaderProgram=shaders["covalent"];
    }
    else if(type==1){
        shaderProgram=shaders["ionic"];
    }
    else if(type==2){
        shaderProgram=shaders["dative"];
    }
    else{
        throw std::invalid_argument("Invalid Bond Type");
    }

    glowShaderProgram=shaders["glowBond"];

    this->ends=ends;
    this->type=type;
    zIndex=Z_NORMAL;
    isSelected=false;
    isHovered=false;
    elements=els;
    
    vertices = {
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f,  0.5f,
        0.5f,  -0.5f
    };
    
    std::vector<GLuint> indices={
        0,1,2,
        2,3,0
    }; 

    vao=VAO();
    vao.Bind();
    vbo=VBO(vertices);
    ebo=EBO(indices);
 
    vao.LinkVBO(vbo,0,2,GL_FLOAT,2*sizeof(GLfloat),0);

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    updateModel();

    bonds.push_back(this);
}

BondObject::BondObject(BondObject&& other) noexcept{
    vertices=std::move(other.vertices);
    vao=std::move(other.vao);
    vbo=std::move(other.vbo);
    ebo=std::move(other.ebo);
    shaderProgram=other.shaderProgram;
    ends=other.ends;
    model=other.model; 
    isSelected=other.isSelected;
    isHovered=other.isHovered;
    zIndex=other.zIndex;
    type=other.type;
    elements=other.elements;

    auto it=std::find(bonds.begin(),bonds.end(),&other);
	if (it != bonds.end()){
		bonds.erase(it);
	}

    bonds.push_back(this);
}

BondObject& BondObject::operator=(BondObject&& other) noexcept{
    if(this!=&other){
        vertices=std::move(other.vertices);
        vao=std::move(other.vao);
        vbo=std::move(other.vbo);
        ebo=std::move(other.ebo);
        shaderProgram=other.shaderProgram;
        ends=other.ends;
        model=other.model; 
        isSelected=other.isSelected;
        isHovered=other.isHovered;
        zIndex=other.zIndex;
        type=other.type;
        elements=other.elements;

        auto it=std::find(bonds.begin(),bonds.end(),&other);
        if (it != bonds.end()){
            bonds.erase(it);
        }

        bonds.push_back(this);
    }
    return *this;
}

BondObject::~BondObject(){
    // vao.Delete(); 
    // vbo.Delete(); 
    // ebo.Delete();
 
    auto it=std::find(bonds.begin(),bonds.end(),this);
	if (it != bonds.end()){
		bonds.erase(it);
	}
}
 
void BondObject::render(){
    if(isSelected||isHovered){
        glm::mat4 glowModel=model;
        glowModel = glm::scale(glowModel, glm::vec3(1.1f, 1.2f, 1.0f));

        glowShaderProgram.Activate();

        glowShaderProgram.SetMat4Uniform(glowModel, "model");
        glowShaderProgram.SetMat4Uniform(camera->GetView(), "view");
        glowShaderProgram.SetMat4Uniform(camera->GetProj(), "proj");
        if(isSelected){
            glowShaderProgram.Set1fUniform(elementSelectedGlowLevel, "glow");
        }
        else if(isHovered){
            glowShaderProgram.Set1fUniform(elementHoveredGlowLevel, "glow");
        }

        vao.Bind();

        glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

        vao.UnBind();
        glowShaderProgram.Deactivate();
    }
    shaderProgram.Activate();

    shaderProgram.SetMat4Uniform(model, "model");
    shaderProgram.SetMat4Uniform(camera->GetView(),"view");
    shaderProgram.SetMat4Uniform(camera->GetProj(),"proj");

    vao.Bind(); 

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate();
} 

void BondObject::move(glm::vec2 delta, int i){
    ends[i]+=delta;
    updateModel();
}

bool BondObject::contains(glm::vec2 pos){
    //Thank you chtgpt again
    glm::mat4 invModel = glm::inverse(model);

    glm::vec4 localPos4 = invModel * glm::vec4(pos, zIndex, 1.0f);
    glm::vec2 localPos = glm::vec2(localPos4);

    // Bond is axis-aligned in local space with center at (0,0), length 1, thickness = 1
    // After scaling, the local bounds are: [-0.5, 0.5] in X, [-0.5, 0.5] in Y
    // So the bounds become:
    float halfLen = 0.5f;  // in local x direction (after scale it's [-0.5, 0.5])
    float halfThickness = 0.5f; // same

    // You can tighten this if you like:
    return std::abs(localPos.x) <= 1.5f && std::abs(localPos.y) <= 1.5f;
}
 
void BondObject::hover(bool b){
    isHovered=b;

    if(!isSelected){
        if(isHovered){
            zIndex=Z_HOVERED;
        }
        else{
            zIndex=Z_NORMAL;
        }
    }

    updateModel();
}

void BondObject::select(bool b){
    isSelected=b;

    if(isSelected){
        zIndex=Z_SELECTED;
    }
    else{
        if(!isHovered){
            zIndex=Z_NORMAL;
        }
    }
 
    updateModel();
}

void BondObject::shift(GLfloat i){
    zIndex=i;
    updateModel();
}

int BondObject::getType(){
    return type;
}

std::vector<ElementObject*> BondObject::getElements(){
    return elements;
}

std::vector<BondObject*> BondObject::getAllBondObjects(){
    return bonds;
}