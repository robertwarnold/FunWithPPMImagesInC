#include "ppm_info.h"

void gray_scale(filePtr_t *image, filePtr_t **theList, int count) { /* The purpose of this function is to get the avg of the colors of each pixel in the file and assign that to the pixel this
makes the colors in the image gray, effectively gray scaling the image. */
int row = 0;
int col = 0;
int avg = 0;
   header_t header = image->theImage->header;
   image_t *resultImage = allocate_memory(header);

   resultImage->header = header;

   char fileName[30] = "g";

  strcat(fileName, image->imageFileName);


     if(fileName[1] != 'g'){
     char buf[5];
     fileName[strlen(fileName)-4] = '\0';
     int length = snprintf(buf,5, "%d", count);
     char *imageName = (char *)malloc(length);
     sprintf(imageName, "%s%02d.ppm", fileName, count);

     FILE *grayOutput = fopen(imageName, "w");
     if(!grayOutput){
        fprintf(stderr, "grayed image file could not open\n\n");

        exit(1);
     }


   for(row = 0; row < header.height; row++) {
      for(col = 0; col < header.width; col++) {
      // calculate the average of the r, g, b values for the pixel
      avg = ( image->theImage->pixels[row][col].r +
              image->theImage->pixels[row][col].g +
              image->theImage->pixels[row][col].b ) / 3;

      // assign avg to each r, g, b value of the pixel

       resultImage->pixels[row][col].r = avg;
       resultImage->pixels[row][col].g = avg;
       resultImage->pixels[row][col].b = avg;
     }
   }
     // after declaring a new image_t and allocating memory for it:
     write_p6(grayOutput, resultImage);
     fclose(grayOutput);
     addToList(image, grayOutput, resultImage, imageName);
}
}

//The purpose of this function is to mirror the image along the y-axis.
void mirror(filePtr_t *image, filePtr_t **theList, int count){
   int row = 0;
   int col = 0;
   header_t header = image->theImage->header;
   image_t *resultImage = allocate_memory(header);
   resultImage->header = header;

   char fileName[30] = "m";
   strcat(fileName, image->imageFileName);

   // if the 2nd letter is a lower case 'g', then it already exists
   if(fileName[1] != 'm') {
     char buf[5];
     fileName[strlen(fileName)-4] = '\0';
     //int length = snprintf(buf, 5, "%d", count);
     char* imageName = (char*)malloc(50);
     sprintf(imageName, "%s%02d.ppm", fileName, count);
     FILE* mirroredImage = fopen(imageName, "w");
     if (!mirroredImage) {
       fprintf(stderr, "grayed image file could not open\n\n");
       exit(1);
     }
     for(row = 0; row < header.height; row++){
       for(col = 0; col < header.width; col++){
         resultImage->pixels[row][col] = image->theImage->pixels[row][header.width - 1 - col];
         resultImage->pixels[row][header.width - 1 - col] = image->theImage->pixels[row][col];
     }
   }
   write_p6(mirroredImage, resultImage);
   fclose(mirroredImage);
   addToList(image, mirroredImage, resultImage, imageName);
   }
 }

//The purpose of this function is to seperate the orange tiger paw logo pixel by pixel from the purple background.
void green_screen (filePtr_t* image1, filePtr_t* image2, filePtr_t** theList, int count) {
	int row, col = 0;


   header_t header = image1->theImage->header;

	// Create new image
	image_t* newImage = allocate_memory(header);

	// Create new file and open for writing
	char fileName[30] = "gs"; // for green screen
	strcat(fileName, image2->imageFileName);

	// see if image already exists in list, if g is second, then yes
	if ((fileName[2] != 'g') && (fileName[3] != 's')) {
		char buf[5];
		fileName[strlen(fileName)-4] = '\0';
		int length = snprintf(buf, 5, "%d", count);
		// snprintf(buf, 5, "%d", count);
		char* imageName = (char*)malloc(length + 1);
		sprintf(imageName, "%s%02d.ppm", fileName, count);

		FILE* gsImage = fopen(imageName, "w");
		if (!gsImage) {
			fprintf(stderr, "green screen image file could not open\n\n");
			exit(1);
		}

		// copy header info over
		newImage->header = header;

		// green screen algorithm
		for (row = 0; row < header.height; row++) {
			for (col = 0; col < header.width; col++) {
				// check image2's pixel value for green
				if ((image1->theImage->pixels[row][col].g == 255) &&
					((image1->theImage->pixels[row][col].b == 0) &&
					(image1->theImage->pixels[row][col].r == 0))) {
					newImage->pixels[row][col] = image2->theImage->pixels[row][col];
				}

				// otherwise
				else {
					newImage->pixels[row][col] = image1->theImage->pixels[row][col];
				}
			}
		}
		// call write_p6 with new image
		write_p6(gsImage, newImage);
		fclose(gsImage);

		//add to list
		addToList(*theList, gsImage, newImage, imageName);
	}
}


void addToList(filePtr_t * frontOfList, FILE *newImage, image_t *theNewImage, char *nameOfImage){
  //create a newfilePtr_t nodeusing the parameters newImage,nameOfImage, and theNewImage to initialize the fields, along withNULL for the nextpointer
  filePtr_t * addNode  = (filePtr_t*) malloc(sizeof(filePtr_t));

      addNode->theFile = newImage;

      addNode->imageFileName = nameOfImage;

      addNode->theImage = theNewImage;

      addNode->next = NULL;


  filePtr_t *currentNode = frontOfList;

  if(currentNode == NULL){
    frontOfList = addNode;
  }
  else{
    while(currentNode->next != NULL){
      currentNode = currentNode->next;
    }
    currentNode->next = addNode;
  }
}
