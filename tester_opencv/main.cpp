//
//  main.cpp
//  tester_opencv
//
//  Created by George Manolakis on 1/29/18.
//
//THANKS to openCV examples
#include <iostream>

#include<vector>
//#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

int edgeThresh = 1;
int edgeThreshScharr=1;
Mat image, gray, blurImage, edge1, edge2, cedge,edge_detect;
const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
const char* window_name2 = "Edge map : Canny with custom gradient (Scharr)";

int lowThreshold;
int const max_lowThreshold = 100;
int rat = 3;
int kernel_size = 3;
Mat files;
Mat files2;

class Image
{
//private:
public:
    string directory ="/Users/georgemanolakis/desktop/pix/";
    vector<string> file_location;
    unsigned long k;
    unsigned long i;
   // vector<Mat> image;
   // vector<Mat> converted_image;

    const char* window_name1 = "Edge map : Canny default (Sobel gradient)";
    const char* window_name2 = "Edge map : Canny with custom gradient (Scharr)";
    
 //public:
    vector<Mat> image;
    vector<Mat> converted_image;
    Mat gray;
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
        
        return file_location.front();
    }
    void append_images()
    {
        i=0;
        k=file_location.size();
        while(file_location.size() != 0)
        {
        image.push_back(imread(get_file_location(),IMREAD_COLOR));
    
            if(!image[i].empty())
            {
              //  cout<<file_location[1];
                pop_file_location();
                //return; //Need to figure out how to make conditions considering that file directories for that image file to compare with
                i=i+1;
            }
            else if(image[i].empty())
            {
                cout<<"The IMAGE in the location: "<<file_location[0]<<" DOES NOT EXIST.....DELETING IMAGE PATH AND SKIPPING THIS IMAGE ERROR: 1";
                pop_file_location();
                image.erase(image.end()-1);
                //i=i+1;
            }
            
        }
    }
    
};
Image file;


static void image_conversion(int,void*)
{
    
    //while(i <= image.size())
    //{
    blur( gray,edge_detect,Size(3,3));
    Canny(edge_detect,edge_detect,lowThreshold,lowThreshold*rat,kernel_size);
    files2=Scalar::all(0);
    files.copyTo(files2,edge_detect);
    //imshow("hello",files2);
    //}
}

int main( int argc, const char** argv )
{
    Image file;
    unsigned long i=0;
    const char* window_name = "Edge Map";
    
    file.append_file_location("1.png");
    file.append_file_location("2.png");
    file.append_file_location("3.png");
    file.append_file_location("4.png");
    file.append_images();
    //imshow("window", file.image[0]);
    //waitKey(0);
    while(i<file.image.size())
    {
    files=file.image[i];
    
     files2.create( files.size(), files.type() );
    
    cvtColor(files, gray, COLOR_BGR2GRAY);
     namedWindow( window_name, WINDOW_AUTOSIZE );
    createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold,image_conversion);
    image_conversion(0, 0);
    file.converted_image.push_back(files2);
    
    
    imshow("test",file.converted_image[i]);
        i=i+1;
        waitKey(0);
    }
    return 0;
}


















