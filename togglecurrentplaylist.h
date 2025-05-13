#pragma once
#include<graphics.h>
#include<stdio.h>
#include<iostream>
#include"currentplaylist.h"
#include"util.h"
extern int mousex;
extern int mousey;
extern IMAGE toggle_list_img;
class togglecurrentplaylist{
public:
	togglecurrentplaylist(int xx,int yy,IMAGE* img,currentplaylist* bl){
		bindlist=bl;
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
			bindlist->isshow=1-bindlist->isshow;
		}
	}
	currentplaylist* bindlist;
private:
	int x;
	int y;
	int dx;
	int dy;
	IMAGE* image;
};
