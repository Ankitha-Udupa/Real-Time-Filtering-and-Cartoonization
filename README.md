# Real-Time-Filtering-and-Cartoonization
This project provides the user different options for real time filtering. The functionality includes turning real time video into grayscale using pixel manipulation and openCV cvtColor, blurring a video stream, edge detection using sobel filters, real time video quantization, cartoonization and brightness control. The project involved using opencv for pixel manipulation to apply filters to real time video stream.

## List of features:

The software could be used to:
1. Grayscale video stream by pressing 'g'.
2. Grayscale video stream by pressing 'h'.
3. Blur video stream by pressing 'b'.
3. SobelX and Sobel edge detection video stream by pressing 'x' and 'y' respectively.
4. Magnitude of sobelX and sobelY on video stream by pressing 'm'.
5. Blur and quantize video stream by pressing 'l'.
6. Cartoonized video stream by pressing 'c'.
7. Brightness controlled video stream by pressing 'a'.

## How To Run:
   
   Run the main.cpp file to start the video stream on your webcam. Use keypresses as stated in list of features to achieve processed video output.
      
## Operating system and IDE
   I have used MacOS operating system and Xcode IDE to implement the project.
   
## DEMO   

https://user-images.githubusercontent.com/44782426/158483635-29456296-20d1-44dd-8cd0-04364efab440.mov


## Grayscale 1:
The user can press ‘g’ to achieve a grayscale version of the video feed. This is implemented using the OpenCV cvtColor command. This applies the formula 0.299 R + 0.587 G + 0.114 B. (according to OpenCV documentation). The input to cvtColor command is the colored frame captured by the webcam and the output is the grayscale frame.

**Original Image**

![image2](https://user-images.githubusercontent.com/44782426/158482706-d641c0eb-748c-4976-8c35-b4d74f9f19da.jpg)

**Grayscale Image**

![grayscale1](https://user-images.githubusercontent.com/44782426/158482740-f35feff8-e65f-4eb0-8f51-e3b562941d9d.jpg)

## Grayscale 2:
The user can press ‘h’ to achieve a grayscale version of the video feed. This is implemented setting the pixel values at R and B channels to that of the G channel for the entire frame. The input is the colored frame captured by the webcam and the output is the grayscale frame.

**Original Image**

![image2](https://user-images.githubusercontent.com/44782426/158482773-1cdd9e4a-b6ae-4035-a25f-17abe633c9a5.jpg)

**Grayscale Image**

![grayscale2](https://user-images.githubusercontent.com/44782426/158482788-e4093ea5-3f19-4327-9869-9e70e4d4b712.jpg)

## 5x5 Gaussian Blur:
The user can press ‘b’ to achieve a blurred version of the video feed. This is implemented using a gaussian filter. I have implemented 2 separable filters that reduces the computation considerably as compared to using one 5x5 filter. The Gaussian filter smoothes out the frame giving a blurred effect.

**Original Image**

![UnblurredImage](https://user-images.githubusercontent.com/44782426/158482809-100f9aae-5ee2-41cf-9ae8-db030e9b567c.jpg)

**Blurred Image**

![blurredImage](https://user-images.githubusercontent.com/44782426/158482832-e00a2378-7513-4360-8ffb-83ce9b719200.jpg)


## SobelX and SobelY Filters:
The user can press ‘x’ and ‘y’ respectively to achieve a SobelX and SobelY version of the video feed. Sobel filters are used to detect edges in an image. SobelX detects the vertical edges and SobelY detects the horizontal edges.

**Original Image**

![image2](https://user-images.githubusercontent.com/44782426/158482888-89b4ee11-dcc0-4dcd-a6d6-fade64635215.jpg)

**SOBEL X Image**

![SobelX](https://user-images.githubusercontent.com/44782426/158482902-fd3e58f5-f1bd-46b8-8c27-a08b26eeec90.jpg)

**SOBEL Y Image**

![SobelY](https://user-images.githubusercontent.com/44782426/158482918-d8659e80-613a-49eb-97bc-736b69a7dc28.jpg)


## Gradient Magnitude Image from SobelX and SobelY:
The user can press ‘m’ to achieve a magnitude of SobelX and SobelY for the video feed. This function uses SobelX and SobelY inputs and calculates the magnitude by taking the Euclidean distance of X and Y values.

**Gradient Mag Image**

![mag](https://user-images.githubusercontent.com/44782426/158482972-46481146-a791-4b6f-9815-33da5d0abf69.jpg)

## Blur and Quantize:
The user can press ‘l’ to achieve a quantized version of the video feed. The input to the function takes the level to quantize the image. We first compute the bucket size by dividing the levels by 255 (total pixel value). Each pixel for every channel is then divided by the bucket size to achieve quantization. Finally, this value is multiplied by the bucket size to retain the range.

**Quantized Image**

![quant](https://user-images.githubusercontent.com/44782426/158483057-5be56d13-ed33-4142-a239-90eb62ded8b7.jpg)

## Cartoonized image:
The user can press ‘c’ to achieve a crartoon version of the video feed. I first calculate the gradient magnitude for the image and quantize/blur the image. The function takes in a threshold value which is compared to pixel value in the B channel of the image. For all magnitude values above the threshold, the pixel values for the destination image are set to 0 (black). This gives us a cartoonized effect on the video feed.

**Cartoonized Image**

![cartoon](https://user-images.githubusercontent.com/44782426/158483087-66a47563-fdc7-4644-8895-6cec834249bf.jpg)


## Brightness Control:
The user can press ‘a’ to achieve a brightness controlled version of the video feed . The brightness of a pixel b is a value between 0-255. b = r + g + b/3. If we increase or decrease b by a small value delta b, we can adjust the brightness of the image. However, we still need to make sure the values range between 0 and 255.

**Bright Image**

![bright64up](https://user-images.githubusercontent.com/44782426/158483116-515e0cf3-e73d-40a8-b473-4c9a8d21623f.jpg)

