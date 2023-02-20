#include <iostream>
#include <fstream>
#include <algorithm> 
#include "../includes/const.h"
#include <filesystem>
#include <format>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc.hpp>

//namespace fs = std::filesystem;

std::filesystem::directory_entry does_dir_exist (const std::filesystem::path &current_path, std::string &dir_name) { // check for directory existence
    
    for (const auto& dir_entry : std::filesystem::directory_iterator(current_path)) {
        if (!dir_entry.is_regular_file()) {
            

            if (dir_entry.path().string().find(dir_name) != -1) 
                return dir_entry;
            }

        }

    return std::filesystem::directory_entry();

    
}

std::list< std::filesystem::path> check_extention(std::list<std::filesystem::path> &path, std::list<std::string> &types) { //validate file extentions
    std::list< std::filesystem::path> validateds{};
    if (types.empty()) { //default behavior incase no types were given
        std::list<std::string> default_type{ "jpg","png" };
        return check_extention(path, default_type);
    };
    for (const auto& file : path) {
        for (const std::string type : types) {

            if ((file.extension().string().find(type)) != -1) { // if extention is legal
                validateds.push_back(file);

            };

        };
    };
            
                //auto string_ext = path.extension().string();
                return validateds;
};


// cv::Mat blocking(int width , int height, int block_width, int block_height, cv::Mat tmp) {
//     for (int bx = 0; bx < width; bx += block_width) // image x=0
//         for (int by = 0; by < height; by += block_height) {// image y=0
//             float sum = 0;
//             for (int x = 0; x < block_width; ++x) //block x = 1
//                 for (int y = 0; y < block_height; ++y) { // block y = 1
//                     //sum += array[bx + x][by + y];
//                     sum += tmp.at<uchar>(cv::Point(by + y, bx + x)); // sum of INTENSITY VALUE AT (y,x) = (y = 0+1, x = 0+1)
//                 }
//             int average = sum / (block_width * block_height);
//             new_array[bx][by] = average;
//         }
// 
//     return tmp;
// }





int main() {


    //ToDo: get user input for find this
    std::string findthis = "images";

    // the path from root
    std::string canon_image_path{};
    
    const std::filesystem::path currentPath(".");

    std::list<std::filesystem::path> list_files{};


    std::filesystem::directory_entry images_path = does_dir_exist(currentPath, findthis);


    if (!images_path.path().empty()) { // if findthis string was found

        for (const auto& dir_entry : std::filesystem::directory_iterator(images_path.path())) {
            canon_image_path = std::filesystem::canonical(dir_entry.path()).string(); // get the canon_path for all the  images 
            
            list_files.push_back(dir_entry.path()); // append all images in path to list_files

        }
    }
        std::list<std::string> extention_list{}; // the extentions which the user wants to validate with
        std::list<std::filesystem::path> validated_images =  check_extention (list_files, extention_list); // extention validator


    // opencv stuff:
        for (const auto& vi : validated_images) { // loop inside validated images list

            cv::Mat grayscale = cv::imread(std::filesystem::canonical(vi).string(), cv::IMREAD_GRAYSCALE);


            // cv::cvtColor(image_file, grayscale, cv::COLOR_RGB2GRAY);


            cv::Mat threshed;
            int pixel_size = 1; // pixel size to refactor and resize the image to
            int cols = grayscale.cols;
            int rows = grayscale.rows;
            cv::resize(grayscale, grayscale, cv::Size(cols / pixel_size, rows / pixel_size), 0, 1); //resize the image
            cv::resize(grayscale, grayscale, cv::Size(cols, rows), 0, 0);

            cv::adaptiveThreshold(grayscale, threshed, 100, 1, 1, 61, 6);


            // loop in the image matrix
            for (int i = 0; i < threshed.rows; i++) {
                for (int j = 0; j < threshed.cols; j++) {

                    cv::Scalar threshed_value = threshed.at<uchar>(cv::Point(j, i)); // get the value for each pixel

                    if (threshed_value[0] > 0) {
                        threshed.at<uchar>(cv::Point(j, i)) = grayscale.at<uchar>(cv::Point(j, i));
                        // adds highliting and varied intensity to the image

                    }

                }
            }


                //std::cout << cv::format(threshed, cv::Formatter::FMT_PYTHON) << std::endl;


                std::ofstream file("outputs/output.txt", std::ios::app); // ToDo: use file name instead of output.txt


                char ascii1 = '\u2591';
                char ascii2 = '\u2581';
                char ascii3 = '\u2592';
                char ascii4 = '\u2593';

                //TODO: map the range of grayscale(threshed image) values to s_grayscale values
                //NEXT write to cout // curses.h? urwid? win.h? etc

                std::string s_grayscale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\" ^ `'.";
                std::reverse(s_grayscale.begin(), s_grayscale.end());

                cv::resize(threshed, threshed, cv::Size(), 0.15, 0.15, 3);
                
                //cv::resize(threshed, threshed, cv::Size(), 2, 2, 0);
                cv::imshow("Image", threshed);
                cv::waitKey(0);




                int t;
                int a_1 = 0, a_2 = 254;
                int b_1 = 0, b_2 = 69;
                for (int i = 0; i < threshed.rows; i++) {
                    for (int j = 0; j < threshed.cols; j++) {



                        cv::Scalar threshed_value = threshed.at<uchar>(cv::Point(j, i)); // get the value for each pixel
                        //TODO: should just map threshed_value[0] to the remap of grayscale(threshed image) values to s_grayscale values instead of this if/else
                        // t = b_1 + ( (s-a_1) (b_2-b1) / (a_2 - a_1) )
                        // [a_1 = 0, a_2 = 254] 
                        // [b_1 = 0, a_2 = 69 ]
                        // s = threshed_value[0]
                        int s = threshed_value[0];
                        t = b_1 + ((s - a_1) * (b_2 - b_1) / (a_2 - a_1));
                        if (t != 0) {

                            std::cout << s_grayscale[t];
                            file << s_grayscale[t];
                        }
                        else {
                            std::cout << ' ';
                            file << ' ';
                        }

         




                        //std::cout << ".";

                        // factoring the pixels into four different characters
                        // if (threshed_value[0] < 42) {
                        //     file << " ";
                        //     //std::cout << ".";
                        // 
                        // 
                        // 
                        // }
                        // else if (threshed_value[0] < 85) {
                        //     //file << char(ascii1);
                        //     file << ":";
                        //     //std::cout << ":";
                        // 
                        // 
                        // }
                        // else if (threshed_value[0] < 127) {
                        //     file << "-";
                        //     //std::cout << "-";
                        // 
                        // }
                        // else if (threshed_value[0] < 170) {
                        //     //file << char(ascii2);
                        //     //std::cout << char(ascii2);
                        //     file << 'r';
                        //     //std::cout << 'r';
                        // }
                        // else if (threshed_value[0] < 212) {
                        //     //file << char(ascii3);
                        //     //std::cout << ascii3;
                        //     file << "X";
                        //     //std::cout << "X";
                        // 
                        // }
                        // else if (threshed_value[0] <= 255) {
                        //     //file << char(ascii4);
                        //     //std::cout << ascii4;
                        //     file << "$";
                        //     //std::cout << "$";
                        // }


                    };
                    file << std::endl;
                    std::cout << std::endl;

                };
                file.close();
            };
};

 