
#include <cv.h>
#include <highgui.h>

#include "OpencvLib.h"

using namespace cv;

const char * file = "D:\\TECHNOPARK\\С\\RCV3000\\WORK\\pic1.jpg";




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
	//CvCapture *capture = cvCreateCameraCapture(0); // Думаю тут всё понятно
	//if(capture == NULL) // Если камер не обнаружено - выходим
	//	return;

   VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;

	Mat mat;
	//IplImage *frame = NULL; // Кадр
	//cvNamedWindow("camera", CV_WINDOW_AUTOSIZE); // Окошко
	
	while(1) {
		Mat frame;
		cap >> frame;
        cvtColor(mat, frame, CV_BGR2GRAY);
		imshow("mat", mat);
       
		//frame = cvQueryFrame(capture); // Получаем кадр, так же как и из видео файла
        //cvShowImage("camera", frame); // Выводим
        char c = cvWaitKey(33); // Ждём
        if(c == 27) break; // Если Esc - выходим
	}
	//cvReleaseCapture(&capture);
}

void Smooth () {
	IplImage *original = cvLoadImage(file); // Создаём и загружаем изображение
	IplImage *result = cvCreateImage(cvGetSize(original), IPL_DEPTH_8U, 3); // Создаём изображение

	cvNamedWindow("original", CV_WINDOW_AUTOSIZE); // Создаём окошко для оригинала
	cvNamedWindow("result", CV_WINDOW_AUTOSIZE); // Создаём окошко для результата
	 
	cvShowImage("original", original); // Выводим оригинал
	cvSmooth(original, result, CV_GAUSSIAN, 3, 3); // Размываем по Гауссу
	 
	cvShowImage("result", result); // Выводим результат

 
	cvWaitKey(); // Ждём нажатия клавиши
	cvDestroyAllWindows(); // Убиваем все окна
	cvReleaseImage(&original); // Освобождаем память
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



