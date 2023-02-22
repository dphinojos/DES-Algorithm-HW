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
	//print
	std::cout << "Left Subblock:\n";
	for (int i = 0; i < leftSub.size(); ++i) {
		std::cout << leftSub[i];
	}
	std::cout << "\n";

	std::cout << "Right Subblock:\n";
	for (int i = 32; i < 64; ++i) {
		rightSub.push_back(inputText[(blockNumber * 64) + i]);
	}
	//print
	for (int i = 0; i < rightSub.size(); ++i) {
		std::cout << rightSub[i];
	}
	std::cout << "\n";

	//Expansion Table
	std::cout << "Expanding Right Subblock...\n";
	std::vector<int> temp = rightSub;
	rightSub.clear();

	for (int i = 0; i < 48; ++i) {
		rightSub.push_back(temp[expansion[i] - 1]);
	}

	//print
	for (int i = 0; i < rightSub.size(); ++i) {
		std::cout << rightSub[i];
	}
	std::cout << "\n";

	temp.clear();

	std::cout << "XOR with Key:\n";
	for (int i = 0; i < 48; ++i) {
		temp.push_back(rightSub[i] ^ inputKey[i]);
	}

	//print
	for (int i = 0; i < temp.size(); ++i) {
		std::cout << temp[i];
	}
	std::cout << "\n";

	switch(blockNumber % 8) {
		case 1:
			temp = sBlock(s1, temp);
			break;
		case 2:
			temp = sBlock(s2, temp);
			break;
		case 3:
			temp = sBlock(s3, temp);
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		default:
			std::cout << "Error\n";
			return;
	}

	return rightSub;
}

std::vector<int> DES::sBlock(int [][16] , std::vector<int> input) {



	return std::vector<int>();
}
