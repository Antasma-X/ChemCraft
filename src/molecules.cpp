#include"../include/molecules.h"


Compound* makeMolecule(std::string name){
    return makeMolecule(molecules[name]);
}

Compound* makeMolecule(int n){

    Compound* newCompound=nullptr;
    
    if(n==1){
        Element* H1=new Element(1);
        Element* H2=new Element(1);
        Element* O=new Element(8);

        newCompound=new Compound(*H1);
        newCompound->addElement(*H1,*O,0);
        newCompound->addElement(*O,*H2,0);
        
    }
    else if(n==2){
        Element* O1=new Element(8);
        Element* O2=new Element(8);
        Element* C=new Element(6);            

        newCompound=new Compound(*C);
        newCompound->addElement(*C,*O1,0);
        newCompound->addElement(*C,*O2,0);
    }
    else if(n==3){
        Element* O=new Element(8);
        Element* C=new Element(6);            

        newCompound=new Compound(*C);
        newCompound->addElement(*C,*O,0);
    } 
    else if(n==4){
        Element* H1=new Element(1);
        Element* H2=new Element(1);
        Element* O1=new Element(8);
        Element* O2=new Element(8);

        newCompound=new Compound(*H1);
        newCompound->addElement(*H1,*O1,0);
        newCompound->addElement(*O1,*O2,0);
        newCompound->addElement(*O2,*H2,0);
    }
    else if(n==5){
        Element* O1=new Element(8);
        Element* O2=new Element(8);
        Element* O3=new Element(8);

        newCompound=new Compound(*O1);
        newCompound->addElement(*O1,*O2,0);
        newCompound->addElement(*O2,*O3,0);
        newCompound->createBond(*O1,*O3,0);
    }
    else if(n==6){
        Element* N=new Element(7);
        Element* H1=new Element(1);
        Element* H2=new Element(1);
        Element* H3=new Element(1);

        newCompound=new Compound(*N);
        newCompound->addElement(*N,*H1,0);
        newCompound->addElement(*N,*H2,0);
        newCompound->addElement(*N,*H3,0);
    }
    else if(n==7){
        Element* N=new Element(7);
        Element* O1=new Element(8);
        Element* O2=new Element(8);

        newCompound=new Compound(*N);
        newCompound->addElement(*N,*O1,0);
        newCompound->addElement(*N,*O2,0);
        newCompound->createBond(*N,*O1,0);         
    }
    else if(n==8){
        Element* C1=new Element(6);
        Element* C2=new Element(6);
        Element* C3=new Element(6);
        Element* C4=new Element(6);
        Element* C5=new Element(6);
        Element* C6=new Element(6);

        Element* H1=new Element(1);
        Element* H2=new Element(1);
        Element* H3=new Element(1);
        Element* H4=new Element(1);
        Element* H5=new Element(1);
        Element* H6=new Element(1);

        newCompound=new Compound(*C1);
        newCompound->addElement(*C1,*C2,0);
        newCompound->addElement(*C2,*C3,0);
        newCompound->addElement(*C3,*C4,0);
        newCompound->addElement(*C4,*C5,0);
        newCompound->addElement(*C5,*C6,0);

        newCompound->createBond(*C2,*C3,0);
        newCompound->createBond(*C4,*C5,0);
        newCompound->createBond(*C6,*C1,0);

        newCompound->addElement(*C1,*H1,0);
        newCompound->addElement(*C2,*H2,0);
        newCompound->addElement(*C3,*H3,0);
        newCompound->addElement(*C4,*H4,0);
        newCompound->addElement(*C5,*H5,0);
        newCompound->addElement(*C6,*H6,0);
    }
    else{
        
    }
    return newCompound;
    
}

Compound* generateMoleculeOfElement(int atomicNumber){
    if(atomicity.find(atomicNumber) == atomicity.end()){
        return nullptr;
        // error
    }else{
        std::vector<Element*> elements;
        
        for(int i=0;i<atomicity[atomicNumber];i++){
            elements.emplace_back(new Element(atomicNumber));
        }
        Compound* newCompound=new Compound(*elements[0]);

        for(std::size_t i=1;i<elements.size();i++){
            newCompound->addElement(*elements[i-1],*elements[i],0);
        }
        newCompound->createBond(*elements[0],*elements[elements.size()-1],0);
        return newCompound;
    }
}

