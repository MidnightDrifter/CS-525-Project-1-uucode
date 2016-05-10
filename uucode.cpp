#include "uucode.h"
#include <stdio.h>
#include <string.h>
#define CHAR_SIZE sizeof(char)
#define SIZE_OF_READ_IN_BUFFER 3  //Know for a fact that you'll be (trying) to read in 3 chars at a time
#define SIZE_OF_WRITE_OUT_BUFFER 4//Know for a fact that you'll be trying to read in 4 chars at a time
#define SIZE_OF_ENCODED_TEXT_BUFFER 4  //Know for a fact that you'll be writing out 4 chars at a time to encoded file
#define SIZE_OF_DECODED_TEXT_BUFFER 3 //Know for a fact that you'll be writing out 3 chars at a time when decoding
#define OFFSET 32  //Will try to add 32 to each 6-bit char generated from the 3 read characters
					//When less than 3 characters are read, pad the RIGHT with 0s




void encode(char a, char b, char c, char * encodedCharacters)
{
	*encodedCharacters = a;
	(*encodedCharacters) >>= 2;
	(*encodedCharacters) &= ~(3 << 6); //3 = 11 in binary, this 0's out the first two bits of encodedCharacters[0]
	*(encodedCharacters + (sizeof(char)) )= a;
	*(encodedCharacters + (sizeof(char))) << 4;
	*(encodedCharacters + (sizeof(char))) &= ~(3 << 6);

	char temp = b;

	temp >> 4;
	temp &= ~(15 << 4);  //15 = 1111 in binary, this 0's out the first 4 bits of temp
	temp |= ~(3 << 6);  //3 = 11 in binary, this sets the 3rd and 4th bits to 1

	*(encodedCharacters + (sizeof(char))) |= temp;


	*(encodedCharacters + (sizeof(char) * 2)) = b;

	(*(encodedCharacters + (sizeof(char) * 2))) <<= 2;
	(*(encodedCharacters + (sizeof(char) * 2))) &= (15 << 2);  //0's out the first 2 and last 2 bits
	 
	temp = c;
	temp >>= 6;  //Shift bits of temp to right
	temp &= ~(63 << 2);  //0 out 1st 6 bits of temp

	(*(encodedCharacters + (sizeof(char) * 2))) |= temp;

	(*(encodedCharacters + (sizeof(char) * 3))) = c;
	(*(encodedCharacters + (sizeof(char) * 3))) &= ~(3 << 6); //0 out 1st 2 bits

		int i;
	for (i = 0; i < 4; i++)
	{
		if ((*(encodedCharacters + (sizeof(char)*i))) == 0)
		{
			(*(encodedCharacters + (sizeof(char)*i))) = 96;
		}

		else
		{
			(*(encodedCharacters + (sizeof(char)*i))) += 32;
		}

	}


}


void decode(char a, char b, char c, char d, char * decodedCharacters)
{
	*decodedCharacters = a;
	*decodedCharacters <<= 2;  //Shift left 2, guaranteed to 0 out last 2 digits
	char temp = b;
	temp >>= 6;  //If encoded properly, chars a-d shouls all have 2 leading 0's, so you're sure to 0 out the 1st 6 bits
	*decodedCharacters |= temp;

	*(decodedCharacters + (sizeof(char))) = b;
	*(decodedCharacters + (sizeof(char))) <<= 4;

	temp = c;
	temp >>= 2;
	*(decodedCharacters + (sizeof(char))) |= temp;

	*(decodedCharacters + (sizeof(char) * 2)) = c;
	*(decodedCharacters + (sizeof(char) * 2)) <<= 6;
	*(decodedCharacters + (sizeof(char) * 2)) |= d;


	int i;
	for (i = 0; i < 3; i++)
	{
		if ((*(decodedCharacters + (sizeof(char)*i))) == 64)
		{	//It's a space?  uuuhhh...
			(*(decodedCharacters + (sizeof(char)*i))) = 32;
		}

		else
		{
			(*(decodedCharacters + (sizeof(char)*i))) -= 32;

		}
	
	}
}




int uuencode(const char *InputFilename, const char *RemoteFilename)
{
	// Text OR Binary file -> text file
	FILE * inputFile = fopen(InputFilename, "rb");
	
	int numCharsInDocument = 0;
	int trash;
	int len = strlen(InputFilename);  //Get the filename, copy it, change the copy to end in ".uue"
	char * uueFile = new char[len];
	strcpy(uueFile, InputFilename);
	*(uueFile + (sizeof(char) - 4)) = '.';
	*(uueFile + (sizeof(char) - 3)) = 'u';
	*(uueFile + (sizeof(char) - 2)) = 'u';
	*(uueFile + (sizeof(char) - 1)) = 'e';


	FILE * outputFile = fopen(uueFile, "w");  //Double check later, might need to use w+ instead
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
		delete uueFile;
		return -1;  //Error code of -1 for failing
	}
	
	else
	{ 
		while ((trash = fgetc(inputFile)) != EOF)
		{
			numCharsInDocument++;

		}
		rewind(inputFile);
		fprintf(outputFile, "begin 644 ");
		fprintf(outputFile, RemoteFilename);
		fprintf(outputFile, "\n");
		char * buffer = new char[SIZE_OF_READ_IN_BUFFER];
		char * encodedText = new char[SIZE_OF_ENCODED_TEXT_BUFFER];

		if (numCharsInDocument < 45)
		{
			putc((numCharsInDocument + 32), outputFile);
		}

		else
		{
			putc('M', outputFile);
		}

		do {
			//Read file here
			

			numCharsRead = fread(buffer, CHAR_SIZE, SIZE_OF_READ_IN_BUFFER, inputFile);

			if (numCharsOnCurrentLine >= 45)
			{
				//Insert newline char, continue alg
				fprintf(outputFile, "\n");
				numCharsInDocument-= numCharsOnCurrentLine;
				
				if (numCharsInDocument < 45)
				{
					putc((numCharsInDocument + 32), outputFile);
				}

				else
				{
					putc('M', outputFile);
				}
			}

			if (numCharsRead == 1)
			{
				encode((*(buffer)), '0', '0', encodedText);
			}

			if (numCharsRead == 2)
			{
				encode((*(buffer)), (*(buffer + CHAR_SIZE)), '0', encodedText);
			}

			if (numCharsRead == 3)
			{
				encode((*(buffer)), (*(buffer + CHAR_SIZE)), (*(buffer + (CHAR_SIZE*2))), encodedText);
			}

			fprintf(outputFile, buffer);

		} while (numCharsRead > 0);
		delete buffer;
	}
	
	//Write last line(s)
	fprintf(outputFile,"`\n");
	fprintf(outputFile, "end\n");
	//Close file streams
	fclose(inputFile);
	fclose(outputFile);

	//Delete various char arrays
	delete uueFile;
	

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



	while ((trash = fgetc(inputFile)) != EOF)
	{
		numCharsInDocument++;

	}
	rewind(inputFile);

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