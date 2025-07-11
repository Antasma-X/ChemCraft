#include "chargeObject.h"

ChargeObject::ChargeObject(glm::vec2 position,int number){
    try{
        numberObj=NumberObject({position[0]+numberTextureWidth,position[1]+numberTextureHeight},number);
    }
    catch(std::invalid_argument& e){
        throw;
    }

    glm::vec2 signPosition={position[0]+numberTextureWidth,position[1]+numberTextureHeight};

    bool isPositive;
    if(number>0){
        isPositive=true;
    }
    else{
        isPositive=false;
    }
    try{
        signObj=SignObject(signPosition,isPositive);
    }
    catch(std::invalid_argument& e){
        throw;
    }
}
 
void ChargeObject::Render(){
    numberObj.Render();
    signObj.Render();
}

void ChargeObject::Destroy(){
    numberObj.Destroy();
    signObj.Destroy();
}

void ChargeObject::Move(glm::vec2 delta){
    numberObj.Move(delta);
    signObj.Move(delta);

}
