//
// Created by nicop on 12/4/2021.
//

#ifndef CACHE_FULLYA_H
#define CACHE_FULLYA_H


#include "Cache.h"

class FullyA: public Cache{
    protected:
        unordered_map<string,int> cache;
    public:
        FullyA(int cSize, int bSize, bool FIFO);
        bool accessMem(string address) override;

};

#endif //CACHE_FULLYA_H
