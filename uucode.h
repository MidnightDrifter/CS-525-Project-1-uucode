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
\param const char * InputFilename
\param const char * RemoteFilename
\return int
*/

int uuencode(const char *InputFilename, const char *RemoteFilename);

/**

\brief
\param const char *InputFilename
\return int
*/


int uudecode(const char *InputFilename);




#endif