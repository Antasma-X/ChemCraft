#include "values.h"

std::vector<std::string> symbols={"H","He","Li","Be","B","C","N","O","F","Ne","Na","Mg","Al","Si","P","S","Cl","Ar","K","Ca","Sc"
,"Ti","V","Cr","Mn","Fe","Co","Ni","Cu","Zn","Ga","Ge","As","Se","Br","Kr","Rb","Sr","Y","Zr","Nb","Mo","Tc","Ru","Rh","Pd","Ag",
"Cd","In","Sn","Sb","Te","I","Xe","Cs","Ba","La","Ce","Pr","Nd","Pm","Sm","Eu","Gd","Tb","Dy","Ho","Er","Tm","Yb","Lu","Hf","Ta",
"W","Re","Os","Ir","Pt","Au","Hg","Tl","Pb","Bi","Po","At","Rn","Fr","Ra","Ac","Th","Pa","U","Np","Pu","Am","Cm","Bk","Cf","Es",
"Fm","Md","No","Lr","Rf","Db","Sg","Bh","Hs","Mt","Ds","Rg","Cn","Nh","Fl","Mc","Lv","Ts","Og"};

std::vector<std::string> names={"Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon", "Nitrogen", "Oxygen", "Fluorine",
 "Neon", "Sodium", "Magnesium", "Aluminum", "Silicon", "Phosphorus", "Sulfur", "Chlorine", "Argon", "Potassium", "Calcium", "Scandium",
  "Titanium", "Vanadium", "Chromium", "Manganese", "Iron", "Cobalt", "Nickel", "Copper", "Zinc", "Gallium", "Germanium", "Arsenic",
   "Selenium", "Bromine", "Krypton", "Rubidium", "Strontium", "Yttrium", "Zirconium", "Niobium", "Molybdenum", "Technetium", "Ruthenium", 
   "Rhodium", "Palladium", "Silver", "Cadmium", "Indium", "Tin", "Antimony", "Tellurium", "Iodine", "Xenon", "Cesium", "Barium", "Lanthanum", 
   "Cerium", "Praseodymium", "Neodymium", "Promethium", "Samarium", "Europium", "Gadolinium", "Terbium", "Dysprosium", "Holmium", "Erbium", 
   "Thulium", "Ytterbium", "Lutetium", "Hafnium", "Tantalum", "Tungsten", "Rhenium", "Osmium", "Iridium", "Platinum", "Gold", "Mercury", "Thallium", 
   "Lead", "Bismuth", "Polonium", "Astatine", "Radon", "Francium", "Radium", "Actinium", "Thorium", "Protactinium", "Uranium", "Neptunium", "Plutonium", 
   "Americium", "Curium", "Berkelium", "Californium", "Einsteinium", "Fermium", "Mendelevium", "Nobelium", "Lawrencium", "Rutherfordium", "Dubnium", "Seaborgium", 
   "Bohrium", "Hassium", "Meitnerium", "Darmstadtium", "Roentgenium", "Copernicium", "Nihonium", "Flerovium", "Moscovium", "Livermorium", "Tennessine", "Oganesson"};

//2 decimal places(I rounded some off because theyre small). Source: https://pubchem.ncbi.nlm.nih.gov/ptable/atomic-mass/
std::vector<double> masses={1,4,7,9.,10.81,12,14,16,19,20,23,24,27,28,31,32,35.5,40,39,40,44.95,47.87,50.94,52,54.94,55.84,58.93,58.69,63.55,65.4,69.72,72.63,74.92,78.97,79.9,
83.8,85.46,87.62,88.9,91.22,92.91,95.95,96.91,101.1,102.9,106.42,107.87,112.41,114.82,118.71,121.76,127.6,126.9,131.29,132.9,137.33,138.9,140.12,140.91,144.24,144.91,150.4,151.96,
157.2,158.92,162.5,164.93,167.26,168.93,173.05,174.97,178.49,180.95,183.84,186.21,190.2,192.22,195.08,196.97,200.59,204.38,207,208.98,208.98,209.99,222.02,223.02,226.02,227.03,232.04,
231.03,238.03,237.05,244.06,243.06,247.07,247.07,251.08,252.08,257.09,258.1,259.1,266.12,267.12,268.13,269.13,270.13,269.133,277.15,282.17,282.17,286.18,286.18,290.19,290.2,293.20,294.21,295.22};

std::vector<std::string> subShell = {"s","p","d","f","g","h","i"};

std::set<int> dBlockExceptions={24,29,41,42,44,45,46,47,78,79};
std::set<int> fBlockExceptions={57,58,64,89,90,91,92,93,96};

