//
// Created by nicop on 12/5/2021.
//

#include "Sets.h"

Sets::Sets(int cSize, int bSize, int numBLKPer, bool FIFO) {
    cacheSize = cSize;
    blockSize = bSize;
    blocks = pow(2.0, numBLKPer);
    sets = pow(2.0, cSize - bSize - numBLKPer);
    this->FIFO = FIFO;
    accessAttempts = 0;
    accessHits = 0;

}

bool Sets::accessMem(string address) {
    accessAttempts++;
    //Get Tag and Line val
    string hex = hexConverter::hexAddrToBinary(address.substr(2));
    string tag = hex.substr(0, (mainMem - blockSize - (cacheSize - blockSize - (int)log2(blocks))));
    hex = hex.substr(tag.size());
    string line = hex.substr(0, (hex.size() - blockSize));
    //See if tag has a hit
    if (setCache[line].find(tag) != setCache[line].end()) {
        accessHits++;

        if (!FIFO) {
            setCache[line][tag] = accessAttempts;
        }
        return true;
    }
    else {
        if (FIFO) {
            //FIRST IN FIRST OUT
            if (setCache[line].size() < blocks) {
                setCache[line][tag] = blocks - setCache[line].size();
            }
            else {
                auto remove = setCache[line].begin();
                for (auto iter = setCache[line].begin(); iter != setCache[line].end(); iter++) {
                    if (iter->second == blocks) {
                        remove = iter;
                    }
                    else {
                        iter->second++;
                    }
                }
                setCache[line].erase(remove);
                setCache[line][tag] = 1;
            }
        }

        else {
            //LEAST RECENTLY USED
            if (setCache[line].size() < blocks) {
                setCache[line][tag] = accessAttempts;
            }
            else {
                auto remove = setCache[line].begin();
                for (auto iter = setCache[line].begin(); iter != setCache[line].end(); iter++) {
                    if (iter->second < remove->second) {
                        remove = iter;
                    }
                }
                setCache[line].erase(remove);
                setCache[line][tag] = accessAttempts;
            }

        }

    }
}