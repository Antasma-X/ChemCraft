#include"molecules.h"




Compound* generateMoleculeOfElement(int atomicNumber){
    if(atomicity.find(atomicNumber) == atomicity.end()){
        return nullptr;
        // error
    }
    else{
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

// Compound* makeMolecule(std::string compoundString){
//     Compound* newCompound= new Compound(compoundString);
//     return newCompound;
// }










































// std::array<std::string,3> splitSaltName(std::string name){
//     std::string cation="";
//     std::string anion ="";
//     std::string stockString="";

//     auto it=name.begin();
//     for(;it!=name.end();it++){
//         if(*it=='(' ){
//             it++;
//             for(;*it!=')';it++){
//                 std::cout<<"skfjsijfsyoooooooooomaballs"<<std::endl;
//                 stockString+=*it;
//             }
//             it+=2;
//             break;
//         }
//         else if(*it==' '){
//             it++;
//             break;
//         }
//         cation+=*it;
//         std::cout<<"skfjsijfsyoooooooooo"<<std::endl;
//     }
//     for(;it!=name.end();it++){
//         anion+=*it;
//     }
//     std::cout<<cation<<stockString<<anion<<std::endl;
//     // while (true){}
//     std::array<std::string,3> arr={cation,stockString,anion};
//     return arr;
// }


// int romanToDecimal(std::string& s)
// {
//     std::unordered_map<char, int> roman = {
//         {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50},
//         {'C', 100}, {'D', 500}, {'M', 1000}
//     };
    
//     int total = 0;
//     int prevValue = 0;
    
//     for (int i = s.size() - 1; i >= 0; --i) {
//         int currValue = roman[s[i]];
        
//         if (currValue < prevValue) {
//             total -= currValue;
//         } else {
//             total += currValue;
//         }
//         prevValue = currValue;
//     }
    
//     return total;

// }
// Compound* makeSalt(std::string name){
//     std::vector<Compound*> cationArray;
//     std::vector<Compound*> anionArray;

//     std::array<std::string,3> sections=splitSaltName(name);
//     std::cout<<sections[0]<<"jdwu"<<sections[1]<<"jdwu"<<sections[2]<<"jdwu"<<std::endl;
//     int n;
//     std::cout<<sections[1]<<std::endl;
//     if(sections[1]==""){
//         n=0;
//     }
//     else{
//         n=romanToDecimal(sections[1]);
//     }
//     std::cout<<n<<std::endl;
//     int anionNumber=anions[sections[2]];
//     int anionValency=std::abs(anionValencies[sections[2]]);

//         int cationValency;
//     std::cout<<anionValencies[sections[2]]<<std::endl;

   
//     if(n==0){
//         cationValency=cationValencies[sections[0]];
//         std::cout<<cationValency<<std::endl;
//         int cationNumber=cations[sections[0]];
//         Compound* cationCompound;

//         for(int i=0;i<int(std::lcm(cationValency,anionValency)/cationValency);i++){
            
        
//         if(cationNumber==1){

//             Element* N=new Element(7,14,1);
//             Element* H1 = new Element(1);
//             Element* H2 = new Element(1);
//             Element* H3 = new Element(1);
//             Element* H4 = new Element(1);

//             cationCompound=new Compound(*N);
//             cationCompound->addElement(*N,*H1,0);
//             cationCompound->addElement(*N,*H2,0);
//             cationCompound->addElement(*N,*H3,0);
//             cationCompound->addElement(*N,*H4,0);
//         }
//         // else if(cationNumber==2){
//         //     Element* O=new Element(8,16,1);
//         //     Element* H1 = new Element(1);
//         //     Element* H2 = new Element(1);
//         //     Element* H3 = new Element(1);      

//         //     cationCompound=new Compound(*O);
//         //     cationCompound->addElement(*O,*H1,0);
//         //     cationCompound->addElement(*O,*H2,0);
//         //     cationCompound->addElement(*O,*H3,0);
                      
//         // }
//         else if(cationNumber>=3 && cationNumber<=14){
//             std::cout<<cationAtomicNumbers[sections[0]]<<std::endl;
//             cationCompound=new Compound(cationAtomicNumbers[sections[0]]);
//             std::cout<<"jcnsjdcbsjcbsjcbsjcbsblows"<<std::endl;
//         }
//         cationArray.emplace_back(cationCompound);
//     }
//     }
//     else{
//         int atomicNumber=transitionMetalAtomicNumbers[sections[0]];
//         cationValency=n;
//         std::cout<<n<<std::endl;
        
//         for(int i=0;i<int(std::lcm(cationValency,anionValency)/n);i++){
//             cationArray.emplace_back(new Compound(atomicNumber));
//         }

//     }
//     std::cout<<anionValency<<std::endl;
//     std::cout<<cationValency<<std::endl;
//     std::cout<<"hsdvujbgvjdvbdjvbdhvbdvbhdhvb"<<"       "<<int(std::lcm(cationValency,anionValency)/anionValency)<<std::endl;
//     for(int i=0;i<int(std::lcm(cationValency,anionValency)/anionValency);i++){
//         Compound* anionCompound;
//         if(anionNumber==1){
//             anionCompound=new Compound(9);
//         }
//         else if(anionNumber==2){
//             anionCompound=new Compound(17);
//         }
//         else if(anionNumber==3){
//             anionCompound=new Compound(35);
//         }
//         else if(anionNumber==4){
//             anionCompound=new Compound(53);
//         }
//         else if(anionNumber==5){
//             Element* S=new Element(16);
//             Element* O1=new Element(8);
//             Element* O2=new Element(8);
//             Element* O3=new Element(8);
//             Element* O4=new Element(8);
//             anionCompound=new Compound(*S);
//             anionCompound->addElement(*S,*O1,0);
//             anionCompound->addElement(*S,*O2,0);
//             anionCompound->addElement(*S,*O3,0);
//             anionCompound->addElement(*S,*O4,0);

//             anionCompound->createBond(*S,*O2,0);
//             anionCompound->createBond(*S,*O4,0);

//         }
//         else if(anionNumber==6){
//             Element* S=new Element(16);
//             Element* O1=new Element(8);
//             Element* O2=new Element(8);
//             Element* O3=new Element(8);

//             anionCompound=new Compound(*S);
//             anionCompound->addElement(*S,*O1,0);
//             anionCompound->addElement(*S,*O2,0);
//             anionCompound->addElement(*S,*O3,0);

//             anionCompound->createBond(*S,*O2,0);
//             anionCompound->createBond(*S,*O3,0);                
//         }
//         else if(anionNumber==7){
//                 Element* C=new Element(6);
//                 Element* O1= new Element(8);
//                 Element* O2= new Element(8);
//                 Element* O3= new Element(8);

//                 anionCompound=new Compound(*C);
//                 anionCompound->addElement(*C,*O1,0);
//                 anionCompound->addElement(*C,*O2,0);
//                 anionCompound->addElement(*C,*O3,0);
//                 anionCompound->createBond(*C,*O1,0);
//         }
//         else if(anionNumber==8){
//             Element* C=new Element(6);
//             Element* O1= new Element(8);
//             Element* O2= new Element(8);
//             Element* O3= new Element(8);
//             Element* H = new Element(1);

//             anionCompound=new Compound(*C);
//             anionCompound->addElement(*C,*O1,0);
//             anionCompound->addElement(*C,*O2,0);
//             anionCompound->addElement(*C,*O3,0);
//             anionCompound->createBond(*C,*O1,0);
//             anionCompound->addElement(*O2,*H,0);
//         }
//         else if(anionNumber==9){
//             Element* N= new Element(7);
//             Element* O1 = new Element(8);
//             Element* O2 = new Element(8);
//             Element* O3 = new Element(8);

//             anionCompound=new Compound(*N);
//             anionCompound->addElement(*N,*O1,0);
//             anionCompound->addElement(*N,*O2,0);
//             anionCompound->addElement(*N,*O3,-2);
//             anionCompound->createBond(*N,*O1,2);
//             //to be checkec
//         }
//         else if (anionNumber==10){
//             Element* N= new Element(7);
//             Element* O1 = new Element(8);
//             Element* O2 = new Element(8);


//             anionCompound=new Compound(*N);
//             anionCompound->addElement(*N,*O1,0);
//             anionCompound->addElement(*N,*O2,-2);
//             anionCompound->createBond(*N,*O1,2);             
//             //N has unstable   
//         }
//         else if(anionNumber==11){
//             Element* P=new Element(15);
//             Element* O1=new Element(8);
//             Element* O2=new Element(8);
//             Element* O3=new Element(8);
//             Element* O4=new Element(8);
//             anionCompound=new Compound(*P);
//             anionCompound->addElement(*P,*O1,0);
//             anionCompound->addElement(*P,*O2,0);
//             anionCompound->addElement(*P,*O3,0);
//             anionCompound->addElement(*P,*O4,0);
//             anionCompound->createBond(*P,*O2,0);
//         }
//         else if(anionNumber==12){
//             Element* P=new Element(15);
//             Element* O1=new Element(8);
//             Element* O2=new Element(8);
//             Element* O3=new Element(8);

//             anionCompound=new Compound(*P);
//             anionCompound->addElement(*P,*O1,0);
//             anionCompound->addElement(*P,*O2,0);
//             anionCompound->addElement(*P,*O3,0);

//         }
//         else if(anionNumber==13){
//             Element* O=new Element(8);
//             Element* H=new Element(1);

//             anionCompound=new Compound(*O);
//             anionCompound->addElement(*O,*H,0);
//         }
//         else if(anionNumber==14){
//             Element* O=new Element(8);
//             anionCompound=new Compound(*O);
//         }else{
//             //error
//         }
//         anionArray.emplace_back(anionCompound);

//     }
//     std::cout<<anionArray.size()<<std::endl;

//     std::vector<Element*> chargedAnions;
//     std::vector<Element*> chargedCations;

    
// std::cout<<"shgugugsugudg"<<std::endl;
//     auto it=cationArray.begin();
//     std::cout<<cationArray.size()<<std::endl;
//     std::cout<<"shgugugsugudg"<<std::endl;

//         std::cout<<anionArray.size()<<cationArray.size()<<std::endl;
//     // while (true){}
//     Compound* newCompound= new Compound(*anionArray[0]);
//     chargedCations=(*it)->getChargedCations();

//     std::cout<<chargedCations.size()<<std::endl;
//     std::cout<<"shgugugsugudg"<<std::endl;
//     auto it2=chargedCations.begin();
//     std::cout<<"fuck"<<std::endl;

//     for(auto anion: anionArray){
//         chargedAnions=anion->getChargedAnions();
//         std::cout<<"fuck"<<std::endl;
//         std::cout<<chargedAnions.size()<<std::endl;
//         std::cout<<chargedCations.size()<<"mwahhhh"<<std::endl;
//         // while(true) {}
//         for(auto chargedAnion: chargedAnions){

//             if(it2==chargedCations.end()){
//                 it++;
//                 std::cout<<"fuckher"<<std::endl;
//                 chargedCations=(*it)->getChargedCations();
//                 std::cout<<"fuckhim"<<std::endl;
//                 std::cout<<chargedCations.size()<<std::endl;

//                 it2=chargedCations.begin();
//             }
//             std::cout<<"fuckme"<<std::endl;
//             newCompound->addElement(*chargedAnion,**it2,**it,-1);
//             std::cout<<"fuckyou"<<std::endl;

//             if((((**it2).getValency()[0]==0 || (**it2).getValency()[1]==0) && (**it2).getAtomicNumber()<18)||(**it2).getAtomicNumber()>18 && ((**it2).getValency()[0]==cationValency || (**it2).getValency()[1]==cationValency)){
//                 it2++;
//             }
            
//         }

        

//     }
//     return newCompound;
// }