std::array<std::string,3> BONDSYMBOL={"-","=","\u2261"};

std::map<std::string,std::string> subScripts={{"0","₀"},{"1","₁"},{"2","₂"},{"3","₃"},{"4","₄"},{"5","₅"},{"6","₆"},{"7","₇"},{"8","₈"},{"9","₉"}};

std::map<std::string,std::string> superScripts = {{"0", "⁰"}, {"1", "¹"}, {"2", "²"}, {"3", "³"}, {"4", "⁴"},{"5", "⁵"}, {"6", "⁶"}, {"7", "⁷"}, {"8", "⁸"}, {"9", "⁹"},{"+", "⁺"}, {"-", "⁻"}};
 
std::map<int,int> atomicity={
    {1,2},{7,2},{8,2},{9,2},{17,2},{35,2},{53,2},
    {15,4},
    {16,8}
};

//i trust chatgpt with my life. this should be fact checked eventually
std::map<int,std::vector<int>> higherValencies={
    {19, {1}},                        // Potassium
    {20, {2}},                        // Calcium
    {21, {3}},                        // Scandium
    {22, {2, 3, 4}},                  // Titanium
    {23, {2, 3, 4, 5}},               // Vanadium
    {24, {2, 3, 6}},                  // Chromium
    {25, {2, 3, 4, 6, 7}},            // Manganese
    {26, {2, 3}},                     // Iron
    {27, {2, 3}},                     // Cobalt
    {28, {2, 3}},                     // Nickel
    {29, {1, 2}},                     // Copper
    {30, {2}},                        // Zinc
    {31, {3}},                        // Gallium
    {32, {2, 4}},                     // Germanium
    {33, {3, 5}},                     // Arsenic
    {34, {2, 4, 6}},                  // Selenium
    {36, {}},                         // Krypton (inert)
    {37, {1}},                        // Rubidium
    {38, {2}},                        // Strontium
    {39, {3}},                        // Yttrium
    {40, {4}},                        // Zirconium
    {41, {3, 5}},                     // Niobium
    {42, {2, 3, 4, 6}},               // Molybdenum
    {43, {4, 6, 7}},                  // Technetium
    {44, {2, 3, 4, 6, 8}},            // Ruthenium
    {45, {2, 3, 4, 6}},               // Rhodium
    {46, {2, 4}},                     // Palladium
    {47, {1}},                        // Silver
    {48, {2}},                        // Cadmium
    {49, {3}},                        // Indium
    {50, {2, 4}},                     // Tin
    {51, {3, 5}},                     // Antimony
    {52, {2, 4, 6}},                  // Tellurium
    {54, {}},                         // Xenon (inert)
    {55, {1}},                        // Cesium
    {56, {2}},                        // Barium
    {57, {3}},                        // Lanthanum
    {58, {3, 4}},                     // Cerium
    {59, {3}},                        // Praseodymium
    {60, {3}},                        // Neodymium
    {61, {3}},                        // Promethium
    {62, {3}},                        // Samarium
    {63, {2, 3}},                     // Europium
    {64, {3}},                        // Gadolinium
    {65, {3}},                        // Terbium
    {66, {3}},                        // Dysprosium
    {67, {3}},                        // Holmium
    {68, {3}},                        // Erbium
    {69, {3}},                        // Thulium
    {70, {2, 3}},                     // Ytterbium
    {71, {3}},                        // Lutetium
    {72, {4}},                        // Hafnium
    {73, {5}},                        // Tantalum
    {74, {2, 3, 4, 5, 6}},            // Tungsten
    {75, {4, 6, 7}},                  // Rhenium
    {76, {2, 3, 4, 6, 8}},            // Osmium
    {77, {2, 3, 4, 6}},               // Iridium
    {78, {2, 4}},                     // Platinum
    {79, {1, 3}},                     // Gold
    {80, {1, 2}},                     // Mercury
    {81, {1, 3}},                     // Thallium
    {82, {2, 4}},                     // Lead
    {83, {3, 5}},                     // Bismuth
    {84, {2, 4, 6}},                  // Polonium
    {86, {}},                         // Radon (inert)
    {87, {1}},                        // Francium
    {88, {2}},                        // Radium
    {89, {3}},                        // Actinium
    {90, {4}},                        // Thorium
    {91, {4, 5}},                     // Protactinium
    {92, {3, 4, 5, 6}},               // Uranium
    {93, {3, 4, 5, 6, 7}},            // Neptunium
    {94, {3, 4, 5, 6}},               // Plutonium
    {95, {3, 4, 5, 6}},               // Americium
    {96, {3}},                        // Curium
    {97, {3, 4}},                     // Berkelium
    {98, {3}},                        // Californium
    {99, {3}},                        // Einsteinium
    {100, {3}},                       // Fermium
    {101, {2, 3}},                    // Mendelevium
    {102, {2, 3}},                    // Nobelium
    {103, {3}},                       // Lawrencium
    {104, {4}},                       // Rutherfordium
    {105, {5}},                       // Dubnium
    {106, {6}},                       // Seaborgium
    {107, {7}},                       // Bohrium
    {108, {8}},                       // Hassium
    {109, {7}},                       // Meitnerium
    {110, {6}},                       // Darmstadtium
    {111, {5}},                       // Roentgenium
    {112, {2}},                       // Copernicium
    {113, {1, 3}},                    // Nihonium
    {114, {2, 4}},                    // Flerovium
    {115, {1, 3, 5}},                 // Moscovium
    {116, {2, 4, 6}},                 // Livermorium
    {118, {}},                        // Oganesson (inert)
};

