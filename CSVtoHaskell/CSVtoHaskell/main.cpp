//
//  main.cpp
//  CSVtoHaskell
//
//  Created by Hilton Pintor Bezerra Leite on 26/06/2018.
//  Copyright © 2018 Hilton Pintor Bezerra Leite. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Koan { theme="", intro="", code="", answer="" }
const string properties[4] = {"theme", "intro", "code", "answer"};

bool hasEvenQuotes(const string &word) {
    return (count(word.begin(), word.end(), '"') % 2) == 0;
}

string arrayToHaskell(string values[]) {
    string haskell = "Koan { ";
    
    for (int index = 0; index < 4; ++index) {
        string assign = values[index].substr(0, 1) == "\"" ? "=" : "=\"";
        string end = assign == "=" ? ", " : "\", ";
        
        if (index == 3) {
            if (end == "\", ") end = "\" ";
            else end = " ";
        }
        
        haskell = haskell + properties[index] + assign + values[index] + end;
    }
    
    return haskell + "}";
}

int main(int argc, const char * argv[]) {
    
    string line;
    ifstream csvFile ("koans.csv");
    
    ofstream haskellFile ("convertedKoans.hs");
    haskellFile << "equalityKoans = [" << endl;
    
    if (csvFile.is_open()) {
        int propertyIndex = 0;
        string propertyValues[4];
        stringstream iss;
        
        while (getline(csvFile, line)) {
            string value;
            iss.str(line);
            
            while (getline(iss, value, ',')) {
                bool evenQuotes = hasEvenQuotes(value);
                string accum = value;
                
                while (!evenQuotes)  {
                    getline(iss, value, ',');
                    accum = accum + "," + value;
                    evenQuotes = hasEvenQuotes(accum);
                }
                
                // Save accum
                if (propertyIndex < 4) {
                    propertyValues[propertyIndex] = accum;
                    
                    ++propertyIndex;
                    if (propertyIndex == 4) {
                        propertyValues[3].pop_back();
                        
                        propertyIndex = 0;

                        // TODO: write to file
                        haskellFile << "    " << arrayToHaskell(propertyValues) << "," << endl;
                    }
                }
            }
            iss.clear();
        }
        csvFile.close();
        
        haskellFile << "  ]" << endl;
        haskellFile.close();
    
    }else {
        cout << "Unable to open file" << endl;
    }
    
    return 0;
}
