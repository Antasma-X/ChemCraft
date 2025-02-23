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

std::map<std::string,std::string> molecules={
    {"water","1&1.000000&0/8&16.000000&0/1&1.000000&0/;1&0)/0&0)2&0)/1&0)/"},
    {"carbon dioxide","6&12.000000&0/8&16.000000&0/8&16.000000&0/;1&0)2&0)1&0)2&0)/0&0)0&0)/0&0)0&0)/"},
    {"carbon monoxide","6&12.000000&0/8&16.000000&0/;1&0)1&0)1&-2)/0&0)0&0)0&2)/"},
    {"hydrogen peroxide","1&1.000000&0/8&16.000000&0/8&16.000000&0/1&1.000000&0/;1&0)/0&0)2&0)/1&0)3&0)/2&0)/"},
    {"ozone","8&16.000000&-1/8&16.000000&1/8&16.000000&0/;1&0)/0&0)2&0)2&0)/1&0)1&0)/"},
    {"ammonia","7&14.000000&0/1&1.000000&0/1&1.000000&0/1&1.000000&0/;1&0)2&0)3&0)/0&0)/0&0)/0&0)/"},
    {"nitrogen dioxide", "7&14.000000&1/8&16.000000&-1/8&16.000000&0/;1&0)2&0)2&0)/0&0)/0&0)0&0)/"},
    {"benzene","6&12.000000&0/6&12.000000&0/6&12.000000&0/6&12.000000&0/6&12.000000&0/6&12.000000&0/1&1.000000&0/1&1.000000&0/1&1.000000&0/1&1.000000&0/1&1.000000&0/1&1.000000&0/;1&0)5&0)5&0)6&0)/0&0)2&0)2&0)7&0)/1&0)3&0)1&0)8&0)/2&0)4&0)4&0)9&0)/3&0)5&0)3&0)10&0)/4&0)0&0)0&0)11&0)/0&0)/1&0)/2&0)/3&0)/4&0)/5&0)/"},
    {"table salt","11&23.000000&0/17&35.500000&0/;1&1)/0&-1)/"},
    {"vinegar","6&12.000000&0/1&1.000000&0/1&1.000000&0/1&1.000000&0/6&12.000000&0/8&16.000000&0/8&16.000000&0/1&1.000000&0/;1&0)2&0)3&0)4&0)/0&0)/0&0)/0&0)/0&0)5&0)5&0)6&0)/4&0)4&0)/4&0)7&0)/6&0)/"},
    {"acetic acid","6&12.000000&0/1&1.000000&0/1&1.000000&0/1&1.000000&0/6&12.000000&0/8&16.000000&0/8&16.000000&0/1&1.000000&0/;1&0)2&0)3&0)4&0)/0&0)/0&0)/0&0)/0&0)5&0)5&0)6&0)/4&0)4&0)/4&0)7&0)/6&0)/"},
    {"baking soda","6&12.000000&0/8&16.000000&0/8&16.000000&0/1&1.000000&0/8&16.000000&0/11&23.000000&0/;1&0)1&0)2&0)4&0)/0&0)0&0)/0&0)3&0)/2&0)/0&0)5&-1)/4&1)/"},
    {"limestone","6&12.000000&0/8&16.000000&0/8&16.000000&0/8&16.000000&0/20&40.000000&0/;1&0)1&0)2&0)3&0)/0&0)0&0)/0&0)4&-1)/0&0)4&-1)/2&1)3&1)/"},
    {"bleach","17&35.500000&0/8&16.000000&0/11&23.000000&0/;1&0)/0&0)2&-1)/1&1)/"},
    {"washing soda","6&12.000000&0/8&16.000000&0/8&16.000000&0/8&16.000000&0/11&23.000000&0/11&23.000000&0/;1&0)1&0)2&0)3&0)/0&0)0&0)/0&0)4&-1)/0&0)5&-1)/2&1)/3&1)/"},
    {"alcohol","6&12.000000&0/1&1.000000&0/1&1.000000&0/1&1.000000&0/6&12.000000&0/1&1.000000&0/1&1.000000&0/8&16.000000&0/1&1.000000&0/;1&0)2&0)3&0)4&0)/0&0)/0&0)/0&0)/0&0)5&0)6&0)7&0)/4&0)/4&0)/4&0)8&0)/7&0)/"}

};

