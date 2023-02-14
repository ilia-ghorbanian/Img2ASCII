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


int main() {


    std::filesystem::directory_entry images_directory{};
    std::string findthis = "images";
    std::string canon_image_path{};
    
    const std::filesystem::path currentPath(".");
    //DEPRECATED
        std::vector<std::filesystem::path> list_files{};



    std::filesystem::directory_entry images_path = does_dir_exist(currentPath, findthis);

    if (!images_path.path().empty()) {
        std::cout << "eyo" << std::endl;
        for (const auto& dir_entry : std::filesystem::directory_iterator(images_path.path())) {
            canon_image_path = std::filesystem::canonical(dir_entry.path()).string();
            //std::cout << dir_entry.path().root_path() << " root path" << std::endl;
            //dir_entry.path().extension

        }
    
    //get all files
    //opencv stuff
    
    }

    



    //for (const auto& dir_entry : std::filesystem::directory_iterator(currentPath)) {
    //    if (!dir_entry.is_regular_file()) {
    //        //list_directories.push_back(dir_entry);
    //
    //        if (dir_entry.path().string().find("images") != -1) {
    //            std::cout << dir_entry.path().string().find("images") << " OOOOOOOOOOOO" << std::endl;
    //            images_directory = dir_entry;
    //        }
    //        
    //    }
    //    
    //}
    std::cout << "h" << std::endl;

    //DEPRECATED
        //for (const auto& directories : list_directories) {
        //    
        //    std::cout << directories.path().string() << std::endl;
        //    if (directories.path().string().find("images") != -1) {
        //        std::cout << directories.path().string().find("images") <<" OOOOOOOOOOOO" << std::endl;
        //    }
        //}

    
    cv::Mat image_file = cv::imread(canon_image_path, cv::IMREAD_COLOR);
    cv::imshow("Image", image_file);
    
    cv::waitKey(0);
    
    
    std::cout << "Hello Donya!!!!!\n";

}