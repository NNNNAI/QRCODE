#include <qr.h>
int thregroup[8] = { 50,70,100,130,170,200,230,240 };

int createqrcode(char *szSourceSring, char *path,int version=0)
{
	///////该函数会生成字符串值为szSourceString的版本为version的二维码，并且以bmp的格式
	///////保存在路径path上，
	
	///////返回1则是生成成功，返回零则失败
	///////version可以设置为0，让函数自动判断生成什么版本。
	unsigned int    unWidth, x, y, l, n, unWidthAdjusted, unDataBytes;
	unsigned char*  pRGBData, *pSourceData, *pDestData;
	QRcode*         pQRC;
	FILE*           f;
	int str_len=strlen(szSourceSring);
	// Compute QRCode
	while (1)
	{
		if (pQRC = QRcode_encodeString(szSourceSring, version, QR_ECLEVEL_H, QR_MODE_8, 1))
		{
			unWidth = pQRC->width;
			unWidthAdjusted = unWidth * OUT_FILE_PIXEL_PRESCALER * 3;
			if (unWidthAdjusted % 4)
				unWidthAdjusted = (unWidthAdjusted / 4 + 1) * 4;
			unDataBytes = unWidthAdjusted * unWidth * OUT_FILE_PIXEL_PRESCALER;

			// Allocate pixels buffer

			if (!(pRGBData = (unsigned char*)malloc(unDataBytes)))
			{
				printf("Out of memory");
				exit(-1);
			}

			// Preset to white

			memset(pRGBData, 0xff, unDataBytes);


			// Prepare bmp headers

			BITMAPFILEHEADER kFileHeader;
			kFileHeader.bfType = 0x4d42;  // "BM"
			kFileHeader.bfSize = sizeof(BITMAPFILEHEADER) +
				sizeof(BITMAPINFOHEADER) +
				unDataBytes;
			kFileHeader.bfReserved1 = 0;
			kFileHeader.bfReserved2 = 0;
			kFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) +
				sizeof(BITMAPINFOHEADER);

			BITMAPINFOHEADER kInfoHeader;
			kInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
			kInfoHeader.biWidth = unWidth * OUT_FILE_PIXEL_PRESCALER;
			kInfoHeader.biHeight = -((int)unWidth * OUT_FILE_PIXEL_PRESCALER);
			kInfoHeader.biPlanes = 1;
			kInfoHeader.biBitCount = 24;
			kInfoHeader.biCompression = BI_RGB;
			kInfoHeader.biSizeImage = 0;
			kInfoHeader.biXPelsPerMeter = 0;
			kInfoHeader.biYPelsPerMeter = 0;
			kInfoHeader.biClrUsed = 0;
			kInfoHeader.biClrImportant = 0;


			// Convert QrCode bits to bmp pixels

			pSourceData = pQRC->data;
			for (y = 0; y < unWidth; y++)
			{
				pDestData = pRGBData + unWidthAdjusted * y * OUT_FILE_PIXEL_PRESCALER;
				for (x = 0; x < unWidth; x++)
				{
					if (*pSourceData & 1)
					{
						for (l = 0; l < OUT_FILE_PIXEL_PRESCALER; l++)
						{
							for (n = 0; n < OUT_FILE_PIXEL_PRESCALER; n++)
							{
								*(pDestData + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_B;
								*(pDestData + 1 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_G;
								*(pDestData + 2 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_R;
							}
						}
					}
					pDestData += 3 * OUT_FILE_PIXEL_PRESCALER;
					pSourceData++;
				}
			}


			// Output the bmp file

			if (!(fopen_s(&f, path, "wb")))
			{
				fwrite(&kFileHeader, sizeof(BITMAPFILEHEADER), 1, f);
				fwrite(&kInfoHeader, sizeof(BITMAPINFOHEADER), 1, f);
				fwrite(pRGBData, sizeof(unsigned char), unDataBytes, f);

				fclose(f);
			}
			else
			{
				printf("Unable to open file");
				exit(-1);
			}

			// Free data

			free(pRGBData);
			QRcode_free(pQRC);
			return 1;
		}
		else
		{
			printf("NULL returned");
			return 0;
		}
	}

}


char *rand_str(char *str, const int len)
{


	//随机生成长度为len的字符串str
	srand(time(NULL));
	int i;
	for (i = 0; i<len; ++i)
	{
		switch ((rand() % 3))
		{
		case 1:
			str[i] = 'A' + rand() % 26;
			break;
		case 2:
			str[i] = 'a' + rand() % 26;
			break;
		default:
			str[i] = '0' + rand() % 10;
			break;
		}
	}
	str[i] = '\0';
	return str;
}




string recognize( char *path)
{

	////输入图片的路径名进行识别若二维码识别成功，函数会打印出类型，条码和阈值数
    ///若识别失败则打印检测失败请重新检测。
	string str;
	int NUM = 71;
	int b = 0;
	int flag_correct = 0;


	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	string  ori, check;

	Mat srcImage, resizeImage, gray, filter, mid;
	int thre = 230, a = 0, flag = 0, flagnum = 10;
	//createTrackbar("thre", "test", &thre, 255, 0);
	srcImage = imread(path);
	cvtColor(srcImage, gray, CV_BGR2GRAY);
	b = 0, flag_correct = 0;
	while (flag_correct == 0 && b < 8)
	{
		thre = thregroup[b];
		gray.copyTo(mid);
		threshold(mid, mid, thre, 255, CV_THRESH_BINARY);
		int width = mid.cols;
		int height = mid.rows;
		uchar *raw = (uchar *)mid.data;
		Image imageZbar(width, height, "Y800", raw, width * height);
		scanner.scan(imageZbar);
		Image::SymbolIterator symbol = imageZbar.symbol_begin();
		for (flag = 0; flag < flagnum; flag++)
		{
			if (imageZbar.symbol_begin() == imageZbar.symbol_end())
			{
				if (flag == flagnum - 1)
				{
					b++;
				}
				continue;
			}
			for (; symbol != imageZbar.symbol_end(); ++symbol)
			{
				ori = symbol->get_data();
				cout << "类型：" << endl << symbol->get_type_name() << endl << endl;
				cout << "条码：" << endl << ori << endl << endl;
				cout << "阈值数" << b + 1 << endl;
				flag_correct = 1;
			}
			break;
		}

	}
	if (flag_correct == 0)
	{
		cout << "检测失败请重新检测" << endl;
	}
	return ori;
}