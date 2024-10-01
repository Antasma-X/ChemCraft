#include "../include/compound.h"
#include "../include/values.h"
#include <map>

//generate molecule for elelemnt idea
Compound* makeMolecule(std::string name){
    makeMolecule(molecules[name]);
}
Compound* makeMolecule(int n){

    Compound* newCompound;
    switch(n){
        case 1:
            Element* H1=new Element(1);
            Element* H2=new Element(1);
            Element* O=new Element(8);

            newCompound=new Compound(*H1);
            newCompound->addElement(*H1,*O,0);
            newCompound->addElement(*O,*H2,0);
            
            break;
        case 2:
            Element* O1=new Element(8);
            Element* O2=new Element(8);
            Element* C=new Element(6);            

            newCompound=new Compound(*C);
            newCompound->addElement(*C,*O1,0);
            newCompound->addElement(*C,*O2,0);
            break;
        case 3:
            Element* O=new Element(8);
            Element* C=new Element(6);            

            newCompound=new Compound(*C);
            newCompound->addElement(*C,*O,0);
            break;          
        case 4:
            Element* H1=new Element(1);
            Element* H2=new Element(1);
            Element* O1=new Element(8);
            Element* O2=new Element(8);

            newCompound=new Compound(*H1);
            newCompound->addElement(*H1,*O1,0);
            newCompound->addElement(*O1,*O2,0);
            newCompound->addElement(*O2,*H2,0);
            break;
        case 5:
            Element* O1=new Element(8);
            Element* O2=new Element(8);
            Element* O3=new Element(8);

            newCompound=new Compound(*O1);
            newCompound->addElement(*O1,*O2,0);
            newCompound->addElement(*O2,*O3,0);
            newCompound->createBond(*O1,*O3,0);
            break;
        case 6:
            Element* N=new Element(7);
            Element* H1=new Element(1);
            Element* H2=new Element(1);
            Element* H3=new Element(1);

            newCompound=new Compound(*N);
            newCompound->addElement(*N,*H1,0);
            newCompound->addElement(*N,*H2,0);
            newCompound->addElement(*N,*H3,0);
            break;
        case 7:
            Element* N=new Element(7);
            Element* O1=new Element(8);
            Element* O2=new Element(8);

            newCompound=new Compound(*N);
            newCompound->addElement(*N,*O1,0);
            newCompound->addElement(*N,*O2,0);
            newCompound->createBond(*N,*O1,0);         
            break;
        default:
            break;   
        
    }
}

//combine 2 elemnts somhow


Compound* generateMoleculeOfElement(int atomicNumber){
    if(atomicity.find(atomicNumber) == atomicity.end()){
        // error
    }else{
        std::vector<Element*> elements;
        
        for(int i=0;i<atomicity[atomicNumber];i++){
            elements.emplace_back(new Element(atomicNumber));
        }
        Compound* newCompound=new Compound(*elements[0]);

        for(int i=1;i<elements.size();i++){
            newCompound->addElement(*elements[i-1],*elements[i],0);
        }
        newCompound->createBond(*elements[0],*elements[elements.size()-1],0);
        return newCompound;
    }
}

Compound* makeAnion(std::string name){
    return makeAnion(anions[name]);
}

