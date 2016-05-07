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
\brief
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




#endif