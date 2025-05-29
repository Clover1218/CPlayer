#pragma once
#include<graphics.h>
#include"playbutton.h"
#include"musicidlist.h"
#include"util.h"
#include"playbutton.h"
#include"currentplaylist.h"
#include"scene.h"
#include"musicbase.h"
extern Scene* list_scene;
extern int mousex,mousey;
extern IMAGE cd_img;
extern musicbase database;
class musiccover{
public:
	musiccover(int x,int y,int w,int h,playbutton* pb,currentplaylist* bl){
		posx=x;posy=y;width=w;height=h;
		play_button=pb;
		bindlist=bl;
	}
	void draw(){
		if(play_button->playcurid==-1)
			return;
		std::string p=database.base[play_button->playcurid].path;
		size_t l=p.length();
        p[l-1]='g';p[l-2]='p';p[l-3]='j';
		IMAGE t;
		loadimage(&t,p.c_str());
		if(t.getwidth()==0){
			drawAlpha(&cd_img,posx,posy);
		}else{
			IMAGE xx;
			loadimage(&xx,p.c_str(),100,100);
			putimage(posx,posy,&xx);
		}
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