#pragma once
#include "Header.h"
void filtrateArrayForBigram(char source[], int sourceLength, char target[]) {
	for (int i = 0, j = 0; i < sourceLength; i++) {
		char tmp = source[i];
		if (tmp >= 'а' && tmp <= 'я') {
			target[j] = tmp;
			j += 1;
		}
	}
}

void setBigrams(char letters[], int ALPHABET_LENGTH, char(&bigrams)[32][32][2]) {
	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			bigrams[i][j][0] = letters[i];
			bigrams[i][j][1] = letters[j];
		}
	}
}

void countBigramAmountIntersection(char textBigramArray[], int realLength, int ALPHABET_LENGTH, int(&bigramAmountIntersection)[32][32], char(&bigrams)[32][32][2]) {
	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			bigramAmountIntersection[i][j] = 0;
		}
	}

	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			char tmp[2];
			tmp[0] = bigrams[i][j][0];
			tmp[1] = bigrams[i][j][1];

			for (int k = 0; k < realLength; k++) {
				if (tmp[0] == textBigramArray[k] && tmp[1] == textBigramArray[k + 1]) {
					bigramAmountIntersection[i][j] += 1;
				}
			}
		}
	}
}

void countBigramAmountWithoutIntersection(char textBigramArray[], int realLength, int ALPHABET_LENGTH, int(&bigramAmountWithoutIntersection)[32][32], char(&bigrams)[32][32][2]) {
	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			bigramAmountWithoutIntersection[i][j] = 0;
		}
	}

	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			char tmp[2];
			tmp[0] = bigrams[i][j][0];
			tmp[1] = bigrams[i][j][1];

			for (int k = 0; k < realLength; k += 2) {
				if (tmp[0] == textBigramArray[k] && tmp[1] == textBigramArray[k + 1]) {
					bigramAmountWithoutIntersection[i][j] += 1;
				}
			}
		}
	}
}

double countEntropForBigram(int(&bigramAmount)[32][32], int ALPHABET_LENGTH, int realLength) {
	double result = 0;

	for (int i = 0; i < ALPHABET_LENGTH; i++) {
		for (int j = 0; j < ALPHABET_LENGTH; j++) {
			if (bigramAmount[i][j] > 0) {
				double p = ((double)bigramAmount[i][j] / (double)realLength);
				result += p * log2(p);
			}
		}
	}
	result *= -1;

	return result;
}