std::map<std::string,int> anions={
   {"Fluoride",1},
   {"Chloride",2},
   {"Bromide",3},
   {"Iodide",4},
   {"Sulphate",5},
   {"Sulphite",6},
   {"Carbonate",7},
   {"Bicarbonate",8},
   {"Nitrate",9},
   {"Nitrite",10},
   {"Phosphate",11},
   {"Phosphite",12},
   {"Hydroxide",13},
   {"Oxide",14}
};

std::map<std::string,int> anionValencies={
    {"Fluoride",-1},
    {"Chloride",-1},
    {"Bromide",-1},
    {"Iodide",-1},
    {"Sulphate",-2},
    {"Sulphite",-2},
    {"Carbonate",-2},
    {"Bicarbonate",-1},
    {"Nitrate",-1},
    {"Nitrite",-1},
    {"Phosphate",-3},
    {"Phosphite",-3},
    {"Hydroxide",-1},
    {"Oxide",-2}
};

std::map<std::string,int> cations={
    {"Ammonium",1},
    {"Hydronium",2},
    {"Lithium", 3},  
    {"Sodium", 4},  
    {"Potassium", 5},  
    {"Rubidium", 6},  
    {"Cesium", 7},  
    {"Francium", 8},  
    {"Beryllium", 9},  
    {"Magnesium", 10},  
    {"Calcium", 11},  
    {"Strontium", 12},  
    {"Barium", 13},  
    {"Radium", 14}  
};

std::map<std::string,int> cationValencies={
    {"Ammonium",1},
    {"Hydronium",1},
    {"Lithium", 1},  
    {"Sodium", 1},  
    {"Potassium", 1},  
    {"Rubidium", 1},  
    {"Cesium", 1},  
    {"Francium", 1},  
    {"Beryllium", 2},  
    {"Magnesium", 2},  
    {"Calcium", 2},  
    {"Strontium", 2},  
    {"Barium", 2},  
    {"Radium", 2}  
};

std::map<std::string,int> cationAtomicNumbers={
    {"Lithium", 3},  
    {"Sodium", 11},  
    {"Potassium", 19},  
    {"Rubidium", 37},  
    {"Cesium", 55},  
    {"Francium", 87},  
    {"Beryllium", 4},  
    {"Magnesium", 12},  
    {"Calcium", 20},  
    {"Strontium", 38},  
    {"Barium", 56},  
    {"Radium", 88}  
};

std::map<std::string,int> transitionMetalAtomicNumbers={
    {"Scandium", 21},  
    {"Titanium", 22},  
    {"Vanadium", 23},  
    {"Chromium", 24},  
    {"Manganese", 25},  
    {"Iron", 26},  
    {"Cobalt", 27},  
    {"Nickel", 28},  
    {"Copper", 29},  
    {"Zinc", 30},  
    {"Yttrium", 39},  
    {"Zirconium", 40},  
    {"Niobium", 41},  
    {"Molybdenum", 42},  
    {"Technetium", 43},  
    {"Ruthenium", 44},  
    {"Rhodium", 45},  
    {"Palladium", 46},  
    {"Silver", 47},  
    {"Cadmium", 48},  
    {"Hafnium", 72},  
    {"Tantalum", 73},  
    {"Tungsten", 74},  
    {"Rhenium", 75},  
    {"Osmium", 76},  
    {"Iridium", 77},  
    {"Platinum", 78},  
    {"Gold", 79},  
    {"Mercury", 80},  
    {"Rutherfordium", 104},  
    {"Dubnium", 105},  
    {"Seaborgium", 106},  
    {"Bohrium", 107},  
    {"Hassium", 108}  

};
