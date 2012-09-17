/* 2base10.cpp - convert number to base 10

This program converts a given number into base 10. Interpretation of numbers
in bases greater than 10 uses the same convention as hexidecimal numbers, extending
the range from A-F all the way up to Z (or shrinking it), allowing this program to
convert numbers up to base 36 into base 10.

Future versions will support converting numbers between arbitrary bases.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define DEFAULT_LENGTH	16

typedef unsigned int	intu;

enum ERRORS
{
	NO_ERROR, // should default to 0
	ERR_NOARGS,
	ERR_INVALIDCHAR,
	ERR_OUTOFRANGE,
};

#include "converter.cpp"

void printCStr(char* str,bool printErr)
{
	while (1)
	{
		char m = *str++;
		if (!m) { break; }
		fprintf(printErr?stderr:stdout,"%c",m);
	}
}

void interactiveModePrompt(char* inNumber, intu &base)
{
	intu len = DEFAULT_LENGTH;
	printf("Please specify your number (maximum length %u): ",len);
	scanf("%16s",inNumber);
	do
	{
		printf("Please specify the base of this number (valid range is 2-36): ");
		scanf("%u",&base);
	} while (base > 36 && base < 2);
}

int main(int argc, char** argv)
{
	char * inputNumber;
	intu originBase;
	if (argc==1)
	{
		inputNumber = (char*) malloc (DEFAULT_LENGTH);
		interactiveModePrompt(inputNumber, originBase);
		printf("%u\n",convertToDecimal(inputNumber,originBase));
	}
	else if (argc==2)
	{
		if (!strcmp(argv[1],"--help")||!strcmp(argv[1],"-h"))
		{
			printCStr(argv[0],0);		
			printf(" [input-number] [original-base]\n"
				"\n"
				"Both arguments are optional, in which case the program launches\n"
				"interactive move. However, you must supply both arguments if you\n"
				"choose not to run interactive mode.\n"
				"\n"
				"input-number: a number of arbitrary base to be converted into base 10.\n"
				"\tIf larger than base 10, use A-Z or a-z for digits greater than 9.\n"
				"\tThe program will complain if the variable contains any other values\n"
				"\tor starts with a 0.\n"
				"\n"
				"original-base: the number of this base for conversion purposes. Because\n"
				"\tthe program uses A-Z for digits larger than 9, you cannot specify a base\n"
				"\tlarger than 36 for this number. The program will complain if you exceed\n"
				"\tthis value.\n");
			exit(NO_ERROR);
		}
		fprintf(stderr,"Incorrect usage.\n"
				"This program requires either zero arguments to enter interactive mode,"
				"or two arguments to enter automatic mode.\n"
				"Usage:");
		printCStr(argv[0],1);
		fprintf(stderr," [input-number] [original-base]\n"
			"\n"
			"You may specify \"--help\" or \'-h\' as the first argument if you do not"
			"know what sorts of input the program expects to see.\n");
		exit(ERR_NOARGS);
	}
	else
	{
		inputNumber = (char*) malloc (strlen(argv[0]));
		originBase = static_cast<intu>(atoi(argv[1]));
		printf("%u\n",convertToDecimal(inputNumber,originBase));
	}
	return 0;
}
