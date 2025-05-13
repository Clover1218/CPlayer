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
extern int mousex;
extern int mousey;
extern playlistmanager* playlist_manager;
class addlistbutton{
public:
	addlistbutton(int xx,int yy,IMAGE* img){
		x=xx;y=yy;
		dx=img->getwidth();dy=img->getheight();
		image=img;
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
			InputBox(a,200,_T("请输入新建歌单名称"),_T("CPlayer"),_T("Write Something..."),0,0,false);
			if(a[0]!='#'){
				std::string pa=a;
				playlist_manager->add(pa);
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

