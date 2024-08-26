//
// Created by nicop on 12/4/2021.
//

#include "hexConverter.h"

string hexConverter::hexToBinary(char val) {
    switch (val) {
        case '0':
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'a':
            return "1010";
        case 'b':
            return "1011";
        case 'c':
            return "1100";
        case 'd':
            return "1101";
        case 'e':
            return "1110";
        case 'f':
            return "1111";
        default:
            return "";
    }
}

string hexConverter::hexAddrToBinary(string addr) {
    string binary;
    for (char x : addr){
        binary += hexToBinary(x);
    }
    return binary;
}
