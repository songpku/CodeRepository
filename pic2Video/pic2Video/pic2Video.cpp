// 图片序列生成视频.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// mog图片序列.cpp : Defines the entry point for the console application.
//
#include"iostream"
#include <string.h>
#include<vector>
#include <io.h>
#include"highgui.h"
#include"cv.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;
using namespace cv;



//查找dir路径下所有文件(dir包括配置符，如c:\*.txt)
//ishavedir表示返回的文件名是否包含全路径，true为返回全路径的文件名，false只返回文件名
vector<string> FindAllFile(const char* dir,bool ishavedir=false)
{
	_finddata_t file;
	vector<string> file_list;
	long lf;
	if((lf = _findfirst(dir, &file))==-1l) { //_findfirst返回的是long型; long __cdecl _findfirst(const char *, struct _finddata_t *)
		return file_list;
	} else {
		do {
			if (ishavedir) {
				string tmppath=dir;
				int index=tmppath.find_last_of("*.")-1;
				tmppath=tmppath.substr(0,index).append(file.name);
				file_list.push_back(tmppath);
				//cout<<file.name<<endl;
			} else {

				file_list.push_back(file.name);
			}
		} while (_findnext( lf, &file ) == 0);//int _findnext(long, struct _finddata_t *);如果找到下个文件的名字成功的话就返回0,否则返回-1
		_findclose(lf);
		return file_list;
	}
}

int main(int argc,char* argv[])
{

	if(argc < 3)
		return 1;
	char* foldInputChar = argv[1];
	char* foldOutputChar = argv[2];
	string foldInput = foldInputChar;
	string foldOutput = foldOutputChar;
	cout<<"input:"<<foldInput<<endl<<"output:"<<foldOutput<<endl;
	if(foldOutput.find(".avi") == -1){
		cout<<"output is illegal"<<endl;
		return 1;
	}
	
	//fold = "F:\\video\\CDnet2014\\baseline\\baseline\\PETS2006\\input\\*.jpg";
	
	string file = foldInput;
	string filename = file;
	vector<string> vec = FindAllFile(file.c_str(),true);
	vector<string>::iterator iter = vec.begin();

	//string writerName = filename.substr(0,filename.size() - 6).append("-M.avi");
	string writerName = foldOutput;
	CvVideoWriter *pWriter = NULL;
	IplImage* pFrame = NULL;
	int frameNum = 0;
	while(iter!=vec.end()) 
	{
		pFrame = cvLoadImage((*(iter++)).c_str());
		if (!pFrame)
			break;
		if (frameNum == 0){
			pWriter =cvCreateVideoWriter(writerName.c_str(),CV_FOURCC('M','J','P','G'),25,cvGetSize(pFrame),1); 
		}else{
			cvWriteFrame(pWriter,pFrame);
		}
		cvReleaseImage(&pFrame);
		//cout<<frameNum++<<endl
		frameNum++;
		
	} 
		
	cvReleaseVideoWriter(&pWriter);
		
	return 0;
}





