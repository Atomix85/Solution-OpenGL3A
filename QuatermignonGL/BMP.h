#pragma once

#include <stdio.h>
#include <stdlib.h>

class BMP
{
public:

	#pragma pack(push, 1)
	typedef struct {
		unsigned short int type;                 /* Magic identifier            */
		unsigned long int size;                       /* File size in bytes          */
		unsigned long int reserved;
		unsigned long int offset;                     /* Offset to image data, bytes */

	} HEADER;
	#pragma pack(pop)
#pragma pack(push, 1)
	typedef struct {
		unsigned long int size;               /* Header size in bytes      */
		unsigned long int width, height;                /* Width and height of image */
		unsigned short planes;       /* Number of colour planes   */
		unsigned short bits;         /* Bits per pixel            */
		unsigned long int compression;        /* Compression type          */
		unsigned long int imagesize;          /* Image size in bytes       */
		long int xresolution, yresolution;     /* Pixels per meter          */
		unsigned long int ncolours;           /* Number of colours         */
		unsigned long int importantcolours;   /* Important colours         */
	} INFOHEADER;
#pragma pack(pop)

	static unsigned char* LoadBitmapFile(const char* filename, INFOHEADER* bitmapInfoHeader);
};

