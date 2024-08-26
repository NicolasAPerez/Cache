//
// Created by nicop on 12/4/2021.
//

#include "FullyA.h"

FullyA::FullyA(int cSize, int bSize, bool FIFO) {
    cacheSize = cSize;
    blockSize = bSize;
    blocks = pow(2.0, cSize - bSize);
    sets = 1;
    this->FIFO = FIFO;
    accessAttempts = 0;
    accessHits = 0;
}

bool FullyA::accessMem(string address) {
    accessAttempts++;
    //Get Tag val
    string tag = hexConverter::hexAddrToBinary(address.substr(2));
    tag = tag.substr(0,(mainMem - blockSize));
    //See if tag has a hit
    if (cache.find(tag) != cache.end()){
        accessHits++;

        //If LRU then make it the most recently accessed
        if (!FIFO){
            cache[tag] = accessAttempts;
        }
        return true;
    }
    else{
        if (FIFO){
            //FIRST IN FIRST OUT
            if (cache.size() < blocks){
                cache[tag] = blocks - cache.size();
            }
            else{
                auto remove = cache.begin();
                for (auto iter = cache.begin(); iter != cache.end(); iter++){
                    if (iter->second == blocks){
                        remove = iter;
                    }
                    else{
                        iter->second++;
                    }
                }
                cache.erase(remove);
                cache[tag] = 1;
            }
        }

        else{
            //LEAST RECENTLY USED
            if (cache.size() < blocks){
                cache[tag] = accessAttempts;
            }
            else{
                auto remove = cache.begin();
                for (auto iter = cache.begin(); iter != cache.end(); iter++){
                    if (iter->second < remove->second){
                        remove = iter;
                    }
                }
                cache.erase(remove);
                cache[tag] = accessAttempts;
            }

        }
    }

    return false;
}
