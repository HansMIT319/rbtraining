#include <opencv2/opencv.hpp>

int main()
{
    // 读取图像
    cv::Mat image = cv::imread("training1.jpg");

    // 转换为HSV颜色空间
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);

    // 定义红色范围
    cv::Scalar lowerRed(0, 100, 100);
    cv::Scalar upperRed(10, 255, 255);

    // 定义蓝色范围
    cv::Scalar lowerBlue(110, 100, 100);
    cv::Scalar upperBlue(130, 255, 255);

    // 对图像进行阈值处理，提取红色和蓝色区域
    cv::Mat redMask, blueMask;
    cv::inRange(hsvImage, lowerRed, upperRed, redMask);
    cv::inRange(hsvImage, lowerBlue, upperBlue, blueMask);

    // 查找红色和蓝色色块的轮廓
    std::vector<std::vector<cv::Point>> redContours, blueContours;
    cv::findContours(redMask, redContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::findContours(blueMask, blueContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 绘制红色色块中心
    for (const auto &redContour : redContours)
    {
        cv::Moments moments = cv::moments(redContour);
        double centerX = moments.m10 / moments.m00;
        double centerY = moments.m01 / moments.m00;
        cv::circle(image, cv::Point(centerX, centerY), 5, cv::Scalar(0, 0, 255), -1);
    }

    // 绘制蓝色色块中心
    for (const auto &blueContour : blueContours)
    {
        cv::Moments moments = cv::moments(blueContour);
        double centerX = moments.m10 / moments.m00;
        double centerY = moments.m01 / moments.m00;
        cv::circle(image, cv::Point(centerX, centerY), 5, cv::Scalar(255, 0, 0), -1);
    }

    // 显示结果图像
    cv::imshow("Detected Colors", image);
    cv::waitKey(0);

    return 0;
}
