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
	//argv[0] its the .exe
	//argv[1] will the image file
	//argv[2] for setting no fly zone 
	//argv[3-6]
	int start_x = 0;
	int start_y = 0;
	int end_x = 0;
	int end_y = 0;
	String fileName;
	//ensures that the right number of command line arguments are passed.
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
	//image that will be used
	Mat img;
	//trained cascade for indentifying planes
	CascadeClassifier plane_classifier;
	
	//loads the cascade into the program
	plane_classifier.load("resources/cascade/cascade.xml");
	
	//fileName = "resources/test6.jpg";
	img = imread(fileName, CV_LOAD_IMAGE_COLOR);

	
	
	//this is used to determine an area that planes are not permitted
	Rect noFly(start_x, start_y, end_x, end_y);

		
		vector<Rect> planes;
		//this detects the object in the image. takes in the img, cascade, scale Factor, nearest neighbor, flags, min size, and max size
		plane_classifier.detectMultiScale(img, planes, 1.1, 8, 0, Size(0.1, 0.1), Size(25, 25));
		
		//loops through and marks the planes on the image
		for (int i = 0; i < planes.size(); i++)
		{
			Point center(planes[i].x + planes[i].width*0.5, planes[i].y + planes[i].height*0.5);
			//if the center of the plane is in a no fly zone then it marks it a different color
			if (noFly.contains(center)) {
				ellipse(img, center, Size(planes[i].width*0.5, planes[i].height*0.5), 0, 0, 360, Scalar(0, 255,255), 2, 8, 0);
			}
			else {
				ellipse(img, center, Size(planes[i].width*0.5, planes[i].height*0.5), 0, 0, 360, Scalar(255, 255, 0), 2, 8, 0);
			}
		}
		//prints the number of planes at the bottom of the image.
		Point org;
		org.x = 0;
		org.y = img.size().height - 10;
		RNG rng(0xFFFFFFFF);
		//the two prints are to have a better vision of the text because of the white text and black text allow for the text to be seen on a variety of backgrounds
		putText(img, "Planes: " + to_string(planes.size()), org, FONT_HERSHEY_SIMPLEX, 2, Scalar(0,0,0), 5, 8);
		putText(img, "Planes: " + to_string(planes.size()), org, FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 255, 255), 3, 8);
		
		rectangle(img, noFly, Scalar(0, 0, 255), 5);
		imshow("test", img);
		//saves the results of the image to a different file so that can be viewed without altering the original image
		imwrite("results/Results.jpg", img);
		int key3 = waitKey(0);
	//}
		//cout << "test1" << endl;

	
	
	return 0;
}
