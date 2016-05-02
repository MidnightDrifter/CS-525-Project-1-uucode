#include <stdio.h>  /* printf */
#include <stdlib.h> /* atoi   */
#include "uucode.h"

int main(int argc, char **argv)
{
  int mode;

    /* If less than 1 argument is provided, remind the user */
    /* how to use the program.                              */
  if (argc < 3)
  {
    printf("\n");
    printf("  Usage: uucode {mode} {inputfile} [decode_path]\n\n");
    printf("  mode = 1 for encoding, 2 for decoding\n");
    printf("  inputfile = file to encode/decode\n");
    printf("  decode_path = filename to store in encoded file (only for encoding)\n\n");
    printf("  Examples: uucode preamble.txt mypreamble.txt > preamble.uue\n");
    printf("            uucode preamble.uue\n\n");
    return -1;
  }

    /* First argument is the mode, 1=encode, 2=decode */
  mode = atoi(argv[1]);

    /* Encode */
  if (mode == 1) 
  {
      /* If only 2 args, the input/remote filename are the same */
    if (argc == 3)
    {
      if (uuencode(argv[2], argv[2]))
        printf("Encoding failed: %s, %s\n", argv[2], argv[2]);
    }
      /* The input filename and remote filename are different   */
    else 
    {
      if (uuencode(argv[2], argv[3]))
        printf("Encoding failed: %s, %s\n", argv[2], argv[3]);
    }
  }
    /* Decode */
  else if (mode == 2)
  {
    if (uudecode(argv[2]))
      printf("Decoding failed: %s\n", argv[2]);
  }
  else  
  {
    printf("Bad mode: %i  Should be 1 or 2.\n", mode);
  }
  return 0;
}
