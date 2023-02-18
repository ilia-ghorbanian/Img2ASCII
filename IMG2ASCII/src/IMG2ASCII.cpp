#include <iostream>
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
            cv::adaptiveThreshold(grayscale, threshed, 100, 1, 1, 61, 6);

            int pixel_size = 2; // pixel size to refactor and resize the image to


            // loop in the image matrix
            for (int i = 0; i < threshed.rows-1; i++) {
                for (int j = 0; j < threshed.cols -1; j++) {

                    cv::Scalar threshed_value = threshed.at<uchar>(cv::Point(j, i)); // get the value for each pixel
                    
                 
                     if (threshed_value[0] > 0) { 
                         threshed.at<uchar>(cv::Point(j, i)) = grayscale.at<uchar>(cv::Point(j, i));
                         // adds highliting and varied intensity to the image 
                     }
                    

     
                    //NEXT try to figure out asci values for the different shades of gray
                    //try to create the ascii


                    //NEXT write to cout // curses.h? urwid? win.h? etc

                }

            }
            cv::resize(threshed, threshed, cv::Size(threshed.cols / 2, threshed.rows / 2), 0, 1); //resize the image
            cv::imshow("Image", threshed);
            cv::waitKey(0);

        };

 

}