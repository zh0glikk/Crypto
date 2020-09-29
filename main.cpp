#include <fstream>
#include <cmath>
#include <iostream>
#include <iomanip>

#define ALPHABET_LENGTH 32

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
	    
	    if ( tmp == '¨' || tmp == '¸') {
	    	array[i] = 'å';
	//    	std::cout << array[i];
		} else if ( tmp >= 'À' && tmp <= 'ß' ) {
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

int countRealLength(int letterAmount[], int alphabetLength) {
	int result = 0;
	
	for ( int i = 0; i < alphabetLength; i++ ) {
		result += letterAmount[i];
	}
	
	return result;
}

double countEntrop(char array[], int length, int letterAmount[], int alphabetLength, int realLength) {	
	double result = 0;
	
	for ( int i = 0; i < alphabetLength; i++ ) {
		if ( letterAmount[i] > 0 ) {
			double p = ((double)letterAmount[i] / (double)realLength);
			result += p * log2(p);
		}
	}
	result *= -1;
	
	return result;	
}




void filtrateArrayForBigram(char source[], int sourceLength, char target[]) {
	for ( int i = 0, j = 0; i < sourceLength; i++ ) {
		char tmp = source[i];
		if ( tmp >= 'à' && tmp <= 'ÿ') {
			target[j] = tmp;
			j += 1;
		}
	}
}

void setBigrams(char letters[], int alphabetLength, char (&bigrams)[32][32][2]) {
    for ( int i = 0; i < alphabetLength; i++) {
		for ( int j = 0; j < alphabetLength; j++ ) {
			bigrams[i][j][0] = letters[i];
			bigrams[i][j][1] = letters[j];
		}
	}
}

void countBigramAmountIntersection(char textBigramArray[], int realLength, int alphabetLength , int (&bigramAmountIntersection)[32][32], char (&bigrams)[32][32][2]) {
	for ( int i = 0; i < alphabetLength; i++ ) {
		for ( int j = 0; j < alphabetLength; j++ ) {
			bigramAmountIntersection[i][j] = 0;
		}
	}
	
	for ( int i = 0; i < alphabetLength; i++ ) {
		for ( int j = 0; j < alphabetLength; j++ ) {
			char tmp[2];
			tmp[0] = bigrams[i][j][0];
			tmp[1] = bigrams[i][j][1];
			
			for ( int k = 0; k < realLength; k++ ) {
				if ( tmp[0] == textBigramArray[k] && tmp[1] == textBigramArray[k+1] ) {
					bigramAmountIntersection[i][j] += 1;
				}
			}
    	}
    }
}

void countBigramAmountWithoutIntersection(char textBigramArray[], int realLength, int alphabetLength , int (&bigramAmountWithoutIntersection)[32][32], char (&bigrams)[32][32][2]) {
	for ( int i = 0; i < alphabetLength; i++ ) {
		for ( int j = 0; j < alphabetLength; j++ ) {
			bigramAmountWithoutIntersection[i][j] = 0;
		}
	}
	
	for ( int i = 0; i < alphabetLength; i++ ) {
		for ( int j = 0; j < alphabetLength; j++ ) {
			char tmp[2];
			tmp[0] = bigrams[i][j][0];
			tmp[1] = bigrams[i][j][1];
			
			for ( int k = 0; k < realLength; k += 2 ) {
				if ( tmp[0] == textBigramArray[k] && tmp[1] == textBigramArray[k+1] ) {
					bigramAmountWithoutIntersection[i][j] += 1;
				}
			}
    	}
    }
}

double countEntropForBigram(int (&bigramAmount)[32][32], int alphabetLength, int realLength) {
    double result = 0;
	
	for ( int i = 0; i < alphabetLength; i++ ) {
		for ( int j = 0; j < alphabetLength; j++ ) {
			if ( bigramAmount[i][j] > 0 ) {
				double p = ((double)bigramAmount[i][j] / (double)realLength);
				result += p * log2(p);
			}
		}
	}
	result *= -1;
	
	return result;	
}

int main() {
	std::setlocale(LC_ALL, "Russian");
  	std::ifstream in ("task.in");
  	int length = fileLen(&in);
  	char *textArray = new char[length];
  
  	const int alphabetLength = 32;
  	char letters[alphabetLength];
  	int letterAmount[alphabetLength];
  	
  	readFile(&in, textArray, length);
  
  	filtrate(textArray, length);
  
 
 	setAlphabet(letters);

  	countLetterAmount(textArray, length, letters, letterAmount, alphabetLength);

  	printLetterAmount(letters, letterAmount, alphabetLength);

  	std::cout << "entr: " << countEntrop(textArray, length, letterAmount, alphabetLength, countRealLength(letterAmount, alphabetLength)) << std::endl;
  
//	for ( int i = -128; i <= 127; i++ ) {
//		std::cout << i << " : " << (char)i << std::endl;
//	}

	int realLength = countRealLength(letterAmount, alphabetLength);
	char *textBigramArray = new char[realLength];
	char bigrams[alphabetLength][alphabetLength][2];
	int bigramAmountIntersection[alphabetLength][alphabetLength];
	int bigramAmountWithoutIntersection[alphabetLength][alphabetLength];
	
	filtrateArrayForBigram(textArray, length, textBigramArray);
	
	setBigrams(letters, alphabetLength, bigrams);
	
	countBigramAmountIntersection(textBigramArray, realLength, alphabetLength , bigramAmountIntersection, bigrams);
	
	
	//output text without spaces
//	for ( int i = 0; i < realLength; i++ ) {
//		std::cout << textBigramArray[i];
//	}
//	std::cout << std::endl;

	//output text bigrams
//	for ( int i = 0; i < alphabetLength; i++ ) {
//		for ( int j = 0; j < alphabetLength; j++ ) {
//			std::cout << bigrams[i][j][0] << bigrams[i][j][1] <<" ";
//		}
//		std::cout << std::endl;
//	}

	//output bigramAMount with interseptions
//	std::cout << "  ";
//	for ( int k = 0; k < alphabetLength; k++ ) {
//		std::cout << std::setw(3) << letters[k] << " ";
//	}
//	std::cout << std::endl;
//	for ( int i = 0; i < alphabetLength; i++ ) {
//		std::cout << letters[i] << " ";
//		for ( int j = 0; j < alphabetLength; j++ ) {
//			std::cout << std::setw(3) << bigramAmountIntersection[i][j] << " ";
//		}
//		std::cout << std::endl;
//	}
	
	countBigramAmountWithoutIntersection(textBigramArray, realLength, alphabetLength , bigramAmountWithoutIntersection, bigrams);
	
//	std::cout << std::endl;
//	//output bigramAMount without interseptions
//	std::cout << "  ";
//	for ( int k = 0; k < alphabetLength; k++ ) {
//		std::cout << std::setw(3) << letters[k] << " ";
//	}
//	std::cout << std::endl;
//	for ( int i = 0; i < alphabetLength; i++ ) {
//		std::cout << letters[i] << " ";
//		for ( int j = 0; j < alphabetLength; j++ ) {
//			std::cout << std::setw(3) << bigramAmountWithoutIntersection[i][j] << " ";
//		}
//		std::cout << std::endl;
//	}
	
	std::cout << "Entr1: " << countEntropForBigram(bigramAmountIntersection, alphabetLength, realLength) << std::endl;
	std::cout << "Entr2: " << countEntropForBigram(bigramAmountWithoutIntersection, alphabetLength, realLength) << std::endl;

}
