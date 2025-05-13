#pragma once
#include<graphics.h>
#include<stdio.h>
#include<iostream>
#include"util.h"
#include"listscene.h"
extern int mousex;
extern int mousey;
extern IMAGE music_edit_img;
extern Scene* list_scene;
class switcheditlist{//now-1 list  now-2 edit
public:
	switcheditlist(int xx,int yy,IMAGE* img){
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
			list_scene->changesubmenu(list_scene->submenu^1);
		}
		
	}
private:
	int x;
	int y;
	int dx;
	int dy;
	IMAGE* image;
	int now=1;
};
