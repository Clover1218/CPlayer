#pragma once
#include<graphics.h>
#include<stdio.h>
#include<iostream>
#include<filesystem>
#include<string>
#include"musicbase.h"
#include"util.h"
namespace fs=std::filesystem;
extern int mousex;
extern int mousey;
extern musicbase database;
static void traveldir(std::string p,currentplaylist* bindlist){
	if(fs::exists(p)){
		for(auto &pp:fs::directory_iterator(p)){
			if(pp.is_directory()==true){
				traveldir(pp.path().string(),bindlist);
			}else{
				if(pp.path().extension()==".mp3"||pp.path().extension()==".wav"){
					bindlist->add(database.add(pp.path().stem().string(),pp.path().string()),pp.path().stem().string());
				}
			}
		}
	}
}
class addmusicbutton{
public:

	addmusicbutton(int xx,int yy,IMAGE* img,currentplaylist* cl){
		x=xx;y=yy;
		dx=img->getwidth();dy=img->getheight();
		image=img;
		bindlist=cl;
		traveldir("E://ScatteredFile//music//歌曲下载//Music",bindlist);
		//traveldir("D:\\KwDownload\\song",bindlist);
		//traveldir("E:\\ScatteredFile\\music",bindlist);
	}
	bool checkin(){
		if(x<=mousex&&mousex<=x+dx&&y<=mousey&&mousey<=y+dy){
			return true;
		}
		return false;
	}
	void draw(){
		drawAlpha(image,x,y);
	}
	void process_move(){

	}
	void process_click(){
		if(checkin()){
			CHAR a[300]={'#'};
			InputBox(a,200,_T("请输入要导入音乐的文件夹路径"),_T("CPlayer"),_T("Write Something..."),0,0,false);
			if(a[0]!='#'){
				std::string pa=a;
				traveldir(pa,bindlist);
				database.print();
			}

			
		}
	}
	currentplaylist* bindlist=nullptr;

private:
	int x;
	int y;
	int dx;
	int dy;
	IMAGE* image;

};

