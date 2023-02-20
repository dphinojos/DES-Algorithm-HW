#include "des.h"

void DES::permitedChoiceOne(std::vector<int>& input) {
	std::vector<int> tempVector = input;

	for (int i = 0; i < input.size(); ++i) {
		input[i] = tempVector[pcOne[i] - 1];
	}
	
	input.erase(input.begin() + 63); //64
	input.erase(input.begin() + 55); //56
	input.erase(input.begin() + 47); //48
	input.erase(input.begin() + 39); //40
	input.erase(input.begin() + 31); //32
	input.erase(input.begin() + 23); //24
	input.erase(input.begin() + 15); //16
	input.erase(input.begin() + 7);  //8

}

std::vector<int> DES::permitedChoiceTwo(std::vector<int> input) {
	std::vector<int> out48;

	for (int i = 0; i < 48; ++i) {
		out48.push_back(input[pcTwo[i] - 1]);
	}

	return out48;
}

void DES::leftShift(int numShift, std::vector<int>& input) {
	std::vector<int> C;
	std::vector<int> D;
	int tempC, tempD;

	//Seperate 
	for (int i = 0; i < 28; ++i) {
		C.push_back(input[i]);
		D.push_back(input[i + 28]);
	}

	for (int i = 0; i < numShift; ++i) {
		tempC = C[0];
		C.erase(C.begin());
		C.push_back(tempC);

		tempD = D[0];
		D.erase(D.begin());
		D.push_back(tempD);
	}

	for (int i = 0; i < D.size(); ++i) {
		C.push_back(D[i]);
	}

	input = C;
}

void DES::initialPermutation(std::vector<int>& input) {
	std::vector<int> tempVector = input;
	int size = input.size() / 64;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < 64; ++j) {
			input[(i * 64) + j] = tempVector[IP[(i*64) + j] - 1];
		}
	}
}

std::vector<int> DES::rounds(std::vector<int> inputKey, std::vector<int> inputText, int blockNumber) {
	std::vector<int> rightSub;
	std::vector<int> leftSub;

	for (int i = 0; i < 32; ++i) {
		leftSub.push_back(inputText[(blockNumber * 64) + i]);
	}

	for (int i = 32; i < 64; ++i) {
		rightSub.push_back(inputText[(blockNumber * 64) + i]);
	}

	//Expansion Table
	std::vector<int> temp = rightSub;
	rightSub.clear();

	for (int i = 0; i < 48; ++i) {
		rightSub.push_back(temp[expansion[i]]);
	}



	return std::vector<int>();
}
