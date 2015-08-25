// 遍历指定文件夹.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<io.h>
#include<string>
#include<vector>
#include<map>
using namespace std;

bool transfer(string fileName,int deep,string specifyName,vector<string> &vecFiles){
	string strdeep(2*deep,'-');
	_finddata_t fileInfo;
	long handle = _findfirst(fileName.c_str(),&fileInfo);
	if(handle == -1L)
		return false;
	do{
		if(fileInfo.attrib == 32){	
		}else if(string(fileInfo.name).compare(".") != 0 && string(fileInfo.name).compare("..") != 0){
			string deeperName = fileName.substr(0,fileName.find_last_of("\\")+1).append(fileInfo.name).append("\\*.*");  //是"."(当前目录)，".."(上一层目录)
			if(string(fileInfo.name).compare(specifyName) == 0){
				string s = deeperName;
				s = s.substr(0,s.size()-1);
				vecFiles.push_back(s);
			}	
			transfer(deeperName.c_str(),deep + 1,specifyName,vecFiles);
		}
	}while(_findnext(handle,&fileInfo) == 0);

	_findclose(handle);
	return true;
} 
int main(){
	vector<string> fileNames;
	transfer("F:\\video\\CDnet2014",2,"input",fileNames);
	for(vector<string>::iterator iter = fileNames.begin();iter != fileNames.end();iter++){
		cout<<*iter<<endl;
	}
	system("pause");
	return 0;
}


