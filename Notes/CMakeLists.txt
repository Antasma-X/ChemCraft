cmake_minimum_required(VERSION 3.20)
project(Nomenclature)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_executable(cute )




// std::vector <GLfloat> Render::getVertices(std::vector <GLfloat> vertices, std::set<std::array<GLfloat,2>>& spawned,GLfloat width){
//     // const GLfloat marginOfError=0.01;

//     // //right
//     // for(auto val: spawned){
//     //     if(vertices[0]+(width*3)+marginOfError>=val[0] && vertices[0]+(width*3)-marginOfError<=val[0] && vertices[1]+marginOfError>=val[1]&&vertices[1]-marginOfError<=val[1]){
//     //         vertices[0]+=(width*3);
//     //     }
//     //     else{
//     //         break;
//     //     }
//     // }
    
// }
// // void Render::createElementObjects(Compound& comp,Element& el, std::vector<Element*> visited,std::vector <GLfloat> vertices,std::set<std::array<GLfloat,2>>& spawned){
// //     static std::vector<GLuint> indices={0,1,2,2,3,0};
// //     ImGuiIO& io = ImGui::GetIO(); (void)io;

// //     visited.emplace_back(&el);



// //     new ElementObject(vertices,indices,&el);

// //     std::vector<Element*> currentCovalentBonds=el.getCurrentCovalentBonds();
// //     std::vector<std::pair<Element*,int>> currentIonic=el.getCurrentIonicBonds();
// // 	std::vector<std::pair<Element*,int>> currentDative=el.getCurrentDativeBonds();

        
// //     int i=0;
// //     for(auto ele: currentCovalentBonds){
// //         if(std::find(visited.begin(),visited.end(),ele)==visited.end()){
// //             GLfloat width;
// //             visited.emplace_back(ele);

// //             if(ele->getSymbol().size()==1){
// //                 width=elementSingleTextureWidth;
// //             }
// //             else if(ele->getSymbol().size()==2){
// //                 width=elementDoubleTextureWidth;
// //             }
// //             else{
// //                 //error
                
// //             }
// //                 //first right then up then down then diagols then left

// //             vertices=getVertices(vertices,spawned,width);





// //             // //right
// //             // if(i==0){
// //             //     for(int i=0;i<4;i++){
// //             //         vertices[i*4]+=(width*3);
// //             //         //vertices[i*4]+=((width/io.DisplaySize.x )*2.5);
// //             //     }
// //             // }
// //             // //up
// //             // else if(i==1){
// //             //     for(int i=0;i<4;i++){
// //             //         vertices[1+i*4]+=(elementTextureHeight*3);
// //             //     }
// //             // }
// //             // //down
// //             // else if(i==2){
// //             //     for(int i=0;i<4;i++){
// //             //         vertices[1+i*4]-=(elementTextureHeight*3);
// //             //     }
// //             // }
// //             // //diagonal up right
// //             // else if(i==3){
// //             //     for(int i=0;i<4;i++){
// //             //         vertices[i*4]+=(width*3);
// //             //         vertices[1+i*4]+=(elementTextureHeight*3);
// //             //     }
// //             // }
// //             // //down right
// //             // else if(i==4){
// //             //     for(int i=0;i<4;i++){
// //             //         vertices[i*4]+=(width*3);
// //             //         vertices[1+i*4]-=(elementTextureHeight*3);
// //             //     }
// //             // }
// //             // //left down
// //             // else if(i==5){
// //             //     for(int i=0;i<4;i++){
// //             //         vertices[i*4]-=(width*3);
// //             //         vertices[1+i*4]-=(elementTextureHeight*3);
// //             //     }
// //             // }
// //             // //left up
// //             // else if(i==6){
// //             //     for(int i=0;i<4;i++){
// //             //         vertices[i*4]-=(width*3);
// //             //         vertices[1+i*4]+=(elementTextureHeight*3);
// //             //     }
// //             // }
// //             // //smth very wrong but left
// //             // else if(i==7){
// //             //     for(int i=0;i<4;i++){
// //             //         vertices[i*4]-=(width*3);

// //             //     }
// //             // }
// //             spawned.insert(vertices[0],vertices[1]);
// //             createElementObjects(comp,*ele,visited,vertices,spawned);
// //             i++;
// //         }
// //     }

