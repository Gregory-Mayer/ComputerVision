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
//class Detector
//{
//	enum Mode { Default, Daimler } m;
//	HOGDescriptor hog, hog_d;
//public:
//	Detector() : m(Default), hog(), hog_d(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9)
//	{
//		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
//		hog_d.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
//	}
//	void toggleMode() { m = (m == Default ? Daimler : Default); }
//	string modeName() const { return (m == Default ? "Default" : "Daimler"); }
//	vector<Rect> detect(InputArray img)
//	{
//		// Run the detector with default parameters. to get a higher hit-rate
//		// (and more false alarms, respectively), decrease the hitThreshold and
//		// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
//		vector<Rect> found;
//		if (m == Default)
//			hog.detectMultiScale(img, found, 0, Size(8, 8), Size(32, 32), 1.05, 2, false);
//		else if (m == Daimler)
//			hog_d.detectMultiScale(img, found, 0.5, Size(8, 8), Size(32, 32), 1.05, 2, true);
//		return found;
//	}
//	void adjustRect(Rect & r) const
//	{
//		// The HOG detector returns slightly larger rectangles than the real objects,
//		// so we slightly shrink the rectangles to get a nicer output.
//		r.x += cvRound(r.width*0.1);
//		r.width = cvRound(r.width*0.8);
//		r.y += cvRound(r.height*0.07);
//		r.height = cvRound(r.height*0.8);
//	}
//};

int main(int argc, char** argv)
{
	// capture from web camera init

	//VideoCapture cap(0);
	//cap.open(0);

	Mat img;

	// Initialize the inbuilt Harr Cascade frontal face detection
	// Below mention the path of where your haarcascade_frontalface_alt2.xml file is located

	//CascadeClassifier face_cascade;
	//face_cascade.load("C:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml");

	//Detector detector;
	//Mat frame;
	//for (;;)
	//{
	//	cap >> frame;
	//	if (frame.empty())
	//	{
	//		cout << "Finished reading: empty frame" << endl;
	//		break;
	//	}
	//	int64 t = getTickCount();
	//	vector<Rect> found = detector.detect(frame);
	//	t = getTickCount() - t;

	//	// show the window
	//	{
	//		ostringstream buf;
	//		buf << "Mode: " << detector.modeName() << " ||| "
	//			<< "FPS: " << fixed << setprecision(1) << (getTickFrequency() / (double)t);
	//		putText(frame, buf.str(), Point(10, 30), FONT_HERSHEY_PLAIN, 2.0, Scalar(0, 0, 255), 2, LINE_AA);
	//	}
	//	for (vector<Rect>::iterator i = found.begin(); i != found.end(); ++i)
	//	{
	//		Rect &r = *i;
	//		detector.adjustRect(r);
	//		rectangle(frame, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
	//	}
	//	imshow("People detector", frame);

	//	// interact with user
	//	const char key = (char)waitKey(30);
	//	if (key == 27 || key == 'q') // ESC
	//	{
	//		cout << "Exit requested" << endl;
	//		break;
	//	}
	//	else if (key == ' ')
	//	{
	//		detector.toggleMode();
	//	}
	//}

	


	//Camera face detection
	/*
	for (;;)
	{

		// Image from camera to Mat

		cap >> img;

		// obtain input image from source
		cap.retrieve(img, CV_CAP_OPENNI_BGR_IMAGE);

		// Just resize input image if you want
		resize(img, img, Size(1000, 640));

		// Container of faces
		vector<Rect> faces;


		// Detect faces
		face_cascade.detectMultiScale(img, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(140, 140));


		//Show the results
		// Draw circles on the detected faces

		for (int i = 0; i < faces.size(); i++)
		{
			Point center(faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5);
			ellipse(img, center, Size(faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
		}

		// To draw rectangles around detected faces
	    //for (unsigned i = 0; i<faces.size(); i++)
				   //rectangle(img,faces[i], Scalar(255, 0, 0), 2, 1);


		imshow("Computer Vision", img);
		int key2 = waitKey(20);

	}*/



	/*
	vector<String> fn; 
	string path = "C:/Users/Serenity/Desktop/UMBC HW/AI/planesnet/*.png";
	glob(path, fn, false);
	
	int i = 0;
	img = imread(fn.front(), CV_LOAD_IMAGE_GRAYSCALE);
	namedWindow("testies", WINDOW_NORMAL);
	resizeWindow("testies", 500,500);
	for (;;)
	{
		
		cout << i << "\n" << fn[i] << "\n";
		imshow("testies", img);
		int key2 = waitKey(20);
		i++;
		if (i>fn.size()-1) 
		{
			i = fn.size()-1;
		}
		img = imread(fn[i], CV_LOAD_IMAGE_GRAYSCALE);
		
	}*/

	CascadeClassifier plane_classifier;
	plane_classifier.load("C:/Users/arrastador/Documents/GitHub/ComputerVision/landons junk folder/cascade/cascade.xml");
	img = imread("C:/Users/arrastador/Documents/GitHub/ComputerVision/landons junk folder/test6.jpg", CV_LOAD_IMAGE_ANYDEPTH);
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
	//}
	imwrite("C:/Users/arrastador/Documents/GitHub/ComputerVision/results/Results.jpg", img);
	
	return 0;
}


