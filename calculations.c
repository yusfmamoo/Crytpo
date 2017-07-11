/*
 * calculations.cpp
 *
 *  Created on: Oct 26, 2016
 *      Author: yusufm
 */

#include "calculations.h"

unsigned char* binaryStringXOR(unsigned char binaryString_1[], unsigned char binaryString_2[])
{
	int strLength;
	unsigned char* XORResult;
	if(strlen(binaryString_1) >= strlen(binaryString_2))
	{
		strLength = strlen(binaryString_1);
		XORResult = (unsigned char*)malloc(strLength);
	}
	else
	{
		strLength = strlen(binaryString_2);
		XORResult = (unsigned char*)malloc(strLength);
	}
	for(int index = 0; index < strLength; index++)
	{
		XORResult[index] = binaryString_1[index] ^ binaryString_2[index];
	}
	XORResult[strLength] = '\0';
	strLength++;
	XORResult[strLength] = 255;

	return XORResult;
}

unsigned char* hexStringXOR(char hexString_1[], char hexString_2[])
{
	unsigned char* binaryString_1 = hexToBinary(hexString_1);
	unsigned char* binaryString_2 = hexToBinary(hexString_2);
	int strLength;
	unsigned char* XORResult;
	if(strlen(binaryString_1) >= strlen(binaryString_2))
	{
		strLength = strlen(binaryString_1);
		XORResult = (unsigned char*)malloc(strLength);
	}
	else
	{
		strLength = strlen(binaryString_2);
		XORResult = (unsigned char*)malloc(strLength);
	}
	for(int index = 0; index < strLength; index++)
	{
		XORResult[index] = binaryString_1[index] ^ binaryString_2[index];
	}
	XORResult[strLength] = '\0';
	strLength++;
	XORResult[strLength] = 255;

	unsigned char* result;
	result = binaryToHex(XORResult);
	return result;
}

unsigned char* hexStringKeyXOR(unsigned char hexString_1[], unsigned char keyString[])
{
	unsigned char* binaryString_1 = hexToBinary(hexString_1);
	int strLength, keyStringLength;
	unsigned char* XORResult;
	strLength = strlen(binaryString_1);
	keyStringLength = strlen(keyString);
	if(keyStringLength == 0)
		keyStringLength++;

	XORResult = (unsigned char*)malloc(strLength);
	for(int index = 0; index < strLength; index++)
	{
		XORResult[index] = binaryString_1[index] ^ keyString[index % keyStringLength];
		if(XORResult[index] == 0)
			XORResult[index] = 255;
	}
	return XORResult;
}

unsigned char* hexStringKeyXOR_notNullTerminated(unsigned char hexString_1[], unsigned char keyString[])
{
	unsigned char* binaryString_1 = hexToBinary(hexString_1);
	int strLength, keyStringLength;
	unsigned char* XORResult;
	strLength = strlenBinary(binaryString_1);
	keyStringLength = strlen(keyString);
	if(keyStringLength == 0)
		keyStringLength++;

	XORResult = (unsigned char*)malloc(strLength);
	for(int index = 0; index < strLength; index++)
	{
		XORResult[index] = binaryString_1[index] ^ keyString[index % keyStringLength];
		if(XORResult[index] == 0)
			XORResult[index] = 255;
	}
	return XORResult;
}

float stringScore(unsigned char* string)
{
	unsigned char* scoreString = "etaoinshrdlc u";
	unsigned char *cleanString;
	cleanString = stringToLower(string);
	float score = 0;
	float weigthageArray[14] = {0.127, 0.906, 0.817, 0.751, 0.697, 0.675, 0.633, 0.609, 0.599, 0.425, 0.402, 0.278, 0.1, 0.276};
	for(unsigned int i = 0; i < strlen(cleanString); i++)
	{
		for(unsigned int j = 0; j < strlen(scoreString); j++)
		{
			if(cleanString[i] == scoreString[j])
			{
				score = score + (weigthageArray[j]);
			}
		}
	}
	return score;
}

