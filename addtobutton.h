#pragma once
#include<graphics.h>
#include<stdio.h>
#include<iostream>
#include<filesystem>
#include<string>
#include"musicbase.h"
#include"util.h"
#include"musicidlist.h"
#include"playlistmanager.h"
namespace fs=std::filesystem;
extern int mousex;
extern int mousey;
extern musicbase database;
extern playlistmanager* playlist_manager;
static void traveldir(std::string p,musicidlist* bindlist){
	if(fs::exists(p)){
		for(auto &pp:fs::directory_iterator(p)){
			std::cout<<pp.path();
			if(pp.is_directory()==true){
				traveldir(pp.path().string(),bindlist);
			}else{
				if(pp.path().extension()==".mp3"){
					bindlist->add(database.add(pp.path().stem().string(),pp.path().string()),pp.path().stem().string());
				}
			}
		}
	}

}
class addtobutton{
public:
	addtobutton(int xx,int yy,IMAGE* img){
		x=xx;y=yy;
		dx=img->getwidth();dy=img->getheight();
		image=img;
		//traveldir("E://ScatteredFile//music",bindlist);
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
			bindlist=playlist_manager->data[playlist_manager->currentselect];
			CHAR a[300]={'#'};
			InputBox(a,200,_T("请输入要导入当前选择歌单的文件夹路径"),_T("CPlayer"),_T("Write Something..."),0,0,false);
			if(a[0]!='#'){
				std::string pa=a;
				traveldir(pa,bindlist);
				database.print();
			}

			
		}
	}
	musicidlist* bindlist=nullptr;

private:
	int x;
	int y;
	int dx;
	int dy;
	IMAGE* image;

};

