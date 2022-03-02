/*************************
 *Robert Arnold
 *CPSC 2311 - 005
 *Spring 22
 *rwarnol@clemson.edu
 *************************/
#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"


int main(int argc, char* argv[]) 
{
  if(argc != 4)
  {
    fprintf(stderr, "Wrong number of args");
  }

	// declares file pointers
	FILE* oldImage = fopen(argv[1], "r");
	FILE* flippedImage = fopen(argv[2], "w");
  FILE* grayedOutput = fopen(argv[3], "w");



	// check that the files opened successfully
   if(!flippedImage || !grayedOutput) 
   {
      fprintf(stderr, "ERROR: File(s) could not be opened.\n");
      return -1;
   }

  readHeader(image_file);
  readPPM(image_file, header);
  writeP6Image(header, pixels, image_file);
  grayScaleImage(header, pixels, image_file);
  flipImage(header, pixels, image_file);
  allocateMemory(header);
  freeMemory(pixels, header);

   return 0;
}