unsigned char* stringToLower(unsigned char* string)
{
	unsigned char* result;
	result = (unsigned char*)malloc(strlen(string)+1000);
	for(unsigned int i = 0; i < strlen(string); i++)
	{
		if(string[i] >= 65 && string[i] <= 90)
		{
			result[i] = string[i] + 32;
		}
		else
			result[i] = string[i];
	}
	return string;
}

char findKey(unsigned char hexString[])
{
	unsigned char* result;
	float score;
	float tempScore = 0;
	char *word;
	word = (char*)malloc(1);
	char key = 0;
	for(int i = 0; i < 128; i++)
	{
		word[0] = i;
		word[1] = '\0';
		result = hexStringKeyXOR(hexString, word);
		score = stringScore(result);
		if( tempScore >= score)
		{
			score = tempScore;
		}
		else
		{
			tempScore = score;
			key = i;
		}
	}
	return key;
}

char findKey_notNullTerminated(unsigned char hexString[])
{
	unsigned char* result;
	float score;
	float tempScore = 0;
	char *word;
	word = (char*)malloc(1);
	char key = 0;
	for(int i = 0; i < 128; i++)
	{
		word[0] = i;
		word[1] = '\0';
		result = hexStringKeyXOR_notNullTerminated(hexString, word);
		score = stringScore(result);
		if( tempScore >= score)
		{
			score = tempScore;
		}
		else
		{
			tempScore = score;
			key = i;
		}
	}
	return key;
}

float findStringScore(unsigned char *string)
{
	float score;
	score = stringScore(string);

	return score;
}

int findHammingDistance(unsigned char* string_1, unsigned char* string_2)
{
	int count = 0;
	int index = 0;

	while(string_1[index] != 255 && string_2[index] !=255)
	{
		unsigned char word_1 = string_1[index];
		unsigned char word_2 = string_2[index];
		for(int bitPos = 7; bitPos >= 0; bitPos--)
		{
			unsigned char var_1;
			var_1 = word_1 << bitPos;
			var_1 = var_1 >> 7;

			unsigned char var_2;
			var_2 = word_2 << bitPos;
			var_2 = var_2 >> 7;

			if(var_1 != var_2)
				count++;
		}
		index++;
	}
	return count;
}

unsigned char* divideBlocks(int startingPosition, int blockSize, const unsigned char* binaryString)
{

	unsigned char* result;

	if(blockSize < 9)
		result = (unsigned char*)malloc(9);
	else
		result = (unsigned char*)malloc((blockSize) + 2);

	int positionCount = 0;

	for(int index = startingPosition; index < (startingPosition + (blockSize));)
	{
		if(binaryString[index] != 255 || (binaryString[index] == 255 && binaryString[index + 1] != 0))
		{
			result[positionCount] = binaryString[index];
			index++;
			positionCount++;
		}
	}
	result[positionCount] = '\0';
	positionCount++;
	result[positionCount] = 255;

	return result;
}

void appendBlock(int startingPosition, unsigned char* block, unsigned char* blockToAppend)
{
	int positionCount = 0;
	for(int index = startingPosition; index < startingPosition + strlen(block); index++)
	{
		blockToAppend[index] = block[positionCount];
		positionCount++;
	}
}

int compareBlocks(unsigned char* block_1, unsigned char* block_2, int blockLength)
{
	int matchingCharacters = 0;
	for(unsigned int index = 0; index < blockLength; index++)
	{
		if(block_1[index] == block_2[index])
			matchingCharacters++;
	}
	return matchingCharacters;
}

void generateRandomString(unsigned char* string, int stringLength)
{
	srand(rand());

	for(int index = 0; index < stringLength; index++)
	{
		int randomNumber = rand() % 254;
		string[index] = randomNumber;
	}
	string[stringLength + 1] = '\0';
	string[stringLength + 2] = 255;
	string[stringLength + 3] = 0;
}
