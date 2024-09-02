#include <vector>
#include <array>
#include <iostream>



std::vector<std::vector<int>> findCombinations(int n){
		std::vector<std::vector<int>> combs;


		for(int i=0;i<=n;i++){
            if (i<=n-i){
                continue;
            }
			combs.push_back({i,n-i});
		}
        return combs;
	}

int main(){

    std::vector<std::vector<int>> combs= findCombinations(7);
    for (int i = 0;i<combs.size();i++){
        std::cout<<combs[i][0]<<","<<combs[i][1]<<std::endl;
    }

}