#include <iostream>
#include "../includes/const.h"
#include <filesystem>
#include <format>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc.hpp>

//namespace fs = std::filesystem;

std::filesystem::directory_entry does_dir_exist (const std::filesystem::path &current_path, std::string &dir_name) {
    
    for (const auto& dir_entry : std::filesystem::directory_iterator(current_path)) {
        if (!dir_entry.is_regular_file()) {
            

            if (dir_entry.path().string().find(dir_name) != -1) 
                return dir_entry;
            }

        }

    return std::filesystem::directory_entry();

    
}

std::list< std::filesystem::path> check_extention(std::list<std::filesystem::path> &path, std::list<std::string> &types) {
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


    //std::filesystem::directory_entry images_directory{};

    //ToDo: get user input for find this
    std::string findthis = "images";
    // the path from root
    std::string canon_image_path{};
    
    const std::filesystem::path currentPath(".");
    // ToDo:
        std::list<std::filesystem::path> list_files{};



    std::filesystem::directory_entry images_path = does_dir_exist(currentPath, findthis);


    if (!images_path.path().empty()) { // if findthis string was found
        std::cout << "eyo" << std::endl;
        for (const auto& dir_entry : std::filesystem::directory_iterator(images_path.path())) {
            canon_image_path = std::filesystem::canonical(dir_entry.path()).string();
            
            list_files.push_back(dir_entry.path());
            // append all images in path to list_files list
             
            
            //std::cout << dir_entry.path().root_path() << " root path" << std::endl;
            //dir_entry.path().extension

        }
    

    //opencv stuff
    
    }
        std::list<std::string> arrayy{};
        std::list<std::filesystem::path> validated_images =  check_extention (list_files, arrayy);
        for (const auto& vi : validated_images) {
            cv::Point origin(0, 0);
            cv::Point end(200, 200);

            std::cout << std::filesystem::canonical(vi) << std::endl;
            cv::Mat image_file = cv::imread(std::filesystem::canonical(vi).string(), cv::IMREAD_COLOR);
            //cv::imshow("Image", image_file);
            
            cv::Mat grayscale;
            cv::cvtColor(image_file, grayscale, cv::COLOR_RGB2GRAY);
            cv::imshow("Image", grayscale);
            cv::waitKey(0);
            int colum = grayscale.cols;
            int rows = grayscale.rows;

            cv::Mat edges;

            cv::Canny(grayscale, edges, 0, 450);
           

            cv::imshow("Image", edges);
            cv::waitKey(0);


            std::cout << edges << std::endl;

            cv::Mat threshed;
            cv::adaptiveThreshold(grayscale, threshed, 100, 1, 1, 61, 6);

            std::cout << threshed << std::endl;

            cv::imshow("Image", threshed);
            cv::waitKey(0);
            int pixel_size = 25;
            cv::Mat tmp;
            cv::resize(grayscale, tmp, cv::Size(colum / pixel_size, rows / pixel_size),0, 1);
            cv::Mat pixelated;
            cv::resize(tmp, pixelated, cv::Size(colum, rows), 0, 0);
            




                                //TOMORROW
            //TODO: Map on threshed image to grayscale image
                //grayscaled should become an invert of the threshed image
                    //this will save the highlights that the grayscale has, but with the data/detail of the threshed image.
            //TODO: REMOVE THE FUCKING PIC.







            // cv::Mat testing;
            // pixelated.copyTo(testing);
            // 
            // cv::Mat D(testing, cv::Rect(10, 10, 100, 100)); // using a rectangle
            // cv::imshow("Image", D);
            // cv::waitKey(0);
            // 
            // cv::Mat E = testing(cv::Range::all(), cv::Range(1, 20)); // using row and column boundaries
            // 
            // cv::imshow("AAAAAAAAAA", testing);
            // 
            // std::cout << cv::format(E,cv::Formatter::FMT_PYTHON) << std::endl;

            //grayscale(,) 

            cv::Mat E = pixelated(cv::Range(0,4), cv::Range(50, 54));
            cv::imshow("Image", pixelated);
            std::cout << cv::format(E, cv::Formatter::FMT_PYTHON) << std::endl;
            cv::waitKey(0);
            
        };

        /*
                                     ///
                                     ///
                                     ///
                                     ///
                                     ///
        
        
        */
   



    
    
    
    
    
    
    std::cout << "Hello Donya!!!!!\n";

}