std::pair<Compound*,std::vector<std::pair<Element*,int>>> makeAnion(std::string name){
    return makeAnion(anions[name]);
}

std::pair<Compound*,std::vector<std::pair<Element*,int>>> makeAnion(int n){
    Compound* newCompound=nullptr;
    std::vector<Element*> elements;
    std::vector<int> valencies;
    
    if(n==1){
        Element* F= new Element(9);

        elements.emplace_back(F);
        valencies.emplace_back(-1);

        newCompound= new Compound(*F);
    }
    else if(n==2){
        Element* Cl= new Element(17);

        elements.emplace_back(Cl);
        valencies.emplace_back(-1);

        newCompound= new Compound(*Cl);
    }
    else if(n==3){
        Element* Br= new Element(35);

        elements.emplace_back(Br);
        valencies.emplace_back(-1);

        newCompound= new Compound(*Br);
    }
    else if(n==4){
        Element* I= new Element(53);

        elements.emplace_back(I);
        valencies.emplace_back(-1);

        newCompound= new Compound(*I);
    }
    else if(n==5){
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

        elements.emplace_back(O1);
        valencies.emplace_back(-1);

        elements.emplace_back(O3);
        valencies.emplace_back(-1);
    }
    else if(n==6){
        Element* S = new Element(16);
        Element* O1 = new Element(8);
        Element* O2= new Element(8);
        Element* O3 = new Element(8);

        newCompound=new Compound(*S);
        newCompound->addElement(*S,*O1,0);
        newCompound->addElement(*S,*O2,0);
        newCompound->addElement(*S,*O3,0);

        newCompound->createBond(*S,*O2,0);

        elements.emplace_back(O1);
        valencies.emplace_back(-1);

        elements.emplace_back(O3);
        valencies.emplace_back(-1);
        
    }
    else if(n==7){
        Element* C = new Element(6);
        Element* O1 = new Element(8);
        Element* O2= new Element(8);
        Element* O3 = new Element(8);

        newCompound=new Compound(*C);
        newCompound->addElement(*C,*O1,0);
        newCompound->addElement(*C,*O2,0);
        newCompound->addElement(*C,*O3,0);
        newCompound->createBond(*C,*O2,0);

        elements.emplace_back(O1);
        valencies.emplace_back(-1);

        elements.emplace_back(O3);
        valencies.emplace_back(-1);
    }
    else if(n==8){
        Element* C = new Element(6);
        Element* O1 = new Element(8);
        Element* O2= new Element(8);
        Element* O3 = new Element(8);
        Element* H = new Element(1);

        newCompound=new Compound(*C);
        newCompound->addElement(*C,*O1,0);
        newCompound->addElement(*C,*O2,0);
        newCompound->addElement(*C,*O3,0);
        newCompound->addElement(*O1,*H,0);
        newCompound->createBond(*C,*O2,0);     

        elements.emplace_back(O3);
        valencies.emplace_back(-1);
    }
    else if(n==9){
        Element* N = new Element(7);
        Element* O1 = new Element(8);
        Element* O2= new Element(8);
        Element* O3 = new Element(8);

        newCompound=new Compound(*N);
        newCompound->addElement(*N,*O1,0);
        newCompound->addElement(*N,*O2,0);
        newCompound->addElement(*N,*O3,0);
        newCompound->createBond(*N,*O2,0);

        elements.emplace_back(O3);
        valencies.emplace_back(-1);
    }
    else if(n==10){
        Element* N = new Element(7);
        Element* O1 = new Element(8);
        Element* O2= new Element(8);

        newCompound=new Compound(*N);
        newCompound->addElement(*N,*O1,0);
        newCompound->addElement(*N,*O2,0);
        newCompound->createBond(*N,*O2,0);       

        elements.emplace_back(O1);
        valencies.emplace_back(-1);
    }
    else if(n==11){
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

        elements.emplace_back(O1);
        valencies.emplace_back(-1);

        elements.emplace_back(O2);
        valencies.emplace_back(-1);

        elements.emplace_back(O3);
        valencies.emplace_back(-1);
    }
    else if(n==12){
        Element* P = new Element(15);
        Element* O1 = new Element(8);
        Element* O2= new Element(8);
        Element* O3 = new Element(8);


        newCompound=new Compound(*P);
        newCompound->addElement(*P,*O1,0);
        newCompound->addElement(*P,*O2,0);
        newCompound->addElement(*P,*O3,0);

        elements.emplace_back(O1);
        valencies.emplace_back(-1);

        elements.emplace_back(O2);
        valencies.emplace_back(-1);

        elements.emplace_back(O3);
        valencies.emplace_back(-1);
    }
    else if(n==13){
        Element* O = new Element(8);
        Element* H = new Element(1);  
        newCompound=new Compound(*O);
        newCompound->addElement(*O,*H,0);         

        elements.emplace_back(O);
        valencies.emplace_back(-1);
    }
    else{
        //error
    }


    
    std::pair<Compound*,std::vector<std::pair<Element*,int>>> info;
    info.first=newCompound;

    for(std::size_t i=0;i<elements.size();i++){
        info.second[i]=std::make_pair(elements[i],valencies[i]);
    }
    
    return info;
}

