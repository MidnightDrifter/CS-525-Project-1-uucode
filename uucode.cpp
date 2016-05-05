#include "uucode.h"
#include <stdio.h>
#include <string.h>
#define CHAR_SIZE sizeof(char)
#define SIZE_OF_BUFFER 3  //Know for a fact that you'll be (trying) to read in 3 chars at a time

int uuencode(const char *InputFilename, const char *RemoteFilename)
{
	// Text OR Binary file -> text file
	FILE * inputFile = fopen(InputFilename, "rb");
	FILE * outputFile = fopen(RemoteFilename, "w");

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
		//Read file here
		char * buffer = new char[SIZE_OF_BUFFER];


	}


}


int uudecode(const char *InputFilename)
{
	//Text file -> decode and write to stdout

	FILE * inputFile = fopen(InputFilename, "r");
}