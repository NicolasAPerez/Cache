//
// Created by nicop on 12/5/2021.
//

#include "Direct.h"

Direct::Direct(int cSize, int bSize) {
    cacheSize = cSize;
    blockSize = bSize;
    blocks = 1;
    sets = pow(2.0, cSize - bSize);
    FIFO = false;
    accessAttempts = 0;
    accessHits = 0;

}

bool Direct::accessMem(string address) {
    accessAttempts++;
    //Get Tag and Line val
    string hex = hexConverter::hexAddrToBinary(address.substr(2));
    string tag = hex.substr(0,(mainMem - blockSize - (cacheSize - blockSize)));
    hex = hex.substr(tag.size());
    string line = hex.substr(0, (hex.size()-blockSize));
    //See if tag has a hit
    if (setCache[line].first == tag) {
        accessHits++;
        return true;
    }
    else{
        setCache[line] = std::make_pair(tag,0);
        return false;
    }
}
