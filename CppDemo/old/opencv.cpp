/*
	功能:模板匹配选择匹配阈值的小测试.
*/
 
#include<opencv2/opencv.hpp>
#include<iostream>
 
using namespace std;
using namespace cv;
 
Mat frame;		//待检测图像
Mat templ;		//模板图像
 
//当前阈值
int threshold_v = 900;
//将[0,1]部分,映射到[0,1000].
int threshold_max = 1000;
//窗口名称
const char* WindowTitle1 = "src";
const char* WindowTitle2 = "templ";
 
//滑动条回调函数
void TestCallback(int, void*);
 
int main(int argc,char* argv[])
{
	//加载图片,创建窗口
	frame = imread("1.jpg");
	templ = imread("2.jpg");
	namedWindow(WindowTitle1, CV_WINDOW_NORMAL);
	namedWindow(WindowTitle2, CV_WINDOW_NORMAL);
 
	//创建滑动条,确定选择阈值
	createTrackbar("Threshold Value:", WindowTitle1, &threshold_v, threshold_max, TestCallback);
	TestCallback(0, 0);
 
	waitKey(0);
}
 
void TestCallback(int, void*)
{
	//模板本身也是有一定体积的,所以result的宽高只能是这样
	int width = frame.cols - templ.cols + 1;
	int height = frame.rows - templ.rows + 1;
	//将各像素的匹配值也输出为图像
	Mat result(width, height, CV_32FC1);
	matchTemplate(frame, templ, result, CV_TM_CCOEFF_NORMED);
 
	cv::Point minLoc;
	cv::Point maxLoc;
	double minValue, maxValue;
	minMaxLoc(result, &minValue, &maxValue, &minLoc, &maxLoc, Mat());
 
	cout << minValue << endl;
	cout << maxValue << endl;
	cout << minLoc << endl;
	cout << maxLoc << endl;
 
	double thresholdD = (double)threshold_v / 1000;
 
	if (maxValue>thresholdD)
	{
		rectangle(frame, Rect(maxLoc.x, maxLoc.y, templ.cols, templ.rows), Scalar(0, 0, 255), 2, 8);
	}
	else
	{
		rectangle(frame, Rect(maxLoc.x, maxLoc.y, templ.cols, templ.rows), Scalar(255, 0, 0), 2, 8);
	}
 
	imshow(WindowTitle1, frame);
	imshow(WindowTitle2, templ);
}s