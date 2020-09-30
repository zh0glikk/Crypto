#pragma once
#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include <cmath>
#include <iomanip>
constexpr auto ALPHABET_LENGTH = 32;
int fileLen(std::ifstream* in);
void readFile(std::ifstream* in, char array[], int length);
void filtrate(char array[], int length);
void setAlphabet(char letters[]);
void printLetterAmount(char letters[], int letterAmount[], int ALPHABET_LENGTH);
void countLetterAmount(char array[], int length, char letters[], int letterAmount[], int ALPHABET_LENGTH);
int countRealLength(int letterAmount[], int ALPHABET_LENGTH);
double countEntrop(char array[], int length, int letterAmount[], int ALPHABET_LENGTH, int realLength);
void filtrateArrayForBigram(char source[], int sourceLength, char target[]);
void setBigrams(char letters[], int ALPHABET_LENGTH, char(&bigrams)[32][32][2]);
void countBigramAmountIntersection(char textBigramArray[], int realLength, int ALPHABET_LENGTH, int(&bigramAmountIntersection)[32][32], char(&bigrams)[32][32][2]);
void countBigramAmountWithoutIntersection(char textBigramArray[], int realLength, int ALPHABET_LENGTH, int(&bigramAmountWithoutIntersection)[32][32], char(&bigrams)[32][32][2]);
double countEntropForBigram(int(&bigramAmount)[32][32], int ALPHABET_LENGTH, int realLength);