#pragma once

#include <string.h>
#include <errno.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>
#include <iostream>
#include <time.h>
#include <zbar.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "qrencode.h"
using namespace cv;
using namespace std;
using namespace zbar;


int createqrcode(char *szSourceSring, char *path,int version);
char *rand_str(char *str, const int len);
string recognize(char *path);
int b = 0;
int flag_correct = 0;
//  -------------------------------------------------------


//  -------------------------------------------------------
//  DEFines
//  -------------------------------------------------------

#define QRCODE_TEXT                 "https://blog.csdn.net/keith_bb/article/details/50063075";      // Text to encode into QRCode
#define OUT_FILE                    "E:/vs/project/ConsoleApplication5/ConsoleApplication5/test.bmp"                               // Output file name
#define OUT_FILE_PIXEL_PRESCALER    8                                           // Prescaler (number of pixels in bmp file for each QRCode pixel, on each dimension)

#define PIXEL_COLOR_R               0                                           // Color of bmp pixels
#define PIXEL_COLOR_G               0
#define PIXEL_COLOR_B               0
#define str_length 20
// BMP defines

typedef unsigned short  WORD;
typedef unsigned long   DWORD;
typedef signed long     LONG;

#define BI_RGB          0L

#pragma pack(push, 2)

typedef struct
{
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct
{
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER;

