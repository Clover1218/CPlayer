#pragma once
#include<graphics.h>
#include<stdio.h>
#include<iostream>
#include"util.h"
#include"musicbase.h"
#include"lyrics.h"
#include"volumebar.h"
extern int mousex;
extern int mousey;
extern musicbase database;
extern volumebar* volume_bar;
class playbutton{
public:		
	playbutton(int xx,int yy,IMAGE* playimg,IMAGE* pauseimg,lyrics* ls){
		x=xx;y=yy;
		dx=playimg->getwidth();dy=pauseimg->getheight();
		play_img=playimg;
		pause_img=pauseimg;
		lyrics_show=ls;
	}
	bool checkin(){
		if(x<=mousex&&mousex<=x+dx&&y<=mousey&&mousey<=y+dy){
			return true;
		}
		return false;
	}
	void draw(){
		char ans[100]={'#','#'};
		mciSendString("status music mode",ans,100,0);
		if(ans[1]=='l')
			putImageAlpha(x,y,pause_img);
		else
			if(ans[1]=='a'||ans[1]=='t'||ans[1]=='#')
				putImageAlpha(x,y,play_img);
	}
	void update(){
		//char ans[100]={'#','#'};
		//if(mciSendString("status music mode",ans,100,0)==0){
		//	if(ans[1]=='t'){
		//		play_next();
		//	}
		//}
	}
	void process_move(){

	}
	void process_click(){
		if(checkin()){
			if(isplaying){
				mciSendString("pause music",0,0,0);
				isplaying=false;
			}else{
				mciSendString("resume music",0,0,0);	
				isplaying=true;
			}
		}
	}	
	void play(int id,int selectid){
		if(selectid==-1){
			mciSendString("close music",0,0,0);
			playcurid=-1;
			playcurrentselect=-1;
			return;
		}
		char command[300];
		const char* ps=database.base[id].path.c_str();
		if(!(playcurid==id&&playcurrentselect==selectid)){
			if(isplaying)
				mciSendString("close music",0,0,0);
			sprintf_s(command,"open \"%s\" alias music",ps);
			if(mciSendString(command,0,0,0)!=0){
				printf("open %s failed!\n",ps);
			}else{
				isplaying=true;
				playcurid=id;
				playcurrentselect=selectid;
				volume_bar->setvolume(volume_bar->current);
				mciSendString("play music",0,0,0);
				lyrics_show->getlyrics(id);
			}
		}
	}
	void process_double_click(){
	}
	bool isplaying=false;
	int playcurid=-1;
	int playcurrentselect=-1;
private:
	int x;
	int y;
	int dx;
	int dy;
	IMAGE* play_img;
	IMAGE* pause_img;
	lyrics* lyrics_show;
};
