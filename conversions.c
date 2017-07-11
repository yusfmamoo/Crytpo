/*
 * conversions.c
 *
 *  Created on: Oct 25, 2016
 *      Author: yusufm
 */

#include "conversions.h"

unsigned char* hexToBinary(char *hexString)
{
	int index;
	unsigned char word;
	unsigned char val;
	unsigned char *binary;
	binary = (unsigned char*)malloc(strlen(hexString)/2);
	for (index = 0; index < strlen(hexString); index++)
	{
		word = hexString[index];
		if(word >= 97)
		{
			val = word-97+10;
		}
		else
		{
			val = word-48;
		}
		if(index%2 == 0)
			binary[index/2] = val << 4;
		else
		{
			binary[index/2] |= val;
		}
	}
	binary[strlen(hexString)/2] = 255;
	return binary;
}

unsigned char* binaryToBase64(unsigned char* binary)
{
	unsigned char word, word_2;
	unsigned char* result;
	result = (unsigned char*)malloc(((strlen(binary))/3)*4);
	int index = 0;
	int resultIndex = 0;
	int binLength = strlen(binary);
	while(index != (binLength))
	{
		if((index + 1) % 3 == 1)
		{
			word = binary[index];
			result[resultIndex] = base64Table(word >> 2);
			resultIndex++;
		}
		else if((index + 1) % 3 == 2)
		{
			word = binary[index-1];
			word = word << 6;
			word_2 = binary[index];
			result[resultIndex] = base64Table((word >> 2) | (word_2 >>4));
			resultIndex++;
		}
		else if((index + 1) % 3 == 0)
		{
			word = binary[index-1];
			word = word << 4;
			word_2 = binary[index];
			result[resultIndex] = base64Table((word >> 2) | (word_2 >> 6));
			resultIndex++;

			word = binary[index];
			word = word << 2;
			result[resultIndex] = base64Table(word >> 2);
			resultIndex++;

		}
		index++;
	}
	return result;
}

unsigned char base64Table(unsigned char val)
{
	if(val >= 0 && val <= 25)
		val = val + 65;
	else if(val >= 26 && val <= 51)
		val = val + 71;
	else if(val >= 52 && val <= 61)
		val = val - 4;
	else if(val == 62)
		val = val - 19;
	else
		val = val - 16;

	return val;
}

unsigned char* binaryToHex(unsigned char* binaryString)
{
	unsigned char word;
	unsigned char val;
	unsigned char* result;
	int resultIndex = 0;
	result = (unsigned char*)malloc(strlen(binaryString)*2);

	for(int index = 0; index < strlenBinary(binaryString); index++)
	{
		word = binaryString[index];
		if(binaryString[index] == 255)
		{
			result[resultIndex] = 48;
			resultIndex++;
			result[resultIndex+1] = 48;
			resultIndex++;
		}
		else
		{
			val = word >> 4;
			if(val >= 0 && val <= 9)
				result[resultIndex] = val + 48;
			else
				result[resultIndex] = val + 97 - 10;
			resultIndex++;
			val = (word << 4);
			val = val >>4;
			if(val >= 0 && val <= 9)
				result[resultIndex] = val + 48;
			else
				result[resultIndex] = val + 97 - 10;
			resultIndex++;
		}
	}
	return result;
}

unsigned char* binaryToHex_notNullTerminated(unsigned char* binaryString)
{
	unsigned char word;
	unsigned char val;
	unsigned char* result;
	int resultIndex = 0;
	int binaryStringLength = 0;
	while(binaryString[binaryStringLength] != 255)
	{
		binaryStringLength++;
	}
	result = (unsigned char*)malloc(binaryStringLength*2 + 2);
	for(int index = 0; index < binaryStringLength; index++)
	{
		word = binaryString[index];
		if(binaryString[index] == 255)
		{
			result[resultIndex] = 48;
			resultIndex++;
			result[resultIndex+1] = 48;
			resultIndex++;
		}
		else
		{
			val = word >> 4;
			if(val >= 0 && val <= 9)
				result[resultIndex] = val + 48;
			else
				result[resultIndex] = val + 97 - 10;
			resultIndex++;
			val = (word << 4);
			val = val >>4;
			if(val >= 0 && val <= 9)
				result[resultIndex] = val + 48;
			else
				result[resultIndex] = val + 97 - 10;
			resultIndex++;
		}
	}
	result[resultIndex] = '\0';
	resultIndex++;
	result[resultIndex] = 255;
	return result;
}

