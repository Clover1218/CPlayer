#pragma once
#include"music.h"
#include<vector>
#include<string>
#include<iostream>
class musicbase{
public:
	musicbase()=default;
	~musicbase()=default;
	void pathConvert_Single2Double(std::string& s){
		std::string::size_type pos = 0;
		while((pos=s.find('\\',pos))!=std::string::npos){
			s.insert(pos,"\\");
			pos=pos+2;
		}	
	}
	int add(std::string name,std::string path){
		pathConvert_Single2Double(path);
		music te(int(base.size()),name,path);
		base.emplace_back(te);
		std::cout<<path<<std::endl;
		return (int)base.size()-1;

	}
	void print(){
		for(music m:base){
			std::cout<<m.id<<" "<<m.name<<" "<<m.path<<std::endl;
		}
	}
	std::vector<music> base;
	
};