#include<iostream>
#include<io.h>
#include<string>
#include<vector>
#include<map>
using namespace std;

bool transfer(string fileName,int deep,string specifyName,map<string,vector<string> > &mapFiles,string suffix,string preName = "",string keyName = "",string abfold=""){
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

			cout<<strdeep<<abfold<<fileInfo.name<<" "<<fileInfo.attrib<<endl;
			abfold += fileInfo.name;
			abfold += "\\";
			if(string(fileInfo.name).compare(specifyName) != 0){
				keyName = preName;
			}	
			transfer(deeperName.c_str(),deep + 1,specifyName,mapFiles,suffix,fileInfo.name,keyName,abfold);
		}
	}while(_findnext(handle,&fileInfo) == 0);

	_findclose(handle);
	return true;
} 
int main(){
	map<string,vector<string> > fileNames;
	transfer("F:\\video\\CDnet2014*.*",2,"input",fileNames,"jpg");
	//	cout<<_A_SUBDIR; //16
	//	cout<<"============================================="<<endl;
	for(map<string,vector<string> >::iterator iter = fileNames.begin();iter != fileNames.end();iter++){
		cout<<iter->first<<endl;
		vector<string>::iterator subiter = iter->second.begin()；
		if(subiter->size()<=0){
			iter->first="";
		}
	}
	for(map<string,vector<string> >::iterator iter = fileNames.begin();iter != fileNames.end();iter++){
		cout<<iter->first<<endl;
		for(vector<string>::iterator subiter = iter->second.begin();subiter != iter->second.end(); subiter++){
			//cout<<"       "<<*subiter<<endl; 
		}
	}
	system("pause");
	return 0;
}
