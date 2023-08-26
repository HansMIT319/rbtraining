#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // 读取图像
    Mat src = imread("training1.jpg");
    if (src.empty())
    {
        cout << "无法读取图像" << endl;
        return -1;
    }

    // 转换为RGB颜色空间
    Mat rgb;
    cvtColor(src, rgb, COLOR_BGR2RGB);

    // 定义红色和蓝色的值范围
    Scalar lower_red = Scalar(200, 0, 0);
    Scalar upper_red = Scalar(255, 100, 100);
    Scalar lower_blue = Scalar(0, 0, 200);
    Scalar upper_blue = Scalar(100, 100, 255);

    // 应用阈值分割，得到红色和蓝色的掩码
    Mat mask_red, mask_blue;
    inRange(rgb, lower_red, upper_red, mask_red);
    inRange(rgb, lower_blue, upper_blue, mask_blue);

    // 找到掩码中的轮廓
    vector<vector<Point>> contours_red, contours_blue;
    findContours(mask_red, contours_red, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    findContours(mask_blue, contours_blue, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // 计算轮廓的中心坐标，并在原图上绘制轮廓和中心点
    for (int i = 0; i < contours_red.size(); i++)
    {
        Moments m = moments(contours_red[i]);
        int cx = int(m.m10 / m.m00);
        int cy = int(m.m01 / m.m00);
        drawContours(src, contours_red, i, Scalar(0, 0, 255), 2);
        circle(src, Point(cx, cy), 5, Scalar(0, 0, 255), -1);
        cout << "红色轮廓" << i + 1 << "的中心坐标为(" << cx << ", " << cy << ")" << endl;
    }

    for (int i = 0; i < contours_blue.size(); i++)
    {
        Moments m = moments(contours_blue[i]);
        int cx = int(m.m10 / m.m00);
        int cy = int(m.m01 / m.m00);
        drawContours(src, contours_blue, i, Scalar(255, 0, 0), 2);
        circle(src, Point(cx, cy), 5, Scalar(255, 0, 0), -1);
        cout << "蓝色轮廓" << i + 1 << "的中心坐标为(" << cx << ", " << cy << ")" << endl;
    }

    // 显示结果
    imshow("src", src);
    waitKey(0);

    return 0;
}
