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
		/*std::string p=database.base[play_button->playcurid].path;
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
		}*/
		//int tw=textwidth(bindlist->bindlist->data[play_button->playcurrentselect].name.c_str());
		RECT r;
		r.left=posx;r.top=posy+gap;r.right=getwidth();r.bottom=posy+texth*3;
		drawtext(bindlist->bindlist->data[play_button->playcurrentselect].name.c_str(),&r,DT_WORD_ELLIPSIS);
	}
	void process_mouse_move(){

	}
	void process_click(){
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
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