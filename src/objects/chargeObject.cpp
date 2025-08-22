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
    if(number>=0){
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

ChargeObject::ChargeObject(ChargeObject&& other) noexcept{
    numberObj=std::move(other.numberObj);
    signObj=std::move(other.signObj);
}

ChargeObject& ChargeObject::operator=(ChargeObject&& other) noexcept{
    if(this!=&other){
        numberObj=std::move(other.numberObj);
        signObj=std::move(other.signObj);
    }
    return *this;
} 

ChargeObject::~ChargeObject(){

}

void ChargeObject::render(){
    numberObj.render();
    signObj.render();
}

void ChargeObject::move(glm::vec2 delta){
    numberObj.move(delta);
    signObj.move(delta);
} 

bool ChargeObject::contains(glm::vec2 pos){
    return signObj.contains(pos)||numberObj.contains(pos);
}

void ChargeObject::setNumber(int n){
    numberObj.setNumber(n);

    if(numberObj.getNumber()>=0&&(!signObj.isPlus())){
        signObj.setCharge(true);
    }
    else if(numberObj.getNumber()<0&&signObj.isPlus()){
        signObj.setCharge(false);
    }
}
 
void ChargeObject::shift(GLfloat i){
    numberObj.shift(i);
    signObj.shift(i);
}

int ChargeObject::getNumber(){
    return numberObj.getNumber();
}