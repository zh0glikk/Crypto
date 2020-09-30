#pragma once
#include "Header.h"
void setAlphabet(char letters[]) {
	for (int i = 224; i <= 255; i++) {
		letters[i - 224] = (char)i;
	}
}

void printLetterAmount(char letters[], int letterAmount[], int ALPHABET_LENGTH) {
	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		std::cout << letters[i] << " : " << letterAmount[i] << std::endl;
	}
}

void countLetterAmount(char array[], int length, char letters[], int letterAmount[], int ALPHABET_LENGTH) {
	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		letterAmount[i] = 0;
	}

	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		char tmp = letters[i];

		for (int j = 0; j < length; j++) {
			if (array[j] == tmp) {
				letterAmount[i] += 1;
			}
		}
	}
}

int countRealLength(int letterAmount[], int ALPHABET_LENGTH) {
	int result = 0;

	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		result += letterAmount[i];
	}

	return result;
}

double countEntrop(char array[], int length, int letterAmount[], int ALPHABET_LENGTH, int realLength) {
	double result = 0;

	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		if (letterAmount[i] > 0) {
			double p = ((double)letterAmount[i] / (double)realLength);
			result += p * log2(p);
		}
	}
	result *= -1;

	return result;
}