void printHexBytes(unsigned char* string)
{
	for(int i = 0; i < strlen(string);)
	{
		printf("%c", string[i]);
		i++;
		printf("%c ", string[i]);
		i++;
	}
	printf("\n");
}
void printString(unsigned char* string)
{
	for (int i = 0; i < strlen(string); i++)
	{
		if(string[i] != 255)
			printf("%c", string[i]);
	}
	printf("\n");
}

void printString_notNullTerminated(unsigned char* string)
{
	int i = 0;

	while(string[i] != 255)
	{
		printf("%c", string[i]);
		i++;
	}

	printf("\n");
}

void printBinaryString(unsigned char* binaryString)
{
	int index = 0;
	while(binaryString[index] != 255 || (binaryString[index] == 255 && binaryString[index + 1] != 0))
	{
		printf("%d,", binaryString[index]);
		index++;
	}
	printf("\n");
}

unsigned char* base64ToBinary(unsigned char* base64String)
{
	unsigned char* resultString;
	resultString = (unsigned char*)calloc((strlen(base64String) * (3/4)) + 1, sizeof(unsigned char));
	unsigned char tempWord;
	int resultStringPosition = 0;
	for(int index = 0; index < strlen(base64String);)
	{
		resultString[resultStringPosition] = reverseBase64Table(base64String[index]);
		resultString[resultStringPosition] = resultString[resultStringPosition] << 2;
		tempWord = reverseBase64Table(base64String[index + 1]);
		resultString[resultStringPosition] = resultString[resultStringPosition] | (tempWord >> 4);

		resultString[resultStringPosition + 1] = tempWord  << 4;
		tempWord = reverseBase64Table(base64String[index + 2]);
		resultString[resultStringPosition + 1] = resultString[resultStringPosition + 1] | (tempWord >> 2);

		resultString[resultStringPosition + 2] = tempWord << 6;
		tempWord = reverseBase64Table(base64String[index + 3]);
		resultString[resultStringPosition + 2] = resultString[resultStringPosition + 2] | tempWord;

		resultStringPosition = resultStringPosition + 3;
		index = index + 4;
	}
	resultString[resultStringPosition] = '\0';
	resultStringPosition++;
	resultString[resultStringPosition] = 255;
	resultStringPosition++;
	resultString[resultStringPosition] = 0;

	return resultString;
}

unsigned char reverseBase64Table(unsigned char val)
{
	if(val >= 65 && val <= 90)
		val = val - 65;
	else if(val >= 97 && val <= 122)
		val = val - 71;
	else if(val >= 48 && val <= 57)
		val = val + 4;
	else if(val == 43)
		val = val + 19;
	else if(val == 47)
		val = val + 16;
	else if(val == 61)
		val = 0;

	return val;
}

int strlenBinary(unsigned char* binaryString)
{
	int index = 0;
	while(binaryString[index] != 255)
	{
		index++;
	}

	return index;
}

void copyBlock(unsigned char* copyFromBlock, unsigned char* copyToBlock)
{
	for(int i = 0; i < strlenBinary(copyFromBlock); i++)
	{
		copyToBlock[i] = copyFromBlock[i];
	}
}

unsigned char* PKCS7_PAD(unsigned char* string, int length)
{
	unsigned char* paddedString;
	paddedString = (unsigned char*)malloc(length + 2);

	int stringLength = 0;
	int padByteValue = length - strlen(string);

	copyBlock(string, paddedString);

	for(int index = strlen(string); index < length; index++)
	{
		paddedString[index] = padByteValue;
	}

	paddedString[length ] = '\0';
	paddedString[length + 1] = 255;
	paddedString[length + 2] = 0;
	return paddedString;
}