// //     for(auto ele: currentIonic){
// //         if(std::find(visited.begin(),visited.end(),ele.first)==visited.end()){
// //             int width;
// //             visited.emplace_back(ele.first);

// //             if(ele.first->getSymbol().size()==1){
// //                 width=elementSingleTextureWidth;
// //             }
// //             else if(ele.first->getSymbol().size()==2){
// //                 width=elementDoubleTextureWidth;
// //             }
// //             else{
// //                 //error
                
// //             }
// //                 //first left then up then down then diagols then right
// //             //right
// //             if(i==0){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]+=(width*3);
// //                 }
// //             }
// //             //up
// //             else if(i==1){
// //                 for(int i=0;i<4;i++){
// //                     vertices[1+i*4]+=(elementTextureHeight*3);
// //                 }
// //             }
// //             //down
// //             else if(i==2){
// //                 for(int i=0;i<4;i++){
// //                     vertices[1+i*4]-=(elementTextureHeight*3);
// //                 }
// //             }
// //             //diagonal up right
// //             else if(i==3){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]+=(width*3);
// //                     vertices[1+i*4]+=(elementTextureHeight*3);
// //                 }
// //             }
// //             //down right
// //             else if(i==4){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]+=(width*3);
// //                     vertices[1+i*4]-=(elementTextureHeight*3);
// //                 }
// //             }
// //             //left down
// //             else if(i==5){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]-=(width*3);
// //                     vertices[1+i*4]-=(elementTextureHeight*3);
// //                 }
// //             }
// //             //left up
// //             else if(i==6){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]-=(width*3);
// //                     vertices[1+i*4]+=(elementTextureHeight*3);
// //                 }
// //             }
// //             //smth very wrong but left
// //             else if(i==7){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]-=(width*3);

// //                 }
// //             }
// //             createElementObjects(comp,*ele.first,visited,vertices,spawned);
// //             i++;
// //         }

// //     }
// //     for(auto ele: currentDative){
// //         if(std::find(visited.begin(),visited.end(),ele.first)==visited.end()){
// //             int width;
// //             visited.emplace_back(ele.first);

// //             if(ele.first->getSymbol().size()==1){
// //                 width=elementSingleTextureWidth;
// //             }
// //             else if(ele.first->getSymbol().size()==2){
// //                 width=elementDoubleTextureWidth;
// //             }
// //             else{
// //                 //error
                
// //             }
// //                 //first left then up then down then diagols then right
// //             //right
// //             if(i==0){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]+=(width*3);
// //                 }
// //             }
// //             //up
// //             else if(i==1){
// //                 for(int i=0;i<4;i++){
// //                     vertices[1+i*4]+=(elementTextureHeight*3);
// //                 }
// //             }
// //             //down
// //             else if(i==2){
// //                 for(int i=0;i<4;i++){
// //                     vertices[1+i*4]-=(elementTextureHeight*3);
// //                 }
// //             }
// //             //diagonal up right
// //             else if(i==3){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]+=(width*3);
// //                     vertices[1+i*4]+=(elementTextureHeight*3);
// //                 }
// //             }
// //             //down right
// //             else if(i==4){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]+=(width*3);
// //                     vertices[1+i*4]-=(elementTextureHeight*3);
// //                 }
// //             }
// //             //left down
// //             else if(i==5){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]-=(width*3);
// //                     vertices[1+i*4]-=(elementTextureHeight*3);
// //                 }
// //             }
// //             //left up
// //             else if(i==6){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]-=(width*3);
// //                     vertices[1+i*4]+=(elementTextureHeight*3);
// //                 }
// //             }
// //             //smth very wrong but left
// //             else if(i==7){
// //                 for(int i=0;i<4;i++){
// //                     vertices[i*4]-=(width*3);

// //                 }
// //             }
// //             createElementObjects(comp,*ele.first,visited,vertices,spawned);
// //         }
// //     }


    
// // }

// // void Render::createCompoundObject(Compound* compound){
    
// //     // ImGuiIO& io = ImGui::GetIO(); (void)io;
// //     // std::vector<GLuint> indices={0,1,2,2,3,0};
// //     // std::vector <GLfloat> vertices;
// //     // GLfloat width;

