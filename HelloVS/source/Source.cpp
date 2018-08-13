#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void main() {
	Mat input = imread("input.png");

	imshow("teste", input);
	waitKey(0);
}