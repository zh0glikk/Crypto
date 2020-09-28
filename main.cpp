#include <fstream>
#include <cmath>
#include <iostream>

int fileLen(std::ifstream *in) {
  int length = 0;
  char tmp;
  
  for ( ; !in->eof() ; length++ ) {
    *in >> tmp;
  }
  
  in->close();
  in->open("task.in");
  
  return length-1;
}

void readFile(std::ifstream *in, char array[], int length) {
   for ( int i = 0; i < length; i++ ) {
     *in >> array[i];
   }
}

void filtrate(char array[], int length) {
  int delta = 32;
  char tmp;
  
  for ( int i = 0; i < length; i++ ) {
    tmp = array[i];
    if ( tmp >= 'À' && tmp <= 'ß' ) {
      array[i] += delta;
    } else if ( tmp < 'à' || tmp > 'ÿ' ) {
      array[i] = ' ';
    }
  }
}

void setAlphabet(char letters[]) {
	 for ( int i = 224; i <= 255; i++ ) {
		letters[i-224] = (char)i;
	}
}

void setBigrams(char** bigrams, int alphabetLength) {
	 for ( int i = 0; i < alphabetLength; i++ ) {
	 	for ( int j = 224; j <= 255; j++ ) {
	 		bigrams[i][j - 224] = (char)i;
		 }
	 }	
	 
	 for ( int i = 0; i < alphabetLength; i++ ) {
	 	for ( int k = 0; k < alphabetLength; k++ ) {
	 		std::cout << bigrams[i][k] << " ";
		 }
		 std::cout << std::endl;
	 }	
	 
}

void printLetterAmount(char letters[], int letterAmount[], int alphabetLength) {
	for ( int i = 0; i < alphabetLength; i++ ) {
		std::cout << letters[i] << " : " << letterAmount[i] << std::endl;
	}
}

void countLetterAmount(char array[], int length, char letters[], int letterAmount[], int alphabetLength) {
	 for ( int i = 0; i < alphabetLength; i++ ) {
		letterAmount[i] = 0;
	}
	
	for ( int i = 0; i < alphabetLength; i++ ) {
        char tmp = letters[i];
        
        for ( int j = 0; j < length; j++ ) {
            if ( array[j] == tmp ) {
                letterAmount[i] += 1;
            }
        }
    }
}

int countEntrop(char array[], int length, int letterAmount[], int alphabetLength) {	
	int result = 0;

	for ( int i = 0; i < alphabetLength; i++ ) {
		if ( letterAmount[i] > 0 ) {
			result += letterAmount[i] * log2(letterAmount[i]);
		}
	}
	
	return result;	
}

int main() {
  std::setlocale(LC_ALL, "Russian");
  std::ifstream in ("task.in");
  int length = fileLen(&in);
  char *array = new char[length];
  
  int alphabetLength = 33;
  char letters[alphabetLength];
  int letterAmount[alphabetLength];
  
  char bigrams[alphabetLength][alphabetLength];
  int bigramsAmount[alphabetLength][alphabetLength];
  
  readFile(&in, array, length);
  
  filtrate(array, length);
  
  
//  setAlphabet(letters);
//  
//  countLetterAmount(array, length, letters, letterAmount, alphabetLength);

//  printLetterAmount(letters, letterAmount, alphabetLength);
//
//
//  std::cout << "entr: " << countEntrop(array, length, letterAmount, alphabetLength) << std::endl;
  
  
}
