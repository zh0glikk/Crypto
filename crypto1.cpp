#include "Header.h"
int fileLen(std::ifstream* in) {
	int length = 0;
	char tmp;
	
	for (; !in->eof(); length++) {
		*in >> tmp;
	}

	in->close();
	in->open("task.in");

	return length - 1;
}

void readFile(std::ifstream* in, char array[], int length) {
	in->seekg(0);
	for (int i = 0; i < length; i++) {
		*in >> array[i];
	}
}

void filtrate(char array[], int length) {
	int delta = 32;
	char tmp;

	for (int i = 0; i < length; i++) {
		tmp = array[i];

		if (tmp == 'ё' || tmp == 'Ё') {
			array[i] = 'е';
		}
		else if (tmp >= 'А' && tmp <= 'Я') {
			array[i] += delta;
		}
		else if (tmp < 'а' || tmp > 'я') {
			array[i] = ' ';
		}
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	std::ifstream in("task.in");
	int length = fileLen(&in);
	char* textArray = new char[length];
	char letters[ALPHABET_LENGTH];
	int letterAmount[ALPHABET_LENGTH];

	readFile(&in, textArray, length);

	filtrate(textArray, length);

	setAlphabet(letters);

	countLetterAmount(textArray, length, letters, letterAmount, ALPHABET_LENGTH);

	printLetterAmount(letters, letterAmount, ALPHABET_LENGTH);

	std::cout << "entr: " << countEntrop(textArray, length, letterAmount, ALPHABET_LENGTH, countRealLength(letterAmount, ALPHABET_LENGTH)) << std::endl;

	//	for ( int i = -128; i <= 127; i++ ) {
	//		std::cout << i << " : " << (char)i << std::endl;
	//	}

	int realLength = countRealLength(letterAmount, ALPHABET_LENGTH);
	char* textBigramArray = new char[realLength];
	char bigrams[ALPHABET_LENGTH][ALPHABET_LENGTH][2];
	int bigramAmountIntersection[ALPHABET_LENGTH][ALPHABET_LENGTH];
	int bigramAmountWithoutIntersection[ALPHABET_LENGTH][ALPHABET_LENGTH];

	filtrateArrayForBigram(textArray, length, textBigramArray);

	setBigrams(letters, ALPHABET_LENGTH, bigrams);

	countBigramAmountIntersection(textBigramArray, realLength, ALPHABET_LENGTH, bigramAmountIntersection, bigrams);


	//output text without spaces
	for ( int i = 0; i < realLength; i++ ) {
		std::cout << textBigramArray[i];
	}
	std::cout << std::endl;

	//output text bigrams
	for ( int i = 0; i < ALPHABET_LENGTH; i++ ) {
		for ( int j = 0; j < ALPHABET_LENGTH; j++ ) {
			std::cout << bigrams[i][j][0] << bigrams[i][j][1] <<" ";
		}
		std::cout << std::endl;
	}

	//output bigramAMount with interseptions
	std::cout << "  ";
	for ( int k = 0; k < ALPHABET_LENGTH; k++ ) {
		std::cout << std::setw(3) << letters[k] << " ";
	}
	std::cout << std::endl;
	for ( int i = 0; i < ALPHABET_LENGTH; i++ ) {
		std::cout << letters[i] << " ";
		for ( int j = 0; j < ALPHABET_LENGTH; j++ ) {
			std::cout << std::setw(3) << bigramAmountIntersection[i][j] << " ";
		}
		std::cout << std::endl;
	}

	countBigramAmountWithoutIntersection(textBigramArray, realLength, ALPHABET_LENGTH, bigramAmountWithoutIntersection, bigrams);

		std::cout << std::endl;
		//output bigramAMount without interseptions
		std::cout << "  ";
		for ( int k = 0; k < ALPHABET_LENGTH; k++ ) {
			std::cout << std::setw(3) << letters[k] << " ";
		}
		std::cout << std::endl;
		for ( int i = 0; i < ALPHABET_LENGTH; i++ ) {
			std::cout << letters[i] << " ";
			for ( int j = 0; j < ALPHABET_LENGTH; j++ ) {
				std::cout << std::setw(3) << bigramAmountWithoutIntersection[i][j] << " ";
			}
			std::cout << std::endl;
		}

	std::cout << "Entr1: " << countEntropForBigram(bigramAmountIntersection, ALPHABET_LENGTH, realLength) << std::endl;
	std::cout << "Entr2: " << countEntropForBigram(bigramAmountWithoutIntersection, ALPHABET_LENGTH, realLength) << std::endl;

}