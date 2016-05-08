#include "uucode.h"
#include <stdio.h>
#include <string.h>
#define CHAR_SIZE sizeof(char)
#define SIZE_OF_READ_IN_BUFFER 3  //Know for a fact that you'll be (trying) to read in 3 chars at a time
#define SIZE_OF_WRITE_OUT_BUFFER 4//Know for a fact that you'll be trying to read in 4 chars at a time
#define OFFSET 32  //Will try to add 32 to each 6-bit char generated from the 3 read characters
					//When less than 3 characters are read, pad the RIGHT with 0s

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
				//Insert newline char, continue alg
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
	FILE * inputFile = fopen(InputFilename, "r");
	int numCharsRead = 0;
	int numCharsOnCurrentLine = 0;
	int numCharsInDocument = 0;
	int trash;
	char A, B, C, w, x, y, z;
	w &= 0;
	x &= 0;
	y &= 0;
	z &= 0;
	A &= 0;
	B &= 0;
	C &= 0;

	fpos_t startOfFile;
	fgetpos(inputFile, &startOfFile);

	while ((trash = fgetc(inputFile)) != EOF)
	{
		numCharsInDocument++;

	}
	fsetpos(inputFile, &startOfFile);

	int lengthOfFilename = 0;
	char temp2 = 123;
	while (temp2 != NULL)
	{
	
		temp2 = *(InputFilename + lengthOfFilename);
		lengthOfFilename++;
	}
	lengthOfFilename += 3;

	char * trashBuffer = new char[lengthOfFilename];

	//Read in first line--3 fseekf, to get through the 2 spaces and 1 newline?  Or can filenames have spaces in 'em?


	if (!inputFile)
	{
		perror(InputFilename);
		printf("Error:  file cannot be opened to be read.\n");
		fclose(inputFile);
		
		return -1;  //Error code of -1 for failing
	}

	else
	{
		do {
			//Read file here
			char * buffer = new char[SIZE_OF_WRITE_OUT_BUFFER];

			//numCharsRead = fread(buffer, CHAR_SIZE, SIZE_OF_WRITE_OUT_BUFFER, inputFile);


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