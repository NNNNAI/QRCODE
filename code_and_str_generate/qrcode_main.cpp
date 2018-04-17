#include <qr.h>



/*int main()

{
	Mat srcImage;
	namedWindow("src", WINDOW_NORMAL);
	string context = QRCODE_TEXT;
	string the_path = OUT_FILE;
	if (createqrcode(context, the_path, 5))
	{
		srcImage = imread(OUT_FILE);
		imshow("src", srcImage);
	}
	return 0;

}*/

int main()

{
	Mat srcImage;
	string the_string;
	char context[256];
	namedWindow("src", WINDOW_NORMAL);
	rand_str(context, str_length);
	char* the_path = OUT_FILE;
	cout << context << endl;
	if (createqrcode(context, the_path, 5))
	{
		srcImage = imread(OUT_FILE);
		imshow("src", srcImage);
	}

	the_string = recognize(the_path);
	cout << endl<<"识别出来的"<<endl<<the_string << endl;
	waitKey(0);
	return 0;


	

}