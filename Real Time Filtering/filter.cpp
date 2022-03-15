//
//  filter.cpp
//  Project1
//
//  Created by Ankitha Udupa on 2/8/22.
//

#include "filter.hpp"
#include<iostream>
#include<string>
using namespace std;

#include"opencv2/core.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int greyscale( cv::Mat &src, cv::Mat &dst ){
    for(int i=0; i<src.size().width;i++){
        for(int j=0; j<src.size().height;j++){
            cv::Vec3b color = src.at<cv::Vec3b>(cv::Point(i,j));
            
            //bgr
            color[0]=color[1];
            color[2]=color[1];

            // set a pixel back to the image
            dst.at<cv::Vec3b>(cv::Point(i,j)) = color;
        }
    }
        
    return(0);
}

cv::Vec3b applyFilter(const cv::Mat &src, int i, int j, const cv::Mat &filter){

    int c,x,y;
    cv::Vec3b result={0,0,0};
    cv::Vec3b finalresult;
    
   
    int halfrow = filter.rows/2;
    int halfcol = filter.cols/2;

    for(y=0;y<filter.rows;y++){
        for(x=0;x<filter.cols;x++){
            for(c=0;c<3;c++){
                result[c] += (filter.at<float>(y,x) * src.at<cv::Vec3b>(i-halfrow+y,j-halfcol+x)[c]/10);
    
            }
        }
    }

    for(c=0;c<3;c++){
        finalresult[c] = (unsigned char) result[c];
    }
    
    return (finalresult);
}
 
int blur5x5( cv::Mat &src, cv::Mat &dst )
{

    
    float data[10] = { 1, 2, 4, 2 ,1 } ;
    cv::Mat filter1 = cv::Mat(1, 5, CV_32F, data);
    cv::Mat filter2 = cv::Mat(5, 1, CV_32F, data);
    
    for(int i=1; i<src.rows-1;i++){
        for(int j=0;j<src.cols-1;j++){
            dst.at<cv::Vec3b>(i,j) = applyFilter(src,i,j,filter1);
            dst.at<cv::Vec3b>(i,j) = applyFilter(dst,i,j,filter2);
        }
    }
    
    return 0;
}

int sobelX3x3( cv::Mat &src, cv::Mat &dst){
    
    
    int c,x,y;
    
    cv::Vec3s result={0,0,0};
    
    for(int i=1; i<src.rows-1; i++){
        for(int j=0; j<src.cols; j++){
            for(int c=0; c<3; c++){
                result[c] = src.at<cv::Vec3b>(i-1, j)[c]*1+
                src.at<cv::Vec3b>(i, j)[c]*2+
                src.at<cv::Vec3b>(i+1, j)[c]*1;
                
                result[c]/=4;
                dst.at<cv::Vec3s>(i, j)[c]=result[c];
            }
        }
    }
    
    cv::Mat inter(src.size(),CV_16SC3);
    
    for(int i=0; i<src.rows; i++){
        for(int j=1; j<src.cols-1; j++){
            for(int c=0; c<3; c++){
                inter.at<cv::Vec3s>(i,j)[c] = dst.at<cv::Vec3s>(i, j-1)[c]*-1
                +dst.at<cv::Vec3s>(i, j)[c]*0+
                dst.at<cv::Vec3s>(i, j+1)[c]*1;
            }
        }
    }
    
    dst=inter;
    
    return 0;
}

int sobelY3x3( cv::Mat &src, cv::Mat &dst ){
    
    int c,x,y;
    
    cv::Vec3s result={0,0,0};
    
    for(int i=1; i<src.rows-1; i++){
        for(int j=0; j<src.cols; j++){
            for(int c=0; c<3; c++){
                result[c] = src.at<cv::Vec3b>(i-1, j)[c]*-1+
                src.at<cv::Vec3b>(i, j)[c]*0+
                src.at<cv::Vec3b>(i+1, j)[c]*1;
                
                dst.at<cv::Vec3s>(i, j)[c]=result[c];
            }
        }
    }
    
    cv::Mat inter(src.size(),CV_16SC3);
    
    for(int i=0; i<src.rows; i++){
        for(int j=1; j<src.cols-1; j++){
            for(int c=0; c<3; c++){
                inter.at<cv::Vec3s>(i,j)[c] = dst.at<cv::Vec3s>(i, j-1)[c]*1/4
                +dst.at<cv::Vec3s>(i, j)[c]*2/4+
                dst.at<cv::Vec3s>(i, j+1)[c]*1/4;
                
            }
        }
    }
    
    dst=inter;
    
    
    return 0;
}