std::pair<Compound*,std::vector<std::pair<Element*,int>>> makeCation(std::string name,int valency){

    auto it=std::find(names.begin(),names.end(),name);
    int n;
    if(it==names.end()){
        auto i=cations.find(name);
        if(i == cations.end()){
            n=0;

        }
        else{
            n=std::distance(cations.begin(),i)+1;
        }
    }
    else{
        n=std::distance(names.begin(),it)+1;

    }
    return makeCation(n,valency);
}

std::pair<Compound*,std::vector<std::pair<Element*,int>>> makeCation(int n,int valency){
    Compound* newCompound=nullptr;
    std::vector<Element*> elements;
    std::vector<int> valencies;

    if(n>=1 && n<=118){
        Element* element1=new Element(n);
        newCompound=new Compound(*element1);

        elements.emplace_back(element1);
        valencies.emplace_back(valency);
    }
    else{
        // switch(n){
        //     case 200:
        //         //ammonium
        //     case 201:
        //     //hydronium
        // }
    }
        std::pair<Compound*,std::vector<std::pair<Element*,int>>> info;
    info.first=newCompound;

    for(size_t i=0;i<elements.size();i++){
        info.second[i]=std::make_pair(elements[i],valencies[i]);
    }

    
    return info;
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
 
int romanToDecimal(std::string& str)
{
    // Initialize result
    int res = 0;
 
    // Traverse given input
    for (size_t i = 0; i < str.size(); i++) 
    {
        // Getting value of symbol s[i]
        int s1 = value(str[i]);
 
        if (i + 1 < str.size()) 
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


Compound* makeSalt(std::string name){
    std::array<std::string,3> sections=splitSaltName(name);
    int n=romanToDecimal(sections[1]);

    std::pair<Compound*,std::vector<std::pair<Element*,int>>> anion= makeAnion(sections[2]);
    std::pair<Compound*,std::vector<std::pair<Element*,int>>> cation=makeCation(sections[0],n);

    int totalAnionValency=0;
    int totalCationValency=0;

    for(auto el:anion.second){
        totalAnionValency+=el.second;
    }

    for(auto el:cation.second){
        totalCationValency+=el.second;
    }

    int lcm=std::lcm(abs(totalAnionValency),totalCationValency);

    std::vector<std::pair<Compound*,std::vector<std::pair<Element*,int>>>> anions={anion};
    std::vector<std::pair<Compound*,std::vector<std::pair<Element*,int>>>> cations={cation};

    for(int i=0;i<(lcm/totalCationValency)-1;i++){
        cations.emplace_back(makeCation(sections[0],n));
    }

    for(int i=0;i<(lcm/abs(totalAnionValency))-1;i++){
        anions.emplace_back(makeAnion(sections[0]));
    }


    //code is built on hopes and prayers
    int i=0;
    int j=0;
    size_t k=0;

    for(auto anion:anions){
        for(int l=0;l<abs(totalAnionValency);i++){
            if(anion.second[i].second !=0){
                
                anion.second[i].second++;
                cations[j].second[k].second--;
                anion.first->addElement(*anion.second[i].first,*cations[j].second[k].first,*cations[j].first,-1);

                while (true){
                    if(cations[j].second[k].second==0){
                        if(cations[j].second.size()==k-1){
                            j++;
                            k=0;
                        }
                        else{
                            k++;
                        }
                    }
                    else{
                        break;
                    }
                }
            }
            else{
                i++;
            }
        }
    }

    return anion.first;
}