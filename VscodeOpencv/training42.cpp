#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    // 玩具机器人的四个角点的像素坐标
    std::vector<cv::Point2d> image_points;
    image_points.push_back(cv::Point2d(100, 150));
    image_points.push_back(cv::Point2d(300, 150));
    image_points.push_back(cv::Point2d(300, 300));
    image_points.push_back(cv::Point2d(100, 300));

    // 玩具机器人的四个角点的三维坐标（单位：厘米）
    std::vector<cv::Point3d> object_points;
    object_points.push_back(cv::Point3d(0, 0, 0));
    object_points.push_back(cv::Point3d(10, 0, 0));
    object_points.push_back(cv::Point3d(10, 10, 0));
    object_points.push_back(cv::Point3d(0, 10, 0));

    // 摄像头的焦距（单位：像素）
    double focal_length = 500;

    // 图像的宽度和高度（单位：像素）
    double image_width = 640;
    double image_height = 480;

    // 计算相机内参矩阵
    cv::Mat camera_matrix = (cv::Mat_<double>(3, 3) << focal_length, 0, image_width / 2, 0, focal_length, image_height / 2, 0, 0, 1);

    // 畸变系数
    cv::Mat dist_coeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type);

    // 计算旋转向量和平移向量
    cv::Mat rotation_vector;
    cv::Mat translation_vector;
    bool success = cv::solvePnP(object_points, image_points, camera_matrix, dist_coeffs, rotation_vector, translation_vector);

    // 将旋转向量转换为旋转矩阵
    cv::Mat rotation_matrix;
    cv::Rodrigues(rotation_vector, rotation_matrix);

    // 输出结果
    std::cout << "旋转矩阵:" << std::endl;
    std::cout << rotation_matrix << std::endl;
    std::cout << "平移向量:" << std::endl;
    std::cout << translation_vector << std::endl;

    return 0;
}