std::vector<std::string> compoundNumbers={"water", "carbon dioxide", "carbon monoxide", "hydrogen peroxide", "ozone", "ammonia", "nitrogen dioxide", "benzene", "table salt", "vinegar", "acetic acid", "baking soda", "limestone", "bleach", "washing soda", "alcohol"};

std::map<int,int> atomicity={
    {1,2},{7,2},{8,2},{9,2},{17,2},{35,2},{53,2},
    {15,4},
    {16,8}
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
std::vector<std::string> searchBar={

        "h", "he", "li", "be", "b", "c", "n", "o", "f", "ne", "na", "mg", "al", "si", "p", "s", "cl", "ar", "k", "ca", "sc", "ti", "v", "cr", "mn", "fe", "co", "ni", "cu", "zn", "ga", "ge", "as", "se", "br", "kr", "rb", "sr", "y", "zr", "nb", "mo", "tc", "ru", "rh", "pd", "ag",
        "cd", "in", "sn", "sb", "te", "i", "xe", "cs", "ba", "la", "ce", "pr", "nd", "pm", "sm", "eu", "gd", "tb", "dy", "ho", "er", "tm", "yb", "lu", "hf", "ta",
        "w", "re", "os", "ir", "pt", "au", "hg", "tl", "pb", "bi", "po", "at", "rn", "fr", "ra", "ac", "th", "pa", "u", "np", "pu", "am", "cm", "bk", "cf", "es",
        "fm", "md", "no", "lr", "rf", "db", "sg", "bh", "hs", "mt", "ds", "rg", "cn", "nh", "fl", "mc", "lv", "ts", "og",
    
        "hydrogen", "helium", "lithium", "beryllium", "boron", "carbon", "nitrogen", "oxygen", "fluorine", "neon", "sodium", "magnesium", "aluminum", "silicon", "phosphorus", "sulfur", "chlorine", "argon", "potassium", "calcium", "scandium",
        "titanium", "vanadium", "chromium", "manganese", "iron", "cobalt", "nickel", "copper", "zinc", "gallium", "germanium", "arsenic",
        "selenium", "bromine", "krypton", "rubidium", "strontium", "yttrium", "zirconium", "niobium", "molybdenum", "technetium", "ruthenium",
        "rhodium", "palladium", "silver", "cadmium", "indium", "tin", "antimony", "tellurium", "iodine", "xenon", "cesium", "barium", "lanthanum",
        "cerium", "praseodymium", "neodymium", "promethium", "samarium", "europium", "gadolinium", "terbium", "dysprosium", "holmium", "erbium",
        "thulium", "ytterbium", "lutetium", "hafnium", "tantalum", "tungsten", "rhenium", "osmium", "iridium", "platinum", "gold", "mercury", "thallium",
        "lead", "bismuth", "polonium", "astatine", "radon", "francium", "radium", "actinium", "thorium", "protactinium", "uranium", "neptunium", "plutonium",
        "americium", "curium", "berkelium", "californium", "einsteinium", "fermium", "mendelevium", "nobelium", "lawrencium", "rutherfordium", "dubnium", "seaborgium",
        "bohrium", "hassium", "meitnerium", "darmstadtium", "roentgenium", "copernicium", "nihonium", "flerovium", "moscovium", "livermorium", "tennessine", "oganesson",
    
        "water", "carbon dioxide", "carbon monoxide", "hydrogen peroxide", "ozone", "ammonia", "nitrogen dioxide", "benzene", "table salt", "acetic acid", "vinegar", "baking soda", "bleach", "limestone", "washing soda", "alcohol"    
//    ,"Fluoride", "Chloride", "Bromide", "Iodide", "Sulphate", "Sulphite", "Carbonate", "Bicarbonate", "Nitrate", "Nitrite", "Phosphate", "Phosphite", "Hydoxide",

//    "Ammonium", "Hydronium"


};