// //     // if(compound->getAtoms()[0]->getSymbol().size()==1){
// //     //     width=elementSingleTextureWidth;
// //     // }
// //     // else if(compound->getAtoms()[0]->getSymbol().size()==2){
// //     //     width=elementDoubleTextureWidth;
// //     // }
// //     // else{
// //     //     throw std::runtime_error("Atomic Symbol is Incorrect");
// //     // }
// //     // vertices={
// //     //     defaultSpawnLocation.x,defaultSpawnLocation.y ,0.0f,0.0f,
// //     //     defaultSpawnLocation.x+((width/io.DisplaySize.x )*2),defaultSpawnLocation.y ,1.0f,0.0f,
// //     //     defaultSpawnLocation.x+((width/io.DisplaySize.x )*2),defaultSpawnLocation.y +((elementTextureHeight/io.DisplaySize.y )*2)     ,1.0f,1.0f,
// //     //     defaultSpawnLocation.x,defaultSpawnLocation.y +((elementTextureHeight/io.DisplaySize.y )*2)     ,0.0f,1.0f,
// //     // };

// //     // //order has to be changed textire coords
// //     // vertices={
// //     //     defaultSpawnLocation.x,defaultSpawnLocation.y ,0.0f,0.0f,
// //     //     defaultSpawnLocation.x+(width),defaultSpawnLocation.y ,1.0f,0.0f,
// //     //     defaultSpawnLocation.x+(width),defaultSpawnLocation.y +(elementTextureHeight)     ,1.0f,1.0f,
// //     //     defaultSpawnLocation.x,defaultSpawnLocation.y +(elementTextureHeight)     ,0.0f,1.0f,
// //     // };
// //     // std::vector<Element*> visited;
// //     // std::set<std::array<GLfloat,2>> spawned={{defaultSpawnLocation.x,defaultSpawnLocation.y}};

// //     // createElementObjects(*compound,*compound->getAtoms()[0],visited,vertices,spawned);

// //     // //bonds
// //     // std::map<Element *, std::vector<std::pair<Element *, int>>> bonds=compound->getBonds();
// //     // for(auto [key,value]:bonds){

// //     // }

// //     // compoundList.push_back(compound);
// //     // glm::vec2 pos={100,200};
// //     // new ElementObject(pos,compound->getAtoms()[0]);
// //     // std::cout<<"hy"<<std::endl;

// //     //ElementObject::elementObjects[compound->getAtoms()[0]] = new ElementObject({0.0f, 0.0f}, compound->getAtoms()[0]);
// //     Render::compoundList.push_back(compound);
// //     new ElementObject({300.0f, 400.0f}, compound->getAtoms()[0]);
// //     // std::cout<<"ifhifhiwhfwihf"<<compound->getAtoms().size()<<std::endl;
// //     // if (!compound || compound->getAtoms().empty()) {
// //     //     error->Push("Invalid or empty compound in createElementObjectsFromCompound()");
// //     //     return;
// //     // }

// //     // std::set<Element*> visited;
// //     // std::unordered_map<Element*, glm::vec2> positions;

// //     // // Step 1: Layout atoms relative to (0,0)
// //     // glm::vec2 origin = glm::vec2(0.0f);
// //     // float spacing = elementTextureHeight * 1.5f;

// //     // std::vector<glm::vec2> directions = {
// //     //     {1, 0},   // right
// //     //     {0, 1},   // up
// //     //     {-1, 0},  // left
// //     //     {0, -1}   // down
// //     // };

// //     // std::queue<std::pair<Element*, glm::vec2>> q;
// //     // Element* root = compound->getAtoms()[0];
// //     // q.push({root, origin});
// //     // positions[root] = origin;

// //     // while (!q.empty()) {
// //     //     auto [current, pos] = q.front();
// //     //     q.pop();

// //     //     if (visited.count(current)) continue;
// //     //     visited.insert(current);

// //     //     const auto& neighbors = compound->getBonds()[current];
// //     //     int dirIndex = 0;

// //     //     for (const auto& [neighbor, bondType] : neighbors) {
// //     //         if (visited.count(neighbor)) continue;

// //     //         glm::vec2 offset = directions[dirIndex % directions.size()] * spacing;
// //     //         glm::vec2 neighborPos = pos + offset;

