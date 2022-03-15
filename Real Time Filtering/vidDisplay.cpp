//
//  vidDisplay.cpp
//  Project1
//
//  Created by Ankitha Udupa on 2/8/22.
//

#include "vidDisplay.hpp"
#include "filter.hpp"
#include<iostream>
#include<string>
using namespace std;

#include"opencv2/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/imgproc.hpp>
using namespace cv;


/*
 Captures live video from the webcam over which we can apply differetn filters
 */
int displayVideo() {
        cv::VideoCapture *capdev;

        // open the video device
        capdev = new cv::VideoCapture(0);
        if( !capdev->isOpened() ) {
                printf("Unable to open video device\n");
                return(-1);
        }

        // get some properties of the image
        cv::Size refS( (int) capdev->get(cv::CAP_PROP_FRAME_WIDTH ),
                       (int) capdev->get(cv::CAP_PROP_FRAME_HEIGHT));
        printf("Expected size: %d %d\n", refS.width, refS.height);

        cv::namedWindow("Video", 0); // identifies a window
        cv::Mat frame;
        bool grayscale1=false;
        bool grayscale2=false;
        bool blur=false;
        bool sobelX=false;
        bool sobelY=false;
        bool mag=false;
        bool quant=false;
        bool car=false;
        bool bright=false;
        
        for(;;) {
                *capdev >> frame; // get a new frame from the camera, treat as a stream
                if( frame.empty() ) {
                  printf("frame is empty\n");
                  break;
                }
                
                if(grayscale1){
                    Mat dst;
                    frame.copyTo(dst);
                    cvtColor(frame, dst, COLOR_BGR2GRAY);
                    cv::putText(dst,"GRAYSCALE 1",cv::Point(3*dst.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    cv::imshow("Video", dst);
                }

                else if(grayscale2){
                    Mat dst;
                    frame.copyTo(dst);
                    greyscale(frame,dst);
                    cv::putText(dst,"GRAYSCALE 2",cv::Point(3*dst.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    cv::imshow("Video", dst);
                }
            
                else if(blur){
                    Mat dst;
                    frame.copyTo(dst);
                    blur5x5(frame,dst);
                    cv::putText(dst,"BLUR",cv::Point(3*dst.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    cv::imshow("Video", dst);
                }
                else if(sobelX){
                    cv::Mat dst(frame.size(),CV_16SC3);
                    sobelX3x3(frame, dst);
                    cv::convertScaleAbs(dst,frame);
                    cv::putText(frame,"SOBEL_X",cv::Point(3*frame.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    cv::imshow("Video", frame);
                }
                else if(sobelY){
                    cv::Mat dst(frame.size(),CV_16SC3);
                    sobelY3x3(frame, dst);
                    cv::convertScaleAbs(dst,frame);
                    cv::putText(frame,"SOBEL_Y",cv::Point(3*frame.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    cv::imshow("Video", frame);
                }
                else if(mag){
                    cv::Mat sobelx(frame.size(),CV_16SC3);
                    sobelX3x3(frame, sobelx);
                    
                    cv::Mat sobely(frame.size(),CV_16SC3);
                    sobelY3x3(frame, sobely);
                    
                    Mat dst;
                    magnitude( sobelx, sobely, dst );
                    
                    cv::putText(dst,"MAG",cv::Point(3*dst.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    
                    cv::imshow("Video", dst);
                }
            
                else if(quant){
                    Mat dst;
                    frame.copyTo(dst);
                    blurQuantize(frame, dst, 10 );
                    cv::putText(dst,"QUANTIZE",cv::Point(3*dst.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    cv::imshow("Video", dst);
                }
                else if(car){
                    Mat dst;
                    frame.copyTo(dst);
                    cartoon(frame,dst, 10, 15);
                    cv::putText(dst,"CARTOON",cv::Point(3*dst.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    cv::imshow("Video", dst);
                }
                else if(bright){
                    Mat dst;
                    frame.copyTo(dst);
                    brightness(frame,dst,64);
                    cv::putText(dst,"BRIGHTNESS",cv::Point(3*dst.cols/4, 50), cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(255, 0, 0),4);
                    cv::imshow("Video", dst);
                }

                else{
                    cv::imshow("Video", frame);
                }
                
        
                // see if there is a waiting keystroke
                char key = cv::waitKey(10);
                if( key == 'q') {
                    break;
                }
            
                if (key=='s'){
                    imwrite("/Users/ankithaudupa/Desktop/Computer Vision/Project1/Project1/Project1/savedImage.jpg", frame);
                }
                
                if (key=='g'){
                    grayscale1=true;
                    grayscale2=false;
                    blur=false;
                    sobelX=false;
                    sobelY=false;
                    mag=false;
                    quant=false;
                    car=false;
                    bright=false;
                }

                if (key=='h'){
                    grayscale1=false;
                    grayscale2=true;
                    blur=false;
                    sobelX=false;
                    sobelY=false;
                    mag=false;
                    quant=false;
                    car=false;
                    bright=false;
                }
            
                if (key=='b'){
                    grayscale1=false;
                    grayscale2=false;
                    blur=true;
                    sobelX=false;
                    sobelY=false;
                    mag=false;
                    quant=false;
                    car=false;
                    bright=false;
                }
            
                if (key=='x'){
                    grayscale1=false;
                    grayscale2=false;
                    blur=false;
                    sobelX=true;
                    sobelY=false;
                    mag=false;
                    quant=false;
                    car=false;
                    bright=false;
                }
            
                if (key=='y'){
                    grayscale1=false;
                    grayscale2=false;
                    blur=false;
                    sobelX=false;
                    sobelY=true;
                    mag=false;
                    quant=false;
                    car=false;
                    bright=false;
                }
                
                if(key=='m'){
                    grayscale1=false;
                    grayscale2=false;
                    blur=false;
                    sobelX=false;
                    sobelY=false;
                    mag=true;
                    quant=false;
                    car=false;
                    bright=false;
                }
                if(key=='l'){
                    grayscale1=false;
                    grayscale2=false;
                    blur=false;
                    sobelX=false;
                    sobelY=false;
                    mag=false;
                    quant=true;
                    car=false;
                    bright=false;
                }
                if(key=='c'){
                    grayscale1=false;
                    grayscale2=false;
                    blur=false;
                    sobelX=false;
                    sobelY=false;
                    mag=false;
                    quant=false;
                    car=true;
                    bright=false;
                   }
                if(key=='a'){
                    grayscale1=false;
                    grayscale2=false;
                    blur=false;
                    sobelX=false;
                    sobelY=false;
                    mag=false;
                    quant=false;
                    car=false;
                    bright=true;
                   }
        }

        delete capdev;
        return(0);
}
