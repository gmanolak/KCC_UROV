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
//#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching.hpp>
#include "opencv2/opencv_modules.hpp"

using namespace cv;
//using namespace cv2;
using namespace std;
//int edgeThresh = 1;
//int edgeThreshScharr=1;

Mat image, gray, blurImage, edge1, edge2, cedge,edge_detect;

int lowThreshold;
int const max_lowThreshold = 100;
int rat = 3;
int kernel_size = 3;
Mat files;
Mat result;
Mat files2;
Mat dst;
Mat diff;

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
    
    file.append_file_location("1.jpg");
    file.append_file_location("2.jpg");
    file.append_file_location("3.jpg");
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
    
    
    
    
    
    
    
  
    
    
    
    //TRYING TO FIGURE OUT HOW TO COMPARE TWO IMAGES
    // trying to get values of differences or similiarities to be able to determine facts in code.
   /*
    files=file.converted_image[0];
    files2=file.converted_image[1];
    //addWeighted( files, .1, files2, .9, 100, dst);
    //imshow("fuc",dst);
    //waitKey(0);
    
    //compare(files,files,result,CMP_EQ);
    //int percentage=countNonZero(result);
   // cout<<percentage<<endl;
    //return 0;
   // matchTemplate(files, files, result, CMP_EQ);
    //cout<<endl;
    //cout<<result<<endl;
    absdiff(files, files2, diff);
    int th = 10;  // 0
    Mat mask(files.size(), CV_8UC1);
    
    for(int j=0; j<diff.rows; ++j) {
        for(int i=0; i<diff.cols; ++i){
            Vec3b pix = diff.at<cv::Vec3b>(j,i);
            int val = (pix[0] + pix[1] + pix[2]);
            if(val>th){
                mask.at<unsigned char>(j,i) = 255;
            }
        }
    }
    
    // get the foreground
    Mat res;
    bitwise_and(files, files2, res, mask);
    
    // display
    imshow("res", res);
   // int percentage=countNonZero(res);
  //  cout<<percentage;
    waitKey();

  */
   
    Mat hsv_base;
    Mat  hsv_test1;
    Mat src_test2, hsv_test2;
    Mat hsv_half_down;
    files=file.converted_image[0];
    files2=file.converted_image[1];
    src_test2=file.converted_image[2];
    cvtColor( files, hsv_base, COLOR_BGR2HSV );
    cvtColor( files2, hsv_test1, COLOR_BGR2HSV );
    cvtColor( src_test2, hsv_test2, COLOR_BGR2HSV );
    
      hsv_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );
    int h_bins = 50; int s_bins = 60;
    int histSize[] = { h_bins, s_bins };
    
    // hue varies from 0 to 179, saturation from 0 to 255
    float h_ranges[] = { 0, 180 };
    float s_ranges[] = { 0, 256 };
    
    const float* ranges[] = { h_ranges, s_ranges };
    
    // Use the o-th and 1-st channels
    int channels[] = { 0, 1 };
    
    
    /// Histograms
    MatND hist_base;
    MatND hist_half_down;
    MatND hist_test1;
    MatND hist_test2;
    
    /// Calculate the histograms for the HSV images
    calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
    normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
    
    calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
    normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );
    
    calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
    normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );
    
    calcHist( &hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false );
    normalize( hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat() );
    
    /// Apply the histogram comparison methods
    for( int i = 0; i < 4; i++ )
    {
        int compare_method = i;
        double base_base = compareHist( hist_base, hist_base, compare_method );
        double base_half = compareHist( hist_base, hist_half_down, compare_method );
        double base_test1 = compareHist( hist_base, hist_test1, compare_method );
        double base_test2 = compareHist( hist_base, hist_test2, compare_method );
        
        printf( " Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n", i, base_base, base_half , base_test1, base_test2 );
    }
    
    printf( "Done \n" );

  
    
    
    
    return 0;
}


















