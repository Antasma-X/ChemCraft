#include"../include/element.h"
#include <gtest/gtest.h>
#include<iostream>

//do later i quit
struct ElementTest: testing::Test{
    protected:
    Element* Hydrogen;
    Element* Argon;
    Element* Carbon;
    Element* Nitrogen;
    Element* Calcium;
    Element* Bromine;
    Element* Gold;

    ElementTest(){
        Hydrogen=new Element(1);
        Argon= new Element(18,40);
        Carbon=new Element(6);
        Nitrogen=new Element(7,14,1);
        Calcium=new Element()
    }

    ~ElementTest(){
        delete testElement;
    }

    void SetUp(){

    }
};

TEST_F(ElementTests, idkyet){
    
    EXPECT_EQ("H",testElement->getName());
}
