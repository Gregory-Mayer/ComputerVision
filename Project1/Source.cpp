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

int boundLower(int var);
int boundUpper(int var);

int main(int argc, char** argv)
{
	//argv[0] its the .exe
	//argv[1] will the image file
	//argv[2] for setting no fly zone 
	//argv[3-6]
	int start_x = 0;
	int start_y = 0;
	int end_x = 0;
	int end_y = 0;
	String fileName;
	/*
	if (argc < 2) {
		cout << "missing image file" << endl;
		return 0;
	}
	else if (argc == 2) {
		fileName = argv[1];
		cout << fileName << endl;
	}
	else if (argc < 6 || argc >= 6) {
		fileName = argv[1];
		start_x = stoi(argv[2]);
		start_y = stoi(argv[3]);
		end_x = stoi(argv[4]);
		end_y = stoi(argv[5]);
	}
	else {
		cout << "invalid arguments" << endl;
		return 0;
	}
	*/

	Mat img;

	CascadeClassifier plane_classifier;
	//cout << "test1" << endl; 

	
	plane_classifier.load("C:/Users/Serenity/Desktop/UMBC HW/AI/final_cascade/cascade.xml");
	//plane_classifier.load("C:/Users/Serenity/Desktop/UMBC HW/AI/_newTraining/cascade30/cascade.xml");
	//cout << "test1" << endl;
	
	//C:\Users\Serenity\source\repos\ComputerVision\landons junk folder\test6.jpg
	fileName = "C:/Users/Serenity/source/repos/ComputerVision/landons junk folder/test6.jpg";
	img = imread(fileName, CV_LOAD_IMAGE_COLOR);

	
	int coords[4] = {start_x,start_y,end_x,end_y};
	//int coords[4] = {50,300,550,250};
	//unneeded input checking
	/*
	int width = img.col;
	int height = img.row;
	for (int i = 0; i < 4; i++) {
		coords[i] = boundLower(coords[i]);
		if (i%2 == 0) {
			coords[i] = boundUpper(coords[i], width);
		}
		else {
			coords[i] = boundUpper(coords[i], height);
		}
		
	}*/

	Rect noFly(coords[0], coords[1], coords[2], coords[3]);
	//cout << "test1" << endl;
	//for (;;)
	//{
		
		vector<Rect> planes;
		//plane_classifier.detectMultiScale(img, planes, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE, Size(1, 1));
		//plane_classifier.detectMultiScale(img, planes, 1.1, 3, 0, Size(1,1), Size(50,50));
		plane_classifier.detectMultiScale(img, planes, 1.1, 8, 0, Size(0.5, 0.5), Size(25, 25));
		//cout << "test1" << endl;
		for (int i = 0; i < planes.size(); i++)
		{
			//cout << "test21" << endl;
			Point center(planes[i].x + planes[i].width*0.5, planes[i].y + planes[i].height*0.5);
			if (noFly.contains(center)) {
				ellipse(img, center, Size(planes[i].width*0.5, planes[i].height*0.5), 0, 0, 360, Scalar(0, 255,255), 2, 8, 0);
			}
			else {
				ellipse(img, center, Size(planes[i].width*0.5, planes[i].height*0.5), 0, 0, 360, Scalar(255, 255, 0), 2, 8, 0);
			}
			//ellipse(img, center, Size(planes[i].width*0.5, planes[i].height*0.5), 0, 0, 360, Scalar(0, 255, 0), 2, 8, 0);
		}
		Point org;
		org.x = 0;
		org.y = img.size().height - 10;
		RNG rng(0xFFFFFFFF);
		putText(img, "Planes: " + to_string(planes.size()), org, FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,0), 5, 8);
		putText(img, "Planes: " + to_string(planes.size()), org, FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 255), 3, 8);
		//Rect noFly();
		//rectangle(img, Point(50, 50), Point(100, 100), Scalar(0,0,255), 5);
		rectangle(img, noFly, Scalar(0, 0, 255), 5);
		imshow("test", img);
		imwrite("C:/Users/Serenity/source/repos/ComputerVision/landons junk folder/results/Results.jpg", img);
		int key3 = waitKey(0);
	//}
		//cout << "test1" << endl;

	
	
	return 0;
}


int boundLower(int var) {
	if (var < 0) {
		return 0;
	}
	else {
		return var;
	}
}

int boundUpper(int var, int max) {
	if (var > max) {
		return max;
	}
	else {
		return var;
	}
}