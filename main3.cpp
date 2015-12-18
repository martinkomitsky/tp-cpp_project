
#include <cv.h>
#include <highgui.h>

#include "OpencvLib.h"

using namespace cv;

const char * file = "D:\\TECHNOPARK\\�\\RCV3000\\WORK\\pic1.jpg";




#include "EventDispatcher.h"

using namespace std;

class Foo : public EventDispatcher
{
    public:
        void Run ( void )
        {
            for ( int key = 0 ; key < 5 ; key ++ )
            {
                this->DispatchEvent ( "EVENT_1" );
                this->DispatchEvent ( "EVENT_2" );
                usleep ( 500000 );
            };
        };
};

class Bar
{
    public:
        void EventHandler1 ( void )
        {
            cout << "FOO_EVENT_1 listen next\n";
        };

        void EventHandler2 ( void )
        {
            cout << "FOO_EVENT_2 listen prev \n";
        };
};



void Capture_camera() {
	//CvCapture *capture = cvCreateCameraCapture(0); // ����� ��� �� �������
	//if(capture == NULL) // ���� ����� �� ���������� - �������
	//	return;

   VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;

	Mat mat;
	//IplImage *frame = NULL; // ����
	//cvNamedWindow("camera", CV_WINDOW_AUTOSIZE); // ������
	
	while(1) {
		Mat frame;
		cap >> frame;
        cvtColor(mat, frame, CV_BGR2GRAY);
		imshow("mat", mat);
       
		//frame = cvQueryFrame(capture); // �������� ����, ��� �� ��� � �� ����� �����
        //cvShowImage("camera", frame); // �������
        char c = cvWaitKey(33); // ���
        if(c == 27) break; // ���� Esc - �������
	}
	//cvReleaseCapture(&capture);
}

void Smooth () {
	IplImage *original = cvLoadImage(file); // ������ � ��������� �����������
	IplImage *result = cvCreateImage(cvGetSize(original), IPL_DEPTH_8U, 3); // ������ �����������

	cvNamedWindow("original", CV_WINDOW_AUTOSIZE); // ������ ������ ��� ���������
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE); // ������ ������ ��� ����������
	 
	cvShowImage("original", original); // ������� ��������
	cvSmooth(original, result, CV_GAUSSIAN, 3, 3); // ��������� �� ������
	 
	cvShowImage("result", result); // ������� ���������

 
	cvWaitKey(); // ��� ������� �������
	cvDestroyAllWindows(); // ������� ��� ����
	cvReleaseImage(&original); // ����������� ������
	cvReleaseImage(&result);
}

int just_for_fun()
{
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat edges;
    namedWindow("edges",1);
    for(;;)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(waitKey(30) >= 0) break;
    }
	
	// the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

int main() {

	ImageFacade facade;
	int t = facade.Get_action();


	return 0;
}



