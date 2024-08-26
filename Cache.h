//
// Created by nicop on 12/4/2021.
//

#ifndef CACHE_CACHE_H
#define CACHE_CACHE_H
#include <unordered_map>
#include <cmath>
#include "hexConverter.h"


using std::string;
using std::unordered_map;

//Class to function as the basis for the Cache types
class Cache{
    protected:
        //Attribute Variables

        //Size in Bytes
        static const int mainMem = 32; //2^32 bytes of main memory
        int cacheSize;
        int blockSize;
        //Number of blocks and sets in a cache
        int blocks;
        int sets;
        //Whether the Cache uses FIFO replacement (if True)
        //Otherwise use LRU
        bool FIFO;

        //Analysis Variables

        int accessAttempts;
        int accessHits;

    public:
        virtual bool accessMem(string address) = 0;

        double hitRate() const{
            return (double) accessHits/accessAttempts;
        }
};

#endif //CACHE_CACHE_H
