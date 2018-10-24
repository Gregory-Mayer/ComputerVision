#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/ml.hpp>
#include <iostream>
#include <iomanip>
using namespace cv;
using namespace std;

int main(int argc, char** argv)
{

	Mat img;

	CascadeClassifier plane_classifier;
	plane_classifier.load("C:/Users/arrastador/source/repos/ComputerVision/Trainer/cascade/cascade.xml");
	img = imread("C:/Users/arrastador/source/repos/ComputerVision/landons junk folder/test6.jpg", CV_LOAD_IMAGE_ANYDEPTH);
	//for (;;)
	//{
		
		vector<Rect> planes;
		plane_classifier.detectMultiScale(img, planes, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(1, 1));
		for (int i = 0; i < planes.size(); i++)
		{
			Point center(planes[i].x + planes[i].width*0.5, planes[i].y + planes[i].height*0.5);
			ellipse(img, center, Size(planes[i].width*0.5, planes[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		}

		imshow("test", img);
		int key3 = waitKey(30);
		cout << planes.size() << endl;
	//}
	imwrite("C:/Users/arrastador/source/repos/ComputerVision/results/Results.jpg", img);
	
	return 0;
}


