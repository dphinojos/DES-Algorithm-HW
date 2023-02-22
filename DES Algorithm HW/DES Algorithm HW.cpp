// DES Algorithm HW.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "des.h"

std::string toBinary(std::string const& str) {
    std::string binary = "";
    for (char const& c: str) {
        binary += std::bitset<8>(c).to_string();
    }
    return binary;
} //Converts String to StringBit

int main()
{
    std::string key;
    std::string plainText;
    std::vector<int> keyOut;
    std::vector <int> key48;
    std::vector <int> plainTextOut;
    int temp = 0;
    DES encryption;

    //Key Preprocess

    //Enter Key
    std::cout << "Insert 8 character key" << std::endl;

    std::cin >> key;

    //Check for invalid input
    if (key.size() > 8) {
        std::cout << "Invalid Input: Key must be 8 characters." << std::endl;
        return -1;
    }
    
    //Store and Print Key in bit format
    std::cout << "Key: " << key << std::endl;
    std::cout << "Key in Bits:\n";

    key = toBinary(key);

    std::cout << key << "\n";

    //Bitstream into Vector
    for (int i = 0; i < key.size(); ++i) {
        temp = int(key.at(i)) - 48;
        keyOut.push_back(temp);
        //std::cout << keyOut.at(i);
    }
    std::cout << "\n";

    encryption.permitedChoiceOne(keyOut);
    
    std::cout << "Permitted Choice One:\n";
    //Print Permitted Choice One
    for (int i = 0; i < keyOut.size(); ++i) {
        std::cout << keyOut[i];
    }
    std::cout << "\n";

    

    //Round 1 - Left Shift
    std::cout << "Left Shift Process:\n";
    
    encryption.leftShift(1, keyOut);

    for (int i = 0; i < keyOut.size(); ++i) {
        std::cout << keyOut[i];
    }
    std::cout << "\n";

    //Permitted Choice 2
    std::cout << "Permitted Choice 2:\n";
    key48 = encryption.permitedChoiceTwo(keyOut);

    for (int i = 0; i < key48.size(); ++i) {
        std::cout << key48[i];
    }
    std::cout << "\n";



    //Text Preprocess

    //Enter Plain Text
    std::cout << "Enter Plain Text:" << std::endl;
    std::cin >> plainText;

    //Bitstream
    plainText = toBinary(plainText);

    //Bitstream into Vector
    for (int i = 0; i < plainText.size(); ++i) {
        temp = int(plainText.at(i)) - 48;
        plainTextOut.push_back(temp);
    }

    while (!(plainTextOut.size() % 64 == 0)) {
        plainTextOut.push_back(0);
    }

    //Print Complete 
    for (int i = 0; i < plainTextOut.size(); ++i) {
        std::cout << plainTextOut[i];
    }
    std::cout << "\n";

    //Initial Permutation
    std::cout << "Initial Permutation:\n";

    encryption.initialPermutation(plainTextOut);

    for (int i = 0; i < plainTextOut.size(); ++i) {
        std::cout << plainTextOut[i];
    }
    std::cout << "\n";

    for (int i = 0; i < (plainTextOut.size() / 64); ++i) {
        plainTextOut = encryption.rounds(keyOut, plainTextOut, i);
    }

    return 0;
}
