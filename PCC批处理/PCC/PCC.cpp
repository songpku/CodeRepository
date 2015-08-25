// PCC.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"iostream"
#include <string.h>
#include<vector>
#include <io.h>
#include"highgui.h"
#include "cv.h"
#include <fstream>
using namespace std;
using namespace cv;

int FPSum=0,FNSum=0,TNSum=0,TPSum=0,GTBackgroundCount=0,GTforegroundCount=0;

bool transfer(string fileName,int deep,string specifyName,map<string,vector<string> > &mapFiles,string suffix,string preName = "",string keyName = ""){
	string strdeep(2*deep,'-');
	_finddata_t fileInfo;
	long handle = _findfirst(fileName.c_str(),&fileInfo);
	if(handle == -1L)
		return false;
	vector<string> *vec = NULL;
	if(keyName.size() != 0){
		vec = &mapFiles[keyName];
	}
	do{
		if(fileInfo.attrib == 32){	
			if(preName.compare(specifyName) == 0 && string(fileInfo.name).find(suffix) != std::string::npos) {
				string tmppath=fileName;
				int index=tmppath.find_last_of("*.")-2;
				tmppath=tmppath.substr(0,index).append(fileInfo.name);
				//	cout<<keyName<<strdeep<<tmppath<<" "<<fileInfo.attrib<<endl;
				if(vec != NULL){
					vec->push_back(tmppath);
				}
			}	
		}else if(string(fileInfo.name).compare(".") != 0 && string(fileInfo.name).compare("..") != 0){
			string deeperName = fileName.substr(0,fileName.find_last_of("\\")+1).append(fileInfo.name).append("\\*.*");  //是"."(当前目录)，".."(上一层目录)
			//	cout<<strdeep<<fileInfo.name<<" "<<fileInfo.attrib<<endl;
			if(string(fileInfo.name).compare(specifyName) == 0){
				keyName = preName;
			}	
			transfer(deeperName.c_str(),deep + 1,specifyName,mapFiles,suffix,fileInfo.name,keyName);
		}
	}while(_findnext(handle,&fileInfo) == 0);

	_findclose(handle);
	return true;
} 
/**
*FP:img[i]>GT[i]
*FN:img[i]<GT[i]
*TN:img[i]==GT[i]==0
*TP:img[i]==GT[i]==255
*/
void PCC(IplImage* img,IplImage* GT,int &FP,int &FN,int &TN,int &TP){
	FP=0;
	FN=0;
	TN=0;
	TP=0;
	cvThreshold(img,img,100,255,CV_THRESH_BINARY);
	cvThreshold(GT,GT,100,255,CV_THRESH_BINARY);
	//cvShowImage("test",img);
	//cvShowImage("GT",GT);
	//cvWaitKey(20);
	//IplImage* test = cvCreateImage(cvGetSize(img),8,1);
	for(int y=0;y<img->height;y++){

		uchar* imgY = (uchar*)(img->imageData + img->widthStep*y);
		uchar* GTY = (uchar*)(GT->imageData + GT->widthStep*y);
		//uchar* testY = (uchar*)(test->imageData + test->widthStep*y);

		for(int x=0;x<img->width;x++){
			uchar imgP = *(imgY+x*3);
			uchar GTP = *(GTY+x*3);
			//*(testY+x) = GTP;
			//cout<<0+imgP<<"-"<<0+GTP<<"  ";
			if(GTP == 255)
				GTforegroundCount++;
			else if(GTP == 0)
				GTBackgroundCount++;
			//GTP>0 ? GTforegroundCount++ : GTBackgroundCount++;
			//if(imgP>GTP){ 
			//	FP++;
			//	//cout<<0+imgP<<" "; 
			//}else if(imgP<GTP){
			//	FN++;
			//	//cout<<0+imgP<<" "; 
			//}else if(imgP == GTP && GTP == 0){
			//	TN++;
			//}else if(imgP == GTP && GTP == 255){
			//	TP++;
			//}
			if(imgP==255 && GTP<50){ 
				FP++;
				//cout<<0+imgP<<" "; 
			}else if(imgP==0 && GTP==255){
				FN++;
				//cout<<0+imgP<<" "; 
			}else if(imgP == 0 && GTP < 50){
				TN++;
			}else if(imgP == 255 && GTP == 255){
				TP++;
			}
			/*if(GTP==170){
			imgP == 255 ? GTforegroundCount++ : GTBackgroundCount;
			imgP == 255 ? TP++ : FN++;
			}*/
		}
	}
	//cvShowImage("test",test);
	FPSum+=FP;
	FNSum+=FN;
	TNSum+=TN;
	TPSum+=TP;
}
int _tmain(int argc, _TCHAR* argv[])
{
	string fold = "F:\\video\\CDnet2014\\*.*";
	string testFold = "F:\\git\\CodeRepository\\subsence2\\subsence2\\";
	//string file = fold;
	//string filename = file;
	map<string,vector<string> > fileNames;
	transfer(fold,2,"groundtruth",fileNames,"png");
	//for(map<string,vector<string> >::iterator iter = fileNames.begin();iter != fileNames.end();iter++){
	//	cout<<iter->first<<endl;
	//	for(vector<string>::iterator subiter = iter->second.begin();subiter != iter->second.end(); subiter++){
	//		cout<<"       "<<*subiter<<endl; 
	//	}
	//}
	string testImgName;
	CvVideoWriter *pWriter = NULL;
	IplImage* pFrame = NULL;
	int frameNum = 0;
	IplImage* GTimg = cvCreateImage(cvSize(352,288),8,3);
	IplImage* pFrameAgjust = cvCreateImage(cvSize(352,288),8,3);
	IplImage* GTimgOri;
	CvCapture* pCapture = NULL;
	string outFileName;
	ofstream outfileSum("vibe-Statistical-Sum.txt");
	if(!outfileSum){
		return 0;
	}
	outfileSum<<"name,pixelSum,frameNum,GTcount,FPSum,FNSum,TNSum,TPSum,GTforegroundCount,"
			  <<"GTBackgroundCount,PBC,Recall,Precision,F-Measure,pcc=(TNSum+TPSum)/(FPSum+FNSum+TNSum+TPSum),"
			  <<"TPSum/GTforegroundCount,(GTBackgroundCount-TNSum)/GTBackgroundCount"<<endl;
	for(map<string,vector<string> >::iterator iter = fileNames.begin();iter != fileNames.end();iter++){
		//cout<<iter->first<<endl;
		frameNum = 0;
		FPSum=0,FNSum=0,TNSum=0,TPSum=0,GTBackgroundCount=0,GTforegroundCount=0;
		int frameNum=0;
		int FP=0,FN=0,TN=0,TP=0;
		int GTcount = 0;
		int pixelNum = 0;
		outFileName = testImgName = testFold;
		testImgName = testImgName.append(iter->first).append("_FG.avi");
		pCapture = NULL;
		pCapture = cvCreateFileCapture(testImgName.c_str());
		if(!pCapture)
			continue;
		outfileSum<<iter->first<<",";
		cout<<iter->first<<","<<endl;
		for(vector<string>::iterator subiter = iter->second.begin();subiter != iter->second.end(); subiter++,frameNum++){
			//cout<<"       "<<*subiter<<endl; 
			/*if(GTcount == 0){
				subiter++;
			}*/
			GTimgOri = cvLoadImage((*subiter).c_str());
			pFrame = cvQueryFrame(pCapture);
			if (!GTimgOri || !pFrame)
				break;
			if (frameNum == 0){ 
				pixelNum = pFrame->width*pFrame->height;
				if(pFrame->width != 352 && pFrame->height != 288)
					cout<<"adjust"<<endl;
			}
			CvScalar scalar = cvGet2D(GTimgOri,50,200);
			if(scalar.val[0] == 85){
				if(GTimgOri)
					cvReleaseImage(&GTimgOri);
				continue;
				
			}
			
			cvResize(pFrame,pFrameAgjust,CV_INTER_LINEAR);
			cvResize(GTimgOri,GTimg,CV_INTER_LINEAR);//将视频大小转换成352*288标准大小.
			PCC(pFrameAgjust,GTimg,FP,FN,TN,TP);

			GTcount++;
			if(GTimgOri)
				cvReleaseImage(&GTimgOri);
			//if(pFrame)
			//	cvReleaseImage(&pFrame);
			cout<<frameNum<<"  "<<GTcount<<endl;
		}
		try{
			int pixelSum = pixelNum*GTcount;
			cout<<"pixelSum="<<pixelSum<<" frameNum="<<frameNum<<" GTcount="<<GTcount
				<<" FPSum="<<FPSum<<" FNSum="<<FNSum<<" TNSum="<<TNSum<<" TPSum="<<TPSum<<endl;
			outfileSum<<pixelSum<<","<<frameNum<<","<<GTcount
				<<","<<FPSum<<","<<FNSum<<","<<TNSum<<","<<TPSum;
			cout<<"GTforegroundCount="<<GTforegroundCount<<" GTBackgroundCount="<<GTBackgroundCount<<endl;
			outfileSum<<","<<GTforegroundCount<<","<<GTBackgroundCount;
			double pcc = (double)(TNSum+TPSum)/(FPSum+FNSum+TNSum+TPSum);
			cout<<"pcc=(TNSum+TPSum)/(FPSum+FNSum+TNSum+TPSum)="<<pcc;
			cout<<"TPSum/GTforegroundCount="<<(double)TPSum/GTforegroundCount<<endl;//体现检测率
			cout<<"(GTBackgroundCount-TNSum)/GTBackgroundCount="<<(double)(GTBackgroundCount-TNSum)/GTBackgroundCount<<endl;//体现噪声水平
			double Recall = (double)TPSum/(TPSum+FNSum);
			double Precision = (double)TPSum/(TPSum+FPSum);
			double F_measure = (2*Precision *Recall)/(Precision+Recall);
			outfileSum<<","<<(double)(FNSum+FPSum)/(TPSum+TNSum+FPSum+FNSum);
			outfileSum<<","<< Recall;
			outfileSum<<","<< Precision;
			outfileSum<<","<< F_measure;
			outfileSum<<","<<pcc;
			outfileSum<<","<<(double)TPSum/GTforegroundCount;//体现检测率
			outfileSum<<","<<(double)(GTBackgroundCount-TNSum)/GTBackgroundCount<<endl;//体现噪声水平
			//outfileSum.flush();
		}catch(Exception e){
			e.what();
			outfileSum.close();
		}
		//outfileSum.close();
		if(pWriter){
			cvReleaseVideoWriter(&pWriter);
		}
		if(pCapture)
			cvReleaseCapture(&pCapture);
	}
	outfileSum.close();
	
	return 0;
}





