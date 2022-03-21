#ifndef PPM_INFO
#define PPM_INFO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// structure that will contain the header information
// the image_t structure contains a header_t object in it
typedef struct header {
   char magicNum[3];  // will contain p6 for our programs
   int width, height, maxVal;
} header_t;


// represents an RGB pixel with integer values between 0-255
// the image_t structure contains a double pointer of this type
//		so, a pixel pointer that points to other pixel pointers
typedef struct pixel {
   unsigned char r, g, b;
} pixel_t;

// PPM Image representation
typedef struct image {
   header_t header;
   pixel_t** pixels;
} image_t;

typedef struct filePtr {
  FILE * theFile;
  char * imageFileName;
  image_t * theImage;
  struct filePtr * next;
} filePtr_t;


// prototypes
header_t read_header(FILE* image_file);
void write_header(FILE* out_file, header_t header);
image_t* read_ppm(FILE* image_file);
image_t* read_pixels(FILE* image_file, header_t header);
image_t* allocate_memory(header_t header);
int printMenu1();
filePtr_t* printList(filePtr_t* theList);
void gray_scale(filePtr_t* image, filePtr_t** theList, int count);
void mirror(filePtr_t* image, filePtr_t** theList, int count);
void green_screen(filePtr_t* image1, filePtr_t* image2,
                  filePtr_t** theList, int count);
void addToList(filePtr_t* frontOfList, FILE* newImage,
                             image_t* theNewImage, char* nameOfImage);
void write_p6(FILE* out_file, image_t* image1);


#endif
