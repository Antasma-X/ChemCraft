#include "bondObject.h"

std::vector<BondObject*> BondObject::bonds={};

BondObject::BondObject(std::vector<glm::vec2> ends,std::vector<ElementObject*> elements,int type){

    if(ends.size()!=2){
        throw std::invalid_argument("Vertices are Invalid");
    }
    
    this->ends=ends;
    this->elements=elements;
    std::vector<GLuint> indices={0,1,2,2,3,0}; 
    
    Vertices = {
        0.0f, -0.5f,
        1.0f, -0.5f,
        0.0f,  0.5f,
        1.0f,  0.5f
    };
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
    glm::vec2 dir = ends[1] - ends[0];
    float len = glm::length(dir);
    float angle = atan2(dir.y, dir.x);

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(ends[0], 0.0f));
    model = glm::rotate(model, angle, glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(len, 10.0f, 1.0f));  // thickness
}
 
void BondObject::Render(){
    shaderProgram.Activate();

        shaderProgram.SetMat4Uniform(model, "model");

    shaderProgram.SetMat4Uniform(camera->GetView(),"view");
    shaderProgram.SetMat4Uniform(camera->GetProj(),"proj");
    vao.Bind(); 

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    // glLineWidth(bondThickness);
    // glDrawArrays(GL_LINES, 0, 2);

    vao.UnBind();
    shaderProgram.Deactivate();
} 

void BondObject::Move(glm::vec2 delta, int i){
    ends[i]+=delta;

    vao.Bind();
    vbo=VBO({ends[0].x,ends[0].y,
             ends[1].x,ends[1].y});
    ebo.Bind();

    vao.LinkVBO(vbo,0,2,GL_FLOAT,2*sizeof(GLfloat),0);

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();
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