// //     //         if (positions.count(neighbor) == 0) {
// //     //             positions[neighbor] = neighborPos;
// //     //             q.push({neighbor, neighborPos});
// //     //         }

// //     //         dirIndex++;
// //     //     }
// //     // }

// //     // // Step 2: Compute bounding box of all positions
// //     // glm::vec2 minPos = positions.begin()->second;
// //     // glm::vec2 maxPos = positions.begin()->second;

// //     // for (const auto& [el, pos] : positions) {
// //     //     minPos = glm::min(minPos, pos);
// //     //     maxPos = glm::max(maxPos, pos);
// //     // }

// //     // glm::vec2 compoundCenter = (minPos + maxPos) * 0.5f;
// //     // glm::vec2 screenCenter = camera->GetCurrentPosition();
// //     // glm::vec2 shift = screenCenter - compoundCenter;

// //     // // Step 3: Create ElementObjects with shifted positions
// //     // for (const auto& [el, pos] : positions) {
// //     //     glm::vec2 finalPos = pos + shift;
// //     //     try {
// //     //         auto* obj = new ElementObject(finalPos, el);
// //     //         ElementObject::elementObjects[el] = obj;
// //     //     } catch (const std::exception& e) {
// //     //         error->Push("Failed to create ElementObject: " + std::string(e.what()));
// //     //     }
// //     // }
// // }



//     ImGuiIO& io = ImGui::GetIO(); (void)io;
    
//     // ImGuiIO& io = ImGui::GetIO(); (void)io;
//     // std::vector<GLuint> indices={0,1,2,2,3,0};
//     // std::vector <GLfloat> vertices;
//     // GLfloat width;

//     // if(compound->getAtoms()[0]->getSymbol().size()==1){
//     //     width=elementSingleTextureWidth;
//     // }
//     // else if(compound->getAtoms()[0]->getSymbol().size()==2){
//     //     width=elementDoubleTextureWidth;
//     // }
//     // else{
//     //     throw std::runtime_error("Atomic Symbol is Incorrect");
//     // }
//     // vertices={
//     //     defaultSpawnLocation.x,defaultSpawnLocation.y ,0.0f,0.0f,
//     //     defaultSpawnLocation.x+((width/io.DisplaySize.x )*2),defaultSpawnLocation.y ,1.0f,0.0f,
//     //     defaultSpawnLocation.x+((width/io.DisplaySize.x )*2),defaultSpawnLocation.y +((elementTextureHeight/io.DisplaySize.y )*2)     ,1.0f,1.0f,
//     //     defaultSpawnLocation.x,defaultSpawnLocation.y +((elementTextureHeight/io.DisplaySize.y )*2)     ,0.0f,1.0f,
//     // };

//     // //order has to be changed textire coords
//     // vertices={
//     //     defaultSpawnLocation.x,defaultSpawnLocation.y ,0.0f,0.0f,
//     //     defaultSpawnLocation.x+(width),defaultSpawnLocation.y ,1.0f,0.0f,
//     //     defaultSpawnLocation.x+(width),defaultSpawnLocation.y +(elementTextureHeight)     ,1.0f,1.0f,
//     //     defaultSpawnLocation.x,defaultSpawnLocation.y +(elementTextureHeight)     ,0.0f,1.0f,
//     // };
//     // std::vector<Element*> visited;
//     // std::set<std::array<GLfloat,2>> spawned={{defaultSpawnLocation.x,defaultSpawnLocation.y}};

//     // createElementObjects(*compound,*compound->getAtoms()[0],visited,vertices,spawned);

//     // //bonds
//     // std::map<Element *, std::vector<std::pair<Element *, int>>> bonds=compound->getBonds();
//     // for(auto [key,value]:bonds){

//     // }

//     // compoundList.push_back(compound);
//     // glm::vec2 pos={100,200};
//     // new ElementObject(pos,compound->getAtoms()[0]);
//     // std::cout<<"hy"<<std::endl;

//     //ElementObject::elementObjects[compound->getAtoms()[0]] = new ElementObject({0.0f, 0.0f}, compound->getAtoms()[0]);
    
//     // new ElementObject({300.0f, 400.0f}, compound->getAtoms()[0]);
//     // std::cout<<"ifhifhiwhfwihf"<<compound->getAtoms().size()<<std::endl;






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