unsigned char* CBC128_DECRYPT(unsigned char* binaryString, int binaryStringLength, unsigned char* key, unsigned char* IVBlock)
{
	unsigned char* block_1;
	block_1 = (unsigned char*)malloc(16 * sizeof(unsigned char));
	unsigned char* block_2;
	block_2 = (unsigned char*)malloc(16 * sizeof(unsigned char));

	unsigned char* decryptedBlock;
	decryptedBlock = (unsigned char*)malloc(16 * sizeof(unsigned char) + 2);

	unsigned char* XORBlock;

	int firstBlock = 1;
	unsigned char* result;
	result = (unsigned char*)malloc((binaryStringLength) + 3);

	for(int index = 0; index < binaryStringLength;)
	{
		block_1 = divideBlocks(index, 16, binaryString);

		AES128_ECB_decrypt(block_1, key, decryptedBlock);

		if(firstBlock == 1)
		{
			XORBlock = binaryStringXOR(decryptedBlock, IVBlock);
			firstBlock = 0;
		}
		else
		{
			XORBlock = binaryStringXOR(decryptedBlock, block_2);
		}

		appendBlock(index, XORBlock, result);

		copyBlock(block_1, block_2);
		index = index + 16;
	}

	result[binaryStringLength] = '\0';
	result[binaryStringLength + 1] = 255;

	return result;
}

unsigned char* CBC128_ENCRYPT(unsigned char* binaryString, int binaryStringLength, unsigned char* key, unsigned char* IVBlock)
{
	unsigned char* block_1;
	block_1 = (unsigned char*)malloc(16 * sizeof(unsigned char));
	unsigned char* block_2;
	block_2 = (unsigned char*)malloc(16 * sizeof(unsigned char));

	unsigned char* encryptedBlock;
	encryptedBlock = (unsigned char*)malloc(16 * sizeof(unsigned char) + 2);

	unsigned char* XORBlock;

	int firstBlock = 1;
	unsigned char* result;
	result = (unsigned char*)malloc((binaryStringLength) + 3);

	for(int index = 0; index < binaryStringLength;)
	{
		block_1 = divideBlocks(index, 16, binaryString);

		if(firstBlock == 1)
		{
			XORBlock = binaryStringXOR(block_1, IVBlock);
			firstBlock = 0;
		}
		else
		{
			XORBlock = binaryStringXOR(block_1, block_2);
		}

		AES128_ECB_encrypt(XORBlock, key, encryptedBlock);

		appendBlock(index, encryptedBlock, result);

		copyBlock(encryptedBlock, block_2);
		index = index + 16;
	}

	result[binaryStringLength] = '\0';
	result[binaryStringLength + 1] = 255;

	return result;
}

unsigned char* ECB128_DECRYPT(unsigned char* binaryString, int binaryStringLength, unsigned char* key)
{
	unsigned char* result;
	result = (unsigned char*)malloc((binaryStringLength) + 3);

	int count = 0;
	unsigned char* block;
	unsigned char* decryptedBlock;
	decryptedBlock = (unsigned char*)calloc((sizeof(unsigned char) * 16) + 3, sizeof(unsigned char));
	for(int index = 0; index < binaryStringLength;)
	{
		block = divideBlocks(index, 16, binaryString);
		AES128_ECB_decrypt(block, key, decryptedBlock);
		appendBlock(index, decryptedBlock, result);
		index = index + 16;
		count++;
	}
	result[(binaryStringLength) + 1] = '\0';

	result[(binaryStringLength) + 2] = 255;

	return result;
}

unsigned char* ECB128_ENCRYPT(unsigned char* binaryString, int binaryStringLength, unsigned char* key)
{
	unsigned char* result;
	result = (unsigned char*)malloc((binaryStringLength) + 3);

	unsigned char* block;
	unsigned char* encryptedBlock;
	encryptedBlock = (unsigned char*)calloc((sizeof(unsigned char) * 16) + 3, sizeof(unsigned char));
	for(int index = 0; index < binaryStringLength;)
	{
		block = divideBlocks(index, 16, binaryString);
		AES128_ECB_encrypt(block, key, encryptedBlock);
		appendBlock(index, encryptedBlock, result);
		index = index + 16;
	}
	result[(binaryStringLength) + 1] = '\0';
	result[(binaryStringLength) + 2] = 255;
	result[(binaryStringLength) + 3] = 0;

	return result;
}

