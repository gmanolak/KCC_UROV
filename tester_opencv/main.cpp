//
//  main.cpp
//  tester_opencv
//
//  Created by George Manolakis on 1/29/18.
//
//SAMPLE FROM OPENCV WEBSITE
#include <iostream>
#include<vector>
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;
int edgeThresh = 1;
int edgeThreshScharr=1;
Mat image, gray, blurImage, edge1, edge2, cedge;
const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
const char* window_name2 = "Edge map : Canny with custom gradient (Scharr)";

// define a trackbar callback
static void onTrackbar(int, void*)
{
    blur(gray, blurImage, Size(3,3));
    // Run the edge detector on grayscale
    Canny(blurImage, edge1, edgeThresh, edgeThresh*3, 3);
    cedge = Scalar::all(0);
    image.copyTo(cedge, edge1);
    imshow(window_name1, cedge);
    Mat dx,dy;
    Scharr(blurImage,dx,CV_16S,1,0);
    Scharr(blurImage,dy,CV_16S,0,1);
    Canny( dx,dy, edge2, edgeThreshScharr, edgeThreshScharr*3 );
    cedge = Scalar::all(0);
    image.copyTo(cedge, edge2);
    imshow(window_name2, cedge);
}
static void help()
{
    printf("\nThis sample demonstrates Canny edge detection\n"
           "Call:\n"
           "    /.edge [image_name -- Default is ../data/fruits.jpg]\n\n");
}

//const char* keys =
//{
 //   "{help h||}{@image |/Users/georgemanolakis/desktop/pix/3.png|input image name}"
//};

class Image
{

private:
    string directory ="location=/Users/georgemanolakis/desktop/pix/";
    vector<string> file_location;
    int edgeThresh = 1;
    int edgeThreshScharr=1;
    Mat image, gray, blurImage, edge1, edge2, cedge;
    const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
    const char* window_name2 = "Edge map : Canny with custom gradient (Scharr)";
    
 public:
    void append_file_location(string file)
    {
        file_location.push_back(directory + file);
    }
    void pop_file_location()
    {
        file_location.erase(file_location.begin());
    }
    string get_file_location()
    {
        return file_location[0];
    }
    
};




int main( int argc, const char** argv )
{
    Image file;
    
    
    
    
/*
    help();
    CommandLineParser parser(argc, argv, keys);
    string filename = parser.get<string>(0);
    image = imread(filename, IMREAD_COLOR);
    if(image.empty())
    {
        printf("Cannot read image file: %s\n", filename.c_str());
        help();
        return -1;
    }
    cedge.create(image.size(), image.type());
    cvtColor(image, gray, COLOR_BGR2GRAY);
    // Create a window
    namedWindow(window_name1, 1);
    namedWindow(window_name2, 1);
    // create a toolbar
    createTrackbar("Canny threshold default", window_name1, &edgeThresh, 100, onTrackbar);
    createTrackbar("Canny threshold Scharr", window_name2, &edgeThreshScharr, 400, onTrackbar);
    // Show the image
    onTrackbar(0, 0);
    // Wait for a key stroke; the same function arranges events processing
    waitKey(0);
    return 0;
 */
}
