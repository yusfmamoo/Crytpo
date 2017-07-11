/*
 * calculations.h
 *
 *  Created on: Oct 26, 2016
 *      Author: yusufm
 */

#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

#include "conversions.h"
#include <time.h>
#include <stdlib.h>

unsigned char* binaryStringXOR(unsigned char binaryString_1[], unsigned char binaryString_2[]);
unsigned char* hexStringXOR(char hexString_1[], char hexString_2[]);
unsigned char* hexStringKeyXOR(unsigned char hexString_1[], unsigned char hexString_2[]);
unsigned char* hexStringKeyXOR_notNullTerminated(unsigned char hexString_1[], unsigned char keyString[]);
float stringScore(unsigned char* string);
unsigned char* stringToLower(unsigned char* string);
char findKey(unsigned char hexString_1[]);
char findKey_notNullTerminated(unsigned char hexString_1[]);
float findStringScore(unsigned char *string);
int findHammingDistance(unsigned char* string_1, unsigned char* string_2);
unsigned char* divideBlocks(int startingPosition, int blockSize, const unsigned char* binaryString);
void appendBlock(int startingPosition, unsigned char* block, unsigned char* blockToAppend);
int compareBlocks(unsigned char* block_1, unsigned char* block_2, int blockLength);
void generateRandomString(unsigned char* string, int stringLength);

#endif /* CALCULATIONS_H_ */
