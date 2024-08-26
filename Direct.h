//
// Created by nicop on 12/5/2021.
//

#ifndef CACHE_DIRECT_H
#define CACHE_DIRECT_H
#include "Cache.h"

class Direct: public Cache{
    protected:
        unordered_map<string,std::pair<string,int>> setCache;


    public:
        Direct(int cSize, int bSize);
        bool accessMem(string address) override;

};


#endif //CACHE_DIRECT_H
