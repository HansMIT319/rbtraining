#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // 读取图像并将其从BGR转换为HSV颜色空间
    Mat image = imread("training1.jpg");
    Mat hsv_image;
    cvtColor(image, hsv_image, COLOR_BGR2HSV);

    // 定义红色和蓝色的HSV颜色范围
    Scalar red_lower = Scalar(0, 43, 46);
    Scalar red_upper = Scalar(10, 255, 255);
    Scalar blue_lower = Scalar(100, 43, 46);
    Scalar blue_upper = Scalar(124, 255, 255);

    // 分别提取红色和蓝色颜色块
    Mat red_mask, blue_mask;
    inRange(hsv_image, red_lower, red_upper, red_mask);
    inRange(hsv_image, blue_lower, blue_upper, blue_mask);

    // 找到红色和蓝色轮廓
    vector<vector<Point>> red_contours;
    findContours(red_mask, red_contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> blue_contours;
    findContours(blue_mask, blue_contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 计算每个轮廓的质心
    for (const auto &contour : red_contours)
    {
        Moments M = moments(contour);
        if (M.m00 != 0)
        {
            int cx = static_cast<int>(M.m10 / M.m00);
            int cy = static_cast<int>(M.m01 / M.m00);
            cout << "Red block center: (" << cx << ", " << cy << ")" << endl;
        }
    }

    for (const auto &contour : blue_contours)
    {
        Moments M = moments(contour);
        if (M.m00 != 0)
        {
            int cx = static_cast<int>(M.m10 / M.m00);
            int cy = static_cast<int>(M.m01 / M.m00);
            cout << "Blue block center: (" << cx << ", " << cy << ")" << endl;
        }
    }
    imshow("hsv", image);
    waitKey(0);

    return 0;
}