int magnitude( cv::Mat &sx, cv::Mat &sy, cv::Mat &dst ){
    

    cv::Mat mag(sx.size(),CV_16SC3);;
    
    for(int i=0; i<sx.rows;i++){
        for(int j=0; j<sx.cols;j++){
            for(int c=0; c<3;c++){
                mag.at<cv::Vec3s>(i, j)[c] = sqrt(pow(sx.at<cv::Vec3s>(i,j)[c] ,2)+pow(sy.at<cv::Vec3s>(i,j)[c] ,2));
            }
        }
    }
    
    cv::convertScaleAbs(mag,dst);
    
    
    return 0;
}

int blurQuantize( cv::Mat &src, cv::Mat &dst, int levels ){
    
    
    blur5x5(src, dst);
    int b = 255/levels;
    
    for(int i=0; i<src.rows;i++){
        for(int j=0;j<src.cols;j++){
            for(int c=0;c<3;c++){
                dst.at<cv::Vec3b>(i,j)[c]= dst.at<cv::Vec3b>(i,j)[c]/b;
                dst.at<cv::Vec3b>(i,j)[c]=dst.at<cv::Vec3b>(i,j)[c]*b;
            }
        }
    }
    
    return 0;
}

int cartoon( cv::Mat &src, cv::Mat&dst, int levels, int magThreshold ){
    
    
    cv::Mat sobelx(src.size(),CV_16SC3);
    sobelX3x3(src, sobelx);
    
    cv::Mat sobely(src.size(),CV_16SC3);
    sobelY3x3(src, sobely);
    
    cv::Mat mag;
    magnitude( sobelx, sobely, mag );
    
    blurQuantize(src, dst, levels);
    
    for(int i=0; i<src.rows;i++){
        for(int j=0; j<src.cols;j++){
            bool thresh = mag.at<cv::Vec3b>(i,j)[0] > magThreshold;
            for(int c=0; c<3; c++){
                if(thresh){
                    dst.at<cv::Vec3b>(i,j)[c]=0;
                }
            }
        }
    }
    
    return 0;
}

int brightness(cv::Mat &src, cv::Mat&dst, int brightness){


    for( int i=0; i<src.rows;i++) {
           for( int j=0; j<src.cols;j++) {

               for( int c=0; c<3; c++){
                   dst.at<cv::Vec3b>(i,j)[c]= min(255,max(0,src.at<cv::Vec3b>(i,j)[c]+brightness));
               }
           }
       }

    return 0;
}

int rgb_hsv(cv::Mat &img1){
    // R, G, B values are divided by 255
            // to change the range from 0..255 to 0..1
    cv::Mat img = cv::imread("/Users/ankithaudupa/Desktop/Computer_Vision/Project1/Project1/Project1/dog.jpg ");
    
    cout<<"read image"<<endl;
    
    cv::Mat hsv(img.size(),CV_32F);

    for(int i=0; i<img.rows;i++){
        for(int j=0; j<img.cols;j++){
            cv::Vec3b color = img.at<cv::Vec3b>(i,j); //BGR
            
            float h=-1;
            float s=-1;
            float v=-1;
            
            float b=color[0]/255;
            float g=color[1]/255;
            float r=color[2]/255;
            
            double cmax = std::max(r, std::max(g, b)); // max of r,g,b
            double cmin = std::min (r, std::min(g, b)); //min of r,g,b
            float diff = cmax - cmin;
            
            if (cmax == cmin)
                h = 0;
            
            else if (cmax == r)
                h = fmod((60 * ((g - b) / diff) + 360),360);
            
            else if (cmax == g)
                h =fmod((60 * ((b - r) / diff) + 120),360);
            
            // if cmax equal b then compute h
            else if (cmax == b)
                h = fmod((60 * ((r - g) / diff) + 240),360);
            
            // if cmax equal zero
            if (cmax == 0)
                s = 0;
            else
                s = (diff / cmax) * 100;
            
            v = cmax * 100;
            
            hsv.at<cv::Vec3b>(i,j)[0]=h;
            hsv.at<cv::Vec3b>(i,j)[1]=s;
            hsv.at<cv::Vec3b>(i,j)[2]=v;
            
            cout<<hsv.at<cv::Vec3b>(i,j)<<endl;
        }
    }
    
    //cv::imwrite("/Users/ankithaudupa/Desktop/Computer_Vision/Project1/Project1/Project1/dogHSV.jpg" , hsv);
    
    return 0;
}
