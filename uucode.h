/**
\file UUCODE.H
\author Sean Higgins
\date 5-16-2015
\brief 





*/



//#pragma once
#ifndef UUCODE_H
#define UUCODE_H


/**
\brief  Given a filename, write the remote filename and the encoded text of the given filename
\param const char * InputFilename  A string containing the name of the file to be encoded.
\param const char * RemoteFilename  A string containing the name of the output file to encode to.
\return int  Return -1 on failure, 0 on success
*/

int uuencode(const char *InputFilename, const char *RemoteFilename);

/**

\brief
\param const char *InputFilename  A string containing the name of the file to be decoded
\return int  Return -1 on failue, 0 on success
*/


int uudecode(const char *InputFilename);


/**
\brief  Encode characters in groups of 3
\param chars a, b, c   The input characters to encode via the uuencode algorithm
\param char * encodedCharacters  Pointer to a character array to store the encoded characters in--I KNOW the array will have a size of 4, as I'm setting it in my implementation
\return  N/A

*/
void encode(char a, char b, char c, char * encodedCharacters);


/**
\brief  Decode characters in groups of 3
\param chars a, b, c, d   The input characters to decode via the uudecode algorithm
\param char * decodedCharacters   Pointer to the array to store the decoded characters in--I KNOW it will have a size of 3, as I'm setting it in my implementation
\return  N/A
*/
void decode(char a, char b, char c, char d, char * decodedCharacters);





#endif