// DES Algorithm HW.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include "des.h"

int main()
{
    std::string key;
    std::string plainText;
    std::vector<int> keyOut;
    std::vector <int> key48;
    std::vector <int> plainTextOut;
    std::vector <int> tempVector;
    std::vector <int> output;
    int temp = 0;
    DES encryption;

    //Key Preprocess

    //Enter Key
    std::cout << "Insert Key String" << std::endl;

    std::cin >> key;

    //Check for invalid input
    /*if (key.size() > 8) {
        std::cout << "Invalid Input: Key must be 8 characters." << std::endl;
        return -1;
    }*/
    
    //Store and Print Key in bit format
    std::cout << "Key: \n" << key << std::endl;
    std::cout << "Hashing:\n";

    key = encryption.berstein_hash(key);

    //Hash
    
    for (int i = 0; i < key.size(); ++i) {
        std::cout << key[i];
    }
    std::cout << "\n";
    
    std::cout << "To Binary:\n";
    key = encryption.toBinary(key);
    for (int i = 0; i < key.size(); ++i) {
        std::cout << key[i];
    }
    std::cout << "\n";


    //Bitstream into Vector
    for (int i = 0; i < key.size(); ++i) {
        temp = int(key.at(i)) - 48;
        keyOut.push_back(temp);
        //std::cout << keyOut.at(i);
    }
    std::cout << "\n";


    //std::cout << "Permitted Choice One:\n";
    //encryption.permitedChoiceOne(keyOut);
    ////Print Permitted Choice One
    //for (int i = 0; i < keyOut.size(); ++i) {
    //    std::cout << keyOut[i];
    //}
    //std::cout << "\n";

    

    ////Round 1 - Left Shift
    //std::cout << "Left Shift Process:\n";
    //
    //encryption.leftShift(1, keyOut);

    //for (int i = 0; i < keyOut.size(); ++i) {
    //    std::cout << keyOut[i];
    //}
    //std::cout << "\n";

    ////Permitted Choice 2
    //std::cout << "Permitted Choice 2:\n";
    //key48 = encryption.permitedChoiceTwo(keyOut);

    //for (int i = 0; i < key48.size(); ++i) {
    //    std::cout << key48[i];
    //}
    //std::cout << "\n";



    //Text Preprocess

    //Enter Plain Text
    std::cout << "Enter Plain Text:" << std::endl;
    std::cin >> plainText;

    //Bitstream
    plainText = encryption.toBinary(plainText);

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

    for (int k = 1; k <= 16; ++k) {
        for (int i = 0; i < (plainTextOut.size() / 64); ++i) {
            tempVector = encryption.rounds(keyOut, plainTextOut, i, k); //Round Function
            std::cout << "Block " << i + 1 << " Complete\n";
            for (int j = 0; j < tempVector.size(); ++j) {
                output.push_back(tempVector[j]); //Output of round into seperate vector 
                                                 //For the multiple 64 bit blocks
            }
        }
        //Update Plaintext and clear output
        std::cout << "Round " << k << " Complete\n";
        plainTextOut = output;
        output.clear();
    }

    std::cout << "Encrypted:\n";
    //print
    for (int i = 0; i < plainTextOut.size(); ++i) {
        std::cout << plainTextOut[i];
    }
    std::cout << "\n";

    return 0;
}
