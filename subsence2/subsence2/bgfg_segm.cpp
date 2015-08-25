
// minimalistic foreground-background segmentation sample, based off OpenCV's bgfg_segm sample
#include "stdafx.h"
#include "BackgroundSubtractorSuBSENSE.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>

static void help() {
    printf("\nMinimalistic example of foreground-background segmentation in a video sequence using\n"
            "OpenCV's BackgroundSubtractor interface; will analyze frames from the default camera\n"
            "or from a specified file.\n\n"
            "Usage: \n"
            "  ./bgfg_segm [--camera]=<use camera, true/false>, [--file]=<path to file> \n\n");
}

const char* keys = {
    "{c  |camera   |true     | use camera or not}"
    "{f  |file     |tree.avi | movie file path  }"
};

int main(int argc, const char** argv) {
	/*if(argc<2)
		return 1;*/

    help();
    cv::CommandLineParser parser(argc, argv, keys);
    const bool bUseDefaultCamera = false/*parser.get<bool>("camera")*/;
    const std::string sVideoFilePath = /*parser.get<std::string>("file");*/"F:\\video\\CDnet2014\\baseline\\baseline\\PETS2006.avi";
	//const std::string sVideoFilePath = argv[1];
	std::string outputBGName,outputFGName;
	outputBGName = sVideoFilePath.substr(sVideoFilePath.find_last_of('\\')+1,sVideoFilePath.find_last_of('.') - sVideoFilePath.find_last_of('\\')-1).append("_BG.avi");
	outputFGName = sVideoFilePath.substr(sVideoFilePath.find_last_of('\\')+1,sVideoFilePath.find_last_of('.') - sVideoFilePath.find_last_of('\\')-1).append("_FG.avi");
	
	
	cv::VideoCapture oVideoInput;
    cv::Mat oCurrInputFrame, oCurrSegmMask, oCurrReconstrBGImg,oCurrResizeInputFrame;
    if(bUseDefaultCamera) {
        oVideoInput.open(0);
        oVideoInput >> oCurrInputFrame;
    }
    else {
        oVideoInput.open(sVideoFilePath);
        oVideoInput >> oCurrInputFrame;
        oVideoInput.set(CV_CAP_PROP_POS_FRAMES,0);
    }
    parser.printParams();
    if(!oVideoInput.isOpened() || oCurrInputFrame.empty()) {
        if(bUseDefaultCamera)
            printf("Could not open default camera.\n");
        else
            printf("Could not open video file at '%s'.\n",sVideoFilePath.c_str());
        return -1;
    }
	CvVideoWriter *writerFg =cvCreateVideoWriter(outputFGName.c_str(),
		CV_FOURCC('M','J','P','G'),25,
		oCurrInputFrame.size(),0); 
	CvVideoWriter *writerBg =cvCreateVideoWriter(outputBGName.c_str(),
		CV_FOURCC('M','J','P','G'),25,
		oCurrInputFrame.size(),1); 
	//resize(oCurrInputFrame,oCurrInputFrame,cvSize(352,288));
    oCurrSegmMask.create(oCurrInputFrame.size(),CV_8UC1);
    oCurrReconstrBGImg.create(oCurrInputFrame.size(),oCurrInputFrame.type());
    cv::Mat oSequenceROI(oCurrInputFrame.size(),CV_8UC1,cv::Scalar_<uchar>(255)); // for optimal results, pass a constrained ROI to the algorithm (ex: for CDnet, use ROI.bmp)
   /* cv::namedWindow("input",cv::WINDOW_NORMAL);
    cv::namedWindow("segmentation mask",cv::WINDOW_NORMAL);
    cv::namedWindow("reconstructed background",cv::WINDOW_NORMAL);*/
    BackgroundSubtractorSuBSENSE oBGSAlg;
    oBGSAlg.initialize(oCurrInputFrame,oSequenceROI);
	IplImage* writeImageFg,*writeImageBg;
    for(int frameNum=1;;frameNum++) {
		std::cout<<"frameNum: "<<frameNum<<std::endl;
        oVideoInput >> oCurrInputFrame;
        if(oCurrInputFrame.empty())
            break;
		//resize(oCurrInputFrame,oCurrInputFrame,cvSize(352,288));
        oBGSAlg(oCurrInputFrame,oCurrSegmMask,100.0/*,double(k<=100)*/); // lower rate in the early frames helps bootstrap the model when foreground is present
        oBGSAlg.getBackgroundImage(oCurrReconstrBGImg);
        imshow("input",oCurrInputFrame);
        imshow("segmentation mask",oCurrSegmMask);
        imshow("reconstructed background",oCurrReconstrBGImg);
		writeImageFg = &oCurrSegmMask.operator IplImage();
		writeImageBg = &oCurrReconstrBGImg.operator IplImage();
		cvWriteFrame(writerFg,writeImageFg);
		cvWriteFrame(writerBg,writeImageBg);
        if(cv::waitKey(1)==27)
            break;
    }
    return 0;
}