unsigned char* RANDOM_ENCRYPT(unsigned char* binaryString, int binaryStringLength)
{
	srand(time(NULL));

	int randomAppendBlockLength = (rand() % 5) + 5;
	printf("%d\n", randomAppendBlockLength);
	unsigned char* paddedBinaryString;
	paddedBinaryString = (unsigned char*)calloc(binaryStringLength + (3 * randomAppendBlockLength), sizeof(unsigned char));

	unsigned char* randomAppendBlock;
	randomAppendBlock = (unsigned char*)calloc(randomAppendBlockLength + 2, sizeof(unsigned char));
	generateRandomString(randomAppendBlock, randomAppendBlockLength);
	printBinaryString(randomAppendBlock);

	appendBlock(0, randomAppendBlock, paddedBinaryString);
	appendBlock(randomAppendBlockLength, binaryString, paddedBinaryString);
	appendBlock(binaryStringLength + randomAppendBlockLength, randomAppendBlock, paddedBinaryString);
	paddedBinaryString[binaryStringLength + (2 * randomAppendBlockLength) + 1] = '\0';
	paddedBinaryString[binaryStringLength + (2 * randomAppendBlockLength) + 2] = 255;
	paddedBinaryString[binaryStringLength + (2 * randomAppendBlockLength) + 3] = 0;

	int paddedBinaryStringLength = strlen(paddedBinaryString);
	int pkcs7PaddedBinaryStringLength = paddedBinaryStringLength - (paddedBinaryStringLength % 16) + 16;

	unsigned char* pkcs7PaddedBinaryString;
	pkcs7PaddedBinaryString = PKCS7_PAD(paddedBinaryString, pkcs7PaddedBinaryStringLength);
	int randomNumber = rand() % 2;
	int IVBlockLength = 16;
	unsigned char* IVBlock;
	IVBlock = (unsigned char*)calloc(IVBlockLength + 2, sizeof(unsigned char));

	int keyLength = 16;
	unsigned char* key;
	key = (unsigned char*)calloc(keyLength + 2, sizeof(unsigned char));

	generateRandomString(key, keyLength);
	printBinaryString(key);

	printBinaryString(paddedBinaryString);
	printBinaryString(pkcs7PaddedBinaryString);

	if(randomNumber == 1)
	{
		printf("ECB ENCRYPTION\n");
		return ECB128_ENCRYPT(pkcs7PaddedBinaryString, pkcs7PaddedBinaryStringLength, key);
	}
	else
	{
		printf("CBC ENCRYPTION\n");
		return CBC128_ENCRYPT(pkcs7PaddedBinaryString, pkcs7PaddedBinaryStringLength, key, generateRandomString(IVBlock, IVBlockLength));
	}
}

int detectECB(unsigned char* string, int stringSize)
{
	int matchingCharacters = 0;
	int matchingCharactersBlock = 0;
	int highestScore = 0;

	int subBlockSize = 16;

	unsigned char* bestBlock;
	bestBlock = (unsigned char*)malloc(((stringSize) * sizeof(unsigned char)) + 2);

	int numberOfBlocks = stringSize / subBlockSize;

	unsigned char* block_1;
	block_1 = (unsigned char*)malloc(((subBlockSize) * sizeof(unsigned char)) + 2);
	unsigned char* block_2;
	block_2 = (unsigned char*)malloc(((subBlockSize) * sizeof(unsigned char)) + 2);

	for(int index_out = 0; index_out < numberOfBlocks; index_out++)
	{
		block_1 = divideBlocks(index_out * subBlockSize, subBlockSize, string);

		for(int index_in = (index_out + 1); index_in < numberOfBlocks; index_in++)
		{
			block_2 = divideBlocks(index_in * subBlockSize, subBlockSize, string);
			matchingCharacters = compareBlocks(block_1, block_2, subBlockSize);
			if(matchingCharacters == 16)
			{
				return 1;
			}
		}
	}
	return 0;
}
