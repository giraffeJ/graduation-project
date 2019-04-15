#include "opencv2/opencv.hpp"  
#include <iostream>  

using namespace cv;
using namespace std;



int main(int, char**)
{
	//������ ���Ϸκ��� ���� ������ �о���� ���� �غ�  
	VideoCapture cap1("2.mp4");
	if (!cap1.isOpened())
	{
		printf("������ ������ ���� �����ϴ�. \n");
	}

	//������ �÷��̽� ũ�⸦  320x240���� ����  
	cap1.set(CAP_PROP_FRAME_WIDTH, 320);
	cap1.set(CAP_PROP_FRAME_HEIGHT, 240);


	Mat frame1;
	namedWindow("video", 1);



	for (;;)
	{

		//��ĸ���κ��� �� �������� �о��  
		cap1 >> frame1;

		imshow("video", frame1);


		//30ms ���� ����ϵ��� �ؾ� �������� �ʹ� ���� ������� ����.  
		if (waitKey(20) == 27) break; //ESCŰ ������ ����  
	}


	return 0;
}