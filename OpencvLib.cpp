#include "OpencvLib.h"

// открываем дефолтную камеру
void ImageFacade::ImageDepartment::Turn_on_camera() {
	cap.open(0);
}

void ImageFacade::ImageDepartment::Set_default_options() {
	_count_of_images = 10;
	// размеры итогового ихображения
	_image_width = 500;
	_image_height = 500;
	// возьмем каждый 10-й кадр (если значение _wait_iter = 10)
	_wait_iter = 5;
}

bool ImageFacade::ImageDepartment::_condition_for_analyze(Mat & img, int i, int j) {
	return ( img.at<Vec3b>(i,j)[0] < img.at<Vec3b>(i,j)[1] - 10 && 
                             img.at<Vec3b>(i,j)[2] < img.at<Vec3b>(i,j)[1] - 10 &&
                             img.at<Vec3b>(i,j)[1] > 64);
}

void ImageFacade::ImageDepartment::_Get_image() {

	Mat img(_image_width, _image_height, CV_8UC3, Scalar(0,100, 100));
	Mat * images = new Mat [_count_of_images];
	for (int i = 0; i < _count_of_images; i++) {
		images[i] = img;
		bool bSuccess = cap.read(images[i]); // read a new frame from video
		for (int j = 0; j < _wait_iter; j++)
			bool bSuccess = cap.read(img); // read a new frame from video
	}



	res_image = img;

	for( int i = 0; i < res_image.rows; i++ ) {
		   for( int j = 0; j < res_image.cols; j++ ) {
			        res_image.at<Vec3b>(i,j)[0]= 0;
                    res_image.at<Vec3b>(i,j)[1]= 0;
	                res_image.at<Vec3b>(i,j)[2]= 0;
            }
	   }


	for (int k = 0; k < _count_of_images; k++) {
       for( int i = 0; i < img.rows; i++ ) {
		   for( int j = 0; j < images[k].cols; j++ ) {
				if ( _condition_for_analyze(images[k], i, j) )
                   {
                           res_image.at<Vec3b>(i,j)[0]= 0;
                           res_image.at<Vec3b>(i,j)[1]= 0;
	                       res_image.at<Vec3b>(i,j)[2]= 255;
                   } 
			}
	   }
	}

	namedWindow("MyWindow", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	imshow("MyWindow", res_image); //display the image which is stored in the 'img' in the "MyWindow" window


	
	waitKey(0); //wait infinite time for a keypress

}

int ImageFacade::Get_action() {
	int act = 0;
	image = _opencv.Get_image();
	act = _analyzer.Analyze_image(image);
	return 0;
}