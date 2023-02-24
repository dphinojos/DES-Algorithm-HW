#include "des.h"

void DES::permitedChoiceOne(std::vector<int>& input) {
	std::vector<int> tempVector = input;

	for (int i = 0; i < 64; ++i) {
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

std::vector<int> DES::rounds(std::vector<int>& inputKey, std::vector<int> inputText, int blockNumber, int roundNumber) {
	std::vector<int> rightSub, rightOut;
	std::vector<int> leftSub, leftOut;
	std::vector<int> key48;

	std::cout << "Left Shift Process:\n";
	
	switch (roundNumber) {
	case 1:
		leftShift(1, inputKey);
		break;
	case 2:
		leftShift(1, inputKey);
		break;
	case 9:
		leftShift(1, inputKey);
		break;
	case 16:
		leftShift(1, inputKey);
	default:
		leftShift(2, inputKey);
		break;
	}

	for (int i = 0; i < inputKey.size(); ++i) {
		std::cout << inputKey[i];
	}
	std::cout << "\n";

	//Permitted Choice 2
	/*std::cout << "Hashing 2:\n";
	key48 = permitedChoiceTwo(inputKey);

	for (int i = 0; i < key48.size(); ++i) {
		std::cout << key48[i];
	}
	std::cout << "\n";*/

	for (int i = 0; i < 32; ++i) {
		leftSub.push_back(inputText[(blockNumber * 64) + i]);
	}
	//print
	std::cout << "Left Subblock:\n";
	for (int i = 0; i < leftSub.size(); ++i) {
		std::cout << leftSub[i];
	}
	//print
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

	//XOR
	std::cout << "XOR with Key:\n";
	for (int i = 0; i < 48; ++i) {
		temp.push_back(rightSub[i] ^ inputKey[i]);
	}

	//print
	for (int i = 0; i < temp.size(); ++i) {
		std::cout << temp[i];
	}
	std::cout << "\n";

	//SBlock Operation
	temp = sBlock(blockNumber % 8, temp);

	for (int i = 0; i < 32; ++i) {
		rightOut.push_back(temp[i] ^ leftSub[i]);
	}

	//Because I'm dumb and cleared out rightSub without realizing I'm gonna need it
	//It's okay though it just turns directly into the left block.
	leftOut.clear();
	std::cout << "Left Out:\n";
	for (int i = 32; i < 64; ++i) {
		leftOut.push_back(inputText[(blockNumber * 64) + i]);
	}
	//print
	for (int i = 0; i < leftOut.size(); ++i) {
		std::cout << leftOut[i];
	}
	std::cout << "\n";

	std::cout << "Right Out:\n";
	//print
	for (int i = 0; i < rightOut.size(); ++i) {
		std::cout << rightOut[i];
	}
	std::cout << "\n";

	temp.clear();
	//COMBINE
	for (int i = 0; i < leftOut.size(); ++i) {
		temp.push_back(leftOut[i]);
	}
	for (int i = 0; i < rightOut.size(); ++i) {
		temp.push_back(rightOut[i]);
	}

	return temp;
}

std::vector<int> DES::sBlock(int s, std::vector<int> input) {

	std::vector<int> temp;
	std::vector<int> group1;
	std::vector<int> group2;
	std::vector<int> group3;
	std::vector<int> group4;
	std::vector<int> group5;
	std::vector<int> group6;
	std::vector<int> group7;
	std::vector<int> group8;

	//Allocate Groups
	for (int i = 0; i < 6; ++i) {
		group1.push_back(input[i]);
		group2.push_back(input[i + 6]);
		group3.push_back(input[i + 12]);
		group4.push_back(input[i + 18]);
		group5.push_back(input[i + 24]);
		group6.push_back(input[i + 30]);
		group7.push_back(input[i + 36]);
		group8.push_back(input[i + 42]);
	}

	sGroupChange(temp, group1, s);
	sGroupChange(temp, group2, s);
	sGroupChange(temp, group3, s);
	sGroupChange(temp, group4, s);
	sGroupChange(temp, group5, s);
	sGroupChange(temp, group6, s);
	sGroupChange(temp, group7, s);
	sGroupChange(temp, group8, s);

	sPermutation(temp);
	
	return temp;
}

int DES::convertBittoDecimal(long long n) {
	int dec = 0, i = 0, rem;

	while (n != 0) {
		rem = n % 10;
		n /= 10;
		dec += rem * pow(2, i);
		++i;
	}

	return dec;
}

void DES::sGroupChange(std::vector<int>& change, std::vector<int> group, int s) {
	int binaryIn, sNumber, x, y;
	int sBlock[4][16];

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 16; ++j) {
			sBlock[i][j] = 0;
		}
	}

	//Pick S block depending on block number
	switch (s) {
	case 0:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 16; ++j) {
				sBlock[i][j] = s1[i][j];
			}
		}
		break;

	case 1:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 16; ++j) {
				sBlock[i][j] = s2[i][j];
			}
		}
		break;

	case 2:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 16; ++j) {
				sBlock[i][j] = s3[i][j];
			}
		}
		break;

	case 3:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 16; ++j) {
				sBlock[i][j] = s4[i][j];
			}
		}
		break;

	case 4:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 16; ++j) {
				sBlock[i][j] = s5[i][j];
			}
		}
		break;

	case 5:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 16; ++j) {
				sBlock[i][j] = s6[i][j];
			}
		}
		break;

	case 6:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 16; ++j) {
				sBlock[i][j] = s7[i][j];
			}
		}
		break;

	case 7:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 16; ++j) {
				sBlock[i][j] = s8[i][j];
			}
		}
		break;

	default:
		break;
	}

	binaryIn = (group[0] * 10) + group[5];
	x = convertBittoDecimal(binaryIn);
	binaryIn = (group[1] * 1000) + (group[2] * 100) + (group[3] * 10) + group[4];
	y = convertBittoDecimal(binaryIn);

	sNumber = sBlock[x - 1][y - 1];

	int array[4];

	for (int i = 0; i < 4; ++i) {
		array[i] = (sNumber >> i) & 1;
	}
	for (int i = 0; i < 4; ++i) {
		change.push_back(array[0]);
	}
}

void DES::sPermutation(std::vector<int>& input) {
	std::vector<int> tempVector = input;

	for (int i = 0; i < input.size(); ++i) {
		input[i] = tempVector[sP[i] - 1];
	}
}

std::string DES::berstein_hash(const std::string& input) {
	unsigned long long hash = 5381;
	for (char c : input) {
		hash = (hash * 33) + static_cast<unsigned char>(c);
	}

	std::stringstream ss;
	ss << std::hex << hash;
	return ss.str();
}

std::string DES::toBinary(std::string const& str) {
	std::string binary = "";
	for (char const& c : str) {
		binary += std::bitset<8>(c).to_string();
	}
	return binary;
} //Converts String to StringBit