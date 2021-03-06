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
	t2 |= temp;  


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


	//ASCII 32 = SPACE, want ` instead
	if (t1 == 32)
	{
		t1 = '`';
	}
	if (t2 == 32)
	{
		t2 = '`';
	}
	if (t3 == 32)
	{
		t3 = '`';
	}
	if (t4 == 32)
	{
		t4 = '`';
	}

	putchar(t1);
	putchar(t2);
	putchar(t3);
	putchar(t4);

}


void decode(char a, char b, char c, char d, FILE * file)
{
	char t1, t2, t3, tA, tB, tC, tD;

	tA = a - 32;
	tB = b - 32;
	tC = c - 32;
	tD = d - 32;


	t1 &= 0;
	t2 &= 0;
	t3 &= 0;
	t1 = tA;
	t1 <<= 2;  //Shift left 2, guaranteed to 0 out last 2 digits
	char temp = tB;
	temp &= ~(3 << 6);
	temp >>= 4;  //If encoded properly, chars a-d should all have 2 leading 0's, so you're sure to 0 out the 1st 6 bits.  0 them out manually to be sure
	t1 |= temp;

	t2 = tB;
	t2 <<= 4;

	temp =tC;
	temp &= ~(3 << 6);
	temp >>= 2;
	t2 |= temp;

	t3 = tC;
	t3 <<= 6;
	temp = tD;
	temp &= ~(3 << 6);
	t3 |= temp;


	//t1 += 32;
	//t2 += 32;
	//t3 += 32;
	if (t1 != '\0')
	{
		putc(t1, file);
	}
	if (t2 != '\0')
	{
		putc(t2, file);
	}
	if (t3 != '\0')
	{
		putc(t3, file);
	}

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

		//char buffer[SIZE_OF_READ_IN_BUFFER] = { '1','1','1' };
		//char encodedText[SIZE_OF_ENCODED_TEXT_BUFFER];
		char * buffer = new char[3];

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
				putchar('\n');
				numCharsInDocument-= numCharsOnCurrentLine;
				numCharsOnCurrentLine = 0;
				
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
				encode((*(buffer)), '\0', '\0');
			}

			if (numCharsRead == 2)
			{
				encode((*(buffer)), (*(buffer + CHAR_SIZE)), '\0');
			}

			if (numCharsRead == 3)
			{
				encode((*(buffer)), (*(buffer + CHAR_SIZE)), (*(buffer + (CHAR_SIZE*2))));
			}
			numCharsOnCurrentLine += 3;
		//	puts(encodedText);

		} while (numCharsRead > 0);
		delete[] buffer;  // Don't need to delete array defined with {} brackets?
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
	int numCharsOutputted = 0;
	int numCharsOnCurrentLine = 60;
	//int numCharsInDocument = 0;
	//int trash;
	//bool isLastLine = false;
	char * trashString = new char[10];
	char A, B, C, w, x, y, z;
	w &= 0;
	x &= 0;
	y &= 0;
	z &= 0;
	A &= 0;
	B &= 0;
	C &= 0;

	


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
		return -1;  //Error code of -1 for failing
	}

	else
	{
		fscanf(inputFile, "%s", trashString);
		fscanf(inputFile, "%s",trashString);
		delete[] trashString;
		fscanf(inputFile, "%s", outputFilename);

		FILE * outputFile = fopen(outputFilename, "wb");  //Double check this--wb for write binary or just w?

		//char buffer[SIZE_OF_WRITE_OUT_BUFFER] = { '0', '0', '0', '0' };
		char * buffer = new char[4];
		fgetc(inputFile);  //get rid of newline char
		//numCharsOnCurrentLine = (fgetc(inputFile) - OFFSET);
		numCharsOnCurrentLine = fgetc(inputFile)-32; //Need to subtract 2 to account for the newline characters?

		do {
			//Read file here
			if (numCharsOutputted >= numCharsOnCurrentLine)
			{
				//fputc('\n', outputFile);
				//Next character should be a newline, then the first character in a line--the # of characters in that line
				
				//numCharsInDocument -= numCharsRead;
				//numCharsRead = fgetc(inputFile);  //Setting it to 0 anyways, so just trash the '\n' character here
				numCharsOnCurrentLine = (fgetc(inputFile)) - 32;
				numCharsOutputted = 0;


			}

	

			else
			{
				//fscanf(inputFile, "%4c", buffer);
				//fputs(decodedText, outputFile);
				//fgets(buffer, 4, inputFile);
				/*int i;
				char tempThing;
				for (i = 0; i < 4; i++)
				{
					tempThing = fgetc(inputFile);
					(*(buffer + (CHAR_SIZE*i))) = tempThing;
				}
				*/

				fread(buffer, CHAR_SIZE, 4, inputFile);
				decode((*buffer), (*(buffer + sizeof(char))), (*(buffer + sizeof(char) * 2)), (*(buffer + sizeof(char) * 3)), outputFile);
				numCharsOutputted += 3;  

			}

			
		} while (numCharsOnCurrentLine != 64);

		//Write last line(s)
		//Close file streams
		
		delete[] buffer;
		
		delete[] outputFilename;
		//delete[] &decodedText;
		

	}

	fclose(inputFile);
	return 0;
}