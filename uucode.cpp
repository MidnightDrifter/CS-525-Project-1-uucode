#include "uucode.h"
#include <stdio.h>
#include <string.h>
#define CHAR_SIZE sizeof(char)
#define SIZE_OF_READ_IN_BUFFER 3  //Know for a fact that you'll be (trying) to read in 3 chars at a time
#define SIZE_OF_WRITE_OUT_BUFFER 4//Know for a fact that you'll be trying to read in 4 chars at a time
#define OFFSET 32  //Will try to add 32 to each 6-bit char generated from the 3 read characters
					//When less than 3 characters are read, pad the LEFT with 0's?

int uuencode(const char *InputFilename, const char *RemoteFilename)
{
	// Text OR Binary file -> text file
	FILE * inputFile = fopen(InputFilename, "rb");
	FILE * outputFile = fopen(RemoteFilename, "w");
	int numCharsRead = 0;
	int numCharsOnCurrentLine = 0;
	char a, b, c, d;
	a &= 0;
	b &= 0;
	c &= 0;
	d &= 0;

	if (!inputFile)
	{
		perror(InputFilename);
		printf("Error:  file cannot be opened to be read.\n");
		fclose(inputFile);
		fclose(outputFile);
		return -1;  //Error code of -1 for failing
	}
	
	else
	{
		do {
			//Read file here
			char * buffer = new char[SIZE_OF_READ_IN_BUFFER];

			numCharsRead = fread(buffer, CHAR_SIZE, SIZE_OF_READ_IN_BUFFER, inputFile);

			if (numCharsOnCurrentLine >= 45)
			{
				//Move to new line and continue alg.
			}

			if (numCharsRead == 1)
			{

			}

			if (numCharsRead == 2)
			{

			}

			if (numCharsRead == 3)
			{

			}

		} while (numCharsRead > 0);
	}
	
	//Write last line(s)
	
	//Close file streams
	fclose(inputFile);
	fclose(outputFile);

}


int uudecode(const char *InputFilename)
{
	//Text file -> decode and write to stdout

	int numCharsRead = 0;
	int numCharsOnCurrentLine = 0;
	char x, y, z;
	x &= 0;
	y &= 0;
	z &= 0;


	FILE * inputFile = fopen(InputFilename, "r");
	//Read in output file name from file
	//Make file
	char * outputFilename = "";
	FILE * outputFile = fopen(outputFilename, "w+");


	if (!inputFile)
	{
		perror(InputFilename);
		printf("Error:  file cannot be opened to be read.\n");
		fclose(inputFile);
		fclose(outputFile);
		return -1;  //Error code of -1 for failing
	}

	else
	{
		do {
			//Read file here
			char * buffer = new char[SIZE_OF_WRITE_OUT_BUFFER];

			numCharsRead = fread(buffer, CHAR_SIZE, SIZE_OF_WRITE_OUT_BUFFER, inputFile);


			if (numCharsRead == 1)
			{

			}

			if (numCharsRead == 2)
			{

			}

			if (numCharsRead == 3)
			{

			}

			if (numCharsRead == 4)
			{

			}

		} while (numCharsRead > 0);

		//Write last line(s)
		//Close file streams

		fclose(inputFile);


}