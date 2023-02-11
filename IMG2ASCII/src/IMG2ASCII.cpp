#include <iostream>
#include "../includes/const.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc.hpp>

int main()
{


    cv::Mat image_file = cv::imread(image, cv::IMREAD_COLOR);
    cv::imshow("Image", image_file);

    cv::waitKey(0);


    std::cout << "Hello Donya!!!!!\n";

        //.vs /
        //IMG2ASCII.sln
        //IMG2ASCII / IMG2ASCII.vcxproj
        //IMG2ASCII / IMG2ASCII.vcxproj.filters
        //IMG2ASCII / IMG2ASCII.vcxproj.user
        //IMG2ASCII / x64 /
        //x64 /
}