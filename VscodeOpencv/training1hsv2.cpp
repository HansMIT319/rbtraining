#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // 读取图像
    Mat image = imread("training1.jpg");

    // 将图像转换为HSV颜色空间
    Mat hsvImage;
    cvtColor(image, hsvImage, COLOR_BGR2HSV);

    // 定义红色和蓝色的HSV范围
    Scalar redLower(0, 100, 100);
    Scalar redUpper(10, 255, 255);
    Scalar blueLower(110, 100, 100);
    Scalar blueUpper(130, 255, 255);

    // 使用颜色范围进行颜色分割
    Mat redMask, blueMask;
    inRange(hsvImage, redLower, redUpper, redMask);
    inRange(hsvImage, blueLower, blueUpper, blueMask);

    // 查找红色和蓝色的轮廓
    vector<vector<Point>> redContours, blueContours;
    findContours(redMask, redContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    findContours(blueMask, blueContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 绘制红色和蓝色的轮廓及中心坐标
    for (const auto &contour : redContours)
    {
        Moments moments = cv::moments(contour);
        Point center(moments.m10 / moments.m00, moments.m01 / moments.m00);
        drawContours(image, {contour}, -1, Scalar(0, 0, 255), 2);
        circle(image, center, 5, Scalar(0, 0, 255), -1);
        cout << "红色色块中心坐标：(" << center.x << ", " << center.y << ")" << endl;
    }

    for (const auto &contour : blueContours)
    {
        Moments moments = cv::moments(contour);
        Point center(moments.m10 / moments.m00, moments.m01 / moments.m00);
        drawContours(image, {contour}, -1, Scalar(255, 0, 0), 2);
        circle(image, center, 5, Scalar(255, 0, 0), -1);
        cout << "蓝色色块中心坐标：(" << center.x << ", " << center.y << ")" << endl;
    }

    // 显示结果图像
    imshow("Result", image);
    waitKey(0);

    return 0;
}