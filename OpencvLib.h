
#include <cv.h>
#include <highgui.h>


using namespace cv;

#ifndef _KOpenCV
#define _KOpenCV

class ImageFacade {

public:

	class AnalizeDepartment
	{
	  public:
		int Analyze_image(Mat image) {
			return 0;
		}
	
		private:

	};

	class ImageDepartment
	{
	  public:
		Mat res_image;

		Mat Get_image() {
			Turn_on_camera(); // �������� ������
			Set_default_options();
			_Get_image();
			return res_image;
		}


		// default options
		int _count_of_images; // ���������� �������, ������� �� ����� ���������
		int _image_width;
		int _image_height;
		int _wait_iter;

		// ������� �������� �������� � ��������
		bool _condition_for_analyze(Mat & img, int i, int j);

		VideoCapture cap;
		void Turn_on_camera();
		void Set_default_options();
		void _Get_image();
	};
	
	ImageFacade() {
  
	}
	int Get_action(); 
	Mat image;
	private:
		ImageDepartment _opencv;
		AnalizeDepartment _analyzer;
};
 

#endif