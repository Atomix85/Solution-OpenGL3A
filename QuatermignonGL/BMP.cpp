#include "BMP.h"

 
unsigned char* BMP::LoadBitmapFile(const char* filename, INFOHEADER* bitmapInfoHeader)
{
	FILE* filePtr; //our file pointer
	HEADER bitmapFileHeader; //our bitmap file header
	unsigned char* bitmapImage;  //store image data
	int imageIdx = 0;  //image index counter
	unsigned char tempRGB;  //our swap variable

	//open filename in read binary mode
	filePtr = fopen(filename, "rb");
	if (filePtr == NULL)
		return NULL;

	//read the bitmap file header
	fread(&bitmapFileHeader, sizeof(HEADER), 1, filePtr);
	printf("%d\n", sizeof(HEADER));


	//verify that this is a bmp file by check bitmap id
	if (bitmapFileHeader.type != 0x4D42)
	{
		fclose(filePtr);
		return NULL;
	}

	//read the bitmap info header
	fread(bitmapInfoHeader, sizeof(INFOHEADER), 1, filePtr); // small edit. forgot to add the closing bracket at sizeof

	//move file point to the begging of bitmap data
	fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

	//allocate enough memory for the bitmap image data
	bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->width * bitmapInfoHeader->height * 3);

	//verify memory allocation
	if (!bitmapImage)
	{
		free(bitmapImage);
		fclose(filePtr);
		return NULL;
	}

	//read in the bitmap image data
	fread(bitmapImage, bitmapInfoHeader->width * bitmapInfoHeader->height*3,1, filePtr);

	//make sure bitmap image data was read
	if (bitmapImage == NULL)
	{
		fclose(filePtr);
		return NULL;
	}
	
	//swap the r and b values to get RGB (bitmap is BGR)
	for (imageIdx = 0; imageIdx < bitmapInfoHeader->width * bitmapInfoHeader->height * 3; imageIdx += 3) // fixed semicolon
	{
		tempRGB = bitmapImage[imageIdx];
		bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
		bitmapImage[imageIdx + 2] = tempRGB;
	}

	//close file and return bitmap iamge data
	fclose(filePtr);
	return bitmapImage;
}