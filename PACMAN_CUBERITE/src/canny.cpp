#define SFML_STATIC
#undef UNICODE
#include <cmath>
#include <iostream>
#include "opencv2/core.hpp"
#include <opencv2/core/utility.hpp>
#include <iostream>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core/cuda.hpp"
#include "opencv2/modules/ximgproc.hpp"

using namespace std;
using namespace cv;
using namespace cv::ximgproc;
//using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;
int lowThreshold = 0;
const int max_lowThreshold = 100;
const int ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";
static void CannyThreshold(int, void*)
{
    blur( src_gray, detected_edges, Size(3,3) );
    Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );
    dst = Scalar::all(0);
    src.copyTo( dst, detected_edges);
    imshow( window_name, dst );
}

int trace( std::string scanfile )  {
  src = imread(  scanfile , IMREAD_COLOR ); // Load an image
  if( src.empty() )
  {
    std::cout << "Could not open or find the image!\n" << std::endl;
    return -1;
  }
  dst.create( src.size(), src.type() );
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  namedWindow( window_name, WINDOW_AUTOSIZE );
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );
  CannyThreshold(0, 0);
  waitKey(0);
  return 0;

}

int trace_line(std::string filename)
{
    // Declare the output variables
    Mat dst, cdst, cdstP;
//    const char* default_file = "../data/sudoku.png";
//    const char* filename = argc >=2 ? argv[1] : default_file;
    // Loads an image
    Mat src = imread( filename, IMREAD_GRAYSCALE );
    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        return -1;
    }
    // Edge detection
//    Canny(src, dst, 100, 200, 3);
    dst = src.clone();
    // Copy edges to the images that will display the results in BGR
    cvtColor(dst, cdst, COLOR_GRAY2BGR);
    cdstP = cdst.clone();
    // Standard Hough Line Transform

    vector<Vec2f> lines; // will hold the results of the detection
    HoughLines(dst, lines, 1, CV_PI/180, 150, 0, 0 ); // runs the actual detection
    // Draw the lines
    for( size_t i = 0; i < lines.size(); i++ )
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a*rho, y0 = b*rho;
        pt1.x = cvRound(x0 + 1000*(-b));
        pt1.y = cvRound(y0 + 1000*(a));
        pt2.x = cvRound(x0 - 1000*(-b));
        pt2.y = cvRound(y0 - 1000*(a));
        line( cdst, pt1, pt2, Scalar(0,0,255), 3, LINE_AA);
    }


    // Probabilistic Line Transform
    vector<Vec4i> linesP; // will hold the results of the detection
    HoughLinesP(dst, linesP, HOUGH_PROBABILISTIC, CV_PI/180, 90, 5, 5 ); // runs the actual detection
//    HoughLinesP(dst, linesP, 1, CV_PI/180, 90, 5, 5 ); // runs the actual detection
//    HoughLinesP(dst, linesP, 1, CV_PI/180, 50, 50, 10 ); // runs the actual detection
    // Draw the lines


    for( size_t i = 0; i < linesP.size(); i++ )
    {
        Vec4i l = linesP[i];
        line( cdstP, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, LINE_AA);
    }
    // Show results
    imshow("Source", src);
    imshow("Detected Lines (in red) - Standard Hough Line Transform", cdst);
    imshow("Detected Lines (in red) - Probabilistic Line Transform", cdstP);
    // Wait and Exit
    waitKey();
    return 0;
}

int trace_line2(std::string in)
{
    Mat input= imread(in, IMREAD_COLOR);
    if( input.empty() )
    {
        return -1;
    }
//    Mat image = imread(in, IMREAD_GRAYSCALE);
    Mat input_grey;
    cvtColor(input, input_grey, COLOR_BGRA2GRAY);

    int length_threshold = 100;
    float distance_threshold = 1.0f;
//    float distance_threshold = 1.41421356f;
    double canny_th1 = 50.0;
    double canny_th2 = 50.0;
    int canny_aperture_size = 3;
    bool do_merge = false;

    Ptr<FastLineDetector> fld = createFastLineDetector(length_threshold, distance_threshold, canny_th1, canny_th2, canny_aperture_size, do_merge);
    vector<Vec4f> lines_fld;
    lines_fld.clear();
    double freq = getTickFrequency();
    int64 start = getTickCount();
    fld->detect(input_grey, lines_fld);
    double duration_ms = double(getTickCount() - start) * 1000 / freq;
    std::cout << "Ealpsed time for FLD " << duration_ms << " ms." << std::endl;

    Mat result;
    result= input.clone();
    for( size_t i = 0; i < lines_fld.size(); i++ )
    {
        Vec4f l = lines_fld[i];
        line( result, Point((int)l[0], (int)l[1]), Point((int)l[2], (int)l[3]), Scalar(0,0,255), 1, LINE_AA);
    }

    Mat line_image_fld;
    line_image_fld=input.clone();
    cvtColor(line_image_fld,line_image_fld, COLOR_BGRA2BGR);
    imshow("FLD result2", line_image_fld);
    waitKey();

    fld->drawSegments(line_image_fld, lines_fld);
    cvtColor(line_image_fld,line_image_fld, COLOR_BGRA2BGR);

    imshow("Input", input);
    imshow("Input_grey", input_grey);
    imshow("FLD result1", result);
    imshow("FLD result2", line_image_fld);

    waitKey();
    return 0;
}



