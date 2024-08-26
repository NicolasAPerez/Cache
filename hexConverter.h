//
// Created by nicop on 12/4/2021.
//

#ifndef CACHE_HEXCONVERTER_H
#define CACHE_HEXCONVERTER_H

#include <iostream>

using std::string;

class hexConverter {
    public:
        static string hexToBinary(char val);
        static string hexAddrToBinary(string addr);
};


#endif //CACHE_HEXCONVERTER_H
