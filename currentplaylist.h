#pragma once
#include"music.h"
#include"musicbase.h"
#include"musicidlist.h"
#include"playbutton.h"
#include<utility>
#include<vector>
#include<iostream>
#include<graphics.h>
extern musicbase database;
extern int mousex,mousey;
extern IMAGE delete_img;
extern IMAGE up_img;
extern IMAGE down_img;
class currentplaylist{
public:
	currentplaylist(int x,int y,int w,int h,int th,musicidlist* bl){
		posx=x;posy=y;width=w;height=h;viewy=0;texth=th;bindlist=bl;
		texth=textheight("L");
	}
	void draw(){
		if(!isshow) return;
		settextstyle(20,0,"Consolas");
		int inity=posy-viewy,i=0;
		POINT tr[3];
		for(musicidlistitem e:bindlist->data){
			tr[0]={posx+gap,inity+gap};
			tr[1]={posx+texth-gap,inity+texth/2};
			tr[2]={posx+gap,inity+texth-gap};
			const char* sn=e.name.c_str();
			outtextxy(posx+texth,inity,sn);
			settextcolor(BLACK);
			if(i==currentselect){
				setlinecolor(BLACK);
				polygon(tr,3);
			}
			if(bindlist->data[i].id==play_button->playcurid&&i==play_button->playcurrentselect){
				setfillcolor(BLACK);
				solidpolygon(tr,3);
			}
			if(i==currentin){
				setlinecolor(BLACK);
				putImageAlpha(posx+width-texth,inity,&delete_img);
				putImageAlpha(posx+width-2*texth,inity,&down_img);
				putImageAlpha(posx+width-3*texth,inity,&up_img);
				polygon(tr,3);
			}
			inity+=textheight(sn);
			i++;
		}
	}
	void process_wheel(int wheel){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			if((int)bindlist->data.size()*texth>height){
				viewy-=wheel/2;
				if(viewy<0)
					viewy=0;
				if(viewy>(int)bindlist->data.size()*texth-height)
					viewy=(int)bindlist->data.size()*texth-height;
			}
		}
	}
	void del(int cur){
		bindlist->data.erase(bindlist->data.begin()+cur);
		if(cur==play_button->playcurrentselect){
			if(cur>=bindlist->data.size()){
				currentin=currentselect=cur=0;
			}
			play_button->play(bindlist->data[cur].id,cur);
		}
		if(cur<currentselect){
			currentselect--;
			play_button->playcurrentselect--;
		}
	}
	void process_click(){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			if(posx+width-texth<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
				del(currentin);
			}else
				if(posx+width-2*texth<=mousex&&mousex<=posx+width-texth&&posy<=mousey&&mousey<=posy+height){
					int downid=(currentin+1)%(int)bindlist->data.size();
					if(currentin==play_button->playcurrentselect){
						std::swap(bindlist->data[downid],bindlist->data[currentin]);
						play_button->playcurrentselect=currentselect=downid;
					}else
						if(downid==play_button->playcurrentselect){
							std::swap(bindlist->data[downid],bindlist->data[currentin]);
							play_button->playcurrentselect=currentselect=currentin;
						}else{
							std::swap(bindlist->data[downid],bindlist->data[currentin]);
						}
						
				}else
					if(posx+width-3*texth<=mousex&&mousex<=posx+width-2*texth&&posy<=mousey&&mousey<=posy+height){
						int upid=(currentin-1+(int)bindlist->data.size())%(int)bindlist->data.size();
						if(currentin==play_button->playcurrentselect){
							std::swap(bindlist->data[upid],bindlist->data[currentin]);
							play_button->playcurrentselect=currentselect=upid;
						}else
							if(upid==play_button->playcurrentselect){
								std::swap(bindlist->data[upid],bindlist->data[currentin]);
								play_button->playcurrentselect=currentselect=currentin;
							}else{
								std::swap(bindlist->data[upid],bindlist->data[currentin]);
							}
					}else{
						int dy=mousey-posy+viewy;
						int n=dy/texth;
						if(n==currentselect){
							play_button->play(bindlist->data[currentselect].id,currentselect);
						}else{
							if(n<bindlist->data.size())
								currentselect=n;
						}
					}
			if(currentselect*texth<viewy)
				viewy=currentselect*texth+texth;
		}
		return;
	} 
	void process_mouse_move(){
		if(!isshow) return;
		if(posx<=mousex&&mousex<=posx+width&&posy<=mousey&&mousey<=posy+height){
			int dy=mousey-posy+viewy;
			int n=dy/texth;
			if(n<bindlist->data.size()){
					currentin=n;
			}
		} else{
			currentin=-1;
		}
	}
	void add(int id,std::string name){
		bindlist->data.push_back({id,false,name});
	}
	void play_next(){
		int cur=currentselect;
		cur=(cur+1)%(int)bindlist->data.size();
		currentselect=cur;
		play_button->play(bindlist->data[currentselect].id,currentselect);
	}
	void play_pre(){
		int cur=currentselect;
		cur=(cur-1+(int)bindlist->data.size())%(int)bindlist->data.size();
		currentselect=cur;
		play_button->play(bindlist->data[currentselect].id,currentselect);
	}
	void update(){
		char ans[100]={'#','#'};
		if(mciSendString("status music mode",ans,100,0)==0){
			if(ans[1]=='t'){
				play_button->playcurrentselect=play_button->playcurid=-1;
				mciSendString("close music",0,0,0);
				play_next();
			}
		}

	}
	int currentselect=-1;
	int currentin=-1;
	musicidlist* bindlist=nullptr;
	playbutton* play_button=nullptr;
	int posx;
	int posy;
	int width;
	int height;	
	int viewy;
	int texth;
	int gap=2;
	bool isshow=true;

};