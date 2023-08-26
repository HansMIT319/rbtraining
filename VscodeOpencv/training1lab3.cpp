#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using namespace std;

void find_color_centers(const Mat &input_image, vector<Point> &red_centers, vector<Point> &blue_centers)
{
    // Convert the input image to Lab color space
    Mat lab_image;
    cvtColor(input_image, lab_image, COLOR_BGR2Lab);

    // Define the color thresholds for red and blue
    int red_lower_threshold = 130;
    int red_upper_threshold = 255;
    int blue_lower_threshold = 95;
    int blue_upper_threshold = 170;

    // Create masks for red and blue color spaces
    Mat red_mask, blue_mask;
    inRange(lab_image, Scalar(red_lower_threshold, 0, 0), Scalar(red_upper_threshold, 255, 255), red_mask);
    inRange(lab_image, Scalar(blue_lower_threshold, 0, 0), Scalar(blue_upper_threshold, 255, 255), blue_mask);

    // Find contours in the red and blue masks
    vector<vector<Point>> red_contours;
    vector<vector<Point>> blue_contours;
    findContours(red_mask, red_contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    findContours(blue_mask, blue_contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Iterate through the contours and find the centers of the red and blue regions
    for (size_t i = 0; i < red_contours.size(); i++)
    {
        Moments red_moments = moments(red_contours[i]);
        double red_center_x = red_moments.m10 / red_moments.m00;
        double red_center_y = red_moments.m01 / red_moments.m00;
        red_centers.push_back(Point(red_center_x, red_center_y));
    }

    for (size_t i = 0; i < blue_contours.size(); i++)
    {
        Moments blue_moments = moments(blue_contours[i]);
        double blue_center_x = blue_moments.m10 / blue_moments.m00;
        double blue_center_y = blue_moments.m01 / blue_moments.m00;
        blue_centers.push_back(Point(blue_center_x, blue_center_y));
    }
}

int main()
{
    // Load the input image
    Mat input_image = imread("training1.jpg");

    // Create empty vectors to store the centers of red and blue regions
    vector<Point> red_centers;
    vector<Point> blue_centers;

    // Find the centers of red and blue regions
    find_color_centers(input_image, red_centers, blue_centers);

    // Print the coordinates of the centers
    cout << "Red centers: " << endl;
    for (const auto &center : red_centers)
    {
        cout << "x: " << center.x << ", y: " << center.y << endl;
    }
    cout << "Blue centers: " << endl;
    for (const auto &center : blue_centers)
    {
        cout << "x: " << center.x << ", y: " << center.y << endl;
    }

    // 显示结果图像
    imshow("Result", input_image);
    waitKey(0);
    return 0;
}