#include <vector>
#include <array>
#include <iostream>
#include "../include/element.h"

std::vector<std::array<int,2>> findCombinations(int n){
	std::vector<std::array<int,2>> combs;


	for(int i=0;i<=n;i++){
		if (i<=n-i){
			continue;
		}
		combs.push_back({i,n-i});
	}
	return combs;
}

int main() {




	auto i=findCombinations(1);
	for(auto it = i.begin();it !=i.end();it++)
	std::cout<<(*it)[0]<<","<<(*it)[1]<<std::endl;

	std::cout << "Hi" << std::endl;

	Element carbon(6);
	//carbon%oxygen;

	carbon.printShells();
	carbon.getNumberOfBonds();
	std::cout << carbon.getName() << std::endl;

}