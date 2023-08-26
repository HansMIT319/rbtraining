#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // 读取图像并将其从BGR转换为LAB颜色空间
    Mat image = imread("training1.jpg");
    Mat lab_image;
    cvtColor(image, lab_image, COLOR_BGR2Lab);

    // 定义红色和蓝色的LAB颜色范围
    Scalar red_lower = Scalar(0, 150, 0);
    Scalar red_upper = Scalar(100, 255, 80);
    Scalar blue_lower = Scalar(0, 0, 128);
    Scalar blue_upper = Scalar(100, 120, 255);

    // 分别提取红色和蓝色颜色块
    Mat red_mask, blue_mask;
    inRange(lab_image, red_lower, red_upper, red_mask);
    inRange(lab_image, blue_lower, blue_upper, blue_mask);

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
    imshow("lab", lab_image);
    waitKey(0);
    return 0;
}