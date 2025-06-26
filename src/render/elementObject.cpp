#include "elementObject.h"

std::map<Element*,ElementObject*> ElementObject::elementObjects={};

ElementObject::ElementObject(glm::vec2 position, Element* el){

    GLfloat width;
    if(el->getSymbol().size()==1){
        width=elementSingleTextureWidth;
    }
    else if(el->getSymbol().size()==2){
        width=elementDoubleTextureWidth;
    }
    else{
        throw std::runtime_error("Atomic Symbol is Incorrect");
    } 

    Vertices={
        -width/2,-elementTextureHeight/2,0.0,0.0,
        -width/2,elementTextureHeight/2,1.0,0.0,
        width/2,elementTextureHeight/2,1.0,1.0,
        width/2,-elementTextureHeight/2,0.0,1.0
    };

    element=el;
    std::vector<GLuint> Indices={
        0,1,2,
        2,3,0
    };
 
    shaderProgram=shaders["element"];

    vao=VAO();
    vao.Bind();
    vbo=VBO(Vertices);
    ebo=EBO(Indices);
 
    vao.LinkVBO(vbo,0,2,GL_FLOAT,4*sizeof(GLfloat),0);
    vao.LinkVBO(vbo,1,2,GL_FLOAT,4*sizeof(GLfloat),(void*)(2*sizeof(GLfloat)));

    vbo.UnBind();
    vao.UnBind();
    ebo.UnBind();

    texture=Texture(elementFilePath1+std::to_string(el->getAtomicNumber())+elementFilePath2);

    this->position=position;
    model=glm::translate(glm::mat4(1.0f),glm::vec3(position,0.0f));

    elementObjects[element]=this;

    try{
        GenerateElectrons(width);
        GenerateDatives(width);
        GenerateCharge(width);
    }
    catch(std::runtime_error& e){
        throw;
    }
} 

void ElementObject::GenerateElectrons(GLfloat width){
    int n=element->getNumberOfValenceElectrons();
    GLfloat transparency=1.0f;

    for(int i=0;i<8;i++){
        glm::vec2 pos;

        if(i==n){
            transparency=0.0f;
        }

        if(i==0){
            pos={
               position[0] -width/2-electronDistanceDirect,position[1]-elementTextureHeight/2+electronDistanceAdjust 
            };

        }
        else if(i==1){
            pos={
                position[0]+ width/2+electronDistanceDirect,position[1]+elementTextureHeight/2-electronDistanceAdjust 
            };         
        }
        else if(i==2){
            pos={
                position[0]-width/2+electronDistanceAdjust,position[1]+elementTextureHeight/2+electronDistanceDirect 
            };         
        }
        else if(i==3){
            pos={
                position[0]+width/2-electronDistanceAdjust,position[13]-elementTextureHeight/2-electronDistanceDirect 
            };         
        }
        else if(i==4){
            pos={
                position[0]-width/2-electronDistanceDirect,position[1]+elementTextureHeight/2-electronDistanceAdjust 
            };
        }
        else if(i==5){
            pos={
                position[0]+width/2-electronDistanceAdjust,position[1]+elementTextureHeight/2+electronDistanceDirect 
            };         
        }
        else if(i==6){
            pos={
                position[12]+width/2+electronDistanceDirect,position[13]-elementTextureHeight/2+electronDistanceAdjust 
            };         
        }
        else if(i==7){
            pos={
                position[0]-width/2+electronDistanceAdjust,position[1]-elementTextureHeight/2-electronDistanceDirect 
            };
        }
        else{
            throw std::runtime_error("Electron Generation went Wrong");
        }

        //removed new for now
        ElectronObject electron= ElectronObject(pos,transparency);
        electrons[i]=electron;
    }
}

void ElementObject::GenerateDatives(GLfloat width){
    for(int i=0;i<4; i++){
        glm::vec2 pos;

        if(i==0){
            pos={
                position[0]-width/2-electronDistanceDirect,position[1]
            };
        }
        if(i==1){
            pos={
                position[0],pos[1]+elementTextureHeight/2+electronDistanceDirect
            };
        }
        if(i==2){
            pos={
                position[0]+width/2+electronDistanceDirect,position[1]
            };
        }
        if(i==3){
            pos={
                position[0],position[1]-elementTextureHeight/2-electronDistanceDirect
            };
        }
        else{
            throw std::runtime_error("Dative Generation went Wrong");
        }
        ElectronObject dative= ElectronObject(pos,0.0f);
        datives[i]=dative;
    }
} 
 
void ElementObject::GenerateCharge(GLfloat width){
    // std::vector<GLfloat> chargeVertice={
    //     Vertices[8],Vertices[9]
    // };
    // charge=ChargeObject(chargeVertice,element->getCharge());

    glm::vec2 pos={position[0]+width/2,position[1]+elementTextureHeight/2};

    charge=ChargeObject(pos,element->getCharge());
}

void ElementObject::Render(){

    shaderProgram.Activate();

    shaderProgram.SetMat4Uniform(model,"model");
    shaderProgram.SetMat4Uniform(cam.view,"view");
    shaderProgram.SetMat4Uniform(cam.proj,"proj");

    vao.Bind();
    texture.BindAndSetTexUnit(shaderProgram,"ourTexture");

    glDrawElements(GL_TRIANGLES, ebo.noOfIndices, GL_UNSIGNED_INT, 0);

    vao.UnBind();
    shaderProgram.Deactivate(); 
    texture.UnBind();

    // for(auto electron:electrons){
    //     electron.Render();
    // }

    // for(auto dative:datives){
    //     dative.Render();
    // }

    // charge.Render();
}






// for(int i=0;i<8;i++){
//     std::vector<GLfloat> electronVertices;

//     if(i==n){
//         transparency=0.0f;
//     }

//     if(i==0){
//         electronVertices={
//            Vertices[0]-electronDistanceDirect,Vertices[1]+electronDistanceAdjust ,transparency
//         };

//     }
//     else if(i==1){
//         electronVertices={
//             Vertices[8]+electronDistanceDirect,Vertices[9]-electronDistanceAdjust ,transparency
//         };         
//     }
//     else if(i==2){
//         electronVertices={
//             Vertices[4]+electronDistanceAdjust,Vertices[5]+electronDistanceDirect ,transparency
//         };         
//     }
//     else if(i==3){
//         electronVertices={
//             Vertices[12]-electronDistanceAdjust,Vertices[13]-electronDistanceDirect ,transparency
//         };         
//     }
//     else if(i==4){
//         electronVertices={
//             Vertices[4]-electronDistanceDirect,Vertices[5]-electronDistanceAdjust ,transparency
//         };
//     }
//     else if(i==5){
//         electronVertices={
//             Vertices[8]-electronDistanceAdjust,Vertices[9]+electronDistanceDirect ,transparency
//         };         
//     }
//     else if(i==6){
//         electronVertices={
//             Vertices[12]+electronDistanceDirect,Vertices[13]+electronDistanceAdjust ,transparency
//         };         
//     }
//     else if(i==7){
//         electronVertices={
//             Vertices[0]+electronDistanceAdjust,Vertices[1]-electronDistanceDirect ,transparency
//         };
//     }
//     else{
//         throw std::runtime_error("Electron Generation went Wrong");
//     }

//     //removed new for now
//     ElectronObject electron= ElectronObject(electronVertices,transparency
    
    
//     );
//     electrons[i]=electron;
