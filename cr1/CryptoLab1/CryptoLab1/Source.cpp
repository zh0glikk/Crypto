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
	for (int i = 0; i < length; i++) {
		*in >> array[i];
	}
}

void filtrate(char array[], int length) {
	int delta = 32;
	char tmp;

	for (int i = 0; i < length; i++) {
		tmp = array[i];

		if (tmp == 'Ë' || tmp == 'ё') {
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
	int realLength;

	char letters[ALPHABET_LENGTH];
	int letterAmount[ALPHABET_LENGTH];
	double letterFrequency[ALPHABET_LENGTH];
	std::ofstream outLF("letterFrequencySorted.txt");

	readFile(&in, textArray, length);

	filtrate(textArray, length);


	setAlphabet(letters);

	countLetterAmount(textArray, length, letters, letterAmount);

	realLength = countRealLength(letterAmount);

	countLetterFrequency(letterAmount, letterFrequency, realLength);

	printLetterFrequencySortedToFile(&outLF, letterFrequency, letters);

	std::cout << "Symbols entrop: " << countEntrop(letterFrequency) << std::endl;


	
	char* textBigramArray = new char[realLength];
	char bigrams[ALPHABET_LENGTH][ALPHABET_LENGTH][2];
	int bigramAmountIntersection[ALPHABET_LENGTH][ALPHABET_LENGTH];
	int bigramAmountWithoutIntersection[ALPHABET_LENGTH][ALPHABET_LENGTH];
	double bigramFrequencyIntersection[ALPHABET_LENGTH][ALPHABET_LENGTH];
	double bigramFrequencyWithoutIntersection[ALPHABET_LENGTH][ALPHABET_LENGTH];
	std::ofstream outBI("bigramFrequencyIntersection.txt");
	std::ofstream outBWI("bigramFrequencyWithoutIntersection.txt");

	filtrateArrayForBigram(textArray, length, textBigramArray);

	setBigrams(letters, bigrams);

	countBigramAmountIntersection(textBigramArray, realLength, bigramAmountIntersection, bigrams);

	countBigramAmountWithoutIntersection(textBigramArray, realLength, bigramAmountWithoutIntersection, bigrams);

	countBigramFrequency(bigramAmountIntersection, bigramFrequencyIntersection, realLength);
	countBigramFrequency(bigramAmountWithoutIntersection, bigramFrequencyWithoutIntersection, realLength);

	printTableToFile(&outBI, bigramFrequencyIntersection, letters);
	printTableToFile(&outBWI, bigramFrequencyWithoutIntersection, letters);

	std::cout << "Bigrams with intersection entrop: " << countEntropForBigram(bigramAmountIntersection, realLength) << std::endl;
	std::cout << "Bigrams without intersection entrop: " << countEntropForBigram(bigramAmountWithoutIntersection, realLength) << std::endl;

}
