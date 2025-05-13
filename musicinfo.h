#pragma once
#include<graphics.h>
#include"playbutton.h"
#include"musicidlist.h"
#include"util.h"
#include"playbutton.h"
#include"currentplaylist.h"
#include"scene.h"
extern Scene* list_scene;
extern int mousex,mousey;
class musicinfo{
public:
	musicinfo(int x,int y,int w,int h,int th,playbutton* pb,currentplaylist* bl){
		posx=x;posy=y;width=w;height=h;
		play_button=pb;
		bindlist=bl;
		texth=th;		
	}
	void draw(){
		settextstyle(texth,0,"Consolas");
		if(0>play_button->playcurrentselect||play_button->playcurrentselect>=bindlist->bindlist->data.size()){
			int tw=textwidth("当前无播放");
			outtextxy(posx+width/2-tw/2,posy,"当前无播放");
			return;
		}
		int tw=textwidth(bindlist->bindlist->data[play_button->playcurrentselect].name.c_str());
		outtextxy(posx+width/2-tw/2,posy+gap,bindlist->bindlist->data[play_button->playcurrentselect].name.c_str());
	}
	void process_mouse_move(){

	}
	void process_click(){
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			list_scene->changesubmenu(list_scene->submenu^2);
		}
	}
	void process_wheel(int wheel){

	}
	void update(){

	}
	int posx;
	int posy;
	int width;
	int height;	
	int viewy;
	int texth;
	int gap=5;
	int currentin;
	bool isshow=true;
	playbutton* play_button=nullptr;
	currentplaylist* bindlist=nullptr;
};