int trace_line3(std::string in)
{
    Mat input= imread(in, IMREAD_COLOR);
    if( input.empty() )
    {
        return -1;
    }
//    Mat image = imread(in, IMREAD_GRAYSCALE);
    Mat input_grey;
    cvtColor(input, input_grey, COLOR_BGRA2GRAY);


    cv::Mat input_grey_blurred;
    cv::medianBlur(input_grey, input_grey_blurred, 3);

    Mat_<double> grad_x;
    Mat_<double> grad_y;
    Sobel(input_grey_blurred, grad_x, CV_64F, 1, 0, 1);
    Sobel(input_grey_blurred, grad_y, CV_64F, 0, 1, 1);

    Mat_<double> magnitude;
    cv::magnitude(grad_x, grad_y, magnitude);

    imshow("Input", input);
    imshow("Input_grey", input_grey);
    imshow("Input_grey_blurred", input_grey_blurred);
    imshow("grad_x", grad_x);
    imshow("grad_y", grad_y);
    imshow("magnitude", magnitude);

    waitKey();
    return 0;
}



int trace_line4(std::string in)
{
    Mat input= imread(in, IMREAD_COLOR);
    if( input.empty() )
    {
        return -1;
    }
//    cvtColor(input, input, COLOR_BGRA2BGR);
    imshow("Input", input);
//    cvtColor(input, input, COLOR_RGBA2BGR);
//    input = input > 1;

//    Mat mask;
//    inRange(input, Scalar(255), Scalar(255), mask);

//    Mat black_image(input.size(), CV_8U, Scalar(0));  // all zeros image
//    black_image.copyTo(input, mask);

    Mat input_grey;
//    input_grey = input.clone();
//    input_grey = input_grey > 1;
    cvtColor(input, input_grey, COLOR_BGRA2GRAY);

//    Mat input_grey_blurred;
//    medianBlur(input_grey, input_grey_blurred, 1);
//    imshow("Input_grey_blurred", input_grey_blurred);

    threshold(input_grey,input_grey,1,255,0);
//    cvtColor(input_grey, input_grey, COLOR_GRAY2BGR);
    imshow("Input_grey", input_grey);

    Mat canny;
    Canny(input_grey, canny, 100, 170, 7);
    imshow("Canny", canny);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(canny, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);

    Mat result;
    result = input.clone();
    Mat result2 = Mat::zeros(input.rows, input.cols, CV_8UC3);
//    result2 = input.clone();
    for( size_t i = 0; i < contours.size(); i++ )
    {
        for( size_t j = 0; j < contours[i].size()-1; j++ ) {
            line( result,   Point((int)contours[i][j].x+5    ,(int)contours[i][j].y+5),
                            Point((int)contours[i][j+1].x+5  ,(int)contours[i][j+1].y+5),
                            Scalar(0,0,255), 1, LINE_AA);
        }

//cvDrawContours(CvArr* img, CvSeq* contour, CvScalar externalColor, CvScalar holeColor, int maxLevel, int thickness=1, int lineType=8 )
    }
    imshow("Result", result);
    int idx = 0;
    for( ; idx >= 0; idx = hierarchy[idx][0] )
    {
        Scalar color( rand()&255, rand()&255, rand()&255 );
        drawContours( result2, contours, idx, color, FILLED, 8, hierarchy );
    }
//    fitLine()
    imshow("Result2", result2);
//    imshow("Result", result);

    waitKey();
    return 0;
}