Compound* makeAnion(int n){
    Compound* newCompound;
    switch(n){
        case 1:
            newCompound= new Compound(9);
            break;
        case 2:
            newCompound= new Compound(17);
            break;
        case 3:
            newCompound= new Compound(35);
            break;
        case 4:
            newCompound= new Compound(53);
            break;
        case 5:
            Element* S = new Element(16);
            Element* O1 = new Element(8);
            Element* O2= new Element(8);
            Element* O3 = new Element(8);
            Element* O4 = new Element(8);

            newCompound=new Compound(*S);
            newCompound->addElement(*S,*O1,0);
            newCompound->addElement(*S,*O2,0);
            newCompound->addElement(*S,*O3,0);
            newCompound->addElement(*S,*O4,0);

            newCompound->createBond(*S,*O2,0);
            newCompound->createBond(*S,*O4,0);
            break;
        case 6:
            Element* S = new Element(16);
            Element* O1 = new Element(8);
            Element* O2= new Element(8);
            Element* O3 = new Element(8);

            newCompound=new Compound(*S);
            newCompound->addElement(*S,*O1,0);
            newCompound->addElement(*S,*O2,0);
            newCompound->addElement(*S,*O3,0);
            newCompound->createBond(*S,*O2,0);
            break;
        case 7:
            Element* C = new Element(6);
            Element* O1 = new Element(8);
            Element* O2= new Element(8);
            Element* O3 = new Element(8);

            newCompound=new Compound(*C);
            newCompound->addElement(*C,*O1,0);
            newCompound->addElement(*C,*O2,0);
            newCompound->addElement(*C,*O3,0);
            newCompound->createBond(*C,*O2,0);
            break;
        case 8:
            Element* C = new Element(6);
            Element* O1 = new Element(8);
            Element* O2= new Element(8);
            Element* O3 = new Element(8);
            Element* H = new Element(1);

            newCompound=new Compound(*C);
            newCompound->addElement(*C,*O1,0);
            newCompound->addElement(*C,*O2,0);
            newCompound->addElement(*C,*O3,0);
            newCompound->createBond(*C,*O2,0);     
            break;
        case 9:  
            Element* N = new Element(7);
            Element* O1 = new Element(8);
            Element* O2= new Element(8);
            Element* O3 = new Element(8);

            newCompound=new Compound(*N);
            newCompound->addElement(*N,*O1,0);
            newCompound->addElement(*N,*O2,0);
            newCompound->addElement(*N,*O3,0);
            newCompound->createBond(*N,*O2,0);
            break;
        case 10:
            Element* N = new Element(7);
            Element* O1 = new Element(8);
            Element* O2= new Element(8);

            newCompound=new Compound(*N);
            newCompound->addElement(*N,*O1,0);
            newCompound->addElement(*N,*O2,0);
            newCompound->createBond(*N,*O2,0);       
        case 11:
            Element* P = new Element(15);
            Element* O1 = new Element(8);
            Element* O2= new Element(8);
            Element* O3 = new Element(8);
            Element* O4= new Element(8);

            newCompound=new Compound(*P);
            newCompound->addElement(*P,*O1,0);
            newCompound->addElement(*P,*O2,0);
            newCompound->addElement(*P,*O3,0);
            newCompound->addElement(*P,*O4,0);
            newCompound->createBond(*P,*O4,0);           
        case 12:
            Element* P = new Element(15);
            Element* O1 = new Element(8);
            Element* O2= new Element(8);
            Element* O3 = new Element(8);


            newCompound=new Compound(*P);
            newCompound->addElement(*P,*O1,0);
            newCompound->addElement(*P,*O2,0);
            newCompound->addElement(*P,*O3,0);
            break;
        case 13:
            Element* O = new Element(8);
            Element* H = new Element(1);  
            newCompound=new Compound(*O);
            newCompound->addElement(*O,*H,0);            
            break;
        default:
            //error
            break;

    }
    return newCompound;
}

std::array<std::string,3> splitSaltName(std::string name){
    std::array<std::string,3> sections;
    int i =0;
    std::string space=" ";
    for(int j=0;j<3;j++){
        while(name[i] !=' '){
            sections[i]+=name[i];
            i++;
        }
        i++;
    }
    return sections;
}

//yoink
int value(char r)
{
    if (r == 'I')
        return 1;
    if (r == 'V')
        return 5;
    if (r == 'X')
        return 10;
    if (r == 'L')
        return 50;
    if (r == 'C')
        return 100;
    if (r == 'D')
        return 500;
    if (r == 'M')
        return 1000;
 
    return -1;
}
 
// Returns decimal value of
// roman numaral
int romanToDecimal(std::string& str)
{
    // Initialize result
    int res = 0;
 
    // Traverse given input
    for (int i = 0; i < str.length(); i++) 
    {
        // Getting value of symbol s[i]
        int s1 = value(str[i]);
 
        if (i + 1 < str.length()) 
        {
            // Getting value of symbol s[i+1]
            int s2 = value(str[i + 1]);
 
            // Comparing both values
            if (s1 >= s2) 
            {
                // Value of current symbol
                // is greater or equal to
                // the next symbol
                res = res + s1;
            }
            else
            {
                // Value of current symbol is
                // less than the next symbol
                res = res + s2 - s1;
                i++;
            }
        }
        else {
            res = res + s1;
        }
    }
    return res;
}
// 3 sections cation roman anion
//stock notation
Compound* makeSalt(std::string name){
    std::array<std::string,3> sections=splitSaltName(name);
    int n=romanToDecimal(sections[1]);

    Compound* anion= makeAnion(sections[2]);
    
}