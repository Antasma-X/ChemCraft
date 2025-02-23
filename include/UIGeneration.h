#ifndef UIGENERATION_H
#define UIGENERATION_H

#include "StdLibDependencies.h"
#include "GUIDependencies.h"

#include"compound.h"

#include "config.h"
#include "values.h" 
#include "compoundRender.h"

namespace UI
{

    void SideMenu( ImFont* searchFontSmall, ImFont* searchFontLarge,ImFont* childWindowFontSmall, ImFont* childWindowFontLarge,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont,ImFont* compoundNameFont,ImFont* molecularFormulaFont);

    static void ElementAndCompoundMenu(ImFont* childWindowFontSmall, ImFont* childWindowFontLarge,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont,ImFont* compoundNameFont,ImFont* molecularFormulaFont,const std::vector<std::string>& currentSearchArray);

    static void GenerateElementButton(int atomicNumber, double sizeChange,ImFont* numberFont,ImFont* symbolFont,ImFont* nameFont,ImFont* massFont,bool isFirstBox);
    
    static void GenerateCompoundButton(int compoundNumber, double sizeChange,ImFont* compoundNameFont,ImFont* molecularFormulaFont,bool isFirstBox);

    static void SearchBar(ImFont* searchFontSmall, ImFont* searchFontLarge,std::vector<std::string>& currentSearchArray);

    static void LoadMagnifyingGlass(double searchBarHeightPerCent);

    static int FilterCharactersSearchBar(ImGuiInputTextCallbackData* data);

    void TopMenu();

    static int FilterLettersCompoundString(ImGuiInputTextCallbackData* data);
    
    static void open(std::string& fileName);

    static void save(std::string& fileName);

    static void saveAs(std::string& fileName);

    static void openHelpLink();
} 


#endif