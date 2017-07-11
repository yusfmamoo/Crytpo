/*
 * main.c
 *
 *  Created on: Oct 18, 2016
 *      Author: yusufm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "conversions.h"
#include "calculations.h"

#include "aes.h"

#define ECB 1

#define HEX_STRING_SIZE 60
void challenge_2();
void challenge_3();
void challenge_4();
void challenge_5();
void challenge_6();
void challenge_7();
void challenge_8();
void challenge_9();
void challenge_10();
void challenge_11();
void challenge_12();

int main(int argc, char* argv[])
{
	//Challenge 1
	printf("Number 1\n");
	char hexString[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	unsigned char* binaryResult;
	unsigned char* base64Result;
	binaryResult = hexToBinary(hexString);
	base64Result = binaryToBase64(binaryResult);
	printString(binaryResult);
	printString(base64Result);

	challenge_2();

	challenge_3();

	challenge_4();

	challenge_5();

	challenge_6();

	challenge_7();

	challenge_8();

	challenge_9();

	challenge_10();

	challenge_11();

	challenge_12();

	return 0;

}

void challenge_2()
{
	printf("\nNumber 2\n");

	char hexString_1[] = "1c0111001f010100061a024b53535009181c";
	char hexString_2[] = "686974207468652062756c6c277320657965";

	unsigned char* result;
	result = hexStringXOR(hexString_1, hexString_2);

	printString(result);
}

void challenge_3()
{
	printf("\nNumber_3\n");
	char *key;
	key = (char*)malloc(1);
	char hexString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	key[0] = findKey(hexString);
	key[1] = '\0';
	printf("%c\n", key[0]);
	unsigned char* result;
	result = hexStringKeyXOR(hexString, key);
	printString(result);
}

void challenge_4()
{
	printf("\nNumber_4\n");
	FILE *file;
	file = fopen("hexStrings.txt", "rb");
	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	fseek(file, 0, SEEK_SET);
	unsigned char word[1];
	char *key;
	char tempKey[1];
	key = (char*)malloc(1);
	unsigned char* result;
	float score;
	float tempScore = 0;
	unsigned char *hexString;
	hexString = (unsigned char*)malloc(HEX_STRING_SIZE* sizeof(unsigned char));
	unsigned char* tempString;
	int positionCounter = 0;
	while(fread(word, 1, 1, file) > 0)
	{
		if(word[0] == 10)
		{
			positionCounter;
		}
		else if(word[0] != 13)
		{
			*(hexString + positionCounter) = word[0];
			positionCounter++;
		}
		else
		{
			positionCounter = 0;
			key[0] = findKey(hexString);
			key[1] = '\0';
			result = hexStringKeyXOR(hexString, key);
			score = findStringScore(result);
			if(score > tempScore)
			{
				tempScore = score;
				tempString = result;
			}
		}
	}
	printf("%f\n", tempScore);
	printString(tempString);

}

void challenge_5()
{
	printf("\nNumber_5\n");

	FILE *file;
	file = fopen("Set_1_Challenge_5.txt", "rb");
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char* string;
	unsigned char* hexString;
	string = (unsigned char*)malloc(fileSize*sizeof(unsigned char) + 2);

	unsigned char key[10] = "ICE";

	char* tempResult;
	char* result;

	fread(string, 1, fileSize, file);
	string[fileSize] = '\0';
	fileSize++;
	string[fileSize] = 255;
	//hexString = binaryToHex(string);
	//tempResult = hexStringKeyXOR(hexString, key);

	//result = binaryToHex(tempResult);
	//printString(result);
}

void challenge_6()
{
	printf("\nNumber_6\n");

	FILE *file;
	file = fopen("Set_1_Challenge_6.txt", "rb");
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char word[1];
	unsigned char* string;
	string = (unsigned char*)malloc(fileSize * sizeof(unsigned char));

	int positionCounter = 0;
	while(fread(word, 1, 1, file) > 0)
	{
		if(!(word[0] == 10 || word[0] == 13))
		{
			*(string + positionCounter) = word[0];
			positionCounter++;
		}
	}
	*(string + positionCounter) = '\0';
	printString(string);

	unsigned char* binaryString;
	binaryString = base64ToBinary(string);

	int binaryStringLength = 0;
	while(binaryString[binaryStringLength] != 255)
	{
		binaryStringLength++;
	}

	printBinaryString(binaryString);

	printString(binaryToHex_notNullTerminated(binaryString));

	unsigned char* block_1;
	unsigned char* block_2;
	unsigned char* block_3;
	unsigned char* block_4;

	int startingPosition = 0;
	int totalHammingDistance = 0;
	int hammingDistance;
	float normalisedHammingDistance;
	float lowestHammingDistance = 0.0;

	int firstBlock = 0;
	int keySize;

	for(int blockSize = 3; blockSize < 40; blockSize++)
	{
		block_1 = divideBlocks(startingPosition, blockSize, binaryString);
		startingPosition = startingPosition + (blockSize);

		block_2 = divideBlocks(startingPosition, blockSize, binaryString);
		startingPosition = startingPosition + (blockSize);

		block_3 = divideBlocks(startingPosition, blockSize, binaryString);
		startingPosition = startingPosition + (blockSize);

		block_4 = divideBlocks(startingPosition, blockSize, binaryString);

		startingPosition = 0;

		hammingDistance = findHammingDistance(block_1, block_2);
		totalHammingDistance = totalHammingDistance + hammingDistance;
		hammingDistance = findHammingDistance(block_1, block_3);
		totalHammingDistance = totalHammingDistance + hammingDistance;
		hammingDistance = findHammingDistance(block_1, block_4);
		totalHammingDistance = totalHammingDistance + hammingDistance;
		hammingDistance = findHammingDistance(block_2, block_3);
		totalHammingDistance = totalHammingDistance + hammingDistance;
		hammingDistance = findHammingDistance(block_2, block_4);
		totalHammingDistance = totalHammingDistance + hammingDistance;
		hammingDistance = findHammingDistance(block_3, block_4);
		totalHammingDistance = totalHammingDistance + hammingDistance;
		normalisedHammingDistance = (float)totalHammingDistance/blockSize;
		totalHammingDistance = 0;

		if( firstBlock == 1)
		{
			if(normalisedHammingDistance < lowestHammingDistance)
			{
				lowestHammingDistance = normalisedHammingDistance;
				keySize = blockSize;
			}
		}
		else
		{
			firstBlock = 1;
			lowestHammingDistance = normalisedHammingDistance;
		}
	}
	printf("Key Size - %d\n", keySize);
	unsigned char* keyString;
	keyString = (unsigned char*)malloc(keySize + 2);
	for(int i = 0; i < keySize; i++)
	{
		unsigned char* transposedBlock;
		transposedBlock = (unsigned char*)malloc((binaryStringLength/keySize) + 2);

		int positionCount = 0;

		for(int index = 0; index < binaryStringLength; index++)
		{
			if(index % keySize == i)
			{
				transposedBlock[positionCount] = binaryString[index];
				positionCount++;
			}
		}
		transposedBlock[positionCount] = '\0';
		positionCount++;
		transposedBlock[positionCount] = 255;

		unsigned char* hexString;
		hexString = binaryToHex_notNullTerminated(transposedBlock);

		unsigned char key[2];

		key[0] = findKey_notNullTerminated(hexString);
		key[1] = '\0';

		keyString[i] = key[0];

		unsigned char* result;
		result = hexStringKeyXOR_notNullTerminated(hexString, key);

		free(transposedBlock);
		free(hexString);
		free(result);
	}
	keyString[keySize] = '\0';

	printString(keyString);

	unsigned char* hexString;
	hexString = binaryToHex_notNullTerminated(binaryString);

	unsigned char* result;
	result = hexStringKeyXOR_notNullTerminated(hexString, keyString);

	printString(result);

	free(result);
	free(hexString);
	free(binaryString);
	free(keyString);
}

void challenge_7()
{
	printf("\nNumber_7\n");

	unsigned char* key = "YELLOW SUBMARINE";

	FILE *file;
	file = fopen("Set_1_Challenge_7.txt", "rb");
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char word[1];
	unsigned char* string;
	string = (unsigned char*)malloc(fileSize * sizeof(unsigned char) + 2);


	int positionCounter = 0;
	int lineCount = 1;
	int firstLine = 1;
	int lineLength = 1;

	while(fread(word, 1, 1, file) > 0)
	{
		if(!(word[0] == 10 || word[0] == 13))
		{
			*(string + positionCounter) = word[0];
			positionCounter++;
		}
		else if(word[0] == 10)
		{
			lineCount++;
			if(firstLine)
			{
				lineLength = positionCounter;
				firstLine = 0;
			}
		}
	}
	*(string + positionCounter) = '\0';
	printString(string);

	unsigned char* binaryString;
	binaryString = base64ToBinary(string);

	int binaryStringLineLength = (lineLength * 3) / 4;
	printBinaryString(binaryString);

	int binaryStringLength = lineCount * binaryStringLineLength;

	unsigned char* result;

	result = ECB128_DECRYPT(binaryString, binaryStringLength, key);

	printString(result);
	free(binaryString);
	free(result);
}

void challenge_8()
{
	printf("\nNumber_8\n");

	FILE *file;
	file = fopen("Set_1_Challenge_8.txt", "rb");
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char word[1];
	unsigned char* string;
	int stringCount = 0;
	string = (unsigned char*)malloc((fileSize * sizeof(unsigned char)) + 2);


	int positionCounter = 0;

	while(fread(word, 1, 1, file) > 0)
	{
		*(string + positionCounter) = word[0];
		positionCounter++;
		if(word[0] == 13)
			stringCount++;
		if(word[0] == 10)
			stringCount;
	}
	*(string + positionCounter) = '\0';

	printf("%d\n", stringCount);
	int stringSize = (fileSize/stringCount) - 1;// for '13' and '10' character spaces

	unsigned char* block;
	block = (unsigned char*)malloc(((stringSize) * sizeof(unsigned char)) + 2);

	int matchingCharacters = 0;
	int matchingCharactersBlock = 0;
	int highestScore = 0;

	int subBlockSize = 16;

	unsigned char* bestBlock;
	bestBlock = (unsigned char*)malloc(((stringSize) * sizeof(unsigned char)) + 2);

	for(int index = 0; index < stringCount; index++)
	{
		for(int stringIndex = 0; stringIndex < stringSize; stringIndex++)
		{
			if(string[(index * stringSize) + stringIndex] != 10 || string[(index * stringSize) + stringIndex] != 13)
			{
				block[stringIndex] = string[(index * stringSize) + stringIndex];
			}
		}
		block[stringSize] = '\0';
		block[stringSize + 1] = 255;

		int numberOfBlocks = stringSize / subBlockSize;

		unsigned char* block_1;
		block_1 = (unsigned char*)malloc(((subBlockSize) * sizeof(unsigned char)) + 2);
		unsigned char* block_2;
		block_2 = (unsigned char*)malloc(((subBlockSize) * sizeof(unsigned char)) + 2);

		for(int index_out = 0; index_out < numberOfBlocks; index_out++)
		{
			block_1 = divideBlocks(index_out * subBlockSize, subBlockSize, block);

			for(int index_in = (index_out + 1); index_in < numberOfBlocks; index_in++)
			{
				block_2 = divideBlocks(index_in * subBlockSize, subBlockSize, block);
				matchingCharacters = compareBlocks(block_1, block_2, subBlockSize);
				matchingCharactersBlock = matchingCharactersBlock + matchingCharacters;
			}
			if(matchingCharactersBlock > highestScore)
			{
				highestScore = matchingCharactersBlock;
				for(int i = 0; i < stringSize; i++)
				{
					bestBlock[i] = block[i];
				}
			}

			matchingCharactersBlock = 0;
		}
	}

	printf("%d\n", highestScore);
	printString(bestBlock);
}

void challenge_9()
{
	printf("Number_9\n");

	unsigned char string[] = "YELLOW SUBMARINE";

	int paddedStringLength = 22;

	unsigned char* paddedString;
	paddedString = PKCS7_PAD(string, paddedStringLength);

	printString(paddedString);
	printBinaryString(paddedString);
}

void challenge_10()
{
	printf("\nNumber_10\n");

	unsigned char* key = "YELLOW SUBMARINE";

	FILE *file;
	file = fopen("Set_2_Challenge_10.txt", "rb");
	fseek(file, 0, SEEK_END);
	int fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	unsigned char word[1];
	unsigned char* string;
	string = (unsigned char*)malloc(fileSize * sizeof(unsigned char) + 2);


	int positionCounter = 0;
	int lineCount = 1;
	int firstLine = 1;
	int lineLength = 1;

	while(fread(word, 1, 1, file) > 0)
	{
		if(!(word[0] == 10 || word[0] == 13))
		{
			*(string + positionCounter) = word[0];
			positionCounter++;
		}
		else if(word[0] == 10)
		{
			lineCount++;
			if(firstLine)
			{
				lineLength = positionCounter;
				firstLine = 0;
			}
		}
	}
	*(string + positionCounter) = '\0';
	positionCounter++;
	*(string + positionCounter) = 255;

	unsigned char* binaryString;
	binaryString = base64ToBinary(string);
	int binaryStringLength = (lineLength * lineCount * 3) / 4;
	printf("%d\n", fileSize);
	printf("%d\n", binaryStringLength);
	printBinaryString(binaryString);

	int stringSize = (fileSize/lineCount) - 1;// for '13' and '10' character spaces

	unsigned char* IVBlock;
	IVBlock = (unsigned char*)calloc(16, sizeof(unsigned char));

	unsigned char* result;

	result = CBC128_DECRYPT(binaryString, binaryStringLength, key, IVBlock);

	printString_notNullTerminated(result);
}

void challenge_11()
{
	printf("\nNumber_11\n");

	unsigned char* string = "1111111111111111111111111111111111111111111111111111111111111111111";
	unsigned char* result;

	result = RANDOM_ENCRYPT(string, strlen(string));
	printBinaryString(result);
	if(detectECB(result, strlen(string)) == 1)
		printf("ECB Detected\n");
	else
		printf("CBC Detected\n");
}

void challenge_12()
{
	printf("\nNumber_12\n");

	unsigned char* stringToDecode = "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkgaGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBqdXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUgYnkK";
	unsigned char* decodedString = base64ToBinary(stringToDecode);

	unsigned char* textToAppend = "1111111111111111111111111111111111111111111111111111111111111111111";

	int stringLength = strlen(decodedString) + strlen(textToAppend) + 3;
	printf("%d\n", stringLength);
	unsigned char* string;
	string = (unsigned char*)calloc(stringLength, sizeof(unsigned char));

	appendBlock(0, decodedString, string);
	appendBlock(strlen(decodedString), textToAppend, string);

	string[strlen(string) + strlen(textToAppend)] = '\0';
	string[strlen(string) + strlen(textToAppend) + 1] = 255;
	string[strlen(string) + strlen(textToAppend) + 2] = 0;
	printString(string);
}
