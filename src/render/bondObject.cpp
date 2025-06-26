#include "bondObject.h"

std::vector<BondObject*> BondObject::bonds={};

BondObject::BondObject(std::vector<glm::vec2> ends,int type){

    if(ends.size()!=2){
        throw std::invalid_argument("Vertices are Invalid");
    }
    
    this->ends=ends;
    Vertices=vertices;
    std::vector<GLuint> indices={0,1};
    
    if(type==0){
        shaderProgram=shaders["covalent"];
    }
    else if(type=1){
        shaderProgram=shaders["ionic"];
    }
    else if(type==2){
        shaderProgram=shaders["dative"];
    }
    else{
        throw std::invalid_argument("Invalid Bond Type");
    }
    this->type=type;


    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);
    ebo=EBO(indices);
 
    vao.LinkVBO(vbo,0,2,GL_FLOAT,2*sizeof(GLfloat),0);

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    bonds.push_back(this);
}

void BondObject::Render(){
    shaderProgram.Activate();
    vao.Bind();

    glLineWidth(bondThickness);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate();
}

BondObject::~BondObject(){
    vao.Delete();
    vbo.Delete();
    ebo.Delete();

    auto it=std::find(bonds.begin(),bonds.end(),this);
	if (it != bonds.end()){
		bonds.erase(it);
	}
}