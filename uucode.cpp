#include "uucode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CHAR_SIZE sizeof(char)
#define SIZE_OF_READ_IN_BUFFER 3 //Know for a fact that you'll be (trying) to read in 3 chars at a time
#define SIZE_OF_WRITE_OUT_BUFFER 4//Know for a fact that you'll be trying to read in 4 chars at a time   
#define SIZE_OF_ENCODED_TEXT_BUFFER 4  //Know for a fact that you'll be writing out 4 chars at a time to encoded file  
#define SIZE_OF_DECODED_TEXT_BUFFER 3 //Know for a fact that you'll be writing out 3 chars at a time when decoding
#define OFFSET 32  //Will try to add 32 to each 6-bit char generated from the 3 read characters
					//When less than 3 characters are read, pad the RIGHT with 0s




void encode(char a, char b, char c)
{
	char t1, t2, t3, t4;
	t1 &= 0;
	t2 &= 0;
	t3 &= 0;
	t4 &= 0;


	t1 = a;
	t1 >>= 2;
	t1 &= ~(3 << 6); //3 = 11 in binary, this 0's out the first two bits of encodedCharacters[0]
	
	t2 = a;
	t2 <<= 4;
	t2 &= ~(3 << 6);
	

	char temp = b;

	temp >>= 4;
	temp &= ~(15 << 4);  //15 = 1111 in binary, this 0's out the first 4 bits of temp
	//temp |= ~(3 << 6);  //3 = 11 in binary, this sets the 3rd and 4th bits to 1
	t2 |= temp;  //**  THE ISSUE SEEMS TO BE WITH THE 2nd ENCODED CHARACTER!!!


	t3 = b;

	t3 <<= 2;
	t3 &= (15 << 2);  //0's out the first 2 and last 2 bits
	 
	temp = c;
	temp >>= 6;  //Shift bits of temp to right
	temp &= ~(63 << 2);  //0 out 1st 6 bits of temp

	t3 |= temp;

	t4 = c;
	t4 &= ~(3 << 6); //0 out 1st 2 bits

	t1 += 32;
	t2 += 32;
	t3 += 32;
	t4 += 32;

	putchar(t1);
	putchar(t2);
	putchar(t3);
	putchar(t4);

}


void decode(char a, char b, char c, char d, FILE * file)
{
	char t1, t2, t3;
	t1 &= 0;
	t2 &= 0;
	t3 &= 0;
	t1 = a;
	t1 <<= 2;  //Shift left 2, guaranteed to 0 out last 2 digits
	char temp = b;
	temp >>= 6;  //If encoded properly, chars a-d shouls all have 2 leading 0's, so you're sure to 0 out the 1st 6 bits
	t1 |= temp;

	t2 = b;
	t2 <<= 4;

	temp = c;
	temp >>= 2;
	t2 |= temp;

	t3 = c;
	t3 <<= 6;
	t3 |= d;


	t1 -= 32;
	t2 -= 32;
	t3 -= 32;

	putc(t1, file);
	putc(t2, file);
	putc(t3, file);

}




