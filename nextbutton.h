#pragma once
#include<graphics.h>
#include<stdio.h>
#include<iostream>
#include"util.h"
#include"currentplaylist.h"
#include"playbutton.h"
extern int mousex;
extern int mousey;
class nextbutton{
public:
	nextbutton(int xx,int yy,IMAGE* img,currentplaylist* bl){
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
		//putimage(x,y,image);
		drawAlpha(image,x,y);
	}
	void process_move(){

	}
	void process_click(){
		if(checkin()){
			bindlist->play_next();
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
