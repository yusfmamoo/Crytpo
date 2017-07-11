/*
 * conversions.h
 *
 *  Created on: Oct 25, 2016
 *      Author: yusufm
 */

#ifndef CONVERSIONS_H_
#define CONVERSIONS_H_

#include <time.h>
#include <stdlib.h>

unsigned char* hexToBinary(char *hexString);
unsigned char* binaryToBase64(unsigned char* binaryResult);
unsigned char base64Table(unsigned char val);
unsigned char* binaryToHex(unsigned char* binaryString);
void printString(unsigned char* string);
unsigned char* base64ToBinary(unsigned char* base64String);
unsigned char reverseBase64Table(unsigned char val);
void printBinaryStrng(unsigned char* binaryString);
int strlenBinary(unsigned char* binaryStrnig);
unsigned char* binaryToHex_notNullTerminated(unsigned char* binaryString);
void printHexBytes(unsigned char* string);
void copyBlock(unsigned char* copyFromBlock, unsigned char* copyToBlock);
int detectECB(unsigned char* string, int stringSize);
unsigned char* PKCS7_PAD(unsigned char* string, int length);
unsigned char* CBC128_DECRYPT(unsigned char* binaryString, int binaryStringLength, unsigned char* key, unsigned char* IVBlock);
unsigned char* CBC128_ENCRYPT(unsigned char* binaryString, int binaryStringLength, unsigned char* key, unsigned char* IVBlock);
unsigned char* ECB128_DECRYPT(unsigned char* binaryString, int binaryStringLength, unsigned char* key);
unsigned char* ECB128_ENCRYPT(unsigned char* binaryString, int binaryStringLength, unsigned char* key);
unsigned char* RANDOM_ENCRYPT(unsigned char* binaryString, int binaryStringLength);
#endif /* CONVERSIONS_H_ */