int uuencode(const char *InputFilename, const char *RemoteFilename)
{
	// Text OR Binary file -> stdout file
	FILE * inputFile;
	inputFile = fopen(InputFilename, "rb");
	
	int numCharsInDocument = 0;
	int trash;
	
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
		//trash = getchar();
		fclose(inputFile);
	
		return -1;  //Error code of -1 for failing
	}
	
	else
	{ 
		while ((trash = fgetc(inputFile)) != EOF)
		{
			numCharsInDocument++;

		}
		rewind(inputFile);
		//puts( "begin 644 ");
		printf("begin 644 ");
		puts( RemoteFilename);
	
		//char * buffer = new char[SIZE_OF_READ_IN_BUFFER];
		//char * encodedText = new char[SIZE_OF_ENCODED_TEXT_BUFFER];

		//char  buffer[4] = { '0', '0', '0', '\0'};
		//char encodedText[5] = { '0', '0',  '0',  '0','\0' };

		char buffer[SIZE_OF_READ_IN_BUFFER] = { '1','1','1' };
		//char encodedText[SIZE_OF_ENCODED_TEXT_BUFFER];

		if (numCharsInDocument < 45)
		{
			putchar((numCharsInDocument + OFFSET));
		}

		else
		{
			putchar('M');
		}


		do {
			//Read file here
			

			numCharsRead = fread(buffer, CHAR_SIZE, SIZE_OF_READ_IN_BUFFER, inputFile);

			if (numCharsOnCurrentLine >= 45)
			{
				//Insert newline char, continue alg
				puts("\n");
				numCharsInDocument-= numCharsOnCurrentLine;
				
				if (numCharsInDocument < 45)
				{
					putchar((numCharsInDocument + OFFSET));
				}

				else
				{
					putchar('M');
				}
			}

			if (numCharsRead == 1)
			{
				encode((*(buffer)), '0', '0');
			}

			if (numCharsRead == 2)
			{
				encode((*(buffer)), (*(buffer + CHAR_SIZE)), '0');
			}

			if (numCharsRead == 3)
			{
				encode((*(buffer)), (*(buffer + CHAR_SIZE)), (*(buffer + (CHAR_SIZE*2))));
			}

		//	puts(encodedText);

		} while (numCharsRead > 0);
		//delete[] &buffer;   Don't need to delete array defined with {} brackets?
	}

	//Write last line(s)
	puts("\n`");
	puts("end");
	//Close file stream
	fclose(inputFile);
	


	return 0;

}


int uudecode(const char *InputFilename)
{
	//Text file -> decode and write to stdout
	FILE * inputFile = fopen(InputFilename, "r");
	int numCharsRead = 0;
	int numCharsOnCurrentLine = 60;
	int numCharsInDocument = 0;
	int trash;
	bool isLastLine = false;
	char * trashString = new char[10];
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
/*
	int lengthOfFilename = 0;
	char temp2 = 123;
	while (temp2 != NULL)
	{
	
		temp2 = *(InputFilename + lengthOfFilename);
		lengthOfFilename++;
	}
	lengthOfFilename += 3;
	*/
	//char * trashBuffer = new char[lengthOfFilename];


	//Read in first line--3 fseekf, to get through the 2 spaces and 1 newline?  Or can filenames have spaces in 'em?
	//Filenames cannot have spaces

	//Figure out the [filename].txt length, or just set it to a large-ish size and leave it at that?
	char * outputFilename = new char[53];
	//char * decodedText = new char[SIZE_OF_DECODED_TEXT_BUFFER];
	if (!inputFile)
	{
		perror(InputFilename);
		printf("Error:  file cannot be opened to be read.\n");
		fclose(inputFile);
		trash = getchar();
		return -1;  //Error code of -1 for failing
	}

	else
	{
		fscanf(inputFile, "%s", trashString);
		fscanf(inputFile, "%s",trashString);
		delete trashString;
		fscanf(inputFile, "%s", outputFilename);

		FILE * outputFile = fopen(outputFilename, "wb");  //Double check this--wb for write binary or just w?

		char buffer[SIZE_OF_WRITE_OUT_BUFFER] = { '0', '0', '0', '\0' };

		numCharsOnCurrentLine = (fgetc(inputFile) - 32);

		do {
			//Read file here
			if (numCharsRead >= numCharsOnCurrentLine)
			{//Next character should be the first character in a line--the # of characters in that line
				numCharsOnCurrentLine = (fgetc(inputFile)) - OFFSET;


			}

			if (numCharsOnCurrentLine == 0)
			{
				isLastLine = true;
				puts("\n");
			}

			else
			{
				fscanf(inputFile, "%4c", buffer);
				//fputs(decodedText, outputFile);
				numCharsRead += 4;

			}

			//numCharsRead = fread(buffer, CHAR_SIZE, SIZE_OF_WRITE_OUT_BUFFER, inputFile);

			/*
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
			*/
		} while (!isLastLine);

		//Write last line(s)
		//Close file streams
		delete outputFilename;
	//	delete[] &buffer;
		//delete[] &decodedText;
		

	}

	fclose(inputFile);
	return 0;
}