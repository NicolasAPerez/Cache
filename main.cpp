#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "FullyA.h"
#include "Direct.h"
#include "Sets.h"

using namespace std;

int main() {
    string fileName;
    fstream file;
    int numSets;
    int numBlocks;
    int blockSize;
    bool menuOption;
    bool FIFO;
    unordered_map<string, bool> cDesigns({{"FA",false},{"Dir", false},{"Sets", false}});
    unordered_map<string, double> hitRates;
    vector<string> addrList;

    cout << "CACHE SIMULATOR" << endl;
    do {
        cout << "Insert File Name: ";
        cin >> fileName;
        cout << endl;
        file.open(fileName + ".trace");
        if (!file.is_open()){
            cout << "ERROR: INVALID FILE" << endl;
        }
    } while (!file.is_open());
    cout << "File opened Succesfully!" << endl;
    string line;

    while (getline(file, line)){
        istringstream inSS(line);
        string temp;
        inSS >> temp;
        inSS >> temp;
        addrList.push_back(temp);
        inSS >> temp;
    }
    file.close();
    while (true) {
        cout << "Cache Creation: " << endl << "(NOTE: All answers are the exponent of 2^x)" << endl;
        cout << "# of Sets in a Cache? ";
        cin >> numSets;
        cout << endl;
        cout << "# of Blocks in a Set? ";
        cin >> numBlocks;
        cout << endl;
        cout << "Size of the Blocks? ";
        cin >> blockSize;
        cout << endl;
        cout << "Generating Approriate Cache..." << endl;

        if (numSets == 0 && !cDesigns["FA"]) {
            FullyA cMemoryUnitFA(numBlocks + blockSize, blockSize, true);
            FullyA cMemoryUnitFA2(numBlocks + blockSize, blockSize, false);

            cout << "Fully Associative Cache Created!" << endl;
            cDesigns["FA"] = true;
            for (string addr: addrList) {
                cMemoryUnitFA.accessMem(addr);
                cMemoryUnitFA2.accessMem(addr);
            }
            cout << "FIFO Hit Rate was: " << cMemoryUnitFA.hitRate() << endl;
            cout << "LRU Hit Rate was: " << cMemoryUnitFA2.hitRate() << endl;

            hitRates["FA FIFO"] = cMemoryUnitFA.hitRate();
            hitRates["FA LRU"] = cMemoryUnitFA2.hitRate();
        }

        else if (numBlocks == 0 && !cDesigns["Dir"]){
            Direct cMemoryUnitDir(numBlocks + blockSize + numSets, blockSize);
            cout << "Directly Mapped Cache Created!" << endl;
            cDesigns["Dir"] = true;
            for (string addr: addrList) {
                cMemoryUnitDir.accessMem(addr);
            }
            cout << "Hit Rate was: " << cMemoryUnitDir.hitRate() << endl;
            hitRates["Direct"] = cMemoryUnitDir.hitRate();
        }
        else if (!cDesigns["Sets"]){
            Sets cMemoryUnitSets(numBlocks + blockSize + numSets, blockSize, numBlocks, true);
            Sets cMemoryUnitSets2(numBlocks + blockSize + numSets, blockSize, numBlocks, false);

            cDesigns["Sets"] = true;
            cout << "Set Associative Cache Created!" << endl;
            for (string addr: addrList) {
                cMemoryUnitSets.accessMem(addr);
                cMemoryUnitSets2.accessMem(addr);
            }
            cout << "FIFO Hit Rate was: " << cMemoryUnitSets.hitRate() << endl;
            cout << "LRU Hit Rate was: " << cMemoryUnitSets2.hitRate() << endl;

            hitRates["Sets FIFO"] = cMemoryUnitSets.hitRate();
            hitRates["Sets LRU"] = cMemoryUnitSets2.hitRate();
        }
        if (cDesigns["FA"] && cDesigns["Dir"] && cDesigns["Sets"]){
            break;
        }
    }
    cout << "All three Cache Designs Created!" << endl;
    cout << "All Hit Rate Results:" << endl;
    for (auto iter = hitRates.begin(); iter != hitRates.end(); iter++){
        cout << iter->first << ": " << iter->second << endl;
    }



}
