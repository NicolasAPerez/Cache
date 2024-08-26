//
// Created by nicop on 12/5/2021.
//

#ifndef CACHE_SETS_H
#define CACHE_SETS_H
#include "Cache.h"

class Sets: public Cache{
    protected:
        std::unordered_map<string, std::unordered_map<string,int>> setCache;
    public:
        Sets(int cSize, int bSize, int numBLKPer, bool FIFO);
        bool accessMem(string address) override;

};


#endif //CACHE_SETS_H
